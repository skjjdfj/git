# nmap笔记-初级渗透测试仪

## nmap实时主机发现

ARP扫描<br>
sudo nmap -PR -sn MACHINE_IP/24<br>
ICMP 回波扫描<br>
sudo nmap -PE -sn MACHINE_IP/24<br>
ICMP 时间戳扫描<br>
sudo nmap -PP -sn MACHINE_IP/24<br>
ICMP 地址掩码扫描<br>
sudo nmap -PM -sn MACHINE_IP/24<br>
TCP SYN Ping 扫描<br>
sudo nmap -PS22,80,443 -sn MACHINE_IP/30<br>
TCP ACK Ping 扫描<br>
sudo nmap -PA22,80,443 -sn MACHINE_IP/30<br>
UDP Ping 扫描<br>
sudo nmap -PU53,161,162 -sn MACHINE_IP/30<br>
-sn如果您只对主机发现感兴趣而无需端口扫描，请记住添加。<br>
省略 -sn将使Nmap默认对活动主机进行端口扫描。<br>

-n	没有DNS查找<br>
-R	所有主机的反向DNS查找<br>
-sn	仅主机发现<br>
使用的特定的DNS服务器:--dns-server DNS_SERVER<br>

## nmap基本端口扫描

TCP连接扫描<br>
nmap -sT MACHINE_IP<br>
TCP SYN 扫描<br>
sudo nmap -sS MACHINE_IP<br>
UDP扫描<br>
sudo nmap -sU MACHINE_IP<br>

这些扫描类型应该可以帮助您开始发现目标主机上正在运行的TCP和 UDP 服务。

选项|	目的
|-|-|
-p-	   |     所有端口  
-p1-1023	|扫描端口1至1023  
-F	    |    100 个最常用端口  
-r	     |   按连续顺序扫描端口  
-T<0-5>	  |  -T0最慢，T5最快  
--max-rate 50|	    速率 <= 50 数据包/秒  
--min-rate 15	|    速率 >= 15 数据包/秒  
--min-parallelism 100|	至少 100 个并行探头

## nmap高级端口扫描

端口扫描类型|	命令示例  
|-|-|
TCP 空扫描	    |sudo nmap -sN MACHINE_IP  
TCP FIN 扫描	|sudo nmap -sF MACHINE_IP  
TCP 圣诞扫描	|sudo nmap -sX MACHINE_IP  
TCP 迈蒙扫描	|sudo nmap -sM MACHINE_IP  
TCP ACK 扫描|   sudo nmap -sW MACHINE_IP  
自定义 TCP 扫描|	sudo nmap --scanflags URGACKPSHRSTSYNFIN MACHINE_IP  
欺骗源IP	|    sudo nmap -S SPOOFED_IP MACHINE_IP  
欺骗的MAC地址|	--spoof-mac SPOOFED_MAC  
诱饵扫描	|    nmap -D DECOY_IP,ME MACHINE_IP  
空闲（僵尸）扫描|	sudo nmap -sI ZOMBIE_IP MACHINE_IP  
将IP数据分片成8个字节|	-f  
将IP数据分片成16字节|	-ff  

选项|	目的
|-|-|  
--source-port PORT_NUM|指定源端口号  
--data-length NUM   |附加随机数据以达到给定长度  

这些扫描类型依赖于以意想不到的方式设置 TCP 标志来提示端口进行  回复。Null、FIN 和 Xmas 扫描会引发来自关闭端口的响应，而 Maimon、ACK 和 Window 扫描会引发来自开放和关闭端口的响应。

选项|	目的  
|-|-|
--reason	|解释 Nmap 如何得出结论  
-v	        |冗长的  
-vv	        |非常详细  
-d	       | 调试  
-dd	        |更多调试细节  

## nmap后端口扫描

选项|意义 
|-|-|
-sV	            |    确定开放端口上的服务/版本信息  
-sV --version-light	|版本探测强度2 
-sV --version-all	|版本探测强度9
-O	                |检测操作系统  
--traceroute	    |路由追踪  
--script=SCRIPTS	|要运行的Nmap脚本  
-sC或者--script=default	|运行默认脚本  
-A	                |相当于-sV -O -sC --traceroute  
-oN	                |以正常格式保存输出  
-oG	                |以 grepable 格式保存输出  
-oX	                |以XML格式保存输出
-oA	                |以普通、XML和 Grepable 格式保存输出

脚本位置：/usr/share/nmap/scripts  
脚本类别|	描述
|-|-|
auth	|认证相关脚本
broadcast|	通过发送广播消息发现主机
brute	|对登录执行暴力密码审核
default	|默认脚本，同-sC
discovery|	检索可访问的信息，例如数据库表和DNS名称
dos	|检测易受拒绝服务 ( DoS )攻击的服务器
exploit|	尝试利用各种易受攻击的服务
external|	使用第三方服务进行检查，例如 Geoplugin 和 Virustotal
fuzzer	|发起模糊攻击
intrusive	|暴力攻击和利用等侵入性脚本
malware	|扫描后门
safe	|不会使目标崩溃的安全脚本
version	|检索服务版本
vuln	|检查漏洞或利用易受攻击的服务

## 我找到的使用方法
sudo nmap -Pn -sV -sC IP  
-sC是默认脚本扫描，找到了端口为2222的ssh,此前的扫描认为2222端口不是ssh  

给的信息非常详实，好用  
nmap -A IP

通过XML输出，我们可以轻松创建易于阅读的HTML报告，即使对于非技术人员也是如此。这在以后的文档中非常有用，因为它以详细而清晰的方式呈现了我们的结果。 要将存储的结果从XML格式转换为HTML，我们可以使用工具 .xsltproc
``````
DarkGoblin@htb[/htb]$ xsltproc target.xml -o target.html
``````

