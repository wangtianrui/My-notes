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
