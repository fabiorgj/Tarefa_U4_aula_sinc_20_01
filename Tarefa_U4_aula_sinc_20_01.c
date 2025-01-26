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

// Biblioteca gerada pelo arquivo .pio durante compilação.
#include "ws2818b.pio.h"

//////////////////////////////// ÁREA PARA DEFINIÇÃO DAS ANIMAÇÕES ///////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

// Definição da quantidade de frames das animações
//  É necessário definir a quantidade de frames de cada animação.

#define fps 5

#define repeticoes 3

#define frames_animex_1 12
#define frames_animex_2 5
#define frames_animex_3 0
#define frames_animex_4 5
#define frames_animex_5 5
#define frames_animex_6 6

int frames_animex;

// Definição das animações

int animex_1[frames_animex_1][5][5][3] = {
    /////////////////////////SUBSTITUIR TODOS OS SPRITES CONVERTIDOS A PARTIR DAQUI
{
    {{0, 69, 255}, {0, 69, 255}, {0, 69, 255}, {0, 69, 255}, {0, 69, 255}},
    {{0, 69, 255}, {0, 0, 0}, {0, 0, 0}, {0, 0, 0}, {0, 69, 255}},
    {{0, 69, 255}, {0, 0, 0}, {0, 0, 0}, {0, 0, 0}, {0, 69, 255}},
    {{0, 69, 255}, {0, 0, 0}, {0, 0, 0}, {0, 0, 0}, {0, 69, 255}},
    {{0, 69, 255}, {0, 69, 255}, {0, 69, 255}, {0, 69, 255}, {0, 69, 255}} 
},

{
    {{0, 0, 0}, {0, 0, 0}, {0, 0, 0}, {0, 0, 0}, {0, 0, 0}},
    {{0, 0, 0}, {0, 69, 255}, {0, 69, 255}, {0, 69, 255}, {0, 0, 0}},
    {{0, 0, 0}, {0, 69, 255}, {0, 0, 0}, {0, 69, 255}, {0, 0, 0}},
    {{0, 0, 0}, {0, 69, 255}, {0, 69, 255}, {0, 69, 255}, {0, 0, 0}},
    {{0, 0, 0}, {0, 0, 0}, {0, 0, 0}, {0, 0, 0}, {0, 0, 0}}
},

{
    {{0, 0, 0}, {0, 0, 0}, {0, 0, 0}, {0, 0, 0}, {0, 0, 0}},
    {{0, 0, 0}, {0, 0, 0}, {0, 0, 0}, {0, 0, 0}, {0, 0, 0}},
    {{0, 0, 0}, {0, 0, 0}, {0, 69, 255}, {0, 0, 0}, {0, 0, 0}},
    {{0, 0, 0}, {0, 0, 0}, {0, 0, 0}, {0, 0, 0}, {0, 0, 0}},
    {{0, 0, 0}, {0, 0, 0}, {0, 0, 0}, {0, 0, 0}, {0, 0, 0}}
},

{
    {{0, 0, 0}, {0, 0, 0}, {0, 0, 0}, {0, 0, 0}, {0, 0, 0}},
    {{0, 0, 0}, {0, 0, 0}, {0, 0, 0}, {0, 0, 0}, {0, 0, 0}},
    {{0, 0, 0}, {0, 0, 0}, {247, 0, 0}, {0, 0, 0}, {0, 0, 0}},
    {{0, 0, 0}, {0, 0, 0}, {0, 0, 0}, {0, 0, 0}, {0, 0, 0}},
    {{0, 0, 0}, {0, 0, 0}, {0, 0, 0}, {0, 0, 0}, {0, 0, 0}}
},

{
    {{0, 0, 0}, {0, 0, 0}, {0, 0, 0}, {0, 0, 0}, {0, 0, 0}},
    {{0, 0, 0}, {247, 0, 0}, {247, 0, 0}, {247, 0, 0}, {0, 0, 0}},
    {{0, 0, 0}, {247, 0, 0}, {0, 0, 0}, {247, 0, 0}, {0, 0, 0}},
    {{0, 0, 0}, {247, 0, 0}, {247, 0, 0}, {247, 0, 0}, {0, 0, 0}},
    {{0, 0, 0}, {0, 0, 0}, {0, 0, 0}, {0, 0, 0}, {0, 0, 0}}
},

{
    {{247, 0, 0}, {247, 0, 0}, {247, 0, 0}, {247, 0, 0}, {247, 0, 0}},
    {{247, 0, 0}, {0, 0, 0}, {0, 0, 0}, {0, 0, 0}, {247, 0, 0}},
    {{247, 0, 0}, {0, 0, 0}, {0, 0, 0}, {0, 0, 0}, {247, 0, 0}},
    {{247, 0, 0}, {0, 0, 0}, {0, 0, 0}, {0, 0, 0}, {247, 0, 0}},
    {{247, 0, 0}, {247, 0, 0}, {247, 0, 0}, {247, 0, 0}, {247, 0, 0}}
},

{
    {{247, 0, 0}, {247, 0, 0}, {247, 0, 0}, {247, 0, 0}, {247, 0, 0}},
    {{247, 0, 0}, {0, 0, 0}, {0, 0, 0}, {0, 0, 0}, {247, 0, 0}},
    {{247, 0, 0}, {0, 0, 0}, {0, 0, 0}, {0, 0, 0}, {247, 0, 0}},
    {{247, 0, 0}, {0, 0, 0}, {0, 0, 0}, {0, 0, 0}, {247, 0, 0}},
    {{247, 0, 0}, {247, 0, 0}, {247, 0, 0}, {247, 0, 0}, {247, 0, 0}}
},

{
    {{0, 0, 0}, {0, 0, 0}, {0, 0, 0}, {0, 0, 0}, {0, 0, 0}},
    {{0, 0, 0}, {247, 0, 0}, {247, 0, 0}, {247, 0, 0}, {0, 0, 0}},
    {{0, 0, 0}, {247, 0, 0}, {0, 0, 0}, {247, 0, 0}, {0, 0, 0}},
    {{0, 0, 0}, {247, 0, 0}, {247, 0, 0}, {247, 0, 0}, {0, 0, 0}},
    {{0, 0, 0}, {0, 0, 0}, {0, 0, 0}, {0, 0, 0}, {0, 0, 0}}
},

{
    {{0, 0, 0}, {0, 0, 0}, {0, 0, 0}, {0, 0, 0}, {0, 0, 0}},
    {{0, 0, 0}, {0, 0, 0}, {0, 0, 0}, {0, 0, 0}, {0, 0, 0}},
    {{0, 0, 0}, {0, 0, 0}, {247, 0, 0}, {0, 0, 0}, {0, 0, 0}},
    {{0, 0, 0}, {0, 0, 0}, {0, 0, 0}, {0, 0, 0}, {0, 0, 0}},
    {{0, 0, 0}, {0, 0, 0}, {0, 0, 0}, {0, 0, 0}, {0, 0, 0}}
},

{
    {{0, 0, 0}, {0, 0, 0}, {0, 0, 0}, {0, 0, 0}, {0, 0, 0}},
    {{0, 0, 0}, {0, 0, 0}, {0, 0, 0}, {0, 0, 0}, {0, 0, 0}},
    {{0, 0, 0}, {0, 0, 0}, {0, 69, 255}, {0, 0, 0}, {0, 0, 0}},
    {{0, 0, 0}, {0, 0, 0}, {0, 0, 0}, {0, 0, 0}, {0, 0, 0}},
    {{0, 0, 0}, {0, 0, 0}, {0, 0, 0}, {0, 0, 0}, {0, 0, 0}}
},

{
    {{0, 0, 0}, {0, 0, 0}, {0, 0, 0}, {0, 0, 0}, {0, 0, 0}},
    {{0, 0, 0}, {0, 69, 255}, {0, 69, 255}, {0, 69, 255}, {0, 0, 0}},
    {{0, 0, 0}, {0, 69, 255}, {0, 0, 0}, {0, 69, 255}, {0, 0, 0}},
    {{0, 0, 0}, {0, 69, 255}, {0, 69, 255}, {0, 69, 255}, {0, 0, 0}},
    {{0, 0, 0}, {0, 0, 0}, {0, 0, 0}, {0, 0, 0}, {0, 0, 0}}
},

{
    {{0, 69, 255}, {0, 69, 255}, {0, 69, 255}, {0, 69, 255}, {0, 69, 255}},
    {{0, 69, 255}, {0, 0, 0}, {0, 0, 0}, {0, 0, 0}, {0, 69, 255}},
    {{0, 69, 255}, {0, 0, 0}, {0, 0, 0}, {0, 0, 0}, {0, 69, 255}},
    {{0, 69, 255}, {0, 0, 0}, {0, 0, 0}, {0, 0, 0}, {0, 69, 255}},
    {{0, 69, 255}, {0, 69, 255}, {0, 69, 255}, {0, 69, 255}, {0, 69, 255}}
}
    
    ///////////////////////////////////////////////////////////////// ATÉ AQUI
};
int animex_4[frames_animex_4][5][5][3] = {
    /////////////////////////SUBSTITUIR TODOS OS SPRITES CONVERTIDOS A PARTIR DAQUI
{
    {{0, 0, 0}, {0, 0, 0}, {0, 0, 0}, {0, 0, 0}, {0, 0, 0}},  
    {{0, 0, 0}, {0, 0, 0}, {0, 0, 0}, {0, 0, 0}, {0, 0, 0}},  
    {{0, 0, 0}, {0, 0, 0}, {0, 0, 0}, {0, 0, 0}, {0, 0, 0}},  
    {{255, 0, 0}, {0, 0, 0}, {0, 0, 0}, {0, 0, 0}, {0, 0, 0}},
    {{0, 0, 0}, {0, 0, 0}, {0, 0, 0}, {0, 0, 0}, {0, 0, 0}}   
},
{
    {{0, 0, 0}, {0, 0, 0}, {0, 0, 0}, {0, 0, 0}, {0, 0, 0}},
    {{0, 0, 0}, {0, 0, 0}, {0, 0, 0}, {0, 0, 0}, {0, 0, 0}},
    {{0, 0, 0}, {0, 0, 0}, {0, 0, 0}, {0, 0, 0}, {0, 0, 0}},
    {{255, 0, 0}, {0, 0, 0}, {0, 0, 0}, {0, 0, 0}, {0, 0, 0}},
    {{0, 0, 0}, {255, 0, 0}, {0, 0, 0}, {0, 0, 0}, {0, 0, 0}}
},
{
    {{0, 0, 0}, {0, 0, 0}, {0, 0, 0}, {0, 0, 0}, {0, 0, 0}},
    {{0, 0, 0}, {0, 0, 0}, {0, 0, 0}, {0, 0, 0}, {0, 0, 0}},
    {{0, 0, 0}, {0, 0, 0}, {0, 0, 0}, {0, 0, 0}, {0, 0, 0}},
    {{255, 0, 0}, {0, 0, 0}, {255, 0, 0}, {0, 0, 0}, {0, 0, 0}},
    {{0, 0, 0}, {255, 0, 0}, {0, 0, 0}, {0, 0, 0}, {0, 0, 0}}
},
{
    {{0, 0, 0}, {0, 0, 0}, {0, 0, 0}, {0, 0, 0}, {0, 0, 0}},
    {{0, 0, 0}, {0, 0, 0}, {0, 0, 0}, {0, 0, 0}, {0, 0, 0}},
    {{0, 0, 0}, {0, 0, 0}, {0, 0, 0}, {255, 0, 0}, {0, 0, 0}},
    {{255, 0, 0}, {0, 0, 0}, {255, 0, 0}, {0, 0, 0}, {0, 0, 0}},
    {{0, 0, 0}, {255, 0, 0}, {0, 0, 0}, {0, 0, 0}, {0, 0, 0}}
},
{
    {{0, 0, 0}, {0, 0, 0}, {0, 0, 0}, {0, 0, 0}, {0, 0, 0}},
    {{0, 0, 0}, {0, 0, 0}, {0, 0, 0}, {0, 0, 0}, {255, 0, 0}},
    {{0, 0, 0}, {0, 0, 0}, {0, 0, 0}, {255, 0, 0}, {0, 0, 0}},
    {{255, 0, 0}, {0, 0, 0}, {255, 0, 0}, {0, 0, 0}, {0, 0, 0}},
    {{0, 0, 0}, {255, 0, 0}, {0, 0, 0}, {0, 0, 0}, {0, 0, 0}}
}
    
    ///////////////////////////////////////////////////////////////// ATÉ AQUI
};

