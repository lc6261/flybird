
/*
实现双向循环链表
实现的运算操作有
 增 ,删 ,改 ,查 
 初始化, 清空 ,求线性表长度
*/
 
#include "node.h"
using namespace std;
template <class DataType>
class DoubleLinkList
{
	int length;
	Node<DataType> *head;
public:
	DoubleLinkList();//初始化————初始化一个空表，
	DoubleLinkList(const  DataType data_[],int n);//初始化————初始化一个含有数据的表
	void Insert(const DataType data_, int pos);//增————向某个位置pos之前插入一个数据data_
	void Delete(int pos);//删————删除某个位置pos处的结点
	void Change(const DataType data_,int pos);//改————改动某个位置pos处的结点
	DataType Search1(int pos);//查————根据下标查数据
	int Search2(const DataType &e);//查————根据数据查下标
	void Clear();//清空————仅保留头节点
	int GetLength();//得到长度
	void PrintAll();//遍历链表输出各节点数值
	~DoubleLinkList();//析构————删除所有结点,释放所有指针
 
};
 
 
//初始化————初始化一个空表（只有头节点）
template <typename  DataType>
DoubleLinkList<typename  DataType>::DoubleLinkList()
 {
	head = new Node<DataType>; //动态分配一个空结点，即头节点
	assert(head);
	head->prior = head;//头节点的首指针指向其本身
	head->next = head;//头节点的尾指针指向其本身
	length = 0;
 }
 
 
//初始化————初始化一个含有数据的表
//实参用数组传入要写入的数据
//由于C++中没有自带直接求数组长度的函数 
//所以需要手动把数组的长度n写进去
template <typename  DataType>
DoubleLinkList<typename  DataType>::DoubleLinkList(const DataType data_[],int n)
{
	head = new Node<DataType>; //动态分配一个空结点，即头节点
	Node<DataType> *p = head;//创建一个指向结点的指针p后面将用这个指针遍历，实现不断的加数据结点
	for (int i = 0; i < n; i++) {
		//这两行代码其实包含了四个操作
		//step1 :new运算符建立下一个结点 且通过构造函数将数据域赋值为data_[i] 
		//step2:通过构造函数将该结点的首指针指向p（即上一个节点） 尾指针指向NULL
		//step3:通过赋值运算符将上一个结点的尾指针指向下一个结点
		//step4 将指针p移动至下一个结点 以便下一步的迭代
		p->next = new Node<DataType>(data_[i], p,NULL);
		p = p->next;
	}
	length = n;
	p->next = head;
	head->prior = p;
}
 
 
//增————向某个位置pos插入一个数据data_
template <typename  DataType>
void DoubleLinkList<typename  DataType>::Insert(const  DataType data_, int pos)
{
	//step0:准备工作 建立要遍历的指针p和新建要插入的数据结点add
	Node<DataType> *p = head;//创建一个指向结点的指针p后面将用这个指针遍历
	Node<DataType> *add = new Node<DataType>(data_, NULL, NULL);//建立一个新结点，包含要插入的数据data_
	//step1:判断插入位置是否正确
	if (pos<1 || pos>length+1)
	{
		std::cout << "插入数据失败" << endl;
	}
	
	else
	{
		//step2,用指针p进行遍历，直到达到指定位置
		int i;
		for(i = 0; i < pos; i++)
		{
			p = p->next;
		}
		//step3 ,开始插入
		add->prior = p->prior;
		p->prior->next = add;
		p->prior = add;
		add->next = p;
		length += 1;
		std::cout << "插入数据成功" << endl;
	}
 
}
 
//删————删除某个位置pos的结点
template <typename  DataType>
void DoubleLinkList<typename  DataType>::Delete(int pos)
{
	//step0:准备工作 建立要遍历的指针p和新建要插入的数据结点add
	Node<DataType> *p = head;//创建一个指向结点的指针p后面将用这个指针遍历
	//step1:判断删除位置是否正确
	if (pos<1 || pos>length)
	{
		std::cout << "删除数据失败" << endl;
	}
	else
	{
		int i;
		for(i = 0; i < pos; i++)
		{
			p = p->next;
		}
	//step2:开始删除
		p->prior->next = p->next;
		p->next->prior = p->prior;
		length = length - 1;
		std::cout << "删除数据成功" << endl;
		delete p;//千万注意此处要delete指针p!
	}
}
 
 
//改————改动某个位置pos处的结点
template <typename  DataType>
void DoubleLinkList<typename  DataType>::Change(const DataType data_,int pos)
{
	//step0:准备工作 建立要遍历的指针p和新建要改动的数据结点add
	Node<DataType> *p = head;//创建一个指向结点的指针p后面将用这个指针遍历
	
	//step1:判断插入位置是否正确
	if (pos<1 || pos>length + 1)
	{
		std::cout << "改动数据失败" << endl;
	}
 
	else
	{
		int i;
		//step2,用指针p进行遍历，直到达到指定位置
		for(i = 0; i < pos; i++)
		{
			p = p->next;
		}
		//step3 ,开始改动
		Node<DataType> *change = new Node<DataType>(data_, p->prior, p->next);//建立一个新结点，包含要改动的数据data_
		p->prior->next = change;
		p->next->prior = change;
		std::cout << "改动数据成功" << endl;
		delete p;//千万注意此处要delete指针p!
	}
 
}
//查————根据下标查数据
template <typename  DataType>
DataType DoubleLinkList<typename  DataType>::Search1(int pos)
{
	//step0:准备工作 建立要遍历的指针p
	Node<DataType> *p = head;//创建一个指向结点的指针p后面将用这个指针遍历
	//step1:判断查找位置是否正确
	if (pos<1 || pos>length)
	{
		std::cout << "查找数据失败" << endl;
		return 0;
	}
	else
	{
		int i;
		for(i = 0; i < pos; i++)
		{
			p = p->next;
		}
		//step2:返回查找数据
		return p->data;
		std::cout << "查找数据成功" << endl;
 
	}
}
 
 
//查————根据数据查下标
template <typename  DataType>
int DoubleLinkList<typename  DataType>::Search2(const DataType &e)
{
	//step0:准备工作 建立要遍历的指针p
	Node<DataType> *p = head;//创建一个指向结点的指针p后面将用这个指针遍历
	//step1:开始查找
	int i = 0;
	while((i<length)&&(p->data != e))
	{
		i++;
		p = p->next;
	}
	if (p == head)
	{
		return 0;
		std::cout << "找不到该数据" << endl;
	}
	else
	{
		return i;
		std::cout << "成功找到该数据" << endl;
	}
	
}
 
//清空
template <typename  DataType>
void DoubleLinkList<typename  DataType>::Clear()
{
	int i = 0;
	while (i < length)
	{
		i++;
		Delete(1);
	}
	length = 0;
}
//析构
template <typename  DataType>
DoubleLinkList<typename  DataType>::~DoubleLinkList()
{
	Clear();
	delete head;
	cout << "析构函数已执行" << endl;
}
 
//求线性表长度
template <typename  DataType>
int DoubleLinkList<typename  DataType>::GetLength()
{
	return length;
}
//遍历输出
template <typename  DataType>
void DoubleLinkList<typename  DataType>::PrintAll()
{
	int i;
	Node<DataType> *p = head;//创建一个指向结点的指针p后面将用这个指针遍历
	cout << "该链表的所有数据如下" << endl;
	for (i = 0; i < length; i++)
	{
		p = p->next;
		cout << p->data << " ";
	}
}