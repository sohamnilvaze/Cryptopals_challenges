#include<iostream>
#include<string>
#include<algorithm>
#include<cmath>
#include<vector>

using namespace std;

string dec_to_bin (const int ascii_value)
{
    int temp = ascii_value;
    string res = "";
    while(temp > 0)
    {
        if (temp % 2 == 0)
        {
            res = res + '0';
        }
        else
        {
            res = res + '1';
        }
        temp = temp / 2;
    }

    while ( res.length() < 8)
    {
        res = res + '0';
    }

    reverse(res.begin(),res.end());

    return res;

}

vector<string> process_to_bytes(string input_string)
{
    vector<string> bytes;

    for(char c : input_string)
    {
        int ascii_value = static_cast<int>(c);
        string byte_value = dec_to_bin(ascii_value);
        bytes.push_back(byte_value);
    }

    return bytes;
}

string process_each_byte(string byte1, string byte2)
{
    string res = "";
    if (byte1.length() != byte2.length())
    {
        cout<< "Two byte lengths are not matching" << "\n";
        return " ";
    }

    for(int i = 0; i<8; i++)
    {
        char bit1 = byte1[i] - '0';
        char bit2 = byte2[i] - '0';
        char c = (bit1 ^ bit2) + '0';
        res = res + c;
    }
    // cout << "res for process_each_byte: " << res << "\n";
    return res;
}

string repeating_xor(vector<string> to_process, vector<string> key)
{
    int k = key.size();
    string net_res = "";
    int len = to_process.size();
    for(int i = 0; i<len; i++)
    {
        string res = process_each_byte(to_process[i],key[i % k]);
        net_res = net_res + res;
    }

    return net_res;

}

char binarytohexchar(const string& b)
{
    // Fast lookup using a switch statement
    if (b == "0000") return '0';
    if (b == "0001") return '1';
    if (b == "0010") return '2';
    if (b == "0011") return '3';
    if (b == "0100") return '4';
    if (b == "0101") return '5';
    if (b == "0110") return '6';
    if (b == "0111") return '7';
    if (b == "1000") return '8';
    if (b == "1001") return '9';
    if (b == "1010") return 'a';
    if (b == "1011") return 'b';
    if (b == "1100") return 'c';
    if (b == "1101") return 'd';
    if (b == "1110") return 'e';
    if (b == "1111") return 'f';
    
    return '\0'; // Return null character for invalid inputs
}

string bin_to_hex_string(const string& bin_string)
{
    string res = "";
    for(int i=0; i< bin_string.length(); i = i+4)
    {
        string to_process = bin_string.substr(i,4);
        res = res + binarytohexchar(to_process);
    }

    return res;
}





int main()
{

    string input = "Burning 'em, if you ain't quick and nimble I go crazy when I hear a cymbal";
    string key = "ICE";

    vector<string> input_bytes = process_to_bytes(input);
    vector<string> key_bytes = process_to_bytes(key);
    cout << "input bytes : \n";
    for (string s : input_bytes)
    {
        cout << s << " ";
    }
    cout << "\n";
    cout << "key bytes : \n";
    for (string s : key_bytes)
    {
        cout << s << " ";
    }
    cout << "\n";
    string res = repeating_xor(input_bytes, key_bytes);
    string hex_res = bin_to_hex_string(res);
    cout << hex_res << "\n";
    return 0;
}