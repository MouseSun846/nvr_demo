#include "CapPicture.h"
#include <stdio.h>
#include <string.h>
#include <iostream>
#include <ctime>
using namespace std;

/*******************************************************************
      Function:   Demo_Capture
   Description:   Capture picture.
     Parameter:   (IN)   none 
        Return:   0--success��-1--fail.   
**********************************************************************/

void logInfo(NET_DVR_IPPARACFG_V40* ipParaCfg) {

    if(ipParaCfg == nullptr) {
        return;
    }
    // 假设已经给 ipParaCfg 的字段赋值
    
    // 打印结构体字段的值
    cout << "dwSize: " << ipParaCfg->dwSize << endl;
    cout << "dwGroupNum: " << ipParaCfg->dwGroupNum << endl;
    cout << "dwAChanNum: " << ipParaCfg->dwAChanNum << endl;
    cout << "dwDChanNum: " << ipParaCfg->dwDChanNum << endl;
    cout << "dwStartDChan: " << ipParaCfg->dwStartDChan << endl;
    
    cout << "byAnalogChanEnable: ";
    for (int i = 0; i < MAX_CHANNUM_V30; ++i)
    {
        cout << static_cast<int>(ipParaCfg->byAnalogChanEnable[i]) << " ";
    }
    cout << endl << endl;
    
    cout << "struIPDevInfo: " << endl;
    for (int i = 0; i < MAX_IP_DEVICE_V40; ++i)
    {
        int enable = static_cast<int>(ipParaCfg->struIPDevInfo[i].byEnable);
        if(enable == 1) {
            cout << "IP Device " << i << ":" << endl;
            // 打印结构体字段的值
            cout << "byEnable: " << static_cast<int>(ipParaCfg->struIPDevInfo[i].byEnable) << endl;
            cout << "byProType: " << static_cast<int>(ipParaCfg->struIPDevInfo[i].byProType) << endl;
            cout << "byEnableQuickAdd: " << static_cast<int>(ipParaCfg->struIPDevInfo[i].byEnableQuickAdd) << endl;
            cout << "byCameraType: " << static_cast<int>(ipParaCfg->struIPDevInfo[i].byCameraType) << endl;
            cout << "sUserName: " << ipParaCfg->struIPDevInfo[i].sUserName << endl;
            cout << "sPassword: " << ipParaCfg->struIPDevInfo[i].sPassword << endl;
            cout << "byDomain: " << ipParaCfg->struIPDevInfo[i].byDomain << endl;
            // 打印 IP 地址
            cout << "struIP: " <<ipParaCfg->struIPDevInfo[i].struIP.sIpV4<< endl;
            cout << "wDVRPort: " << ipParaCfg->struIPDevInfo[i].wDVRPort << endl;
            cout << "szDeviceID: " << ipParaCfg->struIPDevInfo[i].szDeviceID << endl;
            cout << "byEnableTiming: " << static_cast<int>(ipParaCfg->struIPDevInfo[i].byEnableTiming) << endl;
            cout << "byCertificateValidation: " << static_cast<int>(ipParaCfg->struIPDevInfo[i].byCertificateValidation) << endl << endl;            
        }
    }
   
}

int Demo_Capture()
{
    NET_DVR_Init();
    long lUserID;
    //login
    NET_DVR_USER_LOGIN_INFO struLoginInfo = {0};
    NET_DVR_DEVICEINFO_V40 struDeviceInfoV40 = {0};
    struLoginInfo.bUseAsynLogin = false;

    struLoginInfo.wPort = 8000;
    memcpy(struLoginInfo.sDeviceAddress, "192.168.6.64", NET_DVR_DEV_ADDRESS_MAX_LEN);
    memcpy(struLoginInfo.sUserName, "admin", NAME_LEN);
    memcpy(struLoginInfo.sPassword, "leinao123", NAME_LEN);

    lUserID = NET_DVR_Login_V40(&struLoginInfo, &struDeviceInfoV40);

    if (lUserID < 0)
    {
        std::cerr<<"Login error, "<<NET_DVR_GetLastError()<<std::endl;
        return HPR_ERROR;
    }

    // 获取通道个数
    int channelNum =  struDeviceInfoV40.struDeviceV30.byIPChanNum + struDeviceInfoV40.struDeviceV30.byHighDChanNum * 256;
    //获取IP通道参数信息
    NET_DVR_IPPARACFG_V40 IPAccessCfgV40{};
    memset(&IPAccessCfgV40, 0, sizeof(NET_DVR_IPPARACFG));
    DWORD dwReturned = 0;
    if (!NET_DVR_GetDVRConfig(lUserID, NET_DVR_GET_IPPARACFG_V40, 0, &IPAccessCfgV40, sizeof(NET_DVR_IPPARACFG_V40), &dwReturned))
    {
        std::cerr<<"NET_DVR_GET_IPPARACFG_V40 error, "<<NET_DVR_GetLastError()<<std::endl;
        NET_DVR_Logout(lUserID);
        NET_DVR_Cleanup();
        return 0;
    }
    logInfo(&IPAccessCfgV40);

    for (int i = 0; i < MAX_IP_DEVICE_V40; ++i)
    {
        int enable = static_cast<int>(IPAccessCfgV40.struIPDevInfo[i].byEnable);
        if(enable == 1) {
            NET_DVR_JPEGPARA strPicPara = {0};
            strPicPara.wPicQuality = 0;
            strPicPara.wPicSize = 255;
            std::string name = std::to_string(time(0));
            name += "_";
            name += std::to_string(i);
            name += ".jpeg";        
            int iRet;
            iRet = NET_DVR_CaptureJPEGPicture(lUserID, struDeviceInfoV40.struDeviceV30.byStartDChan+i, &strPicPara, (char*) name.c_str());
            if (!iRet)
            {
                std::cerr<<"pyd1---NET_DVR_CaptureJPEGPicture error, "<<NET_DVR_GetLastError()<<std::endl;
            }       
        } 
    }

    // logout
    NET_DVR_Logout_V30(lUserID);
    NET_DVR_Cleanup();

    return HPR_OK;

}