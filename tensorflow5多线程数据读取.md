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
### 队列(对上述方法的补充说明)

```txt
    正如TensorFlow中的其他组件一样，队列就是TensorFlow图中的节点。这是一种有状态的节点，就像变量一样：其他节点可以修改它的内容。具体来说，其他节点可以把新元素插入到队列后端(rear)，也可以把队列前端(front)的元素删除。队列，如FIFOQueue和RandomShuffleQueue(A queue implementation that dequeues elements in a random order.)等对象，在TensorFlow的tensor异步计算时都非常重要。例如，一个典型的输入结构是使用一个RandomShuffleQueue来作为模型训练的输入，多个线程准备训练样本，并且把这些样本压入队列，一个训练线程执行一个训练操作，此操作会从队列中移除最小批次的样本（mini-batches)，这种结构具有许多优点。 
TensorFlow的Session对象是可以支持多线程的，因此多个线程可以很方便地使用同一个会话（Session）并且并行地执行操作。然而，在Python程序实现这样的并行运算却并不容易。所有线程都必须能被同步终止，异常必须能被正确捕获并报告，会话终止的时候， 队列必须能被正确地关闭。所幸TensorFlow提供了两个类来帮助多线程的实现：tf.Coordinator和 tf.QueueRunner。从设计上这两个类必须被一起使用。Coordinator类可以用来同时停止多个工作线程并且向那个在等待所有工作线程终止的程序报告异常。QueueRunner类用来协调多个工作线程同时将多个tensor压入同一个队列中
```
