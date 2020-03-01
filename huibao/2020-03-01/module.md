# 2020-03-01 汇报

> 本汇报分为三个大点
>
> 1、已做的事儿
>
> 2、打算做什么
>
> 3、想问的问题

## 本周已做的事儿

* ###  根据老师的意见完成了 音高提取 、 音素分割  、 Fbank特征提取

  * ### 音高提取（分别采用两种方法对音高进行了提取：自相关法和傅里叶变换法）

    * 傅里叶变换法
      * 参考numpy源码回顾了傅里叶变换过程原理
      * 下面左图为傅里叶变换法的结果
    * 自相关法
      * 在测试音频上，frame长度和傅里叶取得一样，20ms为一帧进行分析
      * 下面右图为自相关法的结果

    ![](http://39.96.162.42/get_audio_src?filename=pitch.png)

    从结果来看，两种方法的结果不同，但是变化趋势等大致一致。从原理来讲，傅里叶变换得到的结果我感觉更合理一点

  * ### Fbank特征提取

    * 查阅了Fbank特征的原理以及实现过程。
    * 代码实现结果如下

    ![](http://39.96.162.42/get_audio_src?filename=audio.png)
    ![](http://39.96.162.42/get_audio_src?filename=fbank.png)

  * ### 音素分割

    * 利用腾讯智聆API对我收集的音频文件进行了因素的标注，如下图所示

    ![](http://39.96.162.42/get_audio_src?filename=phoneme.png)

    * 实现思路是参考文献  2018 arXiv: 《Singing voice phoneme segmentation by hierarchically inferring syllable and phoneme onset positions 》。

      原文献中对于每个音素的检测是分为：检测开头和预测持续时间  两个任务来完成。

      因为我们的目的是通过音素的检测来计算语速，所以我们只需要计算出每个音素的持续时间，我这里用的是他的方法一来实现，也就是说对每帧数据进行判断，判断它是否是音素。然后通过计算每一段音素的“厚度”来进行语速的预测（目前我能实现的思路）

      对于每一帧的长度，我是参考的文献：2017 arxiv：《Gate activation signal analysis for gated recurrent neural networks and its correlation with phoneme boundaries》

      20ms为一帧

    * 特征我采用的是fbank，分类器采用的是两层全链接。目前准确率在87%左右。划分效果如下（示意图是在时域范围展示）

![](http://39.96.162.42/get_audio_src?filename=phome%20seg.png)

​			后续的计算语速的步骤还在着手实现中（目前还是先追求能用，再来优化）

## 下周计划

- 语速计算过程，并且融入判断网络
- 确定音高提取算法，提取所有数据集的音高特征
- 音高的变化率，变化范围等特征提取
- 针对描述的词禁不住推敲的问题进行改进
- （不一定全部能完成。。尽力根据优先度逐个来）

## 想问的问题

- 音素分割有没有更好的方法，我感觉现在这个还远远不够
- 音高的提取方法有很多种，他们的优劣是什么