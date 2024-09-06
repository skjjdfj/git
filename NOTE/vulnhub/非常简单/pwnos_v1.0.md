# pWnOs_v1.0
靶场：vulnhub
难度：简单


### nmap扫描

主机发现&端口扫描：
```
sudo nmap --min-rate 10000 IP

Host is up (0.0030s latency).
Not shown: 995 closed tcp ports (reset)
PORT      STATE SERVICE
22/tcp    open  ssh
80/tcp    open  http
139/tcp   open  netbios-ssn
445/tcp   open  microsoft-ds
10000/tcp open  snet-sensor-mgmt
MAC Address: 00:0C:29:5E:18:C9 (VMware)
```

版本扫描：  
```
sudo nmap -Pn -p22,80,139,445,10000 -sC -sV -O 192.168.162.137

PORT      STATE SERVICE     VERSION
22/tcp    open  ssh         OpenSSH 4.6p1 Debian 5build1 (protocol 2.0)
| ssh-hostkey: 
|   1024 e4:46:40:bf:e6:29:ac:c6:00:e2:b2:a3:e1:50:90:3c (DSA)
|_  2048 10:cc:35:45:8e:f2:7a:a1:cc:db:a0:e8:bf:c7:73:3d (RSA)
80/tcp    open  http        Apache httpd 2.2.4 ((Ubuntu) PHP/5.2.3-1ubuntu6)
|_http-server-header: Apache/2.2.4 (Ubuntu) PHP/5.2.3-1ubuntu6
|_http-title: Site doesn't have a title (text/html).
139/tcp   open  netbios-ssn Samba smbd 3.X - 4.X (workgroup: MSHOME)
445/tcp   open  netbios-ssn Samba smbd 3.0.26a (workgroup: MSHOME)
10000/tcp open  http        MiniServ 0.01 (Webmin httpd)
|_http-title: Site doesn't have a title (text/html; Charset=iso-8859-1).
MAC Address: 00:0C:29:5E:18:C9 (VMware)
Warning: OSScan results may be unreliable because we could not find at least 1 open and 1 closed port
Device type: general purpose
Running: Linux 2.6.X
OS CPE: cpe:/o:linux:linux_kernel:2.6.22
OS details: Linux 2.6.22 (embedded, ARM), Linux 2.6.22 - 2.6.23
Network Distance: 1 hop
Service Info: OS: Linux; CPE: cpe:/o:linux:linux_kernel

Host script results:
| smb-security-mode: 
|   account_used: guest
|   authentication_level: user
|   challenge_response: supported
|_  message_signing: disabled (dangerous, but default)
|_nbstat: NetBIOS name: UBUNTUVM, NetBIOS user: <unknown>, NetBIOS MAC: <unknown> (unknown)
|_smb2-time: Protocol negotiation failed (SMB2)
| smb-os-discovery: 
|   OS: Unix (Samba 3.0.26a)
|   Computer name: ubuntuvm
|   NetBIOS computer name: 
|   Domain name: nsdlab
|   FQDN: ubuntuvm.NSDLAB
|_  System time: 2024-07-26T05:55:57-05:00
|_clock-skew: mean: 2h29m59s, deviation: 3h32m09s, median: -1s

```

