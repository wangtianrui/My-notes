##### SSH——安全外壳协议

SSH 为建立在应用层基础上的安全协议。SSH 是目前较可靠，专为远程登录会话和其他网络服务提供安全性的协议。利用 SSH 协议可以有效防止远程管理过程中的信息泄露问题。

- 在服务器上安装ssh

```cmd
yum install openssh-server    使用的root（centos无界面版默认装好的）
```

- 启动SSH

```cmd
service sshd start
```

- 设置开机自动启动

```cmd
chkconfig sshd on
```

- 查看进程在不在

```cmd
ps -ef |grep ssh
```

- 安装客户端

```cmd
yum install openssh-clients
```

- 使用SSH连接远程服务器，可以在另一台电脑操作远程终端

```cmd
ssh root@公网IP
```

##### SSH config讲解

config为了方便我们批量管理多个SSH，config存放在 ~/.ssh/config 

- ssh config语法关键字

|     Host     |   别名    |
| :----------: | :-----: |
|   HostName   |   主机名   |
|     Port     |   端口    |
|     User     |   用户名   |
| IdentityFile | 密钥文件的路径 |

* ctrl + c 

终止操作

* ifconfig

查看当前服务器状况（ip地址之类的）

* 新建ssh config文件

```cmd
cd ~/.ssh/   
ls 只有一个knowm_hosts文件
touch config           新建文件
vim config
输入
host "wang"
	HostName 公网ip
	User root
	Port 22
```

通过 ssh wang 就可以直接连接了

```cmd
如果多个服务器

host "wang"
	HostName 公网ip1
	User root
	Port 22
	
host "wang2"
	HostName 公网ip2
	User root
	Port 22
```

* 免密码登录:ssh key

ssh key使用非对称加密方式生成公钥和私钥，私钥放在本地 ~/.ssh目录.公钥可以对外开放，放在服务器的~/.ssh/authorized_keys

```cmd
linux系统生成 ssh key:
需要root
ssh-keygen -t rsa
或者 ssh-keygen -t dsa   加密方式不同

ls -al  可以看到刚刚生成的文件  .pub为公钥 没有后缀为私钥
```

使用公钥前，需要添加authorized_keys

```cmd
把公钥里的信息复制到authorized_keys文件
```

* 修改端口号

```cmd
vim /etc/ssh/sshd_config

修改Port后面的号数就行    #为注释   可以写多个端口

service sshd restart
```

