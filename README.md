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
2. Após a instalação, abra o PlatformIO (`Ctrl + Shift + P`) e selecione:
   - `PlatformIO: New Project`
   - Nome do projeto: `esp32_mqtt`
   - Board: `DOIT ESP32 DEVKIT V1`
   - Framework: `Arduino`
3. Clique em **Finish** e aguarde a criação da estrutura do projeto.

---

### **CONFIGURAÇÃO DO WOKWI NO PlatformIO:**

1. **Crie uma conta ou faça login no Wokwi:**
   - Acesse [https://wokwi.com](https://wokwi.com) e faça o login.

2. **Crie um Novo Projeto ESP32 no Wokwi:**
   - Após o login, clique em **New Project**.
   - Selecione o modelo **ESP32 DevKit v1**.
   - Copie o **Project ID** gerado (exemplo: `https://wokwi.com/projects/123456789`). Esse ID será utilizado no `platformio.ini`.

3. **No VSCode, abra o projeto no PlatformIO:**
   - Localize o arquivo `platformio.ini` na raiz do projeto.
   - Substitua o conteúdo por:

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

- Substitua `SEU_PROJECT_ID` pelo ID copiado do Wokwi.

---

### **COMPILAÇÃO E ENVIO DO PROJETO:**

1. **Compilar o projeto no PlatformIO:**
   - No VSCode, abra o terminal e execute o comando:

```bash
pio run
```

- O firmware será gerado na pasta:

```
.pio/build/wokwi/firmware.bin
```

2. **Enviar o Firmware para o Wokwi:**
   - No terminal, execute o comando:

```bash
pio run -t upload
```

- A conexão será estabelecida automaticamente através do link `upload_port` configurado no `platformio.ini`.

3. **Monitorar a Execução no Wokwi:**
   - No Wokwi, clique em **Start Simulation** para iniciar a simulação.
   - No VSCode, utilize o Monitor Serial para visualizar a execução do código:

```bash
pio device monitor
```

- Certifique-se de que a simulação esteja em execução no Wokwi para visualizar os dados no monitor.

## REFERÊNCIAS:
- [Documentação do ESP32](https://docs.espressif.com/projects/esp-idf/en/latest/esp32/)
- [Documentação do NodeRED](https://nodered.org/docs/)
- [Mosquitto MQTT](https://mosquitto.org/documentation/)
- [PlatformIO IDE](https://platformio.org/)
- [Wokwi ESP32 Simulator](https://wokwi.com/)
