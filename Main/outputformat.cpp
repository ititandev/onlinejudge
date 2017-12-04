#include <regex>
#include <iostream>
#include <string>
#include <fstream>
#include "MyException.h"
using namespace std;

class Token
{
private:
	string token;
	string Value;
	string Key;
public:
	Token(const string& token)
	{
		this->token = token;
		regex r("(.*):(.*)");
		smatch sm;
		if (regex_match(token, sm, r))
		{
			Value = sm[2];
			Key = sm[1];
			regex r1("[a-zA-Z]*");
			if (!regex_match(Key, r1))
				throw MyException("Invalid Token Format");
		}
		else throw MyException("Invalid format token");
	}
	string getValue()
	{
		return Value;
	}
	string getKey()
	{
		return Key;
	}
};
vector<Token> getTokens(const string& tokens)
{
	regex r(",");
	sregex_token_iterator first(begin(tokens), end(tokens), r, -1), last;
	return { first,last };
}
//Token has format: ${type}[attribute]
const string word = "([a-zA-Z]+)";
const string Int = "([+-]?[0-9]\\d*|0)";
const string Float = "([+-]?(?:[0-9]+(?:[.][0-9]*)?|[.][0-9]+))";
string makeRegex(const string& token)
{
	regex r("\\$([a-zA-Z]+)\\[(.+)\\]|\\$([a-zA-Z]+)");
	string reg;
	smatch sm;
	if (!regex_match(token,sm,r))
	{
		throw MyException("Invalid format");
	}
	else
	{
		string type, attr;
		if (sm[1]=="")
		{
			type = sm[3];
			if (type == "word") return word;
			else if (type == "int") return Int;
			else if (type == "float") return Float;
		}
		else
		{
			type = sm[1];
			attr = sm[2];
			if (type == "word")
			{
				if (Token(attr).getKey() == "numbers")
				{
					int number = stoi(Token(attr).getValue());
					reg = word;
					for (int i = 1; i < number; ++i) reg += "\\s+"+word ;
				}
			}
			else if (type == "int")
			{
				if (Token(attr).getKey() == "numbers")
				{
					int number = stoi(Token(attr).getValue());
					reg = Int;
					for (int i = 1; i < number; ++i) reg += "\\s+"+Int;
				}
			}
			else if (type == "float")
			{
				if (Token(attr).getKey() == "numbers")
				{
					int number = stoi(Token(attr).getValue());
					reg = Float;
					for (int i = 0; i < number; ++i) reg +="\\s+"+ Float;
				}
			}
			return reg;
		}
		
	}
}
vector<string> getFormat(const string& format)
{
	regex r("\\s");
	sregex_token_iterator first(begin(format), end(format), r, -1), last;
	return {first,last };
}
string getType(const string& format)
{
	regex r("\\$([a-zA-Z]+)\\[?");
	smatch sm;
	regex_match(format, sm, r);
	return sm[1];
}
bool CompareFile(fstream& f1, fstream& f2, fstream& ffor)
{
	if (!f1 || !f2 || !ffor)
	{
		throw MyException("Can't open input file!");
	}
	while (!ffor.eof())
	{
		string format;
		string s1;
		string s2;
		getline(ffor, format);
		getline(f1,s1);
		getline(f2, s2);
		vector<string> vFor = getFormat(format);
		string reg;
		reg = makeRegex(vFor[0]);
		for (int i = 1; i < vFor.size(); ++i) reg += "\\s+" + makeRegex(vFor[i]);
		smatch sm1, sm2;
		regex r(reg);
		if(!regex_match(s1, sm1, r)||!regex_match(s2, sm2, r))
		{
			throw MyException("File input don't match with file format");
		}
		for (int i = 1; i < sm1.size(); ++i)
		{
			if (sm1[i] != sm2[i]) return false;
		}
	}
	return true;
}
//int main()
//{
//	try
//	{
//		cout<<CompareFile(fstream("C:\\Users\\Tuan-Kiet\\source\\repos\\Format\\Debug\\f1.txt"), fstream("C:\\Users\\Tuan-Kiet\\source\\repos\\Format\\Debug\\f2.txt"), fstream("C:\\Users\\Tuan-Kiet\\source\\repos\\Format\\Debug\\format.txt"));
//	}
//	catch (exception& e)
//	{
//		cout << e.what();
//	}
//	system("pause");
//}