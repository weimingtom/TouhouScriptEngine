#include "THScript.h"
#include "function.h"
#include "ScriptExec.h"
#include "stdafx.h"

class ScriptExec_Impl
{
public:
	ScriptExec_Impl(THScript* script):_script(script),_symRoot(new SymbolTable(*_script->symRoot))	
	{
		
	}

	// ִ�нű�
	void Run()
	{
		int count = static_cast<int>(_script->scriptGroup.size());

		for (int s_idx = 0; s_idx < count; ++s_idx)
		{
			// �趨��ǰ������
			_top = _symRoot;

			// �ű�����ջ�ռ�
			vector<string> stack;
			int stack_top = -1;

			int count = _script->scriptGroup[s_idx]->quadList.size();

			// ����ÿһ�仰��ִ��
			for (int c_idx = 0; c_idx < count; ++c_idx)
			{
				Quad* quad = _script->scriptGroup[s_idx]->quadList[c_idx];
				string op = quad->op, 
					arg_1 = quad->arg1,
					arg_2 = quad->arg2,
					obj   = quad->obj;

				if (op == "push")
				{
					stack.push_back(arg_1);
					++stack_top;
				}
				else if (op == "pop")
				{
					for (int idx = 0; idx < StringToInt(arg_1); ++idx)
					{
						stack.pop_back();
						--stack_top;
					}
				}
				else if (op == "call")	
				{
					if (arg_1 == "SYS_F_ChangeTableArea")	// �������������
					{
						int symTabId = StringToInt(stack.back());

						_top = _symRoot->_FindSymbolTable(symTabId);

						assert(_top != NULL  && "Script run symbolTable error(Invalid access : NULL)");
					}
					else if (arg_1 == "sys_print")	// ������
					{
						// ���ֲ²⺯����ջ�ķ���̫sb�ˣ���Ҫ�ģ�������push������������⣬pop������
						int sum = StringToInt(_script->scriptGroup[s_idx]->quadList[c_idx + 1]->arg1);

						cout << "print: " ;
						for (int idx = 0; idx < sum; ++idx)
						{
							if (isContain(stack[stack_top - idx], "SYS_STR_"))
								cout << removeSystemMark(stack[stack_top - idx], "SYS_STR_");
							else
								cout << _getVal(stack[stack_top - idx]);
						}
						cout << endl;
					}	
				}
				else if (op == "goto")
				{
					c_idx = _goto(s_idx, obj) - 1;
				}
				else if (op == "iffalse")
				{
					vector<string> equality = split(arg_1, ' ');

					if (equality.size() == 1)	// ����ֻ��һ��ʱ
					{
						if (!_getVal(equality[0]))
							c_idx = _goto(s_idx, obj) - 1;
					}
					else
					{
						if (_iffalse(equality[0], equality[1], equality[2]))
							c_idx = _goto(s_idx, obj) - 1;
					}
				}
				else if (op == "if")
				{
					vector<string> equality = split(arg_1, ' ');

					if (equality.size() == 1)	// ����ֻ��һ��ʱ
					{
						if (_getVal(equality[0]))
							c_idx = _goto(s_idx, obj) - 1;
					}
					else
					{
						if (!_iffalse(equality[0], equality[1], equality[2]))
							c_idx = _goto(s_idx, obj) - 1;
					}
				}
				else if (op == "=")
				{
					double val = _getVal(arg_1);

					_top->GetSymbol(obj)->value = val;
				}
				else if (op == "+=")
				{
					double val = _getVal(arg_1);

					_top->GetSymbol(obj)->value += val;
				}
				else if (op == "-=")
				{
					double val = _getVal(arg_1);

					_top->GetSymbol(obj)->value -= val;
				}
				else if (op == "*=")
				{
					double val = _getVal(arg_1);

					_top->GetSymbol(obj)->value *= val;
				}
				else if (op == "/=")
				{
					double val = _getVal(arg_1);

					_top->GetSymbol(obj)->value /= val;
				}
				else if (op == "+" && arg_1 != "")	// ��Ԫ+
				{
					double val_1 = _getVal(arg_1);
					double val_2 = _getVal(arg_2);

					_top->GetSymbol(obj)->value = val_1 + val_2;
				}
				else if (op == "+" && arg_1 == "")	// һԪ+
				{
					double val_2 = _getVal(arg_2);

					_top->GetSymbol(obj)->value = val_2;
				}
				else if (op == "-" && arg_1 != "")	// ��Ԫ-
				{
					double val_1 = _getVal(arg_1);
					double val_2 = _getVal(arg_2);

					_top->GetSymbol(obj)->value = val_1 - val_2;
				}
				else if (op == "-" && arg_1 == "")	// һԪ-
				{
					double val_2 = _getVal(arg_2);

					_top->GetSymbol(obj)->value = -val_2;
				}
				else if (op == "*")
				{
					double val_1 = _getVal(arg_1);
					double val_2 = _getVal(arg_2);

					_top->GetSymbol(obj)->value = val_1 * val_2;
				}
				else if (op == "/")
				{
					double val_1 = _getVal(arg_1);
					double val_2 = _getVal(arg_2);

					_top->GetSymbol(obj)->value = val_1 / val_2;
				}
				else if (op == ">")
				{
					double val_1 = _getVal(arg_1);
					double val_2 = _getVal(arg_2);

					_top->GetSymbol(obj)->value = val_1 > val_2;
				}
				else if (op == ">=")
				{
					double val_1 = _getVal(arg_1);
					double val_2 = _getVal(arg_2);

					_top->GetSymbol(obj)->value = val_1 >= val_2;
				}
				else if (op == "<")
				{
					double val_1 = _getVal(arg_1);
					double val_2 = _getVal(arg_2);

					_top->GetSymbol(obj)->value = val_1 < val_2;
				}
				else if (op == "<=")
				{
					double val_1 = _getVal(arg_1);
					double val_2 = _getVal(arg_2);

					_top->GetSymbol(obj)->value = val_1 <= val_2;
				}
				else if (op == "==")
				{
					double val_1 = _getVal(arg_1);
					double val_2 = _getVal(arg_2);

					_top->GetSymbol(obj)->value = val_1 == val_2;
				}
				else if (op == "!=")
				{
					double val_1 = _getVal(arg_1);
					double val_2 = _getVal(arg_2);

					_top->GetSymbol(obj)->value = val_1 != val_2;
				}
				else if (op == "!")
				{
					double val_2 = _getVal(arg_2);

					_top->GetSymbol(obj)->value = !val_2;
				}
				else if (op == "++" && arg_1 == "")	// ����++
				{
					Symbol* sym = _top->GetSymbol(arg_2);

					sym->value++;
					_top->GetSymbol(obj)->value = sym->value;
				}
				else if (op == "++" && arg_2 == "")	// ǰ��++
				{
					Symbol* sym = _top->GetSymbol(arg_1);

					_top->GetSymbol(obj)->value = sym->value;
					sym->value++;
				}
				else if (op == "--" && arg_1 == "")	// ����--
				{
					Symbol* sym = _top->GetSymbol(arg_2);

					sym->value--;
					_top->GetSymbol(obj)->value = sym->value;
				}
				else if (op == "--" && arg_2 == "")	// ǰ��--
				{
					Symbol* sym = _top->GetSymbol(arg_1);

					_top->GetSymbol(obj)->value = sym->value;
					sym->value--;
				}

			}
		}
	}

