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

Siga as instruções do repositório do Professor Arnaldo Viana: https://github.com/arnaldojr/iot-esp32-wokwi-vscode


## CRIAÇÃO DA MÁQUINA VIRTUAL LINUX NA AZURE:

1. Acesse o portal Azure: [https://portal.azure.com](https://portal.azure.com).

2. Crie um recurso do tipo **Máquina Virtual** utilizando a imagem **Ubuntu Server 20.04 LTS**.

3. Configure as portas de acesso:
   - SSH: 22
   - HTTP: 80
   - MQTT: 1883
   - NodeRED: 1880

4. Acesse a máquina virtual via SSH:

```bash
ssh usuario@SEU_IP_VM_AZURE
```

5. Atualize os pacotes:

```bash
sudo apt update && sudo apt upgrade -y
```

---

## INSTALAÇÃO DO NODE.JS E NODE-RED:

1. Remova versões antigas:

```bash
sudo apt remove -y nodejs npm
sudo apt autoremove -y
```

2. Instale Node.js v18.x:

```bash
curl -fsSL https://deb.nodesource.com/setup_18.x | sudo -E bash -
sudo apt install -y nodejs
```

3. Instale o Node-RED:

```bash
sudo npm install -g --unsafe-perm node-red
```

4. Inicie o Node-RED:

```bash
node-red
```

Acesse o Node-RED em: `http://SEU_IP_VM_AZURE:1880`

---

## INSTALAÇÃO DO MOSQUITTO BROKER:

1. **Instale o Mosquitto Broker e os clientes MQTT:**

```bash
sudo apt install -y mosquitto mosquitto-clients
```

---

2. **Criação de um Usuário MQTT:**

Para configurar autenticação no Mosquitto, precisamos criar um usuário com senha.

- Execute o comando abaixo para criar um usuário chamado `admin` e definir a senha:

```bash
sudo mosquitto_passwd -c /etc/mosquitto/passwd admin
```

- O terminal pedirá para definir a senha. Exemplo:

```
Enter new password:
Reenter password:
```

Esse arquivo `passwd` armazena o usuário e a senha criptografados e será referenciado no arquivo de configuração do Mosquitto.

---

3. **Configuração do Mosquitto Broker:**

Para aplicar a autenticação e configurar o listener MQTT, edite o arquivo `mosquitto.conf`:

```bash
sudo nano /etc/mosquitto/mosquitto.conf
```

Adicione as seguintes linhas no final do arquivo:

```plaintext
# Define a porta MQTT
listener 1883

# Desativa o acesso anônimo
allow_anonymous false

# Define o caminho do arquivo de senhas
password_file /etc/mosquitto/passwd
```

Salve (`CTRL + X`, `Y`, `Enter`).

---

4. **Reiniciar o Mosquitto Broker:**

Após a configuração, é necessário reiniciar o serviço para que as alterações sejam aplicadas:

```bash
sudo systemctl restart mosquitto
```

Verifique o status para garantir que o broker esteja ativo e sem erros:

```bash
sudo systemctl status mosquitto
```

---


## PARTE 2: ENVIO DE DADOS SIMULADOS VIA MQTT NO ESP32

- Utilizando o código base `esp32_mqtt_ajustado.ino`, ajuste as credenciais e defina os tópicos MQTT.
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
