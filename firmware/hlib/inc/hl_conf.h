/**
 * @file hl_conf.h
 * Configuring used hardware and firmware features 
 *
 * @author  Bui Van Hieu <bvhieu@cse.hcmut.edu.vn>
 * @version 1.0
 * @date 01-09-2013
 *
 * @copyright
 * This project and all its relevant hardware designs, documents, source codes, compiled libraries
 * belong to <b> Smart Sensing and Intelligent Controlling Group (SSAIC Group)</b>. 
 * You have to comply with <b> Non-Commercial Share-Alike Creative Common License </b> 
 * in order to share (copy, distribute, transmit) or remix (modify, reproduce, adapt) these works.\n
 * SSAIC Group shall not be held liable for any direct, indirect or consequential damages 
 * with respect to any claims arising from the content of hardware, firmware and/or the use 
 * made by customers of the coding information contained herein in connection with their products.\n
 * You are prohibited from commercializing in any kind that using or basing on these works
 * without written permission from SSAIC Group. Please contact ssaic@googlegroups.com for commercializing
 */ 

#ifndef __HL_CONF_H
#define __HL_CONF_H

/* SELECT YOUR PLATFORM BY UNCOMMENTING IT */
#define PLATFORM_STM32F100_STARTER
//#define PLATFORM_MBOARD_ONE

/* SELECET YOUR COMPILER BY UNCOMMENTING IT */
//#define GNU_COMPILER
#define KEIL_COMPILER
//#define IAR_COMPILER 

/* SELECT INITIAL CHECKING */
#define INITIAL_CHECK

/* SELECT PARAMETER CHECKING */
#define PARAM_CHECK_FULL
//#define PARAM_CHECK_CRITICAL
//#define PARAM_CHECK_NONE

#ifdef PLATFORM_STM32F100_STARTER
  #define STM32F100C8_MCU
#elif defined(PLATFORM_MBOARD_ONE)
  #define STM32F103RCT6_MCU
#endif

#endif /* __HL_CONF_H */
