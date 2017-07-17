### 浅谈dropout

* dropout对于防止过拟合效果不错，一般用在全连接的部分。
* Dropout是指在模型训练时随机让网络某些隐含层节点的权重不工作，不工作的那些节点可以暂时认为不是网络结构的一部分，但是它的权重得保留下来（只是暂时不更新而已），因为下次样本输入时它可能又得工作了


### 浅谈卷积

#### padding
* padding='VALID'卷积 

```python
conv2d(pool2, Wconv3, strides=[1, 1, 1, 1], padding='VALID')
```

```txt
VALID(可变的),卷积前后的图片的大小要变。
```

* padding='SAME'卷积（边界填充的卷积）

```python
conv2d(pool2, Wconv3, strides=[1, 1, 1, 1], padding='SAME')
```
```txt
SAME（不变的），卷积前后的图片大小不变
填补方法：（左奇右偶个数补零）
比如1 2 3 4 5 6 7 8 9 10 11 12 13 按步长为5，卷积大小为1*6卷积，那么12  13 将会被drop掉，如果利用边界填充的话需要填充3个0，就在1的左边加1个0（奇数个），在13的右边加2个0（偶数个）
```

#### input 

* 输入的图片

#### filter

* 卷积核，是一个Tensor,具有[filter_height, filter_width, in_channels, out_channels]这样的shape，具体含义是[卷积核的高度，卷积核的宽度，图像通道数，卷积核个数]，要求类型与参数input相同,filter的通道数要求与input的in_channels一致，有一个地方需要注意，第三维in_channels，就是参数input的第四维

# 整体代码实现

