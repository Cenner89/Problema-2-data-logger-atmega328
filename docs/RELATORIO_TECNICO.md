# Relatório Técnico - Problema 2

## Título

Projeto de um Data-Logger Ambiental usando ATmega328P

## Resumo

Neste trabalho foi desenvolvido um protótipo inicial de um data-logger ambiental usando o microcontrolador ATmega328P. A ideia principal foi montar um sistema capaz de ler sensores, colocar data e hora nas medições, aplicar um filtro simples para diminuir ruído e depois enviar os dados por comunicação serial. Também deixamos prevista uma opção de comunicação sem fio, pensando em um módulo serial sem fio, como um Bluetooth HC-05 ou outro equivalente.

O projeto foi feito em linguagem C, porque o problema pede isso e também porque seria muito trabalhoso fazer tudo em Assembly, principalmente por envolver ADC, RTC, comunicação, filtro e armazenamento. A implementação ainda precisaria ser testada com os sensores reais, mas a base do firmware já compila e gera o arquivo HEX.

## 1. Ideia geral do problema

O problema pede um equipamento para monitoramento ambiental remoto. Na prática, seria uma placa que fica em campo coletando informações, como temperatura, luminosidade, umidade e presença de chuva. Cada medição precisa ter data e hora, para depois ser possível saber quando cada evento aconteceu.

Como os sensores analógicos podem apresentar ruído, também foi necessário incluir algum tipo de filtragem digital. Além disso, o sistema deveria ter duas formas de comunicação: uma versão por cabo serial e outra sem fio.

## 2. O que foi implementado

O firmware foi dividido em vários arquivos para não ficar tudo misturado no `main.c`. A organização ficou assim:

- `adc`: faz a leitura dos canais analógicos;
- `filter`: aplica o filtro passa-baixas;
- `sensors`: junta as leituras dos sensores;
- `rtc`: lê data e hora do RTC;
- `twi`: faz a comunicação I2C/TWI usada pelo RTC;
- `storage`: salva registros na EEPROM interna;
- `usart`: cuida da transmissão serial;
- `comm`: monta o pacote de dados no formato CSV;
- `mode_select`: escolhe o modo serial ou sem fio por jumper;
- `datalogger`: junta tudo e controla a sequência principal.

Essa separação ajudou bastante, porque cada parte ficou com uma função mais clara.

## 3. Sensores

Foram considerados dois sensores analógicos:

- temperatura no canal ADC0;
- luminosidade com LDR no canal ADC1.

Também foram previstas duas entradas digitais:

- sensor de umidade;
- sensor de chuva.

Como ainda não temos os modelos exatos dos sensores, o código trabalha com valores brutos do ADC. A conversão para unidades físicas, como graus Celsius ou porcentagem, deve ser feita depois, quando os sensores reais forem definidos.

## 4. Filtro digital

Para reduzir oscilações nas leituras analógicas, foi usado um filtro passa-baixas simples. A fórmula usada foi:

```text
y = y + ((x - y) >> FILTER_SHIFT)
```

Esse filtro é simples, mas já ajuda a suavizar mudanças bruscas. Também evita o uso de número de ponto flutuante, o que é melhor para o ATmega328P.

## 5. RTC

Para data e hora, foi assumido o uso do módulo DS3231, que é um RTC comum e relativamente preciso. Ele se comunica por I2C/TWI usando os pinos:

- SDA em PC4;
- SCL em PC5.

O firmware já possui uma base para ler o horário do DS3231. Se o RTC não responder, o programa usa um horário padrão só para não travar o funcionamento.

## 6. Comunicação

A comunicação foi feita em formato CSV, porque é fácil de ler no terminal serial e também pode ser aberto em planilhas. O cabeçalho usado foi:

```text
timestamp,temp_raw,temp_filt,light_raw,light_filt,humidity,rain,mode
```

Um exemplo de linha transmitida seria:

```text
2026-01-01T00:00:00,512,500,730,710,1,0,USART
```

Para a parte sem fio, a ideia inicial foi manter o mesmo protocolo e usar um módulo serial sem fio. Assim, a lógica do código muda pouco.

## 7. Armazenamento

Também foi implementado um armazenamento simples usando a EEPROM interna do ATmega328P. Ele guarda os últimos registros em forma circular. Quando chega no limite, os dados mais antigos começam a ser sobrescritos.

Essa solução não é perfeita para um produto real, porque a EEPROM tem pouco espaço e limite de escritas, mas serve bem para demonstrar a ideia do data-logger no contexto do trabalho.

## 8. Testes feitos

Foi criado um script para compilar o projeto com o XC8 e gerar o arquivo HEX. Também foi feito um teste simples do filtro passa-baixas fora do hardware.

O resultado final foi:

```text
Build concluido com sucesso.
HEX: build/problema2.hex
PASS filtro passa-baixas
Todos os testes passaram.
```

## 9. Limitações

Apesar da base estar pronta, algumas coisas ainda dependem de teste em bancada:

- testar o RTC DS3231 real;
- calibrar os sensores analógicos;
- confirmar o comportamento dos sensores digitais;
- escolher e testar o módulo sem fio;
- avaliar se a EEPROM interna é suficiente para o uso desejado.

## 10. Conclusão

O projeto ficou com uma base funcional e organizada para o data-logger. O código compila, gera HEX e já possui os blocos principais pedidos no problema: sensores, filtro, RTC, comunicação e armazenamento.

Ainda não dá para dizer que o sistema foi validado em campo, porque faltam os testes físicos. Mesmo assim, para a proposta do trabalho, a estrutura principal foi montada e documentada.
