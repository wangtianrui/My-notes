#### 字符串首字母大写
```c
#include<stdio.h>

int main()
{
	char string[50];
	char * str;
	int i  ;
	gets(string);
	printf("输入的是：");
	for(i = 0 ; i < strlen(string) ; i ++)
	{
		printf("%c",string[i]);
	}
	printf("\n");

	for(i = 0 ; i < strlen(string) ; i++ )
	{
		if(i == 0)
		{
			string[i] = string[i] - 32 ;
		}
		if(string[i] == ' ')
		{
			string[i+1] = string[i+1] - 32 ;
			printf("c");
		}
	}
	printf("输出是：") ;
	for(i = 0 ; i < strlen(string) ; i ++)
	{
		printf("%c",string[i]);
	}

	return 0 ;
}
```

#### 斐波那契
```c
#include<stdio.h>
//该方法可以输出指定位子的斐波那契数
int fibonacci(int n)
{
	if(n == 1 || n == 2)
	{
		return 1;
	}
	else
	{
		return fibonacci(n - 1) + fibonacci(n - 2);
	}
}

#include<stdio.h>
int main()
{
	int n, i;
	int f[100];
	f[0] = 1;
	f[1] = 1;
	for(i = 2; i < 20; i++)
	{
		f[i] = f[i - 1] + f[i - 2];
	}
	for(i = 0; i < 20; i++)
	{
		if(f[i]<=100)
		{
			printf("%d ", f[i]);
		}
	}
	printf("\n");
	return 0;
}
```

#### 输出边长为n的菱形
```c
int main()
{
	int n, i, j;
	while(scanf("%d", &n) == 1)
	{
		n = n - 1 ;
		for(i = 0; i < n; i++)
		{
			for(j = 0; j < 2 * n; j++)
			{
				if(j >= n - i && j <= n + i)
					printf("*");
				else
					printf(" ");
			}
			printf("\n");
		}
		for(i = n; i >= 0; i--)
		{
			for(j = 0; j <= 2 * n; j++)
			{
				if(j >= n - i && j <= n + i)
					printf("*");
				else
					printf(" ");
			}
			printf("\n");
		}
}
	return 0;

}
```

#### 矩阵对角线求和

```c
#include<stdio.h>

int main()
{
	int len ;
	int num[20][20];
	int i , j , sum = 0;
	printf("输入数组边长:\n");
	scanf("%d",&len);
	for(i = 0 ; i < len ; i++)
	{
		for(j = 0 ; j < len ; j++)
		{
			num[i][j] = i * j + i + j + 1 ; //赋值随便写的
		}
	}

	for(i = 0 ; i < len ; i++)
	{
		for(j = 0 ; j < len ; j++)
		{
			if(i == j)
			{
				sum = sum + num[i][j];
			}
			if(len - i == j + 1)
			{
				sum = sum + num[i][j];
			}
		}
	}
	if(len % 2 == 1)
	{
		sum = sum - num[len/2][len/2];
	}
	for(i = 0 ; i < len ; i++)
	{
		for(j = 0 ; j < len ; j++)
		{
			printf("%3d",num[i][j]);  //%nd可规定输出的所占的空间为n
		}

		printf("\n");
	}
	printf("%d",sum);
	return 0 ;
}
```

#### 矩阵乘法
```c
#include<stdio.h>

int main()
{
	int a[2][5] ={1,3,
				  5,7,
				  8,2,
				  2,2,
				  6,9},

 		b[5][2] ={3,5,2,6,8,
		          4,8,4,5,8},
		c[2][2] ;
	int i, j, k;
    int temp;
    for(i = 0; i < 2; i++){
        for(j = 0; j < 2; j++){
            temp = 0;
            for(k = 0; k < 5; k++){
                temp = temp + a[i][k] * b[k][j];
            }
            c[i][j] = temp;
            printf("%3d ", c[i][j]);
        }
        printf("\n");
    }
	return 0 ;
}
```

#### 猴子吃桃

```c
#include<stdio.h>
void main()
{
	int day , x1 , x2 ;
	day = 9;
	x2 = 1;
	while( day > 0 )
	{
		x1 = ( x2 + 1 ) * 2; //第一天的桃子数是第2天桃子数加1后的2倍
		x2 = x1;
		day--;
	}
	printf("the total is %d\n",x1);
}
```

#### 非0数前移(优化后的方法,执行循环次数减少)

```c
#include<stdio.h>
int main()
{
	int num[50];
	int size , i , j;
	printf("输入数组大小：\n");
	scanf("%d", &size);
	printf("请输入%d个数：",size);
	for(i = 0 ; i < size ; i ++)
	{
		scanf("%d",&num[i]);
	}
	for(i = 0 , j = size - 1 ; i < j ;)
	{
		if(num[i]==0 && num[j]!= 0)
		{
			num[i] = num[j];
			num[j] = 0;
			i ++ ;
			j -- ;
		}
		if(num[i] != 0)
		{
			i++ ;
		}
		if(num[i] == 0 && num[j] == 0)
		{
			j -- ;
		}

	}
	for(i = 0 ; i < size ; i ++)
	{
		printf("%4d ",num[i]);
	}

	return 0;
}
```

#### 杨辉三角
```c
#include<stdio.h>
int main()
{
	int yh[100][100];
	int i, j, index;
	while(scanf("%d", &index) != EOF)
	{
		for(i = 0; i < index; i++)
		{
			yh[i][0] = 1;
			yh[i][i] = 1;
		}
		for(i = 0; i < index; i++)
		{
			for(j = 0; j < index - i; j++)
			{
				printf(" ");
			}
			for(j = 0; j <= i; j++)
			{
				if(i == j)
				{
					printf("%2d ", yh[i][i]);
				}
				else if(j == 0)
				{
					printf("%2d ", yh[i][j]);
				}
				else
				{
					yh[i][j] = yh[i - 1][j - 1] + yh[i - 1][j];		/*o?D?*/
					printf("%2d ", yh[i][j]);
				}
			}
			printf("\n");
		}
	}
	return 0;
}
```
