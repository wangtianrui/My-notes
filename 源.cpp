#include<stdio.h>
#include<stdlib.h>
#include<iostream>
using namespace std;
#define MAXSIZE 100
typedef int keytype;
typedef struct {
	keytype key;
	int other;
}recordtype;

typedef struct {
	recordtype r[MAXSIZE - 1];
	int length;
}table;

void initTable(table *table)
{
	table->length = 10;
	//table->r[0]
	for (int i = 0; i < 10; i++)
	{
		table->r[i].key = i + (int)rand() % 10;
		printf("%d\t", table->r[i].key);
	}
	printf("\n");
}
/*
void insertSort(table * tab)
{
	int i, j;
	for (i = 0; i <= tab->length; i++)
	{
		j = i - 1;
		tab->r[0] = tab->r[i];
		while (tab->r[0].key < tab->r[j].key)
		{
			tab->r[j + 1] = tab->r[j];
			j = j - 1;
		}
		tab->r[j + 1] = tab->r[0];
	}
}*/

void insertSort(table *tab)
{
	int i, j;
	recordtype temp;
	for (i = 1; i<tab->length; i++)
	{
		temp = tab->r[i];
		for (j = i - 1; j >= 0 && temp.key<tab->r[i].key; j--)
			tab->r[j + 1] = tab->r[j];
		tab->r[j + 1] = temp;
	}
}

void showTable(table * tab)
{
	for (int i = 0; i < tab->length; i++)
	{
		printf("%d\t", tab->r[i].key);
	}
}
int main()
{
	//printf("test");
	table * t= NULL;
	t = (table*)malloc(sizeof(table));
	initTable(t);
	insertSort(t);
	showTable(t);
	system("pause");
	return 0;
}