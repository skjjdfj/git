// 初始置换IP
public static int[] IP(int[] input) {
    int[] output = new int[64];
    int[] ipTable = {58, 50, 42, 34, 26, 18, 10, 2,
                     60, 52, 44, 36, 28, 20, 12, 4,
                     62, 54, 46, 38, 30, 22, 14, 6,
                     64, 56, 48, 40, 32, 24, 16, 8,
                     57, 49, 41, 33, 25, 17, 9, 1,
                     59, 51, 43, 35, 27, 19, 11, 3,
                     61, 53, 45, 37, 29, 21, 13, 5,
                     63, 55, 47, 39, 31, 23, 15, 7};
    for (int i = 0; i < 64; i++) {
        output[i] = input[ipTable[i] - 1];
    }
    return output;
}

// 逆置换IP-1  
public static int[] IPInverse(int[] input) {
    int[] output = new int[64];
    int[] ipInverseTable = {40, 8, 48, 16, 56, 24, 64, 32,
                            39, 7, 47, 15, 55, 23, 63, 31,
                            38, 6, 46, 14, 54, 22, 62, 30,
                            37, 5, 45, 13, 53, 21, 61, 29,
                            36, 4, 44, 12, 52, 20, 60, 28,
                            35, 3, 43, 11, 51, 19, 59, 27,
                            34, 2, 42, 10, 50, 18, 58, 26,
                            33, 1, 41, 9, 49, 17, 57, 25};
    for (int i = 0; i < 64; i++) {
        output[i] = input[ipInverseTable[i] - 1];
    }
    return output;
}

// PC-1置换
public static int[] PC1(int[] input) {
    int[] output = new int[56];
    int[] pc1Table = {57, 49, 41, 33, 25, 17, 9,
                      1, 58, 50, 42, 34, 26, 18,
                      10, 2, 59, 51, 43, 35, 27,
                      19, 11, 3, 60, 52, 44, 36,
                      63, 55, 47, 39, 31, 23, 15,
                      7, 62, 54, 46, 38, 30, 22,
                      14, 6, 61, 53, 45, 37, 29,
                      21, 13, 5, 28, 20, 12, 4};
    for (int i = 0; i < 56; i++) {
        output[i] = input[pc1Table[i] - 1];
    }
    return output;
}

// PC-2置换  
public static int[] PC2(int[] input) {
    int[] output = new int[48];
    int[] pc2Table = {14, 17, 11, 24, 1, 5,
                      3, 28, 15, 6, 21, 10,
                      23, 19, 12, 4, 26, 8,
                      16, 7, 27, 20, 13, 2,
                      41, 52, 31, 37, 47, 55,
                      30, 40, 51, 45, 33, 48,
                      44, 49, 39, 56, 34, 53,
                      46, 42, 50, 36, 29, 32};
    for (int i = 0; i < 48; i++) {
        output[i] = input[pc2Table[i] - 1];
    }
    return output;
}

// S盒置换
public static int[] SBoxes(int[] input) {
    int[][] sBoxes = {{14, 4, 13, 1, 2, 15, 11, 8, 3, 10, 6, 12, 5, 9, 0, 7},
                     {0, 15, 7, 4, 14, 2, 13, 1, 10, 6, 12, 11, 9, 5, 3, 8},
                     {4, 1, 14, 8, 13, 6, 2, 11, 15, 12, 9, 7, 3, 10, 5, 0},
                     {15, 12, 8, 2, 4, 9, 1, 7, 5, 11, 3, 14, 10, 0, 6, 13}};
    int[] output = new int[32];
    for (int i = 0; i < 8; i++) {
        int row = (input[i * 6] * 2) + input[i * 6 + 5];
        int col = (input[i * 6 + 1] * 8) + (input[i * 6 + 2] * 4) + (input[i * 6 + 3] * 2) + input[i * 6 + 4];
        int value = sBoxes[i][row * 16 + col];
        output[i * 4] = (value & 8) >> 3;
        output[i * 4 + 1] = (value & 4) >> 2;
        output[i * 4 + 2] = (value & 2) >> 1;
        output[i * 4 + 3] = value & 1;
    }
    return output;
}



// P置换
public static int[] PPermutation(int[] input) {
    int[] output = new int[32];
    int[] pTable = {16, 7, 20, 21, 29, 12, 28, 17,
                    1, 15, 23, 26, 5, 18, 31, 10,
                    2, 8, 24, 14, 32, 27, 3, 9,
                    19, 13, 30, 6, 22, 11, 4, 25};
    for (int i = 0; i < 32; i++) {
        output[i] = input[pTable[i] - 1];
    }
    return output;
}

// E置换
public static int[] EExpansion(int[] input) {
    int[] output = new int[48];
    int[] eTable = {32, 1, 2, 3, 4, 5,
                    4, 5, 6, 7, 8, 9,
                    8, 9, 10, 11, 12, 13,
                    12, 13, 14, 15, 16, 17,
                    16, 17, 18, 19, 20, 21,
                    20, 21, 22, 23, 24, 25};
    for (int i=0;i < 32; i++){
        output[i] = input[pTable[i]-1];
    }
    return output;
}


public class DESAlgorithm {
    public static void main(String[] args) {
        // 测试初始置换IP和逆置换IP-1
        int[] inputIP = {0, 0, 0, 0, 0, 0, 0, 1};
        int[] outputIP = IP(inputIP);
        System.out.println("Initial Permutation (IP):");
        printBinaryArray(outputIP);
        int[] outputIPInverse = IPInverse(outputIP);
        System.out.println("Inverse Initial Permutation (IP^-1):");
        printBinaryArray(outputIPInverse);

        // 测试PC-1和PC-2置换
        char[] inputPC1 = {'0', '1', '1', '0', '1', '1', '0'};
        int[] outputPC1 = PC1(charToBinaryArray(inputPC1));
        System.out.println("PC-1 Permutation:");
        printBinaryArray(outputPC1);
        int[] outputPC2 = PC2(outputPC1);
        System.out.println("PC-2 Permutation:");
        printBinaryArray(outputPC2);

        // 测试S盒、P置换和E置换
        int[] inputSBoxes = {0, 0, 0, 0, 0, 1, 0, 1, 0, 1, 0, 1, 1, 0, 0, 0};
        int[] outputSBoxes = SBoxes(inputSBoxes);
        System.out.println("S-Boxes Permutation:");
        printBinaryArray(outputSBoxes);
        int[] outputPPermutation = PPermutation(outputSBoxes);
        System.out.println("P Permutation:");
        printBinaryArray(outputPPermutation);
        int[] outputEExpansion = EExpansion(outputPPermutation);
        System.out.println("E Expansion:");
        printBinaryArray(outputEExpansion);
    }

    // 一些辅助函数
    private static void printBinaryArray(int[] array) {
        for (int i : array) {
            System.out.print(i);
        }
        System.out.println();
    }

    private static int[] charToBinaryArray(char[] input) {
        int[] output = new int[input.length];
        for (int i = 0; i < input.length; i++) {
            output[i] = input[i] - '0';
        }
        return output;
    }

    // 上述DES算法实现省略...
}
