# CTFshow-web

## 命令执行

### 执行命令的方法

system()

shell_exec()

`

popen


## 规避字符

规避空格：  
%20，%09、$IFS$9、${IFS}

注意：上面的$需要用反斜杠进行转义

规避其他字符：  
过滤的flag，php，点，可以用通配符*或?代替  

## 文件包含

1.造成文件包含漏洞的函数通常有：
include、require、include_once、require_once、highlight_file、show_source、file_get_contents、fopen、file、readline
2.data协议
用法：
data://text/plain,xxxx(要执行的php代码)
data://text/plain;base64,xxxx(base64编码后的数据)
3.php://协议
php://input,用于执行php代码，需要post请求提交数据。
————————————————


