### 浅谈dropout

* dropout对于防止过拟合效果不错，一般用在全连接的部分。
* Dropout是指在模型训练时随机让网络某些隐含层节点的权重不工作，不工作的那些节点可以暂时认为不是网络结构的一部分，但是它的权重得保留下来（只是暂时不更新而已），因为下次样本输入时它可能又得工作了


### 浅谈卷积

#### padding
* padding='VALID'卷积 

```python
conv2d(pool2, Wconv3, strides=[1, 1, 1, 1], padding='VALID')
```

```txt
VALID(可变的),卷积前后的图片的大小要变。
```

* padding='SAME'卷积（边界填充的卷积）

```python
conv2d(pool2, Wconv3, strides=[1, 1, 1, 1], padding='SAME')
```
```txt
SAME（不变的），卷积前后的图片大小不变
填补方法：（左奇右偶个数补零）
比如1 2 3 4 5 6 7 8 9 10 11 12 13 按步长为5，卷积大小为1*6卷积，那么12  13 将会被drop掉，如果利用边界填充的话需要填充3个0，就在1的左边加1个0（奇数个），在13的右边加2个0（偶数个）
```

#### input 

* 输入的图片

#### filter

* 卷积核，是一个Tensor,具有[filter_height, filter_width, in_channels, out_channels]这样的shape，具体含义是[卷积核的高度，卷积核的宽度，图像通道数，卷积核个数]，要求类型与参数input相同,filter的通道数要求与input的in_channels一致，有一个地方需要注意，第三维in_channels，就是参数input的第四维
