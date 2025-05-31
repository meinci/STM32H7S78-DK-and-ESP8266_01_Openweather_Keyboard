/* USER CODE BEGIN Header */
/**
  ******************************************************************************
  * @file           : main.c
  * @brief          : Main program body
  ******************************************************************************
  * @attention
  *
  * Copyright (c) 2023 STMicroelectronics.
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
#include "FreeRTOS.h"
#include "cmsis_os2.h"
#include "app_touchgfx.h"

/* Private includes ----------------------------------------------------------*/
/* USER CODE BEGIN Includes */
#include <string.h>
#include <stdio.h>
#include <cJSON.h>
#include "datetime.h"
#include <stdlib.h>
#include <stdio.h>
#include <string.h>

#include "globals.h"
#include "wifi_credentials.h"


/* USER CODE END Includes */

/* Private typedef -----------------------------------------------------------*/
/* USER CODE BEGIN PTD */

/* USER CODE END PTD */

/* Private define ------------------------------------------------------------*/
/* USER CODE BEGIN PD */

/* USER CODE END PD */

/* Private macro -------------------------------------------------------------*/
/* USER CODE BEGIN PM */
// Git

/* USER CODE END PM */

/* Private variables ---------------------------------------------------------*/

CRC_HandleTypeDef hcrc;

DMA2D_HandleTypeDef hdma2d;

GPU2D_HandleTypeDef hgpu2d;

I2C_HandleTypeDef hi2c1;

JPEG_HandleTypeDef hjpeg;
DMA_HandleTypeDef handle_HPDMA1_Channel1;
DMA_HandleTypeDef handle_HPDMA1_Channel0;

LTDC_HandleTypeDef hltdc;

TIM_HandleTypeDef htim7;

UART_HandleTypeDef huart7;

/* Definitions for defaultTask */
osThreadId_t defaultTaskHandle;
const osThreadAttr_t defaultTask_attributes = {
  .name = "defaultTask",
  .stack_size = 1000 * 4,
  .priority = (osPriority_t) osPriorityNormal,
};
/* Definitions for TouchGFXTask */
osThreadId_t TouchGFXTaskHandle;
const osThreadAttr_t TouchGFXTask_attributes = {
  .name = "TouchGFXTask",
  .stack_size = 4096 * 4,
  .priority = (osPriority_t) osPriorityNormal,
};
/* Definitions for GuiQueue */
osMessageQueueId_t GuiQueueHandle;
const osMessageQueueAttr_t GuiQueue_attributes = {
  .name = "GuiQueue"
};
/* USER CODE BEGIN PV */


/* USER CODE END PV */

/* Private function prototypes -----------------------------------------------*/
static void MPU_Config(void);
static void MX_GPIO_Init(void);
static void MX_HPDMA1_Init(void);
static void MX_LTDC_Init(void);
static void MX_CRC_Init(void);
static void MX_DMA2D_Init(void);
static void MX_JPEG_Init(void);
static void MX_FLASH_Init(void);
static void MX_I2C1_Init(void);
static void MX_GPU2D_Init(void);
static void MX_ICACHE_GPU2D_Init(void);
static void MX_UART7_Init(void);
static void MX_TIM7_Init(void);
void StartDefaultTask(void *argument);
extern void TouchGFX_Task(void *argument);

/* USER CODE BEGIN PFP */

/* USER CODE END PFP */

/* Private user code ---------------------------------------------------------*/
/* USER CODE BEGIN 0 */

#define TX_BUFFER_SIZE 256
#define Rx_Data_size 628

uint8_t tx_buffer[TX_BUFFER_SIZE];  // Buffer for transmitting data
char RxData[Rx_Data_size];
char *json_data = NULL; // Hier wird die globale Variable einmalig definiert

__IO float guiTemp;
char guiIcon[6];
char guiDescription[25];
__IO int guiHumi;
__IO int guiPres;
__IO int guiYear;
__IO int guiMonth;
__IO int guiDay;
__IO int guiHour;
__IO int guiMinute;
__IO int request = 0;
char guiCity[30];
char guiSSID[32] = "UnknownSSID";
char stadt[25];


#define MAX_SSIDS  20 // Maximale Anzahl an SSIDs, die gespeichert werden sollen

#define MAX_GUI_SSID_LEN  32+1 // Maximale Laenge einer SSID (inkl. '\0')
int foundCount = 0;
long stamp;
int zone;
int scanSSIDs = 0;
char guissidList[MAX_SSIDS][MAX_GUI_SSID_LEN];
char SSIDs_Buffer[512];  // Der Puffer bleibt bei 512 Bytes

#define MAX_REQ 512
char AT_REQUEST_1[MAX_REQ];

/* Maximale Längen (inkl. NULL-Terminator) definieren */
#define MAX_SSID_LEN     32+1
#define MAX_PASSWORD_LEN 32+1

/* Globale Puffer für SSID und Passwort */
char ssid_global[MAX_SSID_LEN];
char password_global[MAX_PASSWORD_LEN];


typedef struct {
  	double temperature;
  	char iconId[6];
  	char description[35];
  	int humidity;
  	int pressure;
  	long timestamp;       // Aktueller Zeitstempel
  	long sunrise;         // Sonnenaufgang
  	long sunset;          // Sonnenuntergang
  	int timezone;         // Zeitzone in Sekunden
  	char city_name[50];
  }WeatherData;

char stadt[25];
const char *api_key = "b3a6cd1cdf759486e569c8d6daef8db5";

char *AT_REQUEST_SSID = "AT+CWJAP?\r\n";
char *AT_REQUEST_nearby_SSID = "AT+CWLAP\r\n";
char *AT_OPEN_CONNECTION = "AT+CIPSTART=\"TCP\",\"api.openweathermap.org\",80\r\n";
char *AT_REQUEST_0 = "GET /data/2.5/weather?q=Dortmund&appid=b3a6cd1cdf759486e569c8d6daef8db5&lang=de&units=metric\r\nHost: api.openweathermap.org\r\nConnection: close\r\n\r\n";
char *default_request = "GET /data/2.5/weather?q=Ennepetal&appid=b3a6cd1cdf759486e569c8d6daef8db5&lang=de&units=metric\r\nHost: api.openweathermap.org\r\nConnection: close\r\n\r\n";
char AT_NEW_REQUEST_1[MAX_REQ];

