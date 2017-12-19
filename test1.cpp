#include<stdio.h>
#include<stdlib.h>
#define M 20
typedef char DataType;

int visited[M];

typedef struct node{
	int adjvex;
	struct node * next;
}EdgeNode;

typedef struct vnode{
	DataType vertex ;
	EdgeNode *FirstEdge;
}VertexNode;

typedef struct {
	VertexNode adjlist[M];
	int n , e ;
}LinkedGraph;

void create(LinkedGraph *g , char * fileName , int c)
{
	int i,j,k;
	EdgeNode *s ;
	FILE *fp ;
	fp = fopen(fileName,"r");
	if(fp)
	{
		fscanf(fp,"%d%d",&g->n,&g->e);
		for(i=0;i<g->n;i++)
		{
			fscanf(fp,"%c",&g->adjlist[i].vertex);
			//printf("%c heelo\n",g->adjlist[i].vertex);
			g->adjlist[i].FirstEdge = NULL ;
		}
		for(k=0;k<g->e;k++)
		{
			fscanf(fp,"%d%d",&i,&j);
			printf("linked:%d,%d\n",i,j);
			s=(EdgeNode*)malloc(sizeof(EdgeNode));
			s->adjvex = j ;
			s->next = g->adjlist[i].FirstEdge;
			g->adjlist[i].FirstEdge = s ;
			if(c == 0)
			{
				s=(EdgeNode*)malloc(sizeof(EdgeNode));
				s->adjvex = i ;
				s->next = g->adjlist[j].FirstEdge;
				g->adjlist[j].FirstEdge = s ;	
			}
		}
		fclose(fp);	
	}
	else
	{
		printf("open error");
		g->n = 0 ;
	}
	
}
int num = 0 ;
void dfs(LinkedGraph g , int i)
{
	num += 1 ;
	EdgeNode *p ;
	printf("time: %d \n",num);
	printf("visit vertex: %c \n",g.adjlist[i].vertex);
	visited[i] = 1 ;
	p = g.adjlist[i].FirstEdge;
	while(p)
	{
		printf("检查%d\n",p->adjvex);
		if(!visited[p->adjvex])
		{
			printf("切换点到%d\n",p->adjvex);
			dfs(g,p->adjvex);
		}
		printf("deep\n");
		p = p->next;	
	}
}

void DfsTraverse(LinkedGraph g)
{
	int i ;
	for(i=0;i<g.n;i++)
	{
		visited[i] = 0 ;
	}
	for(i=0;i<g.n;i++)
	{
		if(!visited[i])
		{
			printf("travel %d\n",i+1);
			dfs(g,i);
		}
	}
}

void bfs(LinkedGraph g,int i)
{
	int  j ;
	EdgeNode *p ;
	int queue[M],front,rear ;
	front = rear = 0 ;
	printf("%c",g.adjlist[i].vertex);
	visited[i]=1;
	queue[rear++] = i;
	while(rear > front) 
	{
		j = queue[front++]; //取出前一次遍历的第一个 
		p = g.adjlist[j].FirstEdge;
		while(p)
		{
			if(visited[p->adjvex]==0)
			{
				printf("%c",g.adjlist[p->adjvex].vertex);
				queue[rear ++] = p->adjvex;
				visited[p->adjvex]=1;
			}
			
			printf("\tp: %c =p->next\n",g.adjlist[p->adjvex].vertex);
			p = p->next;
		}
	}
} 
int BfsTraverse(LinkedGraph g)
{
	int i , count = 0 ;
	for(i=0;i<g.n;i++)
	{
		visited[i]=0;
	}
	for(i=0;i<g.n;i++)
	{
		if(!visited[i])
		{
			printf("\n");
			count ++;
			bfs(g,i);
		}
	}
	return count ;
}
int main()
{
	LinkedGraph * g = NULL;
	char * filename = "D:\\test.txt";
	int j ;
	g = (LinkedGraph*)malloc(sizeof(LinkedGraph));
	
	create(g,filename,0);
	//DfsTraverse(*g);
	j = BfsTraverse(*g);
	printf("1");
	return 0;
}
