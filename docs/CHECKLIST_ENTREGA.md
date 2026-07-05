# Checklist de Entrega

Data: 2026-07-05

## Itens solicitados no enunciado

| Item | Status | Onde esta |
| --- | --- | --- |
| Especificacao dos requisitos | Feito | `docs/REQUISITOS.md` |
| Diagrama de blocos do hardware | Feito | `docs/HARDWARE.md` |
| Arquitetura de software proposta | Feito | `docs/ARQUITETURA.md` |
| Esquematico simplificado | Feito | `docs/HARDWARE.md` |
| Implementacao em linguagem C | Feito | `src/` |
| Filtragem digital | Feito | `src/filter.c`, `docs/RELATORIO_TECNICO.md` |
| Protocolos de comunicacao | Feito | `docs/PROTOCOLO_COMUNICACAO.md` |
| Relatorio tecnico | Base criada | `docs/RELATORIO_TECNICO.md` |
| Relatorio individual | Base criada | `docs/RELATORIO_INDIVIDUAL.md` |

## Validacoes feitas

```text
powershell -ExecutionPolicy Bypass -File tools\test-all.ps1
```

Resultado:

```text
Build concluido com sucesso.
HEX: build/problema2.hex
PASS filtro passa-baixas
Todos os testes passaram.
```

## Pontos pendentes por dependerem de hardware

- Confirmar sensor de temperatura real e curva de conversao ADC -> unidade fisica.
- Confirmar circuito do LDR e curva de conversao.
- Testar sensor digital de umidade real.
- Testar sensor digital de chuva real.
- Validar DS3231 fisicamente no barramento I2C/TWI.
- Definir e testar o modulo sem fio real.
- Validar consumo de energia em campo.

## Observacao importante

O projeto esta fechado como base funcional e documental. Para uma entrega com prototipo fisico, os itens pendentes acima precisam ser validados em bancada.
