#ifndef _H_FUNCTION
#define _H_FUNCTION

using namespace std;

// ������
extern const double MATH_PI;
extern const double MATH_PI_D;

// ��ѧ����
extern double reg(double _deg);
extern double deg(double _reg);

// ת������
extern string IntToString(int v_int);
extern string DoubleToString(double v_double);
extern int StringToInt(string str);
extern double StringToDouble(string str);
extern string AscToSign(int tag);
extern vector<string> split(string str, char ch);
extern int isContain(string str, string substr);
extern string removeSystemMark(string str, string substr);
#endif
