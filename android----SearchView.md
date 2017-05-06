### SearchView
 #### ①添加menu包

#### ② 添加View

```xml
<?xml version="1.0" encoding="utf-8"?>
<menu xmlns:android="http://schemas.android.com/apk/res/android"
      xmlns:app="http://schemas.android.com/apk/res-auto">

    <item
        android:id="@+id/menu_item_search"
        android:title="@string/search"
        app:actionViewClass="android.support.v7.widget.SearchView"
        app:showAsAction="ifRoom"
        />

</menu>
```

#### ③ fragment的onCreate方法中设置mune可见
```java
@Override
   public void onCreate(@Nullable Bundle savedInstanceState) {
       super.onCreate(savedInstanceState);
       setHasOptionsMenu(true);
   }
```

#### ④在Fragment中获取menu的布局

```java
@Override
    public void onCreateOptionsMenu(Menu menu, MenuInflater inflater) {
        super.onCreateOptionsMenu(menu, inflater);
        inflater.inflate(R.menu.search_menu,menu);
    }
```

#### ⑤获取SearchView中的文字

```java
@Override
    public void onCreateOptionsMenu(Menu menu, MenuInflater inflater) {
        super.onCreateOptionsMenu(menu, inflater);
        inflater.inflate(R.menu.search_menu, menu);
        
        
        //先从菜单中取出MenuItem对象
        MenuItem searchItem = menu.findItem(R.id.menu_item_search);
        //然后通过item对象得到SearchView对象
        final SearchView searchView = (SearchView) searchItem.getActionView();

        searchView.setOnQueryTextListener(new SearchView.OnQueryTextListener() {

            //点击搜索后的操作
            @Override
            public boolean onQueryTextSubmit(String query) {
                Log.d(TAG, "onQueryTextSubmit: " + query);

                return true;
            }

            //字符串改变时的操作
            @Override
            public boolean onQueryTextChange(String newText) {
                Log.d(TAG, "onQueryTextChange: " + newText);
                return false;
            }
        });
    }
```
#### ⑥“记住”搜索记录---使用shared preferences数据储存

shared preferences是一个键值对仓库，可通过持久化储存保存数据

  ①新建一个类，用来进行保存管理操作，添加键值字符串
  ```java
  public class QueryPreferences {
    private static final String PREF_SEARCH_QUETY = "searchQuery";
  }

  ```
  ②封装一个得到shared preferences对象的方法
  ```java
  public static String getStoredQuery(Context context) {
        return PreferenceManager.getDefaultSharedPreferences(context).getString(PREF_SEARCH_QUETY, null);
    }
  ```
  ③再封装一个保存的方法
  ```java
  public static void setStoredQuery(Context context, String query){
        //通过一个editor对象来储存
        PreferenceManager.getDefaultSharedPreferences(context)
                .edit()
                .putString(PREF_SEARCH_QUETY,query)
                .apply();
    }
  ```
  ④在listener中调用setStoredQuery方法
  ```java
  @Override
          public boolean onQueryTextSubmit(String query) {
              Log.d(TAG, "onQueryTextSubmit: " + query);
              QueryPreferences.setStoredQuery(getActivity(),query);
              return true;
          }
  ```
  ⑤设置文本默认框显示已保存的信息
  ```java
  searchView.setOnClickListener(new View.OnClickListener() {
            @Override
            public void onClick(View v) {
                String query = QueryPreferences.getStoredQuery(getActivity());
                searchView.setQuery(query,false);
            }
        });
  ```

