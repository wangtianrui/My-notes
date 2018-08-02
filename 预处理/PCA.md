#### PCA 主成分分析

参考：https://my.oschina.net/gujianhan/blog/225241





​	

##### 一、核心：降维

##### 二、PCA详解

* 原始数据

  二维数据：

  x = [2.5, 0.5, 2.2, 1.9, 3.1, 2.3, 2.0, 1.0 ,1.5, 1.1]

  y = [2.4, 0.7, 2.9, 2.2, 3.0, 2.7, 1.6, 1.1, 1.6, 0.9]	

* 计算协方差

  列出一些常见的误差运算：

  * 均值： $\overline{x}=\frac{\sum^n_{i=1}X_i}{n}$
  * 标准差：$s=\sqrt{\frac{\sum^n_{i=1}(X_i-\overline{X})^2}{n}}​$
  * 方差：$s^2=\frac{\sum^n_{i=1}(X_i-\overline{X})^2}{n}$

  不难发现以上的误差都是一维的。

  在衡量二维的数据之间的关系时就应该用协方差
  $$
  cov(X,Y)=\frac{\sum^n_{i=1}(X_i-\overline{X})(Y_i-\overline{Y})}{n-1}
  $$
  不难发现：        $cov(X,X)=s^2$          $cov(X,Y)=cov(Y,X)$

  **但是单个协方差只能处理二维问题**，如果维度多了就需要计算多个协方差。比如n维数据就需要计算$\frac{n(n-1)}{2}$个协方差。那么自然而然就会想到用矩阵来组织这些数据。即有个协方差矩阵的定义：

  假设数据集为{x,y,z}，则协方差矩阵为：
  $$
  C=\left\{\begin{matrix}cov(x,x) &cov(x,y) &cov(x,z)\\ cov(y,x) & cov(y,y) &cov(y,z)\\ cov(z,x) & cov(z,y) & cov(z,z) \end{matrix}\right\}
  $$

  * 对称矩阵、对角线为各维度上的方差



https://mp.weixin.qq.com/s?__biz=MzA5ODUxOTA5Mg==&mid=2652551576&idx=1&sn=17a125bb29001b3d8d5e3964dcc599a3&chksm=8b7e48c3bc09c1d55dbab168011cba2a853af5623a24a499a2ae110a4facb07c2a4bd033da36&mpshare=1&scene=2&srcid=0123V8FT7YEhcDXZco9gT4Vf&from=timeline&key=e4aa053ffd46a2720096fdf7de2840d48e8716d03c5dd165e9247c7dcd05d35f32c5a56481c26829d4d3e5dbef395c4877e96528fe3a518bd34d91906f6403e0d63776163f6d172ca17cfb6ba5ea8ad2&ascene=2&uin=MTgwOTU2NjU0MQ%3D%3D&devicetype=android-24&version=26050430&nettype=WIFI&abtest_cookie=AQABAAgAAQBChh4AAAA%3D&pass_ticket=sNCtedDpTEPBC88xUKXM3tzXl%2F606nFOdOXtXdJOeRZjV7St1JAOwsumIcivZwOd&wx_header=1