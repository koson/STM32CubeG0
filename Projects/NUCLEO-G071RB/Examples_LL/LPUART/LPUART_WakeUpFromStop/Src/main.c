/**
  ******************************************************************************
  * @file    Examples_LL/LPUART/LPUART_WakeUpFromStop/Src/main.c
  * @author  MCD Application Team
  * @brief   This example describes how to configure LPUART peripheral in Asynchronous mode
  *          for being able to wake from Stop 0 mode when a character is received on RX line using
  *          the STM32G0xx LPUART LL API.
  *          Peripheral initialization done using LL unitary services functions.
  ******************************************************************************
  * @attention
  *
  * Copyright (c) 2018-2020 STMicroelectronics.
  * All rights reserved.
  *
  * This software is licensed under terms that can be found in the LICENSE file
  * in the root directory of this software component.
  * If no LICENSE file comes with this software, it is provided AS-IS.
  *
  ******************************************************************************
  */

/* Includes ------------------------------------------------------------------*/
#include "main.h"

/** @addtogroup STM32G0xx_LL_Examples
  * @{
  */

/** @addtogroup LPUART_WakeUpFromStop
  * @{
  */

/* Private typedef -----------------------------------------------------------*/

/* Private define ------------------------------------------------------------*/

/* Private macro -------------------------------------------------------------*/

/* Private variables ---------------------------------------------------------*/
/**
  * @brief Variables used for character reception from PC Com port
  */
__IO uint8_t      ubFinalCharReceived = 0;
__IO uint32_t     ubReceivedChar;

/**
  * @brief Text string printed on PC Com port to inform MCU will enter in Stop 0 Mode
  */
uint8_t aTextInfo[] = "\r\nLPUART Example : MCU will now enter in Stop 0 mode.\n\rEnter any character for waking up MCU.\r\n";

/* Private function prototypes -----------------------------------------------*/
void     SystemClock_Config(void);
void     LED_Init(void);
void     LED_On(void);
void     LED_Off(void);
void     LED_Blinking(uint32_t Period);
void     LED_Blinking_3s(void);
void     Configure_LPUART1(void);
void     PrepareLPUARTToStopMode(void);
void     EnterSTOP0Mode(void);
void     PrintInfo(void);

/* Private functions ---------------------------------------------------------*/

/**
  * @brief  Main program
  * @param  None
  * @retval None
  */
int main(void)
{
  /* Configure the system clock to 56 MHz */
  SystemClock_Config();

  /* Initialize LED4 */
  LED_Init();

  /* Configure LPUART1 (LPUART IP configuration and related GPIO initialization) */
  Configure_LPUART1();

  /* Start main program loop :
     - make LED blink during 3 sec
     - Enter Stop 0 mode (LED turned Off)
     - Wait for any character received on LPUART RX line for waking up MCU
  */
  while (ubFinalCharReceived == 0)
  {
    /* LED blinks during 3 seconds */
    LED_Blinking_3s();

    /* Send Text Information on LPUART TX to PC Com port */
    PrintInfo();

    /* Prepare LPUART for entering Stop Mode */
    PrepareLPUARTToStopMode();
    
    /* Enter Stop 0 mode */
    EnterSTOP0Mode();
    
    /* At this point, MCU just wakes up from Stop 0 mode */
  }
  
  /* Infinite loop */
  while (1)
  {
  }
}

/**
  * @brief  This function configures LPUART1.
  * @note   This function is used to :
  *         -1- Enable GPIO clock and configures the LPUART1 pins.
  *         -2- NVIC Configuration for LPUART1 interrupts.
  *         -3- Enable the LPUART1 peripheral clock and clock source.
  *         -4- Configure LPUART1 functional parameters.
  *         -5- Enable LPUART1.
  * @note   Peripheral configuration is minimal configuration from reset values.
  *         Thus, some useless LL unitary functions calls below are provided as
  *         commented examples - setting is default configuration from reset.
  * @param  None
  * @retval None
  */
