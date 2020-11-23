#ifndef _DATAFILE_H_
#define _DATAFILE_H_

#include <stdio.h>
#include <stdint.h>

#include <string.h>
#include <fcntl.h>
#include <errno.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/mman.h>

#include "./include/Rte_Type.h"

#include <iostream>

#define MAXSIZE 1024000
// 一帧数据大小 数据头+ 数据+ 数据尾 9768 +4 +4
//#define DATASIZE 9776 108 + 4
#define DATASIZE 205344

struct myData {
	char a;
    int b;
	float c;
};

struct Dt_test {
    uint8_t  Dt_ARRAY_7500[7500];
	Dt_RECORD_SVParkingSlot RecordParkingSlot;
	Dt_RECORD_SVFreeSpace   RecordFreeSpace;
};

typedef struct _SingalTFLinfo
{
		float      S_fTFL_Existence_Probability;
	 	int8_t     S_nTFL_Object_ID;
		int8_t     S_nTFL_LightBox_ID;
		int8_t     S_nTFL_Source;
		int8_t     S_nTFL_Mode;
		int8_t     S_nTFL_Color;
		int8_t     S_nTFL_Shape;
		float      S_fTFL_Long_Distance;
		float      S_fTFL_Lat_Distance;
		float      S_fTFL_Rel_Height;
		float      S_fReserved[4];
		int8_t     S_nReserved[4];
}SingalTFLinfo;

typedef struct  _FrameTFLInfo
{
		int64_t    S_nTimeStamp;
		uint8_t    S_nFrameID;
		int16_t    S_nCounter;
		int64_t    S_nImageTimeStamp;
		int8_t     S_bLight;
		float      S_fDist2Light;
		int64_t    S_nt;
		int64_t    S_ndt;
		int8_t     S_nStraightLightState;
		int16_t    S_nStraightTimeLeft;
		int8_t     S_nLeftLightState;
		int16_t    S_nLeftTimeLeft;
		int8_t     S_nRightLightState;
		int16_t    S_nRightTimeLeft;
		int8_t     S_nUTurnLightState;
		int16_t    S_nUTurnTimeLeft;
		SingalTFLinfo sTI[10];
		float      S_fReserved[4];
		int8_t     S_nReserved[4];
		uint8_t    S_picdata[640*320];       //压缩图像
}FrameTFLInfo;

int ReadFileToData( uint8_t *data, int off_size);

int RteFileoff( uint8_t *data_head, int off_size);

unsigned int FileLen();

#endif