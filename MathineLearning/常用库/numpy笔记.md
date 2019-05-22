##### 广播减法

```python
test_array = np.array([[1,2,3],
                       [5,6,7],
                       [9,10,11]])

y_test_array = np.array([10,20,30])
print(test_array-y_test_array)

"""
[[ -9 -18 -27]
 [ -5 -14 -23]
 [ -1 -10 -19]]
"""
test_array = np.array([[1,2,3],
                       [5,6,7],
                       [9,10,11]])
y_test_array = np.array([[10],[20],[30]])
print(test_array-y_test_array)

"""
[[ -9  -8  -7]
 [-15 -14 -13]
 [-21 -20 -19]]
"""

```

##### 广播除法

```python
test_array = np.array([[1,2,3],
                       [5,6,7],
                       [9,10,11]])
y_test_array = np.array([1,2,0])
print(test_array/y_test_array)

"""
[[1 1 0]
 [5 3 0]
 [9 5 0]]
"""

test_array = np.array([[1,2,3],
                       [5,6,7],
                       [9,10,11]])
y_test_array = np.array([[1],[2],[0]])
print(test_array/y_test_array)

"""
[[1 2 3]
 [2 3 3]
 [0 0 0]]
"""
```

##### 广播比较

```python
test_array = np.array([[10,20,30],
                       [5,20,7],
                       [30,10,11]])

y_test_array = np.array([10,20,30])
print(test_array==y_test_array)

"""
[[ True  True  True]
 [False  True False]
 [False False False]]
"""

test_array = np.array([[10,20,30],
                       [5,20,7],
                       [30,10,11]])

y_test_array = np.array([[10],[20],[30]])
print(test_array==y_test_array)
"""
[[ True False False]
 [False  True False]
 [ True False False]]
"""
```



#####数组索引

```python
test_array = np.array([[1,2,3],
                       [5,6,7],
                       [9,10,11]])
y_test_array = np.array([1,2,0])
print(test_array[y_test_array])

"""
[[ 5  6  7]
 [ 9 10 11]
 [ 1  2  3]]
"""


test_array = np.array([[1,2,3],
                       [5,6,7],
                       [9,10,11]])
y_test_array = np.array([1,2,0])
print(test_array[:,y_test_array])

"""
[[ 2  3  1]
 [ 6  7  5]
 [10 11  9]]
"""


test_array = np.array([[1,2,3],      #最关键的！
                       [5,6,7],
                       [9,10,11]])
y_test_array = np.array([1,2,0])
print(test_array[range(3),y_test_array])

"""
[2 7 9]
"""
```

##### 参数初始化

*  参数初始化不能太大！也不宜太小。不然会出现NAN和inf现象，后者可能导致基本不训练

```python
np.random.normal(size,loc,scale)
"""
loc：float
    此概率分布的均值（对应着整个分布的中心centre）
scale：float
    此概率分布的标准差（对应于分布的宽度，scale越大越矮胖，scale越小，越瘦高）
size：int or tuple of ints
    输出的shape，默认为None，只输出一个值
"""
test_array = np.random.normal(size=[100],scale=1e-5)
plt.figure(figsize=(10,10))
plt.plot(range(100),test_array)
test_array = np.random.normal(size=[100],scale=1e-3)
plt.plot(range(100),test_array)
test_array = np.random.normal(size=[100],scale=5e-2)
plt.plot(range(100),test_array)
```

![](https://ws1.sinaimg.cn/large/0067fcixly1ftxzm1c0mij30h10g2abq.jpg)

##### 复制扩充数组

```python
a=np.array([10,20]) 
new_array = np.tile(a,(3,2))  # 3x2的形式扩充
print(new_array)

"""
[[10 20 10 20]
 [10 20 10 20]
 [10 20 10 20]]
"""
```

