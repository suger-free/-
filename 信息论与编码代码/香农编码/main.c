#include <stdio.h>
#include <stdlib.h>
#include <math.h>

void solution(int n,double *a)//����ĺ���
{
    int i,j,k;
    double t;
    double a_[n];
    for(i=0;i<n;i++)
    {
        a_[i]=a[i];

    }
    for(i=0;i<n;i++)//ð�����򣬵�һ������Դ���Ű����ʴӴ�С����
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

    double b[n];//����������ǵ�i�����ֵ��ۼӸ���
    b[0]=0;
    for(i=1;i<n;i++)
    {
        b[i]=b[i-1]+a[i-1];
    }//�����ֵ��ۼӸ���
    int c[n];//����������ǵ�i�����ֵĳ���
    for(i=0;i<n;i++)//���i�����ֵĳ���
    {
        double x1;//Ϊ����ʽ��ߵı�����-log 2 p(ai))
        x1=-1*log2(a[i]);
        if(((int)x1-x1)==0)//���ǰ����Ǹ�Ϊ����
        {
            c[i]=(int)x1;
        }
        else
        {
            c[i]=(int)x1+1;
        }
    }

    printf("\n�������Ű����ʴӴ�С��˳������֮��:\n��ũ����Ľ�����£�\n");
    //double d[n];//�������ձ���
    for(i=0;i<n;i++)//�����ձ���Ĵ���
    {

        printf("��%d�����ŵĸ���Ϊ: %lf ,����Ϊ��",i+1,a[i]);
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

    double hx=0;//����������Դ��
    for(i=0;i<n;i++)
    {
        hx=-1*log2(a[i])*a[i]+hx;
    }
    double k_=0;//��������ƽ���볤
    for(i=0;i<n;i++)
    {
        k_=k_+c[i]*a[i];
    }
    printf("\n����Դ����Դ��Ϊ��%lf\n",hx);
    printf("����Դ��ƽ���볤Ϊ��%lf\n",k_);
    double Efficiency =hx/k_;
    printf("����Ч��Ϊ��%lf%%",Efficiency*100);
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
    printf("��������Դ���ŵĸ���n��\n");
    scanf("%d",&n);
    double a[n];
    printf("��˳��������Դ�������ŵĸ���(�ӵ�һ��״̬��ʼ)\n");
    for(i=0;i<n;i++)
    {
        scanf("%lf",&a[i]);
    }
    solution(n,a);

}
