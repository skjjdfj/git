#  GoldenEye
tryhackme-challenge-medium


##  介绍和列举

nmap快速扫描
![Alt text](../../../picture/THM/GoldenEye/Snipaste_2024-10-06_13-13-24.png)

详细扫描：
![Alt text](../../../picture/THM/GoldenEye/Snipaste_2024-10-06_13-15-28.png)

进入网站，在源码内部发现：
![Alt text](../../../picture/THM/GoldenEye/Snipaste_2024-10-06_13-16-19.png)

将字符串解密得到密码：
![Alt text](../../../picture/THM/GoldenEye/Snipaste_2024-10-06_13-19-34.png)

凭据：
boris
InvincibleHack3r

**使用 nmap 扫描网络中的所有端口。打开了多少个端口？**
答案：4
**谁需要确保他们更新默认密码？**
答案：boris
**他们的密码是什么？**
答案：InvincibleHack3r

##  邮寄时间到了...



**如果这些凭据似乎不起作用，您可以使用其他程序查找其他用户和密码吗？也许是 Hydra？他们的新密码是什么？**

**检查端口 55007，哪些服务配置为使用此端口？**
答案：