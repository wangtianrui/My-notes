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
