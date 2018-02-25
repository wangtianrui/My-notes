#### 工程build.gradle导入
```java
buildscript {
    repositories {
        jcenter()
    }
    dependencies {
        classpath 'com.android.tools.build:gradle:2.3.0'
        //加入下面这段代码
        classpath 'com.jakewharton:butterknife-gradle-plugin:8.5.1'
    }
}

allprojects {
    repositories {
        jcenter()
    }
}

```

#### 项目build.gradle导入(app)

```java
dependencies {
    compile fileTree(dir: 'libs', include: ['*.jar'])

    compile 'com.android.support:appcompat-v7:25.2.0'

    //加入下面这两行代码
    compile 'com.jakewharton:butterknife:8.5.1'
    annotationProcessor 'com.jakewharton:butterknife-compiler:8.5.1'

}
```

#### 绑定
