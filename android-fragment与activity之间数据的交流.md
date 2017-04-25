### Fragment的复用性 

```txt
因为fragment是一个写好的“界面”，然后Fragment是放在Activity容器里面的一个东西，所以所谓的Fragment的复用性就是可以在不同的Activity中使用相同的fragment。换句话来说就是Fragment类中不能有具体的数据值，所有的值都直接或者间接从其他地方获得，类似于一个空的躯壳
```

### fragment中argument的使用与intent使用的区别

```txt
首先。例如RecyclerView的跳转，在跳转后我们需要在另一个Activity的Fragment中显示出上一个Activity的RecyclerView的item中的数据
```


* 使用Intent的步骤

  ①会在新的Activity中添加一个创建Intent的方法，为新活动中的Fragment传送这个ID，Intent键值放在新Activity中

  ```java
  private static final String EXTRA_CRIME_ID = "com.scorpiomiku.criminalintent.crime_id";

  public static Intent newIntent(Context packageContext, UUID crimeId) {
      Intent intent = new Intent(packageContext, CrimeActivity.class);
      intent.putExtra(EXTRA_CRIME_ID, crimeId);
      return intent;
  }
  ```
  ② 然后在RecyclerView的Fragment中调用这个方法，创建一个Intent
  ```java
  Intent intent = CrimeActivity.newIntent(getContext(), mCrime.getId());
  startActivity(intent);
  ```
  ③最后在新的Fragment中通过Activity的getIntent()方法获取数据
  ```java
  UUID crimeId = (UUID)getActivity().getIntent().getSerializable(CrimeActivity.EXTRA_CRIME_ID);//得到数据
  ```
可以看到，在该方法中新的Activity更像一个工作者，因为两个Fragment都是在Activity中调用方法来实现数据的传递，这样让Activity更加具体化（功能用的越多，越具体），让其失去了作为一个容器的本分（容器应该是少功能）

* 使用argument的步骤

  ①还是在新的Activity中添加一个创建Intent的方法，为新活动中的Fragment传送这个ID，Intent键值放在新Activity中（和Intent的一样）
  ```java
  private static final String EXTRA_CRIME_ID = "com.scorpiomiku.criminalintent.crime_id";

  public static Intent newIntent(Context packageContext, UUID crimeId) {
      Intent intent = new Intent(packageContext, CrimeActivity.class);
      intent.putExtra(EXTRA_CRIME_ID, crimeId);
      return intent;
  }
  ```
  ②在新的Fragment类中添加一个argument的键值，和创建argument的封装方法
  ```java
  public static CrimeFragment newInstance(UUID crimeId) {
       Bundle args = new Bundle();
       args.putSerializable(ARG_CRIME_ID, crimeId);

       CrimeFragment crimeFragment = new CrimeFragment();
       crimeFragment.setArguments(args);
       return crimeFragment;
   }
   ```
   ③在RecyclerView的Fragment中调用这个方法，创建一个Intent
   ```java
   Intent intent = CrimeActivity.newIntent(getContext(), mCrime.getId());
   startActivity(intent);
   ```
   
  ④然后在新的Activity中调用newInstance方法，创建出Fragment---因为argument是通过bundle传送的，bundle是在Activity和Fragment之间传送信息的，所以需要在Activity中创建Fragment，并且在创建的时候为bundle“赋值”（调用Fragment的方法）
  ```java
  @Override
   protected Fragment createFragment() {
       UUID crimeId = (UUID) getIntent().getSerializableExtra(EXTRA_CRIME_ID);  //先从Intent中获取ID，然后为bundle“赋值”
       return  CrimeFragment.newInstance(crimeId);
   }
   ```
   ⑤最后在Fragment中获取ID，信息成功传达
   ```java
    UUID crimeId = (UUID) getArguments().getSerializable(ARG_CRIME_ID);
    ```
可以发现，在使用argument的时候，Activity更多的充当的是一个管理者，它是通过姓名的传递来工作（类似于点名），而不是自己去获取啥的，这样让Activity更抽象，而不是更具体。增强Fragment在Activity中的复用性。
   

