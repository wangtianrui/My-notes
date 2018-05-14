https://www.cnblogs.com/FZfangzheng/p/7588944.html



#### 安装python虚拟环境

window：

```cmd
安装虚拟环境
pip install virtualenv
virtualenv 环境名    新建的环境放在当前操作目录
```

Centos:

```cmd
yum install python-virtualenv

新建环境（默认2.7）
virtualenv 环境名
激活：
cd 环境名/bin
source activate 

新建环境（3.6+）
virtualenv -p python3安装路径(默认是在 /usr/bin/python3) 环境名

deactivate 关闭当前环境
```

#### 虚拟环境管理包

```cmd
pip install virtualenvwrapper

找到.sh文件
sudo find / -name virtualenvwrapper

配置source文件
vim ~/.bashrc 
在后面加上配置信息，详细看网盘教程。生鲜超市那个
```

#### 安装django rest framework

安装django

然后安装framework

```cmd
http://www.django-rest-framework.org/#installation
```



