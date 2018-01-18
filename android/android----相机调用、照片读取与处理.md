### 照片的存取和对照片的操作

* #### 照片的拍摄后存取
①创建一个相机intent
```java
Intent captureImage = new Intent(MediaStore.ACTION_IMAGE_CAPTURE);
```
②检验设备是否支持摄像，如果支持则为intent附加上储存地址（地址是绝对路径并且包括了照片的名字和类型，如：照片.jdp）
```java
boolean canTakePhoto = mPhotoFile != null && captureImage.resolveActivity(packageManager) != null;
        mPhotoButton.setEnabled(canTakePhoto);
        if (canTakePhoto) {
            Uri uri = Uri.fromFile(mPhotoFile);
            captureImage.putExtra(MediaStore.EXTRA_OUTPUT, uri);
        }
```
③打开Intent并要求返回信息(照相后对相片存储路径处的信息进行操作与解码)
```java
mPhotoButton.setOnClickListener(new View.OnClickListener() {
           @Override
           public void onClick(View v) {
               startActivityForResult(captureImage, REQUEST_PHOTO);
           }
       });
```
④通过解码，获得Bitmap型照片
```java
//得到一个options对象，用来得到图片信息
BitmapFactory.Options options = new BitmapFactory.Options();
options.inJustDecodeBounds = true;
//以options控制的标准解码该图片为Bitmap型
Bitmap bitmap = BitmapFactory.decodeFile(path, options);
```
⑤最终加载图片
```java
mPhotoView.setImageBitmap(bitmap);
```

* #### 对图片进行处理操作
对path中的图片进行“降低像素”的处理
```java
public static Bitmap getScaledBitmap(String path, int destWidth, int destHeight) {

        //得到一个options对象，用来得到图片信息
        BitmapFactory.Options options = new BitmapFactory.Options();
        options.inJustDecodeBounds = true;

        //以options控制的标准解码该图片为Bitmap型
        BitmapFactory.decodeFile(path, options);

        float srcWidth = options.outWidth;
        float srcHeigh = options.outHeight;

        int inSampleSize = 1;
        if (srcHeigh > destHeight || srcWidth > destWidth) {
            if (srcWidth > srcHeigh) {
                //四舍五入
                inSampleSize = Math.round(srcHeigh / destHeight);
            } else {
                inSampleSize = Math.round(srcWidth / destWidth);
            }
        }
        //又创建一个options对象，用来操作
        options = new BitmapFactory.Options();
        //设置inSampleSize值
        options.inSampleSize = inSampleSize;

        return BitmapFactory.decodeFile(path, options);
    }
```
在上面方法的基础上让图片以屏幕为基础降低像素
```java
public static Bitmap getScaledBitmap(String path, Activity activity) {
        //表示空间坐标的类（有x,y）
        Point size = new Point();

        activity.getWindowManager().getDefaultDisplay().getSize(size);

        return getScaledBitmap(path, size.x, size.y);
    }
```
