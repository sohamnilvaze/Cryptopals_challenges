#include<iostream>
#include<fstream>
#include<string>
#include<cmath>
#include<algorithm>
#include<map>

using namespace std;

vector<char> tier_1 = {'J','j','X','x','Q','q','Z','z'};
vector<char> tier_2 = {'Y','y','P','p','B','b','V','v','K','k'};
vector<char> tier_3 = {'D','d','L','l','C','c','U','u','M','m', 'W','w','F','f','G','g'};
vector<char> tier_4 = {'T','t','A','a','O','o','I','i','N','n','S','s','H','h','R','r'};
vector<char> tier_5 = {'E','e',' '};


const std::map<char, float> ENGLISH_FREQS = {
    {'a', 0.0817f}, {'b', 0.0149f}, {'c', 0.0278f}, {'d', 0.0425f}, {'e', 0.1270f},
    {'f', 0.0223f}, {'g', 0.0202f}, {'h', 0.0609f}, {'i', 0.0697f}, {'j', 0.0015f},
    {'k', 0.0077f}, {'l', 0.0403f}, {'m', 0.0241f}, {'n', 0.0675f}, {'o', 0.0751f},
    {'p', 0.0193f}, {'q', 0.0009f}, {'r', 0.0599f}, {'s', 0.0633f}, {'t', 0.0906f},
    {'u', 0.0276f}, {'v', 0.0098f}, {'w', 0.0236f}, {'x', 0.0015f}, {'y', 0.0197f},
    {'z', 0.0007f}, {' ', 0.1300f}
};

double min_chi_score = numeric_limits<double>::infinity();
double max_score = numeric_limits<double>::min();
string best_string = "";
char best_char = '?';
string best_dec_string = "";

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
    if (b == "1010") return 'A';
    if (b == "1011") return 'B';
    if (b == "1100") return 'C';
    if (b == "1101") return 'D';
    if (b == "1110") return 'E';
    if (b == "1111") return 'F';
    
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

int score_output_string(string output_string, char c)
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

    // cout << "Score for " << c << ": " << score << "\n";
    return score;
}

double score_output_string2(string input_string)
{
    map<char,int> observable_characters;
    int len = input_string.length();

    if (len == 0)
    {
        return numeric_limits<double>::infinity();
    }
    for(char c: input_string)
    {
        int ascii_value = static_cast<int>(c);
        if((c<32 || c>126) && c != '\n' && c != '\r')
        {
            return numeric_limits<double>::infinity();
        }
        else
        {
            char lower_case = tolower(c);
            observable_characters[lower_case] +=1; 
        }
    }

    double chi_square_score = 0.00;
    for (const auto& [ch,freq] : ENGLISH_FREQS)
    {
        double observed = observable_characters[ch];
        double expected = len * freq;

        if (expected > 0) 
        {
            chi_square_score += pow((observed - expected), 2) / expected;
        }

    }
    // cout<< chi_square_score << "\n";
    return chi_square_score;
}

double score_output_string3(string input_string)
{
    double score = 0.00;
    for(char c : input_string)
    {
        int ascii_value = static_cast<int>(c);
        if ((ascii_value < 32 || ascii_value > 126) && c != '\n' && c != '\t' && c != 'r')
        {
            score = score - 30;
            continue;
        }

        char lower = tolower(c);

        if (lower == 'e') score += 13;
        else if (lower == 't') score += 9;
        else if (lower == 'a') score += 8;
        else if (lower == 'o') score += 8;
        else if (lower == 'i') score += 7;
        else if (lower == 'n') score += 7;
        else if (lower == 's') score += 6;
        else if (lower == 'h') score += 6;
        else if (lower == 'r') score += 6;
        else if (lower == 'd') score += 4;
        else if (lower == 'l') score += 4;
        else if (lower == 'c') score += 3;
        else if (lower == 'u') score += 3;
        else if (lower == 'm') score += 3;
        else if (lower == 'w') score += 2;
        else if (lower == 'f') score += 2;
        else if (lower == 'g') score += 2;
        else if (lower == 'y') score += 2;
        else if (lower == 'p') score += 2;
        else if (lower == 'b') score += 1;
        else if (lower == 'k') score += 1;
        // Space is incredibly common in standard prose sentences
        else if (lower == ' ') score += 13; 
        
        // Penalize weird symbols that rarely show up in plaintext prose sentences
        else if (c == '^' || c == '[' || c == ']' || c == '~' || c == '`' || c == '#') {
            score -= 5;
        }
        
    }

    return score;
}



char process_each_string(string input_string)
{
    // string binary_string = hextobin(input_string);
    int decimal_string = bin_to_dec(input_string);
    char res = static_cast<char>(decimal_string);
    return res;
}

void process_entire_string_per_char(string entire_string, char c)
{
    string res = "";
    for ( int i = 0; i < 240; i = i + 8)
    {
        string to_process = entire_string.substr(i,8);
        char p = process_each_string(to_process);
        char r = c ^ p;
        res = res + r;
    }

    // int score = score_output_string(res,c);
    double score = score_output_string3(res);
    if(score > max_score)
    {
        max_score = score;
        best_string = entire_string;
        string dec_string = "";
        if (entire_string == best_string)
        {
            cout << "For character: ";
            if (c >= 32 && c <= 126) cout << c;
            else cout << "\\x" << hex << (int)(unsigned char)c << dec; // Print control chars as hex codes

            cout << " : ";
            for (char character : res) {
                // If it's a standard printable character, print it. Otherwise, print a dot.
                if (character >= 32 && character <= 126) {
                    dec_string = dec_string + character;
                    cout << character;
                } else {
                    cout << '.'; 
                    dec_string = dec_string + '.';
                }
            }
            cout << "\n";
        }
        best_dec_string = dec_string;
        best_char = c;
    }

    

}

void process_string(string input_hex_string)
{
    string input_bin_string = hextobin(input_hex_string);
    //cout<< "Length of input hex string: " << input_hex_string.length() << "\n";
    //cout<< "Length of processed binary string: " << input_bin_string.length() << "\n";
    for(int i=0; i< 256; i++)
    {
        char c = static_cast<char>(i);
        process_entire_string_per_char(input_bin_string, c);
        
    }
    cout<<"\n";
}

int main()
{
    ifstream file("input.txt");

    if(!file.is_open())
    {
        cout<< "Failed to open the file";
        return 1;
    }

    string line;

    while(getline(file,line))
    {
        cout << "\033[1m processing: \033[0m" << line << "\n";
        process_string(line);
    }

    cout << "Best string: " << bin_to_hex_string(best_string) << "\n";
    cout << "Best char: " << best_char << "\n";
    cout << "Max score: " << max_score << "\n";
    cout << "Decrypted string: " << best_dec_string << "\n";
    
    return 0;
}