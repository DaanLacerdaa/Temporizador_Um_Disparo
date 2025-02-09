#include <stdio.h>
#include "pico/stdlib.h"
#include "hardware/gpio.h"
#include "hardware/timer.h"

// Definição dos pinos (BitDogLab)
#define LED_VERDE 11    // GPIO11 (Verde)
#define LED_AZUL 12     // GPIO12 (Azul)
#define LED_VERMELHO 13 // GPIO13 (Vermelho)
#define BOTAO_A 5       // GPIO5 (Botão A)

// Estados do sistema
typedef enum {
    ESTADO_OFF,     // Todos os LEDs desligados
    ESTADO_TRES,    // Três LEDs ligados
    ESTADO_DOIS,    // Dois LEDs ligados
    ESTADO_UM       // Um LED ligado
} EstadoSistema;

volatile EstadoSistema estado_atual = ESTADO_OFF;
volatile bool sequencia_ativa = false;
volatile absolute_time_t ultimo_clique = 0;

// Função para desligar todos os LEDs
void desligar_leds() {
    gpio_put(LED_VERDE, 0);
    gpio_put(LED_AZUL, 0);
    gpio_put(LED_VERMELHO, 0);
}

// Função para inicializar LEDs
void inicializar_leds() {
    int leds[] = {LED_VERDE, LED_AZUL, LED_VERMELHO};
    for (int i = 0; i < 3; i++) {
        gpio_init(leds[i]);
        gpio_set_dir(leds[i], GPIO_OUT);
        gpio_put(leds[i], 0);  // Garante que inicie apagado
    }
}

// Callback do temporizador para mudança de estado
int64_t proximo_estado(alarm_id_t id, void *user_data) {
    switch (estado_atual) {
        case ESTADO_TRES:
            gpio_put(LED_AZUL, 0);
            estado_atual = ESTADO_DOIS;
            add_alarm_in_ms(3000, proximo_estado, NULL, false);
            break;
        case ESTADO_DOIS:
            gpio_put(LED_VERMELHO, 0);
            estado_atual = ESTADO_UM;
            add_alarm_in_ms(3000, proximo_estado, NULL, false);
            break;
        case ESTADO_UM:
            desligar_leds();
            estado_atual = ESTADO_OFF;
            sequencia_ativa = false;
            break;
        default:
            break;
    }
    return 0;
}

// Handler de interrupção do botão (com debounce)
void botao_handler(uint gpio, uint32_t events) {
    if ((gpio == BOTAO_A) && (to_ms_since_boot(get_absolute_time()) - to_ms_since_boot(ultimo_clique) > 50)) {
        ultimo_clique = get_absolute_time();

        // Desativa apenas a interrupção do botão
        gpio_set_irq_enabled(BOTAO_A, GPIO_IRQ_EDGE_FALL, false);

        if (!sequencia_ativa && estado_atual == ESTADO_OFF) {
            sequencia_ativa = true;
            estado_atual = ESTADO_TRES;

            gpio_put(LED_VERDE, 1);
            gpio_put(LED_AZUL, 1);
            gpio_put(LED_VERMELHO, 1);

            add_alarm_in_ms(3000, proximo_estado, NULL, false);
            printf("Sequência iniciada!\n");
        }

        // Reativa a interrupção do botão
        gpio_set_irq_enabled(BOTAO_A, GPIO_IRQ_EDGE_FALL, true);
    }
}

int main() {
    stdio_init_all();

    // Configuração dos LEDs
    inicializar_leds();

    // Configuração do botão com pull-up
    gpio_init(BOTAO_A);
    gpio_set_dir(BOTAO_A, GPIO_IN);
    gpio_pull_up(BOTAO_A);
    gpio_set_irq_enabled_with_callback(BOTAO_A, GPIO_IRQ_EDGE_FALL, true, &botao_handler);

    printf("Sistema pronto. Pressione o botão A para iniciar.\n");

    while (true) {
        // Mensagem de heartbeat a cada 1 segundo
        printf("Estado atual: %s\n", 
            (estado_atual == ESTADO_OFF) ? "OFF" :
            (estado_atual == ESTADO_TRES) ? "3 LEDS" :
            (estado_atual == ESTADO_DOIS) ? "2 LEDS" : "1 LED");
        sleep_ms(1000);
        tight_loop_contents();
    }
}
