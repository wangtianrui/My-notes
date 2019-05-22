## BeautifulSoup
> 支持Python中HTML解析器

#### 创建一个操作对象

```python
from bs4 import BeautifulSoup

# 创建一个链接的对象
soup = BeautifulSoup(html, 'lxml')
#创建本地的网页的对象
soup = BeautifulSoup(open(r"E:\androidprogrames\pigs\dians\index.html"), features='lxml')
```

#### 四种对象
Beautiful Soup将复杂的HTML文档转换为一个复杂的树形结构，每个节点都是Python对象，所有对象归纳为4种
* Tag
```python
#常见的网页容器
soup.title
soup.head
soup.a
soup.p
#Tag的两个重要属性 name 和 attrs
soup.name
soup.a.name
soup.attrs
```
* NavigableString
```python
得到了标签，可用.string
```
* BeautifulSoup
* Comment

#### 遍历文档树

```python
#tag的.content属性可以将tag的子节点以列表的方式输出
soup.head.contents

# tag的.children返回的不是一个list，但是是一个迭代器
soup.head.children

#.descendants是所有的子孙节点，用法和children类似

#strings 当一个标签下面包含多个内容时，采用strings进行获取，string会变成None

```
* 当标签内有多条内容时，用strings
* stripped_strings
去掉多余空白内容
* 单个父节点
```python
soup.parent
```
* 所有父节点
```python
.parents
```
* 兄弟节点
```python
next_sibling
```
* 所有兄弟节点
```python
next_siblings
```
* 前后节点
```python
.next_elements 
.previous_elements 
```

#### 高级检索