void Configure_LPUART1(void)
{
  /* (1) Enable GPIO clock and configures the LPUART1 pins *******************/
  /*    (TX on PC.1, RX on PC.0)                        **********************/

  /* Enable the peripheral clock of GPIOC */
  LL_IOP_GRP1_EnableClock(LL_IOP_GRP1_PERIPH_GPIOC);

  /* Configure TX Pin as : Alternate function, High Speed, PushPull, No-Pull */
  LL_GPIO_SetPinMode(GPIOC, LL_GPIO_PIN_1, LL_GPIO_MODE_ALTERNATE);
  LL_GPIO_SetAFPin_0_7(GPIOC, LL_GPIO_PIN_1, LL_GPIO_AF_1);
  LL_GPIO_SetPinSpeed(GPIOC, LL_GPIO_PIN_1, LL_GPIO_SPEED_FREQ_HIGH);
  LL_GPIO_SetPinOutputType(GPIOC, LL_GPIO_PIN_1, LL_GPIO_OUTPUT_PUSHPULL);
  LL_GPIO_SetPinPull(GPIOC, LL_GPIO_PIN_1, LL_GPIO_PULL_NO);

  /* Configure RX Pin as : Alternate function, High Speed, PushPull, No-Pull */
  LL_GPIO_SetPinMode(GPIOC, LL_GPIO_PIN_0, LL_GPIO_MODE_ALTERNATE);
  LL_GPIO_SetAFPin_0_7(GPIOC, LL_GPIO_PIN_0, LL_GPIO_AF_1);
  LL_GPIO_SetPinSpeed(GPIOC, LL_GPIO_PIN_0, LL_GPIO_SPEED_FREQ_HIGH);
  LL_GPIO_SetPinOutputType(GPIOC, LL_GPIO_PIN_0, LL_GPIO_OUTPUT_PUSHPULL);
  LL_GPIO_SetPinPull(GPIOC, LL_GPIO_PIN_0, LL_GPIO_PULL_NO);

  /* (2) NVIC Configuration for LPUART1 interrupts */
  /*  - Set priority for USART3_4_LPUART1_IRQn */
  /*  - Enable USART3_4_LPUART1_IRQn           */
  NVIC_SetPriority(USART3_4_LPUART1_IRQn, 0);  
  NVIC_EnableIRQ(USART3_4_LPUART1_IRQn);

  /* (3) Enable the LPUART1 peripheral clock and clock source ****************/
  LL_APB1_GRP1_EnableClock(LL_APB1_GRP1_PERIPH_LPUART1);

  /* Set LPUART1 clock source as HSI */
  LL_RCC_SetLPUARTClockSource(LL_RCC_LPUART1_CLKSOURCE_HSI);

  /* (4) Configure LPUART1 functional parameters ********************************/
  
  /* Disable LPUART1 prior modifying configuration registers */
  /* Note: Commented as corresponding to Reset value */
  // LL_LPUART_Disable(LPUART1);
  
  /* TX/RX direction */
  LL_LPUART_SetTransferDirection(LPUART1, LL_LPUART_DIRECTION_TX_RX);

  /* 8 data bit, 1 start bit, 1 stop bit, no parity */
  LL_LPUART_ConfigCharacter(LPUART1, LL_LPUART_DATAWIDTH_8B, LL_LPUART_PARITY_NONE, LL_LPUART_STOPBITS_1);

  /* No Hardware Flow control */
  /* Reset value is LL_USART_HWCONTROL_NONE */
  // LL_USART_SetHWFlowCtrl(LPUART1, LL_USART_HWCONTROL_NONE);

  /* Set Baudrate to 9600 using HSI frequency set to HSI_VALUE */
  LL_LPUART_SetBaudRate(LPUART1, HSI_VALUE, LL_LPUART_PRESCALER_DIV1, 9600); 

  /* Set the wake-up event type : specify wake-up on RXNE flag */
  LL_LPUART_SetWKUPType(LPUART1, LL_LPUART_WAKEUP_ON_RXNE);

  /* (5) Enable LPUART1 **********************************************************/
  LL_LPUART_Enable(LPUART1);
}

/**
  * @brief  Function to configure LPUART for being ready to enter "Stop 0" mode.
  * @param  None
  * @retval None
  */
void PrepareLPUARTToStopMode(void)
{

  /* Empty RX Fifo before entering Stop mode (Otherwise, characters already present in FIFO
     will lead to immediate wake up */
  while (LL_LPUART_IsActiveFlag_RXNE(LPUART1))
  {
    /* Read Received character. RXNE flag is cleared by reading of RDR register */
    ubReceivedChar = LL_LPUART_ReceiveData8(LPUART1);
  }

  /* Clear OVERRUN flag */
  LL_LPUART_ClearFlag_ORE(LPUART1);

  /* Make sure that no LPUART transfer is on-going */ 
  while(LL_LPUART_IsActiveFlag_BUSY(LPUART1) == 1)
  {
  }
  /* Make sure that LPUART is ready to receive */   
  while(LL_LPUART_IsActiveFlag_REACK(LPUART1) == 0)
  {
  }

  /* About to enter stop mode: switch off LED */
  LED_Off();

  /* Configure LPUART1 transfer interrupts : */
  /* Clear WUF flag and enable the UART Wake Up from stop mode Interrupt */
  LL_LPUART_ClearFlag_WKUP(LPUART1);
  LL_LPUART_EnableIT_WKUP(LPUART1);

  /* Enable Wake Up From Stop */
  LL_LPUART_EnableInStopMode(LPUART1);
}