// animação 2

int animex_2[frames_animex_2][5][5][3] = {
{
    {{140, 45, 157}, {140, 45, 157}, {0, 0, 0}, {0, 0, 0}, {0, 0, 0}},
    {{0, 0, 0}, {140, 45, 157}, {0, 0, 0}, {0, 0, 0}, {0, 0, 0}},
    {{0, 0, 0}, {140, 45, 157}, {0, 0, 0}, {0, 0, 0}, {0, 0, 0}},
    {{0, 0, 0}, {140, 45, 157}, {140, 45, 157}, {140, 45, 157}, {0, 0, 0}},
    {{0, 0, 0}, {140, 45, 157}, {0, 0, 0}, {140, 45, 157}, {0, 0, 0}}
},

{
    {{0, 0, 0}, {140, 45, 157}, {140, 45, 157}, {140, 45, 157}, {0, 0, 0}},
    {{140, 45, 157}, {140, 45, 157}, {140, 45, 157}, {140, 45, 157}, {140, 45, 157}},
    {{0, 0, 0}, {0, 0, 0}, {140, 45, 157}, {0, 0, 0}, {0, 0, 0}},
    {{140, 45, 157}, {0, 0, 0}, {140, 45, 157}, {0, 0, 0}, {0, 0, 0}},
    {{140, 45, 157}, {140, 45, 157}, {140, 45, 157}, {0, 0, 0}, {0, 0, 0}}
},

{
    {{0, 0, 0}, {140, 45, 157}, {140, 45, 157}, {140, 45, 157}, {0, 0, 0}},
    {{140, 45, 157}, {0, 0, 0}, {140, 45, 157}, {0, 0, 0}, {140, 45, 157}},
    {{140, 45, 157}, {140, 45, 157}, {140, 45, 157}, {140, 45, 157}, {140, 45, 157}},
    {{140, 45, 157}, {140, 45, 157}, {140, 45, 157}, {140, 45, 157}, {140, 45, 157}},
    {{140, 45, 157}, {0, 0, 0}, {140, 45, 157}, {0, 0, 0}, {140, 45, 157}}
},

{
    {{0, 0, 0}, {0, 0, 0}, {0, 0, 0}, {0, 0, 0}, {0, 0, 0}},
    {{0, 0, 0}, {140, 45, 157}, {0, 0, 0}, {140, 45, 157}, {0, 0, 0}},
    {{0, 0, 0}, {0, 0, 0}, {0, 0, 0}, {0, 0, 0}, {0, 0, 0}},
    {{140, 45, 157}, {0, 0, 0}, {0, 0, 0}, {0, 0, 0}, {140, 45, 157}},
    {{0, 0, 0}, {140, 45, 157}, {140, 45, 157}, {140, 45, 157}, {0, 0, 0}}
},

{
    {{0, 0, 0}, {140, 45, 157}, {0, 0, 0}, {140, 45, 157}, {0, 0, 0}},
    {{140, 45, 157}, {140, 45, 157}, {140, 45, 157}, {140, 45, 157}, {140, 45, 157}},
    {{140, 45, 157}, {140, 45, 157}, {140, 45, 157}, {140, 45, 157}, {140, 45, 157}},
    {{0, 0, 0}, {140, 45, 157}, {140, 45, 157}, {140, 45, 157}, {0, 0, 0}},
    {{0, 0, 0}, {0, 0, 0}, {140, 45, 157}, {0, 0, 0}, {0, 0, 0}}
}
};

