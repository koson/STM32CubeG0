/**
  @page FDCAN_Com_polling_2_BOARDS FDCAN Communication polling example

  @verbatim
  ******************************************************************************
  * @file    FDCAN/FDCAN_Com_polling_2_BOARDS/readme.txt
  * @author  MCD Application Team
  * @brief   Description of the FDCAN_Com_polling_2_BOARDS example.
  ******************************************************************************
  * @attention
  *
  * Copyright (c) 2020 STMicroelectronics. All rights reserved.
  *
  * This software component is licensed by ST under BSD 3-Clause license,
  * the "License"; You may not use this file except in compliance with the
  * License. You may obtain a copy of the License at:
  *                        opensource.org/licenses/BSD-3-Clause
  *
  ******************************************************************************
  @endverbatim

@par Example Description

How to achieve Polling Process Communication between two FDCAN units.

The sent frames are used to control LEDs by pressing Tamper push-button.

The CAN serial communication link is a bus to which a number of units may be
connected. This number has no theoretical limit. Practically the total number
of units will be limited by delay times and/or electrical loads on the bus line.

At the beginning of the main program the HAL_Init() function is called to reset
all the peripherals, initialize the Flash interface and the systick.
The SystemClock_Config() function is used to configure the system clock (SYSCLK)
to run at 64 MHz.

Then, on each board:
  - FDCAN module is configured to operate in normal mode,
    with Nominal Bit Rate of 1 MBit/s and Data Bit Rate of 8 MBit/s.
  - FDCAN module is configured to receive messages with pre-defined ID to its Rx FIFO 0.
  - FDCAN module is configured with Tx delay compensation, required for Bit Rate
    Switching mode.
  - FDCAN module is started.
  - The main program is polling for message to be received in RX FIFO 0, using
    HAL_FDCAN_GetRxFifoFillLevel().

When Tamper push-button is pressed on any board:
  - its LED1 is turned OFF
  - its FDCAN module sends a message with Bit Rate Switching.

On the other board, after receiving the message:
 - received payload is compared to expected data
 - if the result is OK, LED1 is turned ON

If at any time of the process an error is encountered LED3 is turned ON.

@note Care must be taken when using HAL_Delay(), this function provides accurate delay (in milliseconds)
      based on variable incremented in SysTick ISR. This implies that if HAL_Delay() is called from
      a peripheral ISR process, then the SysTick interrupt must have higher priority (numerically lower)
      than the peripheral interrupt. Otherwise the caller ISR process will be blocked.
      To change the SysTick interrupt priority you have to use HAL_NVIC_SetPriority() function.

@note The application need to ensure that the SysTick time base is always set to 1 millisecond
      to have correct HAL operation.

@par Keywords

FDCAN, Polling, FD, BRS, TxDelay

@par Directory contents

  - FDCAN/FDCAN_Com_polling_2_BOARDS/Inc/stm32g0xx_hal_conf.h    HAL configuration file
  - FDCAN/FDCAN_Com_polling_2_BOARDS/Inc/stm32g0xx_it.h          Header for stm32g0xx_it.c
  - FDCAN/FDCAN_Com_polling_2_BOARDS/Inc/main.h                  Header for main.c module
  - FDCAN/FDCAN_Com_polling_2_BOARDS/Src/stm32g0xx_it.c          Interrupt handlers
  - FDCAN/FDCAN_Com_polling_2_BOARDS/Src/main.c                  Main program
  - FDCAN/FDCAN_Com_polling_2_BOARDS/Src/stm32g0xx_hal_msp.c     HAL MSP module
  - FDCAN/FDCAN_Com_polling_2_BOARDS/Src/system_stm32g0xx.c      stm32g0xx system source file

@par Hardware and Software environment

  - This example runs on STM32G0C1VETx devices.

  - This example has been tested with a couple of STM32G0C1E-EV board and can be
    easily tailored to any other supported device and development board.

  - STM32G0C1E-EV set-up:
    - Jumper JP9 => fitted to connect terminal resistor on CAN physical link (on each board).
    - Connect the 2 points CN12 CAN connector (CAN-H and CAN-L) of the first eval board,
      to the 2 points CN12 CAN connectors (resp. CAN-H and CAN-L) of the second eval board.
       _________________________                       _________________________ 
      |           ______________|                     |______________           |
      |          |FDCAN1        |                     |        FDCAN1|          |
      |          |              |                     |              |          |
      |          |       CAN    |1___________________1|    CAN       |          |
      |          |    connector |2___________________2| connector    |          |
      |          |      (CN12)  |                     |   (CN12)     |          |
      |          |______________|                     |______________|          |
      |                         |                     |                         |
      |   _    _    _    _      |                     |   _    _    _    _      |
      |  |_|  |_|  |_|  |_|     |                     |  |_|  |_|  |_|  |_|     |
      | LED1 LED2 LED3 LED4     |                     | LED1 LED2 LED3 LED4     |
      |          _              |                     |          _              |
      |         (_)             |                     |         (_)             |
      |         User            |                     |         User            |
      |                         |                     |                         |
      |      STM32 Board 1      |                     |      STM32 Board 2      |
      |                         |                     |                         |
      |_________________________|                     |_________________________|
      
@par How to use it ?

In order to make the program work, you must do the following :
  - Open your preferred toolchain
  - Rebuild all files and load your image into target memory
  - Run the example

 * <h3><center>&copy; COPYRIGHT STMicroelectronics</center></h3>
 */
