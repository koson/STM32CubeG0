/**
  @page CRYP_AESModes_Suspension  Suspend a low priority message CBC deciphering
      to carry out a high priority message CTR enciphering

  @verbatim
  ******************************************************************************
  * @file    CRYP/CRYP_AESModes_Suspension/readme.txt
  * @author  MCD Application Team
  * @brief   Description of the CRYP AES Algorithm suspension/resumption
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

How to use the CRYP peripheral to suspend then resume a ciphering processing.

In this example, a low priority message is deciphered in interrupt mode. Deciphering
algorithm is CBC, key is 256-bit long, data type is set to 16_bit (half-word) swapping.

The low-priority data processing is suspended to carry out the CTR-enciphering of
a high priority message with a 256-bit long key and no data swapping.

Once the high priority message processing is completed and the enciphered output
is checked against the expected results, the low priority message processing
is resumed.

Artificial scheme is used to trigger the suspension request after eleven blocks
of the low priority data have been processed.
User can use any other interruption to request the suspension.

When all enciphering and deciphering operations are successful, LED_GREEN is turned on.
In case of ciphering, initialization, suspension or resumption issue, LED_RED is turned on.

@par Keywords

Security, Cryptography, CRYPT, AES, CBC, CTR, USART


@par Directory contents

  - CRYP/CRYP_AESModes_Suspension/Inc/stm32g0xx_hal_conf.h    HAL configuration file
  - CRYP/CRYP_AESModes_Suspension/Inc/stm32g0xx_it.h          Interrupt handlers header file
  - CRYP/CRYP_AESModes_Suspension/Inc/main.h                  Header for main.c module
  - CRYP/CRYP_AESModes_Suspension/Src/stm32g0xx_it.c          Interrupt handlers
  - CRYP/CRYP_AESModes_Suspension/Src/main.c                  Main program
  - CRYP/CRYP_AESModes_Suspension/Src/stm32g0xx_hal_msp.c     HAL MSP module
  - CRYP/CRYP_AESModes_Suspension/Src/system_stm32g0xx.c      STM32G0xx system source file


@par Hardware and Software environment

  - This example runs on STM32G081RBTx devices.
  - This example has been tested with one STM32G081B-EVAL board embedding
    a STM32G081RBTx device and can be easily tailored to any other supported device
    and development board.

@par How to use it ?

In order to make the program work, you must do the following:
 - Open your preferred toolchain
 - Rebuild all files and load your image into target memory
 - Run the example

 * <h3><center>&copy; COPYRIGHT STMicroelectronics</center></h3>
 */
