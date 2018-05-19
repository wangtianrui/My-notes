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

  RCNN一张图像内候选框之间大量重叠，提取特征操作冗余（每个框都提取一次）。

  Fast-Rcnn将整张图归一化后直接送入深度网络。在邻接时，才加入候选框信息，在末尾的少数几层处理每个候选框。

  ②RCNN训练时速度慢

  原理同上

  ③RCNN训练对硬件要求

#### 二、实现：

![](https://img-blog.csdn.net/20160411214438672)

##### 1、特征提取

* 首先是图像预处理：常规操作等（归一、调分布）
* 然后主题特征提取部分和CNN类似，conv+pool

##### 2、候选区

最后一层卷积后加入P个候选区，然后对P个候选区使用roi_pool的操作（差不多2k个左右）

> P个候选区用selective search方法得到
>
> step0：生成区域集R，具体参见论文[《Efficient Graph-Based Image Segmentation》](http://blog.csdn.net/guoyunfei20/article/details/78727972)
>
> step1：计算区域集R里每个相邻区域的相似度S={s1,s2,…} 
> step2：找出相似度最高的两个区域，将其合并为新集，添加进R 
> step3：从S中移除所有与step2中有关的子集 
> step4：计算新集与所有子集的相似度 
> step5：跳至step2，直至S为空
>
> 相识度判定参考了：颜色、纹理、尺寸和空间



> roi_pool层将每个候选区域均分为MxN块，对每块进行max pooling，将特征图上大小不一的候选区转变为大小统一的数据，传入下一层
>
> 特点：输入特征尺寸不定，但是输出尺寸一定
>
> 名词解释：roi：region of interest  特征图上的框
>
> 图解：
>
> ![](https://img-blog.csdn.net/20171112193608750?watermark/2/text/aHR0cDovL2Jsb2cuY3Nkbi5uZXQvQVVUTzE5OTM=/font/5a6L5L2T/fontsize/400/fill/I0JBQkFCMA==/dissolve/70/gravity/Center)
>
> **将其划分为（2\*2）个sections（因为输出大小为2*2），我们可以得到：**
>
> ![](https://img-blog.csdn.net/20171112193628721?watermark/2/text/aHR0cDovL2Jsb2cuY3Nkbi5uZXQvQVVUTzE5OTM=/font/5a6L5L2T/fontsize/400/fill/I0JBQkFCMA==/dissolve/70/gravity/Center)
>
> **将其划分为（2\*2）个sections（因为输出大小为2*2），我们可以得到：**
>
> ![](https://img-blog.csdn.net/20171112193709781?watermark/2/text/aHR0cDovL2Jsb2cuY3Nkbi5uZXQvQVVUTzE5OTM=/font/5a6L5L2T/fontsize/400/fill/I0JBQkFCMA==/dissolve/70/gravity/Center)

##### 3、分类层（FC）

将roi_pool后的p个同size的roi带入到FC层进行分类，这里要注意，最后一层的fc要分为两个，这两个不是前后排布而是并列排布，都接收倒数第二层的fc输出，一个size是n x Num_Class，一个size是n x Num_Class*4的，前者分类，后者回归。