int animex_6[frames_animex_6][5][5][3] = {
    /////////////////////////SUBSTITUIR TODOS OS SPRITES CONVERTIDOS A PARTIR DAQUI
{
    {{0, 0, 0}, {255, 0, 0}, {0, 0, 0}, {255, 0, 0}, {0, 0, 0}},
    {{255,0,0}, {255,0,0}, {255,0,0}, {255,0,0}, {255,0,0}},
    {{255,0,0}, {255,0,0}, {255,0,0}, {255,0,0}, {255,0,0}},
    {{0, 0, 0}, {255,0,0}, {255,0,0}, {255,0,0}, {0, 0, 0}},
    {{0, 0, 0}, {0, 0, 0}, {255,0,0}, {0, 0, 0}, {0, 0, 0}}
},

{
    {{0, 0, 0}, {255, 255, 255}, {0, 0, 0}, {255, 255, 255}, {0, 0, 0}},
    {{255, 255, 255}, {255, 255, 255}, {255, 255, 255}, {255, 255, 255}, {255, 255, 255}},
    {{255, 255, 255}, {255, 255, 255}, {255, 255, 255}, {255, 255, 255}, {255, 255, 255}},
    {{0, 0, 0}, {255, 255, 255}, {255, 255, 255}, {255, 255, 255}, {0, 0, 0}},
    {{0, 0, 0}, {0, 0, 0}, {255, 255, 255}, {0, 0, 0}, {0, 0, 0}}
},

{
    {{0, 0, 0}, {255,0,0}, {0, 0, 0}, {255,0,0}, {0, 0, 0}},
    {{255,0,0}, {255,0,0}, {255,0,0}, {255,0,0}, {255,0,0}},
    {{255,0,0}, {255,0,0}, {255,0,0}, {255,0,0}, {255,0,0}},
    {{0, 0, 0}, {255,0,0}, {255,0,0}, {255,0,0}, {0, 0, 0}},
    {{0, 0, 0}, {0, 0, 0}, {255,0,0}, {0, 0, 0}, {0, 0, 0}}
},

{
    {{0, 0, 0}, {255, 255, 255}, {0, 0, 0}, {255, 255, 255}, {0, 0, 0}},
    {{255, 255, 255}, {255, 255, 255}, {255, 255, 255}, {255, 255, 255}, {255, 255, 255}},
    {{255, 255, 255}, {255, 255, 255}, {255, 255, 255}, {255, 255, 255}, {255, 255, 255}},
    {{0, 0, 0}, {255, 255, 255}, {255, 255, 255}, {255, 255, 255}, {0, 0, 0}},
    {{0, 0, 0}, {0, 0, 0}, {255, 255, 255}, {0, 0, 0}, {0, 0, 0}}
},

{
    {{0, 0, 0}, {255,0,0}, {0, 0, 0}, {255,0,0}, {0, 0, 0}},
    {{255,0,0}, {255,0,0}, {255,0,0}, {255,0,0}, {255,0,0}},
    {{255,0,0}, {255,0,0}, {255,0,0}, {255,0,0}, {255,0,0}},
    {{0, 0, 0}, {255,0,0}, {255,0,0}, {255,0,0}, {0, 0, 0}},
    {{0, 0, 0}, {0, 0, 0}, {255,0,0}, {0, 0, 0}, {0, 0, 0}}
},

{
    {{0, 0, 0}, {255, 255, 255}, {0, 0, 0}, {255, 255, 255}, {0, 0, 0}},
    {{255, 255, 255}, {255, 255, 255}, {255, 255, 255}, {255, 255, 255}, {255, 255, 255}},
    {{255, 255, 255}, {255, 255, 255}, {255, 255, 255}, {255, 255, 255}, {255, 255, 255}},
    {{0, 0, 0}, {255, 255, 255}, {255, 255, 255}, {255, 255, 255}, {0, 0, 0}},
    {{0, 0, 0}, {0, 0, 0}, {255, 255, 255}, {0, 0, 0}, {0, 0, 0}}
}
    ///////////////////////////////////////////////////////////////// ATÉ AQUI
};

