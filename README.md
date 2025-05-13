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

As aulas entre os dias **12 e 22 de maio** poderão ser utilizadas para o desenvolvimento da atividade do CP3 no laboratório, utilizando as placas **ESP32 DEVKIT v1** disponíveis para os grupos.  
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
2. Após a instalação, abra o PlatformIO (`Ctrl + Shift + P`) e selecione:
   - `PlatformIO: New Project`
   - Nome do projeto: `esp32_mqtt`
   - Board: `DOIT ESP32 DEVKIT V1`
   - Framework: `Arduino`
3. Clique em **Finish** e aguarde a criação da estrutura do projeto.

---

### **CONFIGURAÇÃO DO WOKWI NO PlatformIO:**

1. No projeto criado, abra o arquivo `platformio.ini` e substitua o conteúdo por:

```ini
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
   - Copie o **Project ID** gerado e substitua `SEU_PROJECT_ID` no `platformio.ini`.

---

## PARTE 1: CRIAÇÃO DA MÁQUINA VIRTUAL LINUX NA AZURE

1. Acesse o portal Azure: [https://portal.azure.com](https://portal.azure.com)  
2. Crie um recurso do tipo **Máquina Virtual** utilizando a imagem **Ubuntu Server 20.04 LTS**.
3. Configure as portas de acesso:
   - SSH: 22
   - HTTP: 80

4. Crie uma regra de entrada para a liberação das portas 1880 (NodeRED) e 1883 (Broker).

---

## INSTALAÇÃO DO NODE.JS PARA NODE-RED (v18 ou Superior)

```bash
sudo apt update && sudo apt upgrade -y
curl -fsSL https://deb.nodesource.com/setup_18.x | sudo -E bash -
sudo apt install -y nodejs
node -v
npm -v
```

---

## INSTALAÇÃO DO MOSQUITTO BROKER

```bash
sudo apt install -y mosquitto mosquitto-clients
sudo systemctl enable mosquitto
sudo systemctl start mosquitto
```

Abra o arquivo de configuração:

```bash
sudo nano /etc/mosquitto/mosquitto.conf
```

Adicione:

```plaintext
listener 1883
allow_anonymous true
```

Reinicie o serviço:

```bash
sudo systemctl restart mosquitto
```

---

## TESTE DO MOSQUITTO BROKER

Subscrição:

```bash
mosquitto_sub -h localhost -t teste -v
```

Publicação:

```bash
mosquitto_pub -h localhost -t teste -m "Testando conexão no Mosquitto Broker"
```

---

## REFERÊNCIAS:
- [Documentação do ESP32](https://docs.espressif.com/projects/esp-idf/en/latest/esp32/)
- [Documentação do NodeRED](https://nodered.org/docs/)
- [Mosquitto MQTT](https://mosquitto.org/documentation/)
- [PlatformIO IDE](https://platformio.org/)
- [Wokwi ESP32 Simulator](https://wokwi.com/)
