# PowerShell


# 基础

## 基本介绍

Powershell 是使用 .NET Framework 构建的 Windows 脚本语言和 shell 环境。

这也允许 Powershell 直接从其 shell 执行 .NET 函数。大多数 Powershell 命令（称为 cmdlet）都是用 .NET 编写的。与其他脚本语言和 shell 环境不同，这些 cmdlet 的输出是对象，这使得 Powershell 在某种程度上是面向对象的。

这也意味着运行cmdlet允许您对输出对象执行操作（这样可以方便地将输出从一个 cmdlet 传递到另一个 cmdlet）。cmdlet 的正常格式使用Verb-Noun(动词-名词)表示

常用动词包括：
- Get
- Start
- Stop 
- Read
- Write
- New
- Out

在不了解cmdlet时，`Get-Command`,`Get-Help`非常重要。  

**Get-Help**
Get-Help显示有关 cmdlet 的信息。 若要获取有关特定命令的帮助，请运行以下命令：
`Get-Help <Command-Name>`
使用-examples举例:
`Get-Help <COMMAND> -examples`

**Get-Command**
Get-Command获取当前计算机上安装的所有 cmdlet。此 cmdlet 的优点在于它允许如下所示的模式匹配：  
`Get-Command Verb-*`或`Get-Command *-Noun`



**对象操作**
在上一个任务中，我们看到了每个 cmdlet 的输出如何是一个对象。如果我们想操作输出，我们需要弄清楚一些事情：
- 将输出传递给其他 cmdlet
- 使用特定对象 cmdlet 提取信息

**|(管道)**
Pipeline（） 用于将输出从一个 cmdlet 传递到另一个 cmdlet。与其他 shell 相比，主要区别在于 Powershell 将对象传递给下一个 cmdlet，而不是将文本或字符串传递到管道之后的命令。与面向对象框架中的每个对象一样，对象将包含方法和属性。
`Get-Command | Get-Member -MemberType Method`
这句命令的意思是列出powershell的所有方法。

### 对名词和动词的过滤

**动词**
查找与Get相匹配的命令：
```powershell
Get-Command -Verb 'Get'
```

**名词**
查找U开头的名词的命令：
```
Get-Command -Noun U*
```
查找与process相匹配的动词：
```
Get-Command -Name *-Process
```
### 筛选

**select-object**

Select-Object.此通用命令可帮助您从一个或多个属性中挑选出特定属性对象。您还可以限制取回的物品数量。(好像可以简写为select)

返回当前会话中可用的前 5 个命令的 Name 和 Source 属性值:
```powershell
Get-Command | Select-Object -First 5 -Property Name, Source
```
此示例创建的对象具有 Name、ID和工作集（WS）属性 的进程对象。
```powershell
Get-Process | Select-Object -Property ProcessName, Id, WS
```
获取process的所有属性列表：
```
Get-Process | Get-Member -MemberType Property
```
递归查找文件
```powershell
Get-ChildItem -Path C:\Users\lenovo\Desktop\ -Recurse -Filter "大白*"
```


**Get-Member**

获取service的对象：
```powershell
Get-Service | Get-Member
```
默认情况下，Get-Member不会获取静态成员或内部成员。
获取全部对象，加上-Force。

成员类型：
- AliasProperty
- CodeProperty
- Property
- NoteProperty
- ScriptProperty
- Properties
- PropertySet
- Method
- CodeMethod
- ScriptMethod
- Methods
- ParameterizedProperty
- MemberSet
- Event
- Dynamic
- All

# 