//Convert hex to base64
// hex -> bin -> base64

#include<iostream>
#include<vector>
#include<algorithm>
#include<stdlib.h>
#include<cmath>

using namespace std;

string hexchartobinary(char c)
{
    switch(toupper(c))
    {
        case '0': return "0000";
        case '1': return "0001";
        case '2': return "0010";
        case '3': return "0011";
        case '4': return "0100";
        case '5': return "0101";
        case '6': return "0110";
        case '7': return "0111";
        case '8': return "1000";
        case '9': return "1001";
        case 'A': return "1010";
        case 'B': return "1011";
        case 'C': return "1100";
        case 'D': return "1101";
        case 'E': return "1110";
        case 'F': return "1111";
        default : return "";

    }

    return "";
}

string hextobin(string str)
{
    string binstr = "";
    for(char c : str)
    {
        binstr = binstr + hexchartobinary(c);
    }

    return binstr;
}

int bin_to_dec(string bin)
{
    int dec = 0;
    for(int i=0; i<bin.length();i++)
    {
        if(bin[i] == '1')
        {
            dec = dec + (int)pow((double)2, double(bin.length() - i - 1));
        }
    }
    return dec;
}

string bin_to_base64(string bin)
{
    string res = "";
    int n = bin.length();
    if(n % 6 != 0)
    {
        while(bin.length() % 6 != 0)
        {
            bin = bin + '0';
        }
        n = bin.length();
    }

    for(int i=0; i<n;i = i+6)
    {
        string temp = bin.substr(i,6);
        int dec = bin_to_dec(temp);
        if(dec <= 25)
        {
            res = res + static_cast<char>(dec + 65);
        }
        else if(25 < dec && dec<=51)
        {
            res = res + static_cast<char>(dec + 71);
        }
        else if( 51 < dec && dec <= 61)
        {
            res = res + static_cast<char>(dec - 4);
        }
        else if(dec == 62)
        {
            res = res + '+';
        }
        else{
            res = res + '/';
        }

    }

    return res;


}


int main()
{
    string input;
    cout<<"Enter the input hex string:-\n";
    getline(cin,input);

    string binary_str = hextobin(input);
    cout<<"Corrosponding binary string is: "<< binary_str << "\n";

    string base64_str = bin_to_base64(binary_str);

    cout<<"Corrosponding base64 string is: "<< base64_str << "\n";

    return 0;


}