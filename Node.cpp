#include "Node.h"

/// ���ڵ�
//////////////////////////////////////////////////////////////////////////

int Node::labels = 0;

Node::Node():lexline(0) {}

Node::Node(int l):lexline(l) {}

void Node::error(string s)
{
	cout << "Error:" << "near line" << lexline << ": " << s << endl;
}

int Node::newlabel()
{
	++labels;
}

Node::~Node()
{

}

/// ���ʽ
//////////////////////////////////////////////////////////////////////////

