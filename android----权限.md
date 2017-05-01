## 程序运行时申请权限

* 要在AndroidManifest.xml文件中对相关权限的信息进行申请

```android
 <uses-permission android:name="android.permission.CALL_PHONE"/>
 ```

 * 在MainActivity中对相关操作进行书写

 ```android
 buttonMakeCall.setOnClickListener(new View.OnClickListener() {
            @Override
            public void onClick(View v) {
                try {
                    Intent intent = new Intent(Intent.ACTION_CALL); //直接拨号而不是进入拨号界面
                    intent.setData(Uri.parse("tel:10086"));
                    startActivity(intent);  //如果在上述文件中不进行注册申请，这儿会报错
                } catch (SecurityException e ){
                    e.printStackTrace();
                }
            }
        });
//以上书写在android6.0以上会报错，6.0以上在进行危险权限操作的时候都必须进行运行时权限处理
```

* 需要checkSelfPermission方法来确认是否拥有权限
* 在通过onRequestPermissionsResult方法来对用户的选择做出相应事件处理

```android

buttonMakeCall.setOnClickListener(new View.OnClickListener() {
            @Override
            public void onClick(View v) {
                if (ContextCompat.checkSelfPermission(MainActivity.this, Manifest.permission
                        .CALL_PHONE) != PackageManager.PERMISSION_GRANTED) {
                    ActivityCompat.requestPermissions(MainActivity.this, new String[]{
                            Manifest.permission.CALL_PHONE}, 1);
                } else {
                    call();
                }
            }
        });
    
private  void call(){
        try{
            Intent intent = new Intent(Intent.ACTION_CALL);
            intent.setData(Uri.parse("tel:10086"));
            startActivity(intent);
        }catch (SecurityException e){
            e.printStackTrace();
        }
    }

@Override
public void onRequestPermissionsResult(int requestCode, @NonNull String[] permissions,
                                           @NonNull int[] grantResults) {
        super.onRequestPermissionsResult(requestCode, permissions, grantResults);
        switch (requestCode){
            case 1 :
                if( grantResults.length > 0 && grantResults[0] == PackageManager
                        .PERMISSION_GRANTED){
                    call();
                }else{
                    Toast.makeText(this,"you denied the permission",Toast.LENGTH_SHORT).show();
                }
                break;
            default:
        }
      }
```
