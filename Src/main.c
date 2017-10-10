/**
  ******************************************************************************
  * File Name          : main.c
  * Description        : Main program body
  ******************************************************************************
  ** This notice applies to any and all portions of this file
  * that are not between comment pairs USER CODE BEGIN and
  * USER CODE END. Other portions of this file, whether 
  * inserted by the user or by software development tools
  * are owned by their respective copyright owners.
  *
  * COPYRIGHT(c) 2017 STMicroelectronics
  *
  * Redistribution and use in source and binary forms, with or without modification,
  * are permitted provided that the following conditions are met:
  *   1. Redistributions of source code must retain the above copyright notice,
  *      this list of conditions and the following disclaimer.
  *   2. Redistributions in binary form must reproduce the above copyright notice,
  *      this list of conditions and the following disclaimer in the documentation
  *      and/or other materials provided with the distribution.
  *   3. Neither the name of STMicroelectronics nor the names of its contributors
  *      may be used to endorse or promote products derived from this software
  *      without specific prior written permission.
  *
  * THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS"
  * AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE
  * IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE
  * DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT HOLDER OR CONTRIBUTORS BE LIABLE
  * FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL
  * DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR
  * SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER
  * CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY,
  * OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE
  * OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
  *
  ******************************************************************************
  */
/* Includes ------------------------------------------------------------------*/
#include "main.h"
#include "stm32f4xx_hal.h"
#include "spi.h"
#include "gpio.h"

/* USER CODE BEGIN Includes */
#include "spi_flash.h"
#include "spiffs.h"
/* USER CODE END Includes */

/* Private variables ---------------------------------------------------------*/

/* USER CODE BEGIN PV */
/* Private variables ---------------------------------------------------------*/
static spiffs fs;
/* USER CODE END PV */

/* Private function prototypes -----------------------------------------------*/
void SystemClock_Config(void);

/* USER CODE BEGIN PFP */
/* Private function prototypes -----------------------------------------------*/
#define LOG_PAGE_SIZE       256
static void my_spiffs_mount();
static u8_t spiffs_work_buf[LOG_PAGE_SIZE*2];
static u8_t spiffs_fds[32*4];
static u8_t spiffs_cache_buf[(LOG_PAGE_SIZE+32)*4];
/* USER CODE END PFP */

/* USER CODE BEGIN 0 */

/* USER CODE END 0 */

int main(void)
{

  /* USER CODE BEGIN 1 */
	char buf[12];
	spiffs_file fd1,fd2;
  /* USER CODE END 1 */

  /* MCU Configuration----------------------------------------------------------*/

  /* Reset of all peripherals, Initializes the Flash interface and the Systick. */
  HAL_Init();

  /* USER CODE BEGIN Init */

  /* USER CODE END Init */

  /* Configure the system clock */
  SystemClock_Config();

  /* USER CODE BEGIN SysInit */

  /* USER CODE END SysInit */

  /* Initialize all configured peripherals */
  MX_GPIO_Init();
  MX_SPI2_Init();

  /* USER CODE BEGIN 2 */
  sFLASH_Init();
  my_spiffs_mount();


    // create a file, delete previous if it already exists, and open it for reading and writing
    fd1 = SPIFFS_open(&fs, "my_file", SPIFFS_CREAT | SPIFFS_RDWR, 0);
    fd2 = SPIFFS_open(&fs, "baba_file", SPIFFS_CREAT | SPIFFS_RDWR, 0);
    SPIFFS_errno(fs);
//    if (fd1 < 0) {
//      printf("errno %i\n", SPIFFS_errno(&fs));
//      return 1;
//    }
    // write to it
    if (SPIFFS_write(&fs, fd1, (u8_t *)"Hello world", 12) < 0) {
      printf("errno %i\n", SPIFFS_errno(&fs));
      return 1;
    }
    if (SPIFFS_write(&fs, fd2, (u8_t *)"Baba", 5) < 0) {
          printf("errno %i\n", SPIFFS_errno(&fs));
          return 1;
        }
    // close it
    if (SPIFFS_close(&fs, fd1) < 0) {
      printf("errno %i\n", SPIFFS_errno(&fs));
      return 1;
    }
    if (SPIFFS_close(&fs, fd2) < 0) {
         printf("errno %i\n", SPIFFS_errno(&fs));
         return 1;
       }

    // open it
    fd1 = SPIFFS_open(&fs, "my_file", SPIFFS_RDWR, 0);
    fd2 = SPIFFS_open(&fs, "baba_file", SPIFFS_RDWR, 0);
//    if (fd1 < 0) {
//      printf("errno %i\n", SPIFFS_errno(&fs));
//      return 1;
//    }

    // read it
    if (SPIFFS_read(&fs, fd1, (u8_t *)buf, 12) < 0) {
      printf("errno %i\n", SPIFFS_errno(&fs));
      return 1;
    }
    if (SPIFFS_read(&fs, fd2, (u8_t *)buf, 5) < 0) {
         printf("errno %i\n", SPIFFS_errno(&fs));
         return 1;
       }
    // close it
    if (SPIFFS_close(&fs, fd1) < 0) {
      printf("errno %i\n", SPIFFS_errno(&fs));
      return 1;
    }
    if (SPIFFS_close(&fs, fd2) < 0) {
          printf("errno %i\n", SPIFFS_errno(&fs));
          return 1;
        }
  SPIFFS_unmount(&fs);
  //ID = sFLASH_ReadID();

  /* USER CODE END 2 */

  /* Infinite loop */
  /* USER CODE BEGIN WHILE */
  while (1)
  {
  /* USER CODE END WHILE */

  /* USER CODE BEGIN 3 */

  }
  /* USER CODE END 3 */

}

