#### xgboost的参数（正则项是什么）

* CART树

  一个CART树需要确定两个部分：1、树的结构 ； 2、各个节点上的分数

* 加法法则

  本质上是一个元算法，适用于所有的加法模型。

  所以XGBOOST的优化目标：$obj(\theta)=\sum l(y_i,y)+\sum L(f_k)$ (每个CART树的误差加上每个树的正则项)

  可以变为多个树的顺序优化，首先优化第一棵，然后优化第二棵，以此类推

  ![](https://upload-images.jianshu.io/upload_images/1371984-cf05dbf32a770823.PNG?imageMogr2/auto-orient/strip%7CimageView2/2/w/432/format/webp)

  然后我令第t步时，我们添加的是一棵最优的CART树$f_t$，这棵最优的CART树是怎么来的呢？非常简单，就是在现有的t-1棵树的基础上，使得目标函数最小的那棵CART树，如下图所示：

  ![](https://upload-images.jianshu.io/upload_images/1371984-b6b91db419fc88d8.PNG?imageMogr2/auto-orient/strip%7CimageView2/2/w/526/format/webp)

