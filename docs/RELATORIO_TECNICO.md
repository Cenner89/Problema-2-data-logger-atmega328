# Projeto de um Data-Logger Inteligente para Monitoramento Ambiental Remoto Utilizando o Microcontrolador ATmega328P

Werner Pinheiro Guaraná
Departamento de Engenharia Elétrica e de Computação
Universidade Federal da Bahia
Salvador, Brasil

## Resumo

Este trabalho apresenta o desenvolvimento de uma base de firmware para um data-logger ambiental usando o microcontrolador ATmega328P. O sistema foi pensado para coletar dados de sensores analógicos e digitais, associar cada medição a data e hora usando um RTC externo, aplicar um filtro digital passa-baixas nas leituras analógicas e transmitir os registros por comunicação serial. Também foi incluída uma estrutura inicial para comunicação sem fio, usando a mesma lógica de envio dos dados.

Além disso, foi implementado um armazenamento simples em EEPROM interna, com funcionamento circular, para manter os registros mais recentes. O projeto foi desenvolvido em linguagem C e organizado em módulos, facilitando a manutenção e a continuação do trabalho. A base foi validada por compilação com MPLAB XC8 e por um teste simples da lógica do filtro. Ainda assim, algumas partes precisam de validação em bancada, principalmente sensores reais, RTC físico e módulo sem fio.

**Palavras-chave** — ATmega328P, Data-Logger, Sistemas Embarcados, Monitoramento Ambiental, RTC, EEPROM, Filtragem Digital.

## I. INTRODUÇÃO

O monitoramento ambiental é importante em aplicações como agricultura, acompanhamento climático, preservação ambiental e análise de áreas remotas. Em muitos casos, a coleta desses dados ainda é feita manualmente, o que pode gerar atrasos, diferenças nos horários das medições e até perda de informação.

A proposta deste trabalho foi montar a base de um sistema embarcado capaz de registrar variáveis ambientais automaticamente. Para isso, foi usado o ATmega328P como microcontrolador principal. O sistema faz leitura de sensores, processa os dados, associa data e hora às medições e transmite as informações em formato simples.

O desenvolvimento foi feito em C, pois o problema pediu essa linguagem e porque ela facilita bastante a organização do firmware quando comparada com Assembly. Como o projeto envolve vários periféricos, como ADC, USART, I2C e EEPROM, separar o código em módulos foi uma decisão importante.

## II. ARQUITETURA DO SISTEMA

A arquitetura do sistema foi pensada de forma modular. O ATmega328P fica responsável por fazer a leitura dos sensores, aplicar o filtro, buscar data e hora no RTC, armazenar os dados na EEPROM e enviar os registros por comunicação serial ou sem fio.

Foram considerados quatro sensores ambientais. Os sensores de temperatura e luminosidade são tratados como analógicos e ligados ao ADC. Já os sensores de umidade e chuva são tratados como digitais, usando entradas GPIO do microcontrolador.

Depois da leitura, os valores analógicos passam por um filtro digital passa-baixas. Em seguida, o registro recebe o timestamp vindo do RTC DS3231. Por fim, os dados são armazenados na EEPROM e enviados no formato CSV.

**Fig. 1.** Diagrama de blocos da arquitetura proposta: sensores analógicos e digitais conectados ao ATmega328P; RTC DS3231 via I2C/TWI; armazenamento em EEPROM; comunicação por USART ou módulo sem fio.

## III. Implementação do Sistema

A implementação foi organizada em arquivos separados para deixar o projeto mais fácil de entender. No começo até daria para colocar tudo em um arquivo só, mas isso deixaria o `main.c` muito grande e confuso. Como o projeto tem sensor, filtro, RTC, comunicação e armazenamento, separar por função acabou sendo mais organizado.

Na prática, o `main.c` fica quase só chamando o data-logger. Quem coordena o sistema é o módulo `datalogger`, mostrado no trecho abaixo. Ele pega o horário, lê os sensores, salva o registro e envia os dados.

```c
void datalogger_run_once(void)
{
    log_record_t record;

    (void)rtc_get_time(&record.timestamp);
    sensors_read(&record.sensors);
    (void)storage_save_record(&record);
    comm_send_record(&record);
}
```

Essa divisão não foi feita para deixar o código "mais bonito" apenas. Ela ajuda bastante na hora de mexer no projeto, porque se der problema na comunicação, por exemplo, não é preciso procurar no meio do código do ADC ou do filtro.

### A. Aquisição de Dados

