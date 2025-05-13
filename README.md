# CHECKPOINT 03 - PROTOCOLO MQTT COM ESP32
**Disciplina:** Disruptive Architectures: IOT, IOB & Generative AI  
**Professor:** André Tritiack  
**Turmas de Fevereiro:** 2TDSPF, 2TDSPJ, 2TDSPK, 2TDSPV, 2TDSPX, 2TDSPY  
**Turmas de Agosto:** 2TDSZ, 2TDSPA, 2TDSPC, 2TDSPR, 2TDSPS  

---

## FORMATO DA ENTREGA:
A entrega deve conter os seguintes elementos:  
1. Link do repositório no GitHub contendo todos os arquivos do projeto.  
2. Link para um vídeo curto (máximo 3 minutos) demonstrando a aplicação funcionando. O vídeo deve mostrar:  
   - Os dados sendo enviados e visualizados no **Monitor Serial do VSCode ou Arduino IDE**.  
   - A visualização dos dados no **NodeRED**.  
3. Arquivo `integrantes.txt` contendo os nomes completos dos integrantes.  

---

## USO DOS KITS DOIT ESP32 DEVKIT V1 NO LABORATÓRIO:

As aulas entre os dias **12 e 20 de maio** poderão ser utilizadas para o desenvolvimento da atividade do CP3 no laboratório, utilizando as placas **ESP32 DEVKIT v1** disponíveis para os grupos.  
Os alunos que optarem por realizar a atividade remotamente podem utilizar o Wokwi integrado ao PlatformIO (tutorial está incluído abaixo)

---

## OBJETIVO DA ATIVIDADE:
Implementar um sistema de comunicação IoT utilizando o protocolo MQTT com ESP32. A atividade será realizada em duas etapas:  

1. Criação de uma máquina virtual Linux na Azure, com instalação do NodeRED e Mosquitto Broker.  
2. Envio de dados simulados (temperatura, umidade, pressão e altitude) utilizando o protocolo MQTT no ESP32.  

A atividade pode ser realizada em grupos de até **3 integrantes**. Apenas um aluno por grupo deve enviar os links do repositório, vídeo e o arquivo `.txt` com os nomes dos integrantes.

---

## ORIENTAÇÕES GERAIS:
- A atividade deve ser organizada em um repositório no GitHub, com um README detalhado.
- Estrutura do repositório:
  - README.md (Instruções detalhadas do projeto)
  - esp32_mqtt.ino (Código base ajustado com credenciais)
  - integrantes.txt (Nome dos integrantes e link da máquina virtual)

---

## OPÇÃO DE DESENVOLVIMENTO NO PLATFORMIO COM WOKWI (VSCode)

Os alunos também podem optar por simular o projeto utilizando o PlatformIO com Wokwi no VSCode. Essa opção é recomendada para aqueles que não possuem o hardware DOIT ESP32 DEVKIT V1.

### **INSTALAÇÃO DA EXTENSÃO PlatformIO:**

1. No VSCode, abra a aba de extensões (`Ctrl+Shift+X`) e instale a extensão **PlatformIO IDE**.
2. Instale também a extensão **Wokwi Simulator**.

# Projeto IoT com ESP32 e MQTT Simulado no Wokwi

## Descrição

