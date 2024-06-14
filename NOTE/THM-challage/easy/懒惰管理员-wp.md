# 懒惰管理员-wp-简单-tryhackme

sudo nmap -Pn -A IP
``````
PORT   STATE SERVICE VERSION
22/tcp open  ssh     OpenSSH 7.2p2 Ubuntu 4ubuntu2.8 (Ubuntu Linux; protocol 2.0)
| ssh-hostkey: 
|   2048 49:7c:f7:41:10:43:73:da:2c:e6:38:95:86:f8:e0:f0 (RSA)
|   256 2f:d7:c4:4c:e8:1b:5a:90:44:df:c0:63:8c:72:ae:55 (ECDSA)
|_  256 61:84:62:27:c6:c3:29:17:dd:27:45:9e:29:cb:90:5e (ED25519)
80/tcp open  http    Apache httpd 2.4.18 ((Ubuntu))
|_http-server-header: Apache/2.4.18 (Ubuntu)
|_http-title: Apache2 Ubuntu Default Page: It works
No exact OS matches for host (If you know what OS is running on it, see https://nmap.org/submit/ ).
TCP/IP fingerprint:
OS:SCAN(V=7.94SVN%E=4%D=3/9%OT=22%CT=1%CU=40199%PV=Y%DS=2%DC=T%G=Y%TM=65EC4
OS:08B%P=x86_64-pc-linux-gnu)SEQ(SP=F5%GCD=1%ISR=110%TI=Z%CI=Z%TS=A)SEQ(SP=
OS:F6%GCD=1%ISR=110%TI=Z%CI=Z%II=I%TS=A)SEQ(SP=FA%GCD=1%ISR=110%TI=Z%CI=Z%T
OS:S=C)SEQ(SP=FA%GCD=1%ISR=110%TI=Z%CI=Z%II=I%TS=C)SEQ(SP=FB%GCD=1%ISR=110%
OS:TI=Z%CI=Z%II=I%TS=A)OPS(O1=M508ST11NW7%O2=M508ST11NW7%O3=M508NNT11NW7%O4
OS:=M508ST11NW7%O5=M508ST11NW7%O6=M508ST11)WIN(W1=68DF%W2=68DF%W3=68DF%W4=6
OS:8DF%W5=68DF%W6=68DF)ECN(R=Y%DF=Y%T=40%W=6903%O=M508NNSNW7%CC=Y%Q=)T1(R=Y
OS:%DF=Y%T=40%S=O%A=S+%F=AS%RD=0%Q=)T2(R=N)T3(R=N)T4(R=Y%DF=Y%T=40%W=0%S=A%
OS:A=Z%F=R%O=%RD=0%Q=)T5(R=Y%DF=Y%T=40%W=0%S=Z%A=S+%F=AR%O=%RD=0%Q=)T6(R=Y%
OS:DF=Y%T=40%W=0%S=A%A=Z%F=R%O=%RD=0%Q=)T7(R=Y%DF=Y%T=40%W=0%S=Z%A=S+%F=AR%
OS:O=%RD=0%Q=)U1(R=Y%DF=N%T=40%IPL=164%UN=0%RIPL=G%RID=G%RIPCK=G%RUCK=G%RUD
OS:=G)IE(R=Y%DFI=N%T=40%CD=S)
``````

gobuster dir -u http://10.10.126.250/ -w /usr/share/wordlists/dirbuster/directory-list-2.3-medium.txt

扫描出页面content

/content


## 什么是用户标志？



## 什么是根标志？



三次参考WP
第一次找到文件changelog.txt
第二次找到用户名manager（其实是密码Password123输成了password123导致登陆不进去）
第三次提权，但是已经有想法了，但没实践，更改copy.sh文件的内容，把IP改成攻击机的IP