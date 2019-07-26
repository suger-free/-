#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>

#define MAXNUM 20		//最大可处理的带权值叶子节点数

using namespace std;

double count[MAXNUM];     //记录哈夫曼编码的码长 

//树节点定义
typedef struct TREE_Node
{
	double weight;   
	struct TREE_Node *L_Child, *R_Child;
} treeNode;

//从数组weight[]中的length个权值建立哈夫曼树，返回树根指针
treeNode *Huffman_Create(double *weight, int n)
{
	//由权值生成左右子树均为NULL的森林
	treeNode **weightForest = NULL, *temp = NULL;
	weightForest = (treeNode**)malloc(n * sizeof (treeNode));
	for (int i = 0; i < n; i++)
	{
		weightForest[i] = (treeNode *)malloc(sizeof (treeNode));
		weightForest[i]->weight = weight[i];
		weightForest[i]->L_Child = weightForest[i]->R_Child = NULL;
	}        
	//进行length-1次循环生成哈夫曼树
	for (int i = 0; i < n-1; i++)
	{
		int j = 0, k1, k2;
		double min;

		//找出权值最小的所在位置，即数组下标
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
		temp->L_Child = weightForest[k1];//将最小的作为新节点的左子树
		weightForest[k1] = NULL;

		//找出权值次小的所在位置
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
		temp->R_Child = weightForest[k2];//将次小的作为新节点的右子树

		//计算新节点的权值
		temp->weight = temp->L_Child->weight + temp->R_Child->weight;
		weightForest[k2] = temp;//将新节点放到数组中以参与下次比较
	}
	free(weightForest);
	return temp;
}

double ave_length;  //在哈夫曼编码函数中计算平均码长 
//输出每个权值相对应的哈夫曼编码
void Huffman_Code(treeNode *root, char *code, int i)
{
	if (root->L_Child == NULL && root->R_Child == NULL)
	{
		printf("\n权值为 %.3f的元素的哈夫曼编码为: ", root->weight);
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
	printf (" 信源熵H(x)为: %.4lf (bit/sign)   \n", entropy);
	printf (" 平均码长Κ为：%.4lf (bit/sign)  \n", ave_length);
	printf (" 编码效率η为: %.4lf%%  \n", eta);
}

int main(int argc, const char* argv[])
{
	double weight[MAXNUM];
	int length = -1, sum = 0;
	//从键盘读入权值
	printf("Please input weight(input \"q\" to quit): ");
	while (scanf("%lf", &weight[++length]));
	//建立哈夫曼树
	treeNode *Huffman_root = Huffman_Create(weight,length);
	//创建临时数组存储哈夫曼编码
	memset(count, 0, sizeof(count));
	char code[MAXNUM] = { '0','0','0','0','0','0','0','0' };
	//输出哈夫曼编码
	Huffman_Code(Huffman_root, code, 0);
	printf ("\n");
	HuffmanStatistics(weight, length);
	printf("\n\n\n");
	system("pause"); 
}
