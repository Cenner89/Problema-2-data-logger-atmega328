# Avaliacao de ferramentas para o Problema 2

Data: 2026-06-07

## Contexto

O Problema 2 pede a implementacao de um data-logger ambiental baseado no ATmega328. Diferente do Problema 1, que foi feito em Assembly, este problema pede explicitamente **linguagem C**.

O sistema tambem deve lidar com perifericos e modulos externos:

- ADC para sensores analogicos;
- entradas digitais para sensores de umidade/chuva;
- RTC externo, provavelmente via I2C/TWI;
- USART serial;
- modulo de comunicacao sem fio;
- filtro digital passa-baixas;
- organizacao modular do software.

## Ferramentas encontradas na maquina

- Git instalado.
- GitHub Desktop instalado.
- Microchip/Atmel Studio com `avr-gcc`.
- MPLAB X instalado.
- MPLAB XC8 instalado, incluindo a versao `v3.10`.

Versoes verificadas:

```text
avr-gcc: AVR_8_bit_GNU_Toolchain_3.6.2_1778 / GCC 5.4.0
XC8: Microchip MPLAB XC8 C Compiler V3.10
```

## Opcoes avaliadas

### 1. Microchip Studio com avr-gcc

Vantagens:

- Ja foi usado no Problema 1.
- Suporta projetos em C para AVR.
- Possui simulacao e depuracao integradas.
- O compilador `avr-gcc` ja esta instalado junto com o Microchip Studio.

Desvantagens:

- Ambiente mais antigo.
- Menos alinhado ao ecossistema atual da Microchip para novos projetos.
- Pode ser suficiente, mas nao e a melhor escolha para organizar um projeto novo em C com varios perifericos.

### 2. MPLAB X com XC8

Vantagens:

- Mais alinhado ao ecossistema atual da Microchip.
- O XC8 suporta microcontroladores AVR de 8 bits.
- Melhor escolha para um projeto novo em C com documentacao, perifericos e modularizacao.
- Facilita uma estrutura profissional de projeto.

Desvantagens:

- A interface pode ser nova para quem estava usando Microchip Studio.
- Pode exigir uma etapa inicial de configuracao do projeto.

### 3. Arduino IDE

Vantagens:

- Facil para prototipagem rapida.
- Grande quantidade de bibliotecas prontas para RTC, sensores e comunicacao.

Desvantagens:

- Pode esconder detalhes importantes do ATmega328.
- Menos adequado se a disciplina espera uso mais direto dos registradores/perifericos.
- Pode deixar o projeto com cara de prototipo Arduino, nao de firmware embarcado estruturado.

### 4. PlatformIO / VS Code

Vantagens:

- Muito bom para projetos modulares, testes e versionamento.
- Integra bem com GitHub.
- Pode usar frameworks como Arduino ou AVR puro.

Desvantagens:

- Nao foi encontrado instalado nesta maquina.
- Adicionaria outra camada de ferramenta para aprender.
- Pode ser mais trabalhoso no inicio do que o necessario para a entrega.

## Recomendacao

A recomendacao para o Problema 2 e usar:

```text
MPLAB X + MPLAB XC8
```

Motivo: o problema pede linguagem C, uso de perifericos do ATmega328 e uma solucao modular. Como o MPLAB X e o XC8 ja estao instalados, essa opcao parece a mais adequada para iniciar um projeto novo com base mais atual.

O Microchip Studio continua sendo uma alternativa valida, principalmente se quisermos aproveitar a familiaridade adquirida no Problema 1. Mesmo assim, para este Problema 2, a escolha mais forte e migrar para MPLAB X com XC8.

## Referencias consultadas

- Microchip: GCC Compilers for AVR and Arm MCUs/MPUs  
  <https://www.microchip.com/en-us/tools-resources/develop/microchip-studio/gcc-compilers>
- Microchip: MPLAB XC Compilers  
  <https://www.microchip.com/mplab/compilers>
- Microchip Developer Help: AVR toolchains  
  <https://onlinedocs.microchip.com/oxy/GUID-3BDC0F34-77FF-419B-A8D2-263DC616E959-en-US-2/GUID-1D7B916E-12CA-4AFA-9D17-F94D14D8C33D.html>
- PlatformIO: ATmega328 board documentation  
  <https://docs.platformio.org/en/latest/boards/atmelavr/ATmega328.html>
