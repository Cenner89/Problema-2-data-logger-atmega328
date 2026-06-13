# Arquitetura Inicial do Firmware

Data: 2026-06-07

## Visao geral

O firmware sera organizado em camadas simples:

```text
main.c
  |
  +-- datalogger.c
        |
        +-- sensors.c
        |     +-- adc.c
        |     +-- filter.c
        |
        +-- rtc.c
        |
        +-- comm.c
        |
        +-- mode_select.c
```

## Responsabilidades dos modulos

| Modulo | Responsabilidade |
| --- | --- |
| `main.c` | Inicializar o sistema e executar o loop principal. |
| `config.h` | Concentrar constantes de configuracao do firmware. |
| `datalogger.c` | Coordenar coleta, filtragem, timestamp e envio dos registros. |
| `sensors.c` | Ler sensores analogicos e digitais. |
| `adc.c` | Configurar e ler canais do conversor ADC do ATmega328. |
| `filter.c` | Aplicar filtro digital passa-baixas nas amostras analogicas. |
| `rtc.c` | Obter data e hora do RTC externo. |
| `comm.c` | Enviar registros pela interface escolhida. |
| `mode_select.c` | Ler chave/jumper de selecao da interface de comunicacao. |

## Estrategia de filtragem inicial

Nesta primeira base, sera usado um filtro IIR passa-baixas de primeira ordem:

```text
y[n] = y[n-1] + alpha * (x[n] - y[n-1])
```

Para evitar ponto flutuante no microcontrolador, a implementacao usa aritmetica inteira:

```text
y = y + ((x - y) >> FILTER_SHIFT)
```

Com `FILTER_SHIFT = 3`, o filtro usa aproximadamente `alpha = 1/8`.

## Estrategia de comunicacao

A arquitetura tera uma camada `comm`, com uma interface comum:

```c
comm_init(mode);
comm_send_record(&record);
```

Inicialmente serao previstos dois modos:

- `COMM_MODE_USART`
- `COMM_MODE_WIRELESS`

Na primeira etapa, a USART sera priorizada porque e mais facil de testar no simulador e no hardware. O modo sem fio entrara depois como driver especifico.

## Selecao fisica da comunicacao

Foi adicionada uma selecao por pino usando `PD2`.

- `PD2` em nivel alto ou aberto: modo USART.
- `PD2` em nivel baixo, ligado ao GND: modo sem fio.

Essa decisao atende ao enunciado, que pede que o usuario escolha a versao de comunicacao antes da instalacao.

## Proximo passo tecnico

1. Confirmar ferramenta de projeto: MPLAB X + XC8.
2. Criar projeto C no IDE usando ATmega328P.
3. Importar os arquivos da pasta `src`.
4. Compilar firmware minimo.
5. Implementar e testar ADC.
6. Implementar USART.
7. Definir RTC e modulo sem fio.
