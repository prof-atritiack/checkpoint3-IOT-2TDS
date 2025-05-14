/********************************************************************
 * Projeto: Envio de Dados MQTT com ESP32 (WiFi + NTP)
 * Autor: André Tritiack
 * Placa: DOIT ESP32 DEVKIT V1
 * 
 * Descrição:
 * Este projeto conecta o ESP32 a uma rede Wi-Fi e a um Broker MQTT.
 * A cada 10 segundos, envia uma mensagem JSON com:
 * - ID do grupo
 * - ID do módulo
 * - IP local
 * - Data (YYYY-MM-DD)
 * - Hora (HH:MM:SS)
 * 
 * Bibliotecas utilizadas:
 * - WiFi (nativa)
 * - time (nativa do ESP32)
 * - PubSubClient (instalar)
 * - ArduinoJson (instalar)
 * 
 * Baseado em tutoriais da Random Nerd Tutorials e documentação oficial
 * da Espressif.
 ********************************************************************/

//----------------------------------------------------------
// Bibliotecas já disponíveis no ambiente ESP32

#include <WiFi.h>
#include <time.h>

//----------------------------------------------------------
// Bibliotecas a instalar pelo Gerenciador de Bibliotecas

#include <PubSubClient.h>
#include <ArduinoJson.h>

//----------------------------------------------------------
// Definições e configurações

#define boardLED 2 // LED onboard

// Identificadores
const char* ID        = "";
const char* moduleID  = "";

// Wi-Fi
const char* SSID      = "";
const char* PASSWORD  = "";

// MQTT Broker
const char* BROKER_MQTT  = "";
const int   BROKER_PORT  = ;
const char* mqttUser     = "";
const char* mqttPassword = "";

// Tópico MQTT
#define TOPICO_PUBLISH  ""

//----------------------------------------------------------
// Variáveis globais

WiFiClient espClient;
PubSubClient MQTT(espClient);
char buffer[256]; // Buffer para o JSON serializado

//----------------------------------------------------------
// Setup inicial

void setup() {
    Serial.begin(115200);
    pinMode(boardLED, OUTPUT);
    digitalWrite(boardLED, LOW);

    initWiFi();
    initNTP();
    initMQTT();
}

//----------------------------------------------------------
// Loop principal

void loop() {
    // Verifica e mantém conexões ativas com Wi-Fi e MQTT
    verificaConexoesWiFiEMQTT();

    // Captura data e hora via NTP
    struct tm timeinfo;
    getLocalTime(&timeinfo);

    char data[11]; // Formato: "YYYY-MM-DD"
    char hora[9];  // Formato: "HH:MM:SS"
    strftime(data, sizeof(data), "%Y-%m-%d", &timeinfo);
    strftime(hora, sizeof(hora), "%H:%M:%S", &timeinfo);

    // Montagem do documento JSON
    StaticJsonDocument<300> doc;

    // 1. Identificação
    doc["ID"]     = ID;
    doc["Sensor"] = moduleID;

    // 2. Rede
    doc["IP"]     = WiFi.localIP().toString();

    // 3. Data e hora
    doc["data"]   = data;
    doc["hora"]   = hora;

    // Serializa JSON para string
    serializeJson(doc, buffer);

    // Exibe no monitor serial
    Serial.println(buffer);

    // Envia via MQTT
    enviaEstadoOutputMQTT();

    // Feedback visual
    piscaLed();

    // Intervalo de envio
    delay(10000);
}

//----------------------------------------------------------
// Conexão Wi-Fi

void initWiFi() {
    WiFi.begin(SSID, PASSWORD);
    Serial.print("Conectando ao Wi-Fi");
    while (WiFi.status() != WL_CONNECTED) {
        delay(1000);
        Serial.print(".");
    }
    Serial.println("\nWi-Fi conectado!");
    Serial.print("IP: ");
    Serial.println(WiFi.localIP());
    Serial.print("MAC Address: ");
    Serial.println(WiFi.macAddress());
}

void reconectaWiFi() {
    if (WiFi.status() != WL_CONNECTED) {
        Serial.println("Reconectando Wi-Fi...");
        initWiFi();
    }
}

//----------------------------------------------------------
// Configuração NTP (horário de Brasília)

void initNTP() {
    configTime(-3 * 3600, 0, "pool.ntp.org", "time.nist.gov");
    struct tm timeinfo;
    while (!getLocalTime(&timeinfo)) {
        Serial.println("Aguardando sincronização NTP...");
        delay(1000);
    }
    Serial.println("Horário sincronizado via NTP.");
}

//----------------------------------------------------------
// Conexão MQTT

void initMQTT() {
    MQTT.setServer(BROKER_MQTT, BROKER_PORT);
    while (!MQTT.connected()) {
        Serial.println("Conectando ao Broker MQTT...");
        if (MQTT.connect(moduleID, mqttUser, mqttPassword)) {
            Serial.println("Conectado ao Broker!");
        } else {
            Serial.print("Falha na conexão. Estado: ");
            Serial.println(MQTT.state());
            delay(2000);
        }
    }
}

void verificaConexoesWiFiEMQTT() {
    reconectaWiFi();
    if (!MQTT.connected()) {
        initMQTT();
    }
    MQTT.loop();
}

//----------------------------------------------------------
// Envio e feedback

void enviaEstadoOutputMQTT() {
    MQTT.publish(TOPICO_PUBLISH, buffer);
    Serial.println("Mensagem publicada com sucesso!");
}

void piscaLed() {
    digitalWrite(boardLED, HIGH);
    delay(300);
    digitalWrite(boardLED, LOW);
}
