### tensorflow移植安卓

#### machineLearning方面
①在PC上训练好模型,注意这里要记住输入和输出的name

```python
x = tf.constant([[3., 3.]], name='input')
y = tf.add(matrix1, matrix1, name='output')
```

②在模型训练代码末尾添加pb文件保存代码

```python
with tf.gfile.FastGFile('D:/python_code/test/test.pb', mode='wb') as f:
    f.write(output_graph_def.SerializeToString())
```

③用txt文件保存一个Labels.txt
　
#### so文件和jar文件编译(此操作需要Linux系统)
一、bazel安装

```txt
bazel的安装，比较简单，可以直接参考官方文档https://bazel.build/versions/master/docs/install.html ，但值
得注意的是，bazel目前还不支持在window上构建android，官方说的是后期可以支持gradle。
```
①需要JDK 8，如果没安装请使用终端运行
```txt
sudo apt-get install openjdk-8-jdk
```
②添加APT库
```txt
echo "deb [arch=amd64] http://storage.googleapis.com/bazel-apt stable jdk1.8" | sudo tee /etc/apt/sources.list.d/bazel.list`
curl https://bazel.build/bazel-release.pub.gpg | sudo apt-key add -
```
③安装bazel
```txt
sudo apt-get update && sudo apt-get install bazel
```
二、使用bazel编译出so和jar文件(该点的操作都是在tensorflow文件夹里打开终端进行)

①so库：
```txt
bazel build -c opt //tensorflow/contrib/android:libtensorflow_inference.so \
    --crosstool_top=//external:android/crosstool \
    --host_crosstool_top=@bazel_tools//tools/cpp:toolchain \
    --cpu=armeabi-v7a

编译完毕后，libtensorflow_inference.so的路径为： 
/tensorflow/bazel-bin/tensorflow/contrib/android
```
②jar包
```txt
bazel build //tensorflow/contrib/android:android_tensorflow_inference_java

编译完毕后，android_tensorflow_inference_java.jar的路径为： 
/tensorflow/bazel-bin/tensorflow/contrib/android
```

#### android方面

①新建项目

②新建assets文件夹，并将pb文件和labels.txt文件放入

③将libandroid_tensorflow_inference_java.jar存放到/app/libs目录下，并且右键“add as Libary”

④在/app/libs下新建armeabi文件夹，并将libtensorflow_inference.so放进去

⑤app:gradle中android里面添加soureSets，用于制定jniLibs的路径
```xmln
sourceSets {
        main {
            jniLibs.srcDirs = ['libs']
        }
    }
```
⑥在gradle.properties中添加下面一行
```xmln
android.useDeprecatedNdk=true
```
⑦在gradle.properties中添加下面一行
```xmln
android.useDeprecatedNdk=true
```

###### 以上操作完成后就可以开始调用tensorflowAPI了
```txt
所有API都是通过class  TensorFlowInferenceInterface 调用
```
