# Plano de Trabalho

Data: 2026-06-07

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

Status: em andamento

- Confirmar componentes reais disponiveis:
  - modelo do RTC;
  - modelo do sensor de umidade;
  - modelo do modulo sem fio;
  - forma de armazenamento local, se houver.
- Definir mapa de pinos do ATmega328. Status: primeira versao criada.
- Definir periodo de amostragem.
- Definir formato do pacote de dados transmitido.

## Etapa 3 - Perifericos basicos

Status: planejada

- Testar leitura ADC do sensor de temperatura.
- Testar leitura ADC do LDR.
- Testar entradas digitais de umidade e chuva.
- Validar filtro passa-baixas com leituras simuladas ou reais.

## Etapa 4 - Comunicacao

Status: planejada

- Implementar transmissao USART completa.
- Definir protocolo textual ou binario.
- Testar envio dos registros.
- Definir e implementar driver do modulo sem fio.

## Etapa 5 - RTC e timestamp

Status: planejada

- Implementar comunicacao I2C/TWI.
- Ler data e hora do RTC.
- Associar timestamp aos registros do data-logger.

## Etapa 6 - Documentacao final

Status: planejada

- Relatorio em formato de artigo IEEE.
- Especificacao de requisitos.
- Diagrama de blocos.
- Arquitetura de software.
- Esquematico simplificado.
- Descricao da filtragem digital.
- Descricao dos protocolos de comunicacao.
- Relatorio individual.
