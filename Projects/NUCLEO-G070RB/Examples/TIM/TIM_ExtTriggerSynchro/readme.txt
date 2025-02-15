/**
  @page TIM_ExtTriggerSynchro TIM External Trigger Synchro example
  
  @verbatim
  ******************************************************************************
  * @file    TIM/TIM_ExtTriggerSynchro/readme.txt 
  * @author  MCD Application Team
  * @brief   Description of the TIM External Trigger Synchro example.
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

 This example shows how to synchronize TIM peripherals in cascade mode with an external trigger.
 In this example three timers are used:

  1/TIM1 is configured as Master Timer:
      - Toggle Mode is used
      - The TIM1 Enable event is used as Trigger Output 

  2/TIM1 is configured as Slave Timer for an external Trigger connected to TIM1 
    TI2 pin (TIM1 CH2 configured as input pin):
      - The TIM1 TI2FP2 is used as Trigger Input
      - Rising edge is used to start and stop the TIM1: Gated Mode.

  3/TIM3 is slave for TIM1 and Master for TIM15,
      - Toggle Mode is used
      - The ITR1 (TIM1) is used as input trigger 
      - Gated mode is used, so start and stop of slave counter
        are controlled by the Master trigger output signal(TIM1 enable event).
      - The TIM3 enable event is used as Trigger Output. 

  4/TIM15 is slave for TIM3,
      - Toggle Mode is used
      - The ITR2 (TIM3) is used as input trigger
      - Gated mode is used, so start and stop of slave counter
        are controlled by the Master trigger output signal(TIM3 enable event).

   The TIM1CLK is set to SystemCoreClock, 
   TIM3CLK is set to SystemCoreClock and 
   TIM15CLK frequency is set to SystemCoreClock,
   To get TIMx counter clock at 8 MHz the Prescaler is computed as following: 
   - Prescaler = (TIMx CLK / TIMx counter clock) - 1

   SystemCoreClock is set to 56 MHz.

   TIMx frequency = TIMx  counter clock/ 2*(TIMx_Period + 1) = 100 KHz.
   
  The starts and stops of the TIM1 counters are controlled by the external trigger.
  The TIM3 starts and stops are controlled by the TIM1, and the TIM15 starts and 
  stops are controlled by the TIM3.

@note Care must be taken when using HAL_Delay(), this function provides accurate
      delay (in milliseconds) based on variable incremented in SysTick ISR. This
      implies that if HAL_Delay() is called from a peripheral ISR process, then 
      the SysTick interrupt must have higher priority (numerically lower)
      than the peripheral interrupt. Otherwise the caller ISR process will be blocked.
      To change the SysTick interrupt priority you have to use HAL_NVIC_SetPriority() function.
      
@note This example needs to ensure that the SysTick time base is always set to 1 millisecond
      to have correct HAL operation.

@par Keywords

Timer, PWM, External Trigger, Synchronization, Cascade mode, Master, Slave, Duty Cycle, Waveform,
Oscilloscope, Output, Signal,

@par Directory contents

  - TIM/TIM_ExtTriggerSynchro/Inc/stm32g0xx_hal_conf.h    HAL configuration file
  - TIM/TIM_ExtTriggerSynchro/Inc/stm32g0xx_it.h          Interrupt handlers header file
  - TIM/TIM_ExtTriggerSynchro/Inc/main.h                  Header for main.c module  
  - TIM/TIM_ExtTriggerSynchro/Src/stm32g0xx_it.c          Interrupt handlers
  - TIM/TIM_ExtTriggerSynchro/Src/main.c                  Main program
  - TIM/TIM_ExtTriggerSynchro/Src/stm32g0xx_hal_msp.c     HAL MSP file
  - TIM/TIM_ExtTriggerSynchro/Src/system_stm32g0xx.c      STM32G0xx system source file

@par Hardware and Software environment

  - This example runs on STM32G070RBTx devices.
    
  - This example has been tested with NUCLEO-G070RB
    board and can be easily tailored to any other supported device 
    and development board.

  - NUCLEO-G070RB Set-up
    - Connect an external trigger to the TIM1 CH2 PA.09 (pin 21 in CN10 connector).
    - Connect the following pins to an oscilloscope to monitor the different waveforms:
      - TIM1 CH1 PA.08 (pin 23 in CN10 connector)
      - TIM3 CH1 PA.06 (pin 13 in CN10 connector)
      - TIM15 CH1 PB.14 (pin 25 in CN10 connector)
	  
@par How to use it ? 

In order to make the program work, you must do the following :
 - Open your preferred toolchain 
 - Rebuild all files and load your image into target memory
 - Run the example

 * <h3><center>&copy; COPYRIGHT STMicroelectronics</center></h3>
 */
