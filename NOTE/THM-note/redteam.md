# 红队

## 红队基础知识



## 武器化

>windows脚本主机-WSH

Windows 脚本主机是一个内置的 Windows 管理工具，它运行批处理文件以自动执行和管理操作系统中的任务。

它是一个 Windows 本机引擎，cscript.exe（用于命令行脚本）和 wscript.exe（用于 UI 脚本），负责执行各种Microsoft Visual Basic 脚本 （VBScript），包括 vbs 和 vbe。有关 VBScript 的更多信息，请访问此处。需要注意的是，Windows 操作系统上的 VBScript 引擎以与普通用户相同的访问和权限级别运行和执行应用程序;因此，它对红队队员很有用。

一段弹窗的vbs代码：
``````
Dim message 
message = "Welcome to THM"
MsgBox message
``````

一段弹出计算器的代码：
``````
Set shell = WScript.CreateObject("Wscript.Shell")
shell.Run("C:\Windows\System32\calc.exe " & WScript.ScriptFullName),0,True
``````
ps:这个地方的calc.exe本来可以换成cmd.exe调出终端的，但是实现不了，不知道为啥。



>HTML应用程序-HTA

HTA 代表“HTML 应用程序”。它允许您创建一个可下载的文件，该文件包含有关其显示和呈现方式的所有信息。HTML 应用程序，也称为 HTA，它们是包含 JScript 和 VBScript 的动态 HTML 页面。LOLBINS（Living-of-the-land Binaries）工具mshta用于执行HTA文件。它可以自行执行，也可以从 Internet Explorer 自动执行。

可以调出终端的hta代码：
``````
<html>
<body>
<script>
	var c= 'cmd.exe'
	new ActiveXObject('WScript.Shell').Run(c);
</script>
</body>
</html>
``````

>Visual Basic应用程序-VBA

VBA 代表 Visual Basic for Applications，这是 Microsoft 为 Microsoft 应用程序（如 Microsoft Word、Excel、PowerPoint 等）实现的一种编程语言。 VBA 编程允许自动执行用户与 Microsoft Office 应用程序之间几乎所有键盘和鼠标交互的任务。

宏是 Microsoft Office 应用程序，其中包含用称为 Visual Basic for Applications （VBA） 的编程语言编写的嵌入式代码。它用于创建自定义函数，通过创建自动化流程来加快手动任务。VBA 的功能之一是访问 Windows 应用程序编程接口 （API） 和其他低级功能

打开宏：  
视图(view)->宏(macros)


>PowerShell-PSH


## 钓鱼

超链接代码：
``````
<a href="http://spoofsite.thm">Click Here</a>
<a href="http://spoofsite.thm">https://onlinebank.thm</a>
``````

基础设施：  
- 域名
- SSL/TLS 证书
- 电子邮件服务器/帐户
- DNS记录
- 网络服务器
- 分析
- 自动化和有用的软件
- GoPhish -（开源网络钓鱼框架） getgophish.com
- SET -（社会工程工具包） trustedsec.com





## 妥协后

## 主机规避

## 网络安全规避

## 危害活动目录


# 红队实战经验


