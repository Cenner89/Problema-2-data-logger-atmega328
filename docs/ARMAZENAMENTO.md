# Armazenamento Local

Data: 2026-07-05

## Objetivo

Atender ao requisito de armazenamento do data-logger, mantendo registros recentes mesmo antes da transmissao.

## Solucao adotada

Foi implementado um armazenamento circular simples usando a EEPROM interna do ATmega328P.

Arquivo principal:

```text
src/storage.c
src/storage.h
```

## Estrutura

O firmware reserva na EEPROM:

- uma palavra de identificacao (`STORAGE_MAGIC`);
- um indice de escrita;
- um vetor circular com os ultimos registros.

Quantidade inicial:

```text
STORAGE_MAX_RECORDS = 16
```

Quando o limite e atingido, o proximo registro sobrescreve o mais antigo.

## Por que EEPROM?

A EEPROM interna e simples de usar e permite manter dados mesmo sem energia. Para um prototipo academico, ela atende bem a demonstracao do conceito de data-logger.

## Limitacoes

- A EEPROM tem limite de ciclos de escrita.
- A capacidade e pequena.
- Para uso real em campo, o ideal seria avaliar memoria externa, cartao SD ou transmissao periodica para uma base remota.

## Proxima melhoria possivel

Adicionar uma rotina para ler e descarregar registros armazenados quando o usuario solicitar pela serial.
