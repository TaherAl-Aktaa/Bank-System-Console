#pragma once
#include<iostream>
#include<string>
#include<iomanip>
#define ll long long

using namespace std;

class clsUtil
{

public:

    enum enCharType { Capital, Small, Digit, Special, Mix };

	static void Srand()
	{
		srand((unsigned)time(NULL));
	}

	static int RandomNumber(int From, int To)
	{
		return rand() % (To - From + 1) + From;
	}

	static char getRandomCharacter(enCharType WantedData)
    {
        switch (WantedData)
        {
        case Capital:
            return char(RandomNumber(65, 90));
        case Small:
            return char(RandomNumber(97, 122));
        case Digit:
            return char(RandomNumber(48, 57));
        case Special:
            return char(RandomNumber(33, 64));
        case Mix:
            return getRandomCharacter(enCharType(RandomNumber(0, 2)));
        }
    }

    static string generateWord(enCharType CharType, short Length)
    {
        string Word;

        for (int i = 0; i < Length; i++)
            Word += getRandomCharacter(CharType);

        return Word;
    }

    static string generateKey(enCharType CharType, short Parts = 4)
    {
        if (Parts == 1)
            return generateWord(CharType, 4);

        return generateWord(CharType, 4) + "-" + generateKey(CharType, Parts - 1);
    }

    static void generateKeys(int NumberOfKeys, enCharType CharType)
    {
        for (int i = 1; i <= NumberOfKeys; i++)
            cout << "Key [" << setw(2) << i << "] : " << generateKey(CharType) << '\n';
    }

    static void shuffleArray(int Array[], int ArraySize)
    {
        for (int i = 0; i < ArraySize; i++)
        {
            swap(Array[RandomNumber(1, ArraySize) - 1], Array[RandomNumber(1, ArraySize) - 1]);
        }
    }

    static void shuffleArray(string Array[], int ArraySize)
    {
        for (int i = 0; i < ArraySize; i++)
        {
            swap(Array[RandomNumber(1, ArraySize) - 1], Array[RandomNumber(1, ArraySize) - 1]);
        }
    }
    
    static void fillArrayWithRandomNumbers(int Array[], int ArraySize, int From, int To)
    {
        for (int i = 0; i < ArraySize; i++)
            Array[i] = RandomNumber(From, To);
    }

    static void fillArrayWithRandomWords(string Array[], int ArraySize, enCharType CharType, short WordLength)
    {
        for (int i = 0; i < ArraySize; i++)
            Array[i] = generateWord(CharType, WordLength);

    }
    
    static void fillArrayWithKeys(string Array[], int ArraySize, enCharType CharType)
    {
        for (int i = 0; i < ArraySize; i++)
            Array[i] = generateKey(CharType);

    }

    static string Tabs(short NumberOfTabs)
    {
        string s;

        for (int i = 0; i < NumberOfTabs; i++)
            s += '\t';

        return s;
    }

    static string encryptText(string Text, int EncryptionKey = 10)
    {
        for (int i = 0; i < Text.length(); i++)
        {
            Text[i] = char(int(Text[i]) + EncryptionKey);
        }

        return Text;
    }

    static string decryptText(string Text, int EncryptionKey = 10)
    {
        for (int i = 0; i < Text.length(); i++)
        {
            Text[i] = char(int(Text[i]) - EncryptionKey);
        }

        return Text;
    }

    static string NumberToText(int Number)
    {
        if (Number == 0)
            return "";

        if (Number >= 1 && Number <= 19)
        {
            string arr[] = { "",
            "One","Two","Three","Four","Five","Six","Seven",
            "Eight","Nine","Ten","Eleven","Twelve","Thirteen","Fourteen",
            "Fifteen","Sixteen","Seventeen","Eighteen","Nineteen" };
            return arr[Number] + " ";
        }

        if (Number >= 20 && Number <= 99)
        {
            string arr[] = {
            "","","Twenty","Thirty","Forty","Fifty","Sixty","Seventy","Eighty"
            ,"Ninety" };
            return arr[Number / 10] + " " + NumberToText(Number % 10);
        }

        if (Number >= 100 && Number < 200)
            return "One Hundred " + NumberToText(Number % 100);


        if (Number >= 200 && Number < 1e3)
            return NumberToText(Number / 100) + "Hundreds " + NumberToText(Number % 100);

        if (Number >= 1e3 && Number < 2000)
            return "One Thousand " + NumberToText(Number % 1000);

        if (Number >= 2000 && Number < 1e6)
            return NumberToText(Number / 1000) + "Thousands " + NumberToText(Number % 1000);

        if (Number >= 1e6 && Number < 2e6)
            return "One Million " + NumberToText(Number % 1000000);

        if (Number >= 2e6 && Number < 1e9)
            return NumberToText(Number / int(1e6)) + "Millions " + NumberToText(Number % int(1e6));


        if (Number >= 1e9 && Number < 2e9)
            return "One Billion " + NumberToText(Number % (int)1e9);

        else
            return NumberToText(Number / (ll)1e9) + "Billions " + NumberToText(Number % (ll)1e9);
    }

};

