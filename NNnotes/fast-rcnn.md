# FAST-RCNN

参考：https://zhuanlan.zhihu.com/p/24780395

### 继RCNN之后，Ross Girshick推出Fast RCNN，大幅提升了目标检测的速度，大神源码：https://github.com/rbgirshick/fast-rcnn

> 同样使用最大规模的网络，Fast RCNN和RCNN相比，训练时间从84小时减少为9.5小时，**测试时间从47秒减少为0.32秒**。在PASCAL VOC 2007上的准确率相差无几，约在66%-67%之间.

#### 一、思想

* RCNN

  https://github.com/wangtianrui/My-notes/blob/master/NNnotes/R-CNN.md

* 改进：

  Fast RCNN解决了RCNN方法三个问题：

  ①测试时速度慢：

  RCNN一张图像内候选框指尖大量重叠，提取特征操作冗余。

  Fast-Rcnn将整张图归一化后直接送入深度网络。在邻接时，才加入候选框信息，在末尾的少数几层处理每个候选框。

  ②训练时速度慢

  ​