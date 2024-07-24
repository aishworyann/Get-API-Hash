import sys

def __ROR__(val, shift):
    return ((val & 0xffffffff) >> shift) | ((val << (32 - shift)) & 0xffffffff)

def calculate_hash(dll_name):
    result = 0
    for d in dll_name:
        d = ord(d)
        if d > 0x60:
            d -= 0x20
        result = __ROR__(result, 0xD)
        result += d
    
    return result

if __name__ == '__main__':
    dll_name = sys.argv[1]
    print("hash: %x" % calculate_hash(dll_name))