## 使用通知

* 首先要获取一个NotificationManager来进行管理 

```android

NotificationManager manager = (NotificationManager)getSystemService(Context.NOtTIFICATION_SERVICE);
//方法接收一个字符串参数用于确定获取系统的哪个服务

```

* API的兼容问题 NotificationCompat类的所创建的Notification对象可以保证API的兼容性

```android

Notification Notification = new NotificationCompat.Builder(Context)
.setContentTitle("This is content title")  //标题
.setContentText("This is content text")     //内容1
.setWhen(System.currentTimeMillis())     //显示时间
.setSmallIcon(R.drawable.small_icon)    //设置通知的小图标
.setLargeIcon(BitmapFactory.decodeResource(getResources(),R.drawable.large_icon))
.build();

```

* 调用NotificationManager的notify()方法就可以让通知显示出来

```android

manager.notify(1 , notification);

```

## 为通知设置点击事件

* 获取PendingIntent的实例

```android

getActivity()       getBroadcast()    getSystemService()   
 //三个方法的参数一样，第一个是Context,第二个一般用不到传入0，第三个是个Intent对象，第四个用于确定PedingItent的行为

 ```

 * 通过NotificationCompat.Builder来调用setContentIntent()方法来设置

 * 取消一直显示在系统的状态栏

```android
//通过NotificationCompat.Builder来调用setAutoCancel()方法（隐式）
Notification Notification = new NotificationCompat.Builder(Context).setAutoCancel(true);

//也可以显式地设置,调用NotificationManager的cancel()方法来取消
NotificationManager manager = (NotificationManager)getSystemService(Context.NOtTIFICATION_SERVICE);
manager.cancel(1);
```

## 通过manager设置更多的属性(都是通过NotificationCompat.Builder(Context)调用函数来设置)

* 设置声音

```android

.setSound(Uri.fromFile(new File("/system/media/audio/ringtones/Luna.ogg")))

```

* 设置振动

```android
.setVibrate(new long[]{0,1000,1000,1000})


//振动权限需要在AndroidManifest.xml中申请
 <uses-permission android:name="android.permission.VIBRATE"/>
```

* 设置LED灯

```android
.setLights(Color.GREEN,1000,1000)
```

* 全部设置为默认

```android
.setDefaults(NotificationCompat.DEFAULT_ALL)
```


