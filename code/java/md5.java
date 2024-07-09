public static String md5Encode(String srcStr) throws IOException {
		MessageDigest md5 = null;
		try {
			md5 = MessageDigest.getInstance("MD5");
		} catch (NoSuchAlgorithmException e) {
			e.printStackTrace();
			return "";
		}
		byte[] bytyArray = srcStr.getBytes("UTF-8");
		byte[] md5byte = md5.digest(bytyArray);
		StringBuffer hexValue = new StringBuffer();
		for (int i = 0, length = md5byte.length; i < length; i++) {
			int val = ((int)md5byte[i]) & 0xff;
			if (val < 16) {
				hexValue.append("0");
			}
			hexValue.append(Integer.toHexString(val));
		}
		return hexValue.toString();
	}


public static void main(String[] args) throws IOException {
		String testText = "Hi,this is my bank account";
		System.out.println("加密前：" + testText);
		System.out.println("加密后：" + md5Encode(testText));
}

