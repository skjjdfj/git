# Git Happens

nmap快速扫描：
```
PORT   STATE SERVICE
80/tcp open  http
```

nmap版本扫描:
```
PORT   STATE SERVICE VERSION
80/tcp open  http    nginx 1.14.0 (Ubuntu)
|_http-title: Super Awesome Site!
| http-git: 
|   10.10.53.27:80/.git/
|     Git repository found!
|_    Repository description: Unnamed repository; edit this file 'description' to name the...
|_http-server-header: nginx/1.14.0 (Ubuntu)
```
找到了/.git存储库，里面有很多文件，要慢慢看



### 查找超级密码