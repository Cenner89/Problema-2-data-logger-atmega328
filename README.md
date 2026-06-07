# Problema 2 - Data-Logger Ambiental com ATmega328

Projeto da disciplina **ENGC50 - Sistemas Microprocessados**.

## Enunciado

O Problema 2 pede o projeto de um **data-logger inteligente para monitoramento ambiental remoto**, baseado no microcontrolador **ATmega328**.

O sistema deve coletar dados de sensores analogicos e digitais, associar cada medicao a data e hora fornecidas por um modulo RTC, aplicar filtragem digital passa-baixas aos sinais analogicos e transmitir os dados por uma das interfaces de comunicacao escolhidas antes da instalacao.

Arquivo identificado no Google Drive:

- Pasta: `SIS. MICRO`
- Arquivo: `Problema_2.pdf`
- Link: <https://drive.google.com/file/d/1xeA109JW6AHksmDu9G5GhFkz9XFjbPc3/view>

## Requisitos principais

- Usar linguagem C para microcontrolador.
- Utilizar o ATmega328 como base do sistema.
- Ler sensores analogicos:
  - sensor de temperatura com saida em tensao;
  - sensor de luminosidade baseado em LDR.
- Ler sensores digitais:
  - sensor digital de umidade relativa do ar;
  - sensor digital de presenca de chuva.
- Associar as medicoes a data e hora usando um RTC externo.
- Aplicar filtro digital passa-baixas nas medicoes analogicas.
- Implementar duas opcoes de comunicacao:
  - USART serial do ATmega328;
  - comunicacao sem fio usando modulo apropriado.
- Organizar o projeto de forma modular e de facil manutencao.

## Entregas previstas

- Relatorio tecnico no formato de artigo, seguindo padrao IEEE.
- Documentacao do sistema:
  - especificacao de requisitos;
  - diagrama de blocos do hardware;
  - arquitetura de software;
  - esquematico simplificado;
  - implementacao em linguagem C;
  - descricao da filtragem digital;
  - descricao dos protocolos de comunicacao.
- Relatorio individual com descricao do problema, estrategia de solucao, dificuldades e contribuicao individual.

## Estrutura inicial

```text
docs/   Documentacao, requisitos e anotacoes do projeto
src/    Codigo-fonte em C para o ATmega328
tools/  Scripts auxiliares de build, teste ou simulacao
```

## Ferramenta recomendada

A avaliacao inicial aponta como melhor caminho:

```text
MPLAB X + MPLAB XC8
```

Motivo: o Problema 2 pede implementacao em linguagem C, uso de perifericos do ATmega328, modularizacao, documentacao e testes. O Microchip Studio continua sendo uma alternativa valida, mas o MPLAB X com XC8 esta mais alinhado para iniciar um projeto novo em C.

Ver detalhes em:

- `docs/AVALIACAO_FERRAMENTAS.md`

## Status

Repositorio local e remoto iniciados. O proximo passo e criar a especificacao dos requisitos do sistema e definir a arquitetura inicial do firmware.
