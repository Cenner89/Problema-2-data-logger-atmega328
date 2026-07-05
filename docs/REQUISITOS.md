# Requisitos do Sistema

Data: 2026-06-07

## Objetivo

Projetar um data-logger ambiental remoto baseado no ATmega328, capaz de coletar, filtrar, registrar e transmitir medicoes ambientais.

## Requisitos funcionais

| ID | Requisito | Descricao | Status |
| --- | --- | --- | --- |
| RF-01 | Leitura de temperatura | Ler sensor analogico de temperatura por ADC. | Planejado |
| RF-02 | Leitura de luminosidade | Ler sensor analogico baseado em LDR por ADC. | Planejado |
| RF-03 | Leitura de umidade | Ler sensor digital de umidade relativa do ar. | Implementado como entrada digital |
| RF-04 | Leitura de chuva | Ler sensor digital de presenca de chuva. | Implementado como entrada digital |
| RF-05 | RTC | Associar cada amostra a data e hora fornecidas por modulo RTC externo. | Implementado para DS3231 |
| RF-06 | Filtragem digital | Aplicar filtro passa-baixas nas leituras analogicas antes do armazenamento/transmissao. | Implementado |
| RF-07 | Comunicacao serial | Transmitir dados pela USART do ATmega328. | Implementado |
| RF-08 | Comunicacao sem fio | Suportar uma versao com modulo sem fio. | Arquitetura definida |
| RF-09 | Selecao da interface | Permitir escolher, antes da instalacao, qual interface de comunicacao sera usada. | Implementado por jumper |
| RF-10 | Registro das medicoes | Montar registros contendo timestamp e valores dos sensores. | Implementado |

## Requisitos nao funcionais

| ID | Requisito | Descricao |
| --- | --- | --- |
| RNF-01 | Modularidade | Separar ADC, filtros, sensores, RTC, comunicacao e logica principal. |
| RNF-02 | Manutencao | Manter nomes claros e organizacao simples para facilitar revisao do grupo. |
| RNF-03 | Robustez | Evitar dependencia de uma unica interface de comunicacao. |
| RNF-04 | Testabilidade | Permitir compilar por script e, quando possivel, testar partes da logica fora do hardware. |
| RNF-05 | Documentacao | Registrar decisoes tecnicas e arquitetura ao longo do desenvolvimento. |

## Premissas iniciais

- O microcontrolador sera o ATmega328 ou ATmega328P.
- A implementacao sera feita em linguagem C.
- O RTC externo adotado na proposta e o DS3231 usando barramento I2C/TWI.
- A comunicacao sem fio sugerida para prototipo e um modulo serial Bluetooth, mantendo o protocolo CSV.
- O firmware usa fallback de horario caso o RTC nao responda.

## Riscos e pontos em aberto

- Definir o modelo exato do RTC.
- Definir o modulo sem fio.
- Definir o sensor digital de umidade.
- Definir periodicidade de amostragem.
- Definir se havera armazenamento local em EEPROM, memoria externa ou apenas transmissao.
- Confirmar se o professor exige projeto no MPLAB X/XC8 ou aceita Microchip Studio/avr-gcc.
