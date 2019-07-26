#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>

#define MAXNUM 20		//���ɴ���Ĵ�ȨֵҶ�ӽڵ���

using namespace std;

double count[MAXNUM];     //��¼������������볤 

//���ڵ㶨��
typedef struct TREE_Node
{
	double weight;   
	struct TREE_Node *L_Child, *R_Child;
} treeNode;

//������weight[]�е�length��Ȩֵ����������������������ָ��
treeNode *Huffman_Create(double *weight, int n)
{
	//��Ȩֵ��������������ΪNULL��ɭ��
	treeNode **weightForest = NULL, *temp = NULL;
	weightForest = (treeNode**)malloc(n * sizeof (treeNode));
	for (int i = 0; i < n; i++)
	{
		weightForest[i] = (treeNode *)malloc(sizeof (treeNode));
		weightForest[i]->weight = weight[i];
		weightForest[i]->L_Child = weightForest[i]->R_Child = NULL;
	}        
	//����length-1��ѭ�����ɹ�������
	for (int i = 0; i < n-1; i++)
	{
		int j = 0, k1, k2;
		double min;

		//�ҳ�Ȩֵ��С������λ�ã��������±�
		while (!weightForest[j])j++;
		min = weightForest[j]->weight;
		k1 = j;
		j++;
		for (; j < n; j++)
			if (weightForest[j] && weightForest[j]->weight < min)
			{
				min = weightForest[j]->weight;
				k1 = j;
			}
		temp = (treeNode*)malloc(sizeof (treeNode));
		temp->L_Child = weightForest[k1];//����С����Ϊ�½ڵ��������
		weightForest[k1] = NULL;

		//�ҳ�Ȩֵ��С������λ��
		j = 0;
		while (!weightForest[j])j++;
		min = weightForest[j]->weight;
		k2 = j;
		j++;
		for (; j < n; j++)
			if (weightForest[j] && weightForest[j]->weight < min)
			{
				min = weightForest[j]->weight;
				k2 = j;
			}
		temp->R_Child = weightForest[k2];//����С����Ϊ�½ڵ��������

		//�����½ڵ��Ȩֵ
		temp->weight = temp->L_Child->weight + temp->R_Child->weight;
		weightForest[k2] = temp;//���½ڵ�ŵ��������Բ����´αȽ�
	}
	free(weightForest);
	return temp;
}

double ave_length;  //�ڹ��������뺯���м���ƽ���볤 
//���ÿ��Ȩֵ���Ӧ�Ĺ���������
void Huffman_Code(treeNode *root, char *code, int i)
{
	if (root->L_Child == NULL && root->R_Child == NULL)
	{
		printf("\nȨֵΪ %.3f��Ԫ�صĹ���������Ϊ: ", root->weight);
		for (int j = 0; j < i; j++)printf("%c", code[j]);
		ave_length += (root->weight * i);
	}
	else
	{
		code[i] = '1';
		Huffman_Code(root->L_Child, code, i + 1);
		code[i] = '0';
		Huffman_Code(root->R_Child, code, i + 1);
	}
}

int HuffmanStatistics(double *weight, int n)
{
	double entropy, eta;
	entropy = eta = 0; 

	for (int i = 0; i < n; i++) {
		entropy -= weight[i] * log2(weight[i]);
	}
	eta = entropy / ave_length * 100;
	printf (" ��Դ��H(x)Ϊ: %.4lf (bit/sign)   \n", entropy);
	printf (" ƽ���볤��Ϊ��%.4lf (bit/sign)  \n", ave_length);
	printf (" ����Ч�ʦ�Ϊ: %.4lf%%  \n", eta);
}

int main(int argc, const char* argv[])
{
	double weight[MAXNUM];
	int length = -1, sum = 0;
	//�Ӽ��̶���Ȩֵ
	printf("Please input weight(input \"q\" to quit): ");
	while (scanf("%lf", &weight[++length]));
	//������������
	treeNode *Huffman_root = Huffman_Create(weight,length);
	//������ʱ����洢����������
	memset(count, 0, sizeof(count));
	char code[MAXNUM] = { '0','0','0','0','0','0','0','0' };
	//�������������
	Huffman_Code(Huffman_root, code, 0);
	printf ("\n");
	HuffmanStatistics(weight, length);
	printf("\n\n\n");
	system("pause"); 
}
