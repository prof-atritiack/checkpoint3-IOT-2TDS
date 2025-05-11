
# CHECKPOINT 03 - PROTOCOLO MQTT COM ESP32
**Disciplina:** Disruptive Architectures: IOT, IOB & Generative AI  
**Professor:** André Tritiack  
**Turmas de Fevereiro:** 2TDSPF, 2TDSPJ, 2TDSPK, 2TDSPV, 2TDSPX, 2TDSPY  
**Turmas de Agosto:** 2TDSZ, 2TDSPA, 2TDSPC, 2TDSPR, 2TDSPS  

---

## FORMATO DA ENTREGA:
A entrega deve conter os seguintes elementos:  
1. Link do repositório no GitHub contendo todos os arquivos do projeto.  
2. Link para um vídeo curto (máximo 3 minutos) demonstrando a aplicação funcionando.  
3. Arquivo `integrantes.txt` contendo:  
   - Nomes completos dos integrantes.      

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

Os alunos também podem optar por simular o projeto utilizando o PlatformIO com Wokwi no VSCode. Essa opção é recomendada para aqueles que não possuem o hardware ESP32.

### **INSTALAÇÃO DO VSCODE E PLATFORMIO:**

1. Instale o **Visual Studio Code (VSCode)**:  
   [Download VSCode](https://code.visualstudio.com/)  

2. No VSCode, abra a aba de extensões e instale a extensão **PlatformIO IDE**.

3. Após a instalação, abra o PlatformIO (`Ctrl + Shift + P`) e selecione:  
   - `PlatformIO: New Project`
   - Nome do projeto: `esp32_mqtt`
   - Board: `Wokwi ESP32 Devkit v1`
   - Framework: `Arduino`

4. Crie o projeto e abra a pasta gerada.

---

### **INTEGRAÇÃO COM WOKWI:**
1. No projeto criado, abra o arquivo `platformio.ini` e adicione as seguintes configurações:

```
[env:wokwi]
platform = espressif32
board = esp32dev
framework = arduino
monitor_speed = 115200
upload_protocol = custom
upload_flags =
  --chip esp32
  -b 921600
  --before default_reset
  --after hard_reset
  write_flash
  0x1000
  .pio/build/wokwi/firmware.bin
upload_port = https://wokwi.com/projects/SEU_PROJECT_ID
```

2. Acesse o site do Wokwi: [https://wokwi.com](https://wokwi.com)  
   - Crie um novo projeto ESP32.  
   - Copie o Project ID gerado e insira no `platformio.ini` no campo `upload_port`.  

3. Compile e faça o upload do código diretamente para o Wokwi.

---

## PARTE 1: CRIAÇÃO DA MÁQUINA VIRTUAL LINUX NA AZURE

1. Acesse o portal Azure: [https://portal.azure.com](https://portal.azure.com)  
2. Crie um recurso do tipo **Máquina Virtual** utilizando a imagem **Ubuntu Server 20.04 LTS**.
3. Configure as portas de acesso:
   - SSH: 22
   - HTTP: 80
   - MQTT: 1883

### INSTALAÇÃO DO NODE-RED:
Acesse a máquina virtual via SSH:

```bash
ssh usuario@ip_da_vm
```

Atualize os pacotes e instale o Node-RED:

```bash
sudo apt update
sudo apt install -y nodejs npm
sudo npm install -g --unsafe-perm node-red
node-red
```

Acesse o Node-RED no navegador: `http://ip_da_vm:1880`  

### INSTALAÇÃO DO MOSQUITTO BROKER:

```bash
sudo apt install -y mosquitto mosquitto-clients
sudo systemctl enable mosquitto
sudo systemctl start mosquitto
```

Teste o Mosquitto Broker com o comando:

```bash
mosquitto_sub -h localhost -t teste -v
```

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

## REFERÊNCIAS IMPORTANTES:
- [Documentação do ESP32](https://docs.espressif.com/projects/esp-idf/en/latest/esp32/)
- [Documentação do NodeRED](https://nodered.org/docs/)
- [Documentação do Mosquitto MQTT](https://mosquitto.org/documentation/)
- [Protocolo MQTT - Guia Completo](https://mqtt.org/getting-started/)
- [PlatformIO IDE](https://platformio.org/)
- [Wokwi ESP32 Simulator](https://wokwi.com/)
