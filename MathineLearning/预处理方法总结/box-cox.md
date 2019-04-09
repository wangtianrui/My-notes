#### box-cox

<https://www.cnblogs.com/king-lps/p/7843395.html>

> 使数据正态分布的一种操作，可以使模型满足线性、独立性、齐方差性以及正态性

* 使用情形：

  对于连续的响应变量不满足正态分布的情况，在做线性回归的过程中，不可观测的误差可能是和预测变量相关，以至于给模型训练带来误差——方差齐性问题

  ```python
  y = ((1+x)**lmbda - 1) / lmbda  if lmbda != 0
      log(1+x)                    if lmbda == 0
  ```

![](http://onlinestatbook.com/2/transformations/graphics/box-cox1.jpg)

![](http://onlinestatbook.com/2/transformations/graphics/box-cox2.jpg)

![](http://onlinestatbook.com/2/transformations/graphics/box-cox_fig1.jpg)

![](http://onlinestatbook.com/2/transformations/graphics/box-cox_fig2.jpg)