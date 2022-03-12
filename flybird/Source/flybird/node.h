
#pragma once
# include <iostream>
 
template <class DataType>
class Node
{
	
public:
	DataType data;
	Node<DataType> *prior;
	Node<DataType> *next;
	Node();
	Node(DataType data_, Node<DataType> *prior_, Node<DataType> *next_);
 
};
template <class DataType>
Node<DataType>::Node()//定义一个空结点
{
	prior = NULL;
	next = NULL;
}
 
template <class DataType>
Node<DataType>::Node(DataType data_, Node<DataType> *prior_ , Node<DataType> *next_ )//定义一个完整结点
{
	prior = prior_;
	next = next_;
	data = data_;
}