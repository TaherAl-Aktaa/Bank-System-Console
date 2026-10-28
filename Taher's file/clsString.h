#pragma once
#include<iostream>
#include<vector>

using namespace std;

class clsString
{

	string _Value;

	static char _invertChar(char Ch)
	{
		Ch = (isupper(Ch)) ? tolower(Ch) : toupper(Ch);
		return Ch;
	}

	static bool _isVowel(char Letter)
	{
		Letter = tolower(Letter);

		return ((Letter == 'a') || (Letter == 'e') || (Letter == 'i') || (Letter == 'o') || (Letter == 'u'));
	}

public:

	clsString()
	{
		_Value = "";
	}

	clsString(string Value)
	{
		_Value = Value;
	}

	void setValue(string Value)
	{
		_Value = Value;
	}

	string getValue()
	{
		return _Value;
	}

	__declspec(property(get = getValue, put = setValue)) string Value;


	static void printFirstLetterInEachWord(string Text)
	{
		bool IsFirstLetter = true;

		for (short i = 0; i < Text.length(); i++)
		{
			if (Text.at(i) != ' ' && IsFirstLetter)
				cout << Text.at(i) << '\n';

			IsFirstLetter = (Text.at(i) == ' ') ? true : false;
		}
	}

	void printFirstLetterInEachWord()
	{
		printFirstLetterInEachWord(_Value);
	}

	static string upperFirstLetterInEachWord(string& Text)
	{
		bool IsFirstLetter = true;

		for (short i = 0; i < Text.length(); i++)
		{
			if (Text.at(i) != ' ' && IsFirstLetter)
				Text.at(i) = toupper(Text.at(i));

			IsFirstLetter = (Text.at(i) == ' ') ? true : false;
		}

		return Text;
	}

	void upperFirstLetterInEachWord()
	{
		upperFirstLetterInEachWord(_Value);
	}

	static string lowerFirstLetterInEachWord(string& Text)
	{
		bool IsFirstLetter = true;

		for (short i = 0; i < Text.length(); i++)
		{
			if (Text.at(i) != ' ' && IsFirstLetter)
				Text.at(i) = tolower(Text.at(i));

			IsFirstLetter = (Text.at(i) == ' ') ? true : false;
		}

		return Text;
	}

	void lowerFirstLetterInEachWord()
	{
		lowerFirstLetterInEachWord(_Value);
	}

	static string upperString(string Text)
	{
		for (short i = 0; i < Text.length(); i++)
			Text.at(i) = toupper(Text.at(i));

		return Text;
	}

	static string lowerString(string Text)
	{
		for (short i = 0; i < Text.length(); i++)
			Text.at(i) = tolower(Text.at(i));

		return Text;
	}

	void upperString()
	{
		_Value = upperString(_Value);
	}


	void lowerString()
	{
		_Value = lowerString(_Value);
	}

	static string invertString(string& Text)
	{
		for (short i = 0; i < Text.length(); i++)
			Text.at(i) = _invertChar(Text.at(i));

		return Text;
	}

	void invertString()
	{
		invertString(_Value);
	}

	static short countCapitalLetters(string Text)
	{
		short Counter = 0;

		for (short i = 0; i < Text.length(); i++)
		{
			if (isupper(Text.at(i)))
				Counter++;
		}

		return Counter;
	}

	short countCapitalLetters()
	{
		return countCapitalLetters(_Value);
	}

	static short countSmallLetters(string Text)
	{
		short Counter = 0;

		for (short i = 0; i < Text.length(); i++)
		{
			if (islower(Text.at(i)))
				Counter++;
		}

		return Counter;
	}

	short countSmallLetters()
	{
		return countSmallLetters(_Value);
	}

	static short countLetter(string Text, char Letter, bool CaseSensetive = true)
	{
		short Counter = 0;

		for (short i = 0; i < Text.length(); i++)
		{
			if (CaseSensetive)
			{
				if (Text.at(i) == Letter)
					Counter++;
			}
			else
			{
				if (tolower(Text.at(i)) == tolower(Letter))
					Counter++;
			}
		}

		return Counter;
	}

