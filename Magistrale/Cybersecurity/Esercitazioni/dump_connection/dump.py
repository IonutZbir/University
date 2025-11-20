import re

network_protocols = {
    "0000": "0x05DC IEEE 802.3 Length Fields",
    "0600": "0x0600 Xerox XNS IDP",
    "0800": "0x0800 IPv4",
    "0806": "0x0806 ARP",
    "081C": "0x081C Symbolics Private",
    "1000": "0x1000 Berkeley Trailer",
}

ip_protocols = {
    1:  "ICMP",
    6:  "TCP",
    17: "UDP",
}

def hex_to_ascii(h):
    try:
        raw = bytes.fromhex(h)
        return "".join(chr(b) if 32 <= b <= 126 else "." for b in raw)
    except:
        return ""

# -------------------------
# Utility classes
# -------------------------

class IpAddress:
    def __init__(self, addr: str):
        self._parse(addr)

    def _parse(self, addr):
        s = re.sub(r"[^0-9a-fA-F]", "", addr)
        if len(s) != 8:
            raise ValueError("Invalid IP address hex")

        self.dot_hex = ".".join(s[i:i+2] for i in range(0, 8, 2))
        self.dot_dec = ".".join(str(int(s[i:i+2], 16)) for i in range(0, 8, 2))

    def __str__(self):
        return f"{self.dot_dec} ({self.dot_hex})"


class MacAddress:
    def __init__(self, addr: str):
        self._parse(addr)

    def _parse(self, addr):
        s = re.sub(r"[^0-9a-fA-F]", "", addr)
        if len(s) != 12:
            raise ValueError("Invalid MAC address")
        self.dot = ".".join(s[i:i+2] for i in range(0, 12, 2))

    def __str__(self):
        return self.dot


# -------------------------
# TCP
# -------------------------

class Tcp:
    def __init__(self, src_port, dst_port, seq, ack,
                 do_byte, flags_byte, window, checksum, urgent):

        self.source_port = int(src_port, 16)
        self.dest_port = int(dst_port, 16)
        self.seq_number = int(seq, 16)
        self.ack = int(ack, 16)

        # Data Offset (4 bit alti del do_byte)
        self.data_offset = (int(do_byte, 16) >> 4) * 4

        # Flags
        self.flags = self._parse_flags(do_byte, flags_byte)

        self.window = int(window, 16)
        self.checksum = int(checksum, 16)
        self.urgent = int(urgent, 16)

    def _parse_flags(self, do_byte, flags_byte):
        do_val = int(do_byte, 16)
        fl_val = int(flags_byte, 16)

        flags = []
        if do_val & 0x01: flags.append("NS")
        if fl_val & 0x80: flags.append("CWR")
        if fl_val & 0x40: flags.append("ECE")
        if fl_val & 0x20: flags.append("URG")
        if fl_val & 0x10: flags.append("ACK")
        if fl_val & 0x08: flags.append("PSH")
        if fl_val & 0x04: flags.append("RST")
        if fl_val & 0x02: flags.append("SYN")
        if fl_val & 0x01: flags.append("FIN")

        return flags

    def __str__(self):
        out = "\n    TCP:\n"
        out += f"        Source Port: {self.source_port}\n"
        out += f"        Dest Port: {self.dest_port}\n"
        out += f"        Sequence Number: {self.seq_number}\n"
        out += f"        Ack: {self.ack}\n"
        out += f"        Header Length: {self.data_offset} bytes\n"
        out += f"        Flags: {', '.join(self.flags)}\n"
        out += f"        Window: {self.window}\n"
        out += f"        Checksum: {self.checksum}\n"
        out += f"        Urgent Pointer: {self.urgent}\n"
        out += f"        Payload (hex): {self.payload}\n"
        out += f"        Payload (text): {self.payload_ascii}\n"
        return out



# -------------------------
# IP Header
# -------------------------

class Ip:
    def __init__(self, version, ihl, dscp_ecn, total_length,
                 ttl, protocol, checksum, src: IpAddress, dst: IpAddress, payload=None):

        self.version = int(version, 16)
        self.ihl = int(ihl, 16) * 4
        self.total_len = int(total_length, 16)
        self.ttl = int(ttl, 16)
        self.protocol = ip_protocols.get(int(protocol, 16), f"Unknown({protocol})")
        self.checksum = checksum
        self.src = src
        self.dst = dst
        self.payload = payload

    def __str__(self):
        out = "\n  IP Header:\n"
        out += f"    Version: {self.version}\n"
        out += f"    IHL: {self.ihl} bytes\n"
        out += f"    Total Length: {self.total_len} bytes\n"
        out += f"    TTL: {self.ttl}\n"
        out += f"    Protocol: {self.protocol}\n"
        out += f"    Source: {self.src}\n"
        out += f"    Dest:   {self.dst}\n"
        if self.payload:
            out += str(self.payload)
        return out