漏洞扫描：
```
sudo nmap -Pn -p22,80,139,445,10000 --script=vuln 192.168.162.137

PORT      STATE SERVICE
22/tcp    open  ssh
80/tcp    open  http
|_http-trace: TRACE is enabled
|_http-vuln-cve2017-1001000: ERROR: Script execution failed (use -d to debug)
|_http-csrf: Couldn't find any CSRF vulnerabilities.
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
|       http://ha.ckers.org/slowloris/
|_      https://cve.mitre.org/cgi-bin/cvename.cgi?name=CVE-2007-6750
|_http-stored-xss: Couldn't find any stored XSS vulnerabilities.
|_http-dombased-xss: Couldn't find any DOM based XSS.
| http-enum: 
|   /icons/: Potentially interesting directory w/ listing on 'apache/2.2.4 (ubuntu) php/5.2.3-1ubuntu6'
|   /index/: Potentially interesting folder
|_  /php/: Potentially interesting directory w/ listing on 'apache/2.2.4 (ubuntu) php/5.2.3-1ubuntu6'
139/tcp   open  netbios-ssn
445/tcp   open  microsoft-ds
10000/tcp open  snet-sensor-mgmt
| http-vuln-cve2006-3392: 
|   VULNERABLE:
|   Webmin File Disclosure
|     State: VULNERABLE (Exploitable)
|     IDs:  CVE:CVE-2006-3392
|       Webmin before 1.290 and Usermin before 1.220 calls the simplify_path function before decoding HTML.
|       This allows arbitrary files to be read, without requiring authentication, using "..%01" sequences
|       to bypass the removal of "../" directory traversal sequences.
|       
|     Disclosure date: 2006-06-29
|     References:
|       https://cve.mitre.org/cgi-bin/cvename.cgi?name=CVE-2006-3392
|       http://www.rapid7.com/db/modules/auxiliary/admin/webmin/file_disclosure
|_      http://www.exploit-db.com/exploits/1997/
MAC Address: 00:0C:29:5E:18:C9 (VMware)

Host script results:
|_smb-vuln-regsvc-dos: ERROR: Script execution failed (use -d to debug)
|_smb-vuln-ms10-061: false
|_smb-vuln-ms10-054: false
```

### gobuster扫描

```
gobuster dir -w /usr/share/wordlists/dirbuster/directory-list-2.3-medium.txt -u http://192.168.162.137/ -t 30

/index                (Status: 200) [Size: 295]
/index2               (Status: 200) [Size: 156]
/php                  (Status: 301) [Size: 334] [--> http://192.168.162.137/php/]
/index1               (Status: 200) [Size: 1104]
/server-status        (Status: 403) [Size: 314]
```



### smb共享

枚举出来的用户：
```
smbclient -N -L //192.168.12.137/

Anonymous login successful

	Sharename       Type      Comment
	---------       ----      -------
	home            Disk      Home Directory for vmware User
	print$          Disk      Printer Drivers
	IPC$            IPC       IPC Service (ubuntuvm)
Reconnecting with SMB1 for workgroup listing.
Anonymous login successful

	Server               Comment
	---------            -------

	Workgroup            Master
	---------            -------
	MSHOME               
```

好像只有IPC$可以登录，其他的会报错`tree connect failed: NT_STATUS_ACCESS_DENIED`，而且`IPC`的权限不完全，甚至不能使用ls

### 网站
现在来看看80和10000端口的网页
`http://192.168.162.137/index1.php?help=true&connect=true`
这个地方的connect参数有文件包含的漏洞：
![Alt text](<../picture/屏幕截图 2024-07-26 211927.png>)

10000端口有一个登陆页面:
![Alt text](<../picture/屏幕截图 2024-07-26 212301.png>)
应用程序是webmin，去找webmin的漏洞有什么。

可以使用任意文件读取的漏洞读取/etc/shadow(真TMNB)
![Alt text](<../picture/屏幕截图 2024-07-26 215151.png>)

然后把可以解开的哈希用john解一下：
![Alt text](<../picture/屏幕截图 2024-07-27 085006.png>)

nmap扫端口的时候看到22端口开了，直接登录一下。
但是直接使用ssh登录会报错
Unable to negotiate with 192.168.162.137 port 22: no matching host key type found. Their offer: ssh-rsa,ssh-dss

所以要这样登录：
```bash
ssh -oHostKeyAlgorithms=ssh-rsa,ssh-dss vmware@192.168.162.137
password:h4ckm3
```

### 提权

`sudo -l`不能使用
使用提权脚本LinEnum.sh，没有发现可以利用的地方，查看wp后发现新的提权方式，任意文件读取漏洞可以用来提权。

kali端：
![Alt text](<../picture/屏幕截图 2024-07-27 150215.png>)

反shell端：
![Alt text](<../picture/屏幕截图 2024-07-27 150456.png>)
提权成功。拿到root权限。

### 复盘

80端口的网页有文件包含漏洞，但是权限过低没有利用价值，10000端口的网页有wenmin的任意文件泄露漏洞，这个靶机通篇都在围绕这个漏洞进行的，低权限的vmware和高权限的root账户都是使用这个漏洞拿到账户控制权的。