int weatherData_cpl =0;
char AT_CIPSEND_0[32];
char AT_CIPSEND_1[32];
#define TEMP_BUFFER_SIZE 1024
char temp_buffer[TEMP_BUFFER_SIZE];
int temp_buffer_index = 0;

void send_at_command(char *command);//Protype

char* extract_json(const char *response) {
    // Suche den Beginn der JSON-Daten ('{')
    char *json_start = strchr(response, '{');
    if (json_start == NULL) {
        printf("Keine JSON-Daten gefunden!\n");
        return NULL;
    }
    return json_start; // Rückgabe der Position des ersten '{'
}

// Deklaration (Prototyp) der Funktion:
void parse_weather_data(const char *json_response);
void extract_ssid(const char *response, char *ssidBuffer, size_t ssidBufferSize);
void extract_all_ssids(const char *response, char guissidList[][MAX_SSID_LEN], size_t maxSSIDs, size_t ssidBufferSize);

void HAL_UARTEx_RxEventCallback(UART_HandleTypeDef *huart, uint16_t Size) {
	if (huart->Instance == UART7) {
		// Empfange Daten in den temporären Puffer
		if (temp_buffer_index + Size < TEMP_BUFFER_SIZE) {
			memcpy(&temp_buffer[temp_buffer_index], RxData, Size);
			temp_buffer_index += Size;
			temp_buffer[temp_buffer_index] = '\0'; // Nullterminierung

			// Überprüfe auf aktuell verbundene SSID
			if (strstr(temp_buffer, "+CWJAP:") != NULL) {
				extract_ssid(temp_buffer, guiSSID, sizeof(guiSSID));
			}
			//Listet alle verfügbaren SSIDs
			if (strstr(temp_buffer, "+CWLAP:") != NULL){
				//char ssidList[10][32]; // Platz für bis zu 10 SSIDs mit maximal 31 Zeichen
				extract_all_ssids(temp_buffer, guissidList, 10, 32);
				SSIDs_Buffer[0] = '\0';  // Buffer als leeren String initialisieren
				for (int i = 0; i < 10 && guissidList[i][0] != '\0'; i++) {
					// Zeichenkette "- " + SSID anhängen
					strncat(SSIDs_Buffer, "- ", sizeof(SSIDs_Buffer) - strlen(SSIDs_Buffer) - 1);
					strncat(SSIDs_Buffer, guissidList[i], sizeof(SSIDs_Buffer) - strlen(SSIDs_Buffer) - 1);
					strncat(SSIDs_Buffer, "\n", sizeof(SSIDs_Buffer) - strlen(SSIDs_Buffer) - 1);
				}
			}

			if (strstr((char *)RxData, "CONNECT") != NULL && strstr((char *)RxData, "OK")!= NULL) {
				// Puffer zurücksetzen
				memset(RxData, 0, sizeof(RxData)); // Füllt den gesamten Puffer mit Nullen
				send_at_command(AT_CIPSEND_1);
			}

			if (strstr((char *)RxData, "OK") != NULL && strchr((char *)RxData, '>') != NULL) {
				// Puffer zurücksetzen
				memset(RxData, 0, sizeof(RxData)); // Füllt den gesamten Puffer mit Nullen
				send_at_command(AT_REQUEST_1);
			}

			// Überprüfe, ob die Daten vollständig sind (endet mit '}')
			if (strchr(RxData, '}') != NULL) {
				// JSON-Daten extrahieren und verarbeiten
				json_data = extract_json(temp_buffer);
				if (json_data != NULL) {
					parse_weather_data(json_data);
					send_at_command(AT_REQUEST_SSID); // Anfrage nach der aktuellen SSID
					scanSSIDs = 1;
				}
				// Puffer zurücksetzen
				temp_buffer_index = 0;
				memset(temp_buffer, 0, TEMP_BUFFER_SIZE);
			}
		} else {
			temp_buffer_index = 0; // Puffer zurücksetzen
		}

		// Neustart des UART-Empfangs
		if (HAL_UARTEx_ReceiveToIdle_IT(&huart7,  (uint8_t *)RxData, Rx_Data_size) != HAL_OK) {
			printf("Fehler beim Starten des UART-Empfangs\n");
		} else {
			printf("UART-Empfang gestartet\n");
		}
	}
}

void parse_weather_data(const char *json_response) {
	WeatherData data; // Lokale Struct-Variable, die wir füllen
	data.humidity = 0;
	data.temperature = 0.0;
	strcpy(data.city_name, "Unknown");

	DateTime datum; // Deklaration
	datum = convert_unix_timestamp(stamp, zone); // Initialisierung
	guiYear = datum.year;
	guiMonth = datum.month;
	guiDay = datum.day;
	guiHour = datum.hour;
	guiMinute = datum.minute;

	if (json_response == NULL || strlen(json_response) == 0) {
		printf("JSON-Daten sind leer oder NULL!\n");
	}
	cJSON *root = cJSON_Parse(json_response);
	if (root == NULL) {
		const char *error_ptr = cJSON_GetErrorPtr();
		if (error_ptr != NULL) {
			printf("JSON Parsing Error before: %s\n", error_ptr);
		}
	}
	// Aktuellen Zeitstempel extrahieren
	cJSON *dt = cJSON_GetObjectItem(root, "dt");
	if (cJSON_IsNumber(dt)) {
		data.timestamp = dt->valueint;
		stamp = data.timestamp;
	}
	// Zeitzone extrahieren
	cJSON *timezone = cJSON_GetObjectItem(root, "timezone");
	if (cJSON_IsNumber(timezone)) {
		data.timezone = timezone->valueint;
		zone = data.timezone;
	}

	// "weather"-Array holen
	cJSON *weather_array = cJSON_GetObjectItem(root, "weather");
	if (cJSON_IsArray(weather_array)){
		// Erstes Element im "weather"-Array holen
		cJSON *weather_item = cJSON_GetArrayItem(weather_array, 0);
		if (cJSON_IsObject(weather_item)){
			cJSON *icon = cJSON_GetObjectItem(weather_item, "icon"); // Darin das "icon" holen
			if (cJSON_IsString(icon)){
				strncpy(data.iconId, icon->valuestring, sizeof(data.iconId) - 1); // In deine Struct schreiben
				data.iconId[sizeof(data.iconId) - 1] = '\0';
				strncpy(guiIcon, data.iconId, sizeof(guiIcon) - 1); // In dein globales Array schreiben
				guiIcon[sizeof(guiIcon) - 1] = '\0';
			}
		}
		cJSON *description_item = cJSON_GetObjectItem(weather_item, "description"); // Darin das "description" holen
		if (cJSON_IsString(description_item)){
			strncpy(data.description, description_item->valuestring, sizeof(data.description) - 1); // In deine Struct schreiben
			data.description[sizeof(data.description) - 1] = '\0';
			strncpy(guiDescription, data.description, sizeof(guiDescription) - 1); // In dein globales Array schreiben
			guiDescription[sizeof(guiDescription) - 1] = '\0';
		}
	}
	cJSON *main_object = cJSON_GetObjectItem(root, "main"); // "main"-Objekt holen
	if (main_object) {
		cJSON *temp = cJSON_GetObjectItem(main_object, "temp"); // Temperatur
		if (cJSON_IsNumber(temp)) {
			data.temperature = temp->valuedouble;
			guiTemp = data.temperature;
		}
		cJSON *humidity = cJSON_GetObjectItem(main_object, "humidity"); // Luftfeuchtigkeit
		if (cJSON_IsNumber(humidity)) {
			data.humidity = humidity->valueint;
			guiHumi = data.humidity;
		}
		cJSON *pressure = cJSON_GetObjectItem(main_object, "pressure"); //Luftdruck
		if (cJSON_IsNumber(pressure)) {
			data.pressure = pressure->valueint;
			guiPres = data.pressure;
		}
		cJSON *name = cJSON_GetObjectItem(root, "name"); // Stadtname
		if (cJSON_IsString(name)) {
			strncpy(data.city_name, name->valuestring, sizeof(data.city_name) - 1);
			data.city_name[sizeof(data.city_name) - 1] = '\0';
			strncpy(guiCity, data.city_name, sizeof(guiCity) - 1); //kopieren der Name in globales Array guiCity
			guiCity[sizeof(guiCity) - 1] = '\0';
		}
	}
	cJSON_Delete(root);
	HAL_UARTEx_ReceiveToIdle_IT(&huart7, (uint8_t*)RxData, Rx_Data_size);
}

