#include "perifericos.h"
#include "pico/stdlib.h"
//#include "hardware/timer.h"
//#include "hardware/clocks.h"
#include "hardware/i2c.h"
#include "hardware/pio.h"
#include "ws2812.pio.h"
#include "hardware/uart.h"


ssd1306_t ssd_display;  // Definição da variável global do display

// Variáveis PIO
//PIO pio = pio0;
//int sm = 0;
//uint offset;

// Função para inicializar um LED específico
void perifericos_led_init(uint led_pin) {
    gpio_init(led_pin);
    gpio_set_dir(led_pin, GPIO_OUT);
    gpio_put(led_pin, false); // Desliga o LED por padrão
}


// Função para inicializar todos os LEDs (verifica o parâmetro)
void perifericos_led_init_all(void) {
    perifericos_led_init(LED_PIN_RED);   // Inicializa o LED vermelho
    perifericos_led_init(LED_PIN_GREEN); // Inicializa o LED verde
    perifericos_led_init(LED_PIN_BLUE);  // Inicializa o LED azul
}


// Função para inicializar um botão específico
void perifericos_botao_init(uint button_pin) {
    gpio_init(button_pin);
    gpio_set_dir(button_pin, GPIO_IN);
    gpio_pull_up(button_pin);  // Habilita o pull-up interno
}


// Função para inicializar todos os botões (verifica o parâmetro)
void perifericos_botao_init_all(void) {
    perifericos_botao_init(BUTTON_PIN_A); // Inicializa o Botão A
    perifericos_botao_init(BUTTON_PIN_B); // Inicializa o Botão B
    perifericos_botao_init(BUTTON_PIN_C); // Inicializa o Botão C
}


// Função para inicializar o buzzer
void perifericos_buzzer_init(uint buzzer_pin) {
    gpio_init(buzzer_pin);
    gpio_set_dir(buzzer_pin, GPIO_OUT);
}


// Função para inicializar o display I2C
void perifericos_display_init(void) {
    // Inicialização I2C
    i2c_init(I2C_PORT, 400 * 1000);  // Configura I2C a 400kHz

    gpio_set_function(I2C_SDA, GPIO_FUNC_I2C); // Configura o pino SDA para I2C
    gpio_set_function(I2C_SCL, GPIO_FUNC_I2C); // Configura o pino SCL para I2C
    gpio_pull_up(I2C_SDA);  // Habilita pull-up no SDA
    gpio_pull_up(I2C_SCL);  // Habilita pull-up no SCL

    ssd1306_init(&ssd_display, WIDTH, HEIGHT, false, DISP_ADDRESS, I2C_PORT);  // Inicializa o display
    ssd1306_config(&ssd_display);  // Configura o display
    ssd1306_send_data(&ssd_display);  // Envia os dados de configuração


    // Limpa o display (inicializa com todos os pixels apagados)
    ssd1306_fill(&ssd_display, false);
    ssd1306_send_data(&ssd_display);

}


// Função para inicializar o WS2812 (LED RGB ou similar) - Em construção
//void perifericos_ws2812_init(void) {
//    offset = pio_add_program(pio, &ws2812_program);
//    ws2812_program_init(pio, sm, offset, WS2812_PIN, 800000, false);  // WS2812 sem suporte a RGBW (false)
                                                                      // Inicializa o WS2812 no pino 7
//}


// Função para controlar o beep do buzzer
void perifericos_buzzer_beep(uint8_t note, uint32_t duration) {
    // Código para emitir um beep no buzzer
    // Dependendo da nota, você pode configurar um temporizador ou PWM para gerar o som.
}


void perifericos_uart_init(void) {
    // Inicializando a UART com a instância e a taxa de transmissão (baudrate)
    uart_init(UART_ID, BAUD_RATE);
    
    // Configurando os pinos TX e RX para a função UART
    gpio_set_function(UART_TX, GPIO_FUNC_UART);
    gpio_set_function(UART_RX, GPIO_FUNC_UART);
}

// Função para inicializar todos os periféricos
void perifericos_init_all(void) {
    // Inicializa os LEDs
    perifericos_led_init_all();
    
    // Inicializa os botões
    perifericos_botao_init_all();
    
    // Inicializa o buzzer (assumindo um pino, como um exemplo)
    // perifericos_buzzer_init(BUZZER_PIN); // Substitua BUZZER_PIN pelo pino correspondente
    
    // Inicializa o display I2C
    perifericos_display_init();
    
    // Inicializa o WS2812
    // perifericos_ws2812_init();

    // Inicializa o UART
    perifericos_uart_init();
}
