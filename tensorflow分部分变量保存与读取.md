## tensorflow部分参数分开保存与读取
##### test.py
```python
import tensorflow as tf

v1 = tf.Variable(tf.random_normal([1, 2]),float,name='input1')
v2 = tf.Variable(tf.random_normal([2, 3]),float,name='input2')
init_op = tf.global_variables_initializer()

print(v1)

saver = tf.train.Saver({'inV1':v1 ,'inV2':v2})
sess = tf.Session()
sess.run(init_op)
print("v1:", sess.run(v1)) # 打印v1、v2的值一会读取之后对比
print("v2:", sess.run(v2))
saver.save(sess,'data/data.ckpt')

```

```txt
Tensor("input1/read:0", shape=(1, 2), dtype=float32)
v1: [[ 1.06838226 -0.01669908]]
v2: [[-0.49939054  0.91445303  0.83253896]
     [-0.37793371  0.87875128  0.92503953]]

```
将v1与v2都存在了.ckpt中
##### readTest.py

```python
import tensorflow as tf


v2 = tf.Variable(tf.random_normal([2, 3]), float, name='input2')
init_op = tf.global_variables_initializer()
saver = tf.train.import_meta_graph("data/data.ckpt.meta")
with tf.Session() as sess:
    saver.restore(sess, "data/data.ckpt")
    # 通过张量的名称来获取张量

    sess.run(init_op)
    #注意这里名字需要用Tensor("input1/read:0", shape=(1, 2), dtype=float32)中的名字
    v1 = tf.get_default_graph().get_tensor_by_name("input1/read:0")
    
    print(sess.run(v1))

    print(sess.run(v2))

```

```txt
[[ 1.06838226 -0.01669908]]
[[-0.83223385  1.34131098 -0.38305116]
 [-1.11556876 -0.51651555  0.28670248]]
```
