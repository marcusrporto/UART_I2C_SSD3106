#include <stdio.h>
#include "pico/stdlib.h"
#include "inc/perifericos.h"
#include "inc/display.h"
#include "pico/bootrom.h"


int numero = 0;                                    // Esta variável será alterada nas interrupções
static volatile uint32_t last_time = 0;            // Armazena o tempo do último evento (em microssegundos)
static volatile bool led_g_on = false;             // Esta variável (controle) será alterada nas interrupções 
static volatile bool led_b_on = false;             // Esta variável (controle) será alterada nas interrupções

// Prototipo da função de interrupção
static void gpio_irq_handler(uint gpio, uint32_t events);

int main()
{
    
    char caractere;
    
    stdio_init_all();
    
    perifericos_init_all();            // Inicializa todos as GPIO com funções entrada/saída, I2C, PWM, etc. Baseado no Hardware BitDogLab

    pio_init_ws2812(WS2812_PIN);       // Inicializa a GPIO utilizada com PIO para controle da matriz WS2812. 

    // Configuração da interrupção LED Green
    gpio_set_irq_enabled_with_callback(BUTTON_PIN_A, GPIO_IRQ_EDGE_FALL, true, &gpio_irq_handler);
    // Configuração da interrupção Led Blue
    gpio_set_irq_enabled_with_callback(BUTTON_PIN_B, GPIO_IRQ_EDGE_FALL, true, &gpio_irq_handler);
    // Configuração da interrupção Boot Sel
    gpio_set_irq_enabled_with_callback(BUTTON_PIN_C, GPIO_IRQ_EDGE_FALL, true, &gpio_irq_handler);

  while (true) {

    ssd1306_draw_string(&ssd_display, "EMBARCATECH", 8, 5); // Desenha uma string
    ssd1306_send_data(&ssd_display); // Atualiza o display
    char buffer[20]; 
    if(stdio_usb_connected()) {
        printf("Exibe o caractere no display\n");
        puts("");
        printf("Digite um caracter: ");
        caractere = getchar();
  
    // Verifica se o caractere digitado está entre '0' e '9'
    if (caractere >= '0' && caractere <= '9') {
       
    numero = caractere - '0';  // Converte o caractere para um número inteiro
    display_number(numero);    // Chama a função com o número digitado
    printf("Você pressionou: %d\n", numero);
    snprintf(buffer, sizeof(buffer), "CARACTERE: %c", caractere);
    ssd1306_draw_string(&ssd_display, buffer, 8, 50); // Desenha uma string
    ssd1306_send_data(&ssd_display); // Atualiza o display
    
    } else { 
        printf("Você pressionou: %c\n", caractere);
        //sleep_ms(1000);
        snprintf(buffer, sizeof(buffer), "CARACTERE: %c", caractere);
        ssd1306_draw_string(&ssd_display, buffer, 8, 50); // Desenha uma string
        ssd1306_send_data(&ssd_display); // Atualiza o display
    }
     
    }
    sleep_ms(200);
    }

}
// Função de interrupção para os botões A e B com debouncing
void gpio_irq_handler(uint gpio, uint32_t events) {
    // Obtém o tempo atual em microssegundos
    uint32_t current_time = to_us_since_boot(get_absolute_time());
        
    // Verifica se passou tempo suficiente desde o último evento (debouncing de 300ms)
    if (current_time - last_time > 200000) { // 200ms
        last_time = current_time;  // Atualiza o tempo do último evento
        
        // Verifica qual botão foi pressionado e realiza a ação apropriada
        if (gpio == BUTTON_PIN_A) {
            ssd1306_draw_string(&ssd_display, "             ", 8, 20);
            ssd1306_send_data(&ssd_display);
            // Verifica o estado do LED e inverte
            led_g_on = !led_g_on;
            gpio_put(LED_PIN_GREEN,led_g_on);
            if(led_g_on){
                ssd1306_draw_string(&ssd_display, "LED GREEN ON", 8, 20); // Desenha uma string
                puts("\nLED GREEN ON.");
            } else {
                ssd1306_draw_string(&ssd_display, "LED GREEN OFF", 8, 20); // Desenha uma string 
                puts("\nLED GREEN OFF.");
               
            }
        ssd1306_send_data(&ssd_display);                                                            
       
        } else if (gpio == BUTTON_PIN_B) {
            ssd1306_draw_string(&ssd_display, "             ", 8, 35);
            ssd1306_send_data(&ssd_display);
            // Verifica o estado do LED e inverte
            led_b_on = !led_b_on;
            gpio_put(LED_PIN_BLUE,led_b_on);
            if(led_b_on){
                ssd1306_draw_string(&ssd_display, "LED BLUE ON", 8, 35); // Desenha uma string
                puts("\nLED BLUE ON.");
            } else {
                ssd1306_draw_string(&ssd_display, "LED BLUE OFF", 8, 35); // Desenha uma string
              puts("\nLED BLUE OFF.");
            }
        ssd1306_send_data(&ssd_display);
              
        } else if (gpio == BUTTON_PIN_C) {
         printf("Interrupção ocorreu no pino %d, no evento %d\n", gpio, events);
         printf("HABILITANDO O MODO GRAVAÇÃO");
         clear_led_buffer(); // Limpa Matriz LEDS
         ssd1306_fill(&ssd_display, false); //Limpa Display
         ssd1306_send_data(&ssd_display); // Atualiza o display
	     reset_usb_boot(0,0); //habilita o modo de gravação do microcontrolador
        }   
    }
}
