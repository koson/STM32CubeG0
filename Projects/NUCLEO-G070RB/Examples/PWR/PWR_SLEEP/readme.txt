/**
  @page PWR_SLEEP Power sleep Mode Example
  
  @verbatim
  ******************************************************************************
  * @file    PWR/PWR_SLEEP/readme.txt 
  * @author  MCD Application Team
  * @brief   Description of the Power Sleep Mode example.
  ******************************************************************************
  *
  * Copyright (c) 2018 STMicroelectronics. All rights reserved.
  *
  * This software component is licensed by ST under BSD 3-Clause license,
  * the "License"; You may not use this file except in compliance with the
  * License. You may obtain a copy of the License at:
  *                       opensource.org/licenses/BSD-3-Clause
  *
  ******************************************************************************
  @endverbatim

@par Example Description 

How to enter the Sleep mode and wake up from this mode by using an interrupt.

In the associated software, the system clock is set to 56 MHz.
an EXTI line is connected to the user button through PC.13 and configured 
to generate an interrupt on falling edge upon key press.
The SysTick is programmed to generate an interrupt each 1 ms and in the SysTick 
interrupt handler, LED4 is toggled in order to indicate whether the MCU is in SLEEP mode 
or RUN mode.

5 seconds after start-up, the system automatically enters SLEEP mode and 
LED4 stops toggling.
The User push-button can be pressed at any time to wake-up the system. 
The software then comes back in RUN mode for 5 sec. before automatically entering SLEEP mode again. 

LED4 is used to monitor the system state as follows:
 - LED4 toggling: system in RUN mode
 - LED4 off : system in SLEEP mode

These steps are repeated in an infinite loop.

@note To measure the current consumption in SLEEP mode, remove JP3 jumper 
      and connect an amperemeter to JP3 to measure IDD current.     

@note This example can not be used in DEBUG mode due to the fact 
      that the Cortex-M0+ core is no longer clocked during low power mode 
      so debugging features are disabled.

@note Care must be taken when using HAL_Delay(), this function provides accurate delay (in milliseconds)
      based on variable incremented in SysTick ISR. This implies that if HAL_Delay() is called from
      a peripheral ISR process, then the SysTick interrupt must have higher priority (numerically lower)
      than the peripheral interrupt. Otherwise the caller ISR process will be blocked.
      To change the SysTick interrupt priority you have to use HAL_NVIC_SetPriority() function.
      
@note The application needs to ensure that the SysTick time base is always set to 1 millisecond
      to have correct HAL operation.

@par Keywords

Power, PWR, EXTI, Sleep mode, Interrupt, Wakeup, External reset

@par Directory contents 

  - PWR/PWR_SLEEP/Inc/stm32g0xx_conf.h         HAL Configuration file
  - PWR/PWR_SLEEP/Inc/stm32g0xx_it.h           Header for stm32g0xx_it.c
  - PWR/PWR_SLEEP/Inc/main.h                         Header file for main.c
  - PWR/PWR_SLEEP/Src/system_stm32g0xx.c       STM32G0xx system clock configuration file
  - PWR/PWR_SLEEP/Src/stm32g0xx_it.c           Interrupt handlers
  - PWR/PWR_SLEEP/Src/stm32g0xx_hal_msp.c      HAL MSP module
  - PWR/PWR_SLEEP/Src/main.c                         Main program

@par Hardware and Software environment

  - This example runs on STM32G0xx devices

  - This example has been tested with NUCLEO-G070RB
    board and can be easily tailored to any other supported device 
    and development board.

  - NUCLEO-G070RB set-up:
    - LED4 connected to PA.05 pin
    - Use the User push-button connected to pin PC.13 (EXTI_Line4_15)

@par How to use it ? 

In order to make the program work, you must do the following :
 - Open your preferred toolchain 
 - Rebuild all files and load your image into target memory
 - Run the example

 * <h3><center>&copy; COPYRIGHT STMicroelectronics</center></h3>
 */
