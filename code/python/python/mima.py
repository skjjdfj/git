def hex_to_bin(hex_str):
    return bin(int(hex_str, 16))[2:]

def bin_multiplication(bin1, bin2):
    return bin(int(bin1, 2) * int(bin2, 2))[2:]

def mod_bin(bin_str, mod_str):
    mod_int = int(mod_str, 2)
    result_int = int(bin_str, 2) % mod_int
    return bin(result_int)[2:]

def bin_to_hex(bin_str):
    return hex(int(bin_str, 2))[2:].upper()

# 输入的16进制字符串
hex_str1 = "02"
hex_str2 = "38"

# 把16进制字符串转换为二进制字符串
bin_str1 = hex_to_bin(hex_str1)
bin_str2 = hex_to_bin(hex_str2)

# 打印转换后的二进制字符串
print(f"{hex_str1} in binary: {bin_str1}")
print(f"{hex_str2} in binary: {bin_str2}")

# 二进制字符串相乘
multiplied_bin = bin_multiplication(bin_str1, bin_str2)

# 打印相乘后的二进制字符串
print(f"Multiplication result in binary: {multiplied_bin}")

# 取模操作
mod_str = "100011011"  # 100011011 in binary
modded_bin = mod_bin(multiplied_bin, mod_str)

# 打印取模后的二进制字符串
print(f"Result after mod operation in binary: {modded_bin}")

# 转换为16进制
result_hex = bin_to_hex(modded_bin)

# 打印最终结果
print(f"Final result in hex: {result_hex}")

