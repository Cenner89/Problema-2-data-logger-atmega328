# Relatorio Tecnico - Problema 2

## Titulo

Projeto de um Data-Logger Inteligente para Monitoramento Ambiental Remoto com ATmega328P

## Resumo

Este trabalho apresenta a proposta e a implementacao inicial de um data-logger ambiental baseado no microcontrolador ATmega328P. O sistema realiza a leitura de sensores analogicos e digitais, aplica filtragem digital passa-baixas nas medicoes analogicas, associa cada registro a um timestamp obtido por RTC externo e transmite os dados em formato CSV por interface serial. Tambem foi prevista uma versao de comunicacao sem fio baseada no mesmo protocolo textual. O firmware foi desenvolvido em linguagem C, com organizacao modular e compilacao por MPLAB XC8.

## 1. Introducao

O monitoramento ambiental remoto exige sistemas capazes de coletar dados de forma autonoma, confiavel e organizada. A proposta do Problema 2 consiste em desenvolver um prototipo de data-logger para registrar grandezas ambientais, reduzindo a dependencia de coleta manual e permitindo reconstrucao historica das medicoes.

## 2. Requisitos do sistema

O sistema deve:

- ler sensores analogicos de temperatura e luminosidade;
- ler sensores digitais de umidade e chuva;
- associar data e hora a cada medicao;
- aplicar filtro digital passa-baixas nas leituras analogicas;
- armazenar registros localmente;
- transmitir dados por USART ou por interface sem fio;
- manter arquitetura modular em linguagem C.

## 3. Arquitetura proposta

O firmware foi separado em modulos:

- `adc`: leitura dos canais analogicos;
- `filter`: filtro passa-baixas;
- `sensors`: agrupamento das leituras de sensores;
- `rtc`: leitura do RTC DS3231;
- `twi`: comunicacao I2C/TWI;
- `storage`: armazenamento circular em EEPROM;
- `usart`: driver da serial;
- `comm`: protocolo de comunicacao CSV;
- `mode_select`: selecao da interface por jumper;
- `datalogger`: coordenacao geral do sistema.

## 4. Filtragem digital

Foi adotado um filtro IIR passa-baixas de primeira ordem:

```text
y = y + ((x - y) >> FILTER_SHIFT)
```

Com `FILTER_SHIFT = 3`, o filtro equivale aproximadamente a um fator `alpha = 1/8`. Essa abordagem evita ponto flutuante, reduz custo computacional e e adequada ao ATmega328P.

## 5. Comunicacao

O protocolo usa formato CSV, facilitando leitura em terminal serial e importacao em planilhas:

```text
timestamp,temp_raw,temp_filt,light_raw,light_filt,humidity,rain,mode
```

Exemplo:

```text
2026-01-01T00:00:00,512,500,730,710,1,0,USART
```

## 6. Armazenamento

Foi implementado armazenamento circular usando a EEPROM interna do ATmega328P. A versao atual salva os ultimos 16 registros. Essa abordagem e suficiente para demonstracao academica, embora uma solucao real de campo possa exigir memoria externa.

## 7. Resultados de validacao

O firmware compila com MPLAB XC8 v3.10 e gera arquivo HEX. Tambem foi criado teste automatico para validar a logica do filtro passa-baixas fora do hardware.

## 8. Limitacoes

- A leitura real do RTC ainda precisa ser validada com modulo DS3231 fisico ou simulador.
- O modulo sem fio foi definido como arquitetura/protocolo, mas ainda depende da escolha fisica do hardware.
- Sensores reais ainda precisam ser calibrados.
- A EEPROM interna tem capacidade limitada e desgaste por escrita.

## 9. Conclusao

O projeto atende a base funcional solicitada para o Problema 2, oferecendo firmware modular, leitura de sensores, filtragem, timestamp, comunicacao e armazenamento local. A solucao tambem possui documentacao tecnica e scripts de build/teste, facilitando continuidade, revisao e apresentacao.
