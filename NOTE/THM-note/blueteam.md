# BlueTeam

- [BlueTeam](#blueteam)
  - [威胁情报](#威胁情报)
    - [kill-chain](#kill-chain)
    - [Miter ATT\&CK](#miter-attck)
  - [取证](#取证)
  - [事件管理](#事件管理)
  - [钓鱼](#钓鱼)
  - [安全运营与监控](#安全运营与监控)
    - [端点安全监控](#端点安全监控)





## 威胁情报

### kill-chain

### Miter ATT&CK



## 取证

## 事件管理

## 钓鱼

## 安全运营与监控

### 端点安全监控


>system

系统进程（进程 ID 4）是仅在内核模式下运行的特殊线程的主页，即内核模式系统线程。系统线程具有常规用户模式线程的所有属性和上下文（例如硬件上下文、优先级等），但不同之处在于它们仅在内核模式下运行，执行在系统空间中加载的代码，无论是在 Ntoskrnl.exe 中还是在任何其他加载的设备驱动程序中。此外，系统线程没有用户进程地址空间，因此必须从操作系统内存堆（如分页池或非分页池）分配任何动态存储。

>system>smss.exe

smss.exe: 会话管理器子系统，也成为windows会话管理器，负责创建新会话。它是内核启动的第一个用户模式进程。  

该子系统包括 win32k.sys（内核模式）、winsrv.dll（用户模式）和 csrss.exe（用户模式）。  

Smss.exe启动csrss.exe（Windows 子系统）并在会话 0（操作系统的隔离 Windows 会话）中wininit.exe，并在会话 1（即用户会话）中启动csrss.exe和winlogon.exe。第一个子实例在新会话中创建子实例，smss.exe将自身复制到新会话中并自行终止即可完成  

SMSS 还负责创建环境变量、虚拟内存分页文件和启动winlogon.exe（Windows 登录管理器）。  

>csrss.exe

csrss.exe（客户端服务器运行时进程）是 Windows 子系统的用户模式端。此过程始终处于运行状态，对系统操作至关重要。如果此过程偶然终止，将导致系统故障。此进程负责 Win32 控制台窗口和进程线程的创建和删除。对于每个实例，都会加载 csrsrv.dll、basesrv.dll 和 winsrv.dll（以及其他实例）。

>wininit.exe

Windows 初始化进程 （wininit.exe） 负责在会话 0 中启动 services.exe（服务控制管理器）、lsass.exe（本地安全机构）和lsaiso.exe。它是另一个在后台运行的关键 Windows 进程，以及它的子进程。



>wininit.exe > services.exe



>wininit.exe > services.exe > svchost.exe

>lsass.exe

>winlogon.exe

>explorer.exe