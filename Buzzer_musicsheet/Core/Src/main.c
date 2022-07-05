/* USER CODE BEGIN Header */
/**
  ******************************************************************************
  * @file           : main.c
  * @brief          : Main program body
  ******************************************************************************
  * @attention
  *
  * Copyright (c) 2022 STMicroelectronics.
  * All rights reserved.
  *
  * This software is licensed under terms that can be found in the LICENSE file
  * in the root directory of this software component.
  * If no LICENSE file comes with this software, it is provided AS-IS.
  *
  ******************************************************************************
  */
/* USER CODE END Header */
/* Includes ------------------------------------------------------------------*/
#include "main.h"
#include "rtc.h"
#include "tim.h"
#include "usart.h"
#include "gpio.h"

/* Private includes ----------------------------------------------------------*/
/* USER CODE BEGIN Includes */

/* USER CODE END Includes */

/* Private typedef -----------------------------------------------------------*/
/* USER CODE BEGIN PTD */

/* USER CODE END PTD */

/* Private define ------------------------------------------------------------*/
/* USER CODE BEGIN PD */
/* USER CODE END PD */

/* Private macro -------------------------------------------------------------*/
/* USER CODE BEGIN PM */

/* USER CODE END PM */

/* Private variables ---------------------------------------------------------*/

/* USER CODE BEGIN PV */

/* USER CODE END PV */

/* Private function prototypes -----------------------------------------------*/
void SystemClock_Config(void);
static void MX_NVIC_Init(void);
/* USER CODE BEGIN PFP */
int __io_putchar(int ch) {
	HAL_UART_Transmit(&huart3, &ch, 1, 1000);
	return ch;
}
/* USER CODE END PFP */

/* Private user code ---------------------------------------------------------*/
/* USER CODE BEGIN 0 */
#define MaxHz 3060000



int pitchtoint(char p);
int pow2(int num);
double pow106(int num);
void musicQ(char*music, int delay);

struct sheet getsheet(struct music ,int select);



int beat = 1;
uint8_t rx_data;

uint32_t begin_tick = 0;
uint32_t current_tick = 0;

/* USER CODE END 0 */

/**
  * @brief  The application entry point.
  * @retval int
  */
int main(void)
{
  /* USER CODE BEGIN 1 */


  /* USER CODE END 1 */

  /* MCU Configuration--------------------------------------------------------*/

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
  MX_RTC_Init();
  MX_TIM2_Init();
  MX_TIM3_Init();
  MX_TIM4_Init();
  MX_USART3_UART_Init();

  /* Initialize interrupts */
  MX_NVIC_Init();
  /* USER CODE BEGIN 2 */
//HAL_TIM_Base_Start_IT(&htim2);
//HAL_TIM_Base_Start_IT(&htim3);
//HAL_TIM_Base_Start_IT(&htim4);
HAL_UART_Receive_IT(&huart3, &rx_data, 1);
HAL_TIM_PWM_Start(&htim3, TIM_CHANNEL_3);
HAL_TIM_PWM_Start(&htim2, TIM_CHANNEL_3);

uint16_t CCR_value = 100;
uint16_t ARR_value = 100;



//블로그 정리
//delay를 systic으로 변경
//파형을 곡선으로 변경.
//main for문 끝날때 조건을 좀더 자연스럽게 바꾸기
//블루투스로 쏠때 packet데이터 생성하는 함수+parsing하는 함수.

//c++과제하러가야해서 나중에함.
typedef struct _music1 {
	char music1[3];			//구조체 배열 넣으려했는데 안됨. 그리고 이거 악보로 만들려고 한거임.
	int durations[];		//박자.

}music1;

char* canon[] = {
		"5g","5e","5f","5g","5e","5f","5g",
		"4g","4a","4b","5c","5d","5e","5f",
		"5e","5c","5d","5e","4e","4f","4g","4a","4g","4f","4g","5c","4b","5c",
		"4a","5c","4b","4a","4g", "4f","4g","4f","4e","4f","4g","4a","4b","5c",
		"4a","5c","4b","5c","4b","4a","4b","5c","5d","5c","4b","5c","4a","4b",",","5c",
		"5c","5c","5c","5c","5c","5c","6c"
		",",",",",",",",",",",",",",",",",",",",
		"x"

};

int canonduration[] ={
		500,250,250,500,250,250,250,
		250,250,250,250,250,250,250,
		500,250,250,500,250,250,250,250,250,250,250,250,250,250,
		500,250,250,500,250,250,250,250,250,250,250,250,250,250,
		500,250,250,500,250,250,250,250,250,250,250,250,250,250,1000,250,
		250,250,250,250,250,250,2000,
		250,250,250,250,250,250,250,250,250,250
};


  /* USER CODE END 2 */

  /* Infinite loop */
  /* USER CODE BEGIN WHILE */

  while (1)
  {

	  //char 포인터배열 악보. 배열에 저장된건 문자열. 포인터에 저장된건 배열의 주소들
	  //int 박자


	  	  for(int i = 0 ; canon[i][0] != 'x';i++) {
	  			musicQ(canon[i],canonduration[i]/beat);	//뒤의 박자역할하는 /2를 인터럽트로해서 /i 로 바꾸자.
	  	  }






//	  TIM3->CCR3 = ARR_value/2;	//OCR
//	  CCR_value = 5;
//	  //if(value > 20) value = 10;
//	  HAL_Delay(1000);
//	  if(CCR_value>TIM3->ARR) CCR_value = 10;
////	  HAL_Delay(1000);


    /* USER CODE END WHILE */

    /* USER CODE BEGIN 3 */
  }
  /* USER CODE END 3 */
}

