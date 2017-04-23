## 在fragment中使用RecyclerView

* #### 首先是添加依赖

* #### 然后在布局文件中创建出RecyclerView的布局
```xmlns
<?xml version="1.0" encoding="utf-8"?>
<android.support.v7.widget.RecyclerView
    xmlns:android="http://schemas.android.com/apk/res/android"
    android:layout_width="match_parent"
    android:layout_height="match_parent"
    android:id="@+id/crime_recycler_view">
</android.support.v7.widget.RecyclerView>
```

* #### 新建一个Adapter类，继承自RecyclerView.Adapter<一个ViewHolder对象>

* 类中有三个抽象方法需要实现

 ①onCreateViewHolder-----用来获取每个list的view，并用该view创建一个ViewHolder对象
 ```java
 @Override
        public CrimeHolder onCreateViewHolder(ViewGroup parent, int viewType) {
            LayoutInflater layoutInflater = LayoutInflater.from(getActivity());
            View view = layoutInflater.inflate(android.R.layout.simple_list_item_1, parent, false);
            return new CrimeHolder(view);
        }
```
②onBindViewHolder----用来“绑定”数据，也就是填充数据
```java
@Override
        public void onBindViewHolder(CrimeHolder holder, int position) {
            Crime crime = mCrimes.get(position);
            holder.mTitleTextView.setText(crime.getTitle());
        }
```
③getItemCount----用来得到List大小
```java
@Override
       public int getItemCount() {
           return mCrimes.size();
       }
```
* 整体代码为
```java
private class CrimeAdapter extends RecyclerView.Adapter<CrimeHolder> {
        private List<Crime> mCrimes;

        public CrimeAdapter(List<Crime> crimes) {
            mCrimes = crimes;
        }

        @Override
        public CrimeHolder onCreateViewHolder(ViewGroup parent, int viewType) {
            LayoutInflater layoutInflater = LayoutInflater.from(getActivity());
            View view = layoutInflater.inflate(android.R.layout.simple_list_item_1, parent, false);
            return new CrimeHolder(view);
        }

        @Override
        public void onBindViewHolder(CrimeHolder holder, int position) {
            Crime crime = mCrimes.get(position);
            holder.mTitleTextView.setText(crime.getTitle());
        }

        @Override
        public int getItemCount() {
            return mCrimes.size();
        }
    }
```

* #### Adapter类创建好后，需要在fragment中实例化它，并且将fragment中的RecyclerView与Adater绑定
```java
private RecyclerView mCrimeRecyclerView;
    private CrimeAdapter mAdapter;

    @Nullable
    @Override
    public View onCreateView(LayoutInflater inflater, @Nullable ViewGroup container, @Nullable Bundle savedInstanceState) {
        View view = inflater.inflate(R.layout.fragment_crime_list, container, false);
        mCrimeRecyclerView = (RecyclerView) view.findViewById(R.id.crime_recycler_view);
        mCrimeRecyclerView.setLayoutManager(new LinearLayoutManager(getActivity()));
        updateUI();
        return view;
    }

    private void updateUI(){
        CrimeLab crimeLab = CrimeLab.get(getActivity());   //得到List中的对象的实例化
        List<Crime>crimes = crimeLab.getCrimes();   //得到List
        mAdapter=new CrimeAdapter(crimes);  //实例化Adapter
        mCrimeRecyclerView.setAdapter(mAdapter); //将RecyclerView和Adapter绑定
    }
```
