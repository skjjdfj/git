# 赏金黑客-wp-简单-tryhackme

## 部署机器。

>答案：无需回答
## 查找机器上开放的端口
``````
tarting Nmap 7.94SVN ( https://nmap.org ) at 2024-03-09 18:18 CST
Nmap scan report for 10.10.0.146
Host is up (0.24s latency).
Not shown: 967 filtered tcp ports (no-response), 30 closed tcp ports (reset)
PORT   STATE SERVICE VERSION
21/tcp open  ftp     vsftpd 3.0.3
| ftp-anon: Anonymous FTP login allowed (FTP code 230)
|_Can't get directory listing: TIMEOUT
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
|      At session startup, client count was 1
|      vsFTPd 3.0.3 - secure, fast, stable
|_End of status
22/tcp open  ssh     OpenSSH 7.2p2 Ubuntu 4ubuntu2.8 (Ubuntu Linux; protocol 2.0)
| ssh-hostkey: 
|   2048 dc:f8:df:a7:a6:00:6d:18:b0:70:2b:a5:aa:a6:14:3e (RSA)
|   256 ec:c0:f2:d9:1e:6f:48:7d:38:9a:e3:bb:08:c4:0c:c9 (ECDSA)
|_  256 a4:1a:15:a5:d4:b1:cf:8f:16:50:3a:7d:d0:d8:13:c2 (ED25519)
80/tcp open  http    Apache httpd 2.4.18 ((Ubuntu))
|_http-server-header: Apache/2.4.18 (Ubuntu)
``````
>答案：无需回答
## 任务清单是谁写的？ 
匿名登入ftp,可以下载两个文件
locks.txt(记住这个文件，一会要考) task.txt




>答案：lin
## 您可以使用找到的文本文件暴力破解什么服务？
locks.txt在这儿是密码字典，用户名字典自己做一个，刚才的剧情出现那么多人  
破解的是ssh服务，因为ftp破解不了


>答案：ssh
## 用户密码是什么？ 





>答案：
## 用户.txt



>答案：
## 根目录.txt
>答案：