## fragment

### 一般是用支持库中的fragment（方便更新版本）

* #### 首先是添加支持
```txt
File -> Project Structure -> app -> Dependencies -> + -> support-v4 
```

* #### 然后将Activity改为继承fragment,使之成为fragment的托管对象 

```java
public class CrimeActivity extends FragmentActivity {
  
}
```

* #### 然后创建fragment类，用来加载布局 

```java
public class CrimeFragment extends android.support.v4.app.Fragment{
  
}
```
* 该类可以类比为一个Activity，内部有几个自动执行的方法

  首先是onCreate，一般是在此方法中声明需要创建的对象,方便对象的创建和后面方法的调用
  ```java
  @Override
    public void onCreate(@Nullable Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        mCrime = new Crime();
    }
    ```

    然后是onCreateView方法，该方法用来将fragment和布局文件绑定，并且大多数事件处理都是在次方法中实现（类似于Activity的onCreate）,值得注意的是该方法是对一个View对象操作（也就是fragment），最后返回该对象

    ```java
    @Nullable
    @Override
    public View onCreateView(LayoutInflater inflater, @Nullable ViewGroup container, @Nullable Bundle savedInstanceState) {
        View v = inflater.inflate(R.layout.fragment_crime, container, false);

        mTileField = (EditText) v.findViewById(R.id.crime_title);

        //在内部文字改变的同时将文字保存下来，CharSequence代表用户的输入
        mTileField.addTextChangedListener(new TextWatcher() {
            @Override
            public void beforeTextChanged(CharSequence s, int start, int count, int after) {

            }

            @Override
            public void onTextChanged(CharSequence s, int start, int before, int count) {
                mCrime.setTitle(s.toString());
            }

            @Override
            public void afterTextChanged(Editable s) {

            }
        });

        mDateButton = (Button) v.findViewById(R.id.crime_date_button);
        mDateButton.setText(mCrime.getDate()+"");
        mDateButton.setEnabled(false);

        mSolvedCheckBox = (CheckBox)v.findViewById(R.id.crime_solved_checkbox);
        mSolvedCheckBox.setOnCheckedChangeListener(new CompoundButton.OnCheckedChangeListener() {
            @Override
            public void onCheckedChanged(CompoundButton buttonView, boolean isChecked) {
                mCrime.setSolved(isChecked);
            }
        });
        return v;
    }
    ```

* 因为fragment是在Activity上运行，所以为了找到该活动，需要给活动布局添加一个id

```xmlns
<?xml version="1.0" encoding="utf-8"?>
<FrameLayout
    xmlns:android="http://schemas.android.com/apk/res/android"
    xmlns:app="http://schemas.android.com/apk/res-auto"
    android:layout_width="match_parent"
    android:layout_height="match_parent"
    android:id="@+id/fragment_container">
</FrameLayout>
```

* 然后是创建一个fragment的布局，用于Fragment类绑定

```xmlns
<?xml version="1.0" encoding="utf-8"?>
<LinearLayout xmlns:android="http://schemas.android.com/apk/res/android"
              android:layout_width="match_parent"
              android:layout_height="match_parent"
              android:orientation="vertical">

    <TextView
        style="?android:listSeparatorTextViewStyle"
        android:layout_width="match_parent"
        android:layout_height="wrap_content"
        android:text="@string/crime_title_label"/>

    <EditText
        android:id="@+id/crime_title"
        android:layout_width="match_parent"
        android:layout_height="wrap_content"
        android:layout_marginLeft="16dp"
        android:layout_marginRight="16dp"
        android:hint="@string/crime_title"/>
    <TextView
        android:layout_width="match_parent"
        android:layout_height="wrap_content"
        android:text="@string/crime_details_label"
        style="?android:listSeparatorTextViewStyle"/>

    <Button
        android:layout_width="match_parent"
        android:layout_height="wrap_content"
        android:layout_marginRight="16dp"
        android:layout_marginLeft="16dp"
        android:id="@+id/crime_date_button"/>
    <CheckBox
        android:layout_width="match_parent"
        android:layout_height="wrap_content"
        android:text="@string/crime_solved_label"
        android:id="@+id/crime_solved_checkbox"
        android:layout_marginLeft="16dp"
        android:layout_marginRight="16dp"/>

</LinearLayout>
```

* #### 最后是在Activity（继承自Fragment）中用FragmentManager来管理fragment（入栈和出栈）

```android
@Override
    protected void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        setContentView(R.layout.activity_crime);

        FragmentManager fm = getSupportFragmentManager(); 
        Fragment fragment = fm.findFragmentById(R.id.fragment_container);//通过ID找到该容器下的fragment
        //添加fragment
        if( fragment == null){
            fragment = new CrimeFragment();      //fragment类已经绑定了fragment布局
            fm.beginTransaction()
                    .add(R.id.fragment_container,fragment)//为Manager绑定托管布局（Activity的布局）
                    .commit();
        }
    }
    ```
