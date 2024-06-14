# Creative



>nmap扫描

``````
PORT   STATE SERVICE VERSION
22/tcp open  ssh     OpenSSH 8.2p1 Ubuntu 4ubuntu0.5 (Ubuntu Linux; protocol 2.0)
| ssh-hostkey: 
|   3072 a05c1c4eb486cf589f22f97c543d7e7b (RSA)
|   256 47d5bb58b6c5cce36c0b00bd95d2a0fb (ECDSA)
|_  256 cb7cad3141bb98afcfebe4887f125e89 (ED25519)
80/tcp open  http    nginx 1.18.0 (Ubuntu)
|_http-server-header: nginx/1.18.0 (Ubuntu)
|_http-title: Did not follow redirect to http://creative.thm
Service Info: OS: Linux; CPE: cpe:/o:linux:linux_kernel

Service detection performed. Please report any incorrect results at https://nmap.org/submit/ .
Nmap done: 1 IP address (1 host up) scanned in 24.70 seconds
``````
这个room需要把"靶机IP creative.thm"加到/etc/hosts这个文件里  
``````
echo "IP creative.thm" | sudo tee -a /etc/hosts
``````

>gobuster扫描

vocal，一看wp，跟tm子域有关，人都傻了  
用参数vhosts枚举子域名：  
``````
Found: http://enquetes Status: 400 [Size: 166]
Found: http://mobility Status: 400 [Size: 166]
Found: http://partner Status: 400 [Size: 166]
Found: https://assurance Status: 400 [Size: 166]
Found: https://collaboratif Status: 400 [Size: 166]
Found: https://archives Status: 400 [Size: 166]
Found: https://conseil Status: 400 [Size: 166]
Found: https://ee Status: 400 [Size: 166]
Found: https://escale Status: 400 [Size: 166]
Found: https://idees Status: 400 [Size: 166]
Found: https://igc Status: 400 [Size: 166]
Found: https://lvelizy Status: 400 [Size: 166]
Found: https://nomade Status: 400 [Size: 166]
Found: https://mobility Status: 400 [Size: 166]
Found: https://pam Status: 400 [Size: 166]
Found: https://scm Status: 400 [Size: 166]
Found: https://protocoltraining Status: 400 [Size: 166]
Found: https://sft Status: 400 [Size: 166]
Found: https://webpam Status: 400 [Size: 166]
Found: https://www Status: 400 [Size: 166]
Found: https://partner Status: 400 [Size: 166]
``````

## user.txt

## root.txt