void extract_ssid(const char *response, char *ssidBuffer, size_t ssidBufferSize) {
    const char *start = strstr(response, "+CWJAP:\"");
    if (start != NULL) {
        start += strlen("+CWJAP:\""); // Überspringe "+CWJAP:\""
        const char *end = strchr(start, '\"'); // Suche nach dem abschließenden Anführungszeichen
        if (end != NULL) {
            size_t length = end - start; // Länge der SSID
            if (length < ssidBufferSize) {
                strncpy(ssidBuffer, start, length);
                ssidBuffer[length] = '\0'; // Null-terminieren
            } else {
                strncpy(ssidBuffer, "SSID_TOO_LONG", ssidBufferSize - 1);
                ssidBuffer[ssidBufferSize - 1] = '\0';
            }
        } else {
            strncpy(ssidBuffer, "SSID_NOT_FOUND", ssidBufferSize - 1);
            ssidBuffer[ssidBufferSize - 1] = '\0';
        }
    } else {
        strncpy(ssidBuffer, "SSID_NOT_FOUND", ssidBufferSize - 1);
        ssidBuffer[ssidBufferSize - 1] = '\0';
    }
}


void extract_all_ssids(const char *response, char guissidList[][33], size_t maxSSIDs, size_t ssidBufferSize) {
    size_t ssidCount = 0;
    const char *pos = response;

    while ((pos = strstr(pos, "+CWLAP:")) != NULL && ssidCount < maxSSIDs) {
        const char *start = strchr(pos, '\"'); // Finde erstes Anführungszeichen
        if (start != NULL) {
            start++; // Überspringe das Anführungszeichen
            const char *end = strchr(start, '\"'); // Finde das abschließende Anführungszeichen
            if (end != NULL) {
                size_t length = end - start; // Länge der SSID
                if (length < ssidBufferSize) {
                    strncpy(guissidList[ssidCount], start, length);
                    guissidList[ssidCount][length] = '\0'; // Null-terminieren
                } else {
                    strncpy(guissidList[ssidCount], "SSID_TOO_LONG", ssidBufferSize - 1);
                    guissidList[ssidCount][ssidBufferSize - 1] = '\0';
                }
                ssidCount++;
                pos = end; // Weiter suchen ab dem Ende der aktuellen SSID
            } else {
                break; // Keine gültige SSID gefunden, Schleife verlassen
            }
        } else {
            break; // Keine gültige SSID gefunden, Schleife verlassen
        }
    }
    // Optional: Signalisiere Ende der Liste
    if (ssidCount < maxSSIDs) {
        guissidList[ssidCount][0] = '\0'; // Leere Zeichenkette als Ende-Markierung
    }
}

void storeSSIDPassword(const char* ssid, const char* password) {
    // 1) Sichere Kopie in die globals
    strncpy(ssid_global, ssid, MAX_SSID_LEN-1);
    ssid_global[MAX_SSID_LEN-1] = '\0';
    strncpy(password_global, password, MAX_PASSWORD_LEN-1);
    password_global[MAX_PASSWORD_LEN-1] = '\0';

    // 2) Baue den AT-Befehl zusammen
    char AT_NewSSID[128] = "\0";  // Puffer groß genug wählen
    int n = snprintf(AT_NewSSID, sizeof(AT_NewSSID),
                     "AT+CWJAP=\"%s\",\"%s\"\r\n",
                     ssid_global,
                     password_global);

   if (n < 0 || n >= sizeof(AT_NewSSID)) {
        // Fehlerbehandlung: Puffer zu klein oder snprintf-Fehler
        return;
    }
    send_at_command("AT+CWQAP\r\n");
    HAL_Delay(500);
    send_at_command(AT_NewSSID);
}

void storeBuffer_City(const char*cityUTF8) {

	// Template mit Platzhalter für Stadt
	  const char *template =
	         "GET /data/2.5/weather?q=%s&appid=%s&lang=de&units=metric\r\n"
	         "Host: api.openweathermap.org\r\n"
	         "Connection: close\r\n\r\n";

     snprintf(AT_NEW_REQUEST_1,
              sizeof(AT_NEW_REQUEST_1),
              template,
              cityUTF8,
              api_key);

     strncpy(AT_REQUEST_1, AT_NEW_REQUEST_1, sizeof(AT_REQUEST_1) - 1);
     AT_REQUEST_1[sizeof(AT_REQUEST_1)-1] = '\0';  // Sicherheit Null-Terminator
}

