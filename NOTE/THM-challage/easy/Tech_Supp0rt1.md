# Tech_Supp0rt: 1
平台:tryhackme
难度:easy
参考过wp


### Nmap
![Alt text](<../../../picture/THM/Tech_Supp0rt 1/Snipaste_2024-12-08_11-53-23.png>)
开启了smb,http,ssh的服务

### smb

![Alt text](<../../../picture/THM/Tech_Supp0rt 1/Snipaste_2024-12-08_12-28-04.png>)
smb中websvr可以匿名登陆，进去后有一个叫enter.txt的文件。
文件内容：
```
GOALS
=====
1)Make fake popup and host it online on Digital Ocean server
2)Fix subrion site, /subrion doesn't work, edit from panel
3)Edit wordpress website

IMP
===
Subrion creds
|->admin:7sKvntXdPEJaxazce9PXi24zaFrLiKWCk [cooked with magical formula]
Wordpress creds
|->
```
其中admin的密码可以在cyberchef中的magic解出(题中有提示):
![Alt text](<../../../picture/THM/Tech_Supp0rt 1/Snipaste_2024-12-08_12-31-32.png>)
```
admin:Scam2021
```
还暴露出/subrion/panel这个页面的存在(这个真没想到，拿到凭据死活找不到登陆的地方)

登陆进去后就要想办法拿到shell了，通过对subrion的搜索，最后确定了一个漏洞:`cve-2018-19422`，这是一个文件上传的漏洞，通过对POC的分析，这个漏洞是在/uploads页面上传文件的。
![Alt text](<../../../picture/THM/Tech_Supp0rt 1/Snipaste_2024-12-08_12-51-11.png>)
奶奶的，手动传不上去，只能用脚本跑了。
![Alt text](<../../../picture/THM/Tech_Supp0rt 1/Snipaste_2024-12-11_15-12-02.png>)
然后想办法再传一个shell进来，python，php都行，可以自己找，执行一下就行
在/var/www/html/wordpress/wp-config.php文件里
![Alt text](<../../../picture/THM/Tech_Supp0rt 1/Snipaste_2024-12-11_16-56-08.png>)
这对凭据直接可以使用ssh登录，不过用户名是`scamsite`。

最后使用`sudo -l`提权：
![Alt text](<../../../picture/THM/Tech_Supp0rt 1/Snipaste_2024-12-11_16-54-07.png>)