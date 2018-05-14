#### 安装

```cmd
sudo apt-get install mysql-server
```

##### 查看状态

```cmd
ps aux | grep mysqld
```

##### 登陆进入mysql

```cmd
mysql -uroot -p
退出
exit;
```

#####   让外部系统能够链接到远程mysql

```cmd
查看配置文件
sudo vim /etc/mysql/mysql.conf.d/mysqld.cnf
找到bind-address    默认是本地ip
改为0.0.0.0
然后重启服务

查看mysql能供哪些IP使用在mysql中使用
use mysql;
select host,user from user;
```

##### 查找ip地址

```cmd
ifconfig
inet为需要的ip
```

##### 在navicat中点击链接输入ip