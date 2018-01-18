## 简单的回调型点击事件

* 连接OnClickListener接口
* 获得view并且设定点击事件的监听者： button.setOnClickListener(this); //通常用this表示当前活动容器
* 将接口中的方法实现 

```java
@Override
    public void onClick(View v) {
        // TODO Auto-generated method stub
        Log.i("用Activity实现OnClickListener接口", "点击事件");
        }
```

## RecyclerView的item点击事件的处理

* class ViewHolder extends  RecyclerView.ViewHolder implements View.OnClickListener 将ViewHolder类连接接口
* 为view设置监听者view.setOnClickListener(this);以及为item设置监听者
```java
@Override
       public void onClick(View v) {
           if (clickListener != null) {
               clickListener.onClick(getAdapterPosition()); //position可以获得当前item的位子

           }
       }
```
* 书写一个接口规范（让后来的监听事件不用挨着写）
```java
public static interface OnItemClickListener {
        void onClick(int position);  //根据position来确定不同的Item
    }
```
* 在adapter最外部的类中把cliListener让外部实现，并用方法暴露出去
```java
private OnItemClickListener clickListener;

    public void setClickListener(OnItemClickListener clickListener) {
        this.clickListener = clickListener;
    }
```
* 在Activity的onCreate中实现
```java
adapter.setClickListener(new CateGoryAdapter.OnItemClickListener() {

            @Override
            public void onClick( int position) {
                Toast.makeText(MainActivity.this,position+"",Toast.LENGTH_SHORT).show();
            }
        });
```
