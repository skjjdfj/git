# cyborg-WP-TryHackMe

### 前三个问题一波解决
sudo nmap -Pn -A IP
``````
Host is up (0.27s latency).
Not shown: 998 closed tcp ports (reset)
PORT   STATE SERVICE VERSION
22/tcp open  ssh     OpenSSH 7.2p2 Ubuntu 4ubuntu2.10 (Ubuntu Linux; protocol 2.0)
| ssh-hostkey: 
|   2048 dbb270f307ac32003f81b8d03a89f365 (RSA)
|   256 68e6852f69655be7c6312c8e4167d7ba (ECDSA)
|_  256 562c7992ca23c3914935fadd697ccaab (ED25519)
80/tcp open  http    Apache httpd 2.4.18 ((Ubuntu))
|_http-server-header: Apache/2.4.18 (Ubuntu)
|_http-title: Apache2 Ubuntu Default Page: It works
No exact OS matches for host (If you know what OS is running on it, see https://nmap.org/submit/ ).
TCP/IP fingerprint:
OS:SCAN(V=7.93%E=4%D=2/4%OT=22%CT=1%CU=41824%PV=Y%DS=2%DC=T%G=Y%TM=65BF687F
OS:%P=x86_64-pc-linux-gnu)SEQ(SP=106%GCD=1%ISR=10B%TI=Z%CI=Z%II=I%TS=A)OPS(
OS:O1=M508ST11NW7%O2=M508ST11NW7%O3=M508NNT11NW7%O4=M508ST11NW7%O5=M508ST11
OS:NW7%O6=M508ST11)WIN(W1=F4B3%W2=F4B3%W3=F4B3%W4=F4B3%W5=F4B3%W6=F4B3)ECN(
OS:R=Y%DF=Y%T=40%W=F507%O=M508NNSNW7%CC=Y%Q=)T1(R=Y%DF=Y%T=40%S=O%A=S+%F=AS
OS:%RD=0%Q=)T2(R=N)T3(R=N)T4(R=Y%DF=Y%T=40%W=0%S=A%A=Z%F=R%O=%RD=0%Q=)T5(R=
OS:Y%DF=Y%T=40%W=0%S=Z%A=S+%F=AR%O=%RD=0%Q=)T6(R=Y%DF=Y%T=40%W=0%S=A%A=Z%F=
OS:R%O=%RD=0%Q=)T7(R=Y%DF=Y%T=40%W=0%S=Z%A=S+%F=AR%O=%RD=0%Q=)U1(R=Y%DF=N%T
OS:=40%IPL=164%UN=0%RIPL=G%RID=G%RIPCK=G%RUCK=G%RUD=G)IE(R=Y%DFI=N%T=40%CD=
OS:S)

Network Distance: 2 hops
Service Info: OS: Linux; CPE: cpe:/o:linux:linux_kernel

TRACEROUTE (using port 23/tcp)
HOP RTT       ADDRESS
1   273.97 ms 10.11.0.1 (10.11.0.1)
2   274.55 ms 10.10.177.155 (10.10.177.155)
``````

nmap版本扫描：
```
PORT   STATE SERVICE VERSION
22/tcp open  ssh     OpenSSH 7.2p2 Ubuntu 4ubuntu2.10 (Ubuntu Linux; protocol 2.0)
| ssh-hostkey: 
|   2048 db:b2:70:f3:07:ac:32:00:3f:81:b8:d0:3a:89:f3:65 (RSA)
|   256 68:e6:85:2f:69:65:5b:e7:c6:31:2c:8e:41:67:d7:ba (ECDSA)
|_  256 56:2c:79:92:ca:23:c3:91:49:35:fa:dd:69:7c:ca:ab (ED25519)
80/tcp open  http    Apache httpd 2.4.18 ((Ubuntu))
|_http-title: Apache2 Ubuntu Default Page: It works
|_http-server-header: Apache/2.4.18 (Ubuntu)
Service Info: OS: Linux; CPE: cpe:/o:linux:linux_kernel

```

nmap漏洞扫描：
```
PORT   STATE SERVICE
22/tcp open  ssh
80/tcp open  http
|_http-stored-xss: Couldn't find any stored XSS vulnerabilities.
|_http-csrf: Couldn't find any CSRF vulnerabilities.
|_http-dombased-xss: Couldn't find any DOM based XSS.
| http-enum: 
|   /admin/: Possible admin folder
|   /admin/index.html: Possible admin folder
|   /admin/admin.html: Possible admin folder
|_  /etc/: Potentially interesting directory w/ listing on 'apache/2.4.18 (ubuntu)'

```

gobuster扫描：
```
/admin                (Status: 301) [Size: 314] [--> http://10.10.140.112/admin/]
/etc                  (Status: 301) [Size: 312] [--> http://10.10.140.112/etc/]
```

/admin的源码里有一个叫archive.tar的压缩包  
/etc的文件夹有passwd和squid.conf两个文件  

对passwd处理：
``````
文件内容：
music_archive:$apr1$BpZ.Q.1m$F0qqPwHSOG50URuOVQTTn.
hashcat解密为：
hashcat -m 1600 -a 0 /usr/share/wordlists/rockyou.txt hash1.txt 
$apr1$BpZ.Q.1m$F0qqPwHSOG50URuOVQTTn.:squidward
``````

``````
aquid.conf文件内容：
auth_param basic program /usr/lib64/squid/basic_ncsa_auth /etc/squid/passwd
auth_param basic children 5
auth_param basic realm Squid Basic Authentication
auth_param basic credentialsttl 2 hours
acl auth_users proxy_auth REQUIRED
http_access allow auth_users
``````

borg：
```
borg extract YOURPATH/final_archive::music_archive
```
分离出文件夹alex，里面的Document文件夹有名为notes.txt的文件，里面有凭据。
```
alex:S3cretP@s3
```  
可以用来登录ssh，进去后拿到user.txt

sudo -l发现有backup.sh的权限，在backup.sh里添加一个反shell后，监听端口(可以用chmod u+w backup.sh给自己写的权限)
在crontab里面有这个文件的任务，等一会儿自己会执行，然后拿到root

### 扫描机器，有多少端口开放？
答案：2
### 端口 22 上正在运行什么服务？
答案：ssh
### 80 端口上正在运行什么服务？
答案：http


### user.txt 标志是什么？
答案：flag{1_hop3_y0u_ke3p_th3_arch1v3s_saf3}


### root.txt 标志是什么？
答案：flag{Than5s_f0r_play1ng_H0p£_y0u_enJ053d}