/* USER CODE END 0 */

/**
  * @brief  The application entry point.
  * @retval int
  */
int main(void)
{

  /* USER CODE BEGIN 1 */
	strncpy(AT_REQUEST_1, default_request, sizeof(AT_REQUEST_1) - 1);
	AT_REQUEST_1[sizeof(AT_REQUEST_1)-1] = '\0';  // Sicherheit Null-Terminator

  /* USER CODE END 1 */

  /* MPU Configuration--------------------------------------------------------*/
  MPU_Config();

  /* Enable the CPU Cache */

  /* Enable I-Cache---------------------------------------------------------*/
  SCB_EnableICache();

  /* Enable D-Cache---------------------------------------------------------*/
  SCB_EnableDCache();

  /* MCU Configuration--------------------------------------------------------*/

  /* Update SystemCoreClock variable according to RCC registers values. */
  SystemCoreClockUpdate();

  /* Reset of all peripherals, Initializes the Flash interface and the Systick. */
  HAL_Init();

  /* USER CODE BEGIN Init */

  /* USER CODE END Init */

  /* USER CODE BEGIN SysInit */

  /* USER CODE END SysInit */

  /* Initialize all configured peripherals */
  MX_GPIO_Init();
  MX_HPDMA1_Init();
  MX_LTDC_Init();
  MX_CRC_Init();
  MX_DMA2D_Init();
  MX_JPEG_Init();
  MX_FLASH_Init();
  MX_I2C1_Init();
  MX_GPU2D_Init();
  MX_ICACHE_GPU2D_Init();
  MX_UART7_Init();
  MX_TIM7_Init();
  MX_TouchGFX_Init();
  /* Call PreOsInit function */
  MX_TouchGFX_PreOSInit();
  /* USER CODE BEGIN 2 */
  HAL_TIM_Base_Start_IT(&htim7);
  /* USER CODE END 2 */

  /* Init scheduler */
  osKernelInitialize();

  /* USER CODE BEGIN RTOS_MUTEX */
  /* add mutexes, ... */
  /* USER CODE END RTOS_MUTEX */

  /* USER CODE BEGIN RTOS_SEMAPHORES */
  /* add semaphores, ... */
  /* USER CODE END RTOS_SEMAPHORES */

  /* USER CODE BEGIN RTOS_TIMERS */
  /* start timers, add new ones, ... */
  /* USER CODE END RTOS_TIMERS */

  /* Create the queue(s) */
  /* creation of GuiQueue */
  GuiQueueHandle = osMessageQueueNew (16, sizeof(uint8_t), &GuiQueue_attributes);

  /* USER CODE BEGIN RTOS_QUEUES */
  /* add queues, ... */
  /* USER CODE END RTOS_QUEUES */

  /* Create the thread(s) */
  /* creation of defaultTask */
  defaultTaskHandle = osThreadNew(StartDefaultTask, NULL, &defaultTask_attributes);

  /* creation of TouchGFXTask */
  TouchGFXTaskHandle = osThreadNew(TouchGFX_Task, NULL, &TouchGFXTask_attributes);

  /* USER CODE BEGIN RTOS_THREADS */
  /* add threads, ... */
  /* USER CODE END RTOS_THREADS */

  /* USER CODE BEGIN RTOS_EVENTS */
  /* add events, ... */
  /* USER CODE END RTOS_EVENTS */

  /* Start scheduler */
  osKernelStart();

  /* We should never get here as control is now taken by the scheduler */

  /* Infinite loop */
  /* USER CODE BEGIN WHILE */

  while (1)
  {
    /* USER CODE END WHILE */

    /* USER CODE BEGIN 3 */
  }




  /* USER CODE END 3 */
}

/**
  * @brief CRC Initialization Function
  * @param None
  * @retval None
  */
static void MX_CRC_Init(void)
{

  /* USER CODE BEGIN CRC_Init 0 */

  /* USER CODE END CRC_Init 0 */

  /* USER CODE BEGIN CRC_Init 1 */

  /* USER CODE END CRC_Init 1 */
  hcrc.Instance = CRC;
  hcrc.Init.DefaultPolynomialUse = DEFAULT_POLYNOMIAL_ENABLE;
  hcrc.Init.DefaultInitValueUse = DEFAULT_INIT_VALUE_ENABLE;
  hcrc.Init.InputDataInversionMode = CRC_INPUTDATA_INVERSION_NONE;
  hcrc.Init.OutputDataInversionMode = CRC_OUTPUTDATA_INVERSION_DISABLE;
  hcrc.InputDataFormat = CRC_INPUTDATA_FORMAT_BYTES;
  if (HAL_CRC_Init(&hcrc) != HAL_OK)
  {
    Error_Handler();
  }
  /* USER CODE BEGIN CRC_Init 2 */

  /* USER CODE END CRC_Init 2 */

}

/**
  * @brief DMA2D Initialization Function
  * @param None
  * @retval None
  */
static void MX_DMA2D_Init(void)
{

  /* USER CODE BEGIN DMA2D_Init 0 */

  /* USER CODE END DMA2D_Init 0 */

  /* USER CODE BEGIN DMA2D_Init 1 */

  /* USER CODE END DMA2D_Init 1 */
  hdma2d.Instance = DMA2D;
  hdma2d.Init.Mode = DMA2D_R2M;
  hdma2d.Init.ColorMode = DMA2D_OUTPUT_RGB888;
  hdma2d.Init.OutputOffset = 0;
  if (HAL_DMA2D_Init(&hdma2d) != HAL_OK)
  {
    Error_Handler();
  }
  /* USER CODE BEGIN DMA2D_Init 2 */

  /* USER CODE END DMA2D_Init 2 */

}

/**
  * @brief FLASH Initialization Function
  * @param None
  * @retval None
  */
