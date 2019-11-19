#### 如何开启项目

```cmd
scrapy startproject NAME
```

#### 新建爬虫

```cmd
scrapy genspider zbdx "http://www.nuc.edu.cn/"

```

#### 修改setting

```python
ROBOTSTXT_OBEY = False

DEFAULT_REQUEST_HEADERS = {
    'Accept': 'text/html,application/xhtml+xml,application/xml;q=0.9,*/*;q=0.8',
    'Accept-Language': 'en',
    'User-Agent': 'Mozilla/5.0 (Windows NT 10.0; Win64; x64) AppleWebKit/537.36 (KHTML, like Gecko) Chrome/77.0.3865.120 Safari/537.36'
}
```

#### 爬虫类

```python

```

#### 运行

```cmd
scrapy crawl zbdx
```

#### 数据存储

```python
class ZbdxSpider(scrapy.Spider):
    name = 'zbdx'
    # 限制爬虫范围
    allowed_domains = ['http://www.nuc.edu.cn/']
    start_urls = ['http://www.nuc.edu.cn/index/zbxw/1.htm']

    def parse(self, response):
        # pass
        lis = response.xpath("//div[@class='list_con_rightlist']/ul/li")
        for item in lis:
            t = str(item.xpath(".//a/text()").get()).strip()
            h = str(item.xpath(".//a/@href").get()).strip()
            infor = {"text": t, "link": h}

            # 返回给pipelines
            yield infor
            
            
# pipeline
import json
# 要让pipeline运行需要到setting设置
class FirstScrapyPipeline(object):
    def __init__(self):
        # 在构造函数中打开文件
        self.fp = open("data.json", "w", encoding='utf-8')

    def open_spider(self, spider):
        print("爬虫开始")

    def process_item(self, item, spider):
        # yield传过来是item
        item_json = json.dumps(item,ensure_ascii=False)
        self.fp.write(item_json + "\n")
        return item

    def close_spider(self, spider):
        self.fp.close()
        print("爬虫结束")
        
# setting
ITEM_PIPELINES = {
   'first_scrapy.pipelines.FirstScrapyPipeline': 300,
}
```

