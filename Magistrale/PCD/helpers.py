from hashlib import sha256
from datetime import datetime

def hash256(byte_str: bytes) -> bytes:
    return sha256(sha256(byte_str).digest()).digest()

def now():
    return int(datetime.now().timestamp()).to_bytes(4, 'big')


# bytes.fromhex(header)
# le seguenze di byte sono interpretate in little-endian
# hash256(bytes.fromhex(header)[::-1].hex())


