/**
  @page SPI_FullDuplex_ComIT_Slave SPI Full Duplex IT example
  
  @verbatim
  ******************************************************************************
  * @file    SPI/SPI_FullDuplex_ComIT_Slave/readme.txt 
  * @author  MCD Application Team
  * @brief   Description of the SPI Full Duplex IT example.
  ******************************************************************************
  *
  * Copyright (c) 2019 STMicroelectronics. All rights reserved.
  *
  * This software component is licensed by ST under BSD 3-Clause license,
  * the "License"; You may not use this file except in compliance with the
  * License. You may obtain a copy of the License at:
  *                       opensource.org/licenses/BSD-3-Clause
  *
  ******************************************************************************
  @endverbatim

@par Example Description 

Data buffer transmission/reception between two boards via SPI using Interrupt mode.

Board: NUCLEO-G031K8 (embeds a STM32G031K8 device)
CLK Pin : PB3 (CN4, pin 15)
MISO Pin: PB4 (CN3, pin 15)
MOSI Pin: PB5 (CN3, pin 14)
   _________________________                       __________________________
  |           ______________|                      |______________           |
  |          |SPI1          |                      |          SPI1|          |
  |          |              |                      |              |          |
  |          |    CLK(PB.03)|______________________|CLK(PB.03)    |          |
  |          |              |                      |              |          |
  |          |   MISO(PB.04)|______________________|MISO(PB.04)   |          |
  |          |              |                      |              |          |
  |          |   MOSI(PB.05)|______________________|MOSI(PB.05)   |          |
  |          |              |                      |              |          |
  |          |______________|                      |______________|          |
  |      __                 |                      |                         |
  |     |__|                |                      |                         |
  |                      GND|______________________|GND                      |
  |                         |                      |                         |
  |_STM32G0xx Master________|                      |_STM32G0xx Slave_________|

HAL architecture allows user to easily change code to move to DMA or Polling 
mode. To see others communication modes please check following examples:
SPI\SPI_FullDuplex_ComPolling_Master and SPI\SPI_FullDuplex_ComPolling_Slave
SPI\SPI_FullDuplex_ComDMA_Master and SPI\SPI_FullDuplex_ComDMA_Slave

At the beginning of the main program the HAL_Init() function is called to reset 
all the peripherals, initialize the Flash interface and the systick.
Then the SystemClock_Config() function is used to configure the system
clock (SYSCLK) to run at 64 MHz.

The SPI peripheral configuration is ensured by the HAL_SPI_Init() function.
This later is calling the HAL_SPI_MspInit()function which core is implementing
the configuration of the needed SPI resources according to the used hardware (CLOCK, 
GPIO and NVIC). You may update this function to change SPI configuration.

The SPI communication is then initiated.
The HAL_SPI_TransmitReceive_IT() function allows the reception and the 
transmission of a predefined data buffer at the same time (Full Duplex Mode).
If the Master board is used, the project SPI_FullDuplex_ComIT_Master must be used.
If the Slave board is used, the project SPI_FullDuplex_ComIT_Slave must be used.

For this example the aTxBuffer is predefined and the aRxBuffer size is same as aTxBuffer.

In a first step after the user connects the PA.15 (Arduino D2) to GND, SPI Master starts the
communication by sending aTxBuffer and receiving aRxBuffer through 
HAL_SPI_TransmitReceive_IT(), at the same time SPI Slave transmits aTxBuffer 
and receives aRxBuffer through HAL_SPI_TransmitReceive_IT(). 
The callback functions (HAL_SPI_TxRxCpltCallback and HAL_SPI_ErrorCallbackand) update 
the variable wTransferState used in the main function to check the transfer status.
Finally, aRxBuffer and aTxBuffer are compared through Buffercmp() in order to 
check buffers correctness.  

STM32 board's LEDs can be used to monitor the transfer status:
 - LED3 toggles quickly on master board waiting PA.15 (Arduino D2) to be connected to GND
 - LED3 turns ON if transmission/reception is complete and OK.
 - LED3 toggles slowly when there is a timeout or an error in transmission/reception process.   

@note You need to perform a reset on Slave board, then perform it on Master board
      to have the correct behaviour of this example.

@note Care must be taken when using HAL_Delay(), this function provides accurate delay (in milliseconds)
      based on variable incremented in SysTick ISR. This implies that if HAL_Delay() is called from
      a peripheral ISR process, then the SysTick interrupt must have higher priority (numerically lower)
      than the peripheral interrupt. Otherwise the caller ISR process will be blocked.
      To change the SysTick interrupt priority you have to use HAL_NVIC_SetPriority() function.
      
@note The application need to ensure that the SysTick time base is always set to 1 millisecond
      to have correct HAL operation.

@par Keywords

Connectivity, SPI, Full-duplex, Interrupt, Transmission, Reception, Master, Slave, MISO, MOSI

@par Directory contents 

  - SPI/SPI_FullDuplex_ComIT_Slave/Inc/stm32g0xx_hal_conf.h    HAL configuration file
  - SPI/SPI_FullDuplex_ComIT_Slave/Inc/stm32g0xx_it.h          Interrupt handlers header file
  - SPI/SPI_FullDuplex_ComIT_Slave/Inc/main.h                  Header for main.c module  
  - SPI/SPI_FullDuplex_ComIT_Slave/Src/stm32g0xx_it.c          Interrupt handlers
  - SPI/SPI_FullDuplex_ComIT_Slave/Src/main.c                  Main program
  - SPI/SPI_FullDuplex_ComIT_Slave/Src/system_stm32g0xx.c      stm32g0xx system source file
  - SPI/SPI_FullDuplex_ComIT_Slave/Src/stm32g0xx_hal_msp.c     HAL MSP file

@par Hardware and Software environment

  - This example runs on STM32G031K8Tx devices.

  - This example has been tested with NUCLEO-G031K8 board and can be
    easily tailored to any other supported device and development board.

  - NUCLEO-G031K8 Set-up
    - Connect Master board PB3 (CN4, pin 15) to Slave Board PB3 (CN4, pin 15)
    - Connect Master board PB4 (CN3, pin 15) to Slave Board PB4 (CN3, pin 15)
    - Connect Master board PB5 (CN3, pin 14) to Slave Board PB5 (CN3, pin 14)
    - Connect Master board GND  to Slave Board GND

@par How to use it ? 

In order to make the program work, you must do the following:
 - Open your preferred toolchain
 - Rebuild all files (master project) and load your image into target memory
    o Load the project in Master Board
 - Rebuild all files (slave project) and load your image into target memory
    o Load the project in Slave Board
 - Run the example

 * <h3><center>&copy; COPYRIGHT STMicroelectronics</center></h3>
 */
 
