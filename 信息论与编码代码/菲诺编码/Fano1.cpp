#include<iostream>
#include<stdio.h>
#include<math.h>
#include<algorithm>
using namespace std;
const int G=20;
int function1(int c, int M);
void function2(int c,int num1,int M,int cs);
void function3(int c,int M);
float a[G]={0},tmp=0,m[G]={0},k=0,H=0,num[G]={0},sum1=0,sum2=0;
int K[G]={0},i,j,N,s[G][G],c,cs=0,num1=0,ks[G],zj[G],zh[G];

int main()
{

	loop:printf("��������Դ���Ÿ���N��");

	scanf("%d",&N);

	for(i=0;i<N;i++)

 	{

   		scanf("%f",&a[i]);

   		tmp+=a[i];

 	}

 	if(tmp != 1)

 	{

   		printf("��������ݲ�����Ҫ��,����������\n");

       	tmp=0;

  		 goto loop;

 	}
 	else
 	{

		sort(a, a + N,greater<double>());//�������򣬴Ӵ�С
        //����hx
		for(i=0;i<N;i++)
		{

			m[i]=-log2(a[i]);

		}

   		function3(0,N);//��ŵ���뺯��

		for(i=0;i<N;i++)
		{

 			H+=a[i]*m[i];//������Դ��

 			k+=a[i]*K[i];//����ƽ���볤

		}

		printf("��Դ��Ϣ����ai  ���Ÿ���p(ai)    �볤Ki      ��Ԫ����\n");

		for(i=0;i<N;i++)

		{

     		printf("     a%d           %-4.2f              %d           ",i+1,a[i],K[i]);

  	 		for(j=0;j<K[i];j++)

     		printf("%d",s[i][j]);

     		printf("\n");

		}

		printf("��Դ��H=%5.3f bit/����    ��ŵ���ƽ���볤k=%5.3f ��Ԫ/����    ����Ч��n=%4.2f%% \n",H,k,100*(H/k));

 	}

}

int function1(int c,int M)//�ж϶Ͽ�λ�ã��ӵڼ������ڼ����Ͽ���
{

	int d=c;

    for(i=c;i<M-1;i++)

	{

  		for(j=c;j<i+1;j++)		sum1+=a[j];


  		for(j=i+1;j<M;j++)      sum2+=a[j];


      	num[i]=fabs(sum1-sum2);//�ֱ�����η�������Ĳ�ֵ

  		sum1=0;

  		sum2=0;

	}
    //�ҵ���С�Ĳ�ֵλ��
	for(i=c;i<M-1;i++)
	{
		if(num[d]>num[i])

 		 	d=i;
 	}

  	d+=1;

   	return d;//d���ж�λ��

}



void function2(int c,int num1,int M,int cs){
	int i;
	//���ϰ벿�ֽ��б���
   for(i=c;i<num1;i++)
	{

  		s[i][cs]=0;

  		K[i]+=1;
  	}
    //���°벿�ֽ��б��벢�����볤
	for(j=num1;j<M;j++)

	{

  		s[j][cs]=1;

 		 K[j]+=1;

	}

}



void function3(int c,int M)

{

 	num1=function1(c,M);

 	function2(c,num1,M,cs);

 	ks[cs]=c;

 	zj[cs]=num1;

 	zh[cs]=M;

 	cs++;
    //�ж�����λ���Ƿ����ڣ������ڣ����ü�������(�ݹ鷽��)
 	if((zj[cs-1]-ks[cs-1])>1)

 	{

		function3(ks[cs-1],zj[cs-1]);

 	}
    //�ж�����λ���Ƿ����ڣ������ڣ����ü�������(�ݹ鷽��)���°벿��
 	if((zh[cs-1]-zj[cs-1])>1)

 	{

   		function3(zj[cs-1],zh[cs-1]);

 	}

 	cs--;
}

