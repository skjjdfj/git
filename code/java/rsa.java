package RSA;
 
import org.apache.commons.codec.binary.Base64;
 
import java.io.BufferedReader;
import java.io.FileReader;
import java.security.*;
import java.security.interfaces.RSAPrivateKey;
import java.security.interfaces.RSAPublicKey;
import java.security.spec.PKCS8EncodedKeySpec;
import java.security.spec.X509EncodedKeySpec;
import java.util.HashMap;
import java.util.Map;
 

public class RsaSignature {
 
    //数字签名 - 签名验证算法
    private static final String SIGNATRUE_ALGORITHM = "MD5withRSA";
    //数字签名 - RSA算法
    private static final String KEY_ALGORITHM = "RSA";
    //私钥
    private static final String PRIVATEKEY = "RSAPrivateKey";
    //公钥
    private static final String PUBLICKEY = "RSAPublicKey";
 
    /**
     * RSA长度
     * 默认是 1024
     * 必须是 64的倍数
     * 范围：512 - 65536
     */
    private static final int KeySize = 512; // 512 位 2进制，128 位 16进制
 
    /**
     * 初始化
     *
     * @return map
     * @throws Exception
     */
    public static Map<String, Object> initKey() throws Exception {
        //实例化，生成器
        KeyPairGenerator keyPairGenerator = KeyPairGenerator.getInstance(KEY_ALGORITHM);
        //初始化
        keyPairGenerator.initialize(KeySize);
        //获取公私钥对
        KeyPair keyPair = keyPairGenerator.generateKeyPair();
        //获取私钥
        RSAPrivateKey privateKey = (RSAPrivateKey) keyPair.getPrivate();
        //获取公钥
        RSAPublicKey publicKey = (RSAPublicKey) keyPair.getPublic();
        Map<String, Object> map = new HashMap<String, Object>();
        map.put(PRIVATEKEY, privateKey);
        map.put(PUBLICKEY, publicKey);
        return map;
    }
 
    /**
     * 取得公钥
     *
     * @param map
     * @return byte[]
     */
    public static byte[] getPublicKey(Map<String, Object> map) {
        PublicKey publicKey = (PublicKey) map.get(PUBLICKEY);
        return publicKey.getEncoded();
    }
 
    /**
     * 取得私钥
     *
     * @param map
     * @return byte[]
     */
    public static byte[] getPrivateKey(Map<String, Object> map) {
        PrivateKey privateKey = (PrivateKey) map.get(PRIVATEKEY);
        return privateKey.getEncoded();
    }
 
    /**
     * 私钥加密
     *
     * @param source 数据
     * @param key    私钥
     * @return 签名
     * @throws Exception
     */
    public static String sign(String source, byte[] key) throws Exception {
        byte[] data = source.getBytes("utf-8");
 
        // 取得私钥
        PKCS8EncodedKeySpec pkcs8EncodedKeySpec = new PKCS8EncodedKeySpec(key);
        KeyFactory keyFactory = KeyFactory.getInstance(KEY_ALGORITHM);
 
        // 生成私钥
        PrivateKey privateKey = keyFactory.generatePrivate(pkcs8EncodedKeySpec);
 
        //新增： 实例化 签名对象
        Signature signature = Signature.getInstance(SIGNATRUE_ALGORITHM);
        //初始化 私钥
        signature.initSign(privateKey);
        //更新签名
        signature.update(data);
        byte[] enSign = signature.sign();
 
        return Base64.encodeBase64String(enSign);
    }
 
    /**
     * 校验
     *
     * @param source  源数据
     * @param key     公钥
     * @param signStr 已签名的数据
     * @return true or false
     * @throws Exception
     */
    public static boolean verify(String source, byte[] key, String signStr) throws Exception {
        // 还原即将 解密的 数据源
        byte[] data = source.getBytes("utf-8");
        // 还原已签名数据
        byte[] signData = Base64.decodeBase64(signStr);
 
        // 取得公钥
        X509EncodedKeySpec x509EncodedKeySpec = new X509EncodedKeySpec(key);
        KeyFactory keyFactory = KeyFactory.getInstance(KEY_ALGORITHM);
        // 生成公钥
        PublicKey publicKey = keyFactory.generatePublic(x509EncodedKeySpec);
 
        //新增： 实例化 签名对象
        Signature signature = Signature.getInstance(SIGNATRUE_ALGORITHM);
        //初始化 校验公钥
        signature.initVerify(publicKey);
        //更新签名
        signature.update(data);
        //验证
        return signature.verify(signData);
    }
 
    public static void main(String[] args) throws Exception {
        Map<String, Object> keyMap = initKey();
        byte[] privateKey = getPrivateKey(keyMap);
        byte[] publicKey = getPublicKey(keyMap);
        System.out.println("获取的私钥:" + Base64.encodeBase64String(privateKey));
        System.out.println("获取的公钥:" + Base64.encodeBase64String(publicKey));
 
        String source = "";
        //需要签名文件的内容
        String fileName = "D:\\code\\aaa.txt";
        try (BufferedReader br = new BufferedReader(new FileReader(fileName))) {
            String line;
            while ((line = br.readLine()) != null) {
                System.out.println("文件内容是: " + line);
                source = line;
            }
        }
        System.out.println("需要签名的文件内容是: " + source);
        String sign = sign(source, privateKey);
        System.out.println("签名后：" + sign);
        boolean flat = verify(source, publicKey, sign);
        System.out.println("校验结果:" + flat);
    }
}
 