	short countLetter(char Letter, bool CaseSensetive = true)
	{
		return countLetter(_Value, Letter, CaseSensetive);
	}

	static short countVowels(string Text)
	{
		short Counter = 0;

		for (short i = 0; i < Text.length(); i++)
		{
			if (_isVowel(Text.at(i)))
				Counter++;
		}

		return Counter;
	}

	short countVowels()
	{
		return countVowels(_Value);
	}

	static short countWords(string Text)
	{
		short Counter = 0;

		string delim = " ";

		string Word;
		short pos;

		while ((pos = Text.find(delim)) != Text.npos)
		{
			Word = Text.substr(0, pos);

			if (Word != "")
				Counter++;

			Text.erase(0, pos + delim.length());
		}

		if (Text != "")
			Counter++;

		return Counter;
	}

	short countWords()
	{
		return countWords(_Value);
	}

	static vector<string> splitString(string Text, string Delim)
	{
		vector<string> vWords;

		string Word;
		short pos;

		while ((pos = Text.find(Delim)) != Text.npos)
		{
			Word = Text.substr(0, pos);

			if (Word != "")
				vWords.push_back(Word);

			Text.erase(0, pos + Delim.length());
		}

		if (Text != "")
			vWords.push_back(Text);

		return vWords;
	}

	vector<string> splitString(string Delim)
	{
		return splitString(_Value, Delim);
	}

	static string trimLeft(string Text)
	{
		for (short i = 0; i < Text.length(); i++)
		{
			if (Text.at(i) != ' ')
				return Text.substr(i, Text.length() - 1);
		}

		return Text;
	}

	void trimLeft()
	{
		_Value = trimLeft(_Value);
	}

	static string trimRight(string Text)
	{
		for (short i = Text.length() - 1; i >= 0; i--)
		{
			if (Text.at(i) != ' ')
				return Text.substr(0, i + 1);
		}

		return Text;
	}

	void trimRight()
	{
		_Value = trimRight(_Value);
	}

	static string trim(string Text)
	{
		return trimLeft(trimRight(Text));
	}

	void trim()
	{
		_Value = trim(_Value);
	}

	static string reverseWords(string Text, string Delim)
	{
		vector<string> vWords = splitString(Text, Delim);

		string ReversedText = "";

		vector<string>::iterator itWord;

		for (itWord = --vWords.end(); itWord != vWords.begin(); itWord--)
		{
			ReversedText.append(*itWord);
			ReversedText.append(Delim);
		}

		ReversedText.append(*vWords.begin());

		return ReversedText;
	}

	void reverseWords(string Delim)
	{
		_Value = reverseWords(_Value, Delim);
	}

	static string replaceWord(string Text, string OriginalWord, string NewWord, bool CaseSensetive = true)
	{
		string TempText = Text;
		string TempOriginalWord = OriginalWord;

		if (!CaseSensetive)
		{
			TempOriginalWord = lowerString(OriginalWord);
			TempText = lowerString(Text);
		}

		short pos = TempText.find(TempOriginalWord);

		while (pos != TempText.npos)
		{
			Text.replace(pos, OriginalWord.length(), NewWord);
			TempText.replace(pos, OriginalWord.length(), NewWord);
			pos = TempText.find(TempOriginalWord);
		}

		return Text;
	}

	void replaceWord(string OrginalWord, string NewWord, bool CaseSensetive = true)
	{
		_Value = replaceWord(_Value, OrginalWord, NewWord, CaseSensetive);
	}

	static string removePunctuationFromString(string Text)
	{
		string Temp;

		for (short i = 0; i < Text.length(); i++)
		{
			if (!ispunct(Text.at(i)))
				Temp += Text.at(i);
		}

		return Temp;
	}

	void removePunctuationFromString()
	{
		_Value = removePunctuationFromString(_Value);
	}
};