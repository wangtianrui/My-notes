### YOLO

### v1

YOLO将物体检测作为一个回归问题进行求解，输入图像经过一次inference，便能得到图像中所有物体的位置和其所属类别及相应的置信概率。而rcnn/fast rcnn/faster rcnn将检测结果分为两部分求解：物体类别（分类问题），物体位置即bounding box（回归问题）。

#### 一、思路

![](https://img-blog.csdn.net/20170420213841466?watermark/2/text/aHR0cDovL2Jsb2cuY3Nkbi5uZXQvaHJzc3R1ZHk=/font/5a6L5L2T/fontsize/400/fill/I0JBQkFCMA==/dissolve/70/gravity/SouthEast)

YOLO将输入图像划分为SxS的栈格，每个栅格负责检测中心落在该栅格的物体。每个栅格预测B个bounding boxes，及其scores（confidence）

![](https://img-blog.csdn.net/20170420213914966?watermark/2/text/aHR0cDovL2Jsb2cuY3Nkbi5uZXQvaHJzc3R1ZHk=/font/5a6L5L2T/fontsize/400/fill/I0JBQkFCMA==/dissolve/70/gravity/SouthEast)

如果这个栅格中不存在一个 object，则confidence score应该为0；否则的话，confidence score则为 predicted bounding box与 ground truth box之间的 IOU（intersection over union）。

![](https://img-blog.csdn.net/20171214103709855?watermark/2/text/aHR0cDovL2Jsb2cuY3Nkbi5uZXQvSUFNb2xkcGFu/font/5a6L5L2T/fontsize/400/fill/I0JBQkFCMA==/dissolve/70/gravity/SouthEast)

YOLO对每个bounding box有5个predictions：x, y, w, h,  confidence。 
坐标x,y代表了预测的bounding box的中心与栅格边界的相对值。 
坐标w,h代表了预测的bounding box的width、height相对于整幅图像width,height的比例。 
confidence就是预测的bounding box和ground truth box的IOU值。

![](https://img-blog.csdn.net/20170420213936232?watermark/2/text/aHR0cDovL2Jsb2cuY3Nkbi5uZXQvaHJzc3R1ZHk=/font/5a6L5L2T/fontsize/400/fill/I0JBQkFCMA==/dissolve/70/gravity/SouthEast)

每一个栅格还要预测C个 conditional class probability（条件类别概率）：Pr(Classi|Object)。即在一个栅格包含一个Object的前提下，它属于某个类的概率。 
我们只为每个栅格预测一组（C个）类概率，而不考虑框B的数量。

![](https://img-blog.csdn.net/20170420214125579?watermark/2/text/aHR0cDovL2Jsb2cuY3Nkbi5uZXQvaHJzc3R1ZHk=/font/5a6L5L2T/fontsize/400/fill/I0JBQkFCMA==/dissolve/70/gravity/SouthEast)

将YOLO用于PASCAL VOC数据集时： 
论文使用的 S=7，即将一张图像分为7×7=49个栅格每一个栅格预测B=2个boxes（每个box有 x,y,w,h,confidence，5个预测值），同时C=20（PASCAL数据集中有20个类别）。 
因此，最后的prediction是7×7×30 { 即S * S * ( B * 5 + C) }的Tensor。

![](https://img-blog.csdn.net/20170420214145482?watermark/2/text/aHR0cDovL2Jsb2cuY3Nkbi5uZXQvaHJzc3R1ZHk=/font/5a6L5L2T/fontsize/400/fill/I0JBQkFCMA==/dissolve/70/gravity/SouthEast)

#### 二、实现

![](https://img-blog.csdn.net/20170420214206923?watermark/2/text/aHR0cDovL2Jsb2cuY3Nkbi5uZXQvaHJzc3R1ZHk=/font/5a6L5L2T/fontsize/400/fill/I0JBQkFCMA==/dissolve/70/gravity/SouthEast)

![](https://pic1.zhimg.com/80/v2-2c4e8576b987236de47f91ad594bf36d_hd.jpg)

24卷积层和2全连接层。

其中卷积层用来提取图像特征，全连接用来预测图像位置和类别概率值

参考：https://blog.csdn.net/hrsstudy/article/details/70305791



### v2

##### 在v1的基础上，增删了很多操作。将mAP值增加到了78.6

![](https://img-blog.csdn.net/20161229151800828?watermark/2/text/aHR0cDovL2Jsb2cuY3Nkbi5uZXQvSmVzc2VfTXg=/font/5a6L5L2T/fontsize/400/fill/I0JBQkFCMA==/dissolve/70/gravity/SouthEast)

* 加入BN

CNN在训练过程中网络每层输入的分布一直在改变, 会使训练过程难度加大，但可以通过normalize每层的输入解决这个问题。新的YOLO网络在每一个卷积层后添加batch normalization，通过这一方法，mAP获得了2%的提升。batch normalization 也有助于规范化模型，可以在舍弃dropout优化后依然不会过拟合。

* high resolotion classifier

目前的目标检测方法中，基本上都会使用ImageNet预训练过的模型（classifier）来提取特征，如果用的是AlexNet网络，那么输入图片会被resize到不足256 * 256，导致分辨率不够高，给检测带来困难。为此，新的YOLO网络把分辨率直接提升到了448 * 448，这也意味之原有的网络模型必须进行某种调整以适应新的分辨率输入。

对于YOLOv2，作者首先对分类网络（自定义的darknet）进行了fine tune，分辨率改成448 * 448，在ImageNet数据集上训练10轮（10 epochs），训练后的网络就可以适应高分辨率的输入了。然后，作者对检测网络部分（也就是后半部分）也进行fine tune。这样通过提升输入的分辨率，mAP获得了4%的提升。

* Convolutional with anchor boxes

之前的YOLO利用全连接层的数据完成边框的预测，导致丢失较多的空间信息，定位不准。作者在这一版本中借鉴了Faster R-CNN中的anchor思想，回顾一下，anchor是RNP网络中的一个关键步骤，说的是在卷积特征图上进行滑窗操作，每一个中心可以预测9种不同大小的建议框。看到YOLOv2的这一借鉴，我只能说SSD的作者是有先见之明的。

为了引入anchor boxes来预测bounding boxes，作者在网络中果断去掉了全连接层。剩下的具体怎么操作呢？首先，作者去掉了后面的一个池化层以确保输出的卷积特征图有更高的分辨率。然后，通过缩减网络，让图片输入分辨率为416 * 416，这一步的目的是为了让后面产生的卷积特征图宽高都为奇数，这样就可以产生一个center cell。作者观察到，大物体通常占据了图像的中间位置， 就可以只用中心的一个cell来预测这些物体的位置，否则就要用中间的4个cell来进行预测，这个技巧可稍稍提升效率。最后，YOLOv2使用了卷积层降采样（factor为32），使得输入卷积网络的416 * 416图片最终得到13 * 13的卷积特征图（416/32=13）。

数量上去了理所当然recall上升precision下降，但是作者的例子中recall上升了7，precision只下降了0.3（牛逼）

* Dimension Clusters

作者在使用anchor的时候遇到了两个问题，**第一个是anchor boxes的宽高维度往往是精选的先验框（hand-picked priors）**，虽说在训练过程中网络也会学习调整boxes的宽高维度，最终得到准确的bounding boxes。但是，如果一开始就选择了更好的、更有代表性的先验boxes维度，那么网络就更容易学到准确的预测位置。

和以前的精选boxes维度不同，作者使用了K-means聚类方法类训练bounding boxes，可以自动找到更好的boxes宽高维度。传统的K-means聚类方法使用的是欧氏距离函数，也就意味着较大的boxes会比较小的boxes产生更多的error，聚类结果可能会偏离。为此，作者采用的评判标准是IOU得分（也就是boxes之间的交集除以并集），这样的话，error就和box的尺度无关了，最终的距离函数为：

![](https://img-blog.csdn.net/20161229113026773?watermark/2/text/aHR0cDovL2Jsb2cuY3Nkbi5uZXQvSmVzc2VfTXg=/font/5a6L5L2T/fontsize/400/fill/I0JBQkFCMA==/dissolve/70/gravity/SouthEast)

![](https://img-blog.csdn.net/20161229113104156?watermark/2/text/aHR0cDovL2Jsb2cuY3Nkbi5uZXQvSmVzc2VfTXg=/font/5a6L5L2T/fontsize/400/fill/I0JBQkFCMA==/dissolve/70/gravity/SouthEast)

可以看到，平衡复杂度和IOU之后，最终得到k值为5，意味着作者选择了5种大小的box维度来进行定位预测，这与手动精选的box维度不同。结果中扁长的框较少，而瘦高的框更多（这符合行人的特征），这种结论如不通过聚类实验恐怕是发现不了的。