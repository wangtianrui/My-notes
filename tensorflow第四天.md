## 网络解决二分类问题

```python
import tensorflow as tf
from numpy.random import RandomState  #通过工具包生成虚拟数据集


rdm=RandomState(1)
data_size = 128
X1 = rdm.rand(data_size,2)
y_real1 = [[int (x1+x2<1)]for (x1,x2) in X1]

sess = tf.InteractiveSession()

x_input = tf.placeholder('float',[None,2])
y_real = tf.placeholder('float',[None,128])

batch_size = 8   #定义batch（一批数据）的大小

def weight_variable(shape):
    return tf.random_normal(shape=shape,stddev=0.1)

def bias_variable(shape):
    return tf.constant(0.1,shape=shape)

w1=weight_variable([2,3])
w2=weight_variable([3,1])


a=tf.matmul(x_input,w1)
y_result = tf.matmul(a,w2)

cross_entropy = -tf.reduce_sum(y_real*tf.log(tf.clip_by_value(y_result,1e-10,1.0)))


train_step = tf.train.AdamOptimizer(0.01).minimize(cross_entropy)

init=tf.initialize_all_variables()

sess.run(init)
sess.run(train_step,feed_dict={x_input:X1,y_real:y_real1})
sess.close()
```

## 线性模型的局限性

* 向前传播的算法根据矩阵乘法的结合律可以看作是两个w相乘后的一个新的w

* 所以向前传播的方法就是一个线性模型

* 形如：游乐场中第一种模型分布，就是线性不可分的。并且在有噪音的情况下划分效果更加糟糕

### 所以需要激活函数来把线性问题转换为非线性问题

* 激活函数实现去线性化

* 是将“规划的方法(计算出来的规划直线)进行非线性变化”，而不是将数据进行非线性变化


![](http://img.blog.csdn.net/20160630114839844)


```python
#可将线性分布的
y_conv=tf.nn.softmax(tf.matmul(h_fc1_drop, W_fc2) + b_fc2)
```

```txt
激活函数，并不是去激活什么，而是指如何把“激活的神经元的特征”通过函数把特征保留并映射出来（保留特征，去除一些数据中是的冗余），这是神经网络能解决非线性问题关键
```

### 一个神经网络为什么要有那么多参数？？

* input所走的一个“线性划分线”（比如：y1=x1 * w1 + b）代表了一个划分线，最终划分标准（曲线）是根据多个“线性划分线”合成的。

![](http://img.blog.csdn.net/20160630103416973)

![](http://img.blog.csdn.net/20160630104959185)
### 参数的量？

* 根据划分所需要的直线的条数来大致确认

* 直线的条数越多（参数的层数越多），划分越准确（但是考虑到过拟化问题不能太多，需要根据实际情况做出调整）
