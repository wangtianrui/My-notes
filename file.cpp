#include<stdio.h>
#include<stdlib.h>
#define M 20
#define FINITY 5000
typedef char DataType;
typedef char vertextype;
typedef int edgetype;

/*邻接表*/
typedef struct node {
	int adjvex;
	struct node * next;
}EdgeNode;

typedef struct vnode {
	DataType vertex;
	EdgeNode * FirstEdge;
}VertexNode;

typedef struct {
	VertexNode adjlist[M];
	int n, e;
}LinkedGraph;
/*创建邻接表*/
void createLinkedGraph(LinkedGraph *g, char *filename, int c)
{
	int i, j, k;
	EdgeNode *s;
	FILE * fp;
	fp = fopen(filename, "r");
	if (fp)
	{
		fscanf(fp, "%d%d", &g->n, &g->e);
		for (i = 0; i < g->n; i++)
		{
			fscanf(fp, "%c", &g->adjlist[i].vertex);
			g->adjlist[i].FirstEdge = NULL;
		}
		for (k = 0; k < g->e; k++)
		{
			fscanf(fp, "%d%d", &i, &j);
			s = (EdgeNode *)malloc(sizeof(EdgeNode));
			s->adjvex = j;
			s->next = g->adjlist[i].FirstEdge;
			g->adjlist[i].FirstEdge = s;
			if (c == 0)
			{
				s = (EdgeNode*)malloc(sizeof(EdgeNode));
				s->adjvex = i;
				s->next = g->adjlist[j].FirstEdge;
				g->adjlist[j].FirstEdge = s;
			}
		}
		fclose(fp);
	}
	else
	{
		g->n = 0;
	}
}



/*邻接矩阵*/
typedef struct {
	vertextype vexs[M];
	edgetype edges[M][M];
	int n, e;
}Mgraph;

void creatMgraph(Mgraph *g, char *s, int c)
{
	int i, j, k, w;
	FILE * rf;
	rf = fopen(s, "r");
	if (rf)
	{
		fscanf(rf, "%d%d", &g->n, &g->e);
		for (i = 0; i < g->n; i++)
		{
			fscanf(rf, "%c", &g->vexs[i]);
		}
		for (i = 0; i < g->n; i++)
		{
			for (j = 0; j < g->n; j++)
			{
				if (i == j)
				{
					g->edges[i][j] = 0;
				}
				else
				{
					g->edges[i][j] = FINITY;
				}
			}
		}
		for (k = 0; k < g->e; k++)
		{
			fscanf(rf, "%d%d%d", &i, &j, &w);
			g->edges[i][j] = w;
			if (c == 0)
			{
				g->edges[j][i] = w;
			}
		}
		fclose(rf);
	}
	else
	{
	    printf("open error");
		g->n = 0;
	}
}

void showMgraph(Mgraph *g)
{
	for (int i = 0; i < g->n; i++)
	{
		for (int j = 0; j < g->n; j++)
		{
			printf("%5d", g->edges[i][j]);
		}
		printf("\n");
	}
}

/*dijkstra算法*/
typedef enum { FALSE, TRUE } boolean;
typedef int dist[M];
typedef int path[M];

void dijkstra(Mgraph g,int v0,path p,dist d)
{
    boolean final[M];
    int i,k,j,v,min,x;
    for(v = 0 ; v < g.n ; v++)
    {
        final[v]=FALSE;
        d[v]=g.edges[v0][v];
        if(d[v]<FINITY && d[v]!=0)
        {
            p[v]=v0;
        }
        else
        {
            p[v]=-1;
        }
    }
    final[v0] = TRUE;
    d[v0] = 0;
    for(i = 1 ;i < g.n;i++)
    {
        min = FINITY;
        for(k = 0 ; k < g.n ; ++k)
        {
            if(!final[k]&&d[k]<min)
            {
                v=k;
                min=d[k];
            }
        }
        printf("\n%c----%d\n",g.vexs[v],min);
        if(min == FINITY)
        {
            return;
        }
        final[v]=TRUE;
        for(k=0;k<g.n;++k)
        {
            if(!final[k]&&(min+g.edges[v][k]<d[k]))
            {
                d[k]=min+g.edges[v][k];
                p[k]=v;
            }
        }
    }
}

void print_gpd(Mgraph g,path p,dist d)
{
    int st[M],i,pre,top=-1;
    for(i=0;i<g.n;i++)
    {
        printf("\nDistancd:%7d , path:",d[i]);
        st[++top]=i;
        pre=p[i];
        while(pre!=-1)
        {
            st[++top]=pre;
            pre=p[pre];
        }
        while(top>0)
        {
            printf("%2d",st[top--]);
        }
    }
}
/*所有顶点对最短路径*/
typedef int dist2[M][M];
typedef int path2[M][M];
void floyd(Mgraph g,path2 p,dist2 d)
{
    int i,j,k;
    for(i=0;i<g.n;i++)
    {
        for(j=0;j<g.n;j++)
        {
            d[i][j]=g.edges[i][j];
            if(i!=j && d[i][j]<FINITY)
            {
                p[i][j]=i;
            }
            else
            {
                p[i][j]=-1;
            }
        }
    }
    for(k=0;k<g.n;k++)
    {
        for(i=0;i<g.n;i++)
        {
            for(j=0;j<g.n;j++)
            {
                if(d[i][j]>(d[i][k]+d[k][j]))
                {
                    d[i][j]=d[i][k]+d[k][j];
                    p[i][j]=k;
                }
            }
        }
    }
}


int main()
{
	char filename[20] = "E:\\GraphTest.txt";
	Mgraph * g;
	path p;
	dist d;
	path2 p2;
	dist2 d2;
	int v0,v1,v2;
	g = (Mgraph*)malloc(sizeof(Mgraph));
	creatMgraph(g,filename,0);
	showMgraph(g);
	printf("输入点:\n");
	scanf("%d",&v0);
	dijkstra(*g,v0,p,d);
	printf("输入两个点：\n");
	scanf("%d%d",&v1,&v2);
	floyd(*g,p2,d2);
	printf("两点最短路程为:%d",d2[v1][v2]);
	//print_gpd(*g,p2,d2);
	system("pause");
	return 0;
}
