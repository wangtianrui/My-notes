## 艺术风格迁移

####神经风格迁移是把一张图片的内容和另一个图片的风格合成

##### 原理：

* CNN中每层卷积的结果都是每次提取出来的“特征“，所以包含了丰富的信息，这正是风格迁移的核心之处

![](http://pic1.zhimg.com/v2-caa798d49a3eea420a9e9c641d467f3c_b.jpg)

* 每层卷积所得到的特征偏向也相对不同

  ![](http://pic4.zhimg.com/v2-519d22213b2f159418e4b3ff8100a30b_b.jpg)

  可以看到第一层卷积侧重点在于“轮廓”（大体外形）

  ![](http://pic2.zhimg.com/v2-48dc1c29875693f6058e214bc2dc4511_b.jpg)

  最后一层则是侧重于“纹理”（在轮廓的基础上进行细分）

* 从第一层到最后一层，越来越“细节”

* 所以风格迁移则是将一张图的底层输出（纹理）和另一张图的第一层（轮廓）进行结合，所以涉及到两个网络，

![](http://pic3.zhimg.com/v2-3766e6a5463bc34f35ad7378424bad0a_b.jpg)

​	从比较直观的角度来说。随着层数的增加，图越来越糊。这也就是“具体”的信息越来越少，就像是java中一个具体对象在往类的抽象回退，而cnn所要的“特征”也正好就是这个类！

* 基于上述几点，一般就是使用两个训练好的模型来进行“融合”

* 回顾一下CNN中的分类:

  ![](http://img.blog.csdn.net/20170504200742990?watermark/2/text/aHR0cDovL2Jsb2cuY3Nkbi5uZXQvY3htc2Ni/font/5a6L5L2T/fontsize/400/fill/I0JBQkFCMA==/dissolve/70/gravity/SouthEast)

  ​

  CNN无非是一个降维将图片处理到一个低维面上，每层卷积，通过大量的卷积核（每个卷积核都是大量的方阵神经元组成，所以需要激活函数进行“触发”）进行特征提取（w,b），然后再通过池化对“特征”再进行筛选。

  ![](http://pic4.zhimg.com/v2-103ba3ce28a09e886e45cb89bd87f123_b.jpg)

  ![](http://pic3.zhimg.com/v2-f76f956d22a61e2df469997cac453d2e_b.jpg)

  ![](http://img.blog.csdn.net/20170430134321810?watermark/2/text/aHR0cDovL2Jsb2cuY3Nkbi5uZXQvY3htc2Ni/font/5a6L5L2T/fontsize/400/fill/I0JBQkFCMA==/dissolve/70/gravity/SouthEast)

  然后我们再在这个低维平面上度量不同“类”的空间距离，进行划分

* 回到主题上，风格（这里讨论着色风格）一般是比较抽象的概念，但是如果在卷积上进行展开的话，可以发现不同神经元之间会有一定的关联性，所以我们借助gram矩阵，来测量同一层卷积输出不同通道之间的关联性，组成一个关联性矩阵，从而给出一个对风格的度量。

  ​

  ​                   ![](http://pic3.zhimg.com/v2-e078f82f2cc4dafc9b3fa7854874870a_b.jpg)

  ​

  ![把卷积核摊开，计算关联性](http://pic2.zhimg.com/v2-31c98a0b8c42f43f55ec8860b26ae091_b.jpg)

  ​

* 使用到的loss函数为，gram矩阵之间的距离:

  ![](http://pic2.zhimg.com/v2-99db5066c8b5881be751d44c5b5f404d_b.jpg)

* 衡量风格之间的距离，我们是把不同网络层级间的gram矩阵的距离都计算一下加在一起，这样可以把不同层次度量的东西综合起来。

* 目标函数:

  ![](http://pic1.zhimg.com/v2-87b761410c4e91723f36e0b631d7c508_b.jpg)

  ​	该函数前者为分类网络的“距离”，后者为着色网络的“距离”，所以顺其自然可以想到alpha越大越具象化，beta越高越风格化

* 优化：

   优化的不再是参数，而是图像本身，让图像中的像素点卷积后更接近风格提取出来的特征

