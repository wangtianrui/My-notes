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
#### 开辟三维数组
```c
#include<stdio.h>
int *** create(int lenth , int wide , int high)
{
    int i , j ;
    int *** p = ( int *** )malloc( high * sizeof(int**) );
	for( i = 0 ; i < high ; i ++)
	{
		p[i] = (int **)malloc( wide * sizeof(int*) ) ;
	}
	for( i = 0 ; i < high ; i ++)
   	{
   		for( j = 0 ; j < wide ; j ++)
     	{
            p[i][j] = (int *)malloc( lenth * sizeof(int) ) ;
		}
	}
	return p ;
}

int *** initData(int *** p ,int high ,int wide ,int lenth)
{
    int i , j , l ;
	for(i = 0 ; i < high ; i ++)
    {
        for(j = 0 ; j < wide ; j ++)
        {
            for( l = 0 ; l < lenth ; l ++ )
            {
                p[i][j][l] = i + j + l ;
            }
        }
    }
    return p ;
}

void show(int *** p ,int high ,int wide ,int lenth)
{
    int i , j , l ;
    for(i = 0 ; i < high ; i ++)
    {
        for(j = 0 ; j < wide ; j ++)
        {
            for( l = 0 ; l < lenth ; l ++ )
            {
                printf("%3d", p[i][j][l]);
            }
            printf("\n");
        }
         printf("\n");
    }
}

void deleteArray(int *** p ,int high ,int wide ,int lenth)
{
    int i , j ;
    for( i = 0 ; i < high ; i ++)
    {
       for( j = 0 ; j < wide ; j ++)
        {
            free(p[i][j]);
        }
    }
    for( i = 0 ; i < high ; i ++)
    {
        free(p[i]);
        free(p);
    }
}
int main()
{
	int i , j , l;
	int lenth , wide , high ;
	int *** p ;
	printf("输入长、宽、高:\n");
	scanf("%d%d%d",&lenth,&wide,&high);
	p = create(lenth,wide,high);
	p = initData(p,high,wide,lenth);
	show(p,high,wide,lenth);
	deleteArray(p,high,wide,lenth);
	//printf("%d",p[1][1][1]);
	return 0;
}

```

#### 链表倒序
```c
#include<stdio.h>

typedef struct listTest
{
    int num ;
    struct listTest *next ;
}mList;

mList * init()
{
    int i ;
    mList *head , *p , *temp;
    temp = (mList *)malloc(sizeof(mList));
    temp->num = 0 ;
    head = temp ;
    for(i = 1 ; i < 5 ; i++)
    {
        p = (mList *)malloc(sizeof(mList));
        p->num = i ;
        temp->next = p ;
        temp = p ;
    }
    temp->next = NULL ;
    return head ;
}

int showListMember(mList *head , int num)
{
    do
    {
        printf("%d\t",head->num);
        num = num + 1 ;
    }while(head = head->next);
    return num ;
}

void resersal(mList *head,int numOfList)
{
    mList *next , *prev = NULL ;
    int i ;
    for(i = 0 ; i < numOfList  ; i ++)
    {

      //printf("test:%d\t",head->num);
        next = head->next;
        //printf("test in:%d\t",head->num);
        head->next = prev;
        prev = head ;
        if(next == NULL)
        {

        }
        else
        {
             head = next ;
        }

    }
    printf("\n");
    do
    {
        printf("%d\t",head->num);

    }while(head = head->next);
}

int main()
{
    mList *head ;
    head = init();
    int numOfList = 0 , i ;
    numOfList = showListMember(head ,numOfList);
    resersal(head,numOfList);
    return 0 ;
}

```

#### 八个1排8x8，不同行同列（八皇后问题）
```c
#include <stdio.h>
#include <stdlib.h>
#define FALSE (1==0)
#define TRUE  (1==1)
#define SIZE 8

int eight_queen(char checkerboard[SIZE][SIZE], int sum);
int put_queen(char checkerboard[SIZE][SIZE], int row, int column);
int print(char checkerboard[SIZE][SIZE]);

int main(int argc, char *argv[])
 {
	char checkerboard[SIZE][SIZE];

	//init checkerboard
	int i, j;
	for(i = 0; i < SIZE; i++)
	{
		for(j = 0; j < SIZE; j++)
		{
			checkerboard[i][j]='-';
		}
	}
	eight_queen(checkerboard, 0);
	system("pause");
	return 0;
}
int eight_queen(char checkerboard[SIZE][SIZE], int sum)
{
	int i, j, num;
	char array[SIZE][SIZE];
	char array1[SIZE][SIZE];

//复制
	memcpy(array, checkerboard, SIZE*SIZE*sizeof(char));
	memcpy(array1, checkerboard, SIZE*SIZE*sizeof(char));

	if(sum == 8)
	{
		num++;
		printf("~~~~~~~~~第%d种~~~~~~~~~~~~\n",num);
		print(array1);
		//system("pause");
	}
	for(i = 0; i < SIZE; i++)
	{
		for(j = 0; j < SIZE; j++)
		{
			if(TRUE == put_queen(array, i, j))
			{
				sum++;
				if(eight_queen(array, sum) == -1)
				{
					array1[i][j] = '0';
					memcpy(array, array1, SIZE*SIZE*sizeof(char));
					sum--;
				}
			}
		}
	}
	return -1;
}
int put_queen(char checkerboard[SIZE][SIZE], int row, int column)
{
	int i = 0;
	if(checkerboard[row][column]=='-')
	{
		for(i = 0; i < 8; i++)
		{
			checkerboard[row][i] = '0';
			checkerboard[i][column] = '0';
			if(row + i < SIZE && column + i < SIZE)
				checkerboard[row + i][column + i] = '0';
			if(row - i >= 0 && column - i >= 0)
				checkerboard[row - i][column - i] = '0';
			if(row - i >= 0 && column + i < SIZE)
				checkerboard[row - i][column + i] = '0';
			if(row + i < SIZE && column - i >= 0)
				checkerboard[row + i][column - i] = '0';
		}
		checkerboard[row][column] = '1';
		return TRUE;
	}
	return FALSE;
}
int print(char checkerboard[SIZE][SIZE])
{
	int i, j;
	for(i = 0; i < SIZE; i++)
	{
		for(j = 0; j < SIZE; j++)
		{
			printf("%c ",checkerboard[i][j]);
		}
		printf("\n\r");
	}
}
```

