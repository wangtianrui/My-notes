### DataFrame的结合妙用

```python
# 直接能画出dataframe中某一列中多个数据对应的label数值图像
# 点图
sns.lmplot(x='Value', y='Overall', hue='Position', 
           data=footballers.loc[footballers['Position'].isin(['ST', 'RW', 'LW'])],fit_reg=False)

#也可以修改图形形状
sns.lmplot(x='Value', y='Overall', markers=['o', 'x', '*'], hue='Position',data=footballers.loc[footballers['Position'].isin(['ST', 'RW', 'LW'])],fit_reg=False)


# boxplot
f = (footballers
         .loc[footballers['Position'].isin(['ST', 'GK'])]
         .loc[:, ['Value', 'Overall', 'Aggression', 'Position']]
    )
f = f[f["Overall"] >= 80]
f = f[f["Overall"] < 85]
f['Aggression'] = f['Aggression'].astype(float)

sns.boxplot(x="Overall", y="Aggression", hue='Position', data=f)



#画出每对数据之间的相关性
f = (
    footballers.loc[:, ['Acceleration', 'Aggression', 'Agility', 'Balance', 'Ball control']]
        .applymap(lambda v: int(v) if str.isdecimal(v) else np.nan)
        .dropna()
).corr()

sns.heatmap(f, annot=True)
```

