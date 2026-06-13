# Mapa de Pinos Inicial

Data: 2026-06-13

Este mapa e uma proposta inicial para organizar o firmware. Ele ainda pode ser ajustado quando forem definidos os componentes reais do prototipo.

## ATmega328P

| Funcao | Pino do microcontrolador | Nome Arduino comum | Observacao |
| --- | --- | --- | --- |
| Sensor de temperatura analogico | PC0 / ADC0 | A0 | Entrada ADC para temperatura. |
| Sensor LDR analogico | PC1 / ADC1 | A1 | Entrada ADC para luminosidade. |
| Sensor digital de umidade | PB0 | D8 | Entrada digital com pull-up interno. |
| Sensor digital de chuva | PB1 | D9 | Entrada digital com pull-up interno. |
| Selecao de comunicacao | PD2 | D2 | Chave/jumper com pull-up interno. |
| USART RX | PD0 / RXD | D0 | Reservado para comunicacao serial. |
| USART TX | PD1 / TXD | D1 | Saida serial do data-logger. |
| RTC SDA | PC4 / SDA | A4 | Provavel barramento I2C/TWI. |
| RTC SCL | PC5 / SCL | A5 | Provavel barramento I2C/TWI. |

## Selecao de comunicacao

O firmware agora possui um modulo `mode_select`.

Regra inicial:

| Estado em PD2 | Modo escolhido |
| --- | --- |
| Alto / aberto | USART serial |
| Baixo / ligado ao GND | Sem fio |

O modo sem fio ainda e um stub. Por enquanto ele reutiliza a saida serial para manter o firmware compilavel e testavel.

## Observacoes

- Os pinos D0/D1 devem ser tratados com cuidado, pois tambem sao usados para comunicacao serial/programacao em algumas placas.
- O RTC ainda nao foi implementado de verdade; a arquitetura esta preparada para usar I2C/TWI.
- Sensores digitais foram configurados com pull-up interno para evitar entrada flutuante durante testes.