#### 三天打鱼两天晒网
```c
#include<stdio.h>
int leapYear(int year)
{
     if((year%4==0&&year%100!=0)||(year%400==0))
     {
         return 1 ;
     }
     else
     {
         return 0 ;
     }
}
int theDayOfMonth(int month,int isLeap)
{
    if((month>=1) && (month <=7) && (month % 2 == 1))
    {
        return 31 ;
    }
    else if((month>7) && (month <=12) && (month % 2 == 0))
    {
        return 31 ;
    }
    else if((month == 2) && isLeap)
    {
        return 29 ;
    }
    else if((month == 2) && !isLeap)
    {
        return 28 ;
    }
    else
    {
        return 30;
    }

}
int main()
{
    int theSumOfDay = 0 ;
    int month , year , remainder;

    for( year = 1990 ; year < 2017 ; year ++ )
    {
        if(leapYear(year))
        {
            theSumOfDay = theSumOfDay + 366 ;
        }
        else
        {
            theSumOfDay = theSumOfDay + 365 ;
        }
    }
    /*
    for(i = 1 ; i <= 12 ; i ++)
    {
        printf("%d,%d\n",theDayOfMonth(i,1),theDayOfMonth(i,0));
    }
    */
    for( month = 1 ; month < 10 ; month ++)
    {
        theSumOfDay = theSumOfDay + theDayOfMonth(month,leapYear(2017)) ;
    }
    theSumOfDay = theSumOfDay + 15 ;
    remainder = theSumOfDay % 5 ;
    if( remainder <= 3 )
    {
        printf("打渔");
    }
    else
    {
        printf("晒网");
    }
    return 0 ;
}

```

#### 快排

```c
int * quickSort(int *a , int head , int foot)
{
	if(head < foot)
	{

		int i , j  , n;
		i = head ;
		j = foot ;
		int temp ;
		int a0 = a[head];
		printf("test:");
		printf("head=%d,",head);
		printf("foot=%d\n",foot);

		while( i < j )
		{
			for(n = 0 ; n < 8 ; n ++)
			{
				printf("%3d",a[n]);
			}
			printf("\n");

			if(a0 < a[i])
			{
				//printf("%d<%d\n",a0,a[i]);
				a[j] = a[i] ;
				a[i] = a0 ;
				j --;

			}
			else if(a0 > a[j])
			{
				//printf("%d>%d\n",a0,a[j]);
				a[i] = a[j] ;
				a[j] = a0 ;

				i ++;

			}
			else if(a0 < a[j]&& a0 != a[j])
			{
				j -- ;
			}
			else if(a0 > a[i] && a0 != a[i])
			{
				i ++ ;
			}
			else
			{
				//printf("都没有\n");
			}
			//printf("i=%d,j=%d\n",i,j);
		}

			a[i] = a0 ;
			printf("递归前:");
			printf("i=%d,",i);
			printf("j=%d\n",j);
			quickSort(a,head,i-1);


			quickSort(a,i+1,foot);


			return a ;
		}
}


int * bookSort(int * a , int head , int foot)
{
	int i , j , temp;
	printf("test:",a[i]);
	printf("head=%d,",head);
	printf("foot=%d\n",foot);
	for(i = 0 ; i < 8 ; i ++)
	{
		printf("%3d",a[i]);
	}
	printf("\n",a[i]);
	if(head < foot)
	{
		i = head ;
		j = foot ;
		temp = a[head];
		do
		{
			while(a[j]>temp)
			{
				j--;
			}
			if(i<j)
			{
				a[i]=a[j] ;
				a[j]=temp ;
				i++ ;
			}
			while(a[i]<temp)
			{
				i++;
			}
			if(i<j)
			{
				a[j] = a[i] ;
				a[i] = temp ;
				j--;
			}
		}while(i!=j);
		a[j] = temp ;
		printf("递归前:");
		printf("i=%d,",i);
		printf("j=%d\n",j);
		bookSort(a,head,i-1);
		bookSort(a,i+1,foot);
	}
	return a ;
 }

 ```
