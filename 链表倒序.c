#include<stdio.h>
typedef struct node 
{
	int value;
	struct node * next;
}node;

typedef struct linkList
{
	struct node * head ;
	int size ;
}linkList;

linkList * create()
{
	node * head = NULL;
	int size = 0;
	int i ;
	for(i = 1 ; i <= 5 ; i++)
	{
		node * temp = (node*)malloc(sizeof(node));
		temp->next = NULL;
		temp->value = i ;
		if(head==NULL)
		{
			head = temp ;
		}
		else
		{
			node * p = head;
			while(p->next!=NULL)
			{
				p = p->next;
			}
			p->next = temp;	
		}
		size ++;
	}
	linkList* mlinkList ;
	mlinkList = (linkList*)malloc(sizeof(linkList));
	mlinkList->head = head;
	mlinkList->size = size;
	return mlinkList;
}

void show(linkList * mlist)
{
	node * p ;
	p = mlist->head;
	while(p)
	{
		printf("%d\t",p->value);
		p = p->next;
	}
}


linkList * reserve(linkList *mlist)
{
	node * last = NULL ;
	node * p = mlist->head ;
	node * next = NULL ;
	while(p)
	{
		next = p->next ;
		p->next = last ;
		if(last != NULL)
		{
			printf("\n把%d的next指向了%d\n",p->value,last->value);
		}
		else
		{
			printf("\n把%d的next指向了%d\n",p->value,last);
		}
		last = p ;
		p = next ;
	}
	linkList * reList = (linkList *)malloc(sizeof(linkList));
	reList->head = last ;
	reList->size = mlist->size ;
	return reList ;
} 
int main()
{
	linkList * mlist = create();
	show(mlist);
	linkList * reList = reserve(mlist);
	printf("\n-------------\n");
	show(reList);
	return 0;
} 
