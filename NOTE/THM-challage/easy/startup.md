# startup

nmap快速扫描：
```
PORT   STATE SERVICE
21/tcp open  ftp
22/tcp open  ssh
80/tcp open  http
```

nmap版本扫描：
```
PORT   STATE SERVICE VERSION
21/tcp open  ftp     vsftpd 3.0.3
| ftp-anon: Anonymous FTP login allowed (FTP code 230)
| drwxrwxrwx    2 65534    65534        4096 Nov 12  2020 ftp [NSE: writeable]
| -rw-r--r--    1 0        0          251631 Nov 12  2020 important.jpg
|_-rw-r--r--    1 0        0             208 Nov 12  2020 notice.txt
22/tcp open  ssh     OpenSSH 7.2p2 Ubuntu 4ubuntu2.10 (Ubuntu Linux; protocol 2.0)
| ssh-hostkey: 
|   2048 b9:a6:0b:84:1d:22:01:a4:01:30:48:43:61:2b:ab:94 (RSA)
|   256 ec:13:25:8c:18:20:36:e6:ce:91:0e:16:26:eb:a2:be (ECDSA)
|_  256 a2:ff:2a:72:81:aa:a2:9f:55:a4:dc:92:23:e6:b4:3f (ED25519)
80/tcp open  http    Apache httpd 2.4.18 ((Ubuntu))
|_http-server-header: Apache/2.4.18 (Ubuntu)
|_http-title: Maintenance
```


看到有80端口，可以进入目标靶机的网站，可以尝试gobuster进行目录爆破:
```
/files
```
进入后发现两个文件和一个文件夹，文件和目录和后面的ftp是一样的。

看到有21端口ftp，尝试使用anonymous登录，进入后发现一个图片和一个txt文件：
```
Whoever is leaving these damn Among Us memes in this share, it IS NOT FUNNY. People downloading documents from our website will think we are a joke! Now I dont know who it is, but Maya is looking pretty sus.
无论谁把这些该死的我们中间的模因留在这个分享中，这并不好笑。从我们网站下载文档的人会认为我们是个笑话！现在我不知道是谁，但玛雅看起来很可疑。
```

好了，重点来了，这个网站目录和ftp目录相同就说明了一个问题，可以通过ftp上传webshell文件到网站上的，等于一个文件上传，这些都是参考wp的，之后就可以通过激活webshell来进入目标内部，还没完，进到系统里，一般情况下，www-date的账户因为没有什么权限，要依赖提权(很难)或是找到数据库拿到用户的凭证来ssh，这个靶机开了ssh，几乎必然要拿到user的凭证。但是，这个凭证并不在数据库里，而在/incidents文件夹下的一个数据包里，要用wireshark分析的那种！！

用户名：```lennie```
密码：```c4ntg3t3n0ughsp1c3```
登录：
```
ssh lennie@10.10.63.172
```

### 辣汤秘方是什么
答案：love

### user.txt
答案：THM{03ce3d619b80ccbfb3b7fc81e46c0e79}

### root.txt
答案：THM{f963aaa6a430f210222158ae15c3d76d}

未完待续...