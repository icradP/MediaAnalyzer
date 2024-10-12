#include "SPS.h"
#include <iostream>
#include <typeinfo>
#include <cxxabi.h>
#include <memory>

std::string demangle(const char* name) {
    int status = -1;
    std::unique_ptr<char, void(*)(void*)> res {
        abi::__cxa_demangle(name, nullptr, nullptr, &status),
        std::free
    };
    return (status == 0) ? res.get() : name;
}
using namespace std;
string charToHex(const char *input, size_t size)
{
    stringstream hexStream;
    hexStream << hex << std::setfill('0');
    for (size_t i = 0; i < size; ++i)
    {
        hexStream << std::setw(2) << static_cast<int>(static_cast<unsigned char>(input[i]));
    }
    return hexStream.str();
}

std::vector<char> hexToChar(const string &hexInput)
{
    auto adj_input = hexInput;
    if (adj_input.length() % 2 != 0)
    {
        adj_input += '0';
    }
    auto outputLength = adj_input.length() / 2;
    std::vector<char> output;
    output.resize(outputLength);
    for (size_t i = 0; i < adj_input.length(); i += 2)
    {
        string byteString = adj_input.substr(i, 2);
        char byte = static_cast<char>(strtoul(byteString.c_str(), nullptr, 16));
        output[i / 2] = byte;
    }
    return output;
}

bool inputSps(const char *sps, size_t sps_len, T_SPS &tH264SpsInfo)
{
    if (sps_len < 4)
    {
        return false;
    }
    T_GetBitContext tGetBitBuf;
    memset(&tGetBitBuf, 0, sizeof(tGetBitBuf));
    memset(&tH264SpsInfo, 0, sizeof(tH264SpsInfo));
    tGetBitBuf.pu8Buf = (uint8_t *)sps + 1;
    tGetBitBuf.iBufSize = (int)(sps_len - 1);
    if (0 != h264DecSeqParameterSet((void *)&tGetBitBuf, &tH264SpsInfo))
    {
        return false;
    }
    return true;
}

std::vector<char> SPSHelper::getBin()
{
    return bSps;
}
std::string SPSHelper::getHex()
{
    return charToHex(bSps.data(), bSps.size());
}
bool SPSHelper::loadBin(const char *sps, size_t sps_len)
{
    if (sps_len < 4)
    {
        return false;
    }
    T_GetBitContext tGetBitBuf;
    memset(&tGetBitBuf, 0, sizeof(tGetBitBuf));
    memset(&tSps, 0, sizeof(tSps));
    tGetBitBuf.pu8Buf = (uint8_t *)sps + 1;
    tGetBitBuf.iBufSize = (int)(sps_len - 1);
    if (0 != h264DecSeqParameterSet((void *)&tGetBitBuf, &tSps))
    {
        return false;
    }
    return true;
}
bool SPSHelper::loadHex(const string hexInput)
{
    bSps = hexToChar(hexInput);
    isSpsValid=loadBin(bSps.data(), bSps.size());
    return isSpsValid;
}


