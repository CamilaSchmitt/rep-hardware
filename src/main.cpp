#include <Arduino.h>
#include <ArduinoJson.h>
#include <WiFi.h>
#include <WebServer.h>
#include <HTTPClient.h>


#include <_Nfc.h>
#include <_Wifi.h>
#include <_Time.h>
#include <_Fingerprint.h>
#include <ESPmDNS.h>

int pinVerde = 12;
int pinVermelho = 32;

// Credenciais da rede Wi-Fi
const char *ssid = "Gabriel";
const char *password = "4012229401ap";

// Endereço do host onde roda a API (opcional agora)
const char *hostnameAPI = "Lenovo_Legion_5";
const char *hostnameESP = "esp32";
const char *scheme = "http://";
const char *port = ":3002";
const char *prefix = "/rep";

HTTPClient http;
String url_base;

// Servidor HTTP (porta 80)
WebServer server(80);

// Resolve o hostname para um IP
String resolvedIP;

// Rotas que podem ser acessadas pela API
void setupServerRoutes()
{

  server.on("/cadastrar-nfc", HTTP_POST, []()
            {
    loopNfc(true);  // função de cadastro
    server.send(200, "text/plain", "NFC cadastrado com sucesso."); });

  server.on("/cadastrar-digital", HTTP_POST, []()
            {
    String body = server.arg("plain");  // captura o corpo bruto da requisição
    Serial.println("Body recebido:");
    Serial.println(body);

    // Criar buffer para o JSON (ajuste o tamanho conforme seu JSON)
    DynamicJsonDocument doc(256);

    // Parse JSON
    DeserializationError error = deserializeJson(doc, body);
    if (error) {
        Serial.print(F("Falha no parse do JSON: "));
        Serial.println(error.f_str());
        server.send(400, "text/plain", "JSON inválido");
        return;
    }

    // Recupera o id do JSON
    int id = doc["id"] | 0;  // pega o 'id' ou zero caso não exista

    Serial.print("ID recebido: ");
    Serial.println(id);

    // Chama a função de cadastro com o id recebido
    loopFingerprint(id);

    server.send(200, "text/plain", "Digital cadastrada com sucesso."); });
}

void setup()
{
  Serial.begin(115200);

  pinMode(pinVerde, OUTPUT);
  pinMode(pinVermelho, OUTPUT);

  setupWifi(ssid, password);

  // ESP32 como CLIENTE HTTP */
  resolvedIP = resolve(hostnameAPI);
  if (resolvedIP != "")
  {
    Serial.println("IP resolvido: " + resolvedIP);
  }
  else
  {
    Serial.println("Erro ao resolver o IP do host: " + String(hostnameAPI));
    Serial.println("O ESP32 vai reiniciar em 1s...");
    delay(1000);
    ESP.restart();
  }
  // ESP32 como CLIENTE HTTP */

  // ESP32 como SERVIDOR HTTP */
  /* Usa MDNS para resolver o DNS */
  if (!MDNS.begin(hostnameESP))
  {
    // http://esp32.local
    Serial.println("Erro ao configurar mDNS. O ESP32 vai reiniciar em 1s...");
    delay(1000);
    ESP.restart();
  }

  setupServerRoutes(); // configura as rotas
  server.begin();      // inicia o servidor
  Serial.println("mDNS configurado e inicializado.");
  /* ESP32 como SERVIDOR HTTP */

  setupTime();
  setupNfc();
  setupFingerprintVerify();
}

void loop()
{
  server.handleClient(); // trata requisições da API

  delay(2000); // aguarda 2 segundo entre as requisições
  int id = getFingerprintIDez(); // verifica se há digitais cadastradas
  if (id != -1)
  {
    Serial.print("Digital verificada com sucesso! ID: ");
    url_base = scheme + resolvedIP + port + prefix;
    String url = url_base + "/registros";

    http.begin(url);
    http.addHeader("Content-Type", "application/json");

    // Cria o JSON
    StaticJsonDocument<256> jsonDoc;
    jsonDoc["dt_hora_marcacao"] = getLocalDateAndTime();
    JsonObject dispositivoObj = jsonDoc.createNestedObject("dispositivo");
    dispositivoObj["id"] = id;
    dispositivoObj["tipo"] = "Biometria";

    
    String payload;
    serializeJson(jsonDoc, payload);
    
    Serial.print("Payload:");
    Serial.println(payload);
    int httpResponseCode = http.POST(payload);

    if (httpResponseCode == 201)
    {
      Serial.print("Resposta HTTP: ");
      Serial.println(httpResponseCode);
      Serial.println(http.getString());
    }
    else
    {
      Serial.print("Erro HTTP: ");
      Serial.println(httpResponseCode);
    }

    http.end();
  }



  // loopNfc(true); // Cadastrar tag NFC
  // loopNfc(false); // Ler tag NFC

  
}