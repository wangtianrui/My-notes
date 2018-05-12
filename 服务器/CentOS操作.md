### 常用命令

- 软件操作命令 

```cmd
软件包管理器：yum
安装：yum install xxx
卸载:yum remove xxx
搜索：yum search xxx
清理缓存：yum clean packages
列出已安装：yum list
软件包信息：yum info xxx
```

* 资源操作

```cmd
硬件资源信息：

内存：
free -m 
硬盘：
df -h
负载：
w或者top    q退出  loadaverage是一个百分比负载数，1为满值。0.7为健康
cpu：
cat /proc/cpuinfo

fdisk  #格式化
```

* Linux文件目录结构，树状

```txt
根目录：/
家目录：/home
临时目录：/tmp
配置目录：/etc
用户程序目录：/usr
```

* 文件操作

```cmd
ls:查看目录下的文件
touch:新建文件
mkdir:新建文件夹    多层创建：mkdir -p test/wang/tian
cd:进入目录
rm:删除文件和目录    删除整个文件夹 rm -r 文件夹名 (循环删除)  -r会询问   -rf不会询问 
cp:复制  cp ./test ./usr/test
mv:移动 cp ./test  ./usr/test
pwd:显示路径
```

* vim   教程： http://www.runoob.com/linux/linux-vim.html

```cmd
i键为输入模式
esc退出当前模式
:wq 退出并保存
跳转行首：一次大写G跳到最后一行行首，两次小写g到第一行行首
删除行：小写dd
回退：小写u
复制：yy 
黏贴：p
显示行数：    :set number
```

* 文件权限 4-2-1   

```txt
二进制位数
r w x
2 1 0
r:read	   可读ls
w:write    可写
x:execute  可执行
所以r是4，w是2，x是1
```

* 文件搜索、查找、读取

```cmd
tail 从文件尾部读取    
head 从文件头部读取
cat 读取整个文件
more 分页读取
less 可控分页
grep 搜索关键字   grep "关键字" 文件名    grep -n "关键字" 文件名   #显示行号
find 查找文件
wc  统计个数   cat 文件名 | wc -l   显示行数

以上操作都可结合使用：yum list | grep firewall
```

* 文件解压缩

```cmd
tar命令
压缩：
tar -cf 文件名.tar 文件名
查看内容
tar -tf 文件名.tar
解压
tar -xf 文件名.tar

gz压缩：
tar -czvf 文件名.tar.gz 文件名
解压
tar -xzvf 文件名.tar.gz
```

* 系统用户命令

```cmd
https://www.cnblogs.com/whitehorse/p/5847278.html   两个添加用户的区别

useradd  添加用户 

adduser 添加用户

userdel  删除用户

passwd  设置密码   
```

* 防火墙设置

```cmd
安装：
yum install firewalld
启动：
service firewalld start
检查状态：
service firewalld status
关闭或者禁用防火墙：
service firewalld stop/disable

设置相关服务：
firewall-cmd --list-service=ssh
firewall-cmd --query-service=ssh
firewall-cmd --remove-service=ssh
firewall-cmd --add-service=ssh

firewall-cmd --list-all-zones
```

* 用户提权

```cmd
root下输入visudo
找到##Allows people in ......
在下面加上
%用户名 ALL=(ALL)   ALL  退出保存
```

* 文件下载

```cmd
下载
wget http://www.baidu.com
保存
curl -o baidu.html http://www.baidu.com
```

* 本地与服务器文件传送

```cmd
上传
scp imooc.txt root@公网号:存放路径
下载
scp root@公网号:文件路径 存放路径
```

