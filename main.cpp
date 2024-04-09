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
//#include <iostream>
#include <string>
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
 UART_HandleTypeDef huart1;

/* USER CODE BEGIN PV */

/* USER CODE END PV */

/* Private function prototypes -----------------------------------------------*/
void SystemClock_Config(void);
static void MX_GPIO_Init(void);
static void MX_USART1_UART_Init(void);
/* USER CODE BEGIN PFP */

/* USER CODE END PFP */

/* Private user code ---------------------------------------------------------*/
/* USER CODE BEGIN 0 */
short int lin=-1,col=-1,check=0;

class tab {
public:
  struct casa {
    bool in = false;
    char peca = '0';
  };
  char buffer[32];
  short int topo=-1;
  casa tabuleiro[8][8];
  tab() {
    tabuleiro[0][0].peca = 'r';
    tabuleiro[0][1].peca = 'n';
    tabuleiro[0][2].peca = 'b';
    tabuleiro[0][3].peca = 'q';
    tabuleiro[0][4].peca = 'k';
    tabuleiro[0][5].peca = 'b';
    tabuleiro[0][6].peca = 'n';
    tabuleiro[0][7].peca = 'r';
    for (int i = 0; i < 8; i++) {
      tabuleiro[0][i].in = true;
      tabuleiro[1][i].in = true;
      tabuleiro[1][i].peca = 'p';
      tabuleiro[7][i].in = true;
      tabuleiro[6][i].in = true;
      tabuleiro[6][i].peca = 'P';
    }
    tabuleiro[7][0].peca = 'R';
    tabuleiro[7][1].peca = 'N';
    tabuleiro[7][2].peca = 'B';
    tabuleiro[7][3].peca = 'Q';
    tabuleiro[7][4].peca = 'K';
    tabuleiro[7][5].peca = 'B';
    tabuleiro[7][6].peca = 'N';
    tabuleiro[7][7].peca = 'R';
  }
  void empilhar(char p){
    topo++;
    buffer[topo]=p;
  }
  char desempilhar(){
    topo--;
    return buffer[topo+1];
  }
};

tab chess;


bool C[8][8];
int m;
int n;

void leitura (int *c) {

	for (m = 0; m < 7; m++) {

		for (n = 0; n < 7; n++) {
			if (HAL_GPIO_ReadPin(GPIOB, c[n]) == 1) {
				C[m][n] = true;
			} else {
				C[m][n] = false;
			}

		}
		HAL_Delay(1);
		HAL_GPIO_WritePin(GPIOA, GPIO_PIN_1, GPIO_PIN_SET);
		HAL_Delay(1);
		HAL_GPIO_WritePin(GPIOA, GPIO_PIN_1, GPIO_PIN_RESET);
	}

	  	  }

short int cont=0;

void find_out(bool (*readtab)[8], int *c){
  for(int i=0;i<8;i++){
    for(int j=0;j<8;j++){
      if(readtab[i][j]==false && chess.tabuleiro[i][j].in==true){
        if(lin==i && col==j){
          check++;
          if(check==100){
            check=0;
            break;
          }
          i=0;j=0;
          leitura(c);
        }
        else {
        	lin=i;col=j;i=0;j=0;
        }
        }
      }
    }

  if(lin!=-1 && col!=-1){
    chess.empilhar(chess.tabuleiro[lin][col].peca);
    chess.tabuleiro[lin][col].peca='0';
    chess.tabuleiro[lin][col].in=false;
    cont++;
  }
  lin=-1;
  col=-1;
}

void uart_send(void){

	for(int i=0; i<8; i++) {
  for(int j=0;j<8;j++){
    HAL_UART_Transmit(&huart1, (uint8_t*)&chess.tabuleiro[i][j].peca, 1, 100);
  }
}

}

