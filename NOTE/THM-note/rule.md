# RULE

## yara规则

### yara基本语法

>规则：  
``````
rule examplerule {
        condition: true
}
``````

执行：  
yara 规则文件.yar 其他

>注释

//单行

/*
多行
*/

### yara其他工具

>库

Cuckoo Sandbox：  


python的PE模块：  
https://pypi.org/project/pefile/


>yaratool

yara工具：  
https://github.com/InQuest/awesome-yara

>Loki

自述文件：  
https://github.com/Neo23x0/Loki/blob/master/README.md

下载位置；  
https://github.com/Neo23x0/Loki/releases


>THOR

THOR是企业版 THOR lite是民用版  
THOR lite:  
https://www.nextron-systems.com/thor-lite/

>FENRIR

https://github.com/Neo23x0/Fenrir

>YAYA

https://www.eff.org/deeplinks/2020/09/introducing-yaya-new-threat-hunting-tool-eff-threat-lab

>yarGen

位置：  
https://github.com/Neo23x0/yarGen

关于创建 Yara 规则和使用 yarGen 的进一步阅读：

https://www.bsk-consulting.de/2015/02/16/write-simple-sound-yara-rules/
https://www.bsk-consulting.de/2015/10/17/how-to-write-simple-but-sound-yara-rules-part-2/
https://www.bsk-consulting.de/2016/04/15/how-to-write-simple-but-sound-yara-rules-part-3/

>yarAnalyzer

https://github.com/Neo23x0/yarAnalyzer/

>Valhalla

https://www.nextron-systems.com/valhalla/



## snort规则



## wireshark rule

### 基本符号

范围： host,net, port and portrange
方向：  src、dst、src or dst、src and dst，<src是源头,dst是去处>
协议：  ether、wlan、ip、ip6、arp、rarp、tcp and udp。
用于捕获端口 80 流量的示例过滤器： tcp port 80

比较运算符和逻辑运算符与C语言相差不大


### 高级过滤