/**
  * @brief System Clock Configuration
  * @retval None
  */
void SystemClock_Config(void)
{
  RCC_OscInitTypeDef RCC_OscInitStruct = {0};
  RCC_ClkInitTypeDef RCC_ClkInitStruct = {0};

  /** Configure the main internal regulator output voltage
  */
  __HAL_RCC_PWR_CLK_ENABLE();
  __HAL_PWR_VOLTAGESCALING_CONFIG(PWR_REGULATOR_VOLTAGE_SCALE1);

  /** Initializes the RCC Oscillators according to the specified parameters
  * in the RCC_OscInitTypeDef structure.
  */
  RCC_OscInitStruct.OscillatorType = RCC_OSCILLATORTYPE_HSI|RCC_OSCILLATORTYPE_LSE;
  RCC_OscInitStruct.LSEState = RCC_LSE_ON;
  RCC_OscInitStruct.HSIState = RCC_HSI_ON;
  RCC_OscInitStruct.HSICalibrationValue = RCC_HSICALIBRATION_DEFAULT;
  RCC_OscInitStruct.PLL.PLLState = RCC_PLL_ON;
  RCC_OscInitStruct.PLL.PLLSource = RCC_PLLSOURCE_HSI;
  RCC_OscInitStruct.PLL.PLLM = 8;
  RCC_OscInitStruct.PLL.PLLN = 180;
  RCC_OscInitStruct.PLL.PLLP = RCC_PLLP_DIV2;
  RCC_OscInitStruct.PLL.PLLQ = 4;
  if (HAL_RCC_OscConfig(&RCC_OscInitStruct) != HAL_OK)
  {
    Error_Handler();
  }

  /** Activate the Over-Drive mode
  */
  if (HAL_PWREx_EnableOverDrive() != HAL_OK)
  {
    Error_Handler();
  }

  /** Initializes the CPU, AHB and APB buses clocks
  */
  RCC_ClkInitStruct.ClockType = RCC_CLOCKTYPE_HCLK|RCC_CLOCKTYPE_SYSCLK
                              |RCC_CLOCKTYPE_PCLK1|RCC_CLOCKTYPE_PCLK2;
  RCC_ClkInitStruct.SYSCLKSource = RCC_SYSCLKSOURCE_PLLCLK;
  RCC_ClkInitStruct.AHBCLKDivider = RCC_SYSCLK_DIV1;
  RCC_ClkInitStruct.APB1CLKDivider = RCC_HCLK_DIV4;
  RCC_ClkInitStruct.APB2CLKDivider = RCC_HCLK_DIV2;

  if (HAL_RCC_ClockConfig(&RCC_ClkInitStruct, FLASH_LATENCY_5) != HAL_OK)
  {
    Error_Handler();
  }
}

/**
  * @brief NVIC Configuration.
  * @retval None
  */
static void MX_NVIC_Init(void)
{
  /* TIM2_IRQn interrupt configuration */
  HAL_NVIC_SetPriority(TIM2_IRQn, 0, 0);
  HAL_NVIC_EnableIRQ(TIM2_IRQn);
  /* TIM3_IRQn interrupt configuration */
  HAL_NVIC_SetPriority(TIM3_IRQn, 0, 0);
  HAL_NVIC_EnableIRQ(TIM3_IRQn);
  /* TIM4_IRQn interrupt configuration */
  HAL_NVIC_SetPriority(TIM4_IRQn, 0, 0);
  HAL_NVIC_EnableIRQ(TIM4_IRQn);
  /* USART3_IRQn interrupt configuration */
  HAL_NVIC_SetPriority(USART3_IRQn, 0, 0);
  HAL_NVIC_EnableIRQ(USART3_IRQn);
  /* EXTI15_10_IRQn interrupt configuration */
  HAL_NVIC_SetPriority(EXTI15_10_IRQn, 0, 0);
  HAL_NVIC_EnableIRQ(EXTI15_10_IRQn);
}