int animex_5[frames_animex_5][5][5][3] = {
    /////////////////////////SUBSTITUIR TODOS OS SPRITES CONVERTIDOS A PARTIR DAQUI
{
    {{0, 0, 0}, {0, 0, 0}, {0, 0, 0}, {0, 0, 0}, {0, 0, 0}},      
    {{0, 0, 0}, {255, 0, 0}, {0, 0, 0}, {255, 0, 0}, {0, 0, 0}},  
    {{0, 0, 0}, {0, 0, 0}, {0, 0, 0}, {0, 0, 0}, {0, 0, 0}},      
    {{255, 0, 0}, {0, 0, 0}, {0, 0, 0}, {0, 0, 0}, {255, 0, 0}},  
    {{0, 0, 0}, {255, 0, 0}, {255, 0, 0}, {255, 0, 0}, {0, 0, 0}} 
},

{
    {{0, 0, 0}, {0, 0, 0}, {0, 0, 0}, {0, 0, 0}, {0, 0, 0}},      
    {{0, 0, 0}, {255, 0, 0}, {0, 0, 0}, {255, 0, 0}, {0, 0, 0}},  
    {{0, 0, 0}, {0, 0, 0}, {0, 0, 0}, {0, 0, 0}, {0, 0, 0}},      
    {{0, 0, 0}, {255, 0, 0}, {255, 0, 0}, {255, 0, 0}, {0, 0, 0}},
    {{255, 0, 0}, {0, 0, 0}, {0, 0, 0}, {0, 0, 0}, {255, 0, 0}}   
},

{
    {{0, 0, 0}, {255, 0, 0}, {0, 0, 0}, {0, 0, 0}, {255, 0, 0}},
    {{0, 0, 0}, {255, 0, 0}, {0, 0, 0}, {255, 0, 0}, {0, 0, 0}},
    {{0, 0, 0}, {255, 0, 0}, {255, 0, 0}, {0, 0, 0}, {0, 0, 0}},
    {{0, 0, 0}, {255, 0, 0}, {0, 0, 0}, {255, 0, 0}, {0, 0, 0}},
    {{0, 0, 0}, {255, 0, 0}, {0, 0, 0}, {0, 0, 0}, {255, 0, 0}}
},

{
    {{0, 0, 0}, {0, 0, 0}, {255, 0, 0}, {0, 0, 0}, {0, 0, 0}},
    {{255, 0, 0}, {255, 0, 0}, {255, 0, 0}, {255, 0, 0}, {255, 0, 0}},
    {{0, 0, 0}, {0, 0, 0}, {255, 0, 0}, {0, 0, 0}, {0, 0, 0}},
    {{0, 0, 0}, {0, 0, 0}, {255, 0, 0}, {0, 0, 0}, {0, 0, 0}},
    {{0, 0, 0}, {0, 0, 0}, {255, 0, 0}, {0, 0, 0}, {0, 0, 0}}
},

{
    {{0, 0, 0}, {255, 0, 0}, {0, 0, 0}, {0, 0, 0}, {0, 0, 0}},
    {{255, 0, 0}, {255, 0, 0}, {255, 0, 0}, {255, 0, 0}, {255, 0, 0}},
    {{0, 0, 0}, {255, 0, 0}, {0, 0, 0}, {0, 0, 0}, {0, 0, 0}},
    {{0, 0, 0}, {255, 0, 0}, {0, 0, 0}, {0, 0, 0}, {0, 0, 0}},
    {{0, 0, 0}, {255, 0, 0}, {0, 0, 0}, {0, 0, 0}, {0, 0, 0}}
},

{
    {{0, 0, 0}, {0, 0, 0}, {0, 0, 0}, {0, 0, 0}, {0, 0, 0}},
    {{0, 0, 0}, {0, 0, 0}, {0, 0, 0}, {0, 0, 0}, {0, 0, 0}},
    {{0, 0, 0}, {0, 0, 0}, {0, 0, 0}, {0, 0, 0}, {0, 0, 0}},
    {{0, 0, 0}, {0, 0, 0}, {0, 0, 0}, {0, 0, 0}, {0, 0, 0}},
    {{0, 0, 0}, {0, 0, 0}, {0, 0, 0}, {0, 0, 0}, {0, 0, 0}}
}
    ///////////////////////////////////////////////////////////////// ATÉ AQUI
};
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

