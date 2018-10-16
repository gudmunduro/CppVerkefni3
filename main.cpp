// Skilaverkefni2.cpp : Defines the entry point for the console application.
//

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

void calculateAndPrintIpAddresses(unsigned long long baseIp, int bitsInFirstNetwork, int networkCount)
{
    const int bitCount = networkBitCount(networkCount);
    const int magicNum = magicNumber(bitsInFirstNetwork, bitCount);

    printIpTableHeader();
    for (int i = 0; i < networkCount; i++)
    {
        string ipAddr = IpToString(baseIp + magicNum * i); // IP net
        string firstUsable = IpToString(baseIp + magicNum * i + 1); // Fyrsta nothæfa
        string lastUsable = IpToString(baseIp + magicNum * (i + 1) - 2); // Síðasta nothæfa
        string broadcast = IpToString(baseIp + magicNum * (i + 1) - 1); // Broadcast
        string mask = IpToString(calcSubentMask(bitsInFirstNetwork) - magicNum - 1); // Maski
        printIpRow(ipAddr, firstUsable, lastUsable, broadcast, mask); // Prenat út ip tölurnar
    }
}

int main()
{
    while (true)
    {
        string firstIp = Input("Sláðu inn ip tölu: ");

        const int bitsInFirstNetwork = IntInput("Fjöldi neta í upphafsneti: ");
        const int networkCount = IntInput("Fjöldi neta sem á að skipta upphafsnetinu í: ");

        string *hostsOnNetworks = new string[100];
        if (Input("Eiga öll netin að vera jafn stór (j/n)? ") == "j")
        {
            string hostsOnNetworkStr = Input("Sláðu inn fjölda hosta á hverju neti með kommu á milli: ");
           SplitString(hostsOnNetworkStr, ',', hostsOnNetworks);
        }

        calculateAndPrintIpAddresses(IpToInt(firstIp), bitsInFirstNetwork, networkCount);
    }
    return 0;
}

