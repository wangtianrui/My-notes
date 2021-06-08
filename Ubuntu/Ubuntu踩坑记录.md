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

使用方式用实际的名称替换{}的内容，即可加速clone
https://hub.fastgit.org/{username}/{reponame}.git
clone 出来的 remote "origin" 为fastgit的地址，需要手动改回来
你也可以直接使用他们的clone加速工具 fgit-go

github.com的镜像网站(注意：不能登录)
hub.fastgit.org
github.com.cnpmjs.org 这个很容易超限
 
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





注意有个点



sudo apt-get update

sudo apt-get upgrad
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

### git

```cmd
git config --global http.proxy 127.0.0.1:1080
git config --global https.proxy 127.0.0.1:1080

vim ~/.gitconfig

git config --global --unset http.proxy
git config --global --unset https.proxy
curl 'http://10.10.43.3' --data "DDDDD=20120318&upass=015511&0MKKey="

export GIT_SSL_NO_VERIFY=1

  git config --global user.email "1056992492@qq.com"
  git config --global user.name "ScorpioMiku"
```

# awk

```
awk` `'{pattern + action}'` `{filenames}
```

![](https://images2015.cnblogs.com/blog/1089507/201701/1089507-20170126222420597-662074402.jpg)

```
实例一：统计/etc/passwd的账户人数
[root@Gin scripts]``# awk 'BEGIN {count=0;print "[start] user count is ",count} {count=count+1;print $0} END{print "[end] user count is ",count}' passwd
[start] user count is 0
root:x:0:0:root:``/root``:``/bin/bash
...................................................................
[end] user count is 27
```

```
实例二：统计某个文件夹下的文件占用的字节数
[root@Gin scripts]``# ll |awk 'BEGIN {size=0;} {size=size+$5;} END{print "[end]size is ",size}'
[end]size is 1489
```

```
[root@Gin scripts]``# awk 'BEGIN{a=5;a+=5;print a}'
10
```

```
[root@Gin scripts]``# awk 'BEGIN{a=1;b=2;print (a>2&&b>1,a=1||b>1)}'
0 1
```

```
正则
[root@Gin scripts]``# awk 'BEGIN{a="100testaa";if(a~/100/) {print "ok"}}'
ok
```

```
FS="\t" 一个或多个 Tab 分隔 （FS可以自己定义）
[root@Gin scripts]``# cat tab.txt
ww  CC    IDD
[root@Gin scripts]``# awk 'BEGIN{FS="\t+"}{print $1,$2,$3}' tab.txt
ww  CC    IDD
```

```
FS="[[:space:]+]" 一个或多个空白空格，默认的
[root@Gin scripts]``# cat space.txt
we are  studing ``awk` `now!
[root@Gin scripts]``# awk -F [[:space:]+] '{print $1,$2,$3,$4,$5}' space.txt
we are 
[root@Gin scripts]``# awk -F [[:space:]+] '{print $1,$2}' space.txt
we are
```

```
FS="[" ":]+" 以一个或多个空格或：分隔
[root@Gin scripts]``# cat hello.txt
root:x:0:0:root:``/root``:``/bin/bash
[root@Gin scripts]``# awk -F [" ":]+ '{print $1,$2,$3}' hello.txt
root x 0
```

```
字段数量 NF
[root@Gin scripts]``# cat hello.txt
root:x:0:0:root:``/root``:``/bin/bash
bin:x:1:1:bin:``/bin``:``/sbin/nologin``:888
[root@Gin scripts]``# awk -F ":" 'NF==8{print $0}' hello.txt
bin:x:1:1:bin:``/bin``:``/sbin/nologin``:888
```

```
记录数量 NR
[root@Gin scripts]``# ifconfig eth0|awk -F [" ":]+ 'NR==2{print $4}' ## NR==2也就是取第2行
192.168.17.129
```

#### while(<>) 打开文件的所有行