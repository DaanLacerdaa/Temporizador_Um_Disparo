🔴🟢🔵 Projeto: Controle de LEDs com Raspberry Pi Pico

Este projeto implementa um sistema de controle de LEDs utilizando o microcontrolador Raspberry Pi Pico. O código em C, baseado no Pico SDK, gerencia a ativação sequencial de LEDs coloridos (vermelho, azul e verde) por meio da interação com um botão físico. O sistema inclui um mecanismo de debounce e controle de estados, garantindo uma operação confiável e previsível.

🎯 Objetivo

O objetivo deste projeto é explorar a interface de controle de GPIOs do Raspberry Pi Pico, implementando:

Gerenciamento de estados utilizando a enumeração EstadoSistema.

Interrupção por evento de botão com debounce.

Utilização de temporizadores para controle de mudança de estado.

Impressão do estado atual via comunicação serial.

🛠 Tecnologias Utilizadas

Raspberry Pi Pico

Linguagem C

Pico SDK

VSCode com Raspberry Pi Pico SDK

Simulação em Wokwi (opcional)

📌 Funcionamento do Código

Inicialização dos GPIOs:

Configura os LEDs e o botão.

Define o estado inicial como ESTADO_OFF.

Interação com o Botão:

Ao pressionar o botão, a sequência é iniciada se estiver inativa.

Um sistema de debounce evita leituras espúrias.

Sequência de LEDs:

Estado 1: Três LEDs acesos.

Estado 2: Apenas dois LEDs acesos.

Estado 3: Apenas um LED aceso.

Estado 4: Todos os LEDs desligados.

O ciclo se repete apenas quando o botão for pressionado novamente.

Temporização:

Cada estado dura aproximadamente 3 segundos antes de avançar automaticamente para o próximo.

A função add_alarm_in_ms() é utilizada para agendamento de mudanças de estado.

Saída Serial:

O estado atual é reportado a cada segundo para monitoramento.

📥 Instalação e Configuração

1️⃣ Configuração do Pico SDK no VSCode

Caso ainda não tenha o Pico SDK configurado, siga este guia: Raspberry Pi Pico SDK Setup

2️⃣ Clonagem do Repositório

git clone <https://github.com/DaanLacerdaa/Temporizador_Um_Disparo>
cd Temporizador_Um_Disparo

3️⃣ Compilação do Código

Opção 1: Compilar via Terminal com CMake

mkdir build
cd build
cmake ..
make

O arquivo .uf2 será gerado, pronto para ser carregado no Raspberry Pi Pico.

Opção 2: Compilar no VSCode

Abra o projeto no VSCode.

Conecte o Raspberry Pi Pico ao computador via USB.

Ative o modo BOOTSEL pressionando o botão BOOTSEL ao conectar o cabo USB.

Compile e envie o código utilizando o VSCode.

4️⃣ Monitoramento da Saída Serial

Para visualizar a execução em tempo real, conecte-se à porta serial do Raspberry Pi Pico:

screen /dev/ttyUSB0 115200

🎥 Demonstração

🔗 Vídeo do projeto no YouTube: []

🎮 Simulação no Wokwi: [[Wokwi](https://wokwi.com/projects/422013472937946113)]

👨💻 Autor

## 👨💻 Autor

| [<img src="https://avatars.githubusercontent.com/DaanLacerdaa" width=115><br><sub>Daan Lacerda</sub>](https://github.com/DaanLacerdaa) |
|
📜 Licença

Este projeto está licenciado sob os termos da licença MIT .
