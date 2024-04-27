# 初级CTF-wp-tryhackme-挑战-简单

## 1000 端口下有多少服务正在运行？
nmap -Pn -p1-1000 IP
``````
PORT   STATE SERVICE
21/tcp open  ftp
80/tcp open  http
``````
答案：2

## 较高端口上正在运行什么？

只有加上-sV(版本探测)才能扫到端口2222为ssh
sudo nmap -Pn -sV -sC IP
答案：ssh

## 您针对应用程序使用的CVE是什么？



## 应用程序容易遭受哪种类型的漏洞？


SQL注入漏洞也叫sqli
答案：sqli
## 密码是什么？


## 您可以在哪里使用获得的详细信息登录？


## 用户标志是什么？


## 主目录中是否还有其他用户？它叫什么名字？


## 您可以利用什么来生成特权 shell？


## 根标志是什么？

