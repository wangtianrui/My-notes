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

##### * 几种激活函数的区别和使用

* sigmoid

```txt
1. 函数饱和使梯度消失
sigmoid 神经元在值为 0 或 1 的时候接近饱和，这些区域，梯度几乎为 0。因此在反向传播时，这个局部梯度会与整个代价函数关于该单元输出的梯度相乘，结果也会接近为 0 。
这样，几乎就没有信号通过神经元传到权重再到数据了，因此这时梯度就对模型的更新没有任何贡献。
除此之外，为了防止饱和，必须对于权重矩阵的初始化特别留意。比如，如果初始化权重过大，那么大多数神经元将会饱和，导致网络就几乎不学习。

2. sigmoid 函数不是关于原点中心对称的
这个特性会导致后面网络层的输入也不是零中心的，进而影响梯度下降的运作。
因为如果输入都是正数的话（如 中每个元素都 ），那么关于 的梯度在反向传播过程中，要么全是正数，要么全是负数（具体依据整个表达式 而定），这将会导致梯度下降权重更新时出现 z 字型的下降。
当然，如果是按 batch 去训练，那么每个 batch 可能得到不同的信号，整个批量的梯度加起来后可以缓解这个问题。因此，该问题相对于上面的神经元饱和问题来说只是个小麻烦，没有那么严重。
```
![](https://upload.wikimedia.org/wikipedia/commons/thumb/8/88/Logistic-curve.svg/600px-Logistic-curve.svg.png)

* tanh

```txt
tanh 函数同样存在饱和问题，但它的输出是零中心的，因此实际中 tanh 比 sigmoid 更受欢迎。
```

![](http://mathworld.wolfram.com/images/interactive/TanhReal.gif)

* relu

```txt
相较于 sigmoid 和 tanh 函数，ReLU 对于 SGD 的收敛有巨大的加速作用（Alex Krizhevsky 指出有 6 倍之多）。有人认为这是由它的线性、非饱和的公式导致的。
```

![](https://cs231n.github.io/assets/nn1/relu.jpeg)

![](http://7pn4yt.com1.z0.glb.clouddn.com/blog-relu-perf.png)
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


### 层数？(多层网络解决异或问题)

* 单纯的感知机无法解决异或问题，所以需要增加隐藏层数（可以理解为多次判断，多层“多条曲线”的结合）