static void MX_FLASH_Init(void)
{

  /* USER CODE BEGIN FLASH_Init 0 */

  /* USER CODE END FLASH_Init 0 */

  FLASH_OBProgramInitTypeDef pOBInit = {0};

  /* USER CODE BEGIN FLASH_Init 1 */

  /* USER CODE END FLASH_Init 1 */
  HAL_FLASHEx_OBGetConfig(&pOBInit);
  if ((pOBInit.USERConfig1 & OB_IWDG_SW) != OB_IWDG_SW||
(pOBInit.USERConfig1 & OB_XSPI1_HSLV_ENABLE) != OB_XSPI1_HSLV_ENABLE||
(pOBInit.USERConfig1 & OB_XSPI2_HSLV_ENABLE) != OB_XSPI2_HSLV_ENABLE||
(pOBInit.USERConfig2 & OB_I2C_NI3C_I2C) != OB_I2C_NI3C_I2C)
  {
  if (HAL_FLASH_Unlock() != HAL_OK)
  {
    Error_Handler();
  }
  if (HAL_FLASH_OB_Unlock() != HAL_OK)
  {
    Error_Handler();
  }
  pOBInit.OptionType = OPTIONBYTE_USER;
  pOBInit.USERType = OB_USER_IWDG_SW|OB_USER_XSPI1_HSLV
                              |OB_USER_XSPI2_HSLV|OB_USER_I2C_NI3C;
  pOBInit.USERConfig1 = OB_IWDG_SW|OB_XSPI1_HSLV_ENABLE
                              |OB_XSPI2_HSLV_ENABLE;
  pOBInit.USERConfig2 = OB_I2C_NI3C_I2C;
  if (HAL_FLASHEx_OBProgram(&pOBInit) != HAL_OK)
  {
    Error_Handler();
  }
  if (HAL_FLASH_OB_Lock() != HAL_OK)
  {
    Error_Handler();
  }
  if (HAL_FLASH_Lock() != HAL_OK)
  {
    Error_Handler();
  }
  }
  /* USER CODE BEGIN FLASH_Init 2 */

  /* USER CODE END FLASH_Init 2 */

}

/**
  * @brief GPU2D Initialization Function
  * @param None
  * @retval None
  */
static void MX_GPU2D_Init(void)
{

  /* USER CODE BEGIN GPU2D_Init 0 */

  /* USER CODE END GPU2D_Init 0 */

  /* USER CODE BEGIN GPU2D_Init 1 */

  /* USER CODE END GPU2D_Init 1 */
  hgpu2d.Instance = GPU2D;
  if (HAL_GPU2D_Init(&hgpu2d) != HAL_OK)
  {
    Error_Handler();
  }
  /* USER CODE BEGIN GPU2D_Init 2 */

  /* USER CODE END GPU2D_Init 2 */

}

/**
  * @brief HPDMA1 Initialization Function
  * @param None
  * @retval None
  */
static void MX_HPDMA1_Init(void)
{

  /* USER CODE BEGIN HPDMA1_Init 0 */

  /* USER CODE END HPDMA1_Init 0 */

  /* Peripheral clock enable */
  __HAL_RCC_HPDMA1_CLK_ENABLE();

  /* HPDMA1 interrupt Init */
    HAL_NVIC_SetPriority(HPDMA1_Channel0_IRQn, 5, 0);
    HAL_NVIC_EnableIRQ(HPDMA1_Channel0_IRQn);
    HAL_NVIC_SetPriority(HPDMA1_Channel1_IRQn, 5, 0);
    HAL_NVIC_EnableIRQ(HPDMA1_Channel1_IRQn);

  /* USER CODE BEGIN HPDMA1_Init 1 */

  /* USER CODE END HPDMA1_Init 1 */
  /* USER CODE BEGIN HPDMA1_Init 2 */

  /* USER CODE END HPDMA1_Init 2 */

}

/**
  * @brief I2C1 Initialization Function
  * @param None
  * @retval None
  */
static void MX_I2C1_Init(void)
{

  /* USER CODE BEGIN I2C1_Init 0 */

  /* USER CODE END I2C1_Init 0 */

  /* USER CODE BEGIN I2C1_Init 1 */

  /* USER CODE END I2C1_Init 1 */
  hi2c1.Instance = I2C1;
  hi2c1.Init.Timing = 0x00E063FF;
  hi2c1.Init.OwnAddress1 = 0;
  hi2c1.Init.AddressingMode = I2C_ADDRESSINGMODE_7BIT;
  hi2c1.Init.DualAddressMode = I2C_DUALADDRESS_DISABLE;
  hi2c1.Init.OwnAddress2 = 0;
  hi2c1.Init.OwnAddress2Masks = I2C_OA2_NOMASK;
  hi2c1.Init.GeneralCallMode = I2C_GENERALCALL_DISABLE;
  hi2c1.Init.NoStretchMode = I2C_NOSTRETCH_DISABLE;
  if (HAL_I2C_Init(&hi2c1) != HAL_OK)
  {
    Error_Handler();
  }

  /** Configure Analogue filter
  */
  if (HAL_I2CEx_ConfigAnalogFilter(&hi2c1, I2C_ANALOGFILTER_ENABLE) != HAL_OK)
  {
    Error_Handler();
  }

  /** Configure Digital filter
  */
  if (HAL_I2CEx_ConfigDigitalFilter(&hi2c1, 0) != HAL_OK)
  {
    Error_Handler();
  }
  /* USER CODE BEGIN I2C1_Init 2 */

  /* USER CODE END I2C1_Init 2 */

}

/**
  * @brief ICACHE_GPU2D Initialization Function
  * @param None
  * @retval None
  */
static void MX_ICACHE_GPU2D_Init(void)
{

  /* USER CODE BEGIN ICACHE_GPU2D_Init 0 */

  /* USER CODE END ICACHE_GPU2D_Init 0 */

  /* USER CODE BEGIN ICACHE_GPU2D_Init 1 */

  /* USER CODE END ICACHE_GPU2D_Init 1 */

  /** Enable instruction cache (default 2-ways set associative cache)
  */
  if (HAL_ICACHE_Enable() != HAL_OK)
  {
    Error_Handler();
  }
  /* USER CODE BEGIN ICACHE_GPU2D_Init 2 */

  /* USER CODE END ICACHE_GPU2D_Init 2 */

}

/**
  * @brief JPEG Initialization Function
  * @param None
  * @retval None
  */
static void MX_JPEG_Init(void)
{

  /* USER CODE BEGIN JPEG_Init 0 */

  /* USER CODE END JPEG_Init 0 */

  /* USER CODE BEGIN JPEG_Init 1 */

  /* USER CODE END JPEG_Init 1 */
  hjpeg.Instance = JPEG;
  if (HAL_JPEG_Init(&hjpeg) != HAL_OK)
  {
    Error_Handler();
  }
  /* USER CODE BEGIN JPEG_Init 2 */

  /* USER CODE END JPEG_Init 2 */

}