```python
import input_data
import tensorflow as tf
tf.device("/gpu:0")
mnist = input_data.read_data_sets('MNIST_data', one_hot=True)
sess = tf.InteractiveSession()  #就不用在后面调用tf.Session，所有sess都是默认的这个


# 构建占位符
x_input=tf.placeholder("float",shape=[None,784])  # None表示其值大小不定
y_real=tf.placeholder("float",shape=[None,10])

#下面进行卷积神经网络的书写

# 为了创建这个模型，我们需要创建大量的权重和偏置项。这个模型中的权重在初始化时应该加入少量的噪
# 声来打破对称性以及避免0梯度。由于我们使用的是ReLU神经元，因此比较好的做法是用一个较小的正数来
# 初始化偏置项，以避免神经元节点输出恒为0的问题（思考为什么）。
# 为了不在建立模型的时候反复做初始化操作，我们定义两个函数用于初始化。
def weight_variable(shape):
    initial=tf.truncated_normal(shape,stddev=0.1) #随机分配值，值相差为0.1（后面再做调试），想一下为什么要随机
    return tf.Variable(initial)
def bias_variable(shape):
    initial=tf.constant(0.1,shape=shape)  #不能为0，所以定的常量0.1后面再做修改
    return tf.Variable(initial)

#卷积和池化

#第一次卷积
W_conv1=weight_variable([5,5,1,32])
b_conv1=bias_variable([32])
#但是现在的x_input是一个一维向量，我们要把它转换为28*28的图像
x_image = tf.reshape(x_input, [-1,28,28,1])

h_cove1=tf.nn.relu(tf.nn.conv2d(x_image,W_conv1,strides=[1, 1, 1, 1], padding='VALID')+b_conv1)#对卷积后的每一个数使用relu激活
h_pool1=tf.nn.max_pool(h_cove1, ksize=[1, 2, 2, 1], strides=[1, 2, 2, 1], padding='SAME')#池化，将卷积后24*24的矩阵变成12*12的矩阵

#第二次卷积
W_conv2=weight_variable([5,5,32,64])
b_conv2=bias_variable([64])
h_cove2=tf.nn.relu(tf.nn.conv2d(h_pool1,W_conv2,strides=[1, 1, 1, 1], padding='VALID')+b_conv2) #第二次卷积后得到8*8
h_pool2=tf.nn.max_pool(h_cove2, ksize=[1, 2, 2, 1], strides=[1, 2, 2, 1], padding='SAME')#8*8变成4*4


#以上通过两次卷积一张图片变成了64个特征值
W_fc1=weight_variable([4*4*64,800])
b_fc1=bias_variable([800])
h_pool2_flat=tf.reshape(h_pool2,[-1,4*4*64])   #拉成一个一维的
h_fc1=tf.nn.relu(tf.matmul(h_pool2_flat,W_fc1)+b_fc1)  #变成400个特征值


#为了减少过拟合，我们在输出层之前加入dropout。我们用一个placeholder来代表一个神经元的输出在dropout中保持不变的概率。这样我
# 们可以在训练过程中启用dropout，在测试过程中关闭dropout。 TensorFlow的tf.nn.dropout操作除了可以屏蔽神经元的输出外，还会自
# 动处理神经元输出值的scale。所以用dropout的时候可以不用考虑scale。
keep_prob=tf.placeholder("float")
h_fc1_drop=tf.nn.dropout(h_fc1,keep_prob)



#再添加一个softMax层
W_fc2 = weight_variable([800, 10])
b_fc2 = bias_variable([10])

y_conv=tf.nn.softmax(tf.matmul(h_fc1_drop, W_fc2) + b_fc2) #执行softmax函数将数值压缩到0-1



#开始学习
cross_entropy = -tf.reduce_sum(y_real*tf.log(y_conv))


#我们会用更加复杂的ADAM优化器来做梯度最速下降，在feed_dict中加入额外的参数keep_prob来控制dropout比例
train_step2=tf.train.AdamOptimizer(1e-4).minimize(cross_entropy)
correct_prediction=tf.equal(tf.argmax(y_conv,1),tf.argmax(y_real,1)) # 预测的标签和实际的标签进行对比
accuracy=tf.reduce_mean(tf.cast(correct_prediction,"float"))    #reduce_mean 求tensor中平均值    tf.cast将前者参数类型转换为后者参数
sess.run(tf.initialize_all_variables())
for i in range (20000):
    batch = mnist.train.next_batch(50)
    if i%100==0:
        train_accuracy=accuracy.eval(feed_dict={x_input:batch[0],y_real:batch[1],keep_prob:1.0})#对最后一个tensor进行数据输入，输入后
                                                                                                 #系统会从下往上进行查找赋值，但是本次赋值只对该tensor有效
        print("step %d, training accuracy %g" % (i, train_accuracy))
    train_step2.run(feed_dict={x_input: batch[0], y_real: batch[1], keep_prob: 0.5})
print("test accuracy %g"%accuracy.eval(feed_dict={x_input: mnist.test.images, y_real: mnist.test.labels, keep_prob: 1.0}))




```

##### conv2d(input, filter, strides, padding, use_cudnn_on_gpu=None,data_format=None, name=None)
```text
第一个参数input：指需要做卷积的输入图像，它要求是一个Tensor，具有[batch, in_height, in_width, in_channels]这样的shape，具体含义是[训练时一个batch的图片数量, 图片高度, 图片宽度, 图像通道数]，注意这是一个4维的Tensor，要求类型为float32和float64其中之一
第二个参数filter：相当于CNN中的卷积核，它要求是一个Tensor，具有[filter_height, filter_width, in_channels, out_channels]这样的shape，具体含义是[卷积核的高度，卷积核的宽度，图像通道数，卷积核个数]，要求类型与参数input相同，有一个地方需要注意，第三维in_channels，就是参数input的第四维
第三个参数strides：卷积时在图像每一维的步长，这是一个一维的向量，长度4
第四个参数padding：string类型的量，只能是"SAME","VALID"其中之一，这个值决定了不同的卷积方式（后面会介绍）
第五个参数：use_cudnn_on_gpu:bool类型，是否使用cudnn加速，默认为true
结果返回一个Tensor，这个输出，就是我们常说的feature map
```
