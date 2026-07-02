# Protocolo de Comunicacao Serial

Data: 2026-07-01

## Objetivo

Padronizar a forma como o data-logger transmite os registros ambientais pela interface de comunicacao.

Nesta etapa, a transmissao real implementada e pela USART do ATmega328P. O modo sem fio ainda e um stub, mas reutiliza o mesmo formato de dados para manter compatibilidade futura.

## Configuracao USART

| Parametro | Valor inicial |
| --- | --- |
| Baud rate | 9600 bps |
| Bits de dados | 8 |
| Paridade | Nenhuma |
| Stop bits | 1 |
| Fluxo | Sem controle de fluxo |

## Formato escolhido

Foi escolhido um formato textual estilo CSV, por ser facil de ler em terminal serial e tambem facil de importar em planilhas.

Cabecalho enviado ao iniciar:

```text
timestamp,temp_raw,temp_filt,light_raw,light_filt,humidity,rain,mode
```

Exemplo de registro:

```text
2026-01-01T00:00:00,512,500,730,710,1,0,USART
```

## Campos

| Campo | Descricao |
| --- | --- |
| `timestamp` | Data e hora no formato `AAAA-MM-DDTHH:MM:SS`. |
| `temp_raw` | Leitura bruta do ADC para o sensor de temperatura. |
| `temp_filt` | Leitura de temperatura apos filtro passa-baixas. |
| `light_raw` | Leitura bruta do ADC para o LDR. |
| `light_filt` | Leitura de luminosidade apos filtro passa-baixas. |
| `humidity` | Estado do sensor digital de umidade. |
| `rain` | Estado do sensor digital de chuva. |
| `mode` | Interface escolhida: `USART` ou `WIRELESS`. |

## Decisao tecnica

O formato CSV foi escolhido nesta etapa porque reduz complexidade. Um protocolo binario poderia ser mais eficiente, mas dificultaria a depuracao inicial. Como o objetivo agora e validar sensores, filtro e timestamp, legibilidade e mais importante que economia de bytes.
