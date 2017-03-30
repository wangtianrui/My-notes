## 全局const

```c++
const int b = 1 ;    //防止了define的“替换”的缺点
```

## 方法的重载

同个方法名可以有不同类型的参数和返回值

```c++
int max( int , int , int ) ;
float max(float , float , float ) ;
```

##  函数模版

自定义类型

```c++
#include<iostream>
using namespace std ;
template <typename T>  //注意后面不能加分号
T add ( T a , T b ,T c )   // 注意必须把返回的参数也写进来 ，也就是说涉及到的T类型的变量都必须在函数名中声明
{

	c = a + b ;
	return c ;
}
int main()
{
	int  a , b , c ;
	float d , e , f ;
	cin >> a >> b ;
	c = add( a , b , c ) ;
	cout << c << "这是int类型" << endl ;
	cin >> d >> e ;
	cout << add( d , e , f ) << "这是float类型" << endl ;
	return 0;
 }
 ```
## 含默认参数的函数

```c++
float fun( float t = 6.7 )
{
  return 6.5 + t ;
}

int main()
{
  fun() ;  // 相当于fun( 6.7 ) ;
  fun( 7.8 ) // 得到的t是7.8而不是6.7 ;
  return 0 ;
}
```
## 变量的引用
相当于别名
```c++
int a = 1 ;
int &b = a ;//b的地址数值全部都和a相同 , 引用不是独立的变量，系统不会给他赋予储存空间
```
* 用于方法中（实参形参双向）

```c++
#include<iostream>
using namespace std ;
void fun( int &a , int &b )
{
	int c ;
	c = a ;
	a = b ;
	b = c ;
}
int main()
{

	int numA = 1 , numB = 2 ;
	fun( numA , numB ) ;
	cout << numA << endl << numB << endl ;
	return 0 ;
 }
 ```
 * 不能建立空引用，不能建立引用数组，可以建立指针的引用，在写引用前必须明确变量的值，可以用const修饰

 ## 内置函数
 将函数代码直接嵌入到主函数中,在一些函数被多次使用的时候可以提高程序运行速度

```c++
#include<iostream>
using namespace std ;
inline void fun( int &a , int &b )
{
	int c ;
	c = a ;
	a = b ;
	b = c ;
}
int main()
{

	int numA = 1 , numB = 2 ;
	fun( numA , numB ) ;
	cout << numA << endl << numB << endl ;
	return 0 ;
 }
 ```
 上述代码相当于
 ```c++
 #include<iostream>
using namespace std ;

int main()
{

	int numA = 1 , numB = 2 ;
	int c ;
	c = a ;
	a = b ;
	b = c ;
	cout << numA << endl << numB << endl ;
	return 0 ;
 }
 ```
 ## 作用域运算符

 ```c++
 #include<iostream>
using namespace std ;
float a = 3.5 ;
int main()
{
	int a = 1 ;
	cout << a << "这是内部的" << endl ;
	cout << ::a << "这是全局作用域的" << endl ;
	return 0 ;
 } 
 ```
## C++中的new和delete方法

* new 方法是分配一个空间,并且返回一个指向该空间的指针
```c++
new int ; 
new int(100) ;  //开辟一个int空间并将其赋值为100 ；
new cha[10] ;
float *p = new float(1.1);
```
* delete方法是释放该指针指向的区域
```c++
delete p ; //注意没有括号
```

## 运算符的重载

* 主要格式为 类名 operator 符号 (类名 对象名) ; 并且必须写在类的内部,否则无法访问private成员

* 注意：不能重载的运算符有: . (成员访问符)  . * （成员指针访问符）:: （域运算符）sizeof （长度运算符）?: (条件运算符)

* 运算符的作用是根据上下文来自动选择的

