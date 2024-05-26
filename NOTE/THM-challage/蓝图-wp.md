# 蓝图

nmap扫描:
``````
sudo nmap -Pn -p- --min-rate 10000 -sV 10.10.32.191
Starting Nmap 7.93 ( https://nmap.org ) at 2024-05-17 13:39 CST
Warning: 10.10.32.191 giving up on port because retransmission cap hit (10).
Nmap scan report for 10.10.32.191
Host is up (0.41s latency).
Not shown: 48622 closed tcp ports (reset), 16900 filtered tcp ports (no-response)
PORT      STATE SERVICE      VERSION
80/tcp    open  http         Microsoft HTTPAPI httpd 2.0 (SSDP/UPnP)
135/tcp   open  msrpc        Microsoft Windows RPC
139/tcp   open  netbios-ssn  Microsoft Windows netbios-ssn
443/tcp   open  ssl/http     Apache httpd 2.4.23 (OpenSSL/1.0.2h PHP/5.6.28)
445/tcp   open  microsoft-ds Microsoft Windows 7 - 10 microsoft-ds (workgroup: WORKGROUP)
3306/tcp  open  mysql        MariaDB (unauthorized)
8080/tcp  open  http         Apache httpd 2.4.23 (OpenSSL/1.0.2h PHP/5.6.28)
49152/tcp open  msrpc        Microsoft Windows RPC
49153/tcp open  msrpc        Microsoft Windows RPC
49154/tcp open  msrpc        Microsoft Windows RPC
49158/tcp open  unknown
49159/tcp open  msrpc        Microsoft Windows RPC
49160/tcp open  msrpc        Microsoft Windows RPC
``````

``````
sudo nmap -Pn -p80,135,139,443,445,3306,8080,49152,49153,49154,49158,49159,49160 -sC -sV -O 10.10.32.191
PORT      STATE SERVICE      VERSION
80/tcp    open  http         Microsoft IIS httpd 7.5
|_http-server-header: Microsoft-IIS/7.5
|_http-title: 404 - File or directory not found.
| http-methods: 
|_  Potentially risky methods: TRACE
135/tcp   open  msrpc        Microsoft Windows RPC
139/tcp   open  netbios-ssn  Microsoft Windows netbios-ssn                                                                                                                                                    
443/tcp   open  ssl/http     Apache httpd 2.4.23 (OpenSSL/1.0.2h PHP/5.6.28)                                                                                                                                  
|_http-title: Bad request!                                                                                                                                                                                    
|_ssl-date: TLS randomness does not represent time                                                                                                                                                            
| ssl-cert: Subject: commonName=localhost                                                                                                                                                                     
| Not valid before: 2009-11-10T23:48:47                                                                                                                                                                       
|_Not valid after:  2019-11-08T23:48:47                                                                                                                                                                       
| tls-alpn: 
|_  http/1.1
|_http-server-header: Apache/2.4.23 (Win32) OpenSSL/1.0.2h PHP/5.6.28
445/tcp   open  microsoft-ds Windows 7 Home Basic 7601 Service Pack 1 microsoft-ds (workgroup: WORKGROUP)
3306/tcp  open  mysql        MariaDB (unauthorized)
8080/tcp  open  http         Apache httpd 2.4.23 (OpenSSL/1.0.2h PHP/5.6.28)
| http-methods: 
|_  Potentially risky methods: TRACE
| http-ls: Volume /
| SIZE  TIME              FILENAME
| -     2019-04-11 22:52  oscommerce-2.3.4/
| -     2019-04-11 22:52  oscommerce-2.3.4/catalog/
| -     2019-04-11 22:52  oscommerce-2.3.4/docs/
|_
|_http-server-header: Apache/2.4.23 (Win32) OpenSSL/1.0.2h PHP/5.6.28
|_http-title: Index of /
49152/tcp open  msrpc        Microsoft Windows RPC
49153/tcp open  msrpc        Microsoft Windows RPC
49154/tcp open  msrpc        Microsoft Windows RPC
49158/tcp open  msrpc        Microsoft Windows RPC
49159/tcp open  msrpc        Microsoft Windows RPC
49160/tcp open  msrpc        Microsoft Windows RPC
Warning: OSScan results may be unreliable because we could not find at least 1 open and 1 closed port
Device type: general purpose
Running (JUST GUESSING): Microsoft Windows 2008|10|Vista|7|8.1|2016|Longhorn (96%)
OS CPE: cpe:/o:microsoft:windows_server_2008:r2:sp1 cpe:/o:microsoft:windows_10 cpe:/o:microsoft:windows_vista::sp1 cpe:/o:microsoft:windows_vista::sp2 cpe:/o:microsoft:windows_7 cpe:/o:microsoft:windows_8.1:r1 cpe:/o:microsoft:windows_server_2016 cpe:/o:microsoft:windows
Aggressive OS guesses: Microsoft Server 2008 R2 SP1 (96%), Microsoft Windows 10 (91%), Microsoft Windows 10 10586 - 14393 (91%), Microsoft Windows 10 1511 (91%), Microsoft Windows 10 1607 (91%), Microsoft Windows Vista SP1 - SP2, Windows Server 2008 SP2, or Windows 7 (91%), Microsoft Windows 10 1507 (88%), Microsoft Windows 10 1507 - 1607 (88%), Microsoft Windows 7 or 8.1 R1 (88%), Microsoft Windows 7 SP1 (88%)
No exact OS matches for host (test conditions non-ideal).
Network Distance: 5 hops
Service Info: Hosts: www.example.com, BLUEPRINT, localhost; OS: Windows; CPE: cpe:/o:microsoft:windows

Host script results:
| smb2-time: 
|   date: 2024-05-17T05:45:38
|_  start_date: 2024-05-17T05:39:03
| smb-security-mode: 
|   account_used: guest
|   authentication_level: user
|   challenge_response: supported
|_  message_signing: disabled (dangerous, but default)
| smb-os-discovery: 
|   OS: Windows 7 Home Basic 7601 Service Pack 1 (Windows 7 Home Basic 6.1)
|   OS CPE: cpe:/o:microsoft:windows_7::sp1
|   Computer name: BLUEPRINT
|   NetBIOS computer name: BLUEPRINT\x00
|   Workgroup: WORKGROUP\x00
|_  System time: 2024-05-17T06:45:40+01:00
| smb2-security-mode: 
|   210: 
|_    Message signing enabled but not required
|_nbstat: NetBIOS name: BLUEPRINT, NetBIOS user: <unknown>, NetBIOS MAC: 02b594a69fff (unknown)
|_clock-skew: mean: -20m01s, deviation: 34m36s, median: -3s

OS and Service detection performed. Please report any incorrect results at https://nmap.org/submit/ .
Nmap done: 1 IP address (1 host up) scanned in 117.97 seconds

``````

gobuster扫描：
``````

``````

postmaster@localhost

8080端口有东西



## “实验室”用户 NTLM 哈希解密


## root.txt