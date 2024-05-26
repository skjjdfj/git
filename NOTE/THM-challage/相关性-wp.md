# 相关性-tryhackme-medium

nmap大致扫描
``````
sudo nmap -Pn --min-rate 10000 -p- -sV 10.10.195.124
PORT      STATE SERVICE       VERSION
80/tcp    open  http          Microsoft IIS httpd 10.0
135/tcp   open  msrpc         Microsoft Windows RPC
139/tcp   open  netbios-ssn   Microsoft Windows netbios-ssn
445/tcp   open  microsoft-ds  Microsoft Windows Server 2008 R2 - 2012 microsoft-ds
3389/tcp  open  ms-wbt-server Microsoft Terminal Services
49663/tcp open  http          Microsoft IIS httpd 10.0
49667/tcp open  msrpc         Microsoft Windows RPC
49668/tcp open  msrpc         Microsoft Windows RPC
``````

nmap版本扫描：
``````
sudo nmap -Pn -p80,135,139,445,3389,49663,49667,49668 -sV -sC -O 10.10.195.124
PORT      STATE SERVICE       VERSION
80/tcp    open  http          Microsoft IIS httpd 10.0
|_http-title: IIS Windows Server
|_http-server-header: Microsoft-IIS/10.0
135/tcp   open  msrpc         Microsoft Windows RPC
139/tcp   open  netbios-ssn   Microsoft Windows netbios-ssn
445/tcp   open  microsoft-ds  Windows Server 2016 Standard Evaluation 14393 microsoft-ds
3389/tcp  open  ms-wbt-server Microsoft Terminal Services
| ssl-cert: Subject: commonName=Relevant
| Not valid before: 2024-05-15T12:50:08
|_Not valid after:  2024-11-14T12:50:08
|_ssl-date: 2024-05-16T12:57:09+00:00; 0s from scanner time.
49663/tcp open  http          Microsoft IIS httpd 10.0
|_http-server-header: Microsoft-IIS/10.0
|_http-title: IIS Windows Server
| http-methods: 
|_  Potentially risky methods: TRACE
49667/tcp open  msrpc         Microsoft Windows RPC
49668/tcp open  msrpc         Microsoft Windows RPC
Warning: OSScan results may be unreliable because we could not find at least 1 open and 1 closed port
OS fingerprint not ideal because: Missing a closed TCP port so results incomplete
No OS matches for host
Service Info: OSs: Windows, Windows Server 2008 R2 - 2012; CPE: cpe:/o:microsoft:windows

Host script results:
| smb2-time: 
|   date: 2024-05-16T12:56:31
|_  start_date: 2024-05-16T12:50:09
|_clock-skew: mean: 1h45m01s, deviation: 3h30m02s, median: 0s
| smb-os-discovery: 
|   OS: Windows Server 2016 Standard Evaluation 14393 (Windows Server 2016 Standard Evaluation 6.3)
|   Computer name: Relevant
|   NetBIOS computer name: RELEVANT\x00
|   Workgroup: WORKGROUP\x00
|_  System time: 2024-05-16T05:56:33-07:00
| smb2-security-mode: 
|   311: 
|_    Message signing enabled but not required
| smb-security-mode: 
|   account_used: guest
|   authentication_level: user
|   challenge_response: supported
|_  message_signing: disabled (dangerous, but default)

OS and Service detection performed. Please report any incorrect results at https://nmap.org/submit/ .
Nmap done: 1 IP address (1 host up) scanned in 118.75 seconds

``````


gobuster扫描
``````
/*checkout*           (Status: 400) [Size: 3420]
Progress: 8195 / 220561 (3.72%)[ERROR] Get "http://10.10.195.124/VMS": context deadline exceeded (Client.Timeout exceeded while awaiting headers)
/*docroot*            (Status: 400) [Size: 3420]
/*                    (Status: 400) [Size: 3420]
/http%3A%2F%2Fwww     (Status: 400) [Size: 3420]
/http%3A              (Status: 400) [Size: 3420]
/q%26a                (Status: 400) [Size: 3420]
/**http%3a            (Status: 400) [Size: 3420]
/*http%3A             (Status: 400) [Size: 3420]
/**http%3A            (Status: 400) [Size: 3420]
/http%3A%2F%2Fyoutube (Status: 400) [Size: 3420]
/http%3A%2F%2Fblogs   (Status: 400) [Size: 3420]
/http%3A%2F%2Fblog    (Status: 400) [Size: 3420]
/**http%3A%2F%2Fwww   (Status: 400) [Size: 3420]
/s%26p                (Status: 400) [Size: 3420]
/%3FRID%3D2671        (Status: 400) [Size: 3420]
/devinmoore*          (Status: 400) [Size: 3420]
/200109*              (Status: 400) [Size: 3420]
/*dc_                 (Status: 400) [Size: 3420]
/*sa_                 (Status: 400) [Size: 3420]

``````

说明：服务器上发生应用程序错误。出于安全原因，此应用程序的当前自定义错误设置可防止远程查看应用程序错误的详细信息。但是，在本地服务器计算机上运行的浏览器可以查看它。

详细信息：若要使此特定错误消息的详细信息能够在远程计算机上查看，请<customErrors>在当前 Web 应用程序根目录中的“web.config”配置文件中创建一个标记。然后，此<customErrors>标记应将其“mode”属性设置为“Off”

注意：通过修改应用程序配置标记的“defaultRedirect”属性<customErrors>以指向自定义错误页 URL，可以将您看到的当前错误页替换为自定义错误页。

139端口的smb有突破口

smbclient -N -L //10.10.195.124/
``````
        Sharename       Type      Comment
        ---------       ----      -------
        ADMIN$          Disk      Remote Admin
        C$              Disk      Default share
        IPC$            IPC       Remote IPC
        nt4wrksv        Disk      
Reconnecting with SMB1 for workgroup listing.
do_connect: Connection to 10.10.195.124 failed (Error NT_STATUS_RESOURCE_NAME_NOT_FOUND)
Unable to connect with SMB1 -- no workgroup available
``````

smbclient //10.10.195.124/nt4wrksv  
没有密码，而且里面有一个passwords.txt的文件，内容是；、
``````  
[User Passwords - Encoded]
Qm9iIC0gIVBAJCRXMHJEITEyMw==
QmlsbCAtIEp1dzRubmFNNG40MjA2OTY5NjkhJCQk
``````

Qm9iIC0gIVBAJCRXMHJEITEyMw== base64解码结果；  
Bob - !P@$$W0rD!123

QmlsbCAtIEp1dzRubmFNNG40MjA2OTY5NjkhJCQk base64解码结果；  
Bill - Juw4nnaM4n420696969!$$$


## user flag

## root flag