// Definição do número de LEDs e pino.
#define LED_COUNT 25
#define LED_PIN 20

// Definição de pixel GRB
struct pixel_t
{
    uint8_t G, R, B; // Três valores de 8-bits compõem um pixel.
};
typedef struct pixel_t pixel_t;
typedef pixel_t npLED_t; // Mudança de nome de "struct pixel_t" para "npLED_t" por clareza.

// Declaração do buffer de pixels que formam a matriz.
npLED_t leds[LED_COUNT];

// Variáveis para uso da máquina PIO.
PIO np_pio;
uint sm;

/**
 * Inicializa a máquina PIO para controle da matriz de LEDs.
 */
void npInit(uint pin)
{

    // Cria programa PIO.
    uint offset = pio_add_program(pio0, &ws2818b_program);
    np_pio = pio0;

    // Toma posse de uma máquina PIO.
    sm = pio_claim_unused_sm(np_pio, false);
    if (sm < 0)
    {
        np_pio = pio1;
        sm = pio_claim_unused_sm(np_pio, true); // Se nenhuma máquina estiver livre, panic!
    }

    // Inicia programa na máquina PIO obtida.
    ws2818b_program_init(np_pio, sm, offset, pin, 800000.f);

    // Limpa buffer de pixels.
    for (uint i = 0; i < LED_COUNT; ++i)
    {
        leds[i].R = 0;
        leds[i].G = 0;
        leds[i].B = 0;
    }
}

