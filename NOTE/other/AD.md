# AD

## thm-AD

### 配置DNS

systemd-resolve --interface breachad --set-dns 10.200.26.101 --set-domain za.tryhackme.com

ntlmauth.za.tryhackme.com

sudo systemctl restart NetworkManager


## HTBA-AD

### 基础知识

对Windows来说很重要的端口：
```
53: .DNS
88: .Kerberos
135: /.WMIRPC
137-139 & 445: .SMB
389 & 636: .LDAP
3389: RDP
5985 & 5896: PowerShell Remoting (WinRM)
```

## AD-other


