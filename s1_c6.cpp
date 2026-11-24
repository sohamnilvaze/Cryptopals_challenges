#include<iostream>
#include<string>
#include<cmath>
#include<algorithm>
#include<fstream>
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
    // cout << res.length()<<"\n";
    return res;

}

int getbase64Value( char ch)
{
    if  ( ch >= 'A' && ch <= 'Z')
    {
        return ch - 'A';
    }
    if (ch >= 'a' && ch <= 'z')
    {
        return ch - 'a' + 26;
    }
    if ( ch >= '0' && ch <='9')
    {
        return ch - '0' + 52;
    }
    if(ch == '+')
    {
        return 62;
    }
    if(ch == '/')
    {
        return 63;
    }

    return -1;

}

string base64_to_bits(string input_string)
{    
    string allbits = "";
    int padding_count = 0;


    for(char ch : input_string)
    {
        if ( ch == '=')
        {
            padding_count++;
            continue;
        }
        int val = getbase64Value(ch);
        if ( val == -1)
        {
        continue;
        }

        for(int i = 5; i>=0; --i)
        {
            int bit  = ( val >> i) & 1;
            if(bit == 1)
            {
                allbits = allbits + '1';
            }
            else{
                allbits = allbits + '0';
            }

        }

        


    }
    int bitsToRemove = 2 * padding_count;
    if(bitsToRemove > 0 && allbits.size() >= static_cast<size_t>(bitsToRemove))
    {
        allbits.erase(allbits.size() - bitsToRemove); // removing the bits to be removed from trailing position

    }

    return allbits;

}

int compute_hamming_distance(string str1, string str2)
{
    // string str1_bits = to_bits(str1);
    // string str2_bits = to_bits(str2);
    if(str1.length() != str2.length())
    {
        cout << "Cannot compute hamming distance as the lengths of both the input strings is not equal";
        return 0;
    }

    int dist = 0;
    for(int i=0;i<str1.length();i++)
    {
        if(str1[i] != str2[i])
        {
            dist++;
        }
    }
    return dist;

}

double analyse_for_keysize(string input_bitstring, int key_size)
{
    double normalized_hamming_dist;
    double total_hamming_dist = 0.00;
    int no_of_pairs = 0.00;
    int len = input_bitstring.length();
    
    for(int i = 0; i + (key_size*16) < len;i = i + (key_size*16))
    {
        string str1 = input_bitstring.substr(i,8*key_size);
        string str2 = input_bitstring.substr(i + 8*key_size, 8*key_size);
        double ham_dist = compute_hamming_distance(str1,str2);
        total_hamming_dist = total_hamming_dist + ham_dist;
        no_of_pairs+=1;
    }

    normalized_hamming_dist = total_hamming_dist / no_of_pairs;
    return normalized_hamming_dist / ((double)key_size * 8);
    // return total_hamming_dist;
}

double analyse_for_keysize2(string input_bitstring, int key_size)
{
    double normalised_hamming_dist;
    double total_hamming_dist = 0.00;
    int no_of_groups = 0.00;
    int len = input_bitstring.length();
    
    for(int i=0; i + (key_size*32) < len; i = i + (key_size*32))
    {
        string bl1 = input_bitstring.substr(i, 8*key_size);
        string bl2 = input_bitstring.substr(i+8*key_size, 8*key_size);
        string bl3 = input_bitstring.substr(i+16*key_size, 8*key_size);
        string bl4 = input_bitstring.substr(i+24*key_size, 8*key_size);
        double dist1 = compute_hamming_distance(bl1,bl2);
        double dist2 = compute_hamming_distance(bl1,bl3);
        double dist3 = compute_hamming_distance(bl1,bl4);
        double dist4 = compute_hamming_distance(bl2,bl3);
        double dist5 = compute_hamming_distance(bl2,bl4);
        double dist6 = compute_hamming_distance(bl3,bl4);
        double avg_dist = (dist1+dist2+dist3+dist4+dist5+dist6) / 6.00;
        total_hamming_dist = total_hamming_dist + avg_dist;
        no_of_groups+=1;
    }
    if (no_of_groups == 0)
    {
        return 999.0;
    }
    normalised_hamming_dist = total_hamming_dist / no_of_groups;
    return normalised_hamming_dist / (double)key_size;

}