/**
  * @brief  Function to enter in "Stop 0" mode.
  * @param  None
  * @retval None
  */
void EnterSTOP0Mode(void)
{
  /** Request to enter "Stop 0" mode
    * Following procedure describe in STM32G0xx Reference Manual
    * See PWR part, section Low-power modes, "Stop 0" mode
    */
  /* Set Stop 0 mode when CPU enters deepsleep */
  LL_PWR_SetPowerMode(LL_PWR_MODE_STOP0);

  /* Set SLEEPDEEP bit of Cortex System Control Register */
  LL_LPM_EnableDeepSleep();

  /* Request Wait For Interrupt */
  __WFI();
}

/**
  * @brief  Send Txt information message on LPUART Tx line (to PC Com port).
  * @param  None
  * @retval None
  */
void PrintInfo(void)
{
  uint32_t index = 0;
  
  /* Send characters one per one, until last char to be sent */
  for (index = 0; index < sizeof(aTextInfo); index++)
  {
    /* Wait for TXE flag to be raised */
    while (!LL_LPUART_IsActiveFlag_TXE(LPUART1))
    {
    }

    /* Write character in Transmit Data register.
       TXE flag is cleared by writing data in TDR register */
    LL_LPUART_TransmitData8(LPUART1, aTextInfo[index]);
  }

  /* Wait for TC flag to be raised for last char */
  while (!LL_LPUART_IsActiveFlag_TC(LPUART1))
  {
  }
}

/**
  * @brief  Initialize LED4.
  * @param  None
  * @retval None
  */
void LED_Init(void)
{
  /* Enable the LED4 Clock */
  LED4_GPIO_CLK_ENABLE();

  /* Configure IO in output push-pull mode to drive external LED4 */
  LL_GPIO_SetPinMode(LED4_GPIO_PORT, LED4_PIN, LL_GPIO_MODE_OUTPUT);
  /* Reset value is LL_GPIO_OUTPUT_PUSHPULL */
  //LL_GPIO_SetPinOutputType(LED4_GPIO_PORT, LED4_PIN, LL_GPIO_OUTPUT_PUSHPULL);
  /* Reset value is LL_GPIO_SPEED_FREQ_LOW */
  //LL_GPIO_SetPinSpeed(LED4_GPIO_PORT, LED4_PIN, LL_GPIO_SPEED_FREQ_LOW);
  /* Reset value is LL_GPIO_PULL_NO */
  //LL_GPIO_SetPinPull(LED4_GPIO_PORT, LED4_PIN, LL_GPIO_PULL_NO);
}

/**
  * @brief  Turn-on LED4.
  * @param  None
  * @retval None
  */
void LED_On(void)
{
  /* Turn LED4 on */
  LL_GPIO_SetOutputPin(LED4_GPIO_PORT, LED4_PIN);
}

/**
  * @brief  Turn-off LED4.
  * @param  None
  * @retval None
  */
void LED_Off(void)
{
  /* Turn LED4 off */
  LL_GPIO_ResetOutputPin(LED4_GPIO_PORT, LED4_PIN);
}

/**
  * @brief  Set LED4 to Blinking mode for an infinite loop (toggle period based on value provided as input parameter).
  * @param  Period : Period of time (in ms) between each toggling of LED
  *   This parameter can be user defined values. Pre-defined values used in that example are :
  *     @arg LED_BLINK_FAST : Fast Blinking
  *     @arg LED_BLINK_SLOW : Slow Blinking
  *     @arg LED_BLINK_ERROR : Error specific Blinking
  * @retval None
  */
void LED_Blinking(uint32_t Period)
{
  /* Toggle IO in an infinite loop */
  while (1)
  {
    LL_GPIO_TogglePin(LED4_GPIO_PORT, LED4_PIN);  
    LL_mDelay(Period);
  }
}

/**
  * @brief  Set LED4 to Blinking mode during 3s.
  * @param  None
  * @retval None
  */
void LED_Blinking_3s(void)
{
  uint32_t index=0;

  /* Toggle IO in during 3s (15*200ms) */
  for(index = 0; index < 15; index++)
  {
    LL_GPIO_TogglePin(LED4_GPIO_PORT, LED4_PIN);  
    LL_mDelay(200);
  }
}


