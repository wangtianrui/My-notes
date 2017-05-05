### 另一个开辟线程的方法------HandlerThread 
该方法与AsyncTask对比
```txt
AsyncTask更多用于单线程开辟，在android3.2后，不再为每一个AsyncTask实例单独开辟线程，而是在一个单一的线程Executor中运行后台任务
HandlerThread则是用来解决多个线程同时创建的问题，更加省事儿
```
正因为HandlerThread的多线程进行，带来了很多信息传递问题，则引入了handler来处理信息

①新建一个类，继承自HandlerThread来进行线程处理

```java
public class ThumbnailDownloader<T> extends HandlerThread {
    private static final String TAG = "ThumbnailDownloader";

    private Boolean mHasQuit = false;

    public ThumbnailDownloader() {
        super(TAG);
    }

    //用来关闭线程
    @Override
    public boolean quit() {
        return super.quit();
    }
    
//用来绑定url和holder对象
    public void queueThumbnail(T target, String url) {
        Log.i(TAG, "queueThumbnail: Got a URL" + url);
    }
}
```

②在Fragment中声明一个线程对象，并开启，同时在onDestroy中声明线程的退出

```java
mThumbnailDownloader = new ThumbnailDownloader<>();
mThumbnailDownloader.start();
mThumbnailDownloader.getLooper();//调用该方法，来确认线程准备就绪
Log.i(TAG, "onCreate: BackGroud thread start");



@Override
   public void onDestroy() {
       super.onDestroy();
       mThumbnailDownloader.quit();
       Log.i(TAG, "onDestroy:BackGroud thread Destroy ");
   }
```

③调用线程类中包装好的queueThumbnail方法，使线程进行相应操作

```java
//该APP是一个加载图片的应用，所以线程操作是在RecyclerView的onBindViewHolder中进行操作
@Override
        public void onBindViewHolder(PhotoHolder holder, int position) {
           GalleryItem galleryItem = mGalleryItems.get(position);
            Drawable placeHolder = getContext().getResources().getDrawable(R.drawable.bill_up_close);
            holder.bindGalleryItem(placeHolder);
            mThumbnailDownloader.queueThumbnail(holder,galleryItem.getUrl());
        }
```
以上实现了多线程的开辟（可同时进行）,那么如何在开辟的线程与主线程之间进行信息交互呢？-----用到handler,handler是“在哪儿创建，属于哪里”,可以发送信息也可以接受信息

④得到一个handler,和一个ConcurrentMap -- 用来打包和管理线程以及其对应的url和ViewHolder

```java
private Handler mRequestHandler;
private ConcurrentMap<T, String> mRequestMap = new ConcurrentHashMap<>();
```

⑤绑定url并更新线程操作的方法

```txt
信息的格式：
what : int类型，用来描述和识别信息
obj:随消息发送的对象
target:处理消息的handler
```

绑定
```java
public void queueThumbnail(T target, String url) {
        Log.i(TAG, "queueThumbnail: Got a URL" + url);

        if (url == null) {
            mRequestMap.remove(target);
        }else{
            mRequestMap.put(target,url);   //按照“信息”的格式存储     
            mRequestHandler.obtainMessage(MESSAGE_DOWNLOAD,target)  //从循环池中获取消息
                    .sendToTarget(); //告诉发消息的，我已经收到消息，使得循环池把接受了的消息放到最后
        }
    }
```

操作
```java
@Override
    protected void onLooperPrepared() {
        mRequestHandler = new Handler() {
            @Override
            public void handleMessage(Message msg) {
              //核对，如果是需要的Message，则进行操作
                if (msg.what == MESSAGE_DOWNLOAD) {
                    T target = (T) msg.obj;
                    handleRequest(target);
                }
            }
        };
    }

//下载图片的操作
private void handleRequest(final T target) {
        try {
            final String url = mRequestMap.get(target);

            if (url == null) {
                return;
            }
            byte[] bitmapBytes = new FlickrFetchr().getUrlBytes(url);
            final Bitmap bitmap = BitmapFactory.decodeByteArray(bitmapBytes, 0, bitmapBytes.length);
            Log.i(TAG, "handleRequest: bitmap Create");
        }catch (IOException i){
            Log.e(TAG, "handleRequest: erro download ",i);
        }
    }
```

与主线程实现信息交流----在主线程中创建handler,然后在新线程中调用即可

⑥在线程类中新曾一个handler（用来接收主线程中的handler） ， 和一个监听器（用来回调）
```java
    private Handler mResponseHandler;
    private ThumbnailDownloadListener<T> mThumbnailDownloadListener;

    public interface ThumbnailDownloadListener<T> {
        void onThumbnailDownload(T target, Bitmap bitmap);
    }

    public void setThumbnailDownloadListener(ThumbnailDownloadListener<T> listener) {
        mThumbnailDownloadListener = listener;
    }

    public ThumbnailDownloader(Handler handler) {
        super(TAG);
        mResponseHandler = handler;
    }

```
⑦在Fragment中创建和绑定监听器和操作的实现
```java
Handler mResponseHandler = new Handler();
       mThumbnailDownloader.setThumbnailDownloadListener(new ThumbnailDownloader.ThumbnailDownloadListener<PhotoHolder>() {
           @Override
           public void onThumbnailDownload(PhotoHolder target, Bitmap bitmap) {
               Drawable drawable = new BitmapDrawable(getResources(), bitmap);
               target.bindGalleryItem(drawable);
           }
       });
       ```
⑧发布Message给主线程

```java
mResponseHandler.post(new Runnable() {
                @Override
                public void run() {
                    if (mRequestMap.get(target) != url || mHasQuit) {
                        return;
                    }
                    mRequestMap.remove(target);
                    mThumbnailDownloadListener.onThumbnailDownload(target,bitmap);
                }
            });
```
⑨退出线程
```java
mRequestHandler.removeMessages(MESSAGE_DOWNLOAD);
```
