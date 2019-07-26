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

	loop:printf("请输入信源符号个数N：");

	scanf("%d",&N);

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

		sort(a, a + N,greater<double>());//概率排序，从大到小
        //计算hx
		for(i=0;i<N;i++)
		{

			m[i]=-log2(a[i]);

		}

   		function3(0,N);//菲诺编码函数

		for(i=0;i<N;i++)
		{

 			H+=a[i]*m[i];//计算信源熵

 			k+=a[i]*K[i];//计算平均码长

		}

		printf("信源消息符号ai  符号概率p(ai)    码长Ki      二元码字\n");

		for(i=0;i<N;i++)

		{

     		printf("     a%d           %-4.2f              %d           ",i+1,a[i],K[i]);

  	 		for(j=0;j<K[i];j++)

     		printf("%d",s[i][j]);

     		printf("\n");

		}

		printf("信源熵H=%5.3f bit/符号    费诺码的平均码长k=%5.3f 码元/符号    编码效率n=%4.2f%% \n",H,k,100*(H/k));

 	}

}

int function1(int c,int M)//判断断开位置（从第几个到第几个断开）
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



void function2(int c,int num1,int M,int cs){
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



void function3(int c,int M)

{

 	num1=function1(c,M);

 	function2(c,num1,M,cs);

 	ks[cs]=c;

 	zj[cs]=num1;

 	zh[cs]=M;

 	cs++;
    //判断两个位置是否相邻，若相邻，则不用继续编码(递归方法)
 	if((zj[cs-1]-ks[cs-1])>1)

 	{

		function3(ks[cs-1],zj[cs-1]);

 	}
    //判断两个位置是否相邻，若相邻，则不用继续编码(递归方法)，下半部分
 	if((zh[cs-1]-zj[cs-1])>1)

 	{

   		function3(zj[cs-1],zh[cs-1]);

 	}

 	cs--;
}

