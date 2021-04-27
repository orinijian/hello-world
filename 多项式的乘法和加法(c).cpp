#include<iostream> 
#include<stdlib.h>

using namespace std;

typedef struct PolyNode *Polynomial;//������һ���ṹ�������ָ�룬�Ժ������ֱ����Polynomial������struct PolyNode *�������.
struct PolyNode//�����Ľṹ 
{
	int coef;//ϵ��
	int expon;//ָ��
	Polynomial link; //��һ���ĵ�ַ 
};

void Attach(int c,int e,Polynomial *pRear)
{
	Polynomial P;
	P = (Polynomial)malloc(sizeof(struct PolyNode));
	P->coef = c;//�Խ����и�ֵ
	P->expon = e;//��ϵ���ĸ�ֵ
	P->link = NULL;
	
	(*pRear)->link = P;
	*pRear = P;  
}

Polynomial ReadPoly()//�������ʽ�ĺ��� 
{
	int c,e,N;
	Polynomial P,Rear,t;

	scanf("%d",&N);
	P = (Polynomial)malloc(sizeof(struct PolyNode));//����ͷ�ս��
	P->link = NULL;
	Rear = P;//P��ʱ����ʱ���ɵ�ͷ��� 
	while(N--)
	{
		scanf("%d %d",&c,&e);
		Attach(c,e,&Rear);
	}
	
	t=P;
	P=P->link;
	free(t);//ɾ����ʱͷ��� 
	
	return P;
}

Polynomial Add(Polynomial P1, Polynomial P2)//����ʽ��� 
{
	
	Polynomial Rear,P,t1,t2,t;
	t1 = P1;t2 = P2;
	int sum = 0;
	
	P = (Polynomial)malloc(sizeof(struct PolyNode));
	
	P->link = NULL;//PΪ�������ı�ͷ
	 
	Rear = P;
	while(t1 && t2)
	{
		if(t1->expon == t2->expon)//����ϵ���Ƚ� 
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
	while(t1)//t1��t2ʣ��Ľӵ������� 
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
	{		/*����P1�ĵ�1��P2,�õ�P*/ 
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
			while(Rear->link&&Rear->link->expon>e) Rear=Rear->link;//�����ʱ������һ���ϵ����Ҫ����Ĵ�,ָ��ͼ��������� 
		
			if(Rear->link&&Rear->link->expon == e)
			{//���������ϵ�������,��ʱ��Ҫ�� 
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
{/*�������ʽ*/ 
	int flag = 0;
	if(!P)
	{
		printf("0 0\n");return;//��ֵ 
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
	PP = Mult( P1,P2 );//����ʽ�ĳ˷����� (ʵ��) 
	PrintPoly(PP);
	
	PS = Add( P1,P2 );//����ʽ�ļӷ����� (ʵ�֣� 
	PrintPoly( PS );
	return 0;
}
