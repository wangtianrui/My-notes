#### tf.readuce_mean()
* def reduce_mean(input_tensor,
                axis=None,
                keep_dims=False,
                name=None,
                reduction_indices=None):
* reduction_indices:在哪一维上求解。
```python
x = [[[1, 2],
      [3, 4]],
     [[5, 6],
      [7, 8]]]
#将x看为下图的二维图
```

![](https://github.com/wangtianrui/My-notes/blob/master/tensorflow/reduce_mean.png)

```python
y = tf.reduce_mean(x,0)  

'''
在1,5方向进行运算
[[3 4]
 [5 6]]
'''

y = tf.reduce_mean(x,1)
'''
在1，3方向运算
[[2 3]
 [6 7]]
'''

y = tf.reduce_mean(x,2)
'''
在1，2方向进行运算
[[1 3]
 [5 7]]

'''
```
