# SQL

#### 建库：

* 方法1：

  右键数据库，然后点新建数据库

* 方法2：

```sql
CREATE DATABASE XSCJ
ON 
(
NAME='XSCJ1_Data', /*数据库名*/
FILENAME='E:\sqlclass\class1\XSCJ1.mdf', /*数据库保存路径*/
SIZE=5MB, /*数据库初始大小*/
MAXSIZE=50MB, /*数据库最大size*/
FILEGROWTH=10% /*数据库增长速率*/
)
LOG ON
(
NAME='XSCJ1_Log',   /*日志文件名*/
FILENAME='E:\sqlclass\class1\XSCJ1_Log.ldf', /*日志文件路径*/
SIZE=2MB, /*日志文件初始大小*/
MAXSIZE=5MB, /*日志文件最大size*/
FILEGROWTH=1MB /*日志文件增长速率*/
)
GO
```

#### 修改库属性

```sql
alter database BSXT
modify file
(
name = 'BSXT1_Data', /*欲修改的表名*/
MAXSIZE=UNLIMITED /*直接修改属性即可*/
);
go

```

#### 建表

* 方法1：

  鼠标右键

* 方法2：

```sql
/*新建表COURSE*/
CREATE TABLE COURSE
(
Cno CHAR(2) PRIMARY KEY,  /*课程号，并且设置为主键*/
Cname CHAR(10), /*课程名*/
Cpno CHAR(2), /*先行课*/
Ccredit CHAR(5) /*学分*/
)
/*新建表Student*/
create table student 
(
Sno char(10) not null primary key, /*设置主键*/
Sname char(10) not null,/*设置名字不能为空*/
Ssex char(10) check(Ssex='男' or Ssex='女'),
  					/*设置性别必须是男或女*/
Sclass char(10),
Stel char(11) not null,
Sgroup char(1) not null,
Spassword char(10) not null
);
/*新建表teacher*/
create table Teacher
(
Tno char(10) not null primary key, /*多属性描述直接写上就行*/
Tname char(10) not null unique,
Tsex char(2) check(Tsex='男' or Tsex='女'),
Tdept char(20) not null default'计算机科学与技术',/*设置默认*/
Tdegree char(8),
Ttitle char(10),
Tright BIT not null check(Tright = 0 or Tright = 1),
Ttel char not null,
Temail char(50),
Tgroup char(1) not null,
Tpassword char(10) not null
)
/*新建表毕设*/
create table Iteminfo
(
Hno char(4) not null primary key,
Hname char(50) not null,
Hstatus char(5) ,
dircetion char(200),
Tno char(10) references Teacher(Tno), /*外键声明*/
Sno char(10) references student(Sno)
)


```

#### 为已经建好的表增加一列

```sql
alter table Course ADD Csemester char(10) /*增加了一列学期属性*/
```

#### 为表中属性建立索引

```sql
/*普通索引*/
CREATE INDEX Cname_index 
ON COURSE(Cname)
/*唯一索引*/
CREATE UNIQUE INDEX Cname_index 
ON COURSE(Cname)

/*删除索引*/
DROP INDEX Course.Cname_index
```

#### 向表中添加元素

```sql
INSERT INTO Student VALUES('201215121','李勇','男',20,'CS')
```

#### 删除表

```sql
Drop table Course
```

#### 删除数据库

```sql
/*执行对象切换至master*/
Drop database XSCJ
```

#### 查询

```sql
SELECT * FROM ITEM  /*查询某表中所有元素以及其所有属性*/

/*查询student表中各元素的学号、名字、电话号码*/
SELECT Sno,Sname,Stel FROM student; 

/*信息匹配搜索查询,IS NULL 用来检索属性为空的情况*/
SELECT * FROM teacher WHERE Tname = '朱龙' or Tdegree = '博士' or Tdegree IS NULL;

/*去重复查询*/
SELECT DISTINCT Tno FROM ITEM;

/*模糊查询*/
SELECT * FROM student WHERE Sname LIKE '王%';

/*排序查询*/
SELECT * FROM ITEM ORDER BY Ino

/*计数查询*/
SELECT Tdegree,COUNT(Tdegree) 人数 FROM teacher GROUP BY Tdegree;   /*加上Tdegree用来做表时获得row的名，人数位置参数为col的名输出结果是:
博士    	2
硕士    	1
*/
```

