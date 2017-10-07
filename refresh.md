### Adapter部分
①首先是item_foot.xml（这个给你加了）是用来表示recyclerView最后一个item“正在加载”

②Adapter中添加以下方法
```java
@Override
    public int getItemViewType(int position) {
        if (position + 1 == getItemCount()) {
            return TYPE_FOOTER;
        } else {
            return TYPE_ITEM;
        }
    }
```

③修改Adapter中onBindViewHolder方法
```java
@Override
       public void onBindViewHolder(holder holder, int position) {
        //如果是最后一个item就不调用bindView
           if (position + 1 == getItemCount()) {

           } else {
               holder.bindView(position, mListFoodNames.get(position),mListFoodMetirals.get(position));
           }
       }
```
④修改Adapter中onCreateViewHolder方法
```java
@Override
       public holder onCreateViewHolder(ViewGroup parent, int viewType) {
           if (viewType == TYPE_ITEM) {
               View v = LayoutInflater.from(getContext()).inflate(R.layout
                       .recommend_default_recycler_view_item, parent, false);
               return new holder(v);
           } else if (viewType == TYPE_FOOTER) {
               View v = LayoutInflater.from(getContext()).inflate(R.layout
                       .item_foot, parent, false);
               return new holder(v);
           }
           return null;
       }

```
调用第二步的方法，如果是最后一个item就加载第一步创建的view

### 把更新的操作包装起来(为ArrayList添加数据和动态更新Adapter)

```java
private void getData() {
//这个判断是用来限制最多加载多少的
       if(mAdapter.getItemCount()>40){

       }else{
           for (int i = 0; i < 3; i++) {
           //这里面加扩大ArrayList的方法，也就是你网络获取数据就写这儿
               list.add("1");
           }
           //下面两个方法是观测Adapter是否更新，更新了就改变view
           mAdapter.notifyDataSetChanged();
    
           mAdapter.notifyItemRemoved(mAdapter.getItemCount());
       }
   }
```

### RecyclerView的初始化和事件处理
```java

//变量声明最好放到最前面，以便后面在其他方法里调用
private LinearLayoutManager mLinearLayoutManager;
private List<String> list = new ArrayList<>();
private Adapter mAdapter = new Adapter(list);
boolean isLoading;
private Handler handler = new Handler();
private static final int TYPE_ITEM = 0;
private static final int TYPE_FOOTER = 1;
 private RecyclerView mRecyclerView;



 
 mRecyclerView = (RecyclerView) v.findViewById(R.id.recommend_default_recycler_view);
 mLinearLayoutManager = new LinearLayoutManager(getContext());
mRecyclerView.setLayoutManager(mLinearLayoutManager);
mRecyclerView.setNestedScrollingEnabled(false);
mRecyclerView.setAdapter(mAdapter);

//检测recyclerView的滑动事件，在这里添加刷新事件处理
mRecyclerView.addOnScrollListener(new RecyclerView.OnScrollListener() {
    @Override
    public void onScrollStateChanged(RecyclerView recyclerView, int newState) {
        super.onScrollStateChanged(recyclerView, newState);
        Log.d("test", "StateChanged = " + newState);
    }

    @Override
    public void onScrolled(RecyclerView recyclerView, int dx, int dy) {
        super.onScrolled(recyclerView, dx, dy);
        Log.d("test", "在滑动");
        int lastVisibleItemPosition = mLinearLayoutManager.findLastVisibleItemPosition();
        Log.d("test", "onScrolled:最后一个可见的位子 " + lastVisibleItemPosition);
        Log.d("test", "onScrolled: adapter" + mAdapter.getItemCount());
        if (lastVisibleItemPosition + 1 == mAdapter.getItemCount()) {
            Log.d("test", "loading executed在加载新的");

        
            if (!isLoading) {
                isLoading = true;
                //开辟新的线程来刷新
                handler.postDelayed(new Runnable() {
                    @Override
                    public void run() {
                        getData();
                        Log.d("test", "load more completed");
                        isLoading = false;
                    }
                }, 1000);
            }
        }
    }
});
```


