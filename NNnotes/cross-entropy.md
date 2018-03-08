### 交叉熵产生于信息论里面的信息压缩编码技术，但是它后来演变成为从博弈论到机器学习等其他领域里的重要技术手段。它的定义如下：

![](https://pic4.zhimg.com/80/v2-8cd1c428c096608e38c46dc0b5433798_hd.jpg)

​							其中，y 是我们预测的概率分布, y’ 是实际的分布

​		特点：1.交叉熵是正的，2.当所有输入x的输出都能接近期望输出y的话，交叉熵的值将会接近 0。

​		优点：

​		对比于二次代价函数：以下为二次代价函数参数更新的公式:

​		                				![](https://pic1.zhimg.com/80/v2-527975d183e4d89e4b918086e4d9b75d_hd.jpg)

![](https://pic1.zhimg.com/80/v2-4d7a9b7d68a8893ddc6d0d75ba082fe9_hd.jpg)

​		a 是 神经元的输出，其中 a = σ(z)， z = wx + b，一般激活函数在末和头的导数都特别小，如：     

​       sigmoid，所以如果用二元代价函数来做代价函数的话，会出现开头和末尾训练速度特别慢的情况

​	 					![](https://pic3.zhimg.com/80/v2-e380672ebecf809c6edc79a9f692804b_hd.jpg)

​		

​		对于cross-entropy来说:

​		![](https://pic4.zhimg.com/80/v2-c5cfad423e9cdf6e3348411b8cebad34_hd.jpg)

​		偏导后：

![](https://pic2.zhimg.com/80/v2-8418217157122a69cb3f752ea1af4bb4_hd.jpg)

​		可以发现。偏导结果是与“距离值”有关的，所以会比二次代价函数好