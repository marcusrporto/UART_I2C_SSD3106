#ifndef PERIFERICOS_H
#define PERIFERICOS_H
#include "inc/ssd1306.h"

// Definições dos pinos
#define LED_PIN_GREEN 11
#define LED_PIN_BLUE 12
#define LED_PIN_RED 13
#define BUTTON_PIN_A 5
#define BUTTON_PIN_B 6
#define BUTTON_PIN_C 22
#define BUZZER_PIN 21
#define BUZZER_PIN_B 10
#define WS2812_PIN 7
#define I2C_PORT i2c1
#define I2C_SDA 14
#define I2C_SCL 15
#define DISP_ADDRESS 0x3C
#define UART_ID uart0
#define UART_TX 0
#define UART_RX 1
#define BAUD_RATE 115200

extern ssd1306_t ssd_display;  // Variável global para o display

// Funções de Inicialização
void perifericos_init_all(void);      // Inicializa todos os priféricos da placa Bit Dog Lab (Em construção)
void perifericos_led_init(uint led_pin);          // Inicializa um LED específico
void perifericos_led_init_all(void);              // Inicializa todos os LEDs
void perifericos_botao_init(uint button_pin);     // Inicializa um botão específico
void perifericos_botao_init_all(void);            // Inicializa todos os botões
void perifericos_buzzer_init(uint buzzer_pin);    // Inicializa um buzzer específico
void perifericos_display_init(void);              // Inicializa o display I2C
void perifericos_ws2812_init(void);               // Inicializa o WS2812
void perifericos_uart_init(void);


// Funções para Interação
void perifericos_buzzer_beep(uint8_t note, uint32_t duration);  
//void display_number(int numero);                    


#endif