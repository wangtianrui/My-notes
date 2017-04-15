# tensorflow从零开始（第一天）

### 选择gpu来跑程序

```python
tf.device("/gpu:0")
```
### tensorflow对象

* 几乎所有tf的方法返回的都是一个op，而不是一个数值

* tensorflow用tensor数据类型来表示所有的数据，相当于一个N维数组或者列表

* 所有赋值都是使用一个tensorflow的对象来完成,tensorflow是一个“图”，通过向“图”中增加节点来组建整个程序

```python
hello = tf.constant('Hello Tensorflow')
```

### tf.Session()

```txt
该方法返回一个sess（会议），相当于是将该tensorflow中的东西全部融合在一起
该类有多层继承
```
* 方法一：run（一个操作 ）

```txt
  执行参数名字的进程
```
```python
hello = tf.constant('Hello Tensorflow')
sess = tf.Session()
sess.run(hello)  #执行hello的赋值但是没有输出
print(sess.run(hello)) #执行赋值并输出
```
```python
print(sess.run([updata,state])) #一个run还可以对多个op进行执行，返回一个tensor
```
```python
#1*2矩阵
matrix1=tf.constant([[3.,3.]])

#2*1矩阵
matrix2=tf.constant([[2.],[2.]])

sess = tf.Session()

result=tf.matmul(matrix1,matrix2) # 代表矩阵乘法的输出（动作），但不是输出（数值）

# 返回值 'product' 是一个 numpy `ndarray` 对象.
product=sess.run(result)#将输出赋值给product

print(product)

sess.close()
```

### with....as语句

```python
with tf.Session() as sess :
    print("a=2,b=3")
    print("Addition with constants:%i"% sess.run(a+b))
    print("Multiplication with constants:%i" % sess.run(a*b))
```
* 将with后面的变量用as后面的名字来代替


## 细谈tensor中的Rank,Shape,Type

### Rank(阶)

 ```txt
用来描述维度、顺序或者度数，比如
```

```python
 t = [[1, 2, 3], [4, 5, 6], [7, 8, 9]]
 # 表示的是一个2阶张量。
 ```
 
 * 2阶张量相当于就是一个二维空间，1阶则为一维，0维为一个数，以此类推

### Shape（形状）

 ```txt
阶数=维数，而Shape是用来衡量维数的一个变量
[] 为一个0维张量
[D0]为一个一维张量
[D0，D1]为一个二维张量
[D0,D1,D2]为一个三维张量
以此类推
 ```

 ### Type（类型）

 ```txt
DT_FLOAT	 tf.float32	32 位浮点数.
DT_DOUBLE	  tf.float64	64 位浮点数.
DT_INT64	 tf.int64	64 位有符号整型.
DT_INT32	 tf.int32	32 位有符号整型.
DT_INT16	 tf.int16	16 位有符号整型.
DT_INT8	  tf.int8	8 位有符号整型.
DT_UINT8	 tf.uint8	8 位无符号整型.
DT_STRING	  tf.string	可变长度的字节数组.每一个张量元素都是一个字节数组.
DT_BOOL	  tf.bool	布尔型.
DT_COMPLEX64	 tf.complex64	由两个32位浮点数组成的复数:实数和虚数.
DT_QINT32	  tf.qint32	用于量化Ops的32位有符号整型.
DT_QINT8	 tf.qint8	用于量化Ops的8位有符号整型.
DT_QUINT8	  tf.quint8	用于量化Ops的8位无符号整型.
```
## 变量（Variable）的基本用法

* #### 主要用于图执行过程中的状态信息（如：计数器）

```python
import tensorflow as tf

state = tf.Variable(0, name="counter") # name参数是Variable类的一个属性，在这儿可以调用state.name()得知该属性的值

one = tf.constant(1)
new_value = tf.add(state,one)
updata = tf.assign(state,new_value) #调用assign方法将new_value的值赋给state，updata为该op的“名字”

#变量必须初始化,（可以理解为分配空间，注意不是赋值）
init_operation = tf.initialize_all_variables()

sess = tf.Session()
orignData=sess.run(init_operation)
# print(orignData)              #输出'None'
# print(sess.run(state))         #输出'0'
# up_data=sess.run(updata)            #输出'1'
# print(up_data)
for _ in range(3):    #注意循环的使用
    sess.run(updata)
    print (sess.run(state))
    
sess.close()

```

## 后来输入的变量用feed来填充

```python
import tensorflow as tf

#使用placeholder()来创建占位符
input1 = tf.placeholder(tf.float32)
input2 = tf.placeholder(tf.float32)

output = tf.multiply(input1, input2)

with tf.Session() as sess:
  print (sess.run([output], feed_dict={input1:[7.], input2:[2.]}))
  #对占位符进行填充，进而实现动态数据赋值
```
