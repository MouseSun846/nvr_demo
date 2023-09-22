#include "public.h"
#include "CapPicture.h"
#include <stdio.h>
#include <string.h>
#include <iostream>
/*******************************************************************
      Function:   Demo_Capture
   Description:   Capture picture.
     Parameter:   (IN)   none 
        Return:   0--success��-1--fail.   
**********************************************************************/

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
        printf("pyd1---Login error, %d\n", NET_DVR_GetLastError());
        return HPR_ERROR;
    }

    NET_DVR_JPEGPARA strPicPara = {0};
    strPicPara.wPicQuality = 2;
    strPicPara.wPicSize = 9;
    for(int i =0;i<6;i++) {
        std::string name="./ssss_"+std::to_string(i+1);
        name+=".jpeg";
        int iRet;
        iRet = NET_DVR_CaptureJPEGPicture(lUserID, i+1, &strPicPara, (char *)name.c_str());
        if (!iRet)
        {
            std::cout<<"pyd1---NET_DVR_CaptureJPEGPicture error, "<< NET_DVR_GetLastError()<<std::endl;
            return HPR_ERROR;
        }
    }


    //logout
    NET_DVR_Logout_V30(lUserID);
    NET_DVR_Cleanup();

    return HPR_OK;

}