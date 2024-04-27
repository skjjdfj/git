# AD

### 前置模块
红队基础知识->初始访问->妥协后->主机规避->网络安全规避

### 配置DNS

systemd-resolve --interface breachad --set-dns 10.200.26.101 --set-domain za.tryhackme.com

ntlmauth.za.tryhackme.com

sudo systemctl restart NetworkManager