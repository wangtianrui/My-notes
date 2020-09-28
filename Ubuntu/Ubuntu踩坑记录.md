# Ubuntu踩坑记录

#####  安装系统：注意装好后重启要修改*quiet splash*为nomodeset （在选择系统时，按e)

##### 进去后进行N卡驱动的下载  https://blog.csdn.net/qq_17573955/article/details/79143328  

##### 安装好显卡驱动后，重启，进行网络的配置:直接sh校园网.sh会报错，所以新建一个文档.sh

```txt
#! /bin/bash

./rjsupplicant.sh -u account -p password -d 1
```

pip freeze>request.txt

pip install -r request.txt

mysql wTr135410

/etc/init.d/nginx start

##### sh新建文档后会发现右上角的网络图标没了 https://blog.csdn.net/carl_qi/article/details/50769282

```txt
补充：在编辑文档时会遇到权限问题，这时需要 su root  获取root权限。然后cd到目标文件目录。sudo chmod +w Networkd....
获得权限后就可以进行文件的编辑
```

##### 镜像的使用

```txt
例如：pip install -i  https://pypi.douban.com/simple

http://mirrors.aliyun.com/pypi/simple/

https://pypi.mirrors.ustc.edu.cn/simple/

http://pypi.hustunique.com/
tensorflow   

pip install -i https://pypi.tuna.tsinghua.edu.cn/simple --trusted-host pypi.tuna.tsinghua.edu.cn numpy

原地址：https://github.com/xxx.git
替换为：https://github.com.cnpmjs.org/xxx.git
 
git clone https://github.com.cnpmjs.org/xxx.git

tensorflow 1.12.0

def plotmesh(x):
    shape = x.shape
    plt.pcolormesh(range(shape[0]), range(shape[1]), x.T)
    plt.show()
    
python导入c++库,出现找不到cl的情况
Install the C++ compiler https://visualstudio.microsoft.com/downloads/#build-tools-for-visual-studio-2019
Go to the installation folder (In my case it is): C:\Program Files (x86)\Microsoft Visual C++ Build Tools
Open Visual C++ 2015 x86 x64 Cross Build Tools Command Prompt
Type: pip install package_name

-DCMAKE_SH="CMAKE_SH-NOTFOUND
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

##### 删除文件

```txt
   rmdir 目录名        （删除一个空文件夹，文件夹里有内容则不可用）

　　rm -rf 非空目录名 （删除一个包含文件的文件夹）

　　rm 文件名 文件名 （删除多个文件）
```

##### 创建文件

```txt
touch 文件名        （新建一个空文件）
 mkdir 目录名        （新建一个文件夹，文件夹在Linux系统中叫做“目录”
```

##### 复制文件

```txt
cp 文件名 目标路径（拷贝一个文件到目标路径，如cp hserver /opt/hqueue）
```



##### git配置

```txt
https://www.cnblogs.com/superGG1990/p/6844952.html   git链接ssh
https://blog.csdn.net/vosang/article/details/50499300   无法push
```



jupyter notebook修改主题

https://blog.csdn.net/wh8514/article/details/81532286

代码提示

<https://www.cnblogs.com/qiuxirufeng/p/9609031.html>







![](https://s2.ax1x.com/2019/03/21/A1dnw4.png)

注意有个点



sudo apt-get update

sudo apt-get upgrade
sudo apt-get install lightdm

### .tar 文件

```bash
# 仅打包，并非压缩
tar -xvf FileName.tar         # 解包
tar -cvf FileName.tar DirName # 将DirName和其下所有文件（夹）打包123
```

### .gz文件

```bash
# .gz
gunzip FileName.gz  # 解压1
gzip -d FileName.gz # 解压2
gzip FileName       # 压缩，只能压缩文件1234
```

## .tar.gz文件、 .tgz文件

```bash
# .tar.gz 和 .tgz
tar -zxvf FileName.tar.gz               # 解压
tar -zcvf FileName.tar.gz DirName       # 将DirName和其下所有文件（夹）压缩
tar -C DesDirName -zxvf FileName.tar.gz # 解压到目标路径1234
```

### .zip文件

```bash
# 感觉.zip占用空间比.tar.gz大
unzip FileName.zip          # 解压
zip FileName.zip DirName    # 将DirName本身压缩
zip -r FileName.zip DirName # 压缩，递归处理，将指定目录下的所有文件和子目录一并压缩1234
```

### .rar文件

```bash
# mac和linux并没有自带rar，需要去下载
rar x FileName.rar      # 解压
rar a FileName.rar DirName # 压缩
```