/**
  * @brief LTDC Initialization Function
  * @param None
  * @retval None
  */
static void MX_LTDC_Init(void)
{

  /* USER CODE BEGIN LTDC_Init 0 */

  /* USER CODE END LTDC_Init 0 */

  LTDC_LayerCfgTypeDef pLayerCfg = {0};

  /* USER CODE BEGIN LTDC_Init 1 */

  /* USER CODE END LTDC_Init 1 */
  hltdc.Instance = LTDC;
  hltdc.Init.HSPolarity = LTDC_HSPOLARITY_AL;
  hltdc.Init.VSPolarity = LTDC_VSPOLARITY_AL;
  hltdc.Init.DEPolarity = LTDC_DEPOLARITY_AL;
  hltdc.Init.PCPolarity = LTDC_PCPOLARITY_IPC;
  hltdc.Init.HorizontalSync = 4;
  hltdc.Init.VerticalSync = 4;
  hltdc.Init.AccumulatedHBP = 12;
  hltdc.Init.AccumulatedVBP = 12;
  hltdc.Init.AccumulatedActiveW = 812;
  hltdc.Init.AccumulatedActiveH = 492;
  hltdc.Init.TotalWidth = 820;
  hltdc.Init.TotalHeigh = 506;
  hltdc.Init.Backcolor.Blue = 0;
  hltdc.Init.Backcolor.Green = 0;
  hltdc.Init.Backcolor.Red = 0;
  if (HAL_LTDC_Init(&hltdc) != HAL_OK)
  {
    Error_Handler();
  }
  pLayerCfg.WindowX0 = 0;
  pLayerCfg.WindowX1 = 800;
  pLayerCfg.WindowY0 = 0;
  pLayerCfg.WindowY1 = 480;
  pLayerCfg.PixelFormat = LTDC_PIXEL_FORMAT_RGB565;
  pLayerCfg.Alpha = 255;
  pLayerCfg.Alpha0 = 0;
  pLayerCfg.BlendingFactor1 = LTDC_BLENDING_FACTOR1_CA;
  pLayerCfg.BlendingFactor2 = LTDC_BLENDING_FACTOR2_CA;
  pLayerCfg.FBStartAdress = 0;
  pLayerCfg.ImageWidth = 800;
  pLayerCfg.ImageHeight = 480;
  pLayerCfg.Backcolor.Blue = 0;
  pLayerCfg.Backcolor.Green = 0;
  pLayerCfg.Backcolor.Red = 0;
  if (HAL_LTDC_ConfigLayer(&hltdc, &pLayerCfg, 0) != HAL_OK)
  {
    Error_Handler();
  }
  /* USER CODE BEGIN LTDC_Init 2 */

  /* USER CODE END LTDC_Init 2 */

}

/**
  * @brief TIM7 Initialization Function
  * @param None
  * @retval None
  */
static void MX_TIM7_Init(void)
{

  /* USER CODE BEGIN TIM7_Init 0 */

  /* USER CODE END TIM7_Init 0 */

  TIM_MasterConfigTypeDef sMasterConfig = {0};

  /* USER CODE BEGIN TIM7_Init 1 */

  /* USER CODE END TIM7_Init 1 */
  htim7.Instance = TIM7;
  htim7.Init.Prescaler = 65535;
  htim7.Init.CounterMode = TIM_COUNTERMODE_UP;
  htim7.Init.Period = 65535;
  htim7.Init.AutoReloadPreload = TIM_AUTORELOAD_PRELOAD_DISABLE;
  if (HAL_TIM_Base_Init(&htim7) != HAL_OK)
  {
    Error_Handler();
  }
  sMasterConfig.MasterOutputTrigger = TIM_TRGO_RESET;
  sMasterConfig.MasterSlaveMode = TIM_MASTERSLAVEMODE_DISABLE;
  if (HAL_TIMEx_MasterConfigSynchronization(&htim7, &sMasterConfig) != HAL_OK)
  {
    Error_Handler();
  }
  /* USER CODE BEGIN TIM7_Init 2 */

  /* USER CODE END TIM7_Init 2 */

}

/**
  * @brief UART7 Initialization Function
  * @param None
  * @retval None
  */
static void MX_UART7_Init(void)
{

  /* USER CODE BEGIN UART7_Init 0 */

  /* USER CODE END UART7_Init 0 */

  /* USER CODE BEGIN UART7_Init 1 */

  /* USER CODE END UART7_Init 1 */
  huart7.Instance = UART7;
  huart7.Init.BaudRate = 115200;
  huart7.Init.WordLength = UART_WORDLENGTH_8B;
  huart7.Init.StopBits = UART_STOPBITS_1;
  huart7.Init.Parity = UART_PARITY_NONE;
  huart7.Init.Mode = UART_MODE_TX_RX;
  huart7.Init.HwFlowCtl = UART_HWCONTROL_NONE;
  huart7.Init.OverSampling = UART_OVERSAMPLING_16;
  huart7.Init.OneBitSampling = UART_ONE_BIT_SAMPLE_DISABLE;
  huart7.Init.ClockPrescaler = UART_PRESCALER_DIV1;
  huart7.AdvancedInit.AdvFeatureInit = UART_ADVFEATURE_NO_INIT;
  if (HAL_UART_Init(&huart7) != HAL_OK)
  {
    Error_Handler();
  }
  if (HAL_UARTEx_SetTxFifoThreshold(&huart7, UART_TXFIFO_THRESHOLD_1_8) != HAL_OK)
  {
    Error_Handler();
  }
  if (HAL_UARTEx_SetRxFifoThreshold(&huart7, UART_RXFIFO_THRESHOLD_1_8) != HAL_OK)
  {
    Error_Handler();
  }
  if (HAL_UARTEx_DisableFifoMode(&huart7) != HAL_OK)
  {
    Error_Handler();
  }
  /* USER CODE BEGIN UART7_Init 2 */

  /* USER CODE END UART7_Init 2 */

}

/**
  * @brief GPIO Initialization Function
  * @param None
  * @retval None
  */
