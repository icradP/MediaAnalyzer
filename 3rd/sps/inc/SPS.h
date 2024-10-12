
#pragma once 
#include <iostream>
#include <sstream>
#include <string>
#include <vector>
#include <iomanip>
#include <cstring>
#include <map>
#include "SPSParser.h"
std::string charToHex(const char* input, size_t size) ;
std::vector<char> hexToChar(const std::string& hexInput) ;
bool inputSps(const char *sps, size_t sps_len,T_SPS& tH264SpsInfo);
struct SPSHelper
{   
    bool isSpsValid=false;
    T_SPS tSps;
    std::vector<char> bSps;
    std::map<std::string, std::pair<std::string,void*>> spsInfo;
    std::vector<char> getBin();
    std::string getHex();
    bool loadBin(const char *sps, size_t sps_len);
    bool loadHex(const std::string hexInput);
    //获取T_SPS 结构体的成员变量地址 并将值映射到map容器中
    void loadSPSInfo();
    void getWidthXHeight(int &width, int &height);
    void getFremeRateInt(int &frameRate);
    void getFremeRateFloat(float &frameRate);


};