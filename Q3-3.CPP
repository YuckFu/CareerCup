#define M 5
#define MAX 3
typedef int ElemType;
typedef struct HashNode
{
	int *Arr;
}HashNode,*pHashTable;
int top = -1;	//ȫ�ֱ�������¼ջ��
int cur = 0;    //ȫ�ֱ�������¼��ǰ���õ���������

#include<stdio.h>
#include<stdlib.h>
pHashTable create_HashTable()
{
	//ʹ��callocֱ�ӽ��ڲ���ÿ��Arr��ʼ��ΪNULL
	pHashTable hashtable = (pHashTable)calloc(M,sizeof(HashNode));
	if(!hashtable)
	{
		printf("malloc failed");
		exit(-1);
	}
	return hashtable;
}

void push(pHashTable hashtable,ElemType data)
{
	if(cur==0 && top==-1)
	{
		//�ڲ�Ԫ��ȫ����ʼ��Ϊ0
		hashtable[cur].Arr = (int *)calloc(MAX,sizeof(int));
		if(!hashtable[cur].Arr)
		{
			printf("malloc failed");
			exit(-1);
		}
	}
	if(cur>M-1)
		return;
	if(top<MAX-1)
		hashtable[cur].Arr[++top] = data;
	else if(top>MAX-1)
		return;
	else
	{
		//�����ǰ�����Ѿ����ˣ���ת����һ���������push����
		cur++;
		top = -1;
		hashtable[cur].Arr = (int *)calloc(MAX,sizeof(int));
		if(!hashtable[cur].Arr)
		{
			printf("malloc failed");
			exit(-1);
		}
		push(hashtable,data);
	}
}

void pop(pHashTable hashtable)
{
	if(cur>M-1 || cur<0)
		return;
	if(top>-1)
		hashtable[cur].Arr[top--] = 0;  //��pop��Ԫ����Ϊ0������ԭ��Ĭ�ϳ�ֵֵ
	else if(top<-1)
		return;
	else
	{
		//�����ǰ����Ϊ���ˣ����ͷŵ�������ռ䣬ת����һ���������pop����
		free(hashtable[cur].Arr);
		hashtable[cur].Arr = NULL;
		cur--;
		top = MAX-1;
		pop(hashtable);
	}
}

int main()
{
	pHashTable hashtable = create_HashTable();
	push(hashtable,1);
	push(hashtable,2);
	push(hashtable,3);
	push(hashtable,4);
	push(hashtable,5);
	push(hashtable,6);
	push(hashtable,7);	

	int i,j;
	printf("After pushed:\n");
	for(i=0;i<M;i++)
	{
		if(hashtable[i].Arr)
		{
			for(j=0;j<MAX;j++)
				printf("%d ",hashtable[i].Arr[j]);
			printf("\n");
		}
	}

	pop(hashtable);
	pop(hashtable);
	pop(hashtable);
	pop(hashtable);
	pop(hashtable);

	printf("After poped:\n");
	for(i=0;i<M;i++)
	{
		if(hashtable[i].Arr)
		{
			for(j=0;j<MAX;j++)
				printf("%d ",hashtable[i].Arr[j]);
			printf("\n");
		}
	}	
	return 0;
}