##### 读取

```python
# 这里提一下读取同级其他目录的子文件
father_tree_path = os.path.abspath(os.path.join(os.path.dirname(__file__), ".."))
train_data_file = os.path.join(father_tree_path, "data/train.csv")
predict_data_file = os.path.join(father_tree_path, "data/test.csv")

pd.read_csv(train_data_file)
```

##### Nan值处理

```python
#丢弃Nan值的行！
# "all"：所有为Nan
# "any" :包含Nan
X_train.dropna(axis=0, how="all")
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

