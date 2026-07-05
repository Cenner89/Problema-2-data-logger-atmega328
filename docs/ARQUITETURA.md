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
        |     +-- twi.c
        |
        +-- storage.c
        |
        +-- comm.c
        |     +-- usart.c
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
| `twi.c` | Implementar comunicacao I2C/TWI usada pelo RTC. |
| `storage.c` | Salvar registros recentes na EEPROM interna. |
| `comm.c` | Enviar registros pela interface escolhida. |
| `usart.c` | Configurar e transmitir bytes pela USART do ATmega328P. |
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
comm_send_header();
comm_send_record(&record);
```

Inicialmente serao previstos dois modos:

- `COMM_MODE_USART`
- `COMM_MODE_WIRELESS`

Na primeira etapa, a USART sera priorizada porque e mais facil de testar no simulador e no hardware. O modo sem fio entrara depois como driver especifico.

O formato textual escolhido nesta etapa e CSV:

```text
timestamp,temp_raw,temp_filt,light_raw,light_filt,humidity,rain,mode
```

## Selecao fisica da comunicacao

Foi adicionada uma selecao por pino usando `PD2`.

- `PD2` em nivel alto ou aberto: modo USART.
- `PD2` em nivel baixo, ligado ao GND: modo sem fio.

Essa decisao atende ao enunciado, que pede que o usuario escolha a versao de comunicacao antes da instalacao.

## RTC

O firmware passou a assumir um RTC DS3231 no endereco I2C `0x68`.

- SDA: `PC4` / `A4`.
- SCL: `PC5` / `A5`.
- Frequencia TWI: 100 kHz.

Se o RTC nao responder, o firmware usa um horario fallback para manter o registro compilavel e transmissivel.

## Armazenamento

O firmware salva cada registro tambem na EEPROM interna do ATmega328P. A estrategia e circular: quando o limite configurado e atingido, o registro mais novo passa a sobrescrever o mais antigo.

Configuracao inicial:

```text
STORAGE_MAX_RECORDS = 16
```

Essa solucao demonstra o comportamento de data-logger sem exigir hardware externo de memoria.

## Proximo passo tecnico

1. Confirmar ferramenta de projeto: MPLAB X + XC8.
2. Criar projeto C no IDE usando ATmega328P.
3. Importar os arquivos da pasta `src`.
4. Compilar firmware minimo.
5. Implementar e testar ADC.
6. Implementar USART.
7. Validar RTC DS3231 em hardware/simulador.
8. Definir modulo sem fio.
