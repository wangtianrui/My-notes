### As a whole

* present  residual learning framework : 152 layers—8×deeper than VGG nets but still having lower com-plexity.

### Detail Point

* what is the residual ? 

$$
\eta=y_{label} - y_{pred}
$$

* how and why they present residual learning framework ?
  * they noticed When deeper networks are able to start converging , adegradation problem has been exposed.
  * but this problem is not caused by overfitting . (compare the train_data_set error and test_data_set error)
  * if the added layers can be constructed as identity mappings, a deeper model should have training error no greater than its shallower counterpart.(caused by Identity mapping can not find the best mapping)
  * so they add residual to change the mapping !
* residual function

$$
F(x) = H(x)-x
$$

* residual mapping function 

$$
y = f(x,\omega)+x \\st.f(x,\omega).shape =x.shape
$$

* we can perform a linear projection Ws by the shortcut connections to match the dimensions

$$
y = f(x,\omega_i)+\omega_{j} x \\st.f(x,\omega_i).shape \neq x.shape
$$

* net framework 

  * Plain Network

    inspired by the pholosophy of VGG nets. （都是较深的网络）

    ①so the conv size is 3x3

    ②for the same output feature map size,the layers have the same number of filters (只要图像size不变卷积核数就不变)

    ③if the feature map size is halved , the number of filters is doubled ! (图像size减半，卷积核数增倍)

    ④ conv have a stride of 2 .

    ⑤average pooling and 1000-fc with softmax (the end)

* Deeper Botteleneck Architectures

  For each residual function F, we use a stack of 3 layers instead of 2.

  The three layers are : 1x1 ,  3x3  ,  1x1  conv .

  前一个1x1是负责减小维度（通过filter的数量），后一个1x1是负责增大维度（把减小的给增回来）。个人理解这里的1x1还能增加一个上一个输出的各层之间的关系。

  这个方法的优点：论文上只说了加快训练时间。个人觉得还能减少参数的数量

### Advatages

* 解决了深度网络的“退化”问题。


* 使用残差函数作为优化目标不会增加复杂度。（个人理解：使用残差函数作为优化目标后的mapping函数为$y=f(x,\omega)+x$，这里只是在原基础上加了一个X的映射，但是我们求梯度的时候是对$\omega$求导，所以加上的项是只对输出的结果有意义。对我们的优化却不影响）
* 既然深度网络的退化问题解决了，那么也肯定有所提升。
* 比VGG的复杂度低，效果也比VGG好。
  * vgg19:2$\times$conv3-64+2$\times$conv3-128+4$\times$conv3-256+4$\times$conv3-512 + maxpool + 2$\times$fc-4096 + fc-1000 
  * ResNet34: conv7-64+max-pool3+3$\times$conv3-64+4$\times$conv3-128+6$\times$conv3-256+3$\times$conv3-512 +aver-agepool + fc-1000



