#include "Symbol.h"

Symbol::Symbol():name("")
{

}

Symbol::Symbol(string name, int type, int kind):name(name),type(type),kind(kind)
{
	
}

Symbol::Symbol(string name, int type, int kind, double value):name(name),type(type),kind(kind),value(value)
{

}

Id* Symbol::ToID()
{
	// Ŀǰֻ֧��Double����
	Id* idTemp = new Id(new Word(name, IDEN), Type::Double, Type::Double->width);

	return idTemp;
}


Symbol::~Symbol()
{

}