#include "pico/stdlib.h"
#include <stdio.h>
#include <stdlib.h>
#include "hardware/pwm.h"
#include "hardware/timer.h"
#include <math.h>
#include "hardware/pio.h"
#include "hardware/clocks.h"
#include "hardware/adc.h"
#include "pico/bootrom.h"


//mapa de teclas
char mapa_TECLAS[4][4]={
  '1','2','3','A',
  '4','5','6','B',
  '7','8','9','C',
  '*','0','#','D'
};

// Definindo os pinos para linhas e colunas
const uint linhas[] = {8, 7, 6, 5};   // Pinos das linhas (GP5, GP6, GP7, GP8)
const uint colunas[] = {4, 3, 2, 1}; // Pinos das colunas (GP1, GP2, GP3, GP4)

// Protótipos das funções chamadas por cada tecla
void func_0(void);
void func_1(void);
void func_2(void);
void func_3(void);
void func_4(void);
void func_5(void);
void func_6(void);
void func_7(void);
void func_8(void);
void func_9(void);
void func_A(void);
void func_B(void);
void func_C(void);
void func_D(void);
void func_reboot(void);
void func_hash(void);
void aciona_buzzer(void);

// Configuração do pino do buzzer
#define BUZZER_PIN 28

// Frequência do buzzer em Hz
#define BUZZER_FREQUENCY 2000

// Função para inicializar o PWM no pino do buzzer
void init_buzzer(uint pin) {
    // Configurar o pino como saída de PWM
    gpio_set_function(pin, GPIO_FUNC_PWM);

    // Obter o slice do PWM associado ao pino
    uint slice_num = pwm_gpio_to_slice_num(pin);

    // Configurar o PWM com frequência desejada
    pwm_config config = pwm_get_default_config();
    pwm_config_set_clkdiv(&config, clock_get_hz(clk_sys) / (BUZZER_FREQUENCY * 4096)); // Divisor de clock
    pwm_init(slice_num, &config, true);


    // Iniciar o PWM no nível baixo
    pwm_set_gpio_level(pin, 0);
}

// Inicializando os GPIOs do teclado 
void inicializa_teclado() {
    // Configurando as linhas como saída
    for (int i = 0; i < 4; i++) {
        gpio_init(linhas[i]);
        gpio_set_dir(linhas[i], GPIO_OUT);
        gpio_put(linhas[i], 1); // Mantendo em nível alto
    }

    // Configurando as colunas como entrada com pull-up
    for (int i = 0; i < 4; i++) {
        gpio_init(colunas[i]);
        gpio_set_dir(colunas[i], GPIO_IN);
        gpio_pull_up(colunas[i]);
    }
}

//Lendo a tecla pressionada no teclado 
char ler_tecla() {
    for (int i = 0; i < 4; i++) {
        //Colocando a linha atual em nível baixo
        gpio_put(linhas[i], 0);

        //Verificando se alguma coluna está em nível baixo
        for (int j = 0; j < 4; j++) {
            if (gpio_get(colunas[j]) == 0) { //Coluna em nível baixo
                sleep_ms(20); //intervalo simples
                if (gpio_get(colunas[j]) == 0) {
                    //Restaurandi a linha para nível alto
                    gpio_put(linhas[i], 1);
                    return mapa_TECLAS[i][j];
                }
            }
        }

        //Restaurando a linha para nível alto
        gpio_put(linhas[i], 1);
    }
    return '\0'; //Sem teclas pressionadas
}

//main
int main(){
  //inicializações
  stdio_init_all();
  init_buzzer(BUZZER_PIN);
  inicializa_teclado();
  while(true){
    //lendo a tecla
    char tecla = ler_tecla();
    char last_tecla;
    char escolha_switch;

    if (tecla != last_tecla) {
        last_tecla = tecla;
        escolha_switch = tecla;
    }else{
      sleep_ms(50);
      escolha_switch = 'N';
    }
    //se for 8,chama a função que liga todos os LEDs
    switch (escolha_switch) {
        case '0': func_0(); break;
        case '1': func_1(); break;
        case '2': func_2(); break;
        case '3': func_3(); break;
        case '4': func_4(); break;
        case '5': func_5(); break;
        case '6': func_6(); break;
        case '7': func_7(); break;
        case '8': func_8(); break;
        case '9': func_9(); break;
        case 'A': func_A(); break;
        case 'B': func_B(); break;
        case 'C': func_C(); break;
        case 'D': func_D(); break;
        case '*': func_reboot(); break;
        case '#': func_hash; break;
        default: break; // Nenhuma tecla válida
    }
  }
return 0;
}

void func_0(void){
    aciona_buzzer();
}

void func_1(void){
    
}

void func_2(void){
    
}

void func_3(void){
    
}

void func_4(void){
    
}

void func_5(void){
    
}

void func_6(void){
    
}

void func_7(void){
    
}

void func_8(void){
    
}

void func_9(void){
    
}

void func_A(void){
    
}

void func_B(void){
    
}

void func_C(void){

}

void func_D(void){
    
}

void func_reboot(void){
    printf("Dando reboot...\n");
    sleep_ms(1000);
    reset_usb_boot(0,0);
}

void func_hash(void){
    
}

//Aciona o buzzer por meio segundo
void aciona_buzzer(void) {
    // Obter o slice do PWM associado ao pino
    uint slice_num = pwm_gpio_to_slice_num(BUZZER_PIN);

    // Ativar o PWM com duty cycle de 50%
    pwm_set_gpio_level(BUZZER_PIN, 2048); // 50% de 4096

    // Escrever "beep" no terminal
    printf("Buzz\n");

    // Temporização para duração do som
    sleep_ms(500);

    // Desativar o PWM (duty cycle 0)
    pwm_set_gpio_level(BUZZER_PIN, 0);
}
