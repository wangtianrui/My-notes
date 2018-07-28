#### As a whole

* DataSet : ImageNet 

* Architecture :  

  eight learned layers = 5 * convolutional + 3 * fully-connected

  Nice Points :  relu 、LRN 、Overlapping Pooling  、PCA on the set of RGB pixel values 、dropout  

#### Detail Point (new fuctions to make faster and more powerful)

* Relu

$$
f(x) = \max(0,x)
$$

​	<u>advantages</u> : 

​	①make training faster

​	②do not require input normalization to prevent themfrom saturating. （why?）

​	<u>reasons</u> : (参考公式自己总结的，如有错误还望指出)

​	①for example "sigmod" : during beginning and ending , the gradient of sigmod can be very small , on 

​	the 	other hand , our net has a feature - "deep" , so that it's easy to cause to Gradient Diffusion . Come 

​	back to Relu , the	gradient during neuron expressing is equal to origin function's gradient . so it can av-

​	oid Gradient 	Diffusion .

​	②it play the activate role more extreme. 

​	③*（reason for advantage2)* sigmod and tanh , when inputs are too large or too small , the gradient will 

​	become small . so we require input normalization . but relu dont care this , the gradient with relu is the 	

​	same like origin gradient .

* Training on Multiple GPUs 

   puts half of the kernels (or neurons) on each GPU

* Local Reponse Normalization

  a function to normalization . create a competition mechanism . make the large values relatively larger .

  创建竞争机制，使得其中响应比较大的值变得相对更大，并抑制其他较小的神经元。
  $$
  b^i_x,y=\frac{a^i_{x,y}}{(k+\alpha *\sum_{j=max(0,i-n/2)}^{min(N-1,i+n/2)}(a^j_{x,y})^2 )^\beta}
  $$
  通俗理解：通过该公式后，如果一个小值周围分布了很多大值，那么这个小值通过除以一个由很多大值算出的分母后就会变得相对更小。大值除以一个由小值算出的分母后就会变得相对更大。

  ![](https://ws1.sinaimg.cn/large/0067fcixly1ftphdresxcj30n30b7dga.jpg)

* Overlapping Pooling

  * general pooling

    s = z   ( s : step_size   ,   z : pool kernel size )


  * Overlapping Pooling 

    s < z 

  个人理解：通过对stepsize的减小，横向、纵向池化后图像大小变大，换而言之池化所提取出来的特征（经过卷积精化后的特征）更多了。而且stepsize减小降低了大步移动某些特征之间联系的丢失。

#### Combat Overfitting !

* PCA on the set of RGB pixel values 

  add multiples of the found principal components,with magnitudes proportional to the corresponding eigenvalues times a random variable drawn from a Gaussian with mean zero and standard deviation 0.1.

  what is PCA ？？how it work....？

* Dropout

  consists of setting to zero the output of each hidden neuron with probability 0.5. and they do not contribute to the forward pass and do not participate in backpropagation.

  At test time, we use all the neurons but multiply their outputs by 0.5

  个人理解：每个批次训练的时候神经元随机“死亡”，能够随机地干掉 概率值（文中为0.5）比例的特征。让其不参与训练。因为我们训练次数只要得到保证就可以弥补上这个随机丢掉的特征不能参与训练的缺点。相当于就是减少了某些特征参与训练的次数。