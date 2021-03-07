//---------------------------------------------------------------------------
//---------------------------------------------------------------------------
#ifndef _HK_ADCF_H
#define _HK_ADCF_H
//---------------------------------------------------------------------------
//---------------------------------------------------------------------------
#include <stdint.h>

#define ADCF_MAX_CHN 18
#define ADCF_SAMPLE_CONST 0x04   //0..7
//---------------------------------------------------------------------------
//---------------------------------------------------------------------------
//---------------------------------------------------------------------------
//---------------------------------------------------------------------------
//-----------------------------------------------------------------------------
//-----------------------------------------------------------------------------
//----------------------------------------------------------------------
#if defined(STM32F030) || defined(STM32F031) || \
    defined(STM32F051) || defined(STM32F072) || defined(STM32F042)
  #include "adcf_drv_f0xx.h"
#endif

#if defined(STM32F10X_LD) || defined(STM32F10X_LD_VL) || \
    defined(STM32F10X_MD) || defined(STM32F10X_MD_VL) || \
    defined(STM32F10X_HD) || defined(STM32F10X_HD_VL) || \
    defined(STM32F10X_XL) || defined (STM32F10X_CL)
  #include "adcf_drv_f10x.h"
#endif

#if defined(STM32F303xC)
  #include "adcf_drv_f303xc.h"
#endif
//-----------------------------------------------------------------------------
//-----------------------------------------------------------------------------
uint16_t* adcf_add(uint8_t* chls, uint8_t chn, uint8_t flt_deep, uint8_t flt_deci, fptr ev_handler);
//---------------------------------------------------------------------------
//---------------------------------------------------------------------------

extern uint8_t adc_trig;


#endif //_HK_ADCF_H