### 网络信息解析和JSON数据解析以及后台任务

* #### 网络数据解析
  ①首先获得一个URL对象,该对象是由“网址得来”
  ```java
  public byte[] getUrlBytes(String urlSpec) throws IOException {
        URL url = new URL(urlSpec);
    }
  ```
  ②不同的URL对象对应着不同的URLConnection对象来处理, httpURL 都是由HttpURLConnection对象来处理
  ```java
  HttpURLConnection connection = (HttpURLConnection) url.openConnection();
  ```
  ③得到输出/入流
  ```java
  ByteArrayOutputStream out = new ByteArrayOutputStream();
  InputStream in = connection.getInputStream();  //输入流由connection来获取
  ```
  ④从输入流中获取数据，填充到输出流中
  ```java
  int bytesRead = 0;
  byte[] buffer = new byte[1024];
  //in.read(byte[] b ) ;    从in中最多读取byte.length个字节
  while ((bytesRead = in.read(buffer)) > 0) {
        out.write(buffer, 0, bytesRead);
  }
  out.close();
  out.toByteArray();//得到想要的byte[]
  ```
  ⑤关闭connection
  ```java
  connection.disconnect();
  ```
  整体代码为
  ```java
  public byte[] getUrlBytes(String urlSpec) throws IOException {
        URL url = new URL(urlSpec);
        HttpURLConnection connection = (HttpURLConnection) url.openConnection();
        try {
            ByteArrayOutputStream out = new ByteArrayOutputStream();
            InputStream in = connection.getInputStream();

            if (connection.getResponseCode() != HttpURLConnection.HTTP_OK) {
                throw new IOException(connection.getResponseMessage()
                        + ":with" + urlSpec);
            }
            int bytesRead = 0;
            byte[] buffer = new byte[1024];
            //in.read(byte[] b ) ;    从in中最多读取byte.length个字节
            while ((bytesRead = in.read(buffer)) > 0) {
                out.write(buffer, 0, bytesRead);
            }
            out.close();
            return out.toByteArray();
        } finally {
            connection.disconnect();
        }
    }
    
    //将得到的byte[]转换为字符串最终得到解析后的url
    public String getUrlString(String urlSpec) throws IOException {
        return new String(getUrlBytes(urlSpec));
    }
  ```

* #### JSON数据的获取与解析
  ①获取解析后的url(用上述方法)
  ```java
  String url = Uri.parse("http://api.flickr.com/services/rest/")
                      .buildUpon()
                      .appendQueryParameter("method", "flickr.photos.getRecent")
                      .appendQueryParameter("api_key", API_KEY)
                      .appendQueryParameter("format", "json")
                      .appendQueryParameter("nojsoncallback", "1")
                      .appendQueryParameter("extras", "url_s")
                      .build() + "";
  String jsonString = getUrlString(url);
  ```
  ②创建解析后得到的数据的对象类
  ```java
  public class GalleryItem {
    private String mCaption;
    private String mId;
    private String mUrl;

    public void setCaption(String caption) {
        mCaption = caption;
    }

    public void setId(String id) {
        mId = id;
    }

    public void setUrl(String url) {
        mUrl = url;
    }

    public String getCaption() {

        return mCaption;
    }

    public String getId() {
        return mId;
    }

    public String getUrl() {
        return mUrl;
    }

    @Override
    public String toString() {
        return mCaption;
    }
  }
  ```
  然后通过提供的专用对象来处理与解析JSON数据
  
  ③首先是得到JSONObject类对象
  
  个人理解该对象有多种内容形式--下面会逐一遇到
  
  ```java
  JSONObject jsonBody = new JSONObject(jsonString);  //首先是一个从解析后的url数据得到的一个“广泛”的对象的集合（不止包涵图片）
  ```
  ④通过上述得到的jsonBody集合得到一个目标数据的集合（注意上面是对象的集合，比如一个照片他有图片和名字还有大小等信息，此处获得的是对象集合的每个对象的   信息的集合）
  ```java
  JSONObject photosJsonObject = jsonBody.getJSONObject("photos");//得到photo信息集合
  ```
  ⑤再由photo信息集合得到一个数组，并通过数组获得一个目标对象的信息
  ```java
  JSONArray photoJsonArray = photosJsonObject.getJSONArray("photo");

  for (int i = 0; i < photoJsonArray.length(); i++) {
            //由数组得到个体
            JSONObject photoJsonObject = photoJsonArray.getJSONObject(i);

            GalleryItem item = new GalleryItem();
            item.setId(photoJsonObject.getString("id"));
            item.setCaption(photoJsonObject.getString("title"));

            if (!photoJsonObject.has("url_s")) {
                continue;
            }
            item.setUrl(photoJsonObject.getString("url_s"));
        }
  ```

  整体代码为
  ```java
  private void parseItems(List<GalleryItem> items, JSONObject jsonBody) throws IOException, JSONException {

        //jsonBody是一个JSONObject对象的集合
        JSONObject photosJsonObject = jsonBody.getJSONObject("photos");
        //由集合得到一个数组
        JSONArray photoJsonArray = photosJsonObject.getJSONArray("photo");
        for (int i = 0; i < photoJsonArray.length(); i++) {
            //由数组得到个体
            JSONObject photoJsonObject = photoJsonArray.getJSONObject(i);

            GalleryItem item = new GalleryItem();
            item.setId(photoJsonObject.getString("id"));
            item.setCaption(photoJsonObject.getString("title"));

            if (!photoJsonObject.has("url_s")) {
                continue;
            }
            item.setUrl(photoJsonObject.getString("url_s"));
            items.add(item);
        }
    }
  ```

* #### 再谈谈线程开辟用来加载网络信息，因为加载网络需要“等”，所以绝对不能用主线程来跑，参考书上的“闪电侠解释”
```java
private class FetchItemsTask extends AsyncTask<Void, Void, List<GalleryItem>> {

      //每次就调用这两个方法
      
      //后台加载数据
      @Override
      protected List<GalleryItem> doInBackground(Void... params) {
//            new FlickrFetchr().fetchItems();  //获得List ，用来加载recyclerView ， 不必在意
//            return new FlickrFetchr().fetchItems();
          return null ;
      }
      
      //主线程中更新UI , 如果在后台更新ui容易冲突
      @Override
       protected void onPostExecute(List<GalleryItem> galleryItems) {
           mItems = galleryItems;
           setupAdapter();
       }
}
```
