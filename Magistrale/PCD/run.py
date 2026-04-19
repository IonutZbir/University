from block import Block
import helpers

GENESIS = '0100000000000000000000000000000000000000000000000000000000000000000000003ba3edfd7a7b12b27ac72c3e67768f617fc81bc3888a51323a9fb8aa4b1e5e4a29ab5f49ffff001d1dac2b7c'
GENESIS_HASH = '000000000019d6689c085ae165831e934ff763ae46a2a6c172b3f1b60a8ce26f'

blk = Block.parse(bytes.fromhex(GENESIS))
print(blk)
print(blk.hash().hex())

height = 0

while True:
    blk.prev_hash = blk.hash()
    blk.bits = bytes.fromhex("1e02ffff")
    blk.timestamp = helpers.now()
    height += 1
    tx = 'PCD 25/26 block' + str(height)
    blk.merkle_root = helpers.hash256(tx.encode('utf-8'))
    # print(blk.merkle_root.hex())
    i = 0
    blk.update_nonce(i)
    flag = blk.is_valid_target()
    while not flag:
        if i == 2**32:
            i = 0
            blk.timestamp = helpers.now()
        i += 1
        blk.update_nonce(i)
        flag = blk.is_valid_target()
    print(blk.hash().hex())
    print(blk)
    print()