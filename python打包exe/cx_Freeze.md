### 安装cx_freeze

### 用的Python3.5

### setup.py文件
```python
import os
from cx_Freeze import setup, Executable

PYTHON_INSTALL_DIR = r"E:\Anaconda3\envs\mypython"
os.environ['TCL_LIBRARY'] = os.path.join(PYTHON_INSTALL_DIR, 'tcl', 'tcl8.6')
os.environ['TK_LIBRARY'] = os.path.join(PYTHON_INSTALL_DIR, 'tcl', 'tk8.6')

options = {
    'build_exe':
        {
            'excludes': [ 'Tkinter'],
            'packages': ['pandas', 'numpy'],

        }
}

executables = [Executable("Main.py")]
setup(
    name='hello',
    version='1.0',
    author="Adam",
    author_email="Omitted",
    options=options ,
    executables=executables
)

```

### python setup.py build


### utf-8问题
代码第一行加
#-*- coding: utf-8 -*-


### 找不到包问题
在setup.py里加入