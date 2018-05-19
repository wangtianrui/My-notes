### YOLO

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