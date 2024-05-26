# 超泰克

>基本过程：  

从找到/auth往后基本参照wp写:  
找到/js/api.js代码里的命令注入  
命令注入后找到数据库文件  
通过数据库文件找到两个用户名和密码（自己做的）  
ssh登录（自己做的）  
通过docker提权  

nmap扫描结果：  
ports:   
21  
22  
8081  
31331  

gobuster扫描结果：  
``````
对31331端口页面的扫描：
/images               (Status: 301) [Size: 322] [--> http://10.10.87.228:31331/images/]
/css                  (Status: 301) [Size: 319] [--> http://10.10.87.228:31331/css/]
/js                   (Status: 301) [Size: 318] [--> http://10.10.87.228:31331/js/]
/javascript           (Status: 301) [Size: 326] [--> http://10.10.87.228:31331/javascript/]

对8081端口的扫描：
/auth
/ping
UltraTech API v0.1.3
``````


## 