static void MX_GPIO_Init(void)
{
  GPIO_InitTypeDef GPIO_InitStruct = {0};
/* USER CODE BEGIN MX_GPIO_Init_1 */
/* USER CODE END MX_GPIO_Init_1 */

  /* GPIO Ports Clock Enable */
  __HAL_RCC_GPIOF_CLK_ENABLE();
  __HAL_RCC_GPIOM_CLK_ENABLE();
  __HAL_RCC_GPIOG_CLK_ENABLE();
  __HAL_RCC_GPIOB_CLK_ENABLE();
  __HAL_RCC_GPIOE_CLK_ENABLE();
  __HAL_RCC_GPIOD_CLK_ENABLE();
  __HAL_RCC_GPIOA_CLK_ENABLE();

  /*Configure GPIO pin Output Level */
  HAL_GPIO_WritePin(GPIOF, FRAME_RATE_Pin|RENDER_TIME_Pin|MCU_ACTIVE_Pin|VSYNC_FREQ_Pin, GPIO_PIN_RESET);

  /*Configure GPIO pin Output Level */
  HAL_GPIO_WritePin(LED_GPIO_Port, LED_Pin, GPIO_PIN_RESET);

  /*Configure GPIO pin Output Level */
  HAL_GPIO_WritePin(LCD_EN_GPIO_Port, LCD_EN_Pin, GPIO_PIN_SET);

  /*Configure GPIO pin Output Level */
  HAL_GPIO_WritePin(LCD_BL_CTRL_GPIO_Port, LCD_BL_CTRL_Pin, GPIO_PIN_SET);

  /*Configure GPIO pin Output Level */
  HAL_GPIO_WritePin(ESP8266_EN_GPIO_Port, ESP8266_EN_Pin, GPIO_PIN_SET);

  /*Configure GPIO pins : FRAME_RATE_Pin RENDER_TIME_Pin VSYNC_FREQ_Pin */
  GPIO_InitStruct.Pin = FRAME_RATE_Pin|RENDER_TIME_Pin|VSYNC_FREQ_Pin;
  GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
  GPIO_InitStruct.Pull = GPIO_NOPULL;
  GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_MEDIUM;
  HAL_GPIO_Init(GPIOF, &GPIO_InitStruct);

  /*Configure GPIO pin : MCU_ACTIVE_Pin */
  GPIO_InitStruct.Pin = MCU_ACTIVE_Pin;
  GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
  GPIO_InitStruct.Pull = GPIO_NOPULL;
  GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_LOW;
  HAL_GPIO_Init(MCU_ACTIVE_GPIO_Port, &GPIO_InitStruct);

  /*Configure GPIO pin : LED_Pin */
  GPIO_InitStruct.Pin = LED_Pin;
  GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
  GPIO_InitStruct.Pull = GPIO_NOPULL;
  GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_LOW;
  HAL_GPIO_Init(LED_GPIO_Port, &GPIO_InitStruct);

  /*Configure GPIO pin : PD0 */
  GPIO_InitStruct.Pin = GPIO_PIN_0;
  GPIO_InitStruct.Mode = GPIO_MODE_AF_PP;
  GPIO_InitStruct.Pull = GPIO_NOPULL;
  GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_LOW;
  GPIO_InitStruct.Alternate = GPIO_AF8_UART4;
  HAL_GPIO_Init(GPIOD, &GPIO_InitStruct);

  /*Configure GPIO pin : LCD_EN_Pin */
  GPIO_InitStruct.Pin = LCD_EN_Pin;
  GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
  GPIO_InitStruct.Pull = GPIO_NOPULL;
  GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_LOW;
  HAL_GPIO_Init(LCD_EN_GPIO_Port, &GPIO_InitStruct);

  /*Configure GPIO pin : TP_IRQ_Pin */
  GPIO_InitStruct.Pin = TP_IRQ_Pin;
  GPIO_InitStruct.Mode = GPIO_MODE_IT_FALLING;
  GPIO_InitStruct.Pull = GPIO_NOPULL;
  HAL_GPIO_Init(TP_IRQ_GPIO_Port, &GPIO_InitStruct);

  /*Configure GPIO pin : LCD_BL_CTRL_Pin */
  GPIO_InitStruct.Pin = LCD_BL_CTRL_Pin;
  GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
  GPIO_InitStruct.Pull = GPIO_NOPULL;
  GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_LOW;
  HAL_GPIO_Init(LCD_BL_CTRL_GPIO_Port, &GPIO_InitStruct);

  /*Configure GPIO pin : ESP8266_EN_Pin */
  GPIO_InitStruct.Pin = ESP8266_EN_Pin;
  GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
  GPIO_InitStruct.Pull = GPIO_PULLUP;
  GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_LOW;
  HAL_GPIO_Init(ESP8266_EN_GPIO_Port, &GPIO_InitStruct);

  /* EXTI interrupt init*/
  HAL_NVIC_SetPriority(TP_IRQ_EXTI_IRQn, 5, 0);
  HAL_NVIC_EnableIRQ(TP_IRQ_EXTI_IRQn);

/* USER CODE BEGIN MX_GPIO_Init_2 */
/* USER CODE END MX_GPIO_Init_2 */
}

/* USER CODE BEGIN 4 */
void send_at_command(char *command) {
	strcpy((char*)tx_buffer, command);
	HAL_UART_Transmit_IT(&huart7, tx_buffer, strlen(command));
}

void HAL_UART_TxCpltCallback(UART_HandleTypeDef *huart) {
	if (huart->Instance == UART7) {
		printf("Übertragung abgeschlossen\n");
		HAL_GPIO_TogglePin(GPIOM, GPIO_PIN_2);
	}
}

void myScanFunctionInC(void)
{
    // Hier implementierst du deinen Scan-Code (z. B. Aufruf eines WiFi-Treibers)
	if(scanSSIDs == 1){
		printf("Scanning for SSIDs...\n");
	  send_at_command(AT_REQUEST_nearby_SSID);
	  HAL_Delay(5000); // 5 Sekunden warten
	}
}

/* USER CODE END 4 */

/* USER CODE BEGIN Header_StartDefaultTask */
/**
  * @brief  Function implementing the defaultTask thread.
  * @param  argument: Not used
  * @retval None
  */