/* USER CODE BEGIN 4 */
void musicQ(char*music, int delay){


	int octave = music[0] - '0';
	int pitch = pitchtoint(music[1]);
	int plat = 0;
	double volume = 1;

	begin_tick = HAL_GetTick();

	if(music[2] == 'p') {
		plat = 1;
	} else {
		plat = 0;
	}



	current_tick = HAL_GetTick();
	if(current_tick - begin_tick >= 1){	//틱이 1000이 넘어가면 시작은 끝난지점을 시점이 시작지점이 된다. 1을 반환하여 time_module의 값이 진행되도록 한다.

		begin_tick = current_tick;
	}
	for(int i = delay; i > 0; i--){	//ex) delay = 1000

			if (music[0] == ',') {	//쉼표

				TIM2->CCR3 = 0;
				HAL_Delay(1);
			} else {
				if (i > (delay / 2)) {

					TIM2->ARR = (MaxHz / (16.35 * pow106(pitch + plat) * pow2(octave)));
					TIM2->CCR3 = (MaxHz/ (16.35 * pow106(pitch + plat) * pow2(octave))) * (volume / delay);
					volume++;
					HAL_Delay(1);

				} else if (i <= (delay / 2)) {
					TIM2->ARR = (MaxHz / (16.35 * pow106(pitch + plat) * pow2(octave)));
					TIM2->CCR3 = (MaxHz/ (16.35 * pow106(pitch + plat) * pow2(octave))) * (volume / delay);
					volume--;
					HAL_Delay(1);
				}
			}
	}
		//	if(pitch == 0 && plat == 1) {	//도플랫
		//
		//
		//		TIM2 -> ARR = (MaxHz /(16.35 *pow106(pitch+plat) * pow2(octave)));
		//		TIM2 -> CCR3 = (MaxHz /(16.35 *pow106(pitch+plat) * pow2(octave))) / 2;
		//		HAL_Delay(delay);
		//	}
		//	else if (pitch == 0 && plat == 0) { 	//도
		//		TIM2->ARR = (MaxHz / (16.35  * pow2(octave)));
		//		TIM2->CCR3 = (MaxHz / (16.35 * pow2(octave))) / 2;
		//		HAL_Delay(delay);
		//
		//	}




		//	else {
		//	}
}


int pitchtoint(char p){	//계이름.
	if(p == 'c')	{
		return 0;
	}
	else if(p == 'd')	{
		return 2;
	}
	else if(p == 'e')	{
		return 4;
	}
	else if(p == 'f')	{
		return 5;
	}
	else if(p == 'g')	{
		return 7;
	}
	else if(p == 'a')	{
		return 9;
	}
	else if(p == 'b')	{
		return 11;
	}
	else if(','){
		return 12;
	}
}
double pow106(int num){		//2의 제곱승들		//옥타브전용
	double result = 1;

	if(num == 0) result = 1;
	else {
		for(int i = 0 ;i < num; i++){
			result *= 1.06;
		}
	}

	return result;
}
int pow2(int num){		//2의 제곱승들		//옥타브전용
	int result = 1;

	if(num == 0) result = 1;
	else {
		for(int i = 0 ;i < num; i++){
			result *= 2;
		}
	}

	return result;
}

void HAL_GPIO_EXTI_Callback(uint16_t GPIO_Pin){
	if(GPIO_Pin == GPIO_PIN_13) {

		beat *= 2;
		if(beat > 8) {
			beat = 1;
		}

	}

}
void HAL_UART_RxCpltCallback(UART_HandleTypeDef *huart) {

	if(huart->Instance == USART3) {
		HAL_UART_Receive_IT(&huart3, &rx_data, 1);
		HAL_UART_Transmit(&huart3, &rx_data, 1, 1000);
	}

}
//struct sheet getsheet( int select){//음악들이 들어가있는 구조체중에 select 번호의 음악을 선택.
//
//
//
//
//	return;
//}





//void HAL_TIM_PeriodElapsedCallback(TIM_HandleTypeDef *htim) {
//	if(htim->Instance == TIM2) {
//		HAL_GPIO_TogglePin(GPIOB, GPIO_PIN_0);
//	}
//	if(htim->Instance == TIM3) {
//		HAL_GPIO_TogglePin(GPIOB, GPIO_PIN_7);
//	}
//	if(htim->Instance == TIM4) {
//		HAL_GPIO_TogglePin(GPIOB, GPIO_PIN_14);
//	}
//
//
//}
/* USER CODE END 4 */

/**
  * @brief  This function is executed in case of error occurrence.
  * @retval None
  */
void Error_Handler(void)
{
  /* USER CODE BEGIN Error_Handler_Debug */
  /* User can add his own implementation to report the HAL error return state */
  __disable_irq();
  while (1)
  {
  }
  /* USER CODE END Error_Handler_Debug */
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
  /* USER CODE BEGIN 6 */
  /* User can add his own implementation to report the file name and line number,
     ex: printf("Wrong parameters value: file %s on line %d\r\n", file, line) */
  /* USER CODE END 6 */
}
#endif /* USE_FULL_ASSERT */