```c++
#include<iostream>
using namespace std ;
class Complex
{
	private:
		int real ;
		int imag ;
		
	public:
		Complex( int real1 , int imag1 )
		{
			real = real1 ;
			imag = imag1 ;
		}
		Complex ()
		{
			real = 1 ;
			imag = 2 ;
		}
		Complex operator + ( Complex &c2 )
		{
			Complex c = Complex( 0 , 0 );
			c.imag = imag + c2.imag ;
			c.real = real + c2.real ;
			return c ;
		}
		void show()
		{
			cout << "(" << real << "," << imag << ")" << endl ;
		}
};

int main( )
{
	Complex c1 = Complex( 1 , 2 ) ;
	Complex c2 = Complex( 2 , 3 ) ;
	Complex c3 = Complex( 3 , 4 ) ;
	c3 = c1 + c2 ;
	cout << "c1为"  ;
	c1.show() ;  
	cout << "c2为" ;
	c2.show() ;
	cout << "c3为" ;
	c3.show() ;
	return 0 ;
}
```

*  双目运算符的重载并且注意c++中cstring包和string包的区别

```c++
#include<iostream>
#include<cstring>  //cstring包中是对字符串的操作（比较、复制啥的） string（则是对string这一数据类型的一些自定义方法包含）
using namespace std ;
class String
{
	public :
		String()
		{
			p = NULL ;
		}
		String(char * str)
		{
			p = str ;
		}
		void display()
		{
			cout << p ;
		}
		friend bool operator > ( String &str1 , String &str2 ) ;
	
	private :
		char * p ;
};

bool operator > ( String &string1 , String &string2 ) 
{
	if( strcmp( string1.p , string2.p ) > 0 )
	{
		return true ;
	}
	else return false ;
}
int main( )
{
	String str1("Hello") , str2("World") ;
	cout << (str1 > str2) << endl ;
	return 0 ;
}

```

## 重载流提取运算符

* 注意流提取运算符是对流的操作 

```c++ 
#include<iostream>
using namespace std ;
class Complex 
{
	public :
		Complex( int real1 , int imag1 )
		{
			real = real1 ;
			imag = imag1 ;
		}
		Complex( )
		{
			real = 0 ;
			imag = 0 ;
		}
		friend ostream& operator << ( ostream& output, Complex& c ) ;  
		friend istream& operator >> ( istream& input , Complex& c ) ;
	private :
		int real ;
		int imag ;
};
ostream& operator << ( ostream& output, Complex& c ) 
{
	output << "(" << c.real << "," << c.imag << "i)" << endl ;
}
istream& operator >> ( istream& input , Complex& c )
{
	cout << "请分别输入实部和虚部" << endl ;
	input >> c.real >> c.imag ;
}
int main( )
{
	Complex c1 , c2 ;
	cin >> c1 >> c2 ;
	cout << "c1=" << c1 ;
	return 0 ;
}
```

## 不同数据类型的转换

* 隐式转换 

```c++
int i = 6 ;
i = 7.5 + 6 ;//先将6转换为double与7.5相加得到13.5然后将13.5转换为整型得到i ；
```

* 显式转换

```c++
int(89.5) ; //类型名(数据)
```
* 转换型构造函数

```c++
Complex(double r)
{
	real = r ; //将一种数据转换为一个对象中的数据
	imag = 0 ;
}
Complex( Student& s )
{
	real = s.score ;  //将一个类的对象转换为另一个类的对象
	imag = s.num ;
}
```
* 用类型转换函数进行类型的转换     格式为     operator 类型名()   {实现转换的语句}
* 注：该函数是自动使用的，系统在需要的时候自动调用，所以在类中写了该函数后可以直接将对象和数据相加减。

```c++
operator double()
{
	return real ; //返回一个double型变量，其值是Complex类中数据成员real的值。
}
```
```c++
#include<iostream>
using namespace std ;
class Complex 
{
	public :
		Complex( int real1 , int imag1 )
		{
			real = real1 ;
			imag = imag1 ;
		}
		Complex( )
		{
			real = 0 ;
			imag = 0 ;
		}
		operator int ()  //对int的重载函数 
		{
			return real ;
		}
	private :
		int real ;
		int imag ;
};

int main( )
{
	Complex c1(1 , 2) , c2(3 , 4);
	int d = 0 ;
	d = 2 + c1 ;
	cout << d << endl ;
	return 0 ;
}
```

