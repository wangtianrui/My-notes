综述：<https://blog.csdn.net/zouxy09/article/details/9156785>

梅尔频谱和梅尔倒谱就是使用非常广泛的声音特征形式

短时傅里叶，小波，Wigner分布等都是常用的时频域分析方法。

<https://blog.csdn.net/goodchoes/article/details/47152379>  倒谱的作用

##### db值

在实际日常生活中，住宅小区告知牌上面标示噪音要低于60分贝，也就是要低于60dB，在这里dB（分贝）的定义为噪声源功率与基准声功率比值的对数乘10的数值，不是一个单位，而是一个数值，用来形容声音的大小。

> 10 * log10(S / ref)

#### 声音的形成

声音波由三个阶段组成，第一个阶段是声带发出来基音频率，第二阶段是气体声波经长约17cm的声道，也是共振峰产生的场所，第三阶段是唇口鼻舌，这些部位影响声音的发音，比如元音、辅音等。

声道的shape包括舌头、牙齿等。如果可以准确知道这个形状，就可以对产生的声素进行准确描述.声道的形状在**语音短时功率谱的包络**中显示出来。MFCCs就是一种准确描述这个包络的特征

> 所以MFCCs是描述声道形状的一种特征

#### 声谱图

按帧分割（如分为N帧），对每一帧进行傅里叶变换，得到N个频谱图。然后N个频谱图在时间域上摆放起来就是声谱图。

#### 倒谱分析——用来得到包络

![](https://img-blog.csdn.net/20130623210115156?watermark/2/text/aHR0cDovL2Jsb2cuY3Nkbi5uZXQvem91eHkwOQ==/font/5a6L5L2T/fontsize/400/fill/I0JBQkFCMA==/dissolve/70/gravity/Center)

频谱图的峰值表示语音的主要频率成分。峰值称为共振峰，共振峰就是携带了声音的辨识属性（IDcard）

那么它如此重要。我们就将它提取出来。我们不仅要值，还要它的变化过程。所以得到了**包络**（其实就是连接共振峰点的平滑曲线）

![](https://img-blog.csdn.net/20130623210133203?watermark/2/text/aHR0cDovL2Jsb2cuY3Nkbi5uZXQvem91eHkwOQ==/font/5a6L5L2T/fontsize/400/fill/I0JBQkFCMA==/dissolve/70/gravity/Center)

倒过来理解的话：原始频谱其实是由两个玩意构成：**包络和细节**

#### Mel频率分布

好了。现在拿到一段语音，已经能得到它的包络了。但是研究表明，人的听觉的感知只聚焦在某个特定的区域，而不是整个频谱包络。

      而Mel频率分析就是基于人类听觉感知实验的。实验观测发现人耳就像一个滤波器组一样，它只关注某些特定的频率分量（人的听觉对频率是有选择性的）。也就说，它只让某些频率的信号通过，而压根就直接无视它不想感知的某些频率信号。但是这些滤波器在频率坐标轴上却不是统一分布的，在低频区域有很多的滤波器，他们分布比较密集，但在高频区域，滤波器的数目就变得比较少，分布很稀疏。
梅尔频率倒谱系数（Mel Frequency Cepstrum Coefficient, MFCC）考虑到了人类的听觉特征，先将线性频谱映射到基于听觉感知的Mel非线性频谱中，然后转换到倒谱上。

> mel(f) = 2595 * log10(1+f/700)

![](https://img-blog.csdn.net/20130623210430296?watermark/2/text/aHR0cDovL2Jsb2cuY3Nkbi5uZXQvem91eHkwOQ==/font/5a6L5L2T/fontsize/400/fill/I0JBQkFCMA==/dissolve/70/gravity/Center)

#### Mel频率倒谱系数

我们将频谱通过一组Mel滤波器就得到Mel频谱。公式表述就是：log X[k] = log (Mel-Spectrum)。这时候我们在log X[k]上进行倒谱分析：

1）取对数：log X[k] = log H[k] + log E[k]。

2）进行逆变换：x[k] = h[k] + e[k]。

      在Mel频谱上面获得的倒谱系数h[k]就称为Mel频率倒谱系数，简称MFCC。
#### 总结

1）先对语音进行预加重、分帧和加窗；

2）对每一个短时分析窗，通过FFT得到对应的频谱；

3）将上面的频谱通过Mel滤波器组得到Mel频谱；

4）在Mel频谱上面进行倒谱分析（取对数，做逆变换，实际逆变换一般是通过DCT离散余弦变换来实现，取DCT后的第2个到第13个系数作为MFCC系数），获得Mel频率倒谱系数MFCC，这个MFCC就是这帧语音的特征；

![](https://img-blog.csdn.net/20130623210522390?watermark/2/text/aHR0cDovL2Jsb2cuY3Nkbi5uZXQvem91eHkwOQ==/font/5a6L5L2T/fontsize/400/fill/I0JBQkFCMA==/dissolve/70/gravity/Center)