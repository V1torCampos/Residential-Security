# Sistema de Segurança Residencial com ESP32, FreeRTOS e Blynk

Este é um projeto que visa criar um sistema de segurança residencial eficiente e fácil de usar, utilizando o ESP32, FreeRTOS e Blynk. O sistema envolve a integração de sensores de movimento e abertura, um teclado para inserção de senha e a plataforma Blynk para monitoramento e controle remoto


## Funcionalidades

O ESP32 é responsável por executar várias tarefas em paralelo, permitindo um funcionamento integrado do sistema. Aqui estão as principais funcionalidades do sistema de segurança residencial:

* Sensores de Movimento e Abertura: O sistema faz uso de sensores de movimento e sensores de abertura para detectar atividades suspeitas na residência. Uma tarefa específica no ESP32 é responsável por ler constantemente esses sensores e, quando o sistema está habilitado, caso algum dos sensores seja acionado, o alarme é disparado e uma atualização é enviada para a plataforma Blynk.

* Teclado para Inserção de Senha: O sistema também inclui um teclado que permite aos usuários inserir uma senha para habilitar ou desabilitar o sistema de segurança. Uma tarefa separada no ESP32 lê a senha digitada e verifica sua corretude. Se a senha estiver correta, o estado do sistema é alterado conforme desejado. Caso contrário, o alarme é disparado.

* Integração com a Plataforma Blynk: A plataforma Blynk é utilizada para o monitoramento e controle remoto do sistema de segurança residencial. Quando ocorre uma atividade suspeita ou quando o estado do sistema é alterado, uma atualização é enviada para o Blynk, permitindo que os usuários recebam notificações em tempo real e monitorem o status do sistema por meio de dispositivos móveis.
## Configuração e Uso

Para configurar e utilizar este sistema de segurança residencial, siga as instruções abaixo:

## 1 Hardware necessário:

* ESP32 (ou placa compatível)
* Sensores de movimento(PIR) e abertura(Sensor magnético xas)
* Teclado
* Dispositivos móveis com suporte à plataforma Blynk (https://play.google.com/store/apps/details?id=cloud.blynk&hl=pt_BR&gl=US)

## Instalação do software:

* Faça o download e instale a IDE do Arduino (https://www.arduino.cc/en/software)
* Instale o suporte ao ESP32 na IDE do Arduino, seguindo as instruções fornecidas pela documentação oficial (https://github.com/espressif/arduino-esp32)

## Configuração do projeto:

* Clone ou faça o download do repositório do projeto.
* Abra o arquivo do projeto na IDE do Arduino.
* Conecte o ESP32 ao computador por meio de um cabo USB.

## Configuração do Blynk:

* Crie uma conta no Blynk (https://blynk.io/) e crie um novo projeto.
* Anote o token de autenticação do projeto Blynk.

## Configuração do código:

* Abra o arquivo do projeto que contém o código fonte.
* Procure pela seção de configuração e insira o token de autenticação do projeto Blynk.

## Compilação e upload:

* Verifique se o ESP32 está corretamente selecionado como placa na IDE do Arduino.
* Compile o código para verificar se não há erros.
* Conecte o ESP32 ao computador por meio de um cabo USB.
* Selecione a porta correta na IDE do Arduino.
* Faça o upload do código para o ESP32.

## Montagem do hardware:

* Conecte os sensores de movimento e abertura aos pinos especificados no código.
* Conecte o teclado aos pinos correspondentes.
* Verifique as conexões e certifique-se de que todos os componentes estão corretamente conectados ao ESP32.

## Inicialização e utilização:

* Alimente o ESP32 com uma fonte de energia adequada.
* O sistema de segurança residencial será inicializado e estará pronto para uso.
* Utilize o aplicativo Blynk em seus dispositivos móveis para monitorar e controlar o sistema remotamente.
* Insira a senha correta no teclado para habilitar ou desabilitar o sistema.
* Monitore as notificações do Blynk para atividades suspeitas e atualizações de status do sistema.
