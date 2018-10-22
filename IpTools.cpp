//
// Created by gudmundur on 15.10.2018.
//

#include "pch.h"
#include "Functions.cpp"

using namespace Functions;

namespace IpTools {
    inline unsigned long long IpToInt(int *ipArray)
    {
        // Breytir ip t�lu �r array yfir � t�lu(sem long long) og skilar �v�
        return ipArray[0] << 24|ipArray[1] << 16|ipArray[2] << 8|ipArray[3];
    }
    inline unsigned long long IpToInt(string ip)
    {
        string *ipArrayStr = new string[4];
        SplitString(ip, '.', ipArrayStr);
        return stoi(ipArrayStr[0].c_str()) << 24|stoi(ipArrayStr[1].c_str()) << 16|stoi(ipArrayStr[2].c_str()) << 8|stoi(ipArrayStr[3].c_str());
    }
    inline void IpIntToArray(int *ipArray, unsigned long long ip)
    {
        //Breytir ip t�lu �r t�lu(long long) yfir � array og setur �a� � ipArray
        for (int i = 0; i < 4; i++)
        {
            ipArray[i] = (ip >> ((4 - 1 - i) * 8)) & 0xff;
        }
    }
    inline void IpStringToArray(int *ipArray, string ip)
    {
        string *ipArrayStr = new string[4];
        SplitString(ip, '.', ipArrayStr);
        for (int i = 0; i < 4; i++)
        {
            ipArray[i] = stoi(ipArrayStr[i]);
        }
    }

	inline string IpToString(unsigned long long ip)
	{
		// Breytir ip t�lu �r t�lu(long long) og skilar �v�
		string ipString = "";
		for (int i = 0; i < 4; i++)
		{
			ipString += (i != 0) ? "." : ""; // B�ta vi� p�nkt fyrir allt nema fyrsta
			ipString += to_string((ip >> ((4 - 1 - i) * 8)) & 0xff);
		}
		return ipString;
	}

    inline string IpToString(int* ipArray)
    {
        // Breytir ip t�lu �r arry yfir � string me� p�nktum � milli og skilar �v�
        return to_string(ipArray[0]) + "." + to_string(ipArray[1]) + "." + to_string(ipArray[2]) + "." + to_string(ipArray[3]) + ".";
    }
}