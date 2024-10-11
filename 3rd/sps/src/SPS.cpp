#include "SPS.h"
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
    return loadBin(bSps.data(), bSps.size());
}

//获取T_SPS 结构体的成员变量地址 并将值映射到map容器中
void SPSHelper::loadSPSInfo()
{
    spsInfo["uiSpsId"] = &(tSps.uiSpsId);
    spsInfo["iProfileIdc"] = &(tSps.iProfileIdc);
    spsInfo["iLevelIdc"] = &(tSps.iLevelIdc);
    spsInfo["iChromaFormatIdc"] = &(tSps.iChromaFormatIdc);
    spsInfo["iTransformBypass"] = &(tSps.iTransformBypass);
    spsInfo["iLog2MaxFrameNum"] = &(tSps.iLog2MaxFrameNum);
    spsInfo["iPocType"] = &(tSps.iPocType);
    spsInfo["iLog2MaxPocLsb"] = &(tSps.iLog2MaxPocLsb);
    spsInfo["iDeltaPicOrderAlwaysZeroFlag"] = &(tSps.iDeltaPicOrderAlwaysZeroFlag);
    spsInfo["iOffsetForNonRefPic"] = &(tSps.iOffsetForNonRefPic);
    spsInfo["iOffsetForTopToBottomField"] = &(tSps.iOffsetForTopToBottomField);
    spsInfo["iPocCycleLength"] = &(tSps.iPocCycleLength);
    spsInfo["iRefFrameCount"] = &(tSps.iRefFrameCount);
    spsInfo["iGapsInFrameNumAllowedFlag"] = &(tSps.iGapsInFrameNumAllowedFlag);
    spsInfo["iMbWidth"] = &(tSps.iMbWidth);
    spsInfo["iMbHeight"] = &(tSps.iMbHeight);
    spsInfo["iFrameMbsOnlyFlag"] = &(tSps.iFrameMbsOnlyFlag);
    spsInfo["iMbAff"] = &(tSps.iMbAff);
    spsInfo["iDirect8x8InferenceFlag"] = &(tSps.iDirect8x8InferenceFlag);
    spsInfo["iCrop"] = &(tSps.iCrop);
    spsInfo["uiCropLeft"] = &(tSps.uiCropLeft);
    spsInfo["uiCropRight"] = &(tSps.uiCropRight);
    spsInfo["uiCropTop"] = &(tSps.uiCropTop);
    spsInfo["uiCropBottom"] = &(tSps.uiCropBottom);
    spsInfo["iVuiParametersPresentFlag"] = &(tSps.iVuiParametersPresentFlag);
    spsInfo["tSar"] = &(tSps.tSar);
    spsInfo["iVideoSignalTypePresentFlag"] = &(tSps.iVideoSignalTypePresentFlag);
    spsInfo["iFullRange"] = &(tSps.iFullRange);
    spsInfo["iColourDescriptionPresentFlag"] = &(tSps.iColourDescriptionPresentFlag);
    spsInfo["tColorPrimaries"] = &(tSps.tColorPrimaries);
    spsInfo["tColorTrc"] = &(tSps.tColorTrc);
    spsInfo["tColorspace"] = &(tSps.tColorspace);
    spsInfo["iTimingInfoPresentFlag"] = &(tSps.iTimingInfoPresentFlag);
    spsInfo["u32NumUnitsInTick"] = &(tSps.u32NumUnitsInTick);
    spsInfo["u32TimeScale"] = &(tSps.u32TimeScale);
    spsInfo["iFixedFrameRateFlag"] = &(tSps.iFixedFrameRateFlag);
    spsInfo["asOffsetForRefFrame"] = &(tSps.asOffsetForRefFrame);
    spsInfo["iBitstreamRestrictionFlag"] = &(tSps.iBitstreamRestrictionFlag);
    spsInfo["iNumReorderFrames"] = &(tSps.iNumReorderFrames);
    spsInfo["iScalingMatrixPresent"] = &(tSps.iScalingMatrixPresent);
    spsInfo["aau8ScalingMatrix4"] = &(tSps.aau8ScalingMatrix4);
    spsInfo["aau8ScalingMatrix8"] = &(tSps.aau8ScalingMatrix8);
    spsInfo["iNalHrdParametersPresentFlag"] = &(tSps.iNalHrdParametersPresentFlag);
    spsInfo["iVclHrdParametersPresentFlag"] = &(tSps.iVclHrdParametersPresentFlag);
    spsInfo["iPicStructPresentFlag"] = &(tSps.iPicStructPresentFlag);
    spsInfo["iTimeOffsetLength"] = &(tSps.iTimeOffsetLength);
    spsInfo["iCpbCnt"] = &(tSps.iCpbCnt);
    spsInfo["iInitialCpbRemovalDelayLength"] = &(tSps.iInitialCpbRemovalDelayLength);
    spsInfo["iCpbRemovalDelayLength"] = &(tSps.iCpbRemovalDelayLength);
    spsInfo["iDpbOutputDelayLength"] = &(tSps.iDpbOutputDelayLength);
    spsInfo["iBitDepthLuma"] = &(tSps.iBitDepthLuma);
    spsInfo["iBitDepthChroma"] = &(tSps.iBitDepthChroma);
    spsInfo["iResidualColorTransformFlag"] = &(tSps.iResidualColorTransformFlag);
    spsInfo["iConstraintSetFlags"] = &(tSps.iConstraintSetFlags);
    spsInfo["iNew"] = &(tSps.iNew);
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