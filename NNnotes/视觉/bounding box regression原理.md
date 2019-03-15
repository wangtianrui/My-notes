## bounding box regression

![](https://pic3.zhimg.com/80/v2-93021a3c03d66456150efa1da95416d3_hd.jpg)

对于窗口一般使用四维向量 ![(x, y, w, h)](https://www.zhihu.com/equation?tex=%28x%2C+y%2C+w%2C+h%29) 表示，分别表示窗口的中心点坐标和宽高。对于图 10，红色的框A代表原始的Foreground Anchors，绿色的框G代表目标的GT，我们的目标是寻找一种关系，使得输入原始的anchor A经过映射得到一个跟真实窗口G更接近的回归窗口G'，即：

- 给定：anchor ![A=(A_{x}, A_{y}, A_{w}, A_{h})](https://www.zhihu.com/equation?tex=A%3D%28A_%7Bx%7D%2C+A_%7By%7D%2C+A_%7Bw%7D%2C+A_%7Bh%7D%29) 和 ![GT=[G_{x}, G_{y}, G_{w}, G_{h}]](https://www.zhihu.com/equation?tex=GT%3D%5BG_%7Bx%7D%2C+G_%7By%7D%2C+G_%7Bw%7D%2C+G_%7Bh%7D%5D)
- 寻找一种变换**F，**使得：![F(A_{x}, A_{y}, A_{w}, A_{h})=(G_{x}^{'}, G_{y}^{'}, G_{w}^{'}, G_{h}^{'})](https://www.zhihu.com/equation?tex=F%28A_%7Bx%7D%2C+A_%7By%7D%2C+A_%7Bw%7D%2C+A_%7Bh%7D%29%3D%28G_%7Bx%7D%5E%7B%27%7D%2C+G_%7By%7D%5E%7B%27%7D%2C+G_%7Bw%7D%5E%7B%27%7D%2C+G_%7Bh%7D%5E%7B%27%7D%29)，其中![(G_{x}^{'}, G_{y}^{'}, G_{w}^{'}, G_{h}^{'})≈(G_{x}, G_{y}, G_{w}, G_{h})](https://www.zhihu.com/equation?tex=%28G_%7Bx%7D%5E%7B%27%7D%2C+G_%7By%7D%5E%7B%27%7D%2C+G_%7Bw%7D%5E%7B%27%7D%2C+G_%7Bh%7D%5E%7B%27%7D%29%E2%89%88%28G_%7Bx%7D%2C+G_%7By%7D%2C+G_%7Bw%7D%2C+G_%7Bh%7D%29)

![img](https://pic1.zhimg.com/80/v2-ea7e6e48662bfa68ec73bdf32f36bb85_hd.jpg)

那么经过何种变换**F**才能从图10中的anchor A变为G'呢？ 比较简单的思路就是:

- 先做平移

![img](https://pic1.zhimg.com/80/v2-a9380736b49a548736b35d182ffd44ab_hd.jpg)

- 再做缩放

![img](https://pic1.zhimg.com/80/v2-c4d9c89c3fb1baa90631f662f906626f_hd.jpg)

观察上面4个公式发现，需要学习的是 ![d_{x}(A),d_{y}(A),d_{w}(A),d_{h}(A)](https://www.zhihu.com/equation?tex=d_%7Bx%7D%28A%29%2Cd_%7By%7D%28A%29%2Cd_%7Bw%7D%28A%29%2Cd_%7Bh%7D%28A%29) 这四个变换。当输入的anchor A与GT相差较小时，可以认为这种变换是一种线性变换， 那么就可以用线性回归来建模对窗口进行微调（注意，只有当anchors A和GT比较接近时，才能使用线性回归模型，否则就是复杂的非线性问题了）。
接下来的问题就是如何通过线性回归获得 ![d_{x}(A),d_{y}(A),d_{w}(A),d_{h}(A)](https://www.zhihu.com/equation?tex=d_%7Bx%7D%28A%29%2Cd_%7By%7D%28A%29%2Cd_%7Bw%7D%28A%29%2Cd_%7Bh%7D%28A%29) 了。线性回归就是给定输入的特征向量X, 学习一组参数W, 使得经过线性回归后的值跟真实值Y非常接近，即![Y=WX](https://www.zhihu.com/equation?tex=Y%3DWX)。对于该问题，输入X是一张经过卷积获得的feature map，定义为Φ；同时还有训练传入的GT，即![(t_{x}, t_{y}, t_{w}, t_{h})](https://www.zhihu.com/equation?tex=%28t_%7Bx%7D%2C+t_%7By%7D%2C+t_%7Bw%7D%2C+t_%7Bh%7D%29)。输出是![d_{x}(A),d_{y}(A),d_{w}(A),d_{h}(A)](https://www.zhihu.com/equation?tex=d_%7Bx%7D%28A%29%2Cd_%7By%7D%28A%29%2Cd_%7Bw%7D%28A%29%2Cd_%7Bh%7D%28A%29)四个变换。那么目标函数可以表示为：

![img](https://pic4.zhimg.com/80/v2-0dad3f869b9c1760c7188efd0b6f81f1_hd.jpg)

其中Φ(A)是对应anchor的feature map组成的特征向量，w是需要学习的参数，d(A)是得到的预测值（*表示 x，y，w，h，也就是每一个变换对应一个上述目标函数）。为了让预测值![(t_{x}, t_{y}, t_{w}, t_{h})](https://www.zhihu.com/equation?tex=%28t_%7Bx%7D%2C+t_%7By%7D%2C+t_%7Bw%7D%2C+t_%7Bh%7D%29)与真实值差距最小，设计损失函数：

![img](https://pic4.zhimg.com/80/v2-c898fc9738b82afa2729a5a5f61ac893_hd.jpg)

函数优化目标为：

![img](https://pic1.zhimg.com/80/v2-1e67089e47548f8a383a221f184dea04_hd.jpg)

需要说明，只有在GT与需要回归框位置比较接近时，才可近似认为上述线性变换成立。
说完原理，对应于Faster RCNN原文，foreground anchor与ground truth之间的平移量 ![(t_x, t_y)](https://www.zhihu.com/equation?tex=%28t_x%2C+t_y%29) 与尺度因子 ![(t_w, t_h)](https://www.zhihu.com/equation?tex=%28t_w%2C+t_h%29) 如下：

![img](https://pic4.zhimg.com/80/v2-18fdc24fc392a80e456b77b9a7f69c71_hd.jpg)

对于训练bouding box regression网络回归分支，输入是cnn feature Φ，监督信号是Anchor与GT的差距 ![(t_x, t_y, t_w, t_h)](https://www.zhihu.com/equation?tex=%28t_x%2C+t_y%2C+t_w%2C+t_h%29)，即训练目标是：输入 Φ的情况下使网络输出与监督信号尽可能接近。
那么当bouding box regression工作时，再输入Φ时，回归网络分支的输出就是每个Anchor的平移量和变换尺度 ![(t_x, t_y, t_w, t_h)](https://www.zhihu.com/equation?tex=%28t_x%2C+t_y%2C+t_w%2C+t_h%29)，显然即可用来修正Anchor位置了。