### 隐式intent （以发送消息为例子）

 #### 是让程序自己发出Intent然后让系统自动检测能够响应这个intent的程序
 
* #### 第一类，简单的intent打开
 ① 创建Intent  (注意有些Intent响应是需要获取权限的)
 ```java
Intent i = new Intent(Intent.ACTION_SEND);
 ```
 
  ② 为Intent附加信息
  ```java
i.setType("text/plain");
i.putExtra(Intent.EXTRA_TEXT, getCrimeReport());
i.putExtra(Intent.EXTRA_SUBJECT, getString(R.string.crime_report_suspect));
  ```

  ③ start
  ```java
 startActivity(i);
  ```

* #### 第二类，需要返回信息的Intent打开(联系人，获取联系人信息)
① 创建Intent  (和第一类一样)
```java
Intent pickContact = new Intent(Intent.ACTION_PICK, ContactsContract.Contacts.CONTENT_URI);
```
② 打开
```java
startActivityForResult(pickContact, REQUEST_CONTACT);
```
③ 在OnActivityResult中响应（注意别把requestCode与resultCode搞混了）
```java
@Override
    public void onActivityResult(int requestCode, int resultCode, Intent data) {
      //必须判断的 。 将result与ok对比。 注意是result，也就是这个活动是否正确
        if (resultCode != Activity.RESULT_OK) {
            return;
        }
        //然后用requestCode来对比，查看详细的结果是什么。
        if (requestCode == REQUEST_DATE) {
            Date date = (Date) data.getSerializableExtra(DatePickerFragment.EXTRA_DATE);
            mCrime.setDate(date);
            updateDate();
        } else if (requestCode == REQUEST_CONTACT && data != null) {
            Log.d(TAG, "request is OK");
            Uri contactUri = data.getData();
            String[] queryFields = new String[]{
                    ContactsContract.Contacts.DISPLAY_NAME
            };
            Cursor c = getActivity().getContentResolver().query(contactUri, queryFields, null, null, null);

            try {
                if (c.getCount() == 0) {
                    return;
                }
                c.moveToFirst();
                String suspect = c.getString(0);
                mCrime.setSuspect(suspect);
                Log.d(TAG, suspect);
                mSuspectButton.setText(suspect);
            } finally {
                c.close();
            }
        }
    }
```
