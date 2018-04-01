# pbject detection



#### 一、object detection技术的演进：RCNN->SppNET->Fast-RCNN->Faster-RCNN



![](https://images2015.cnblogs.com/blog/1093303/201705/1093303-20170504112530304-2103953078.jpg)

#### 二、CNN已经比较好地解决了识别的问题

#### 那么检测问题我们可以大致转化成什么问题呢？

* #### 回归问题：需要预测出(x,y,w,h)四维坐标，得出方框的位子

![](https://images2015.cnblogs.com/blog/1093303/201705/1093303-20170504112638429-1953242676.png)

​	步骤：

​		步骤1、一个cnn		![](https://images2015.cnblogs.com/blog/1093303/201705/1093303-20170504112659914-1900232742.jpg)

​	步骤2、将cnn尾部展开，加两个“头”（分类头和回归头） 

​	将原本的classification模式改成：classification+regression模式(R-CNN的由来)

​	![](https://images2015.cnblogs.com/blog/1093303/201705/1093303-20170504112723757-880743532.png)

​	步骤3、Regression部分使用欧式距离计算损失，然后结合梯度法进行优化

​	步骤4、预测阶段将2个头拼接上来完成不同的功能

​	那么regression部分应该加在哪儿？

​	加在最后一个卷积层后或者是最后一个FC层后

regression的训练参数收敛的时间要长得多，所以上面的网络采取了用classification的网络来计算出网络共同部分的连接权值。

* #### 取图像窗口

  还是刚才的classification+regression思路

  取不同大小的框

  让框出现在不同位子，得出这个框打判定得分

  取出得分最高的框



![](https://images2015.cnblogs.com/blog/1093303/201705/1093303-20170504112903273-1900432759.jpg)

![](https://images2015.cnblogs.com/blog/1093303/201705/1093303-20170504112919320-1728574836.jpg)

![](https://images2015.cnblogs.com/blog/1093303/201705/1093303-20170504112933164-1200242604.jpg)

![](https://images2015.cnblogs.com/blog/1093303/201705/1093303-20170504112949320-428298146.jpg)

如果有两个框得分相同，就取两个框的交集部分

![](https://images2015.cnblogs.com/blog/1093303/201705/1093303-20170504113014179-105680354.jpg)

但是这个方法太耗时