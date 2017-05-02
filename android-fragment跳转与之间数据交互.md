### Fragment之间的“目标跳转”

 #### ①首先是为Fragment设置目标(下文中的dialog都是一个Fragment)

 ```java
dialog.setTargetFragment(CrimeFragment.this, REQUEST_DATE);//REQUEST_DATE是用来作为信息标识的“代号”
 ```

 #### ②使用Fragment.onActivityResult()方法来携带intent（传送的信息）跳转

 ```java
 Intent intent = new Intent();
 intent.putExtra(EXTRA_DATE, date);
 getTargetFragment().onActivityResult(getTargetRequestCode(), resultCode, intent);
 ```

 #### ③在dialog中设置传送信息
 ```java
 int year = mDatePicker.getYear();
 int month = mDatePicker.getMonth();
  int day = mDatePicker.getDayOfMonth();
  Date date = new GregorianCalendar(year, month, day).getTime();
  sendResult(Activity.RESULT_OK,date);
 ```

 #### ④在目标Fragment中获取数据

 ```java
 @Override
    public void onActivityResult(int requestCode, int resultCode, Intent data) {
        if (requestCode != Activity.RESULT_OK) {
            return;
        }
        if (requestCode == REQUEST_DATE) {
            Date date = (Date) data.getSerializableExtra(DatePickerFragment.EXTRA_DATE);
            mCrime.setDate(date);
            mDateButton.setText(mCrime.getDate() + "");
        }
    }
```
startActivityForResult是打开一个activity，以当前Activity为Result（也就是新Activity销毁后的跳转目标）
onActivityResult是Activity销毁后目标Activity会自动调用的方法，数据传送逻辑处理的地方

### Fragment之间的跳转

* #### 方法一（直接使用manager添加），但是这种方法是写在Fragment中，让每个Fragment更加具体，不建议采用

```java
public void onClick(View v){
       Fragment fragment = CrimeFragment.newInstance(mCrime.getId());
       FragmentManager fm = getActivity().getSupportFragment();
       fm.beginTransaction()
          .add(R.id.detail_fragment_container,fragment)
          .commit();
}
```
* #### 方法二（使用回调接口来实现）

```txt
由Fragment定义名为Callbacks的回调接口，回调接口定义为了Fragment委托给托管activity处理的工作任务，任何打算托管目标Fragment
的activity都得实现它。
```

* ①在Fragment类中创建Callbacks接口，并声明一个接口的对象。

```java
private Callbacks mCallbacks;

public interface Callbacks {
    void onCrimeSelected(Crime crime);
}
```
* ②为mCallbacks赋值和注销,在fragment类中重写onAttach方法，和onDetach方法

```java
//在Fragment附加给activity的时候调用的
    @Override
    public void onAttach(Context context) {
        super.onAttach(context);
        mCallbacks = (Callbacks) context;
    }
//在Fragment销毁时调用
    @Override
       public void onDetach() {
           super.onDetach();
           mCallbacks = null;
       }
```

* ③在activity中实现接口和方法,(将方法选取的判断交给activity，使得Fragment不那么“具体”)

```java
@Override
    public void onCrimeSelected(Crime crime) {
        //判断是不是有detail_fragment_container，也就是说判断是不是平板
        //将两种方法打包
        if (findViewById(R.id.detail_fragment_container) == null) {
            Intent intent = CrimePagerActivity.newIntent(this, crime.getId());
            startActivity(intent);
        } else {
            Fragment newDetial = CrimeFragment.newInstance(crime.getId());

            getSupportFragmentManager().beginTransaction()
                    .replace(R.id.detail_fragment_container, newDetial)
                    .commit();
        }
    }
    ```
* ④如果在平板上，如何实现数据同时刷新？（右边改左边也改)

  ①在右边的Fragment类中添加接口和对象
  ```java
  private Callbacks mCallbacks;
      
  public interface Callbacks{
      void onCrimeUpdated(Crime crime);
    }
    ```
    ②在activity中实现接口与方法(注意：所有托管该Fragment的activity都必须实现接口，如果方法已经实现了，那么就实现一个空方法就行)
    ```java
    @Override
       public void onCrimeUpdated(Crime crime) {
           CrimeListFragment listFragment = (CrimeListFragment) getSupportFragmentManager().findFragmentById(R.id.fragment_container);
           listFragment.updateUI();
       }

    ```
    ③ 最后调用更新数据的方法
    ```java
    private void updateCrime() {
            CrimeLab.get(getActivity()).updateCrime(mCrime);
            mCallbacks.onCrimeUpdated(mCrime);
        }

    ```