vector<pair<int,double>> process_for_all_keysizes(string input_bitstring)
{
    vector<pair<int,double>> norm_ham_dist_map;
    for(int k = 2; k<41;k++)
    {
        double norm_ham_dist = analyse_for_keysize2(input_bitstring,k);
        // cout<< "For key size " << k << " : " << norm_ham_dist << "\n";
        norm_ham_dist_map.push_back({k,norm_ham_dist});
    }
    return norm_ham_dist_map;
}

vector<string> break_into_blocks(string input_bitstring, int key_size)
{
    vector<string> blocks;
    
    for(int i=0; i< input_bitstring.length();i = i+(key_size*8))
    {
        blocks.push_back(input_bitstring.substr(i,key_size*8));
    }
    return blocks;
}

vector<string> transpose_blocks(vector<string> blocks, int key_size)
{
    vector<string> transposed_blocks;
    for(int i=0; i<key_size;i++)
    {
        string res = "";
        int bit_offset = i * 8;
        for(int j = 0; j<blocks.size();j++)
        {
            if ( bit_offset + 8 <= blocks[j].length())
            {
                res = res + blocks[j].substr(bit_offset,8);
            }
        }
        transposed_blocks.push_back(res);
    }

    return transposed_blocks;
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
        unsigned char uc = static_cast<unsigned char>(c);
        int ascii_value = static_cast<int>(uc);
        if ((ascii_value < 32 || ascii_value > 126) && c != '\n' && c != '\t' && c != '\r')
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
        else if (lower == ' ') score += 5; 
        
        // Penalize weird symbols that rarely show up in plaintext prose sentences
        else if (c == '^' || c == '[' || c == ']' || c == '~' || c == '`' || c == '#') {
            score -= 5;
        }
        
    }

    return score;
}