/**
  * @brief  System Clock Configuration
  *         The system Clock is configured as follow : 
  *            System Clock source            = PLL (HSI)
  *            SYSCLK(Hz)                     = 56000000
  *            HCLK(Hz)                       = 56000000
  *            AHB Prescaler                  = 1
  *            APB1 Prescaler                 = 1
  *            HSI Frequency(Hz)              = 16000000
  *            Flash Latency(WS)              = 2
  *            PLLM                           = 4
  *            PLLN                           = 70
  *            PLLP                           = 10
  *            PLLQ                           = 5
  *            PLLR                           = 5
  *            Flash Latency(WS)              = 2
  * @param  None
  * @retval None
  */
void SystemClock_Config(void)
{
  LL_FLASH_SetLatency(LL_FLASH_LATENCY_2);
  /* HSI configuration and activation */
  LL_RCC_HSI_Enable();
  while(LL_RCC_HSI_IsReady() != 1) 
  {
  }

  /* Main PLL configuration and activation */
  LL_RCC_PLL_ConfigDomain_SYS(LL_RCC_PLLSOURCE_HSI, LL_RCC_PLLM_DIV_4, 70, LL_RCC_PLLR_DIV_5);
  LL_RCC_PLL_Enable();
  LL_RCC_PLL_EnableDomain_SYS();
  while(LL_RCC_PLL_IsReady() != 1) 
  {
  }

  /* Sysclk activation on the main PLL */

  LL_RCC_SetSysClkSource(LL_RCC_SYS_CLKSOURCE_PLL);
  while(LL_RCC_GetSysClkSource() != LL_RCC_SYS_CLKSOURCE_STATUS_PLL) 
  {
  }

  /* Set AHB prescaler*/
  LL_RCC_SetAHBPrescaler(LL_RCC_SYSCLK_DIV_1);

  /* Set APB1 prescaler*/
  LL_RCC_SetAPB1Prescaler(LL_RCC_APB1_DIV_1);

  /* Set systick to 1ms in using frequency set to 56MHz */
  /* This frequency can be calculated through LL RCC macro */
  /* ex: __LL_RCC_CALC_PLLCLK_FREQ(__LL_RCC_CALC_HSI_FREQ(), 
                                  LL_RCC_PLLM_DIV_4, 70, LL_RCC_PLLR_DIV_5)*/
  LL_Init1msTick(56000000);

  /* Update CMSIS variable (which can be updated also through SystemCoreClockUpdate function) */
  LL_SetSystemCoreClock(56000000);
}

/******************************************************************************/
/*   IRQ HANDLER TREATMENT Functions                                          */
/******************************************************************************/

/**
  * @brief  Function called from LPUART IRQ Handler when RXNE flag is set
  *         Function is in charge of reading character received on LPUART RX line.
  * @param  None
  * @retval None
  */
void LPUART_CharReception_Callback(void)
{
  /* Restore initial system clock configuration */
  SystemClock_Config();

  /* Read Received character. RXNE flag is cleared by reading of RDR register */
  ubReceivedChar = LL_LPUART_ReceiveData8(LPUART1);

  /* Check if received value is corresponding to specific one : S or s */
  if ((ubReceivedChar == 'S') || (ubReceivedChar == 's'))
  {
    /* Turn LED4 On : Expected character has been received */
    LED_On();

    /* End of program : set boolean for main loop exit */
    ubFinalCharReceived = 1;
  }

  /* Echo received character on TX */
  LL_LPUART_TransmitData8(LPUART1, ubReceivedChar);
}

/**
  * @brief  Function called in case of error detected in LPUART IT Handler
  * @param  None
  * @retval None
  */
void Error_Callback(void)
{
  /* Disable USART3_4_LPUART1_IRQn */
  NVIC_DisableIRQ(USART3_4_LPUART1_IRQn);
  
  /* Unexpected event : Set LED4 to Blinking mode to indicate error occurs */
  LED_Blinking(LED_BLINK_ERROR);
}

#ifdef  USE_FULL_ASSERT

/**
  * @brief  Reports the name of the source file and the source line number
  *         where the assert_param error has occurred.
  * @param  file: pointer to the source file name
  * @param  line: assert_param error line source number
  * @retval None
  */
void assert_failed(uint8_t *file, uint32_t line)
{
  /* User can add his own implementation to report the file name and line number,
     ex: printf("Wrong parameters value: file %s on line %d", file, line) */

  /* Infinite loop */
  while (1)
  {
  }
}
#endif

/**
  * @}
  */

/**
  * @}
  */

/************************ (C) COPYRIGHT STMicroelectronics *****END OF FILE****/
