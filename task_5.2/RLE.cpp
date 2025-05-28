#include <iostream>
#include <string>

std::string RLECompress(const std::string str);
std::string RLEDecompress(const std::string& str);

//RLE сжатие
int main(void) {
    std::string str;
    std::cin >> str;
    std::string CompressStr = RLECompress(str);
    std::cout << "RLECompressStr = " << CompressStr << std::endl;
    std::string DecompressStr = RLEDecompress(CompressStr);
    std::cout << "RLEDecompressStr = " <<DecompressStr << std::endl;
    

}

std::string RLECompress(const std::string str) {
    if (str.size() == 0) return "";
    char symbol = str[0];
    int chain_len=1;
    int k=0;
    std::string out_str;
    for(int i=1; i<=str.size(); i++) {
        if(str[i] == symbol) {
            chain_len++;
        }
        else if(chain_len > 1) {
            out_str +=std::to_string(chain_len);
            out_str += symbol;
            symbol = str[i];
            chain_len=1;
        }
        else if(chain_len == 1) {
            out_str +=std::to_string(chain_len);
            out_str += symbol;
            symbol = str[i];
        }
    }
    return out_str;
}

std::string RLEDecompress(const std::string& str) { 
    std::string out_str = "";
    int chain_len=1;
    int i=0;
    std::string num_of_char = "";
    while(i<str.size()) {
        num_of_char = "";
        while(isdigit(str[i])){
            num_of_char+=str[i];
            i++;
        }
        chain_len = stoi(num_of_char);
        for(int k=0; k<chain_len; k++) {
            out_str+=str[i];
        }
        i++;
    }
    return out_str;
}