# -------------------------
# Ethernet frame
# -------------------------

class Ethernet:
    def __init__(self, dst, src, ethertype, payload=None):
        self.dst = dst
        self.src = src
        self.ethertype = network_protocols.get(ethertype.upper(), f"Unknown({ethertype})")
        self.payload = payload

    def __str__(self):
        out = "Ethernet Frame:\n"
        out += f"  Dest: {self.dst}\n"
        out += f"  Src:  {self.src}\n"
        out += f"  Type: {self.ethertype}\n"
        if self.payload:
            out += str(self.payload)
        return out


# -------------------------
# Main Parser
# -------------------------

class Parser:
    def __init__(self, file):
        self.file = file
        self.connection = []

    def parse(self):
        with open(self.file, "r") as fh:
            line = fh.read().replace(" ", "").strip()

        cursor = 0

        while cursor + 28 < len(line):  # minimo: MAC MAC EtherType
            dst = MacAddress(line[cursor:cursor+12]); cursor += 12
            src = MacAddress(line[cursor:cursor+12]); cursor += 12
            ethertype = line[cursor:cursor+4]; cursor += 4

            ip = None

            if ethertype.lower() == "0800":
                ip_start = cursor

                vihl = line[cursor:cursor+2]
                version = vihl[0]
                ihl = vihl[1]
                cursor += 2

                dscp_ecn = line[cursor:cursor+2]; cursor += 2
                total_length = line[cursor:cursor+4]; cursor += 4
                cursor += 4   # identification
                cursor += 4   # flags+frag
                ttl = line[cursor:cursor+2]; cursor += 2
                protocol = line[cursor:cursor+2]; cursor += 2
                checksum = line[cursor:cursor+4]; cursor += 4

                src_ip = IpAddress(line[cursor:cursor+8]); cursor += 8
                dst_ip = IpAddress(line[cursor:cursor+8]); cursor += 8

                ip = Ip(version, ihl, dscp_ecn, total_length,
                        ttl, protocol, checksum, src_ip, dst_ip)

                tcp_start = ip_start + ip.ihl * 2
                ip_end = ip_start + ip.total_len * 2

                if ip.protocol == "TCP" and cursor == tcp_start:
                    src_port = line[cursor:cursor+4]; cursor += 4
                    dst_port = line[cursor:cursor+4]; cursor += 4
                    seq_num = line[cursor:cursor+8]; cursor += 8
                    ack_num = line[cursor:cursor+8]; cursor += 8

                    do_byte = line[cursor:cursor+2]; cursor += 2
                    flags_byte = line[cursor:cursor+2]; cursor += 2

                    window = line[cursor:cursor+4]; cursor += 4
                    tcp_checksum = line[cursor:cursor+4]; cursor += 4
                    urgent = line[cursor:cursor+4]; cursor += 4

                    tcp = Tcp(src_port, dst_port, seq_num, ack_num,
                              do_byte, flags_byte, window,
                              tcp_checksum, urgent)

                    # --------------------------------------
                    # Extract PAYLOAD TCP
                    # --------------------------------------

                    tcp_header_len_hex = tcp.data_offset * 2  # bytes → hex chars
                    tcp_header_start = tcp_start
                    tcp_data_start = tcp_header_start + tcp_header_len_hex
                    tcp_data_end = ip_end

                    if tcp_data_start < tcp_data_end:
                        tcp_payload_hex = line[tcp_data_start:tcp_data_end]
                    else:
                        tcp_payload_hex = ""

                    tcp.payload = tcp_payload_hex
                    tcp.payload_ascii = hex_to_ascii(tcp_payload_hex)
                    ip.payload = tcp


                cursor = ip_end

            frame = Ethernet(dst, src, ethertype, ip)
            self.connection.append(frame)

    def __str__(self):
        return "\n".join(str(c) for c in self.connection)


if __name__ == "__main__":
    p = Parser("dump.txt")
    p.parse()
    print(p)
