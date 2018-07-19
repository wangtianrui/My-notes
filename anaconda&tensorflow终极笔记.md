首先下载anaconda（别下最新版本，最好是后退一个版本）

如果下的是最新版本，python可能会出现不兼容tf的情况：

```
conda create --name 名字 python=3.5   #snowflake是自己想要的名字。创建一个环境python为3.5+
```

```
Linux，OS X: source activate snowflakes    #激活，切换到创建的环境
Windows：activate snowflake  
```



开始调用pip和conda进行必要包的安装

-i <https://pypi.tuna.tsinghua.edu.cn/simple>              #pip镜像



conda config --add channels https://mirrors.tuna.tsinghua.edu.cn/anaconda/pkgs/free/
conda config --set show_channel_urls yes        #conda镜像设置



CUDA：

下载9.0吧。+cudnn9.0的对应的tf是1.6.0    #网盘里有

pip install -i <https://pypi.tuna.tsinghua.edu.cn/simple> tensorflow==1.6.0





pip tensorflow 升降级





config = tf.ConfigProto() 
config.gpu_options.per_process_gpu_memory_fraction = 0.9 # 占用GPU90%的显存 
session = tf.Session(config=config)

config = tf.ConfigProto() 
config.gpu_options.allow_growth = True 
session = tf.Session(config=config)







