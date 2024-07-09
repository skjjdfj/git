file = open("391.zlib", "rb")
content = file.read()
hex_string = ""
for byte in content:
    hex_string += hex(byte)[2:].zfill(2)
print(hex_string)
result = binascii.unhexlify(hex_string)
print(result)
result = zlib.decompress(result)
print(result)

//
file = open("391.zlib", "rb")
content = file.read()
result = zlib.decompress(content)
print(result)

//

import zlib

# 打开二进制文件并读取内容
with open('391.zlib', 'rb') as f:
    compressed_data = f.read()

# 使用 zlib.decompress() 对压缩数据进行解压缩
decompressed_data = zlib.decompress(compressed_data)

# 输出解压缩后的数据
print(decompressed_data)