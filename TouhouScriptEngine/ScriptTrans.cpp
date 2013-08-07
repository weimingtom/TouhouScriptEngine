#include "THScript.h"
#include "function.h"
#include "ScriptTrans.h"
#include "stdafx.h"

using namespace std;

/// Impl
//////////////////////////////////////////////////////////////////////////


class Translator::Impl {
public:
	Impl():_streamIdx(-1),_tableId(-1) {}

	// ����ű�
	THScript* Translate(THScript *script)
	{

		string st, op, arg_1, arg_2, obj;
		string l_str,r_str, cmp_str;

		while ((st = _Next()) != "NULL")
		{
			string lineID = "";
			op = "", arg_1 = "", arg_2 = "", obj = "";

			if (st[0] == '@')									// �ű���
			{
				QuadGroup* quadGroup = new QuadGroup(st);
				script->scriptGroup.push_back(quadGroup);

				_lastGroup = quadGroup;

				continue;
			}

			while (st[st.length()- 1] == ':')					// �к� 
			{
				lineID += st;
				st = _Next();
			}

			if (st == "iffalse" || st == "if")					// if��iffalse���
			{
				op = st;

				// ��ȡ�ж�����
				l_str = _Next();
				cmp_str = _Next();

				if (cmp_str == "goto")
				{
					arg_1 = l_str;
					obj = _Next();
				}
				else
				{
					r_str = _Next();
					arg_1 = l_str + " " + cmp_str + " " + r_str;

					// ��ȡ��ת�к�
					_Next();
					obj = _Next();
				}
			}
			else if (st == "push" || st == "call" || st == "pop")
			{
				op = st;
				arg_1 = _Next();

				if (arg_1 == "SYS_F_ChangeTableArea") // ���������
				{
					_tableId = StringToInt(_lastGroup->quadList.back()->arg1);
				}
			}
			else if (st == "goto")
			{
				op = st;
				obj = _Next();
			}
			else if (st[0] == '@')	// ������һ����
			{
				_lastGroup->AddQuad(_NewQuad("SYS_V_END", arg_1, arg_2, obj, lineID));	// ֱ�Ӵ�����β���
				_Retract(1);

				continue;
			}
			else	// ���ڸ�ֵ���
			{
				obj = st;

				st = _Next();
				if (st == "+=" || st == "-=" || st == "*=" || st == "/=")	// �������
				{
					op = st;
					arg_1 = _Next();
				}
				else if (st == "=")
				{
					st = _Next();

					if (st == "+" || st == "++" || st == "-" || st == "--" || st == "!" || st == "call") // һԪ�����
					{
						op = st;
						arg_2 = _Next();
					}
					else 
					{
						arg_1 = st;

						st = _Next();
						if (st == "+" || st == "-" || st == "*" || st == "/" || st == ">" || st == ">=" || st == "<" 
							|| st == "<=" || st == "==" || st == "!=")	// ��Ԫ�����
						{
							op = st;
							arg_2 = _Next();
						}
						else if ( st == "++" || st == "--")	//����++ --
						{
							op = st;
						}
						else
						{
							op = "=";
							_Retract(1);
						}
					}
				}
			}

			_lastGroup->AddQuad(_NewQuad(op, arg_1, arg_2, obj, lineID));
			_AddTempVar(obj, script);
		}

		return script;
	}

	// ��ӵ��м������
	void Add(string word)
	{
		vector<string> _vecStr = split(word, ' ');
		
		int _count = _vecStr.size();

		for (int idx = 0; idx < _count; ++idx)
			_scriptStream.push_back(_vecStr[idx]);
	}

private:
	vector<string> _scriptStream;		// �м������
	QuadGroup* _lastGroup;				// ���һ�β����Ľű��飨�����ͷţ�
	int _streamIdx;						// ��ǰ�ű��ļ���λ��
	int _tableId;						// ��ǰ���ű�λ��

	Impl(const Impl& rhs);					// ��ֹ���ƹ���
	Impl& operator= (const Impl& rhs);		// ��ֹ��ֵ����

	// ��ȡ��һ������
	string _Next()
	{
		++_streamIdx;

		if (_streamIdx < (int)_scriptStream.size())
			return _scriptStream[_streamIdx];
		else
			return "NULL";
	}

	// �˻�ָ����Ŀ�Ĵ�
	string _Retract(int num)
	{
		_streamIdx -= num;

		assert(_streamIdx >= 0 && "Script Interpreter's _streamIdx is invalid(must >= 0)");
		return _scriptStream[_streamIdx];
	}

	// �����ʱ���������ű�
	void _AddTempVar(string name, THScript* script)
	{
		if (isContain(name, "SYS_T_"))
		{
			Symbol* sym = new Symbol(name, TYPE_DOUBLE, KIND_TVAR);
			script->symRoot->AddSymbol(sym);
		}	
		
	}

	// �½�һ��ű�
	Quad* _NewQuad(string op, string arg_1, string arg_2, string obj, string lineId)
	{
		op = (op == "") ? "SYS_V_END" : op;

		Quad* quad = new Quad(op, arg_1, arg_2, obj);

		quad->lineID = lineId;

		

		return quad;	// quad����ṩ��ֵ����������NRV�Ż�
	}
	
};



/// Translator
//////////////////////////////////////////////////////////////////////////

Translator::Translator():_pImpl(new Impl)
{
	
}

THScript* Translator::Translate(THScript *script)
{
	return _pImpl->Translate(script);
}

void Translator::Add(string word)
{
	_pImpl->Add(word);
}


Translator::~Translator()
{
	delete _pImpl;
	_pImpl = NULL;
}