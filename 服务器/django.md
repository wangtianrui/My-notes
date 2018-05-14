##### 安装专业版pycharm

##### 新建django项目

##### 修改setting.py中的DATABASE属性

```python
#让我们的django使用mysql数据库, options中的设置是为了兼容QQ登录等
DATABASES = {
    'default': {
        'ENGINE': 'django.db.backends.mysql',
        'NAME': "mxshop",
        'USER': 'root',
        'PASSWORD': '135410',
        'HOST': '127.0.0.1',
        'OPTIONS': {'init_command': 'SET default_storage_engine=INNODB;'}
    }
}
```

##### 设置好后运行不了。按要求安装mysqlclient

```cmd
pip install mysqlclient
#这里容易出错
www.lfd.uci.edu/~gohlke/ppythonlibs/  这个网址给出了在windows下安装经常出错的包。找到对应的包下载后可以本地进行安装
```

##### pillow(图片处理包)

##### 修改setting.py一些初始化信息方便后面开发

```python
import os
import sys

# Build paths inside the project like this: os.path.join(BASE_DIR, ...)
BASE_DIR = os.path.dirname(os.path.dirname(os.path.abspath(__file__)))
sys.path.insert(0, BASE_DIR)
sys.path.insert(0, os.path.join(BASE_DIR, 'apps'))
sys.path.insert(0, os.path.join(BASE_DIR, 'extra_apps'))
```

##### python中为django创建标准对象

```py
tools->run manager.py task....
然后在下面操作栏中输入  startapp 需要创建的对象名
```

##### 对象(一个对象文件中放所有和本对象有关的类，以下为Users)

```python
from datetime import datetime

from django.db import models
from django.contrib.auth.models import AbstractUser


# Create your models here.
class UserProfile(AbstractUser):
    """
    用户，定义字段
    """

    name = models.CharField(max_length=30, null=True, verbose_name="姓名")
    birthday = models.DateField(null=True, blank=True, verbose_name="出生年月")
    mobile = models.CharField(max_length=11, verbose_name="电话")
    gender = models.CharField(max_length=6, choices=(("male", u"男"), ("female", "女")), default="")
    email = models.CharField(max_length=100, null=True, blank=True, verbose_name="邮箱")

    class Meta:
        """
        ?????
        """
        verbose_name = "用户"
        verbose_name_plural = "用户"

    def __str__(self):
        """
        返回name
        :return:
        """
        return self.name


class VerifyCode(models):
    """
    短信验证码
    """
    code = models.CharField(max_length=10, verbose_name="验证码")  # CharField一定要加max_length
    mobile = models.CharField(max_length=11, verbose_name="电话")
    add_time = models.DateTimeField(default=datetime.now, verbose_name="添加时间")  # 注意now()和now的区别

    class Meta:
        verbose_name = "短信验证码"
        verbose_name_plural = verbose_name

    def __str__(self):
        return self.code

```

##### 替换系统用户对象

```python
#在settings.py中加入
AUTH_USER_MODEL = 'users.UserProfile'  #替换系统用户
```



