# Plano de Trabalho

Data: 2026-07-05

## Etapa 1 - Base do projeto

Status: concluida

- Identificar o enunciado no Google Drive.
- Criar repositorio local e remoto no GitHub.
- Definir ferramenta recomendada: MPLAB X + XC8.
- Criar estrutura inicial de pastas.
- Criar requisitos iniciais.
- Criar arquitetura inicial.
- Criar firmware minimo em C.
- Criar script de build com XC8.
- Validar geracao de arquivo ELF e HEX.

## Etapa 2 - Requisitos e arquitetura detalhada

Status: concluida na proposta atual

- Confirmar componentes reais disponiveis:
  - modelo do RTC; Status: DS3231 assumido.
  - modelo do sensor de umidade;
  - modelo do modulo sem fio; Status: modulo serial Bluetooth sugerido para prototipo.
  - forma de armazenamento local, se houver. Status: EEPROM circular implementada.
- Definir mapa de pinos do ATmega328. Status: primeira versao criada.
- Definir periodo de amostragem. Status: 1 segundo.
- Definir formato do pacote de dados transmitido. Status: CSV textual.

## Etapa 3 - Perifericos basicos

Status: base implementada

- Testar leitura ADC do sensor de temperatura.
- Testar leitura ADC do LDR.
- Testar entradas digitais de umidade e chuva.
- Validar filtro passa-baixas com leituras simuladas ou reais. Status: teste automatico de logica criado.

## Etapa 4 - Comunicacao

Status: base implementada

- Implementar transmissao USART completa. Status: base criada.
- Definir protocolo textual ou binario. Status: CSV textual definido.
- Testar envio dos registros.
- Definir e implementar driver do modulo sem fio. Status: arquitetura definida; teste fisico pendente.

## Etapa 5 - RTC e timestamp

Status: base implementada

- Implementar comunicacao I2C/TWI. Status: base criada.
- Ler data e hora do RTC. Status: base DS3231 criada.
- Associar timestamp aos registros do data-logger. Status: integrado ao protocolo CSV.
- Validar leitura com modulo RTC real ou simulador.

## Etapa 6 - Documentacao final

Status: base criada

- Relatorio em formato de artigo IEEE.
- Especificacao de requisitos.
- Diagrama de blocos.
- Arquitetura de software.
- Esquematico simplificado.
- Descricao da filtragem digital.
- Descricao dos protocolos de comunicacao.
- Relatorio individual.
