# Cat Pictures 2
tryhackme-challenge-easy

## 信息收集


### nmap

**全端口扫描**
![Alt text](../../../picture/THM/Cat-Pictures-2/Snipaste_2024-10-05_18-56-10.png)

这边有一个git泄露，robots也是看可以读的：
![Alt text](../../../picture/THM/Cat-Pictures-2/Snipaste_2024-10-05_18-59-20.png)

robots.txt:
![Alt text](../../../picture/THM/Cat-Pictures-2/Snipaste_2024-10-05_19-03-14.png)
好像有文件上传

左上角有一个登录框：
![Alt text](../../../picture/THM/Cat-Pictures-2/Snipaste_2024-10-05_19-29-42.png)

这四个文件是可以下载的：
![Alt text](../../../picture/THM/Cat-Pictures-2/Snipaste_2024-10-05_19-30-51.png)

其中/.gitignore文件的内容：
![Alt text](../../../picture/THM/Cat-Pictures-2/Snipaste_2024-10-05_19-32-19.png)
这里面的一些文件夹是可以访问的。

plugins/Log:
**You have to be logged in to see the log.**

plugins/Diagnostics/:
![Alt text](../../../picture/THM/Cat-Pictures-2/Snipaste_2024-10-05_19-34-46.png)