A aquisição dos dados foi dividida entre sensores analógicos e digitais. Os sensores analógicos usam o ADC do ATmega328P. Nesta proposta, o sensor de temperatura foi colocado no canal ADC0 e o sensor de luminosidade, baseado em LDR, no canal ADC1.

Os sensores digitais de umidade e chuva foram configurados como entradas digitais. Para evitar entradas flutuantes durante os testes, foram usados pull-ups internos. Como ainda não foram definidos os modelos exatos dos sensores, o firmware trabalha inicialmente com valores brutos.

### B. Filtragem Digital

Os sensores analógicos podem apresentar oscilações por ruído elétrico ou variações pequenas do próprio circuito. Para suavizar isso, foi implementado um filtro digital passa-baixas do tipo IIR simples.

A fórmula usada foi:

```text
y = y + ((x - y) >> FILTER_SHIFT)
```

No código, essa ideia aparece de forma bem direta:

```c
delta = (int16_t)sample - (int16_t)filter->value;
filter->value = (uint16_t)((int16_t)filter->value + (delta >> FILTER_SHIFT));
```

Essa escolha evita o uso de ponto flutuante e usa apenas operações inteiras, o que combina melhor com o ATmega328P. No projeto, `FILTER_SHIFT` foi definido como 3, equivalente a uma suavização aproximada de 1/8 da diferença entre a nova leitura e o valor filtrado anterior.

### C. Gerenciamento de Data e Hora

Para registrar o instante de cada medição, foi adotado o RTC DS3231. Ele se comunica com o ATmega328P pelo barramento I2C/TWI, usando os pinos PC4 para SDA e PC5 para SCL.

O firmware lê os registradores do DS3231, converte os valores de BCD para decimal e monta uma estrutura com ano, mês, dia, hora, minuto e segundo. Caso o RTC não responda, o sistema usa um horário padrão, apenas para permitir que o restante do firmware continue funcionando.

### D. Armazenamento dos Dados

Os registros são armazenados na EEPROM interna do ATmega328P. Foi usada uma estratégia circular: quando o número máximo de registros é atingido, os dados novos passam a sobrescrever os mais antigos.

Essa solução não é a mais completa para um produto real, porque a EEPROM tem pouco espaço e limite de ciclos de escrita. Mesmo assim, ela atende bem à proposta do trabalho, pois demonstra o funcionamento básico de um data-logger sem precisar de memória externa.

### E. Comunicação

A comunicação foi organizada em duas camadas. O módulo `usart` cuida diretamente da transmissão serial, enquanto o módulo `comm` monta os registros no formato definido.

O formato escolhido foi CSV, porque é fácil de visualizar em um terminal serial e também pode ser importado em planilhas. O cabeçalho enviado pelo sistema é:

```text
timestamp,temp_raw,temp_filt,light_raw,light_filt,humidity,rain,mode
```

Um exemplo de registro seria:

```text
2026-01-01T00:00:00,512,500,730,710,1,0,USART
```

Um trecho simplificado da montagem do registro é:

```c
comm_send_timestamp(record);
usart_send_char(',');
usart_send_uint16(record->sensors.temperature_raw);
usart_send_char(',');
usart_send_uint16(record->sensors.temperature_filtered);
```

Para a comunicação sem fio, a ideia foi manter o mesmo formato de dados e usar um módulo compatível com comunicação serial, como um módulo Bluetooth. Assim, o firmware muda pouco entre a versão com cabo e a versão sem fio.

## Conclusão

O projeto resultou em uma base funcional para um data-logger ambiental com ATmega328P. Foram implementados os principais blocos pedidos no problema: leitura de sensores, filtro digital, RTC, armazenamento, comunicação e seleção da interface.

O firmware compila com MPLAB XC8 e gera o arquivo HEX. Também foi criado um teste simples para validar a lógica do filtro passa-baixas. Apesar disso, ainda faltam testes físicos com sensores reais, RTC DS3231 conectado e módulo sem fio. Portanto, o trabalho está fechado como uma base de projeto organizada e pronta para validação em bancada.

## Referências

[1] Microchip Technology Inc., ATmega328P Datasheet.
[2] Microchip Technology Inc., MPLAB XC8 C Compiler User's Guide.
[3] Analog Devices / Maxim Integrated, DS3231 Extremely Accurate I2C-Integrated RTC.
[4] M. A. Mazidi, S. Naimi, S. Naimi, The AVR Microcontroller and Embedded Systems Using Assembly and C.
[5] Material da disciplina ENGC50 - Sistemas Microprocessados, 2026.1.
