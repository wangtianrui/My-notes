# Ubuntu踩坑记录

#####  安装系统：注意装好后重启要修改*quiet splash*为nomodeset （在选择系统时，按e)

##### 进去后进行N卡驱动的下载  https://blog.csdn.net/qq_17573955/article/details/79143328  

##### 安装好显卡驱动后，重启，进行网络的配置:直接sh校园网.sh会报错，所以新建一个文档.sh

```txt
#! /bin/bash

./rjsupplicant.sh -u account -p password -d 1
```



##### sh新建文档后会发现右上角的网络图标没了 https://blog.csdn.net/carl_qi/article/details/50769282

```txt
补充：在编辑文档时会遇到权限问题，这时需要 su root  获取root权限。然后cd到目标文件目录。sudo chmod +w Networkd....
获得权限后就可以进行文件的编辑
```

##### 镜像的使用

```txt
例如：pip install -i http://e.pypi.python.org/simple tensorflow   这个是使用的清华大学打镜像
```

##### 为sh文件创建快捷方式

```txt
新建appName.desktop  --> vim/gedit 编辑该文件;如下信息：

[Desktop Entry]

Encoding=UTF-8

Name=webstorm

Comment=webstorm IDE

Exec=/home/yin/WebStorm-171.4424.58/bin/webstorm.sh

Icon=/home/yin/WebStorm-171.4424.58/bin/webstorm.svg

Terminal=false

StartupNotify=true

Type=Application

Categories=Application;Development;


```

下载东西https://blog.csdn.net/Liuqz2009/article/details/52087019

##### .deb文件安装

```txt
sudo dpkg -i 文件名
会失败然后
 sudo apt-get -f install
 sudo netease-cloud-music
```

##### 复制文件

```txt
sudo mv 目标文件 目标目录  
```

![](https://images2015.cnblogs.com/blog/16576/201607/16576-20160710222051796-1907038675.png)

