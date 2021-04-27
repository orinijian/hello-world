#include<iostream> 
#include<stdlib.h>

using namespace std;

typedef struct PolyNode *Polynomial;//定义了一个结构体变量的指针，以后你可以直接用Polynomial来代表struct PolyNode *这个数据.
struct PolyNode//搭建链表的结构 
{
	int coef;//系数
	int expon;//指数
	Polynomial link; //下一个的地址 
};

void Attach(int c,int e,Polynomial *pRear)
{
	Polynomial P;
	P = (Polynomial)malloc(sizeof(struct PolyNode));
	P->coef = c;//对结点进行赋值
	P->expon = e;//对系数的赋值
	P->link = NULL;
	
	(*pRear)->link = P;
	*pRear = P;  
}

Polynomial ReadPoly()//读入多项式的函数 
{
	int c,e,N;
	Polynomial P,Rear,t;

	scanf("%d",&N);
	P = (Polynomial)malloc(sizeof(struct PolyNode));//链表头空结点
	P->link = NULL;
	Rear = P;//P此时是临时生成的头结点 
	while(N--)
	{
		scanf("%d %d",&c,&e);
		Attach(c,e,&Rear);
	}
	
	t=P;
	P=P->link;
	free(t);//删除临时头结点 
	
	return P;
}

Polynomial Add(Polynomial P1, Polynomial P2)//多项式相加 
{
	
	Polynomial Rear,P,t1,t2,t;
	t1 = P1;t2 = P2;
	int sum = 0;
	
	P = (Polynomial)malloc(sizeof(struct PolyNode));
	
	P->link = NULL;//P为输出链表的表头
	 
	Rear = P;
	while(t1 && t2)
	{
		if(t1->expon == t2->expon)//进行系数比较 
		{
			sum = t1->coef + t2->coef;
			Attach(sum,t1->expon,&Rear);
			t1 = t1->link;
			t2 = t2->link;
		}
		else if(t1->expon > t2->expon)
		{
			Attach(t1->coef , t1->expon , &Rear);
			t1 = t1->link;
		}
		else
		{
			Attach(t2->coef , t2->expon , &Rear);
			t2 = t2->link;
		}
	}
	while(t1)//t1或t2剩余的接到链表后端 
	{
		Attach(t1->coef,t1->expon,&Rear);
		t1 = t1->link;
	}
	while(t2)
	{
		Attach(t2->coef,t2->expon,&Rear);
		t2 = t2->link;
	}
	
	t = P;
	P=P->link;
	free(t);
	 
	return P;
} 

Polynomial Mult(Polynomial P1, Polynomial P2)
{
	Polynomial P,t,t1,t2,Rear;
	int c,e;

	t1 = P1; t2 = P2;
	
	if(!P1||!P2)return NULL;
	
	P=(Polynomial)malloc(sizeof(struct PolyNode));
	P->link = NULL;
	Rear = P;
	//printf("%p\n",P) ;
	while(t2)
	{		/*先用P1的第1项P2,得到P*/ 
		Attach(t1->coef*t2->coef,t1->expon+t2->expon,&Rear);
		t2 = t2->link;
	}
	t1= t1->link;
	
	while (t1)
	{
		t2 = P2; Rear = P;
		while(t2)
		{
			e = t1->expon + t2->expon;
			c = t1->coef*t2->coef;
			while(Rear->link&&Rear->link->expon>e) Rear=Rear->link;//如果此时链表下一项的系数比要插入的大,指针就继续往后走 
		
			if(Rear->link&&Rear->link->expon == e)
			{//如果与后面的系数是相等,这时候要加 
				if(Rear->link->coef + c)
				{
					Rear->link->coef += c;
				}
				else
				{
					t=Rear->link;
					Rear->link=t->link;
					free(t);
				}
			}
			else
			{
				t=(Polynomial)malloc(sizeof(struct PolyNode));
				t->coef = c;t->expon = e;
				t->link = Rear->link;
				Rear->link = t;
				Rear = Rear->link;
			}
			
			t2=t2->link;
		}
		t1 = t1->link;
	}
	t = P;P=P->link;free(t);
	//printf("%d",P) ;
	return P; 
}

void PrintPoly(Polynomial P)
{/*输出多项式*/ 
	int flag = 0;
	if(!P)
	{
		printf("0 0\n");return;//空值 
	}
	
	while(P)
	{
		if(!flag) flag = 1;
		else printf(" ");
		printf("%d %d",P->coef,P->expon);
		P=P->link;
	}
	printf("\n");
}


int main()
{
	Polynomial P1,P2,PP,PS;
	P1 = ReadPoly();
	P2 = ReadPoly();
	//PrintPoly(P1);
	//PrintPoly(P2);
	PP = Mult( P1,P2 );//多项式的乘法运算 (实现) 
	PrintPoly(PP);
	
	PS = Add( P1,P2 );//多项式的加法运算 (实现） 
	PrintPoly( PS );
	return 0;
}
