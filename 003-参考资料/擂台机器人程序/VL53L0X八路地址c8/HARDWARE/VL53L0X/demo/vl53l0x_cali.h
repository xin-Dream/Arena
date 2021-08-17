#ifndef __VL53L0X_CAIL_H
#define __VL53L0X_CAIL_H

#include "vl53l0x.h"

//////////////////////////////////////////////////////////////////////////////////
//������ֻ��ѧϰʹ�ã�δ��������ɣ��������������κ���;
//ALIENTEK ս��V3 STM32������
//VL53L0X-У׼ģʽ ��������
//����ԭ��@ALIENTEK
//������̳:www.openedv.com
//��������:2017/7/1
//�汾��V1.0
//��Ȩ���У�����ؾ���
//Copyright(C) ������������ӿƼ����޹�˾ 2009-2019
//All rights reserved
//////////////////////////////////////////////////////////////////////////////////

//vl53l0x������У׼��Ϣ�ṹ�嶨��
typedef __packed struct
{
    uint8_t  adjustok;                    //У׼�ɹ���־��0XAA����У׼;������δУ׼
    uint8_t  isApertureSpads;             //ApertureSpadsֵ
    uint8_t  VhvSettings;                 //VhvSettingsֵ
    uint8_t  PhaseCal;                    //PhaseCalֵ
    uint32_t XTalkCalDistance;            //XTalkCalDistanceֵ
    uint32_t XTalkCompensationRateMegaCps;//XTalkCompensationRateMegaCpsֵ
    uint32_t CalDistanceMilliMeter;       //CalDistanceMilliMeterֵ
    int32_t  OffsetMicroMeter;            //OffsetMicroMeterֵ
    uint32_t refSpadCount;                //refSpadCountֵ

} _vl53l0x_adjust;

extern _vl53l0x_adjust Vl53l0x_data;

typedef __packed struct
{
    uint8_t  adjustok;                    //У׼�ɹ���־��0XAA����У׼;������δУ׼
    uint8_t  isApertureSpads;             //ApertureSpadsֵ
    uint8_t  VhvSettings;                 //VhvSettingsֵ
    uint8_t  PhaseCal;                    //PhaseCalֵ
    uint32_t XTalkCalDistance;            //XTalkCalDistanceֵ
    uint32_t XTalkCompensationRateMegaCps;//XTalkCompensationRateMegaCpsֵ
    uint32_t CalDistanceMilliMeter;       //CalDistanceMilliMeterֵ
    int32_t  OffsetMicroMeter;            //OffsetMicroMeterֵ
    uint32_t refSpadCount;                //refSpadCountֵ

} _vl53l0x_adjust1;

extern _vl53l0x_adjust1 Vl53l0x_data1;

typedef __packed struct
{
    uint8_t  adjustok;                    //У׼�ɹ���־��0XAA����У׼;������δУ׼
    uint8_t  isApertureSpads;             //ApertureSpadsֵ
    uint8_t  VhvSettings;                 //VhvSettingsֵ
    uint8_t  PhaseCal;                    //PhaseCalֵ
    uint32_t XTalkCalDistance;            //XTalkCalDistanceֵ
    uint32_t XTalkCompensationRateMegaCps;//XTalkCompensationRateMegaCpsֵ
    uint32_t CalDistanceMilliMeter;       //CalDistanceMilliMeterֵ
    int32_t  OffsetMicroMeter;            //OffsetMicroMeterֵ
    uint32_t refSpadCount;                //refSpadCountֵ

} _vl53l0x_adjust2;

extern _vl53l0x_adjust2 Vl53l0x_data2;

typedef __packed struct
{
    uint8_t  adjustok;                    //У׼�ɹ���־��0XAA����У׼;������δУ׼
    uint8_t  isApertureSpads;             //ApertureSpadsֵ
    uint8_t  VhvSettings;                 //VhvSettingsֵ
    uint8_t  PhaseCal;                    //PhaseCalֵ
    uint32_t XTalkCalDistance;            //XTalkCalDistanceֵ
    uint32_t XTalkCompensationRateMegaCps;//XTalkCompensationRateMegaCpsֵ
    uint32_t CalDistanceMilliMeter;       //CalDistanceMilliMeterֵ
    int32_t  OffsetMicroMeter;            //OffsetMicroMeterֵ
    uint32_t refSpadCount;                //refSpadCountֵ

} _vl53l0x_adjust3;

extern _vl53l0x_adjust3 Vl53l0x_data3;

typedef __packed struct
{
    uint8_t  adjustok;                    //У׼�ɹ���־��0XAA����У׼;������δУ׼
    uint8_t  isApertureSpads;             //ApertureSpadsֵ
    uint8_t  VhvSettings;                 //VhvSettingsֵ
    uint8_t  PhaseCal;                    //PhaseCalֵ
    uint32_t XTalkCalDistance;            //XTalkCalDistanceֵ
    uint32_t XTalkCompensationRateMegaCps;//XTalkCompensationRateMegaCpsֵ
    uint32_t CalDistanceMilliMeter;       //CalDistanceMilliMeterֵ
    int32_t  OffsetMicroMeter;            //OffsetMicroMeterֵ
    uint32_t refSpadCount;                //refSpadCountֵ

} _vl53l0x_adjust4;

extern _vl53l0x_adjust4 Vl53l0x_data4;

typedef __packed struct
{
    uint8_t  adjustok;                    //У׼�ɹ���־��0XAA����У׼;������δУ׼
    uint8_t  isApertureSpads;             //ApertureSpadsֵ
    uint8_t  VhvSettings;                 //VhvSettingsֵ
    uint8_t  PhaseCal;                    //PhaseCalֵ
    uint32_t XTalkCalDistance;            //XTalkCalDistanceֵ
    uint32_t XTalkCompensationRateMegaCps;//XTalkCompensationRateMegaCpsֵ
    uint32_t CalDistanceMilliMeter;       //CalDistanceMilliMeterֵ
    int32_t  OffsetMicroMeter;            //OffsetMicroMeterֵ
    uint32_t refSpadCount;                //refSpadCountֵ

} _vl53l0x_adjust5;

extern _vl53l0x_adjust5 Vl53l0x_data5;


void vl53l0x_calibration_test(VL53L0X_Dev_t *dev);

#endif
