#include<iostream>
#include<stdio.h>
#include<math.h>
#include<algorithm>
using namespace std;
const int MAXN=20;
int f1(int, int);
void f2(int,int,int,int);
void f3(int,int);
float a[MAXN]={0},tmp=0,m[MAXN]={0},num[MAXN]={0},sum1=0,sum2=0;
int K[MAXN]={0},s[MAXN][MAXN],cs=0,num1=0,S1[MAXN],S2[MAXN],S3[MAXN];
int i, j, N;
float k, H;
int b[MAXN];
void initb()
{
    for(i = 0; i < MAXN; i++)
    {
        b[i] = i + 1;
    }
}
void sort_(){
    for(i=0;i<N;i++)//冒泡排序，第一步把信源符号按概率从大到小排列
    {
        for(j=0;j<N-1-i;j++)
        {
            if(a[j]<a[j+1])
            {
             /*   t=a[j];
                a[j]=a[j+1];
                a[j+1]=t;*/
                swap(a[j], a[j + 1]);
                swap(b[j], b[j + 1]);
            }
        }
    }}
int main()
{
    initb();
	loop:cout<< "请输入信源符号个数N：";
	cin >> N;
    cout << "请输入每个信源出现概率: ";

	for(i=0;i<N;i++)

 	{

   		scanf("%f",&a[i]);

   		tmp+=a[i];

 	}

 	if(tmp != 1)

 	{

   		printf("输入的数据不符合要求,请重新输入\n");

       	tmp=0;

  		 goto loop;

 	}
 	else
 	{

		//sort_(a, a + N,greater<double>());//概率排序，从大到小
		sort_();
        //计算hx
		for(i=0;i<N;i++)
		{

			m[i]=-log2(a[i]);

		}

   		f3(0,N);//菲诺编码函数

		for(i=0;i<N;i++)
		{

 			H+=a[i]*m[i];//计算信源熵

 			k+=a[i]*K[i];//计算平均码长

		}

		printf("信源消息符号ai  符号概率p(ai)    码长Ki      二元码字\n");

		for(i=0;i<N;i++)

		{

     		printf("     a%d           %-4.2f              %d           ",/*i+1*/b[i],a[i],K[i]);

  	 		for(j=0;j<K[i];j++)

     		printf("%d",s[i][j]);

     		printf("\n");

		}

		printf("信源熵H=%5.3f bit/符号    费诺码的平均码长k=%5.3f 码元/符号    编码效率n=%4.2f%% \n",H,k,100*(H/k));

 	}

}

int f1(int c,int M)//判断断开位置（从第几个到第几个断开）
{

	int d=c;

    for(i=c;i<M-1;i++)

	{

  		for(j=c;j<i+1;j++)		sum1+=a[j];


  		for(j=i+1;j<M;j++)      sum2+=a[j];


      	num[i]=fabs(sum1-sum2);//分别计算多次分组情况的差值

  		sum1=0;

  		sum2=0;

	}
    //找到最小的差值位置
	for(i=c;i<M-1;i++)
	{
		if(num[d]>num[i])

 		 	d=i;
 	}

  	d+=1;

   	return d;//d是中断位置

}



void f2(int c,int num1,int M,int cs){
	int i;
	//对上半部分进行编码
   for(i=c;i<num1;i++)
	{

  		s[i][cs]=0;

  		K[i]+=1;
  	}
    //对下半部分进行编码并计算码长
	for(j=num1;j<M;j++)

	{

  		s[j][cs]=1;

 		 K[j]+=1;

	}

}



void f3(int c,int M)

{

 	num1=f1(c,M);

 	f2(c,num1,M,cs);

 	S1[cs]=c;

 	S2[cs]=num1;

 	S3[cs]=M;

 	cs++;
    //判断两个位置是否相邻，若相邻，则不用继续编码(递归方法)
 	if((S2[cs-1]-S1[cs-1])>1)

 	{

		f3(S1[cs-1],S2[cs-1]);

 	}
    //判断两个位置是否相邻，若相邻，则不用继续编码(递归方法)，下半部分
 	if((S3[cs-1]-S2[cs-1])>1)

 	{

   		f3(S2[cs-1],S3[cs-1]);

 	}

 	cs--;
}

