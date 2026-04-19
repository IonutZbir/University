from io import BytesIO
import helpers

class Block:
    def __init__(self, version: bytes, prev_hash: bytes, merkle_root: bytes, timestamp: bytes, bits: bytes, nonce: bytes):
        # il target in bitcoin è del tipo: exp;mantissa
        #                                  2      6   byte
        self.version = version
        self.prev_hash = prev_hash
        self.merkle_root = merkle_root
        self.timestamp = timestamp
        self.bits = bits
        self.nonce = nonce
        
    @classmethod
    def parse(cls, byte_str: bytes) -> Block:
        reader = BytesIO(byte_str)
        version = reader.read(4)
        prev_hash = reader.read(32)
        merkle_root = reader.read(32)
        timestamp = reader.read(4)
        bits = reader.read(4)
        nonce = reader.read(4)
        
        return Block(version[::-1], prev_hash[::-1], merkle_root[::-1], timestamp[::-1], bits[::-1], nonce[::-1])

    def serialize(self):
        return self.version[::-1] + self.prev_hash[::-1] + self.merkle_root[::-1] + self.timestamp[::-1] + self.bits[::-1] + self.nonce[::-1]

    def hash(self):
        return helpers.hash256(self.serialize())[::-1]
    
    def target(self):
        return int.from_bytes(self.bits[1:], byteorder='big') * pow(256, self.bits[0] - 3)

    def is_valid_target(self):
        return int.from_bytes(self.hash(), 'big') <= self.target()

    def update_nonce(self, i: int):
        self.nonce = i.to_bytes(4, 'big')

    def __str__(self):
        out = dict()
        out["version"] = self.version.hex()
        out["prev_hash"] = self.prev_hash.hex()
        out["merkle_root"] = self.merkle_root.hex()
        out["timestamp"] = self.timestamp.hex()
        out["bits"] = self.bits.hex()
        out["nonce"] = int(self.nonce.hex(), 16)
        out["nonceHex"] = self.nonce.hex()
        
        return out.__str__()

if __name__ == "__main__":
    header = '00e0a323fd73cb833ac1b091f339b14cb320f98fa7756d31fe520100000000000000000093918fc1931493becee43e9ec9f4d12fbcb4e8815653163ea58ecffe8c4e6a361f9edc6984060217395b599f'
    blk = Block.parse(bytes.fromhex(header))
    print(blk)          
    print(blk.hash().hex())
    print(hex(blk.target()))
    print(blk.is_valid_target())
    
    
    
    
    