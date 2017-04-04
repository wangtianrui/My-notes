## 占位符的使用

```python
import tensorflow as tf

w1 = tf.Variable(tf.random_normal([2,3],stddev=1,seed=1))   #seed是一个初始值
w2 = tf.Variable(tf.random_normal([3,1],stddev=1,seed=1))

x=tf.placeholder("float",shape=[1,2])
a = tf.matmul(x,w1)
y = tf.matmul(a,w2)

sess = tf.InteractiveSession()

init=tf.initialize_all_variables() # 该过程会自动处理变量之间的依赖关系

sess.run(init)
print(sess.run(y,feed_dict={x:[[0.7,0.9]]}))  #“连贯”run   # 使用了占位符后run的时候都需要feed_dict
#注意二维向量的书写，要有两层大括号

sess.close()

```