#define REGISTER_SPS_INFO(member) \
    spsInfo[#member]={demangle(typeid(tSps.member).name()),&(tSps.member)};
//获取T_SPS 结构体的成员变量地址 并将值映射到map容器中
void SPSHelper::loadSPSInfo()
{
    
    REGISTER_SPS_INFO(uiSpsId);
    REGISTER_SPS_INFO(iProfileIdc); 
    REGISTER_SPS_INFO(iLevelIdc); 
    REGISTER_SPS_INFO(iChromaFormatIdc); 
    REGISTER_SPS_INFO(iTransformBypass); 
    REGISTER_SPS_INFO(iLog2MaxFrameNum); 
    REGISTER_SPS_INFO(iPocType); 
    REGISTER_SPS_INFO(iLog2MaxPocLsb); 
    REGISTER_SPS_INFO(iDeltaPicOrderAlwaysZeroFlag); 
    REGISTER_SPS_INFO(iOffsetForNonRefPic); 
    REGISTER_SPS_INFO(iOffsetForTopToBottomField); 
    REGISTER_SPS_INFO(iPocCycleLength); 
    REGISTER_SPS_INFO(iRefFrameCount); 
    REGISTER_SPS_INFO(iGapsInFrameNumAllowedFlag); 
    REGISTER_SPS_INFO(iMbWidth); 
    REGISTER_SPS_INFO(iMbHeight); 
    REGISTER_SPS_INFO(iFrameMbsOnlyFlag); 
    REGISTER_SPS_INFO(iMbAff); 
    REGISTER_SPS_INFO(iDirect8x8InferenceFlag); 
    REGISTER_SPS_INFO(iCrop); 
    REGISTER_SPS_INFO(uiCropLeft); 
    REGISTER_SPS_INFO(uiCropRight); 
    REGISTER_SPS_INFO(uiCropTop); 
    REGISTER_SPS_INFO(uiCropBottom); 
    REGISTER_SPS_INFO(iVuiParametersPresentFlag); 
    REGISTER_SPS_INFO(tSar); 
    REGISTER_SPS_INFO(iVideoSignalTypePresentFlag); 
    REGISTER_SPS_INFO(iFullRange); 
    REGISTER_SPS_INFO(iColourDescriptionPresentFlag); 
    REGISTER_SPS_INFO(tColorPrimaries); 
    REGISTER_SPS_INFO(tColorTrc); 
    REGISTER_SPS_INFO(tColorspace); 
    REGISTER_SPS_INFO(iTimingInfoPresentFlag); 
    REGISTER_SPS_INFO(u32NumUnitsInTick); 
    REGISTER_SPS_INFO(u32TimeScale); 
    REGISTER_SPS_INFO(iFixedFrameRateFlag); 
    REGISTER_SPS_INFO(iBitstreamRestrictionFlag); 
    REGISTER_SPS_INFO(iNumReorderFrames); 
    REGISTER_SPS_INFO(iScalingMatrixPresent); 
    REGISTER_SPS_INFO(aau8ScalingMatrix4); 
    REGISTER_SPS_INFO(aau8ScalingMatrix8); 
    REGISTER_SPS_INFO(iNalHrdParametersPresentFlag); 
    REGISTER_SPS_INFO(iVclHrdParametersPresentFlag); 
    REGISTER_SPS_INFO(iPicStructPresentFlag); 
    REGISTER_SPS_INFO(iTimeOffsetLength); 
    REGISTER_SPS_INFO(iCpbCnt); 
    REGISTER_SPS_INFO(iInitialCpbRemovalDelayLength); 
    REGISTER_SPS_INFO(iCpbRemovalDelayLength); 
    REGISTER_SPS_INFO(iDpbOutputDelayLength); 
    REGISTER_SPS_INFO(iBitDepthLuma); 
    REGISTER_SPS_INFO(iBitDepthChroma); 
    REGISTER_SPS_INFO(iResidualColorTransformFlag); 
    REGISTER_SPS_INFO(iConstraintSetFlags); 
    REGISTER_SPS_INFO(iNew); 
}

void SPSHelper::getWidthXHeight(int &width, int &height)
{
    int iCodeWidth = 0;
    int iCodedHeight = 0;
    iCodeWidth	= 16 * tSps.iMbWidth;
    iCodedHeight = 16 * tSps.iMbHeight;
    width		 = iCodeWidth  - (tSps.uiCropRight + tSps.uiCropLeft);
    height		 = iCodedHeight - (tSps.uiCropTop	+ tSps.uiCropBottom);
     if (width <= 0 || height <= 0) {
         width  = iCodeWidth;
         height = iCodedHeight;
     }
}

void SPSHelper::getFremeRateFloat(float &frameRate)
{
    int iFrInt = 0;
    if(tSps.iTimingInfoPresentFlag)
    {
        if(!tSps.iFixedFrameRateFlag)
        {
            frameRate = (float)tSps.u32TimeScale / (float)tSps.u32NumUnitsInTick;
            //iFrInt = tSps.vui_parameters.u32TimeScale / tSps.vui_parameters.u32NumUnitsInTick;
        }else
        {
            frameRate = (float)tSps.u32TimeScale / (float)tSps.u32NumUnitsInTick / 2.0;
            //iFrInt = tSps.vui_parameters.u32TimeScale / tSps.vui_parameters.u32NumUnitsInTick / 2;
        }
        iFrInt = tSps.u32TimeScale / tSps.u32NumUnitsInTick / 2;
    }
}
void SPSHelper::getFremeRateInt(int &frameRate)
{
    int iFrInt = 0;
    float fFramerate= 0;
    if(tSps.iTimingInfoPresentFlag)
    {
        if(!tSps.iFixedFrameRateFlag)
        {
            fFramerate = (float)tSps.u32TimeScale / (float)tSps.u32NumUnitsInTick;
            //iFrInt = tSps.vui_parameters.u32TimeScale / tSps.vui_parameters.u32NumUnitsInTick;
        }else
        {
            fFramerate = (float)tSps.u32TimeScale / (float)tSps.u32NumUnitsInTick / 2.0;
            //iFrInt = tSps.vui_parameters.u32TimeScale / tSps.vui_parameters.u32NumUnitsInTick / 2;
        }
        iFrInt = tSps.u32TimeScale / tSps.u32NumUnitsInTick / 2;
    }
    frameRate = iFrInt;
}