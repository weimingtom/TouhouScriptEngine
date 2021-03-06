#include "Lexer.h"
#include "function.h"

/// Token
//////////////////////////////////////////////////////////////////////////

Token::Token(int t):tag(t)
{
	
}

Token::Token()
{

}

string Token::ToString()
{
	return IntToString(tag);
}

string Token::ToSign()
{
	return AscToSign(tag);
}

/// Num
//////////////////////////////////////////////////////////////////////////

Num::Num():Token(INTCON)
{

}

Num::Num(int v):Token(INTCON),value(v)
{
	
}

string Num::ToString()
{
	return IntToString(value);
}

/// Word
//////////////////////////////////////////////////////////////////////////

Word* Word::eql = new Word("==", EQL);
Word* Word::neq = new Word("!=", NEQ);
Word* Word::leq = new Word("<=", LEQ);
Word* Word::geq = new Word(">=", GEQ);
Word* Word::and = new Word("&&", AND);
Word* Word::or  = new Word("||", OR);
Word* Word::not = new Word("!", NOT);

Word* Word::plus = new Word("+", PLUS);
Word* Word::plusplus = new Word("++", PLUSPLUS);
Word* Word::minus = new Word("-", MINUS);
Word* Word::minusminus = new Word("--", MINUSMINUS);
Word* Word::mult = new Word("*", MULT);
Word* Word::div = new Word("/", DIV);
Word* Word::assign_plus = new Word("+=", ASSIGN_PLUS);
Word* Word::assign_minus = new Word("-=", ASSIGN_MINUS);
Word* Word::assign_mult = new Word("*=", ASSIGN_MULT);
Word* Word::assign_div = new Word("/=", ASSIGN_DIV);


Word* Word::lss = new Word("<", LSS);
Word* Word::gre = new Word(">", GRE);
Word* Word::assign = new Word("=", ASSIGN);
Word* Word::semicn = new Word(";", SEMICN);
Word* Word::comma = new Word(",", COMMA);
Word* Word::dot = new Word(".", DOT);

Word* Word::lparent = new Word("(", LPARENT);
Word* Word::rparent = new Word(")", RPARENT);
Word* Word::lbrace = new Word("{", LBRACE);
Word* Word::rbrace = new Word("}", RBRACE);

Word* Word::temp = new Word("t", TEMP);
Word* Word::True = new Word("true", TRUE);
Word* Word::False = new Word("false", FALSE);

Word* Word::note = new Word("//", NOTE);
Word* Word::note_a = new Word("/*", NOTE_A);
Word* Word::note_b = new Word("*/", NOTE_B);
Word* Word::null = new Word("null", NULL_A);

Word::Word():lexeme("")
{

}

Word::Word(string s, int tag):Token(tag),lexeme(s)
{

}

string Word::ToString()
{
	return lexeme;
}

/// Double
//////////////////////////////////////////////////////////////////////////

Double::Double():Token(DOUBLECON)
{

}

Double::Double(double v):Token(DOUBLECON),value(v)
{
	
}

string Double::ToString()
{
	return DoubleToString(value);
}


/// Type
//////////////////////////////////////////////////////////////////////////

Type* Type::Double = new Type("double", DOUBLETK, 8);
Type* Type::Int = new Type("int", INTTK, 4);
Type* Type::Func = new Type("func", FUNCTK ,1);
Type* Type::String = new Type("string", STRCON, 1);

Type::Type():width(0)
{

}

Type::Type(string s, int tag, int w):Word(s, tag),width(w)
{

}

bool Type::numeric(Type* p)
{
	return true;
}

Type* Type::max(Type* l_type, Type* r_type)
{
	// TO-DO: 暂时默认所有的变量都是Double类型

	return Type::Double;
}

/// Lexer
//////////////////////////////////////////////////////////////////////////

Lexer::Lexer():lineID(1),peek(' '),fileManager(0),nowWord(-1)
{
	Reserve(new Word("if", IFTK));
	Reserve(new Word("else", ELSETK));
	Reserve(new Word("while", WHILETK));
	Reserve(new Word("loop", LOOPTK));
	Reserve(new Word("var", VARTK));
	Reserve(new Word("for", FORTK));

	Reserve(new Word("#TouhouScript", TOUHOUSCRIPT));
	Reserve(new Word("#Title", TITLE));
	Reserve(new Word("#Text", TEXT));
	Reserve(new Word("#Music", MUSIC));
	Reserve(new Word("#Image", IMAGE));
	Reserve(new Word("#BackGround", BACKGROUND));
	Reserve(new Word("#Player", PLAYER));
	Reserve(new Word("#ScriptVersion", SCRIPTVERSION));

	Reserve(new Word("@MainLoop", MAINLOOPTK));
	Reserve(new Word("@Initialize", INITTK));
	Reserve(new Word("@Finalize",FINALTK));
	Reserve(new Word("@Background", BACKGROUNDTK));
	Reserve(new Word("script_stage_main", STAGEMAIN));
	Reserve(new Word("script_enemy_main", ENEMYMAIN));

	fileManager = fileManager->Instance();
}

void Lexer::Reserve(Word* w)
{
	words.insert(make_pair(w->ToString(), w));
}

void Lexer::ReadCh()
{
	peek = fileManager->ReadCh();
}

bool Lexer::ReadCh(char ch)
{
	ReadCh();

	if (peek != ch) return false;	// 匹配失败
	peek = ' ';		// 匹配成功，下一个字符预置成空
	return true;	

}