### 整体代码
```java
package com.scorpiomiku.cookbook.recommend;

import android.content.Intent;
import android.os.Bundle;
import android.os.Handler;
import android.support.annotation.Nullable;
import android.support.v4.widget.SwipeRefreshLayout;
import android.support.v7.widget.GridLayoutManager;
import android.support.v7.widget.LinearLayoutManager;
import android.support.v7.widget.RecyclerView;
import android.util.Log;
import android.view.LayoutInflater;
import android.view.View;
import android.view.ViewGroup;
import android.widget.ImageButton;
import android.widget.ImageView;
import android.widget.TextView;
import android.widget.Toast;

import com.scorpiomiku.cookbook.R;
import com.scorpiomiku.cookbook.menuactivity.MenuActivity;
import com.scorpiomiku.cookbook.module.FragmentModule;

import java.util.ArrayList;
import java.util.List;

/**
 * Created by Administrator on 2017/6/5.
 */

public class RecommendDefultFragment extends FragmentModule {

    private LinearLayoutManager mLinearLayoutManager;

    private List<String> list = new ArrayList<>();

    private Adapter mAdapter = new Adapter(list);
    boolean isLoading;
    private Handler handler = new Handler();
    private static final int TYPE_ITEM = 0;
    private static final int TYPE_FOOTER = 1;



    public static RecommendDefultFragment newInstance() {
        return new RecommendDefultFragment();
    }

    private RecyclerView mRecyclerView;


    @Override
    public void onCreate(@Nullable Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
    }

    @Nullable
    @Override
    public View onCreateView(LayoutInflater inflater, @Nullable ViewGroup container, @Nullable Bundle savedInstanceState) {
        View v = inflater.inflate(R.layout.recommend_default_fragment_layout, container, false);
        mRecyclerView = (RecyclerView) v.findViewById(R.id.recommend_default_recycler_view);
        mRecyclerView.setLayoutManager(mLinearLayoutManager);
        mRecyclerView.setNestedScrollingEnabled(false);
        initData();
        setRefresh();
        mRecyclerView.setAdapter(mAdapter);
        return v;
    }

    /*-------------------------------------holder------------------------------*/
    private class holder extends RecyclerView.ViewHolder implements View.OnClickListener {
        private ImageView mImageView;
        private TextView mFoodNameTextView;
        private TextView mFoodMatirialTextView;
        private View mWholeView;

        public holder(View itemView) {
            super(itemView);
            mWholeView = itemView;
            mImageView = (ImageView) itemView.findViewById(R.id
                    .recommend_default_item_image_button);
            mFoodMatirialTextView = (TextView) itemView.findViewById(R.id
                    .recommend_default_item_food_matirial_text_view);
            mFoodNameTextView = (TextView) itemView.findViewById(R.id
                    .recommend_default_item_food_name_text_view);
        }

        private void bindView(int i) {

            mWholeView.setOnClickListener(this);
        }

        @Override
        public void onClick(View v) {
            Intent i = new Intent(getActivity(), MenuActivity.class);
            startActivity(i);
        }
    }

    /*-----------------------------------------adapter--------------------------*/
    private class Adapter extends RecyclerView.Adapter<holder> {
        List<String> mStringList;

        public Adapter(List<String> list) {
            mStringList = list;
  
        }

        @Override
        public holder onCreateViewHolder(ViewGroup parent, int viewType) {
            if (viewType == TYPE_ITEM) {
                View v = LayoutInflater.from(getContext()).inflate(R.layout
                        .recommend_default_recycler_view_item, parent, false);
                return new holder(v);
            } else if (viewType == TYPE_FOOTER) {
                View v = LayoutInflater.from(getContext()).inflate(R.layout
                        .item_foot, parent, false);
                return new holder(v);
            }
            return null;
        }

        @Override
        public void onBindViewHolder(holder holder, int position) {

            if (position + 1 == getItemCount()) {

            } else {
                holder.bindView(position);
            }
        }


        @Override
        public int getItemCount() {
            return mStringList.size();
        }

        @Override
        public int getItemViewType(int position) {
            if (position + 1 == getItemCount()) {
                return TYPE_FOOTER;
            } else {
                return TYPE_ITEM;
            }
        }
    }

    private void initData() {
        handler.postDelayed(new Runnable() {
            @Override
            public void run() {
                getData();
            }
        }, 1000);
    }

    private void getData() {
        if (mAdapter.getItemCount() > 40) {

        } else {
            for (int i = 0; i < 6; i++) {
                list.add("1");
                mListFoodNames.add("1");
                mListFoodMetirals.add("1");
            }
            mAdapter.notifyDataSetChanged();
            //RecommendFragment.mSwipeRefreshLayout.setRefreshing(false);
            mAdapter.notifyItemRemoved(mAdapter.getItemCount());
        }
    }

    private void setRefresh() {
        /*RecommendFragment.mSwipeRefreshLayout.setColorSchemeResources(R.color.toolbar_and_menu_color);
        RecommendFragment.mSwipeRefreshLayout.post(new Runnable() {
            @Override
            public void run() {
                RecommendFragment.mSwipeRefreshLayout.setRefreshing(true);
            }
        });
        RecommendFragment.mSwipeRefreshLayout.setOnRefreshListener(new SwipeRefreshLayout.OnRefreshListener() {
            @Override
            public void onRefresh() {
                handler.postDelayed(new Runnable() {
                    @Override
                    public void run() {
                        Log.d(TAG, "run: clear");
                        list.clear();
                        getData();
                    }
                }, 2000);
            }
        });*/
        mLinearLayoutManager = new LinearLayoutManager(getContext());
        mRecyclerView.setLayoutManager(mLinearLayoutManager);
        mRecyclerView.setNestedScrollingEnabled(false);
        mRecyclerView.setAdapter(mAdapter);
        mRecyclerView.addOnScrollListener(new RecyclerView.OnScrollListener() {
            @Override
            public void onScrollStateChanged(RecyclerView recyclerView, int newState) {
                super.onScrollStateChanged(recyclerView, newState);
                Log.d("test", "StateChanged = " + newState);
            }

            @Override
            public void onScrolled(RecyclerView recyclerView, int dx, int dy) {
                super.onScrolled(recyclerView, dx, dy);
                Log.d("test", "在滑动");
                int lastVisibleItemPosition = mLinearLayoutManager.findLastVisibleItemPosition();
                Log.d("test", "onScrolled:最后一个可见的位子 " + lastVisibleItemPosition);
                Log.d("test", "onScrolled: adapter" + mAdapter.getItemCount());
                if (lastVisibleItemPosition + 1 == mAdapter.getItemCount()) {
                    Log.d("test", "loading executed在加载新的");

                    /*boolean isRefreshing = RecommendFragment.mSwipeRefreshLayout.isRefreshing();
                    if (isRefreshing) {
                        mAdapter.notifyItemRemoved(mAdapter.getItemCount());
                        return;
                    }*/
                    if (!isLoading) {
                        isLoading = true;
                        handler.postDelayed(new Runnable() {
                            @Override
                            public void run() {
                                getData();
                                Log.d("test", "load more completed");
                                isLoading = false;
                            }
                        }, 1000);
                    }
                }
            }
        });
    }
}

```
