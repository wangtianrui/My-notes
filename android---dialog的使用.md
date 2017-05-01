### dialogFragment的使用

①创建一个dialogFragment的类，继承于AppCompatDialogFragment
```java
public class PhotoShowFragment extends AppCompatDialogFragment {

}
```
②创建这个dialogFragment的layout
```xlmns
<?xml version="1.0" encoding="utf-8"?>
<LinearLayout
    xmlns:android="http://schemas.android.com/apk/res/android"
    android:layout_width="match_parent"
    android:layout_height="match_parent"
    android:orientation="vertical"
    android:padding="16dp">
    <ImageView
        android:layout_width="match_parent"
        android:layout_height="match_parent"
        android:id="@+id/iamge_show_image_view"
        />
</LinearLayout>
```
③加载布局，并获取其中的重要部件（对部件的赋值也是在此）
```java
@Override
    public Dialog onCreateDialog(Bundle savedInstanceState) {
        View v = LayoutInflater.from(getActivity()).inflate(R.layout.photo_show_fragment_layout, null);
        mPhotoShowImageView = (ImageView) v.findViewById(R.id.iamge_show_image_view);
        Bitmap bitmap = BitmapFactory.decodeFile(mphotoPath);
        mPhotoShowImageView.setImageBitmap(bitmap);
        return new AlertDialog.Builder(getActivity())
                .setView(v)
                .create();
    }
```
④在dialogFragment的类中封装一个创建该fragment对象的方法,用来获取数据和创建fragment对象
```java
public static PhotoShowFragment newInstance(String photoDir) {
    PhotoShowFragment fragment = new PhotoShowFragment();
    fragment.mphotoPath = photoDir;
    return fragment;
}
```
④在需要跳转的fragment中获取该对象，并进行Dialog显示
```java
mPhotoView.setOnClickListener(new View.OnClickListener() {
           @Override
           public void onClick(View v) {
               FragmentManager manager = getFragmentManager();
               PhotoShowFragment photoShowFragment = PhotoShowFragment.newInstance(mPhotoFile.getPath());
               photoShowFragment.show(manager,DIALOG_PHOTO);
           }
       });
```
