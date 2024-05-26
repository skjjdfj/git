# start point wp

## 

##


## 第二层-Oopsie

nmap扫描：
``````
快速扫描：
22/tcp open  ssh
80/tcp open  http

版本扫描：
22/tcp open  ssh     OpenSSH 7.6p1 Ubuntu 4ubuntu0.3 (Ubuntu Linux; protocol 2.0)
| ssh-hostkey: 
|   2048 61e43fd41ee2b2f10d3ced36283667c7 (RSA)
|   256 241da417d4e32a9c905c30588f60778d (ECDSA)
|_  256 78030eb4a1afe5c2f98d29053e29c9f2 (ED25519)
80/tcp open  http    Apache httpd 2.4.29 ((Ubuntu))
|_http-title: Welcome
|_http-server-header: Apache/2.4.29 (Ubuntu)
Service Info: OS: Linux; CPE: cpe:/o:linux:linux_kernel

漏洞扫描：
PORT   STATE SERVICE
22/tcp open  ssh
80/tcp open  http
| http-internal-ip-disclosure: 
|_  Internal IP Leaked: 127.0.1.1
|_http-vuln-cve2017-1001000: ERROR: Script execution failed (use -d to debug)
|_http-csrf: Couldn't find any CSRF vulnerabilities.
|_http-dombased-xss: Couldn't find any DOM based XSS.
|_http-stored-xss: Couldn't find any stored XSS vulnerabilities.

``````

gobuster扫描：
```
/images               (Status: 301) [Size: 313] [--> http://10.129.48.18/images/]
/themes               (Status: 301) [Size: 313] [--> http://10.129.48.18/themes/]
/uploads              (Status: 301) [Size: 314] [--> http://10.129.48.18/uploads/]
/css                  (Status: 301) [Size: 310] [--> http://10.129.48.18/css/]
/js                   (Status: 301) [Size: 309] [--> http://10.129.48.18/js/]
/fonts                (Status: 301) [Size: 312] [--> http://10.129.48.18/fonts/]

```

### 使用什么样的工具可以拦截网络流量？
```
答案:proxy
```

### 返回登录页面的 Web 服务器上目录的路径是什么？
```
答案：/cdn-cgi/login
```

### 在Firefox中可以修改哪些内容来访问上传页面？
```
答案：cookie
```

### 管理员用户的访问ID是什么？