/**
 * Atribui uma cor RGB a um LED.
 */
void npSetLED(const uint index, const uint8_t r, const uint8_t g, const uint8_t b)
{
    leds[index].R = r;
    leds[index].G = g;
    leds[index].B = b;
}

/**
 * Escreve os dados do buffer nos LEDs.
 */
void npWrite()
{
    // Escreve cada dado de 8-bits dos pixels em sequência no buffer da máquina PIO.
    for (uint i = 0; i < LED_COUNT; ++i)
    {
        pio_sm_put_blocking(np_pio, sm, leds[i].G);
        pio_sm_put_blocking(np_pio, sm, leds[i].R);
        pio_sm_put_blocking(np_pio, sm, leds[i].B);
    }
    sleep_us(100); // Espera 100us, sinal de RESET do datasheet.
}

/**
 * Limpa o buffer de pixels.
 */
void npClear()
{
    for (uint i = 0; i < LED_COUNT; ++i){
        npSetLED(i, 0, 0, 0);
    }
    npWrite();
}

// mapa de teclas
char mapa_TECLAS[4][4] = {
    '1', '2', '3', 'A',
    '4', '5', '6', 'B',
    '7', '8', '9', 'C',
    '*', '0', '#', 'D'};

// Definindo os pinos para linhas e colunas
const uint linhas[] = {8, 7, 6, 5};  // Pinos das linhas (GP5, GP6, GP7, GP8)
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
void init_buzzer(uint pin)
{
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
void inicializa_teclado()
{
    // Configurando as linhas como saída
    for (int i = 0; i < 4; i++)
    {
        gpio_init(linhas[i]);
        gpio_set_dir(linhas[i], GPIO_OUT);
        gpio_put(linhas[i], 1); // Mantendo em nível alto
    }

    // Configurando as colunas como entrada com pull-up
    for (int i = 0; i < 4; i++)
    {
        gpio_init(colunas[i]);
        gpio_set_dir(colunas[i], GPIO_IN);
        gpio_pull_up(colunas[i]);
    }
}

// Lendo a tecla pressionada no teclado
char ler_tecla()
{
    for (int i = 0; i < 4; i++)
    {
        // Colocando a linha atual em nível baixo
        gpio_put(linhas[i], 0);

        // Verificando se alguma coluna está em nível baixo
        for (int j = 0; j < 4; j++)
        {
            if (gpio_get(colunas[j]) == 0)
            {                 // Coluna em nível baixo
                sleep_ms(20); // intervalo simples
                if (gpio_get(colunas[j]) == 0)
                {
                    // Restaurandi a linha para nível alto
                    gpio_put(linhas[i], 1);
                    return mapa_TECLAS[i][j];
                }
            }
        }

        // Restaurando a linha para nível alto
        gpio_put(linhas[i], 1);
    }
    return '\0'; // Sem teclas pressionadas
}

// Função para converter a posição do matriz para uma posição do vetor.
int getIndex(int x, int y)
{
    // Se a linha for par (0, 2, 4), percorremos da esquerda para a direita.
    // Se a linha for ímpar (1, 3), percorremos da direita para a esquerda.
    if (y % 2 == 0)
    {
        return 24 - (y * 5 + x); // Linha par (esquerda para direita).
    }
    else
    {
        return 24 - (y * 5 + (4 - x)); // Linha ímpar (direita para esquerda).
    }
}

// Função para fazer a animação na matriz de leds
void desenhar_sprite(int animacao[frames_animex][5][5][3], int sprite)
{
    // Desenhando Sprite contido na animex[?][]
    for (int linha = 0; linha < 5; linha++)
    {
        for (int coluna = 0; coluna < 5; coluna++)
        {
            int posicao = getIndex(linha, coluna);
            npSetLED(posicao, animacao[sprite][coluna][linha][0], animacao[sprite][coluna][linha][1], animacao[sprite][coluna][linha][2]);
        }
    }
}

// main
int main()
{
    // inicializações
    stdio_init_all();
    init_buzzer(BUZZER_PIN);
    inicializa_teclado();
    npInit(LED_PIN);
    npClear();
    npWrite();

    while (true)
    {
        // lendo a tecla
        char tecla = ler_tecla();
        char last_tecla;
        char escolha_switch;

        if (tecla != last_tecla)
        {
            last_tecla = tecla;
            escolha_switch = tecla;
        }
        else
        {
            sleep_ms(50);
            escolha_switch = 'N';
        }
        // se for 8,chama a função que liga todos os LEDs
        switch (escolha_switch)
        {
        case '0':
            func_0();
            break;
        case '1':
            func_1();
            break;
        case '2':
            func_2();
            break;
        case '3':
            func_3();
            break;
        case '4':
            func_4();
            break;
        case '5':
            func_5();
            break;
        case '6':
            func_6();
            break;
        case '7':
            func_7();
            break;
        case '8':
            func_8();
            break;
        case '9':
            func_9();
            break;
        case 'A':
            func_A();
            break;
        case 'B':
            func_B();
            break;
        case 'C':
            func_C();
            break;
        case 'D':
            func_D();
            break;
        case '*':
            func_reboot();
            break;
        case '#':
            func_hash();
            break;
        default:
            break; // Nenhuma tecla válida
        }
    }
    return 0;
}

void func_0(void)
{
}

void func_1(void)
{
 for (int i = 0; i < repeticoes; i++)
    {
        for (int s = 0; s < frames_animex_1; s++)
        {
            frames_animex = frames_animex_1;
            desenhar_sprite(animex_1, s);
            sleep_ms(1000 / fps);
            aciona_buzzer();
            npWrite(); // Escreve os dados nos LEDs.
        }
    }
    npClear();   
}

void func_2(void)
{
for (int i = 0; i < repeticoes; i++)
    {
        for (int s = 0; s < frames_animex_2; s++)
        {
            frames_animex = frames_animex_2;
            desenhar_sprite(animex_2, s);
            sleep_ms(1000 / fps);
            aciona_buzzer();
            npWrite(); // Escreve os dados nos LEDs.
        }
    }
    npClear(); 
}

void func_3(void)
{
}

void func_4(void)
{
 for (int i = 0; i < repeticoes; i++)
    {
        for (int s = 0; s < frames_animex_4; s++)
        {
            frames_animex = frames_animex_4;
            desenhar_sprite(animex_4, s);
            sleep_ms(1000 / fps);
            aciona_buzzer();
            npWrite(); // Escreve os dados nos LEDs.
        }
    }
    npClear();   
}

void func_5(void)
{

    for (int i = 0; i < repeticoes; i++)
    {
        for (int s = 0; s < frames_animex_5; s++)
        {
            frames_animex = frames_animex_5;
            desenhar_sprite(animex_5, s);
            sleep_ms(1000 / fps);
            aciona_buzzer();
            npWrite(); // Escreve os dados nos LEDs.
        }
    }
    npClear();
}

void func_6(void)
{
    for (int i = 0; i < repeticoes; i++)
    {
        for (int s = 0; s < frames_animex_6; s++)
        {
            frames_animex = frames_animex_6;
            desenhar_sprite(animex_6, s);
            sleep_ms(1000 / fps);
            aciona_buzzer();
            npWrite(); // Escreve os dados nos LEDs.
        }
    }
    npClear();
}

void func_7(void)
{
}

void func_8(void)
{
}

void func_9(void)
{
}

void func_A(void)
{
    for (uint i = 0; i < LED_COUNT; ++i){
        npSetLED(i, 0, 0, 0);
    }
    npWrite();
}

void func_B(void)
{
     for (uint i = 0; i < LED_COUNT; ++i){
        npSetLED(i, 0, 0, 255);
    }
    npWrite();
}

void func_C(void)
{
}

void func_D(void)
{
    for (uint i = 0; i < LED_COUNT; ++i){
        npSetLED(i, 0, 127, 0);
    }
    npWrite();
    
}

void func_reboot(void)
{
    printf("Dando reboot...\n");
    sleep_ms(1000);
    reset_usb_boot(0, 0);
}

void func_hash(void)
{
    for (int i = 0; i < LED_COUNT; i++)
    {
        npSetLED(i, 51, 51, 51); // Branco com 20% de intensidade
    }
    npWrite(); // Atualiza os LEDs
}

// Aciona o buzzer
void aciona_buzzer(void)
{
    // Obter o slice do PWM associado ao pino
    uint slice_num = pwm_gpio_to_slice_num(BUZZER_PIN);

    // Ativar o PWM com duty cycle de 50%
    pwm_set_gpio_level(BUZZER_PIN, 2048); // 50% de 4096

    // Escrever "beep" no terminal
    printf("Buzz\n");

    // Temporização para duração do som
    sleep_ms(1000 / fps);

    // Desativar o PWM (duty cycle 0)
    pwm_set_gpio_level(BUZZER_PIN, 0);
}