Este projeto demonstra como configurar um ESP32 para conectar-se a uma rede Wi-Fi e enviar e receber dados via MQTT. A simulação é realizada no [Wokwi](https://wokwi.com/), um simulador online de hardware. O desenvolvimento é feito utilizando o Visual Studio Code com a extensão PlatformIO.

## Adaptação

Esse repositório é uma adaptação deste tutorial.[https://docs.google.com/document/d/1y6IfbOT_rAimZx41tNBL9NlscoB1ObjgaPmy2g4UGO0/edit?usp=sharing](https://docs.google.com/document/d/1y6IfbOT_rAimZx41tNBL9NlscoB1ObjgaPmy2g4UGO0/edit?usp=sharing) 


## Funcionalidades

- **Conexão Wi-Fi**: O ESP32 conecta-se automaticamente à rede Wi-Fi especificada.
- **Comunicação MQTT**: Envia e recebe mensagens através de um broker MQTT.
- **Simulação no Wokwi**: Permite testar o projeto sem a necessidade de hardware físico.

## Pré-requisitos

- [Visual Studio Code](https://code.visualstudio.com/)
- [PlatformIO IDE](https://platformio.org/install/ide?install=vscode)
- Conta no [Wokwi](https://wokwi.com/)
- Broker MQTT (como o [Mosquitto](https://mosquitto.org/) ou serviços online como o [HiveMQ](https://www.hivemq.com/))

## Instalação

1. **Clone o repositório:**

   ```bash
   git clone https://github.com/arnaldojr/iot-esp32-wokwi-vscode.git
   ```

2. Abra o projeto no VSCode:

    Abra o Visual Studio Code e navegue até a pasta do projeto clonado.

3. Instale as dependências:

    O PlatformIO irá instalar automaticamente as bibliotecas necessárias durante a primeira compilação.

## Configuração

Credenciais Wi-Fi e MQTT:

No arquivo src/main.cpp, insira suas credenciais de Wi-Fi e as informações do broker MQTT:

```cpp

// Configurações de WiFi
const char *SSID = "Wokwi-GUEST"; // não precisa alterar no simulador
const char *PASSWORD = "";        // 

// Configurações de MQTT
const char *BROKER_MQTT = "broker.hivemq.com"; // seu broker mqtt
const int BROKER_PORT = 1883;
const char *ID_MQTT = "esp32_mqtt";
const char *TOPIC_SUBSCRIBE_LED = "fiap/iot/led";  // seu topico SUB
const char *TOPIC_PUBLISH_TEMP_HUMI = "fiap/iot/temphumi"; // seu tópico PUB
```

## Uso

1. Compilar o projeto:

No PlatformIO, clique em Build para compilar o código.

2. Iniciar a simulação:

- No Wokwi, inicie a simulação.
- Observe a saída serial para verificar a conexão Wi-Fi e a comunicação MQTT.

3. Testar a comunicação MQTT:

- Use um cliente MQTT (como o node-red) para publicar e subscrever tópicos para interagir com o ESP32.

4. Simulação Dicas:

- O Wokwi permite simular o comportamento do ESP32 em tempo real, mas preste atenção no tempo de execução que pode variar e ficar lento:
- Utilize o monitor serial para acompanhar os logs da aplicação.

  ## PARTE 1: CRIAÇÃO DA MÁQUINA VIRTUAL LINUX NA AZURE

1. Acesse o portal Azure: [https://portal.azure.com](https://portal.azure.com)  
2. Crie um recurso do tipo **Máquina Virtual** utilizando a imagem **Ubuntu Server 20.04 LTS**.
3. Configure as portas de acesso:
   - SSH: 22
   - HTTP: 80

4. Crie uma regra de entrada para a liberação das portas 1880 (NodeRED) e 1883 (Broker).  

# INSTALAÇÃO E ATUALIZAÇÃO DO NODE.JS PARA NODE-RED (v18 ou Superior)

Acesse a máquina virtual via SSH:

bash
ssh usuario@ip_da_vm


---

## 1. Remover versões antigas do Node.js

Antes de instalar a nova versão do Node.js, é recomendado remover versões anteriores para evitar conflitos:

bash
sudo apt remove -y nodejs npm
sudo apt autoremove -y


---

## 2. Atualizar os pacotes do sistema

bash
sudo apt update && sudo apt upgrade -y


---

## 3. Instalar Node.js v18.x

- Adicione o repositório NodeSource:

bash
curl -fsSL https://deb.nodesource.com/setup_18.x | sudo -E bash -


- Instale o Node.js:

bash
sudo apt install -y nodejs


- Verifique a versão instalada:

bash
node -v
npm -v


---

## 4. Instalar o Node-RED

bash
sudo npm install -g --unsafe-perm node-red


---

## 5. Iniciar o Node-RED

bash
node-red


Acesse o Node-RED no navegador em:  
http://ip_da_vm:1880

---

Agora o Node.js está atualizado para a versão v18, compatível com a versão atual do Node-RED.

# Instalação e Teste do Mosquitto Broker na CLI da Azure

## Pré-requisitos
- Sistema operacional Linux (Ubuntu ou similar)
- Acesso à CLI da Azure
- Permissões de administrador

---

## 1. Instalação do Mosquitto Broker

Execute os comandos abaixo para instalar o Mosquitto Broker e o cliente Mosquitto:

bash
sudo apt update
sudo apt install -y mosquitto mosquitto-clients


Habilite o serviço para iniciar automaticamente:

bash
sudo systemctl enable mosquitto


Inicie o serviço:

bash
sudo systemctl start mosquitto


Verifique o status do serviço:

bash
sudo systemctl status mosquitto


---

## 2. Configuração do Mosquitto para Acesso Local

Abra o arquivo de configuração do Mosquitto:

bash
sudo nano /etc/mosquitto/mosquitto.conf


Adicione as seguintes linhas ao final do arquivo:

plaintext
listener 1883
allow_anonymous true


Salve e saia do editor (Ctrl + X, Y, Enter).

Reinicie o serviço para aplicar as configurações:

bash
sudo systemctl restart mosquitto


---

## 3. Teste do Mosquitto Broker

Abra um terminal e execute o seguinte comando para se inscrever no tópico teste:

bash
mosquitto_sub -h localhost -t teste -v


Em outro terminal, publique uma mensagem para testar a conexão:

bash
mosquitto_pub -h localhost -t teste -m "Testando conexão no Mosquitto Broker"


Você deverá ver a mensagem recebida no terminal do mosquitto_sub.

---

## 4. Depuração e Solução de Problemas

Se a mensagem não aparecer no terminal do mosquitto_sub, execute o comando com a flag -d para depurar:

bash
mosquitto_sub -h localhost -t teste -v -d


Verifique também o status do serviço:

bash
sudo systemctl status mosquitto


Em caso de problemas de conexão, verifique o arquivo de log do Mosquitto:

bash
sudo tail -f /var/log/mosquitto/mosquitto.log

---

## PARTE 2: ENVIO DE DADOS SIMULADOS VIA MQTT NO ESP32

- Utilizando o código base `esp32_mqtt.ino`, ajuste as credenciais e defina os tópicos MQTT.
- Os dados enviados devem incluir:
  - Temperatura: 20°C a 35°C
  - Umidade: 40% a 80%
  - Pressão: 980 hPa a 1050 hPa
  - Altitude: 0 m a 500 m

### INSTRUÇÕES PARA AJUSTE DO CÓDIGO:
- Informe as credenciais no código nas seções marcadas como **INSIRA AQUI**.
- Verifique o IP da máquina virtual e ajuste o broker MQTT no código.

---








## REFERÊNCIAS:
- [Documentação do ESP32](https://docs.espressif.com/projects/esp-idf/en/latest/esp32/)
- [Documentação do NodeRED](https://nodered.org/docs/)
- [Mosquitto MQTT](https://mosquitto.org/documentation/)
- [PlatformIO IDE](https://platformio.org/)
- [Wokwi ESP32 Simulator](https://wokwi.com/)
