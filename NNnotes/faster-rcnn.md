## faster-rcnn

参考：https://blog.csdn.net/shenxiaolu1984/article/details/51152614

http://lib.csdn.net/article/deeplearning/61641  （这篇是RPN详解）

是继RCNN[[1](https://blog.csdn.net/shenxiaolu1984/article/details/51152614#fn:1)]，fast RCNN[[2](https://blog.csdn.net/shenxiaolu1984/article/details/51152614#fn:2)]之后，目标检测界的领军人物[Ross Girshick](http://www.cs.berkeley.edu/~rbg/)团队在2015年的又一力作。**简单网络目标检测速度达到17fps**，在PASCAL VOC上准确率为59.9%；复杂网络达到5fps，准确率78.8%。

#### 一、思想

从RCNN到fast rcnn，再到faster rcnn。目标检测的四个基本步骤（候选区域生成，特征提取，分类，位置精修）终于被**统一到一个深度网络框架之内**。所有计算没有重复，完全在GPU中完成，大大提高了运行速度。 

![](https://img-blog.csdn.net/20160414164536029)

faster rcnn主要是用区域生成网络提到fast rcnn中的SS roi选取操作

#### 二、实现

* 整体思路：

![](https://pic1.zhimg.com/80/v2-e64a99b38f411c337f538eb5f093bdf3_hd.jpg)



* 区域生成网络

![](https://pic4.zhimg.com/80/v2-1908feeaba591d28bee3c4a754cca282_hd.jpg)

上图展示了RPN网络的具体结构。可以看到RPN网络实际分为2条线，上面一条通过softmax分类anchors获得foreground和background（检测目标是foreground），下面一条用于计算对于anchors的bounding box regression偏移量，以获得精确的proposal。而最后的Proposal层则负责综合foreground anchors和bounding box regression偏移量获取proposals，同时剔除太小和超出边界的proposals。其实整个网络到了Proposal Layer这里，就完成了相当于目标定位的功能。

##### 首先是原始特征提取（cnn卷积）

![](http://img.blog.csdn.net/20170322103903632)

解释一下图中参数：

```txt
在原文中使用的是ZF model中，其Conv Layers中最后的conv5层num_output=256，对应生成256张特征图，所以相当于feature map每个点都是256-d
由于输入图像M=800，N=600，且Conv Layers做了4次Pooling，feature map的长宽为[M/16, N/16]=[50, 38]
在conv5之后，做了rpn_conv/3x3卷积，num_output=256，相当于每个点使用了周围3x3的空间信息，同时256-d不变，如图3红框，同时对应图4中的红框中的3x3卷积
假设一共有k个anchor，而每个anhcor要分foreground和background，所以cls=2k scores；而每个anchor都有[x, y, w, h]对应4个偏移量，所以reg=4k coordinates
```

##### 然后是候选区：选取候选区的方法：anchors，下图为50 * 38个anchor中心，以及9种示例

> 在整个faster RCNN算法中，有三种尺度。 
> **原图尺度**：原始输入的大小。不受任何限制，不影响性能。 
> **归一化尺度**：输入特征提取网络的大小，在测试时设置，源码中opts.test_scale=600。anchor在这个尺度上设定。这个参数和anchor的相对大小决定了想要检测的目标范围。 
> **网络输入尺度**：输入特征检测网络的大小，在训练时设置，源码中为224*224。

![](https://img-blog.csdn.net/20160419145709355)

> anchors
>
> 所谓anchors，实际上就是一组由rpn/generate_anchors.py生成的矩形。直接运行generate_anchors.py得到以下输出：
>
> ```text
> [[ -84.  -40.   99.   55.]
>  [-176.  -88.  191.  103.]
>  [-360. -184.  375.  199.]
>  [ -56.  -56.   71.   71.]
>  [-120. -120.  135.  135.]
>  [-248. -248.  263.  263.]
>  [ -36.  -80.   51.   95.]
>  [ -80. -168.   95.  183.]
>  [-168. -344.  183.  359.]]
> ```
>
> ![](http://img.blog.csdn.net/20170322103823615)

##### 经过通常卷积后做1x1卷积（加强256层各层之间同位置的像素框的联系）

![](https://pic1.zhimg.com/80/v2-1ab4b6c3dd607a5035b5203c76b078f3_hd.jpg)

可以看到其num_output=18，也就是经过该卷积的输出图像为 ![W\times H \times 18](https://www.zhihu.com/equation?tex=W%5Ctimes+H+%5Ctimes+18) 大小（注意第二章开头提到的卷积计算方式）。这也就刚好对应了feature maps每一个点都有9个anchors，同时每个anchors又有可能是foreground和background，所有这些信息都保存 ![W\times H\times (9\cdot2)](https://www.zhihu.com/equation?tex=W%5Ctimes+H%5Ctimes+%289%5Ccdot2%29) 大小的矩阵。为何这样做？后面接softmax分类获得foreground anchors，也就相当于初步提取了检测目标候选区域box（一般认为目标在foreground anchors中）。那么为何要在softmax前后都接一个reshape layer？其实只是为了便于softmax分类。

##### 于此同时，对proposals进行bounding box regression

![](https://pic4.zhimg.com/80/v2-8241c8076d60156248916fe2f1a5674a_hd.jpg)

可以看到其 ![num\_output=36](https://www.zhihu.com/equation?tex=num%5C_output%3D36) ，即经过该卷积输出图像为 ![W\times H\times 36](https://www.zhihu.com/equation?tex=W%5Ctimes+H%5Ctimes+36) ，这里相当于feature maps每个点都有9个anchors，每个anchors又都有4个用于回归的![[d_{x}(A),d_{y}(A),d_{w}(A),d_{h}(A)]](https://www.zhihu.com/equation?tex=%5Bd_%7Bx%7D%28A%29%2Cd_%7By%7D%28A%29%2Cd_%7Bw%7D%28A%29%2Cd_%7Bh%7D%28A%29%5D)变换量。

##### Proposal

Proposal Layer有3个输入：fg/bg anchors分类器结果rpn_cls_prob_reshape，对应的bbox reg的[dx(A)，dy(A)，dw(A)，dh(A)]变换量rpn_bbox_pred，以及im_info；另外还有参数feat_stride=16，这和图4是对应的。

首先解释im_info。对于一副任意大小PxQ图像，传入Faster RCNN前首先reshape到固定MxN，im_info=[M, N, scale_factor]则保存了此次缩放的所有信息。然后经过Conv Layers，经过4次pooling变为WxH=(M/16)x(N/16)大小，其中feature_stride=16则保存了该信息，用于计算anchor偏移量

#####  RoI pooling

而RoI Pooling层则负责收集proposal，并计算出proposal feature maps，送入后续网络。从图2中可以看到Rol pooling层有2个输入：

1. 原始的feature maps
2. RPN输出的proposal boxes（大小各不相同）