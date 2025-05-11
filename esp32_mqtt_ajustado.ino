
/********************************************************************
 * Checkpoint 03 - Protocolo MQTT com ESP32
 * Curso: Disruptive Architectures: IOT, IOB & Generative AI
 * Professor: André Tritiack
 * Data: 05/2025
 * Descrição: Código base para envio de dados MQTT (temperatura, umidade,
 * pressão e altitude) usando ESP32. Os dados são simulados aleatoriamente.
 ********************************************************************/

#include <WiFi.h>
#include <PubSubClient.h>

// Credenciais WiFi
const char* ssid = "INSIRA_SUA_REDE_WIFI";
const char* password = "INSIRA_SUA_SENHA_WIFI";

// Servidor MQTT
const char* mqttServer = "INSIRA_SEU_BROKER_MQTT";
const int mqttPort = 1883;
const char* mqttUser = "INSIRA_SEU_USUARIO_MQTT";
const char* mqttPassword = "INSIRA_SUA_SENHA_MQTT";

WiFiClient espClient;
PubSubClient client(espClient);

void setup() {
  Serial.begin(115200);

  // Conectar ao WiFi
  Serial.print("Conectando ao WiFi");
  WiFi.begin(ssid, password);
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }
  Serial.println("
WiFi conectado");

  // Conectar ao servidor MQTT
  client.setServer(mqttServer, mqttPort);
  conectarMQTT();
}

void conectarMQTT() {
  while (!client.connected()) {
    Serial.println("Conectando ao servidor MQTT...");
    if (client.connect("ESP32Client", mqttUser, mqttPassword)) {
      Serial.println("Conectado ao servidor MQTT");
    } else {
      Serial.print("Falha na conexão. Estado: ");
      Serial.println(client.state());
      delay(2000);
    }
  }
}

void enviarDadosMQTT(float temperatura, float umidade, float pressao, float altitude) {
  String payload = "{";
  payload += ""temperatura":" + String(temperatura, 1) + ",";
  payload += ""umidade":" + String(umidade, 1) + ",";
  payload += ""pressao":" + String(pressao, 1) + ",";
  payload += ""altitude":" + String(altitude, 1);
  payload += "}";

  client.publish("esp32/sensores", payload.c_str());
  Serial.println("Dados enviados: " + payload);
}

void loop() {
  if (!client.connected()) {
    conectarMQTT();
  }
  client.loop();

  // Geração de dados simulados
  float temperatura = random(200, 350) / 10.0; // 20.0°C a 35.0°C
  float umidade = random(400, 800) / 10.0;      // 40.0% a 80.0%
  float pressao = random(980, 1050);            // 980 hPa a 1050 hPa
  float altitude = random(0, 500);              // 0 m a 500 m

  // Enviar dados
  enviarDadosMQTT(temperatura, umidade, pressao, altitude);

  delay(10000); // Intervalo de envio de 10 segundos
}