void find_in(bool (*readtab)[8], int *c){
  for(int i=0;i<8;i++){
    for(int j=0;j<8;j++){
      if(readtab[i][j]==true && chess.tabuleiro[i][j].in==false){
        if(lin==i && col==j){
          check++;
          if(check==100){
            check=0;
            break;
          }
          i=0;j=0;
          leitura(c);
        }
        else {
        	lin=i;col=j;i=0;j=0;
        }
      }
    }
  }
  if(lin!=-1 && col!=-1){
    chess.tabuleiro[lin][col].peca=chess.desempilhar();
    chess.tabuleiro[lin][col].in=true;
    cont=0;
    uart_send();
  }
  lin=-1;
  col=-1;
}
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
  MX_USART1_UART_Init();
  /* USER CODE BEGIN 2 */
	int c[8];

	c[0] = GPIO_PIN_0;
	c[1] = GPIO_PIN_1;
	c[2] = GPIO_PIN_2;
	c[3] = GPIO_PIN_3;
	c[4] = GPIO_PIN_4;
	c[5] = GPIO_PIN_5;
	c[6] = GPIO_PIN_6;
	c[7] = GPIO_PIN_7;
  /* USER CODE END 2 */

  /* Infinite loop */
  /* USER CODE BEGIN WHILE */
  while (1)
  {
		leitura(c);
		switch (cont) {
		case 0:
			find_out(C, c);
		case 1:
			find_in(C, c);
			find_out(C, c);
		case 2:
			find_in(C, c);
						}
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
  RCC_PeriphCLKInitTypeDef PeriphClkInit = {0};

  /** Initializes the RCC Oscillators according to the specified parameters
  * in the RCC_OscInitTypeDef structure.
  */
  RCC_OscInitStruct.OscillatorType = RCC_OSCILLATORTYPE_HSI;
  RCC_OscInitStruct.HSIState = RCC_HSI_ON;
  RCC_OscInitStruct.HSICalibrationValue = RCC_HSICALIBRATION_DEFAULT;
  RCC_OscInitStruct.PLL.PLLState = RCC_PLL_NONE;
  if (HAL_RCC_OscConfig(&RCC_OscInitStruct) != HAL_OK)
  {
    Error_Handler();
  }

  /** Initializes the CPU, AHB and APB buses clocks
  */
  RCC_ClkInitStruct.ClockType = RCC_CLOCKTYPE_HCLK|RCC_CLOCKTYPE_SYSCLK
                              |RCC_CLOCKTYPE_PCLK1;
  RCC_ClkInitStruct.SYSCLKSource = RCC_SYSCLKSOURCE_HSI;
  RCC_ClkInitStruct.AHBCLKDivider = RCC_SYSCLK_DIV1;
  RCC_ClkInitStruct.APB1CLKDivider = RCC_HCLK_DIV1;

  if (HAL_RCC_ClockConfig(&RCC_ClkInitStruct, FLASH_LATENCY_0) != HAL_OK)
  {
    Error_Handler();
  }
  PeriphClkInit.PeriphClockSelection = RCC_PERIPHCLK_USART1;
  PeriphClkInit.Usart1ClockSelection = RCC_USART1CLKSOURCE_PCLK1;
  if (HAL_RCCEx_PeriphCLKConfig(&PeriphClkInit) != HAL_OK)
  {
    Error_Handler();
  }
}

/**
  * @brief USART1 Initialization Function
  * @param None
  * @retval None
  */
static void MX_USART1_UART_Init(void)
{

  /* USER CODE BEGIN USART1_Init 0 */

  /* USER CODE END USART1_Init 0 */

  /* USER CODE BEGIN USART1_Init 1 */

  /* USER CODE END USART1_Init 1 */
  huart1.Instance = USART1;
  huart1.Init.BaudRate = 9600;
  huart1.Init.WordLength = UART_WORDLENGTH_8B;
  huart1.Init.StopBits = UART_STOPBITS_1;
  huart1.Init.Parity = UART_PARITY_NONE;
  huart1.Init.Mode = UART_MODE_TX_RX;
  huart1.Init.HwFlowCtl = UART_HWCONTROL_NONE;
  huart1.Init.OverSampling = UART_OVERSAMPLING_16;
  huart1.Init.OneBitSampling = UART_ONE_BIT_SAMPLE_DISABLE;
  huart1.AdvancedInit.AdvFeatureInit = UART_ADVFEATURE_NO_INIT;
  if (HAL_UART_Init(&huart1) != HAL_OK)
  {
    Error_Handler();
  }
  /* USER CODE BEGIN USART1_Init 2 */

  /* USER CODE END USART1_Init 2 */

}

/**
  * @brief GPIO Initialization Function
  * @param None
  * @retval None
  */
static void MX_GPIO_Init(void)
{
  GPIO_InitTypeDef GPIO_InitStruct = {0};

  /* GPIO Ports Clock Enable */
  __HAL_RCC_GPIOA_CLK_ENABLE();
  __HAL_RCC_GPIOB_CLK_ENABLE();

  /*Configure GPIO pin Output Level */
  HAL_GPIO_WritePin(GPIOB, GPIO_PIN_1, GPIO_PIN_RESET);

  /*Configure GPIO pins : PA0 PA1 PA2 PA3
                           PA4 PA5 PA6 PA7 */
  GPIO_InitStruct.Pin = GPIO_PIN_0|GPIO_PIN_1|GPIO_PIN_2|GPIO_PIN_3
                          |GPIO_PIN_4|GPIO_PIN_5|GPIO_PIN_6|GPIO_PIN_7;
  GPIO_InitStruct.Mode = GPIO_MODE_INPUT;
  GPIO_InitStruct.Pull = GPIO_PULLDOWN;
  HAL_GPIO_Init(GPIOA, &GPIO_InitStruct);

  /*Configure GPIO pin : PB1 */
  GPIO_InitStruct.Pin = GPIO_PIN_1;
  GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
  GPIO_InitStruct.Pull = GPIO_NOPULL;
  GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_LOW;
  HAL_GPIO_Init(GPIOB, &GPIO_InitStruct);

}

/* USER CODE BEGIN 4 */

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
