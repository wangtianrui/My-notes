## 自定义camera

#### 一、首先是简单的相机调用（画面未调整）

  ①权限
  ```xml
  <?xml version="1.0" encoding="utf-8"?>
  <manifest xmlns:android="http://schemas.android.com/apk/res/android"
    package="org.xm.camerasimple"
    android:versionCode="1"
    android:versionName="1.0" >

    <uses-permission android:name="android.permission.CAMERA"/>
    <uses-feature android:name="android.hardware.camera" android:required="false"/>
    <uses-permission android:name="android.permission.WRITE_EXTERNAL_STORAGE" />

    ...

  </manifest>
  ```
  ②检测是否有相机与获取相机的方法
  ```java
  // 判断相机是否支持
    private boolean checkCameraHardware(Context context) {
        if (context.getPackageManager().hasSystemFeature(
                PackageManager.FEATURE_CAMERA)) {
            return true;
        } else {
            return false;
        }
    }

    // 获取相机
    public static Camera getCameraInstance() {
        Camera c = null;
        try {
            c = Camera.open();
        } catch (Exception e) {
            e.printStackTrace();
        }
        return c;
    }
  ```
  ③创建prieview----相机拍摄的画面
  ```java
  public class CameraPreview extends SurfaceView implements SurfaceHolder.Callback {
    private SurfaceHolder mHolder;
    private Camera mCamera;

    public CameraPreview(Context c, Camera camera) {
        super(c);
        mCamera = camera;
        mHolder = getHolder();

        //相当于是一个listener
        mHolder.addCallback(this);

        //SURFACE_TYPE_PUSH_BUFFER表明该Surface用到的数据由其他对象提供
        mHolder.setType(SurfaceHolder.SURFACE_TYPE_PUSH_BUFFERS);
    }

    public void surfaceCreated(SurfaceHolder holder) {
       try{
           mCamera.setPreviewDisplay(holder);
           mCamera.startPreview();
       }catch (Exception e){
           e.printStackTrace();
       }
    }

    @Override
    public void surfaceChanged(SurfaceHolder holder, int format, int width, int height) {
        if(mHolder.getSurface() == null){
            return ;
        }
        try{
            mCamera.stopPreview();
        }catch (Exception e){
            e.printStackTrace();
        }
        try{
            mCamera.setPreviewDisplay(mHolder);
            mCamera.startPreview();
        }catch (Exception e){
            e.printStackTrace();
        }
    }

    @Override
    public void surfaceDestroyed(SurfaceHolder holder) {

    }
  }

  ```
  ④创建相机的layout
  ```xml
   <?xml version="1.0" encoding="utf-8"?>
   <RelativeLayout xmlns:android="http://schemas.android.com/apk/res/android"
    android:layout_width="match_parent"
    android:layout_height="match_parent" >

    <FrameLayout
        android:id="@+id/camera_preview"
        android:layout_width="match_parent"
        android:layout_height="match_parent" />

    <Button
        android:id="@+id/button_capture"
        android:layout_width="wrap_content"
        android:layout_height="wrap_content"
        android:layout_alignParentBottom="true"
        android:layout_centerHorizontal="true"
        android:text="拍照" />

    </RelativeLayout>
  ```
  ⑤在Activity中引用视图
  ```java
  public class CameraActivity extends Activity {

    public static final String TAG = "CameraSimple";
    private Camera mCamera;
    private CameraPreview mPreview;
    private FrameLayout mCameralayout;
    private Button mTakePictureBtn;

    @Override
    protected void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        setContentView(R.layout.activity_camera);
        if (!checkCameraHardware(this)) {
            Toast.makeText(CameraActivity.this, "相机不支持", Toast.LENGTH_SHORT)
                    .show();
        } else {
            mCamera = getCameraInstance();
            mPreview = new CameraPreview(CameraActivity.this, mCamera);
            mCameralayout = (FrameLayout) findViewById(R.id.camera_preview);
            mCameralayout.addView(mPreview);
        }
    }
  ```
  ⑥实例化拍照按钮并赋予功能
  ```java
  // 拍照回调
    private PictureCallback mPictureCallback = new PictureCallback() {

        @Override
        public void onPictureTaken(byte[] data, Camera camera) {
            File pictureDir = Environment
                    .getExternalStoragePublicDirectory(Environment.DIRECTORY_PICTURES);
            if (pictureDir == null) {
                Log.d(TAG,
                        "Error creating media file, check storage permissions!");
                return;
            }

            try {
                String pictureName = new DateFormat().format("yyyyMMddHHmmss",
                        new Date()).toString()
                        + ".png";
                FileOutputStream fos = new FileOutputStream(pictureDir
                        + File.separator + pictureName);
                fos.write(data);
                fos.close();
            } catch (FileNotFoundException e) {
                Log.d(TAG, "File not found: " + e.getMessage());
            } catch (IOException e) {
                Log.d(TAG, "Error accessing file: " + e.getMessage());
            }
        }
    };

    mTakePictureBtn = (Button) findViewById(R.id.button_capture);
    mTakePictureBtn.setOnClickListener(new View.OnClickListener() {
        @Override
        public void onClick(View v) {
            mCamera.takePicture(null, null, mPictureCallback);
        }
    });
  ```
#### 二、调整画面
