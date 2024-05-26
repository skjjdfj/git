# AD

## 枚举AD

>通过CMD枚举：

枚举所有的AD用户：  
``````
net user /domain
net user zoe.marshall /domain
枚举某一个用户的信息
``````
注意：如果用户只是少数 AD 组的一部分，则此命令将能够向我们显示组成员身份。但是，通常，在超过十个组成员身份后，该命令将无法列出所有组成员身份


枚举AD组：

``````
net group /domain
net group "Tier 1 Admins" /domain
枚举一个组的信息，包括成员身份
``````

枚举密码策略：
``````
net accounts
``````

>通过powershell枚举：

通过powershell的cmdlet枚举，cmdlet可以自己编写

>Get-ADUser

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

>Get-ADGroup

``````
Get-ADGroup -Identity Administrators -Server za.tryhackme.com
``````

可以用Get-ADGroupMember枚举组员身份
``````
Get-ADGroupMember -Identity Administrators -Server za.tryhackme.com
``````

>Get-ADObject

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


>Get-ADDomain

``````
Get-ADDomain -Server za.tryhackme.com
``````
枚举域

>Set-ADAccountPassword
更改AD对象
``````
Set-ADAccountPassword -Identity gordon.stevens -Server za.tryhackme.com -OldPassword (ConvertTo-SecureString -AsPlaintext "old" -force) -NewPassword (ConvertTo-SecureString -AsPlainText "new" -Force)
``````


强大的枚举工具：bloodhound


## 横向移动与旋转

### 远程生成进程

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





## 内网使用的工具

### mimikatz

mimikatz使用需要提权到administrator。

命令| 描述
|-|-| 
privilege::debug |
sekurlsa::wdigest |
sekurlsa::USERNAEM |