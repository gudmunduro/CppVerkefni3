#pragma once
#include "pch.h"
#include <iterator>
#include <iostream>
#include <string>
#include <sstream>

using namespace std;

namespace Functions { // Fyiri einhver random f�ll sem �g held a� �g muni geta nota� aftur
	inline string Input(string message = ": ", string nullValue = "") 
	{
		// Til a� einfalda a� f� input fr� lyklabor�inu.
		cout << message;
		string input = "";
		do {
			cin >> input;
		} while (input == "");
		return input;
	}
	inline int IntInput(string message = ": ", int nullValue = -1)
	{
		// Til a� einfalda a� f� input fr� lyklabor�inu fyrir integer.
		cout << message;
		int input = nullValue;
		do {
			cin >> input;
		} while (input == -1);
		return input;
	}
	inline void IntArrayInput(int *arrayValue, string message = ": ")
	{
		// Tekur inn input sem array og setur �a� � arrayValue
		cout << message;
		for (int i = 0; i < 4; i++)
		{
			cin >> arrayValue[i];
		}
	}

	inline void SplitString(string str, char on, string *result)
	{
		string buffer;
		stringstream stream(str);

		int current = 0;
		while (getline(stream, buffer, on))
		{
			result[current] = buffer;
			current++;
		}
	}

	inline void ____SplitString2(string str, string on, string *result)
	{
		// EKKI NOTA
		int current = 0;
		string cutStrings[10000];
		cutStrings[0] = str;
		while (cutStrings[current].find_first_of(on) != 0)
		{
			const unsigned long index = cutStrings[current].find_first_of(on);
			cout << "!!    ";
			cout << cutStrings[current] << endl;
			cout << index;
			cout << cutStrings[current].substr(0, index) << endl;
			result[current] = cutStrings[current].substr(0, index);
			current++;
			cutStrings[current] = cutStrings[current - 1].substr(index + 1, cutStrings[current - 1].length());
			cout << cutStrings[current];
		}
	}

    inline void ArrayStringToInt(string* from, int* to, int size)
    {
	    for (int i = 0; i < size; i++)
        {
	        to[i] = stoi(from[i]);
        }
    }
}