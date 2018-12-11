

### 主页

conf/routes

```txt
# Home page
GET     /                                       Application.index
*       /hello                                  Application.bilibili
```

### 自带数据库

```txt
conf/application.conf
H2 DBMS
# Database configuration
db.default=mem

然后类继承Model (play.db.jpa.)
加限制@Entity
```

```java
public static void index() {
    //存
    new User("1056992492@qq.com", "wang123", "ScorpioMiku", "1").save();
    new User("1056992492@qq.com", "1056992492@qq.com", "ScorpioMiku", "1").save();
    //查询 ， 第一参数："by" + 属性名,整体按驼峰式
    User test = User.find("byPassWord", "1056992492@qq.com").first();
    //多条件查询
    User test1 = User.find("byEmailAndPassWord", "1056992492@qq.com","wang123").first();
    System.out.println(test);
	//通过对象直接查找
    new Post("我是标题", bob).save();
    System.out.println(Post.count());
    List<Post> test = Post.find("byAuthor", bob).fetch();
    System.out.println(test.size());
    System.out.println(test.get(0));
    render();
}
```

### 单元测试

```txt
play test
http://localhost:9000/@tests
```

```java
package controllers;

import org.junit.Test;
import play.test.UnitTest;

public class BasicTest extends UnitTest {
    @Test
    public void test() {
        assertEquals(3, 1 + 1);
    }
}


/*
//
//希望执行每个单元测试函数前清空之前的测试数据
//@Before
//setup()
//Fixtures
public class BasicTest extends UnitTest {
@Before
    public void setup() {
        Fixtures.deleteAllModels();
    }
*/
```

### 大对象

```java
//large object    longtext
@Lob
private String content;

//large object   varchar(255)
private Blob photo;
```

