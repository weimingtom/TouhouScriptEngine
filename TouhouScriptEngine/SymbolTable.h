#ifndef _H_SYMBOLTABLE
#define _H_SYMBOLTABLE

#include "Symbol.h"

class SymbolTable
{
public:
	static int _nextId;					// 下一个Id

	SymbolTable* father;				// 父表
	map<string, Symbol*> symbolMap;		// 符号Map
	vector<SymbolTable*> son;			// 下属符号表
	int sonIndex;						// 下一个要获取的符号表
	int tableId;						// 符号表Id，用以区分不同的符号表
	
	SymbolTable();
	explicit SymbolTable(SymbolTable* father);
	explicit SymbolTable(const SymbolTable& rhs);
	

	void AddSymbol(Symbol* symbol);		// 添加一个新符号=
	void ResetSymbolTableStatus();		// 重置所有符号表的状态
	void ResetSymbolTableValue();		// 重置所有符号表的初始数据
	SymbolTable* MakeNewSymbolTable();	// 生成一个新的符号表
	SymbolTable* GetNextSymbolTable();	// 获得下一个符号表
	Symbol* GetSymbol(string name);		// 获得一个符号

	Symbol* _FindSymbol(SymbolTable* symTable,string name);	// 在指定符号表中搜索指定名称的符号
	SymbolTable* _FindSymbolTable(int id);					// 根据指定的Id寻找该符号表以下同Id的符号表并返回

	~SymbolTable();

private:
	SymbolTable* operator= (const SymbolTable& ths);		// 禁止赋值复制构造
};

#endif // !_H_SYMBOLTABLE
