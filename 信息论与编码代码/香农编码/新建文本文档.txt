#include <stdio.h>
#include <stdlib.h>
#include <math.h>

void solution(int n,double *a)//编码的函数
{
    int i,j,k;
    double t;
    double a_[n];
    for(i=0;i<n;i++)
    {
        a_[i]=a[i];

    }
    for(i=0;i<n;i++)//冒泡排序，第一步把信源符号按概率从大到小排列
    {
        for(j=0;j<n-1-i;j++)
        {
            if(a[j]<a[j+1])
            {
                t=a[j];
                a[j]=a[j+1];
                a[j+1]=t;
            }
        }
    }

    double b[n];//这个数组存的是第i个码字的累加概率
    b[0]=0;
    for(i=1;i<n;i++)
    {
        b[i]=b[i-1]+a[i-1];
    }//算码字的累加概率
    int c[n];//这个数组存的是第i个码字的长度
    for(i=0;i<n;i++)//求第i个码字的长度
    {
        double x1;//为不等式左边的变量（-log 2 p(ai))
        x1=-1*log2(a[i]);
        if(((int)x1-x1)==0)//如果前面的那个为整数
        {
            c[i]=(int)x1;
        }
        else
        {
            c[i]=(int)x1+1;
        }
    }

    printf("\n将各符号按概率从大到小的顺序排列之后:\n香农编码的结果如下：\n");
    //double d[n];//保存最终编码
    for(i=0;i<n;i++)//求最终编码的代码
    {

        printf("第%d个符号的概率为: %lf ,编码为：",i+1,a[i]);
        int num=0;
        double t;
        t=b[i]*2;
        while(num<c[i])
        {

            if(t==1)
            {
                //printf("%lf\n",t);
                printf("1");
                t=0;
            }
            else
            {
                //printf("%lf\n",t);
                printf("%d",(int)t);
                if(t>1)
                    t=t-1;
            }
            t=t*2;
            num++;
        }
        if(num==c[i])
            printf("\n");

    }

    double hx=0;//计算它的信源熵
    for(i=0;i<n;i++)
    {
        hx=-1*log2(a[i])*a[i]+hx;
    }
    double k_=0;//计算它的平均码长
    for(i=0;i<n;i++)
    {
        k_=k_+c[i]*a[i];
    }
    printf("\n该信源的信源熵为：%lf\n",hx);
    printf("该信源的平均码长为：%lf\n",k_);
    double Efficiency =hx/k_;
    printf("编码效率为：%lf%%",Efficiency*100);
    /*
    for(i=0;i<n;i++)
    {
        printf("%lf  ",a[i]);
    }
    */
}




int main()
{

    int n,i,j,k;
    printf("请输入信源符号的个数n：\n");
    scanf("%d",&n);
    double a[n];
    printf("请顺序输入信源各个符号的概率(从第一个状态开始)\n");
    for(i=0;i<n;i++)
    {
        scanf("%lf",&a[i]);
    }
    solution(n,a);

}
