#include "THScript.h"
#include "function.h"



THScript::THScript():symRoot(NULL),_streamIdx(-1)
{

}

void THScript::SetValue(string varStr, string value)
{
	if (varStr == "#TouhouScript")
		touhouScript = value;
	else if (varStr == "#Title")
		title = value;
	else if (varStr == "#Text")
		text = value;
	else if (varStr == "#Music")
		music = value;
	else if (varStr == "#Image")
		image = value;
	else if (varStr == "#BackGround")
		background = value;
	else if (varStr == "#Player")
		player = value;
	else if (varStr == "#ScriptVersion")
		scriptVersion = value;
}

void THScript::AddToStream(string str) 
{
	vector<string> result = split(str, ' ');

	for (int i = 0; i < result.size(); ++i)
	{
		scriptStream.push_back(result[i]);
	}
}

string THScript::_NextWord()
{
	++_streamIdx;

	if (_streamIdx < scriptStream.size())
		return scriptStream[_streamIdx];
	else
		return "NULL";
}

string THScript::_RetrackWord(int num)
{
	_streamIdx -= num;

	if (_streamIdx < 0)
		cout << "�ű���������е�����Խ��" << endl;
	else
		return scriptStream[_streamIdx];
}

void THScript::_MakeNewQuad(string op, string arg_1, string arg_2, string obj, string lineID)
{
	Quad* quad;

	if (op == "")
		quad = new Quad("END", arg_1, arg_2, obj);
	else
		quad = new Quad(op, arg_1, arg_2, obj);

	if (lineID != "")
		quad->lineID = lineID;

	_lastGroup->AddQuad(quad);
}

void THScript::TranslateScript()
{
	string st, op, arg_1, arg_2, obj;
	string l_str,r_str, cmp_str;

	while ((st = _NextWord()) != "NULL")
	{
		string lineID = "";
		op = "", arg_1 = "", arg_2 = "", obj = "";

		if (st[0] == '@')									// �ű���
		{
			QuadGroup* quadGroup = new QuadGroup(st);
			scriptGroup.push_back(quadGroup);

			_lastGroup = quadGroup;

			continue;
		}

		while (st[st.length()- 1] == ':')					// �к� 
		{
			lineID += st;
			st = _NextWord();
		}

		if (st == "iffalse" || st == "if")					// if��iffalse���
		{
			op = st;

			// ��ȡ�ж�����
			l_str = _NextWord();
			cmp_str = _NextWord();
			
			if (cmp_str == "goto")
			{
				obj = _NextWord();
			}
			else
			{
				r_str = _NextWord();
				arg_1 = l_str + " " + cmp_str + " " + r_str;

				// ��ȡ��ת�к�
				_NextWord();
				obj = _NextWord();
			}
		}
		else if (st == "push" || st == "call")
		{
			op = st;
			arg_1 = _NextWord();
		}
		else if (st == "goto")
		{
			op = st;
			obj = _NextWord();
		}
		else if (st[0] == '@')	// ������һ����
		{
			_MakeNewQuad("END", arg_1, arg_2, obj, lineID);	// ֱ�Ӵ�����β���
			_RetrackWord(1);

			continue;
		}
		else	// ���ڸ�ֵ���
		{
			obj = st;

			st = _NextWord();
			if (st == "+=" || st == "-=" || st == "*=" || st == "/=")	// �������
			{
				op = st;
				arg_1 = _NextWord();
			}
			else if (st == "=")
			{
				st = _NextWord();

				if (st == "+" || st == "++" || st == "-" || st == "--" || st == "!" || st == "call") // һԪ�����
				{
					op = st;
					arg_1 = _NextWord();
				}
				else 
				{
					arg_1 = st;

					st = _NextWord();
					if (st == "+" || st == "-" || st == "*" || st == "/" || st == ">" || st == ">=" || st == "<" 
						|| st == "<=" || st == "==" || st == "!=")	// ��Ԫ�����
					{
						op = st;
						arg_2 = _NextWord();
					}
					else
					{
						op = "=";
						_RetrackWord(1);
					}
				}
			}
		}

		_MakeNewQuad(op, arg_1, arg_2, obj, lineID);
	}
}

THScript::~THScript()
{

}