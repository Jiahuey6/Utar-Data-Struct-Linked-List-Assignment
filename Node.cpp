#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
#include "Node.h"



using type = Student;

Node::Node(type newItem)
{
	item = newItem;
	next = NULL;
}