	~ScriptExec_Impl()
	{
		delete _symRoot;
		_symRoot = NULL;
	}

private:
	THScript* const	_script;	// �����õĽű��������ɸı�
	SymbolTable*	_symRoot;	// ִ��������ı����� 
	SymbolTable*	_top;		// ��ǰ��������

	// ������з�ȫ�ֱ�����ֵ
	void _clearNotGlobalSymTable(SymbolTable* symTable)
	{
		for (vector<SymbolTable*>::iterator itor = symTable->son.begin(); 
			itor != symTable->son.end(); ++itor)
		{
			(*itor)->ResetSymbolTableValue();
		}
	}

	// ��ȡһ������ʵ�ʵ�ֵ(����ζ����������һ�����������߾���һ������)
	double	_getVal(string arg)
	{
		if (isdigit(arg[0]))
			return StringToInt(arg);
		else
		{
			return _top->GetSymbol(arg)->value;
		}
	}

	// ��ת��ָ����������ִ��
	int _goto(int scriptGroupId, string lineId)
	{
		int count = _script->scriptGroup[scriptGroupId]->quadList.size();
		for (int c_idx = 0; c_idx < count; ++c_idx)
		{
			if (isContain(_script->scriptGroup[scriptGroupId]->quadList[c_idx]->lineID, lineId))
			{
				return c_idx;
			}
		}

		return -1;
	}

	// ����iffalse���ж�����
	int	_iffalse(string l_str, string cmp_str, string r_str)
	{
		int _flag = 1;

		if (cmp_str == ">")
		{
			if (_getVal(l_str) > _getVal(r_str))
				_flag = 0;
		}
		else if (cmp_str == ">=")
		{
			if (_getVal(l_str) >= _getVal(r_str))
				_flag = 0;
		}
		else if (cmp_str == "<")
		{
			if (_getVal(l_str) < _getVal(r_str))
				_flag = 0;
		}
		else if (cmp_str == "<=")
		{
			if (_getVal(l_str) <= _getVal(r_str))
				_flag = 0;
		}
		else if (cmp_str == "==")
		{
			if (_getVal(l_str) == _getVal(r_str))
				_flag = 0;
		}
		else if (cmp_str == "!=")
		{
			if (_getVal(l_str) != _getVal(r_str))
				_flag = 0;
		}

		return _flag;
	}
};

ScriptExec::ScriptExec(THScript* script):_pImpl(new ScriptExec_Impl(script))
{

}

void ScriptExec::Run()
{
	_pImpl->Run();
}

ScriptExec::~ScriptExec()
{
	delete _pImpl;
	_pImpl = NULL;
}