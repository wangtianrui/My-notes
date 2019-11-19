### flex

### 简介

flex是弹性布局，用来为盒状模型提供支持，任何一个容器都可以指定位Flex布局

* 他是用来修改子布局排布的：①可以将块级改为行内



```css
.box{
    display:flex;
}
//行内元素
.box{
    display:inline-flex;
}
```

块级元素：一行一个

行内元素：一行n个 

```css
display:inline-block;   //这个是设置给子元素的。如果设置了flex就不用设了
```

* 排列方向

```css
.box{
    flex-direction:row | row-reverse | column | column-reverse ;
}
```

* 项目换行

```css
.box{
    flex-wrap: wrap
}
//默认：nowrap | wrap | wrap-reverse
nowrap:不换行
wrap:换行，保留原始大小
```

* flex-flow

```css
//direction与wrap的综合体
//默认row nowrap 其他和前面的一样的
```

* 内容水平对齐

```css
//flex-star   flex-end  center space-around space-between
justify-content:flex-end
```

* 垂直对齐

```css
// flex-star flex-end center stretch baseline 
align-items:
```

* 设置各个行的对齐方式（多行子控件的情况下）

```css
//flex-star   flex-end  center space-around space-between
align-content
```

