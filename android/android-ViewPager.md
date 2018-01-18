### ViewPager的使用
```txt
ViewPager类似于RecyclerView，也是一种布局文件，内部使用Fragment填充
```

```android
public class CrimePagerActivity extends FragmentActivity {
    private ViewPager mViewPager;
    private static final String EXTRA_CRIME_ID = "com.scorpiomiku.criminalintent.crime_id";
    private List<Crime> mCrimes;

    public static Intent newIntent(Context packageContext, UUID crimeId) {
        Intent intent = new Intent(packageContext, CrimePagerActivity.class);
        intent.putExtra(EXTRA_CRIME_ID, crimeId);
        return intent;
    }

    @Override
    protected void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        setContentView(R.layout.activity_crime_pager);

        mViewPager = (ViewPager) findViewById(R.id.activity_crime_pager_view_pager);//获取该控件
        mCrimes = CrimeLab.get(this).getCrimes();


        FragmentManager fragmentManager = getSupportFragmentManager();  //得到manager

        //为ViewPager设置专用的Adapter，内部要实现两个方法（一个方法是获取item，一个是获取item数量）
        mViewPager.setAdapter(new FragmentStatePagerAdapter(fragmentManager) {
            @Override
            public Fragment getItem(int position) {
              //获取当前的Fragment
                Crime crime = mCrimes.get(position);  
                return CrimeFragment.newInstance(crime.getId());
            }

            @Override
            public int getCount() {
                return mCrimes.size();
            }
        });
        UUID crimeId = (UUID) getIntent().getSerializableExtra(EXTRA_CRIME_ID);

        //设置ViewPager的初始位子。调用setCurrentItem() 
        for (int i = 0; i < mCrimes.size(); i++){
            if(mCrimes.get(i).getId().equals(crimeId)){
                mViewPager.setCurrentItem(i);
                break;
            }
        }
    }
}
```
