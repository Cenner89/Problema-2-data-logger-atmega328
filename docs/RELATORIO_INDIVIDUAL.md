# Relatorio Individual

Aluno: Werner Pinheiro Guarana

## Descricao do problema

O Problema 2 propoe o desenvolvimento de um data-logger ambiental remoto baseado no ATmega328P. O sistema deve coletar dados de sensores analogicos e digitais, registrar data e hora com um RTC, aplicar filtragem digital aos sinais analogicos, armazenar os dados e permitir comunicacao serial ou sem fio.

## Estrategia adotada

A estrategia foi dividir o projeto em partes menores e modulares. Primeiro foi criada a estrutura do repositorio e a documentacao inicial. Depois foram implementados os blocos principais do firmware em C: leitura ADC, sensores, filtro, RTC, comunicacao USART, selecao de modo, armazenamento em EEPROM e rotina central do data-logger.

## Principais dificuldades

As maiores dificuldades estiveram na organizacao da arquitetura e na escolha das ferramentas. Como o projeto envolve varios perifericos, seria facil misturar tudo em um unico arquivo. Para evitar isso, cada responsabilidade foi separada em um modulo especifico.

Outro desafio foi preparar o projeto para ser testado sem depender totalmente do hardware. Por isso foram criados scripts de build e testes de logica, permitindo validar parte do funcionamento pelo computador.

## Contribuicao individual

Minha contribuicao principal foi acompanhar a definicao da arquitetura, organizar o projeto, revisar os requisitos, testar a compilacao e validar a evolucao do firmware. Tambem participei da interpretacao do enunciado e da construcao da documentacao tecnica.

## Aprendizados

O trabalho ajudou a consolidar conceitos de sistemas microprocessados, especialmente uso de ADC, comunicacao serial, I2C/TWI, RTC, filtros digitais, armazenamento em EEPROM e organizacao de firmware em linguagem C.
