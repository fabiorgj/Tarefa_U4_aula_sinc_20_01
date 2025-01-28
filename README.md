Embarcatech - U4 - Microcontroladores

Atividade: Geração de animações em uma matriz de LEDs 5x5. - Aula sícrona de 20/01/2025

Grupo 1, Subgrupo 8

### Integrantes:

Fábio Rocha Gomes Jardim  (líder)

Igor de Eça Almeida  

Kauan Lopes de Jesus  

Larissa Batista dos Santos  

Luis Guilherme Coelho Saturnino  

Paolla Giselle Ribeiro  

## Links  

### Vídeo  
https://drive.google.com/file/d/1GXCoEkWMC9J3REm9Sa4LUnjT9olMfhby/view?usp=sharing  

### Piskel  
https://www.piskelapp.com/p/create/sprite

## DESCRIÇÃO DA SOLUÇÃO  
Este programa foi desenvolvido para a Raspberry Pi Pico W e utiliza um teclado matricial 4x4 para controlar uma matriz de LEDs RGB 5x5 e um buzzer. Cada tecla do teclado aciona uma função específica, como chmar as animações, ligar/desligar os LEDs em cores e intensidades especificadas, ou ativar o buzzer.  

O programa é composto por funções para inicializar e operar a matriz de LEDS que são do tipo Neopixel ws2812b, o buzzer, e o teclado, além de um loop principal que monitora a entrada do teclado e executa as funções correspondentes. Foram 6 animações, uma para cada integrante da equipe.

## FUNCIONALIDADES  
As teclas de 1 a 6 correspondem às animações;  

Tecla A, apaga todos os LEDs;  

Tecla B, aciona todos os LEDS azuis com 100% da intensidade;  

Tecla C, aciona todos os LEDs vermelhos com 80% da intensidade;  

Tecla D, aciona todos os LEDs verdes com 50% da intensidade;  

Tecla #, aciona todas as três cores de os LEDs, formando a cor branca, com 20% de intensidade;  

Telca *, coloca a raspberry em modo bootloader

## TESTES NO DESENVOLVIMENTO  
Durante o desenvolvimento do código a equipe utilizou printfs com informações especificas para ajudar a rastrear o fluxo do código

## HARDWARE E SIMULAÇÃO  
Foi utilizado o Wokwi integrado ao VS Code para simular o hardware necessário. A lista de componentes e suas conexões está a seguir:   

GP1: Conectado ao C4 do Keypad.

GP2: Conectado ao C3 do Keypad.

GP3: Conectado ao C2 do Keypad.

GP4: Conectado ao C1 do Keypad.

GP5: Conectado ao R4 do Keypad.

GP6: Conectado ao R3 do Keypad.

GP7: Conectado ao R2 do Keypad.

GP8: Conectado ao R1 do Keypad.

GP20: Conectado ao controle da matriz de LEDs.

GP28: Conectado ao terminal positivo (pino 2) do buzzer.

GND.8: Conectado ao terminal negativo (pino 1) do buzzer.

![Conexões do Circuito](https://github.com/fabiorgj/Tarefa_U4_aula_sinc_20_01/blob/main/esquema_simulacao_wokwi.png)

## EXPLICAÇÃO DAS FUNÇÕES  

### Inicialização  

npInit(uint pin): Configura o controle dos LEDs RGB na matriz utilizando a máquina PIO da Raspberry Pi Pico.

inicializa_teclado(): Configura os pinos GPIO como entradas ou saídas para operar o teclado matricial.

init_buzzer(uint pin): Configura o buzzer para operar com uma frequência de 2 kHz.

### Controle de LEDs

npSetLED(index, r, g, b): Define uma cor RGB para um LED específico na matriz.

npWrite(): Atualiza a matriz de LEDs com as cores definidas no buffer.

npClear(): Limpa a matriz de LEDs (desliga todos os LEDs).

desenhar_sprite(animacao, sprite): Renderiza uma animação na matriz de LEDs a partir de um sprite predefinido.

### Controle do Teclado

ler_tecla(): Detecta e retorna a tecla pressionada no teclado matricial.

### Funções para Animações e Controle

Funções 'func_1' a 'func_6': Disparam animações predefinidas sincronizadas com o buzzer.

Funções 'func_A' a 'func_D': Alteram a cor da matriz para padrões predefinidos (ex.: vermelho, azul, verde).

func_reboot(): Reinicia a Raspberry Pi Pico.

func_hash(): Define todos os LEDs da matriz para branco com baixa intensidade.

aciona_buzzer(): Emite um som pelo buzzer com duty cycle de 50%