double score_output_string4(const string& text) {
    // Standard English letter frequencies + space
    static const unordered_map<char, double> freq = {
        {' ', 13.0}, {'e', 12.7}, {'t', 9.1}, {'a', 8.2}, {'o', 7.5},
        {'i', 7.0},  {'n', 6.7},  {'s', 6.3}, {'h', 6.1}, {'r', 6.0},
        {'d', 4.3},  {'l', 4.0},  {'c', 2.8}, {'u', 2.8}, {'m', 2.4},
        {'w', 2.4},  {'f', 2.2},  {'g', 2.0}, {'y', 2.0}, {'p', 1.9},
        {'b', 1.5},  {'v', 1.0},  {'k', 0.8}, {'j', 0.15},{'x', 0.15},
        {'q', 0.10}, {'z', 0.07}
    };

    double score = 0.0;
    for (unsigned char ch : text) {
        char lower = tolower(ch);
        if (freq.count(lower)) {
            score += freq.at(lower);
        } else if (ch == '\n' || ch == '\r' || ch == '\'' || ch == ',' || ch == '.' || ch == '!' || ch == '?' || ch == '-' || ch == ':') {
            score += 1.0; // Common punctuation & newlines in lyrics
        } else if (ch >= '0' && ch <= '9') {
            score += 0.5;
        } else if (ch >= 32 && ch <= 126) {
            score -= 5.0; // Weird symbols like {, }, |, ^, ~, `, @, #
        } else {
            score -= 20.0; // Non-printable control bytes (0x00-0x1F, 0x7F-0xFF)
        }
    }
    return score;
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


char process_each_string(string input_string)
{
    // string binary_string = hextobin(input_string);
    int decimal_string = bin_to_dec(input_string);
    char res = static_cast<char>(decimal_string);
    return res;
}

void process_entire_string_per_char(string entire_string, char c, double& max_score, string& best_string, string& best_dec_string, char& best_char)
{
    string res = "";
    
    
    for ( int i = 0; i < entire_string.length(); i = i + 8)
    {
        string to_process = entire_string.substr(i,8);
        char p = process_each_string(to_process);
        char r = c ^ p;
        res = res + r;
    }

    // int score = score_output_string(res,c);
    double score = score_output_string4(res);
    if(score > max_score)
    {
        max_score = score;
        best_string = entire_string;
        string dec_string = "";
        for (char character : res) {
            // If it's a standard printable character, print it. Otherwise, print a dot.
            if (character >= 32 && character <= 126) {
                dec_string = dec_string + character;
                //cout << character;
            } else {
                //cout << '.'; 
                dec_string = dec_string + '.';
            }
        }
        best_dec_string = dec_string;
        best_char = c;
    }

    

}

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


string process_string(string input_bin_string, vector<char>& keys)
{
    //string input_bin_string = hextobin(input_hex_string);
    //cout<< "Length of input hex string: " << input_hex_string.length() << "\n";
    //cout<< "Length of processed binary string: " << input_bin_string.length() << "\n";
    double max_score = numeric_limits<double>::lowest();
    string best_string = "";
    char best_char = '?';
    string best_dec_string = "";

    for(int i=0; i< 256; i++)
    {
        char c = static_cast<char>(i);
        process_entire_string_per_char(input_bin_string, c, max_score, best_string, best_dec_string, best_char);
        
    }
    string hex_input_string = bintohex(input_bin_string);
    // cout << "For input string: " << hex_input_string << " best char: ";
    if (best_char >= 32 && best_char <= 126) {
        cout << best_char;
    } else {
        cout << "\\x" << hex << (int)(unsigned char)best_char << dec;
    }
    // cout << " | Decrypted preview: " << best_dec_string << "\n";
    
    if(best_dec_string.length() > 0)
    {
        keys.push_back(best_char);
    }
    return best_dec_string;
}






int main()
{
    // string str1 = "this is a test";
    // string str2 = "wokka wokka!!!";

    // cout << compute_hamming_distance(str1,str2)<<"\n";

    ifstream file("s1c6_input.txt");

    if(!file.is_open())
    {
        cout << "Failed to open the file";
        return 1;
    }

    string input_text = "";
    char ch;
    while(file.get(ch))
    {
        if ( ch != '\n' && ch != '\r' && ch != ' ')
        {
            input_text = input_text + ch;
        }
    
    }
    cout<< input_text << "\n";
    // cout << input_text.length() << "\n";
    string input_bitstring = base64_to_bits(input_text);
    cout<< input_bitstring << "\n";
    vector<pair<int,double>> norm_ham_dist_map = process_for_all_keysizes(input_bitstring);
    sort(norm_ham_dist_map.begin(), norm_ham_dist_map.end(),[](const auto& a, const auto& b){
        return a.second < b.second;
    });
    vector<int>top_keysizes;
    for( auto& pair : norm_ham_dist_map)
    {
        cout<< pair.first << " : " << pair.second << "\n";
        while(top_keysizes.size() < 5)
        {
            top_keysizes.push_back(pair.first);
        }
    }

    // vector<int> selected_key_sizes = {20,37,12,4,32};
    
    
    
    // vector<int> selected_key_sizes2 = {4,12,20,8,16,24};
    
    map<int, vector<char>> all_keys;
    map<int,string> all_decstrings;
    for(int key_size: top_keysizes)
    {
        cout << "For key size: " << key_size << "\n";
        vector<char> keys;
        vector<string> blocks = break_into_blocks(input_bitstring,key_size);
        cout<< "blocks:" << blocks.size() <<  "\n";
        
        vector<string> transposed_blocks = transpose_blocks(blocks, key_size);
        cout<<"transposed blocks:" << transposed_blocks.size() << "\n";
        string entire_dec_string = "";
        for(string str: transposed_blocks)
        {
            entire_dec_string = entire_dec_string + process_string(str,keys);
        }
        // cout<< " Keys:\n";
        // for(char c : keys)
        // {
        //     cout<<c << " ";
        // }
        all_keys[key_size] = keys;
        all_decstrings[key_size] = entire_dec_string;

    }


    for( const auto& [key, value] : all_keys)
    {
        cout << "For key size " << key << " :\n";
        for( char c : value)
        {
            cout << c << " ";
        }
        cout << "\n";
    }

    for ( const auto& [key, value] : all_decstrings)
    {
        cout << " For key size " << key << " : \n" << value << "\n";
    }


    return 0;


}