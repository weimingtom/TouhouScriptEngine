#ifndef _SCRIPT_TRANS
#define _SCRIPT_TRANS

class Translator
{
public:
	Translator();

	THScript*	Translate(THScript *script);	// ����ű�
	void		Add(string word);				// ��ӵ��м������

	~Translator();
private:
	class Impl;
	Impl *_pImpl;
};

#endif // !_SCRIPT_TRANS
