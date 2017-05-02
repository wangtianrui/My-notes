### 加载音频

* #### 首先是使用Assets来储存音频文件
```txt
在包里新建一个assets包，将音频文件放进去
```

* #### 新建一个Sound类，用来作为描述一个音频文件的对象

```java
public class Sound {
    private String mAssetPath;
    private String mName;
    private Integer mSoundId;

    
    public Sound(String assetPath) {
        mAssetPath = assetPath;
        String[] components = assetPath.split("/");
        String filename = components[components.length - 1];
        mName = filename.replace(".wav", "");
    }

    public void setSoundId(Integer soundId) {
        mSoundId = soundId;
    }

    public Integer getSoundId() {
        return mSoundId;
    }

    public String getAssetPath() {
        return mAssetPath;
    }

    public String getName() {
        return mName;
    }
}
```

* 得到一个SoundPool类对象，用来播放音频

```java

private SoundPool mSoundPool = buildSoundPool();

//根据不同的API版本来选取不同的构造方法
@SuppressWarnings("deprecation")
   @TargetApi(Build.VERSION_CODES.LOLLIPOP)
   private SoundPool buildSoundPool() {
       SoundPool soundPool;
       if (Build.VERSION.SDK_INT >= Build.VERSION_CODES.LOLLIPOP) {
           AudioAttributes attributes = new AudioAttributes.Builder()
                   .setUsage(AudioAttributes.USAGE_MEDIA)
                   .setContentType(AudioAttributes.CONTENT_TYPE_MUSIC)
                   .build();
           soundPool = new SoundPool.Builder()
                   .setAudioAttributes(attributes)
                   .setMaxStreams(MAX_SOUNDS)
                   .build();
       } else {
           soundPool = new SoundPool(MAX_SOUNDS, AudioManager.STREAM_MUSIC, 0);
       }
       return soundPool;
   }

```

* #### 加载一个音乐文件

```java
//加载音乐
    private void loadSounds() {

        //文件名数组
        String[] soundNames;
        try {
            //list能列出指定目录中的所有文件名
            soundNames = mAsset.list(SOUND_FOLDER);
            Log.d(TAG, "Found" + soundNames.length + "sounds");
        } catch (IOException ioe) {
            Log.e(TAG, "Could not list assets", ioe);
            return;
        }
        for (String filename : soundNames) {
            try {

                String assetPath = SOUND_FOLDER + "/" + filename;
                Sound sound = new Sound(assetPath);
                load(sound);
                mSounds.add(sound);
            } catch (IOException i) {
                Log.e(TAG, "Could not load sound" + filename, i);
            }
        }
    }


    //向SoundPool中添加音频
    private void load(Sound sound) throws IOException {
        AssetFileDescriptor afd = mAsset.openFd(sound.getAssetPath());
        int soundId = mSoundPool.load(afd, 1);
        sound.setSoundId(soundId);
    }
```

* #### 播放音频

```java
@Override
       public void onClick(View v) {
           mBeatBox.play(mSound);    //mBeatBox是一“整体对象”
       }
```
* #### 如何防止旋转屏幕中断声音

```java
//在fragment类中的oncreate方法中
@Override
    public void onCreate(@Nullable Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        setRetainInstance(true);   //将该数值设置为true，即可

        mBeatBox = new BeatBox(getActivity());
    }
```
