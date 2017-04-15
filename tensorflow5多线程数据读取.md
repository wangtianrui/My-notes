## tensorflow数据读取线程管理QueueRunner

#### Session对象多线程运行

* #### tensorflow提供了两个类：

```txt
tf.Coordinator   
tf.QueueRunner   

这两个类必须被一起使用
```
* tf.Coordinator

```txt
该类可以用来同时停止多个线程，并且进行异常报告,相当于用于信息管理
```

* tf.QueueRunner

```txt
用来协调多个线程同时将多个tensor推入同一个队列中，相当于用来进行数据管理
tf.train.start_queue_runners 该方法会开启输入数据的通道线程
```

* #### 大致理解多线程读取数据原理

```txt
  1.首先，在第一阶段生成文件名，然后读取这些文件名将他们添加到队列中
  2.从文件中读取数据（reader），产生样本，并且把样本放在一个队列中
```
![](http://wiki.jikexueyuan.com/project/tensorflow-zh/images/AnimatedFileQueues.gif)

```txt
入队操作则需要添加tf.train.QueueRunner到一个使用tf.train.add_queue_runner函数的数据流图中，每个QueueRunner
负责一个阶段，一旦数据流图构造成功，tf.train.start_queue_runners函数就会要求数据流图中每个QueueRunner去开始
它的线程运行入队操作。
```