/** System Clock Configuration
*/
void SystemClock_Config(void)
{

  RCC_OscInitTypeDef RCC_OscInitStruct;
  RCC_ClkInitTypeDef RCC_ClkInitStruct;

    /**Configure the main internal regulator output voltage 
    */
  __HAL_RCC_PWR_CLK_ENABLE();

  __HAL_PWR_VOLTAGESCALING_CONFIG(PWR_REGULATOR_VOLTAGE_SCALE3);

    /**Initializes the CPU, AHB and APB busses clocks 
    */
  RCC_OscInitStruct.OscillatorType = RCC_OSCILLATORTYPE_HSE;
  RCC_OscInitStruct.HSEState = RCC_HSE_ON;
  RCC_OscInitStruct.PLL.PLLState = RCC_PLL_ON;
  RCC_OscInitStruct.PLL.PLLSource = RCC_PLLSOURCE_HSE;
  RCC_OscInitStruct.PLL.PLLM = 8;
  RCC_OscInitStruct.PLL.PLLN = 180;
  RCC_OscInitStruct.PLL.PLLP = RCC_PLLP_DIV2;
  RCC_OscInitStruct.PLL.PLLQ = 7;
  if (HAL_RCC_OscConfig(&RCC_OscInitStruct) != HAL_OK)
  {
    _Error_Handler(__FILE__, __LINE__);
  }

    /**Initializes the CPU, AHB and APB busses clocks 
    */
  RCC_ClkInitStruct.ClockType = RCC_CLOCKTYPE_HCLK|RCC_CLOCKTYPE_SYSCLK
                              |RCC_CLOCKTYPE_PCLK1|RCC_CLOCKTYPE_PCLK2;
  RCC_ClkInitStruct.SYSCLKSource = RCC_SYSCLKSOURCE_PLLCLK;
  RCC_ClkInitStruct.AHBCLKDivider = RCC_SYSCLK_DIV1;
  RCC_ClkInitStruct.APB1CLKDivider = RCC_HCLK_DIV4;
  RCC_ClkInitStruct.APB2CLKDivider = RCC_HCLK_DIV2;

  if (HAL_RCC_ClockConfig(&RCC_ClkInitStruct, FLASH_LATENCY_2) != HAL_OK)
  {
    _Error_Handler(__FILE__, __LINE__);
  }

    /**Configure the Systick interrupt time 
    */
  HAL_SYSTICK_Config(HAL_RCC_GetHCLKFreq()/1000);

    /**Configure the Systick 
    */
  HAL_SYSTICK_CLKSourceConfig(SYSTICK_CLKSOURCE_HCLK);

  /* SysTick_IRQn interrupt configuration */
  HAL_NVIC_SetPriority(SysTick_IRQn, 0, 0);
}

/* USER CODE BEGIN 4 */
static s32_t my_spiffs_read(u32_t addr, u32_t size, u8_t *dst) {
    sFLASH_ReadBuffer(dst,addr,size);
    return SPIFFS_OK;
  }

  static s32_t my_spiffs_write(u32_t addr, u32_t size, u8_t *src) {
	sFLASH_WriteBuffer(src,addr,size);
    return SPIFFS_OK;
  }

  static s32_t my_spiffs_erase(u32_t addr, u32_t size) {

    return sFLASH_Erase(addr, size);
  }

void my_spiffs_mount() {
    spiffs_config cfg;
    cfg.phys_size = N25Q256A_FLASH_SIZE; // use all spi flash
    cfg.phys_addr = 0; // start spiffs at start of spi flash
    cfg.phys_erase_block = N25Q256A_SECTOR_SIZE; // according to datasheet
    cfg.log_block_size = N25Q256A_SECTOR_SIZE; // let us not complicate things
    cfg.log_page_size = N25Q256A_PAGE_SIZE; // as we said

    cfg.hal_read_f = my_spiffs_read;
    cfg.hal_write_f = my_spiffs_write;
    cfg.hal_erase_f = my_spiffs_erase;

    int res = SPIFFS_mount(&fs,
      &cfg,
      spiffs_work_buf,
      spiffs_fds,
      sizeof(spiffs_fds),
      spiffs_cache_buf,
      sizeof(spiffs_cache_buf),
      0);
    printf("mount res: %i\n", res);
  }



/* USER CODE END 4 */

/**
  * @brief  This function is executed in case of error occurrence.
  * @param  None
  * @retval None
  */
void _Error_Handler(char * file, int line)
{
  /* USER CODE BEGIN Error_Handler_Debug */
  /* User can add his own implementation to report the HAL error return state */
  while(1) 
  {
  }
  /* USER CODE END Error_Handler_Debug */ 
}

#ifdef USE_FULL_ASSERT

/**
   * @brief Reports the name of the source file and the source line number
   * where the assert_param error has occurred.
   * @param file: pointer to the source file name
   * @param line: assert_param error line source number
   * @retval None
   */
void assert_failed(uint8_t* file, uint32_t line)
{
  /* USER CODE BEGIN 6 */
  /* User can add his own implementation to report the file name and line number,
    ex: printf("Wrong parameters value: file %s on line %d\r\n", file, line) */
  /* USER CODE END 6 */

}

#endif

/**
  * @}
  */ 

/**
  * @}
*/ 

/************************ (C) COPYRIGHT STMicroelectronics *****END OF FILE****/
