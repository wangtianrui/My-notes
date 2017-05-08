### Service与计时器的使用

#### 服务   
服务类似于activity，拥有生命周期，并且可以通过Intent来跳转
```txt
oncreate -> onstart -> onhandleIntent -> onDestroy
```

```txt
①onCreate()方法 ：服务创建时调用

②onStartCommand(Intent intent,int a,int b)方法：每次组件通过startService（intent）方法启动服务时调用一次。a是标识符，b是启
动ID.标识符是用来判断当前服务是重新发送了一次还是一次都没发送过，每次调用该方法ID都不同，所以ID可以用来区别不同的服务

③onDestroy（）方法 服务在不在需要时和停止后调用，后者主要取决于服务类型
服务类型：
Service.START_NOT_STICKY ：START_NOT_STICKY：“非粘性的”。使用这个返回值时，如果在执行完onStartCommand后，服务被异常kill掉，
系统将会把它置为started状态，系统不会自动重启该服务，直到startService(Intent intent)方法再次被调用。

START_STICKY：如果service进程被kill掉，保留service的状态为开始状态，但不保留递送的intent对象。随后系统会尝试重新创建service，
由于服务状态为开始状态，所以创建服务后一定会调用onStartCommand(Intent,int,int)方法。如果在此期间没有任何启动命令被传递到service
，那么参数Intent将为null。

START_REDELIVER_INTENT：重传Intent。使用这个返回值时，如果在执行完onStartCommand后，服务被异常kill掉，系统会自动重启该服务，并
将Intent的值传入。
```
① 创建一个类，继承自IntentService
```java
public class PollService extends IntentService {
    private static final String TAG = "PollService";

    private static final int POLL_INTERVAL = 1000 * 60; //60秒

    //包装一个创建Intent的方法
    public static Intent newIntent(Context context) {
        return new Intent(context, PollService.class);
    }

    public PollService() {
        super(TAG);
    }
}
```
②在类中重写服务运行时执行的主题方法
```java
@Override
  protected void onHandleIntent(@Nullable Intent intent) {
      Log.d(TAG, "onHandleIntent: Service is running");
  }
```
③在该类中包装一个判断该服务是否在运行的方法
```java
public static boolean isServiceAlarmOn(Context context) {
        Intent i = PollService.newIntent(context);
        //一个PendingIntent只能对应一个服务
        //可通过检测是否存在pendingIntent 来检测是否已有计时器
        PendingIntent pi = PendingIntent.getService(context, 0, i, PendingIntent.FLAG_NO_CREATE);
        return pi != null;
    }
```
④在Fragment中运行服务
```java
 getActivity().startService(PollService.newIntent(getActivity()));
 ```

#### 为服务加上定时器
①在上述服务类中新包装创建计时器和服务，并给予绑定的方法
```java
public static void setServiceAlarm(Context context, boolean isOn) {
        Intent i = PollService.newIntent(context);
        PendingIntent pi = PendingIntent.getService(context, 0, i, 0);

        AlarmManager alarmManager = (AlarmManager) context.getSystemService(Context.ALARM_SERVICE);

        if (isOn) {
            //AlarmManager.ELAPSED_REALTIME是基准时间值，SystemClock.elapsedRealtime走过的时间来确定
            alarmManager.setInexactRepeating(AlarmManager.ELAPSED_REALTIME, SystemClock.elapsedRealtime(), POLL_INTERVAL, pi);
        } else {
            alarmManager.cancel(pi);
            pi.cancel();
        }
    }
```
②在Fragment中调用即可
```java
PollService.setServiceAlarm(getActivity(), !PollService.isServiceAlarmOn(getActivity()));
```
