```txt

//将当前文件夹改编成仓库
  git init


//添加文件到仓库（文件修改后也用这个）
   git add readme.txt


//提交并备注
  git commit -m "wrote a readme file"
  

//查看当前仓库状态
  git status

  
//查看文档改变了什么 
  git diff readme.txt 


//恢复到上次提交
  git reset --hard HEAD 


//恢复到某次提交
  git reset --hard (commit id)


//在提交前想撤销修改
  git checkout -- test.java
//git checkout -- file命令中的--很重要，没有--，就变成了“切换到另一个分支”的命令，我们在后面的分支管理中会再次遇到git checkout命令。


//把add后的修改了的部分撤销
  git reset HEAD test.java


//将仓库中的文件删除
   rm test.txt    ->     git commit -m"1"
   git checkout -- test.txt   //撤销删除


//将本地git托管到github
①在github创建新的repository，然后再在目标目录下使用github上的指令（第二个）


//从github克隆仓库
  git clone 目标.git
  例：git clone https://github.com/wangtianrui/gitCloneTest.git

```
* #### 分支开发

>只有主支
>
>![alt text](https://www.liaoxuefeng.com/files/attachments/0013849087937492135fbf4bbd24dfcbc18349a8a59d36d000/0)


>添加分支 

>git checkout -b dev   添加分支并切换过去此命令等价于 git branch dev然后git checkout dev
>![alt text](https://www.liaoxuefeng.com/files/attachments/001384908811773187a597e2d844eefb11f5cf5d56135ca000/0)


>分支与主支的指针是互不影响的
>git branch 查看当前分支
![alt text](https://www.liaoxuefeng.com/files/attachments/0013849088235627813efe7649b4f008900e5365bb72323000/0)
>
>![alt text](https://www.liaoxuefeng.com/files/attachments/00138490883510324231a837e5d4aee844d3e4692ba50f5000/0)

>git merge dev 合并分支（切换回主支再用）

>git branch -d dev 删除分支



* 信息查看

```git
git config --list  //查看已设置信息
git config --global --list //查看全局属性的信息

git remote add origin http://git.......... //远程连接
```

