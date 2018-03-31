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
补充：在编辑文档时会遇到权限问题，这时需要 su root
```

