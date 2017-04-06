# tensorflow学习第二天

## MNIST数据集处理(单纯使用线性规划来进行图像识别)

* 首先将数据集（图片）映射成60000*784的张量，60000代表样本的数量，784代表每个样本的属性
* 然后把标签写成只有第n维度的数字为1的10维向量，既labels为一个60000*10的矩阵

### SoftMax回归介绍

* #### 一般分为两步

```txt
第一步，为了得到一张给定图片属于某个特定数字类的证据（evidence），我们对图片像素值进行加权求和。
如果这个像素具有很强的证据说明这张图片不属于该类，那么相应的权值为负数，
相反如果这个像素拥有有利的证据支持这张图片属于这个类，那么权值是正数。
进一步将一个图片的判别问题转换为一个线性问题

这一步主要涉及到对权重值W和偏量b的“优化”
```
```txt
第二步是使用SoftMax来处理线性公式后得到的数据，将数据转换为[0,1]之间的数据，更加便于分析
```
* #### 浅谈SoftMax函数（将得到的结果转换成概率）

* 相当于就是目标的取值取exp的值比上每个值取exp的和的比例（相当于概率）

* 问题来了，为啥要取exp函数呢？

```txt
可以将负无穷到0的数值无限逼近于0
```
* 为什么要用SoftMax函数？

```txt
这里的softmax可以看成是一个激励（activation）函数或者链接（link）函数，把我们定义的线性函数的输出转换成我们想要
的格式，也就是关于10个数字类的概率分布。因此，给定一张图片，它对于每一个数字的吻合度可以被softmax函数转换成为一个
概率值。
```

### 实现回归模型

* 模型计算涉及到很多算法，相对而言对系统资源的开销也比较大,tensorflow有它的处理方法

```txt
Tensorflow不单独地运行单一的复杂计算，而是让我们可以先用图描述一系列可交互的计算操作，然后全部一起在Python之外运行。
```

* 用python代码来实现softMax模型

```python
import tensorflow as tf

#x不是一个特定的值，而是一个占位符placeholder，我们在TensorFlow运行计算时输入这个值。
# 我们希望能够输入任意数量的MNIST图像，每一张图展平成784维的向量。我们用2维的浮点数张量来表示这些图，
# 这个张量的形状是[None，784 ]。
x=tf.placeholder("float",[None , 784]) #相当于就是样本集的输入占位符



#我们的模型也需要权重值和偏置量，当然我们可以把它们当做是另外的输入（使用占位符），但TensorFlow有一个
# 更好的方法来表示它们：Variable 。 一个Variable代表一个可修改的张量， 存在在TensorFlow的用于描述交互
# 性操作的图中。它们可以用于计算输入值，也可以在计算中被修改。 对于各种机器学习应用，一般都会有模型参数
# 可以用Variable表示。
w = tf.Variable(tf.zeros([784,10])) # 权重值(784*10的矩阵，思考为什么？)
b = tf.Variable(tf.zeros([10]))   # 偏量(10*1的矩阵，思考为什么？)
# W的维度是[784，10]，因为我们想要用784维的图片向量乘以它以得到一个10维的证据值向量，每一位对应不同数字类。
# b的形状是[10]，所以我们可以直接把它加到输出上面。


# 实现SoftMax回归模型
y=tf.nn.softmax(tf.matmul(x,w)+b)
```
### 浅谈交叉熵代价函数

* 交叉熵刻画的是两个概率分布之间的距离

* #### 有两个性质

```markdown
 * 非负性（所以可以通过研究该函数的最小值来减小loss）
 * 当输出值与实际值接近时，交叉熵趋近于0
 * 导数是“非压缩值”与实际值的差为主导，所以在误差很大时，权重更新很快
```
* 当我们用sigmoid函数作为神经元的激活函数时，最好使用交叉熵代价函数来替代方差代价函数，以避免训练过程太慢。

```python
# 开始计算误差
# 使用交叉熵

y_=tf.placeholder("float",[None,10]) # 用于输入正确值的占位符
cross_entropy = -tf.reduce_sum(y_real*tf.log(y_conv))
#注意，这里的交叉熵不仅仅用来衡量单一的一对预测和真实值，而是所有100幅图片的交叉熵的总和。
```
### 优化/训练评估

```python
 优化步骤
#在这里，我们要求TensorFlow用梯度下降算法（gradient descent algorithm）以0.01的学习速率最小化交叉熵。梯度下
# 降算法（gradient descent algorithm）是一个简单的学习过程，TensorFlow只需将每个变量一点点地往使成本不断降低
# 的方向移动
train_step = tf.train.GradientDescentOptimizer(0.01).minimize(cross_entropy)

#现在，我们已经设置好了我们的模型。在运行计算之前，我们需要添加一个操作来初始化我们创建的变量
init=tf.initialize_all_variables()


#启动初始化操作
sess = tf.Session()
sess.run(init)

#然后进行1000次训练
for i in range(1000):
    batch_xs, batch_ys = mnist.train.next_batch(100)
    sess.run(train_step,feed_dict={x:batch_xs,y:batch_ys})     #执行train_step，并且用batch_xs,batch_ys分别填补x,y


#评估模型
correct_prediction = tf.equal(tf.argmax(y,1), tf.argmax(y_,1))
#tf.argmax 是一个非常有用的函数，它能给出某个tensor对象在某一维上的其数据最大值所在的索引值。由于标签向量是由0,1组成，
# 因此最大值1所在的索引位置就是类别标签，比如tf.argmax(y,1)返回的是模型对于任一输入x预测到的标签值，而 tf.argmax(y_,1)
#  代表正确的标签，我们可以用 tf.equal 来检测我们的预测是否真实标签匹配(索引位置一样表示匹配)。


#为了更好地检测模型的“匹配性”单纯用布尔值不够直观，所以将布尔值转换为浮点型[True, False, True, True] 会变成 [1,0,1,1] ，
# 取平均值后得到 0.75.
accuracy = tf.reduce_mean(tf.cast(correct_prediction, "float"))

print (sess.run(accuracy, feed_dict={x: mnist.test.images, y_: mnist.test.labels}))

```
