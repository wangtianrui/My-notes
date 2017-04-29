## dataBinding

* 在app的build里声明
```android
dataBinding {
      enabled = true
  }
```

* 创建一个类用来操作

```android
//新建一个类
public class User extends BaseObservable {   
  //继承观察者类

    private String userName;
    private String passWords;

    //alt + ins    getter  和  setter


    @Bindable  // 加观察者
    public void setUserName(String userName) {
        this.userName = userName;
        notifyPropertyChanged(BR.userName);   //双向绑定，否则不会改
    }

    @Bindable
    public void setPassWords(String passWords) {
        this.passWords = passWords;
    }

    @Bindable
    public String getUserName() {

        return userName;
    }

    @Bindable      
    public String getPassWords() {
        return passWords;
    }
}
```

* 修改布局文件中的代码

```android
<?xml version="1.0" encoding="utf-8"?>
<layout xmlns:android="http://schemas.android.com/apk/res/android">
<data>
    <import type="android.view.View"/>   //用来修改属性
    <variable
        name="user"
        type="com.example.mvvmtest.User"/>
</data>

    <LinearLayout xmlns:android="http://schemas.android.com/apk/res/android"
        xmlns:tools="http://schemas.android.com/tools"
        android:id="@+id/activity_main"
        android:layout_width="match_parent"
        android:layout_height="match_parent"
        android:orientation="vertical"
        android:paddingBottom="@dimen/activity_vertical_margin"
        android:paddingLeft="@dimen/activity_horizontal_margin"
        android:paddingRight="@dimen/activity_horizontal_margin"
        android:paddingTop="@dimen/activity_vertical_margin"
        tools:context="com.example.mvvmtest.MainActivity">

        <TextView
            android:layout_margin="16dp"
            android:layout_width="match_parent"
            android:layout_height="wrap_content"
            android:text="@={user.userName}"     //加了等号才能双向绑定
            android:textSize="30sp"
            android:background="#09f7eb"/>

        <TextView
            android:layout_margin="16dp"
            android:layout_width="match_parent"
            android:layout_height="wrap_content"
            android:textSize="30sp"
            android:background="#f4ecad"
            android:text="@{user.passWords}"/>
        
    </LinearLayout>
</layout>
```
* 在MainActivity中创建操作类的对象,用来操作

```android

@Override
  protected void onCreate(Bundle savedInstanceState) {
      super.onCreate(savedInstanceState);
      /*setContentView(R.layout.activity_main);*/
      ActivityMainBinding binding = 
              DataBindingUtil.setContentView(this,R.layout.activity_main);
        //可以直接通过user来获得和设置内容
       final User user = new User() ;
       user.setUserName("WangTian");
       user.setPassWords("135410");
       binding.setUser(user);
  }
  ```

  ```android

* 布局中需要改变的view的设置

  <ImageView
            android:layout_width="wrap_content"
            android:layout_height="wrap_content"
            android:src="@mipmap/ic_launcher"
            android:layout_gravity="center"
            android:visibility="@{user.visible ? View.VISIBLE : View.GONE }"/>
```
