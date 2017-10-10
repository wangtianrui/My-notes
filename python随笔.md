#### python字符串

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
