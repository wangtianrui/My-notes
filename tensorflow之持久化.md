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
## 持久化原理以及数据格式

#### 回顾

```txt
tensorflow是以图与节点的形式进行数据运算，tensorflow通过MetaGraph（元图）来记录计算图中的节点信息以及
运行计算图中接点所需要的元数据。
```

#### MetaGraphDef 

* tensorflow中的元图是由MetaGraphDef Protocol Buffer定义的，所以 MetaGraphDef 构成了持久问及文件中的第一个文件（modelMnist.ckpt.meta）

* 元图中包含了4种重要的信息

```txt
1 . meta_info_def : 记录了元图中的元数据和程序中所有运用到的运算方法的信息
2 . graph_def : 记录了计算图上的节点信息（详细运算，运算的连接结构）
3 . saver_def : 记录了参数（文件名，保存操作等）
4 . collection_def : 维护集合
```

#### model.ckpt

* 该文件用来储存变量信息

#### checkpoint 

* 维护作用
