#include<iostream>
#include<vector>
#include<stdlib.h>
#include<map>
#include<bitset>
#include<cmath>
#include<algorithm>

using namespace std;

vector<char> tier_1 = {'J','j','X','x','Q','q','Z','z'};
vector<char> tier_2 = {'Y','y','P','p','B','b','V','v','K','k'};
vector<char> tier_3 = {'D','d','L','l','C','c','U','u','M','m', 'W','w','F','f','G','g'};
vector<char> tier_4 = {'T','t','A','a','O','o','I','i','N','n','S','s','H','h','R','r'};
vector<char> tier_5 = {'E','e',' '};

int max_score = -170;
char key = '?';
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

void score_output_string(string output_string, char c)
{
    int score = 0;
    for(char c: output_string)
    {
        int no = static_cast<int>(c);
        if(c<=32 || c>=126)
        {
            score = score - 5;
        }
        else if(find(tier_1.begin(), tier_1.end(), c) != tier_1.end())
        {
            score+=1;
        }
        else if(find(tier_2.begin(), tier_2.end(), c) != tier_2.end())
        {
            score+=2;
        }
        else if(find(tier_3.begin(), tier_3.end(), c) != tier_3.end())
        {
            score+=3;
        }
        else if(find(tier_4.begin(), tier_4.end(), c) != tier_4.end())
        {
            score+=4;
        }
        else if(find(tier_5.begin(), tier_5.end(), c) != tier_5.end())
        {
            score+=5;
        }

    }

    if(max_score < score)
    {
        max_score = score;
        key = c;
    }

    cout << "Score for " << c << ": " << score << "\n";

}




void process_string_per_char(string input_bin_string,char c)
{
    
    // cout<< "Binary string: " << input_bin_string << "\n";
    // cout<< "Length: " << input_bin_string.length() << "\n";
    string res = "";
    for (int i=0; i<272; i=i+8)
    {
        string to_process = input_bin_string.substr(i,8);
        int decimal_no = bin_to_dec(to_process);
        char output = c ^ static_cast<char>(decimal_no);
        res = res + output;
    }

    if (c == 'X')
    {
        cout<< "For character " << c << " output string: " << res << "\n";
    }
    score_output_string(res,c);
}


void process_string(string input_hex_string)
{
    string input_bin_string = hextobin(input_hex_string);
    for(int i=0; i< 256; i++)
    {
        char c = static_cast<char>(i);
        process_string_per_char(input_bin_string, c);
        
    }
}




int main()
{
    string input_string = "1b37373331363f78151b7f2b783431333d78397828372d363c78373e783a393b3736";

    // map<char,int> char_record;
    // for(char c: input_string)
    // {
    //     if( char_record.find(c) != char_record.end())
    //     {
    //         char_record[c]++;
    //     }
    //     else
    //     {
    //         char_record[c] = 1;
    //     }
    // }

    // for(const auto& pair : char_record)
    // {
    //     cout << pair.first << " : " << pair.second << "\n";
    // }

    process_string(input_string);
    cout << key << " : " << max_score << "\n";
    return 0;



}