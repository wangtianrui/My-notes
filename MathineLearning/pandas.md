##### 创建

![](https://i.imgur.com/CHPn7ZF.png)

```python
test = pd.DataFrame([[35,21],[41,34]],columns=["Apples","Bananas"],index=["2017 Sales","2018 Sales"])    //直接创建 ， 除此之外还可以通过构建Series进行创建
```

##### 读取

```python
# 这里提一下读取同级其他目录的子文件
father_tree_path = os.path.abspath(os.path.join(os.path.dirname(__file__), ".."))
train_data_file = os.path.join(father_tree_path, "data/train.csv")
predict_data_file = os.path.join(father_tree_path, "data/test.csv")

pd.read_csv(train_data_file)
```

##### 查看数据的信息与构成

```python
import pandas as pd

reviews = pd.read_csv("../input/wine-reviews/winemag-data-130k-v2.csv", index_col=0)
pd.set_option("display.max_rows", 5)
from learntools.core import binder; binder.bind(globals())
from learntools.pandas.indexing_selecting_and_assigning import *
print("Setup complete.")


reviews.head()   #数据概述
reviews.points.describe()  #对于数值类列，可以直接获取到points这一列的均值、最大最小值等信息
reviews.taster_name.describe() #对于String类列
reviews.points.mean() #获取均值
reviews.taster_name.unique() #查看某列不重复的值有哪些
reviews.taster_name.value_counts() #获取某列变量出现的次数

# 通过map函数进行“循环”操作
review_points_mean = reviews.points.mean()
reviews.points.map(lambda p: p - review_points_mean)

median_points = reviews.points.median()  #获取中位数


bargain_idx = (reviews.points / reviews.price).idxmax()
bargain_wine = reviews.loc[bargain_idx, 'title']  #获得“价格比”最高的葡萄酒


n_trop = reviews.description.map(lambda desc: "tropical" in desc).sum() #计算某列中"tropical”出现的次数
n_fruity = reviews.description.map(lambda desc: "fruity" in desc).sum()
descriptor_counts = pd.Series([n_trop, n_fruity], index=['tropical', 'fruity'])
```

##### 选取某元素

```python
# loc 和 iloc 区别： loc 是多行多列数据   ; iloc 是单个元素

desc = reviews["description"]   ##直接通过列名来进行获取某列所有数据的操作
first_description = reviews.description.iloc[0]   # 获取某列第一个元素的操作
first_row = reviews.iloc[0]    #选取某行
first_descriptions = reviews.description.iloc[:10]  # 获取descriptions中的前10元素

indices = [1, 2, 3, 5, 8]
sample_reviews = reviews.loc[indices]  # 获取多行数据  
# 多行多列获取后都是dataframe数据格式

cols = ['country', 'province', 'region_1', 'region_2']  #选取特定几行几列的数据
indices = [0, 1, 10, 100]
df = reviews.loc[indices, cols]

cols = ['country', 'variety']  # 获取两列中 0-99 行的数据
df = reviews.loc[:99, cols]

cols_idx = [0, 11]
df = reviews.iloc[:100, cols_idx]  # 获取两列中  0-99  行数据。注意与loc的区别

italian_wines = reviews[reviews.country == 'Italy']  #获取到所有某列元素等于某值的行

# 多条件搜索
top_oceania_wines = reviews.loc[
    (reviews.country.isin(['Australia', 'New Zealand']))
    & (reviews.points >= 95)
]  
```

##### Nan值处理

```python
#丢弃Nan值的行！
# "all"：所有为Nan
# "any" :包含Nan
X_train.dropna(axis=0, how="all")
```

##### 广播

```python
review_points_mean = reviews.points.mean()
reviews.points - review_points_mean  #广播运算

reviews.country + " - " + reviews.region_1  #两列直接合并
```

##### 根据某条件（字典）替换dataframe中数据

```python
#得到每列中所有元素（train、test数据集必须合起来！）
#得到每列所有不同元素的值  data["type"].unique(),返回numpylist
unique_list = np.append(X_train[row_name].unique(), X_predit[row_name].unique())
dict = {}
number = 0
for index in unique_list:
    dict[index] = number
    number += 1
X_train[row_name] = X_train[row_name].apply(lambda x: changeNan(dict, x))
X_predit[row_name] = X_predit[row_name].apply(lambda x: changeNan(dict, x))

def changeNan(dict, x):
    return dict[x]

# 使用apply方法来对某一列进行函数操作
def remean_points(row):
    row.points = row.points - review_points_mean
    return row

reviews.apply(remean_points, axis='columns')


# 可以直接根据函数替换信息
def stars(row):
    if row.country == 'Canada':
        return 3
    elif row.points >= 95:
        return 3
    elif row.points >= 85:
        return 2
    else:
        return 1

star_ratings = reviews.apply(stars, axis='columns')
```

##### 均值填充

```python
def fillNanWithMean(df):
    #df.columns为列名数组
    for column in list(df.columns[df.isnull().sum() > 0]):
        #可以直接通过df[列名].mean得到该列均值
        mean_val = df[column].mean()
        df[column].fillna(mean_val, inplace=True)
    return df
```

