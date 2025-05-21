# CHECKPOINT 03 - PROTOCOLO MQTT COM ESP32
**Disciplina:** Disruptive Architectures: IOT, IOB & Generative AI  
**Professor:** André Tritiack

---

## FORMATO DA ENTREGA:

1. Link do repositório no GitHub contendo todos os arquivos do projeto.
2. Link para um vídeo curto (máximo 3 minutos) demonstrando a aplicação funcionando.
3. Arquivo `integrantes.txt` contendo os nomes completos dos integrantes.

---

## OBJETIVO DA ATIVIDADE:

Implementar um sistema de comunicação IoT utilizando o protocolo MQTT com ESP32. A atividade será dividida em **duas partes:**

1. Criação da infraestrutura na Azure, com instalação do NodeRED e Mosquitto Broker.
2. Envio de dados simulados utilizando um ESP32 programado no PlatformIO e simulado no Wokwi.

A atividade pode ser realizada em grupos de até **3 integrantes**.

---

## PARTE 1: CRIAÇÃO DA INFRAESTRUTURA NA AZURE

### 1. Criação da Máquina Virtual
- Acesse o portal Azure: [https://portal.azure.com](https://portal.azure.com).
- Crie um recurso do tipo **Máquina Virtual** com a imagem **Ubuntu Server 20.04 LTS**.

**Configuração das portas:**
- SSH: 22
- HTTP: 80
- MQTT: 1883
- NodeRED: 1880

Acesse a máquina virtual via SSH:

```bash
ssh usuario@SEU_IP_VM_AZURE
```

Atualize os pacotes:

```bash
sudo apt update && sudo apt upgrade -y
```

---

### 2. Instalação do Node.js e Node-RED

Remova versões antigas:

```bash
sudo apt remove -y nodejs npm
sudo apt autoremove -y
```

Instale o Node.js:

```bash
curl -fsSL https://deb.nodesource.com/setup_18.x | sudo -E bash -
sudo apt install -y nodejs
```

Instale o Node-RED:

```bash
sudo npm install -g --unsafe-perm node-red
```

Inicie o Node-RED:

```bash
node-red
```

Acesse o Node-RED em: `http://SEU_IP_VM_AZURE:1880`

---

### 3. Instalação do Mosquitto Broker

Instale o Mosquitto Broker e os clientes MQTT:

```bash
sudo apt install -y mosquitto mosquitto-clients
```

Crie um usuário MQTT:

Substitua "admin" pelo usuario que quer criar.

```bash
sudo mosquitto_passwd -c /etc/mosquitto/passwd admin
```

A seguir, insira e confirme a senha que quer criar.

Edite o arquivo de configuração:

```bash
sudo nano /etc/mosquitto/mosquitto.conf
```

Adicione as linhas:

```plaintext
listener 1883
allow_anonymous false
password_file /etc/mosquitto/passwd
```

Reinicie o Mosquitto:

```bash
sudo systemctl restart mosquitto
```

---

## PARTE 2: ENVIO DE DADOS VIA MQTT NO ESP32

### 1. Clonagem do Repositório no Wokwi

Clone o repositório base para o Wokwi:

```bash
git clone https://github.com/arnaldojr/iot-esp32-wokwi-vscode.git
```
Link para vídeo de demonstração:
https://fiapcom-my.sharepoint.com/:v:/g/personal/pf1745_fiap_com_br/ESugYBDBbMxBv3su8quXIDIBVV7Em3ydKeWfZZPNP2HcSQ


---

### 2. Configuração do Código ESP32 no PlatformIO

1. Crie uma pasta para uma nova questão (Q4)
2. No arquivo "wokwi.toml" altere os campos para Q4.
3. No arquivo "platform.ini" crie uma nova questão (Q4) e apague as referências das dependências.
4. No arquivo "src/main.cpp", no trecho descrito abaixo, insira as credenciais de Wi-Fi e as informações do broker MQTT configurado na Azure:

```cpp

// Identificadores
const char* ID        = "INSIRA O ID DO SEU GRUPO";
const char* moduleID  = "INSIRA O ID DO SEU ESP32";

// Wi-Fi
const char* SSID      = "Wokwi-GUEST";
const char* PASSWORD  = "";

// MQTT Broker
const char* BROKER_MQTT  = "INSIRA O ENDEREÇO DO SEU BROKER";
const int   BROKER_PORT  = 1883;
const char* mqttUser     = "";
const char* mqttPassword = "";

// Tópico MQTT
#define TOPICO_PUBLISH  "INSIRA O NOME DO SEU TÓPICO"

```

---

### 3. Envio dos Dados Simulados

No código de exemplo, simule os seguintes dados:
- Temperatura: 20°C a 35°C
- Umidade: 40% a 80%
- Pressão: 980 hPa a 1050 hPa
- Altitude: 0 m a 500 m

Compile o projeto e teste o envio dos dados.

---

### 4. Testes no Node-RED

- Acesse o Node-RED na Azure: "http://SEU_IP_VM_AZURE:1880"
- Crie fluxos para receber os dados no tópico definido.
- Verifique a comunicação MQTT através do console do Node-RED e do monitor serial no Wokwi.

---

## REFERÊNCIAS:
- [ESP32 Documentation](https://docs.espressif.com/projects/esp-idf/en/latest/esp32/)
- [Node-RED Documentation](https://nodered.org/docs/)
- [Mosquitto MQTT](https://mosquitto.org/documentation/)
- [PlatformIO IDE](https://platformio.org/)
- [Wokwi Simulator](https://wokwi.com/)
