// Fixed XOR:- take 3 hex numbers and xor them and give result in xor format

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

char bincharstohex(string bin_str)
{
    if(bin_str == "0000")
    {
        return '0';
    }
    else if(bin_str == "0001")
    {
        return '1';
    }
    else if(bin_str == "0010")
    {
        return '2';
    }
    else if(bin_str == "0011")
    {
        return '3';
    }
    else if(bin_str == "0100")
    {
        return '4';
    }
    else if(bin_str == "0101")
    {
        return '5';
    }
    else if(bin_str == "0110")
    {
        return '6';
    }
    else if(bin_str == "0111")
    {
        return '7';
    }
    else if(bin_str == "1000")
    {
        return '8';
    }
    else if(bin_str == "1001")
    {
        return '9';
    }
    else if(bin_str == "1010")
    {
        return 'A';
    }
    else if(bin_str == "1011")
    {
        return 'B';
    }
    else if(bin_str == "1100")
    {
        return 'C';
    }
    else if(bin_str == "1101")
    {
        return 'D';
    }
    else if(bin_str == "1110")
    {
        return 'E';
    }
    else if(bin_str == "1111")
    {
        return 'F';
    }

    return '/';
}

string bintohex(string binstr)
{
    string hexstr = "";
    for(int i = 0; i< binstr.size();i=i+4)
    {
        string temp = binstr.substr(i,4);
        hexstr = hexstr + bincharstohex(temp);
    }

    return hexstr;
}

string perform_fixed_xor(string b1, string b2)
{
    string res = "";
    for(int i=0; i<b1.size();i++)
    {
        if(b1[i] == b2[i])
        {
            res = res + '0';
        }
        else{
            res = res + '1';
        }
    }

    return res;
}


int main()
{
    string hex1, hex2;
    cout<<"Enter the 1st hexadecimal string:-\n";
    cin>>hex1;
    cout<<"Enter the 2nd hexadecimal string:-\n";
    cin>>hex2;

    if(hex1.size() != hex2.size())
    {
        cout<<"Strings of unequal sizes!!!";
        return 1;
    }

    string bin1 = hextobin(hex1);
    string bin2 = hextobin(hex2);

    string xor_res = perform_fixed_xor(bin1, bin2);

    cout<<"Binary result of fixed xor:- " << xor_res << "\n";

    string hex_res = bintohex(xor_res);

    cout<<"hexadecimal result of fixed xor:- " << hex_res << "\n";

    return 0;


}


