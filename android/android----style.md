### style相关知识

* #### 修改背景（style的）-----通过覆盖父类主题中的属性来修改相应的空间的颜色

```xml
<!-- Base application theme. -->
    <style name="AppTheme" parent="Theme.AppCompat">
        <!-- Customize your theme here. -->
        <item name="colorPrimary">@color/red</item>
        <item name="colorPrimaryDark">@color/dark_red</item>
        <item name="colorAccent">@color/gray</item>
        <!-- 覆盖父文件中的背景属性-->
        <item name="android:colorBackground">@color/soothing_blue</item>
        <item name="android:buttonStyle">@style/BeatBoxButton</item>
    </style>

    <style name="BeatBoxButton" parent="android:Widget.Holo.Button">
        <item name="android:background">@color/dark_blue</item>
    </style>

    <!--通过继承的形式创建新的style-->
```

* #### 修改形状（利用shape drawable）
    ①在drawable文件中先定义一个圆形
    ```xml
    <?xml version="1.0" encoding="utf-8"?>
    <shape
    xmlns:android="http://schemas.android.com/apk/res/android"
    android:shape="oval" ><!--定义一个圆形-->

    <solid
        android:color="@color/dark_blue"/>   <!--定义圆形的颜色 -->
    </shape>
    ```
    ②在style文件中修改相关信息
    ```xml
    <!-- Base application theme. -->
   <style name="AppTheme" parent="Theme.AppCompat">
       <!-- Customize your theme here. -->
       <item name="colorPrimary">@color/red</item>
       <item name="colorPrimaryDark">@color/dark_red</item>
       <item name="colorAccent">@color/gray</item>
       <!-- 覆盖父文件中的背景属性-->
       <item name="android:colorBackground">@color/soothing_blue</item>
       <item name="android:buttonStyle">@style/BeatBoxButton</item>
   </style>

   <style name="BeatBoxButton" parent="android:Widget.Holo.Button">
       <item name="android:background">@drawable/button_beat_box_normal</item>    <!--只需修改这行就行-->
   </style>
   ```

* #### 让button在点击时动起来
    ①需要定义一个用于按钮按下状态的shape drawable
    ```xml
    <?xml version="1.0" encoding="utf-8"?>
    <shape
    xmlns:android="http://schemas.android.com/apk/res/android"
    android:shape="oval" ><!--定义一个圆形-->

    <solid
        android:color="@color/red"/>   <!--定义圆形的颜色 -->

    </shape>
    ```
    ②创建一个state list drawable,来设置不同时候button的样子
    ```xml
    <?xml version="1.0" encoding="utf-8"?>
    <selector xmlns:android="http://schemas.android.com/apk/res/android">
    <item android:drawable="@drawable/button_beat_box_pressed"
          android:state_pressed="true"/>    <!--设置按下时的样子-->
    
    <item android:drawable="@drawable/button_beat_box_normal"/> <!--设置平时的样子-->
    </selector>
    ```
    ③最后再修改style属性代码
    ```xml
    <style name="BeatBoxButton" parent="android:Widget.Holo.Button">
        <item name="android:background">@drawable/button_beat_box</item>
    </style>
    ```
    
* #### 让两个XML drawable合二为一，创建出新的效果
```xml
<?xml version="1.0" encoding="utf-8"?>
<layer-list xmlns:android="http://schemas.android.com/apk/res/android">
    <item>
        <shape
            android:shape="oval"><!--定义一个圆形-->

            <solid
                android:color="@color/red"/>   <!--定义圆形的颜色 -->

        </shape>
    </item>
    <item>
        <shape
            android:shape="oval">
            <stroke
                android:width="4dp"
                android:color="@color/dark_red"/>
        </shape>
    </item>
</layer-list>
```
