# RTC via I2C/TWI

Data: 2026-07-01

## Objetivo

Substituir o horario fixo inicial por leitura real de um modulo RTC externo.

## Modulo assumido

Nesta etapa, o firmware assume o uso do **DS3231**, um modulo RTC comum em projetos com ATmega328P.

Endereco I2C usado:

```text
0x68
```

## Pinos usados no ATmega328P

| Sinal | Pino ATmega328P | Nome Arduino comum |
| --- | --- | --- |
| SDA | PC4 | A4 |
| SCL | PC5 | A5 |

## Configuracao TWI

| Parametro | Valor |
| --- | --- |
| Frequencia do barramento | 100 kHz |
| Modo | Master |
| Pull-ups externos | Necessarios/recomendados em SDA e SCL |

## O que foi implementado

- Driver basico `twi.c/h` para iniciar, escrever e ler bytes no barramento I2C/TWI.
- Leitura dos registradores de tempo do DS3231 a partir do endereco `0x00`.
- Conversao de BCD para decimal.
- Retorno de horario fallback caso o RTC nao responda.

## Formato lido

O DS3231 armazena os campos de tempo em BCD:

```text
segundo, minuto, hora, dia_da_semana, dia, mes, ano
```

O firmware usa:

```text
ano, mes, dia, hora, minuto, segundo
```

## Limitacoes atuais

- O firmware ainda nao ajusta a data/hora do RTC; apenas le.
- O driver ainda nao valida ranges de data/hora.
- Ainda falta teste com modulo fisico ou simulador configurado com RTC.
- Se o RTC nao responder, o sistema usa `2026-01-01T00:00:00` como fallback.
