// Skilaverkefni2.cpp : Defines the entry point for the console application.
//

#include "pch.h"
#include <cmath>
#include "IpTools.cpp"

using namespace Functions;
using namespace IpTools;

int networkBitCount(int networkCount)
{
	return ceil(log2(networkCount));
}

int magicNumber(int bitsInFirstNetwork, int bitCount)
{
	return pow(2, 32 - (bitsInFirstNetwork + bitCount));
}

unsigned long long calcSubentMask(int bitsInFirstNetwork)
{
	unsigned long long subnet = 255255255255;
	int toRemove = 1;
	int currentPart = 3;
	for (int i = 0; i < (32 - bitsInFirstNetwork - 2); i++)
	{
		if (to_string(toRemove).find("128") != string::npos)
		{
			cout << i;
			int length = to_string(toRemove).length();
			toRemove = 1 << (8 * (length - 3));
		}
		subnet -= toRemove;
		toRemove *= 2;
	}
	return subnet;
}

void printIpTableHeader()
{
	cout << "IP net        Fyrsta nothæfa Síðasta nothæfa Broadcast     Maski" << endl;
	cout << "-------------------------------------------------------------------------- - " << endl;
}

void printIpRow(string ip, string firstUsableIp, string lastUsableIp, string broadcast, string mask)
{
	cout << ip << " " << firstUsableIp << " " << lastUsableIp << " " << broadcast << " " << mask << endl;
}

int roundToNearestUsableNetworkSize(int networkSize)
{
	int num = 1;
	int lastNum;
	while (true)
	{
		lastNum = num;
		num *= 2;
		if (num > networkSize)
		{
			return ((networkSize - lastNum) > (num - networkSize)) ? num : lastNum;
		}
	}
}

void calculateAndPrintIpAddresses(unsigned long long baseIp, int bitsInFirstNetwork, int networkCount, int* networkSizes = 0)
{
	const int bitCount = networkBitCount(networkCount);
	const int magicNum = magicNumber(bitsInFirstNetwork, bitCount);
	int ip = baseIp;

	printIpTableHeader();

	for (int i = 0; i < networkCount; i++)
	{
		int networkSize = 0;

		if (networkSizes == 0) networkSize = magicNum * (i + 1);
		else networkSize = roundToNearestUsableNetworkSize(networkSizes[i]);

		string ipAddr = IpToString(ip); // IP net
		string firstUsable = IpToString(ip + 1); // Fyrsta nothæfa
		string lastUsable = IpToString(ip + networkSize - 2); // Síðasta nothæfa
		string broadcast = IpToString(ip + networkSize - 1); // Broadcast
		string mask = IpToString(calcSubentMask(bitsInFirstNetwork) - magicNum - 1); // Maski
		printIpRow(ipAddr, firstUsable, lastUsable, broadcast, mask); // Prenat út ip tölurnar

		ip += networkSize;
	}
}

int main()
{
	while (true)
	{
		string firstIp = Input("Sláðu inn ip tölu: ");

		const int bitsInFirstNetwork = IntInput("Fjöldi neta í upphafsneti: ");
		const int networkCount = IntInput("Fjöldi neta sem á að skipta upphafsnetinu í: ");

		int *hostsOnNetworks = new int[100];
		if (Input("Eiga öll netin að vera jafn stór (j/n)? ") == "j")
		{
			string *hostsStrings = new string[100];
			string hostsOnNetworkStr = Input("Sláðu inn fjölda hosta á hverju neti með kommu á milli: ");
			SplitString(hostsOnNetworkStr, ',', hostsStrings);
			ArrayStringToInt(hostsStrings, hostsOnNetworks, 4);
		}

		calculateAndPrintIpAddresses(IpToInt(firstIp), bitsInFirstNetwork, networkCount, hostsOnNetworks);
	}
	return 0;
}

