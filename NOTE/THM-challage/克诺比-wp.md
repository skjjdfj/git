# 克诺比-tryhackme-wp

## 部署易受攻击的机器

**用nmap扫描机器，有多少个端口开放？**  
``````
sudo nmap -Pn -A IP
PORT     STATE SERVICE     VERSION
21/tcp   open  ftp         ProFTPD 1.3.5
22/tcp   open  ssh         OpenSSH 7.2p2 Ubuntu 4ubuntu2.7 (Ubuntu Linux; protocol 2.0)
| ssh-hostkey: 
|   2048 b3:ad:83:41:49:e9:5d:16:8d:3b:0f:05:7b:e2:c0:ae (RSA)
|   256 f8:27:7d:64:29:97:e6:f8:65:54:65:22:f7:c8:1d:8a (ECDSA)
|_  256 5a:06:ed:eb:b6:56:7e:4c:01:dd:ea:bc:ba:fa:33:79 (EdDSA)
80/tcp   open  http        Apache httpd 2.4.18 ((Ubuntu))
| http-robots.txt: 1 disallowed entry 
|_/admin.html
|_http-server-header: Apache/2.4.18 (Ubuntu)
|_http-title: Site doesn't have a title (text/html).
111/tcp  open  rpcbind     2-4 (RPC #100000)
| rpcinfo: 
|   program version   port/proto  service
|   100000  2,3,4        111/tcp  rpcbind
|   100000  2,3,4        111/udp  rpcbind
|   100003  2,3,4       2049/tcp  nfs
|   100003  2,3,4       2049/udp  nfs
|   100005  1,2,3      37845/tcp  mountd
|   100005  1,2,3      48857/udp  mountd
|   100021  1,3,4      35691/tcp  nlockmgr
|   100021  1,3,4      46064/udp  nlockmgr
|   100227  2,3         2049/tcp  nfs_acl
|_  100227  2,3         2049/udp  nfs_acl
139/tcp  open  netbios-ssn Samba smbd 3.X - 4.X (workgroup: WORKGROUP)
445/tcp  open  netbios-ssn Samba smbd 4.3.11-Ubuntu (workgroup: WORKGROUP)
2049/tcp open  nfs_acl     2-3 (RPC #100227)
``````
答案：7

## 枚举 Samba 共享

**使用上面的nmap命令，找到了多少个共享？**  
``````
nmap -p 445 --script=smb-enum-shares.nse,smb-enum-users.nse IP
PORT    STATE SERVICE
445/tcp open  microsoft-ds
MAC Address: 02:C9:2B:CB:7E:79 (Unknown)

Host script results:
| smb-enum-shares: 
|   account_used: guest
|   \\10.10.147.101\IPC$: 
|     Type: STYPE_IPC_HIDDEN
|     Comment: IPC Service (kenobi server (Samba, Ubuntu))
|     Users: 2
|     Max Users: <unlimited>
|     Path: C:\tmp
|     Anonymous access: READ/WRITE
|     Current user access: READ/WRITE
|   \\10.10.147.101\anonymous: 
|     Type: STYPE_DISKTREE
|     Comment: 
|     Users: 0
|     Max Users: <unlimited>
|     Path: C:\home\kenobi\share
|     Anonymous access: READ/WRITE
|     Current user access: READ/WRITE
|   \\10.10.147.101\print$: 
|     Type: STYPE_DISKTREE
|     Comment: Printer Drivers
|     Users: 0
|     Max Users: <unlimited>
|     Path: C:\var\lib\samba\printers
|     Anonymous access: <none>
|_    Current user access: <none>
``````
答案：3
**连接后，列出共享上的文件。你能看到什么文件？**  
大多数 Linux 发行版上都已经安装了 smbclient。让我们检查其中一支股票。  
smbclient //IP/anonymous  

答案：log.txt
**FTP 在什么端口上运行？**  



**我们能看到什么坐骑？**  

## 使用 ProFtpd 获得初始访问权限

**版本是什么？**  

**ProFTPd 运行有多少个漏洞？**  

**Kenobi 的用户标志 (/home/kenobi/user.txt) 是什么？**  

## 通过路径变量操作进行权限提升

**什么文件看起来特别不寻常？**  

**运行二进制文件，出现多少个选项？**  

**什么是根标志（/root/root.txt）？**  
要进到/tmp文件夹里面操作

