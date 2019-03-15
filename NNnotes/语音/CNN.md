### 首先

<https://blog.csdn.net/joycesunny/article/details/79294239>

声音是一种波，常见的mp3、wmv等格式都是压缩格式，必须转换成非压缩格式的纯波形文件来进行处理，比如windows的wav。wav文件里存储的除了一个文件头外，就是声音波形的一个个点，下图是一个波形的示例

![](http://ss.csdn.net/p?http://mmbiz.qpic.cn/mmbiz/ldSjzkNDxlkb34UeYdd7cBKFgRR4V9ic24VZYXbejBBxvgEEZBqugQzFhcyJMYicvOukRIxnsjxKv8fxKt2fcxMA/640?wx_fmt=png&wxfrom=5&wx_lazy=1)

在开始语音识别之前，有时要把首尾静音给去掉，降低后续步骤的干扰，这个操作成为VAD，需要用到信号处理的一些技术，需要对声音进行分析、分帧，也就是把声音切成一段一段的，每段为一帧。

![](http://ss.csdn.net/p?http://mmbiz.qpic.cn/mmbiz/ldSjzkNDxlkb34UeYdd7cBKFgRR4V9ic2Rap10Qa03Om8JwUkKUgYQDGhd737VzyrZeKfjNteHa2VwUU6vpHYJw/640?wx_fmt=png&wxfrom=5&wx_lazy=1)

分帧后语音就变成了很多小段，但是波形在时域上几乎没有描述能力，因此必须将波形作变换。常用的方式是提取MFCC特征，根据人耳的生理特性，把每一帧波形变成一个多维向量，可以简单地理解为这个向量包含了这帧语音的内容信息。这个过程叫声学特征提取。

至此，声音成了一个12（假设声音特征是12维的）,N列的矩阵。成为观察序列，这里N为总帧数。如图，每一帧都是一个12维向量，色块颜色深浅表示向量值的大小

![](http://ss.csdn.net/p?http://mmbiz.qpic.cn/mmbiz/ldSjzkNDxlkb34UeYdd7cBKFgRR4V9ic2l2n9Ew4ibctjgqFuA1mNtMFLxKbVVY2gmMT3WLCtRsiaQ1VaLtLQtf2w/640?wx_fmt=png)



### 语音识别中的CNN

通常情况下，语音识别都是基于时频分析后的语音谱完成的，而其中语音时频谱是具有结构特点的。

一个卷积神经网络提供在时间和空间上的平移不变性卷积，能克服语音信号本身的多样性。以这种思维来讲，就可以将整个语音信号分析得到的时频谱当作一张图像一样来处理