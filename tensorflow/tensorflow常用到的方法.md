## tensorflow的一些常用的函数

* ### 数字的生成函数

* 随机数的生成

```text
tf.random_normal(平均值，标准差，取值类型)        随机数满足正态分布     
tf.truncated_normal(平均值，标准差，取值类型)     随机数满足正态分布，如果随机出来的数偏离平均值超过两个标准差，那么这个数将会被重新随机
tf.random_uniform(最小值，最大值，取值类型)       随机数满足平均分布
tf.random_gamma(形状参数，尺度参数，取值类型)     随机数满足Gamma分布
```

* 常数生成

```text
tf.zeros(矩阵规格，取值类型)          产生全为0的矩阵
tf.ones(矩阵规格，取值类型)           产生全为1的矩阵
tf.fill(矩阵规格，数值i)              产生全为数值i的矩阵
tf.constant(矩阵值)                  直接产生常量
```
* 交叉熵计算

```txt
cross_entropy = -tf.reduce_sum(y_real*tf.log(y_result)) 

reduce_sum函数是求和函数(此处的reduce可以理解为压缩的意思)
```
* softmax函数

```txt
y_conv=tf.nn.softmax(tf.matmul(h_fc1_drop, W_fc2) + b_fc2) #执行softmax函数将数值压缩到0-1，转换为概率
```
* 常用优化方法

```python
tf.train.GradientDescentOptimizer().minimize()  # 梯度下降法
tf.train.AdamOptimizer().minimize()  #综合梯度下降法和随机梯度下降法
tf.train.MomentumOptimizer().minimize() #动量型梯度下降法 （ 加快优化速率 ）
```

## 滑动平均模型

* 在tensorflow中提供了tf.train.ExponentialMovingAverage来实现滑动平均模型

```txt
在初始化时需要一个参数：衰减率(decay)  //将会用于控制模型更新速度，值越大模型越趋近于稳定，一般设置为接近
1的值如0.999
```
```python
import tensorflow as tf

#定义一个变量用于计算滑动平均，初始值为0，滑动平均的变量必须是实数型
v1 = tf.Variable(0,dtype=tf.float32)
#控制迭代轮数
step = tf.Variable(0,trainable=False)

#定义一个滑动平均的类（class），初始化衰减率为0.99
ema = tf.train.ExponentialMovingAverage(0.99,step)

maintain_averages_op = ema.apply([v1])

sess = tf.InteractiveSession()

init_op = tf.initialize_all_variables()
sess.run(init_op)

print(sess.run([v1,ema.average(v1)]))
sess.run(tf.assign(v1,5))
sess.run(maintain_averages_op)

print(sess.run([v1,ema.average(v1)]))

sess.run(tf.assign(step,10000))
sess.run(tf.assign(v1,10))
sess.run(maintain_averages_op)
print(sess.run([v1,ema.average(v1)]))

```
* #### 分布式程序通过tf.app.run()来运行

* #### flags用来存储管理多个变量

* #### python assert断言语句的语法
```python
assert 1==1
assert 2+2==2*2
assert len(['my boy',12])<10
assert range(4)==[0,1,2,3]
```
```txt
如果断言语句中出现了flase，那么程序会报错
```
* ### tf.transpose(x,perm=[])

```txt
实现对x的转置，转置为perm型
```

```python
x =  [[1 2 3]
      [4 5 6]]

tf.transpose(x) ==> [[1 4]
                     [2 5]
                     [3 6]]

tf.transpose(x) 等价于：
tf.transpose(x perm=[1, 0]) ==> [[1 4]
                                 [2 5]
                                 [3 6]]

'x' =  [[[1  2  3]
         [4  5  6]]
        [[7  8  9]
         [10 11 12]]]

tf.transpose(b, perm=[0, 2, 1]) ==> [[[1  4]
                                      [2  5]
                                      [3  6]]
                                     [[7 10]
                                      [8 11]
                                      [9 12]]]
```
* ### os.path.join()

```txt
是在拼接路径的时候用的。举个例子，
os.path.join(“home”, "me", "mywork")
在Linux系统上会返回
“home/me/mywork"
在Windows系统上会返回
"home\me\mywork"
好处是可以根据系统自动选择正确的路径分隔符"/"或"\"
```