/* USER CODE END Header_StartDefaultTask */
void StartDefaultTask(void *argument)
{
  /* USER CODE BEGIN 5 */
	// Berechne die Länge des AT_REQUEST-Strings
	int request_length_0 = strlen(AT_REQUEST_0);
	int request_length_1 = strlen(AT_REQUEST_1);
	sprintf(AT_CIPSEND_0, "AT+CIPSEND=%d\r\n", (int)request_length_0);
	sprintf(AT_CIPSEND_1, "AT+CIPSEND=%d\r\n", (int)request_length_1);
	HAL_UARTEx_ReceiveToIdle_IT(&huart7, (uint8_t*)RxData, Rx_Data_size);
	osDelay(5000);
	HAL_GPIO_WritePin(GPIOF, GPIO_PIN_13, GPIO_PIN_SET);//Set ESP8266 enable Pin high
	send_at_command(AT_OPEN_CONNECTION);

	/* Infinite loop */
	for(;;)
	{
		osDelay(1);
	}
  /* USER CODE END 5 */
}

 /* MPU Configuration */

static void MPU_Config(void)
{

	MPU_Region_InitTypeDef MPU_InitStruct = {0};

  /* Disables the MPU */
  HAL_MPU_Disable();

  /** Initializes and configures the Region and the memory to be protected
  */
  MPU_InitStruct.Enable = MPU_REGION_ENABLE;
  MPU_InitStruct.Number = MPU_REGION_NUMBER0;
  MPU_InitStruct.BaseAddress = 0x0;
  MPU_InitStruct.Size = MPU_REGION_SIZE_4GB;
  MPU_InitStruct.SubRegionDisable = 0x87;
  MPU_InitStruct.TypeExtField = MPU_TEX_LEVEL0;
  MPU_InitStruct.AccessPermission = MPU_REGION_FULL_ACCESS;
  MPU_InitStruct.DisableExec = MPU_INSTRUCTION_ACCESS_DISABLE;
  MPU_InitStruct.IsShareable = MPU_ACCESS_SHAREABLE;
  MPU_InitStruct.IsCacheable = MPU_ACCESS_NOT_CACHEABLE;
  MPU_InitStruct.IsBufferable = MPU_ACCESS_NOT_BUFFERABLE;

  HAL_MPU_ConfigRegion(&MPU_InitStruct);

  /** Initializes and configures the Region and the memory to be protected
  */
  MPU_InitStruct.Number = MPU_REGION_NUMBER1;
  MPU_InitStruct.BaseAddress = 0x70000000;
  MPU_InitStruct.Size = MPU_REGION_SIZE_128MB;
  MPU_InitStruct.SubRegionDisable = 0x0;
  MPU_InitStruct.TypeExtField = MPU_TEX_LEVEL1;
  MPU_InitStruct.IsShareable = MPU_ACCESS_NOT_SHAREABLE;
  MPU_InitStruct.IsCacheable = MPU_ACCESS_CACHEABLE;
  MPU_InitStruct.IsBufferable = MPU_ACCESS_BUFFERABLE;

  HAL_MPU_ConfigRegion(&MPU_InitStruct);

  /** Initializes and configures the Region and the memory to be protected
  */
  MPU_InitStruct.Number = MPU_REGION_NUMBER2;
  MPU_InitStruct.Size = MPU_REGION_SIZE_2MB;
  MPU_InitStruct.DisableExec = MPU_INSTRUCTION_ACCESS_ENABLE;

  HAL_MPU_ConfigRegion(&MPU_InitStruct);

  /** Initializes and configures the Region and the memory to be protected
  */
  MPU_InitStruct.Number = MPU_REGION_NUMBER3;
  MPU_InitStruct.BaseAddress = 0x90000000;
  MPU_InitStruct.Size = MPU_REGION_SIZE_32MB;
  MPU_InitStruct.DisableExec = MPU_INSTRUCTION_ACCESS_DISABLE;
  MPU_InitStruct.IsCacheable = MPU_ACCESS_NOT_CACHEABLE;
  MPU_InitStruct.IsBufferable = MPU_ACCESS_NOT_BUFFERABLE;

  HAL_MPU_ConfigRegion(&MPU_InitStruct);

  /** Initializes and configures the Region and the memory to be protected
  */
  MPU_InitStruct.Number = MPU_REGION_NUMBER4;
  MPU_InitStruct.BaseAddress = 0x20000000;
  MPU_InitStruct.Size = MPU_REGION_SIZE_64KB;

  HAL_MPU_ConfigRegion(&MPU_InitStruct);

  /** Initializes and configures the Region and the memory to be protected
  */
  MPU_InitStruct.Number = MPU_REGION_NUMBER5;
  MPU_InitStruct.BaseAddress = 0x24000000;
  MPU_InitStruct.Size = MPU_REGION_SIZE_512KB;
  MPU_InitStruct.IsShareable = MPU_ACCESS_SHAREABLE;
  MPU_InitStruct.IsCacheable = MPU_ACCESS_CACHEABLE;
  MPU_InitStruct.IsBufferable = MPU_ACCESS_BUFFERABLE;

  HAL_MPU_ConfigRegion(&MPU_InitStruct);

  /** Initializes and configures the Region and the memory to be protected
  */
  MPU_InitStruct.Number = MPU_REGION_NUMBER6;
  MPU_InitStruct.BaseAddress = 0x2406e000;
  MPU_InitStruct.Size = MPU_REGION_SIZE_16KB;
  MPU_InitStruct.TypeExtField = MPU_TEX_LEVEL0;
  MPU_InitStruct.IsCacheable = MPU_ACCESS_NOT_CACHEABLE;

  HAL_MPU_ConfigRegion(&MPU_InitStruct);
  /* Enables the MPU */
  HAL_MPU_Enable(MPU_PRIVILEGED_DEFAULT);

}

/**
  * @brief  Period elapsed callback in non blocking mode
  * @note   This function is called  when TIM6 interrupt took place, inside
  * HAL_TIM_IRQHandler(). It makes a direct call to HAL_IncTick() to increment
  * a global variable "uwTick" used as application time base.
  * @param  htim TIM handle
  * @retval None
  */
void HAL_TIM_PeriodElapsedCallback(TIM_HandleTypeDef *htim){
  /* USER CODE BEGIN Callback 0 */

  /* USER CODE END Callback 0 */
  if (htim->Instance == TIM6) {
    HAL_IncTick();
  }

  /* USER CODE BEGIN Callback 1 */
if (htim->Instance == TIM7){
	HAL_GPIO_TogglePin(GPIOM, GPIO_PIN_2);
	send_at_command(AT_OPEN_CONNECTION);
}
  /* USER CODE END Callback 1 */
}

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
