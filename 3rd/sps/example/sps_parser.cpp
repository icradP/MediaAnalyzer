
#include <iomanip>
#include <sstream> 
#include <string>
#include <vector>
#include <iostream>
#include <cstring>
#include "SPSParser.h"



using namespace std; 

inline string charToHex(const char* input, size_t size) {
    stringstream hexStream;
    hexStream << hex << std::setfill('0');
    for (size_t i = 0; i < size; ++i) {
        hexStream << std::setw(2) << static_cast<int>(static_cast<unsigned char>(input[i]));
    }
    return hexStream.str();
}

inline std::vector<char> hexToChar(const string& hexInput, size_t& outputLength) {
    auto adj_input =hexInput;
    if (adj_input.length() % 2 != 0) {
        adj_input+= '0';
    }
    outputLength = adj_input.length() / 2;
    std::vector<char> output;
    output.resize(outputLength);
    for (size_t i = 0; i < adj_input.length(); i += 2) {
        string byteString = adj_input.substr(i, 2);
        char byte = static_cast<char>(strtoul(byteString.c_str(), nullptr, 16));
        output[i / 2] = byte;
    }
    return output;
}

static bool inputSps(const char *sps, size_t sps_len,T_SPS& tH264SpsInfo){
    if (sps_len < 4) {
        return false;
    }
    T_GetBitContext tGetBitBuf;
    memset(&tGetBitBuf,0,sizeof(tGetBitBuf));
    memset(&tH264SpsInfo,0,sizeof(tH264SpsInfo));
    tGetBitBuf.pu8Buf = (uint8_t*)sps + 1;
    tGetBitBuf.iBufSize = (int)(sps_len - 1);
    if(0 != h264DecSeqParameterSet((void *) &tGetBitBuf, &tH264SpsInfo)){
        return false;
    }
    return true;
}




int main(){

    std::string hexsps {"6742C029E901405EF2C02C2211A8"};
    size_t size = 0;
    auto binsps = hexToChar(hexsps,size);
    T_SPS tH264SpsInfo;
    inputSps(binsps.data(),binsps.size(),tH264SpsInfo);
    cout<<"SPS DUMP:"<<charToHex(binsps.data(),binsps.size())<<endl;
    cout<<"iVuiParametersPresentFlag: "<<tH264SpsInfo.iVuiParametersPresentFlag<<endl;;
    cout<<"iTimingInfoPresentFlag: "<<tH264SpsInfo.iTimingInfoPresentFlag<<endl;;
    cout<<"u32TimeScale: "<<tH264SpsInfo.u32TimeScale<<endl;;
    cout<<"u32NumUnitsInTick: "<<tH264SpsInfo.u32NumUnitsInTick<<endl;;
    
}
