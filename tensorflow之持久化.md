## tensorflow模型的持久化

* 将文件的“图”和“数据”保存至ckpt文件中

```python
# 在代码最后写下列代码可以进行保存操作
saver = tf.train.Saver()
saver.save(sess,'D:\python_code\pbResources\MNISTdata\modelMnist.ckpt')
```

```python
# 以下为提取操作
import tensorflow as tf

saver = tf.train.import_meta_graph('D:\python_code\pbResources\MNISTdata\modelMnist.ckpt.meta')

sess = tf.InteractiveSession()

saver.restore(sess,'D:\python_code\pbResources\MNISTdata\modelMnist.ckpt.index')

```
* 注意事项

```txt
可以在储存时指定需要储存或者加载的变量
saver = tf.train.Saver([v1]) #该代码就是只对v1值进行了储存或者加载
但是在执行该种操作时需要注意该操作只将v1加载，而v2（其他变量）却没有被加载，所以会出现变量错误的报错
```
