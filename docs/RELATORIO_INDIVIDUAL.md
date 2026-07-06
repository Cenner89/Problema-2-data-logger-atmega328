# Relatório Individual

Aluno: Werner Pinheiro Guaraná

## Descrição do problema

O Problema 2 pedia um data-logger ambiental usando o ATmega328P. Pelo que entendi, a ideia era montar um sistema capaz de medir algumas grandezas do ambiente, salvar essas informações com data e hora e depois enviar os dados por algum tipo de comunicação.

Esse problema foi mais amplo que o anterior, porque não era só fazer uma conta ou uma rotina específica. Aqui o projeto precisava juntar várias partes: sensores, ADC, RTC, comunicação serial, comunicação sem fio, filtro digital, armazenamento e documentação.

## Estratégia usada

A estratégia foi começar organizando o projeto em partes menores. Em vez de colocar tudo em um único arquivo, separamos o código em módulos. Isso deixou o projeto mais fácil de acompanhar e também facilitou os testes.

Primeiro foi criada a estrutura do repositório e a documentação básica. Depois começamos o firmware em C, com os arquivos para ADC, sensores, filtro, comunicação, RTC e armazenamento. Também foi criado um script para compilar sem precisar abrir o MPLAB toda hora.

## Atividades realizadas

- Organização inicial do repositório no GitHub.
- Leitura e interpretação do enunciado.
- Definição da ferramenta de desenvolvimento.
- Criação da estrutura do firmware em C.
- Implementação da leitura ADC.
- Implementação do filtro passa-baixas.
- Implementação da comunicação serial em CSV.
- Implementação da base do RTC via I2C.
- Implementação de armazenamento simples em EEPROM.
- Criação de documentação do hardware, arquitetura e protocolo.
- Criação de teste automático para a lógica do filtro.

## Dificuldades encontradas

Uma dificuldade foi entender como dividir o projeto. No começo dava vontade de resolver tudo direto no `main.c`, mas isso deixaria o código confuso. Separar em módulos deu mais trabalho no início, mas depois fez mais sentido.

Outra dificuldade foi lidar com as partes que dependem de hardware real. Por exemplo, o código do RTC compila, mas o teste de verdade depende de conectar um DS3231. A mesma coisa vale para sensores e módulo sem fio.

Também foi necessário entender melhor a diferença entre compilar e realmente validar o sistema. O código pode compilar e gerar o HEX, mas isso não significa que todos os sensores já foram testados fisicamente.

## Minha contribuição

Minha contribuição foi principalmente acompanhar a construção do projeto, organizar os arquivos, revisar os requisitos e entender o que precisava ser implementado. Também participei da parte de documentação e da validação por compilação.

A parte mais importante foi ajudar a transformar o enunciado em uma estrutura de projeto que desse para continuar desenvolvendo, em vez de deixar tudo solto.

## Aprendizados

Com esse trabalho, entendi melhor como um projeto embarcado em C pode ser organizado. Também ficou mais claro como o ATmega usa periféricos como ADC, USART, I2C e EEPROM.

Outro aprendizado foi perceber que nem tudo precisa estar perfeito logo de primeira. Em sistemas embarcados, muita coisa começa como uma base, depois vai sendo testada e ajustada com o hardware real.

## Conclusão pessoal

No geral, o projeto ajudou bastante a entender como juntar programação, eletrônica e documentação. Ainda existem testes físicos para fazer, mas a base ficou montada e dá para explicar bem as escolhas feitas.
