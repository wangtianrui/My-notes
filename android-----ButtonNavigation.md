### BottomNavigationView

##### 首先是在build里面添加依赖
```java
compile 'com.android.support:design:25.3.1'
```

##### 然后创建menu用来管理每个button的文字、图标和id
```xml
<?xml version="1.0" encoding="utf-8"?>
<menu xmlns:android="http://schemas.android.com/apk/res/android">

    <item
        android:id="@+id/navigation_home"
        android:icon="@drawable/ic_home_black_24dp"
        android:title="@string/title_home"/>

    <item
        android:id="@+id/navigation_dashboard"
        android:icon="@drawable/ic_dashboard_black_24dp"
        android:title="@string/title_dashboard"/>

    <item
        android:id="@+id/navigation_notifications"
        android:icon="@drawable/ic_notifications_black_24dp"
        android:title="@string/title_notifications"/>

</menu>

```

##### 在布局中添加控件     ,  注意里面的app:menu就是用来加载menu的
```xml
<android.support.design.widget.BottomNavigationView
        android:id="@+id/navigation"
        android:layout_width="match_parent"
        android:layout_height="wrap_content"
        android:layout_gravity="bottom"
        android:background="?android:attr/windowBackground"
        app:menu="@menu/navigation"/>
```

##### 相应的点击事件的处理
在activity中

```java
@Override
       public boolean onNavigationItemSelected(@NonNull MenuItem item) {
           switch (item.getItemId()) {
               case R.id.navigation_home:
                   mTextMessage.setText(R.string.title_home);
                   return true;
               case R.id.navigation_dashboard:
                   mTextMessage.setText(R.string.title_dashboard);
                   return true;
               case R.id.navigation_notifications:
                   mTextMessage.setText(R.string.title_notifications);
                   return true;
           }
           return false;
       }
```
