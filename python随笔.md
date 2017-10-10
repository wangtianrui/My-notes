#### 字符串

```python
print("Hello World")
message = 'Hello "1" World'
print(message)
message = "hello 'python' world"
print(message)
message = message.title()
print(message)
message = message.upper()
print(message)
message = message.lower()
print(message)

message2 = "I will print"
messageAdd = message2 + " " + message
print(messageAdd)

```
>Hello World

>Hello "1" World

>hello 'python' world

>Hello 'Python' World

>HELLO 'PYTHON' WORLD

>hello 'python' world

>I will print hello 'python' world

```python
message = '    python    '
print(message)
print(message.rstrip())  # 去掉后面的空格
print(message.lstrip())  # 去掉前面的空格
print(message.strip())  # 去掉前后的空格
```
>  ----python----    
>  ----python  
> python----      
>python

>"-"表示空格

```python
number = 23
# message = message + number  错误！TypeError: Can't convert 'int' object to str implicitly
# 必须先把int数据类型转换成string才能进行"+"
message = message + str(number)
print(message)
```
>    python    23

#### 列表
```python
bicycles = ['trek','cannondale','redline','specialized']
print(bicycles)
print(bicycles[0])
print(bicycles[-1]) #返回最后一个
print(bicycles[-2])#返回倒数第二个
print(bicycles[-3])#返回倒数第三个
```
>['trek', 'cannondale', 'redline', 'specialized']

>trek

>specialized

>redline

>cannondale

```python
bicycles.append('Giant') #在尾部加一个,动态改变列表
print(bicycles)
```
>['trek', 'cannondale', 'redline', 'specialized', 'Giant']

```python
'''
*****************动态改变列表*****************
'''
print("Original:",bicycles)

bicycles.append('Giant') #在尾部加一个
print("append:",bicycles)

bicycles.insert(2,'Fenghuang') #在位置2处增加一个元素
print("insert:",bicycles)

del bicycles[1]  #删除位置1的元素
print("del:",bicycles)

the_last_element = bicycles.pop() #弹出最后一个元素（删除后返回该元素）,“栈抛出”
print("pop:",the_last_element)
print("after pop:",bicycles)

poped_element = bicycles.pop(2) #弹出任意位子元素
print("pop2:",poped_element)
print("after pop2:",bicycles)

bicycles.remove('Fenghuang') #删除第一个出现的该变量，无返回值
print("remove:",bicycles)
deleted_element = 'specialized'
bicycles.remove(deleted_element)
print("remove:",bicycles)
print("I deleted " + deleted_element) #注意思想，这样可以暂时保存删除的变量
```

>Original: ['trek', 'cannondale', 'redline', 'specialized']

>append: ['trek', 'cannondale', 'redline', 'specialized', 'Giant']

>insert: ['trek', 'cannondale', 'Fenghuang', 'redline', 'specialized', 'Giant']
>del: ['trek', 'Fenghuang', 'redline', 'specialized', 'Giant']

>pop: Giant

>after pop: ['trek', 'Fenghuang', 'redline', 'specialized']

>pop2: redline

>after pop2: ['trek', 'Fenghuang', 'specialized']

>remove: ['trek', 'specialized']

>remove: ['trek']

>I deleted specialized

```python
'''
***************列表的顺序操作***************
'''
cars = ["bmw","audi","benz","toyota","Subaru"]
print("original:",cars)

cars.sort() #排序，并且无法变回以前的顺序
print("sort:",cars)

cars.sort(reverse=True) #倒序
print("reverse sort:",cars)

cars = ["bmw","audi","benz","toyota","Subaru"]
print("original:",cars)
cars_sort= sorted(cars) #此方法是将参数列表排序后返回给新的变量，原列表不变
print("after sorted the original:",cars,"\nthe return by sorted():",cars_sort)

print("original:",cars)
cars.reverse() #倒序，但是不会排序！
print("reverse:",cars)

print("len:",len(cars)) #得到列表长度
```
>original: ['bmw', 'audi', 'benz', 'toyota', 'Subaru']

>sort: ['Subaru', 'audi', 'benz', 'bmw', 'toyota']

>reverse sort: ['toyota', 'bmw', 'benz', 'audi', 'Subaru']

>original: ['bmw', 'audi', 'benz', 'toyota', 'Subaru']

>after sorted the original: ['bmw', 'audi', 'benz', 'toyota', 'Subaru']

>the return by sorted(): ['Subaru', 'audi', 'benz', 'bmw', 'toyota']

>original: ['bmw', 'audi', 'benz', 'toyota', 'Subaru']

>reverse: ['Subaru', 'toyota', 'benz', 'audi', 'bmw']

>len: 5