string Lexer::getString() {
	string bufferStr = "";
	do 
	{
		bufferStr.append(1,peek);
		ReadCh();
	} while (isalpha(peek) || isdigit(peek) || peek == '_');

	fileManager->Retrack(1);

	return bufferStr;
}

Token* Lexer::Scan()
{
	// To-do: 读取一个单词并返回
	peek = ' ';
	for(;;ReadCh())
	{
		if ( peek == ' ' || peek == '\t' || peek == '[' || peek == ']') continue;
		else if (peek == '\n') ++lineID;
		else if (peek == EOF)
			break;		
		else break;
	}

	switch (peek)		// 判断各种字符
	{
	case '&':
		if (ReadCh('&')) return Word::and;
		else
		{
			fileManager->Retrack(1);
			return new Token('&');
		}
	case '|':
		if (ReadCh('|')) return Word::or;
		else
		{
			fileManager->Retrack(1);
			return new Token('|');
		}
	case '=':
		if (ReadCh('=')) return Word::eql;
		else 
		{
			fileManager->Retrack(1);
			return Word::assign;
		}
	case '!':
		if (ReadCh('=')) return Word::neq;
		else 
		{
			fileManager->Retrack(1);
			return Word::not;
		}
	case '<':
		if (ReadCh('=')) return Word::leq;
		else
		{
			fileManager->Retrack(1);
			return Word::lss;
		}
	case '>':
		if (ReadCh('=')) return Word::geq;
		else
		{
			fileManager->Retrack(1);
			return Word::gre;
		}
	case '+':
		{
			ReadCh();

			if (peek == '+') return Word::plusplus;
			else if (peek == '=') return Word::assign_plus;
			else
			{
				fileManager->Retrack(1);
				return Word::plus;
			}
		}
	case '-':
		{
			ReadCh();

			if (peek == '-') return Word::minusminus;
			else if (peek == '=') return Word::assign_minus;
			else
			{
				fileManager->Retrack(1);
				return Word::minus;
			}
		}
		
	case '"':
		{
			Word* w;
			string str = "";

			while (!ReadCh('"'))
			{
				if (peek >= 35 && peek <= 126)
				{
					str.append(1, peek);
				}
			}

			w = new Word(str, STRCON);
			return w;
		}
	case '/':
		{
			ReadCh();

			if (peek == '/')
			{
				while (!ReadCh('\n')) { };
				fileManager->Retrack(1);
				return Word::null;
			}
			else if (peek == '*')		// 去掉所有注释
			{
				while (true) 
				{
					if (peek == '\n')	// 行数正常增加
						++lineID;

 					if (ReadCh('*'))
					{
						if (ReadCh('/'))
							return Word::null;
						else
							fileManager->Retrack(1);
					}
				}
			}
			else if (peek == '=')
				return Word::assign_div;
			else
			{
				fileManager->Retrack(1);
				return Word::div;
			}

			break;
		}
		
	case '*':	
		{
			ReadCh();

			if (peek == '=')
				return Word::assign_mult;
			else
			{
				fileManager->Retrack(1);
				return Word::mult;
			}
			
		}
		
	case ';':	return Word::semicn;
	case ',':	return Word::comma;
	case '(':	return Word::lparent;
	case ')':	return Word::rparent;
	case '{':	return Word::lbrace;
	case '}':	return Word::rbrace;
 	default:
		break;
	}

	if (isdigit(peek))	// 如果读取到的是数字
	{

		double doubleValue = 0;	// 保存DOUBLE
		
		do 
		{
			doubleValue = doubleValue * 10 + (peek - '0');
			ReadCh();
		} while (isdigit(peek));

		if (peek == '.')
		{
			ReadCh();
			double mod = 1;

			while (isdigit(peek))
			{
				mod *= 10;
				doubleValue += (peek - '0') / mod;
				ReadCh();
			}
		}

		fileManager->Retrack(1);

		return new Double(doubleValue);
	}

	if (isalpha(peek) || (peek == '@' || peek == '#' || peek == '_'))		// 如果是字符串或者是特定的字串
	{
		string bufferStr = getString();
		
		Word* w;

		if (words.find(bufferStr) != words.end())		// 已经存在了
		{
			w = (Word*)words[bufferStr];
			return w;
		}

		w = new Word(bufferStr, IDEN);
		words.insert(make_pair(bufferStr, w));
		return w;
	}

	Token* token = new Token(peek);
	peek = ' ';
	return token;
}

void Lexer::MakeWordStream()
{
	// To-do: 构造语法分析使用的单词流

	Token* token;

	do 
	{
		token = Scan();

		if (token->tag != NULL_A && token->tag != EOF)
		{
			wordStream.push_back(token);
			wordLine.push_back(lineID);

			cout << token->ToString() << "\t\t" << token->ToSign() << endl;
		}

	} while (token->tag != EOF);
}

Token* Lexer::ScanWord()
{
	nowWord++;

	if (nowWord < wordStream.size())
	{
		line = wordLine[nowWord];
		return wordStream[nowWord];
	}
	else
	{
		return NULL;
	}
}

Token* Lexer::RetrackWord(int num)
{
	if (nowWord - num < 0)
	{
		cout << "error: Lexer倒读超越了单词流边界" << endl;
		exit(1);
	}
	
	nowWord -= num;
	line = wordLine[nowWord];
	return wordStream[nowWord];
}