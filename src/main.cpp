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

uint8_t opcao = 0;

// Rotas que podem ser acessadas pela API
void setupServerRoutes()
{
  // server.on("/ler-digital", HTTP_GET, []() {
  //   int id = loopFingerprintVerify();  // ou outra função sua que retorne a digital
  //   server.send(200, "application/json", "{\"digital\": " + String(id) + "}");
  // });

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

  server.on("/cadastrar-nfc", HTTP_POST, []()
            {
    loopNfc(true);  // função de cadastro
    server.send(200, "text/plain", "NFC cadastrado com sucesso."); });

  // server.on("/ler-nfc", HTTP_GET, []() {
  //   String tag = loopNfc(false);  // Lê uma tag NFC
  //   server.send(200, "application/json", "{\"tag\": \"" + tag + "\"}");
  // });

  // server.on("/hora", HTTP_GET, []() {
  //   String hora = getLocalDateOrTime(false);
  //   server.send(200, "text/plain", hora);
  // });

  // server.on("/data", HTTP_GET, []() {
  //   String data = getLocalDateOrTime(true);
  //   server.send(200, "text/plain", data);
  // });
}

void setup()
{
  Serial.begin(115200);

  setupWifi(ssid, password);

  String resolvedIP = resolve(hostnameAPI);
  if (resolvedIP != "")
  {
    url_base = scheme + resolvedIP + port + prefix;
    String url = url_base + "/usuarios";

    http.begin(url);
    int httpResponseCode = http.GET();
    if (httpResponseCode > 0)
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
  Serial.println("mDNS configurado e inicializado;");

  setupNfc();
  setupTime();
  setupFingerprintVerify();
}

void loop()
{
  server.handleClient(); // trata requisições da API

  // Modo manual via Serial (menu)
  // Serial.println("Menu:");
  // Serial.println("1 - Cadastrar digital");
  // Serial.println("2 - Ler digital");
  // Serial.println("3 - Cadastrar tag NFC");
  // Serial.println("4 - Ler tag NFC");
  // Serial.println("5 - Verificar data");
  // Serial.println("6 - Verificar hora");
  // Serial.println("Digite a opção desejada:");

  // while (opcao == 0) {
  //   while (!Serial.available());
  //   opcao = Serial.parseInt();
  // }

  // switch (opcao) {
  //   case 1:
  //     loopFingerprint();
  //     break;
  //   case 2:
  //     loopFingerprintVerify();
  //     break;
  //   case 3:
  //     loopNfc(true);
  //     break;
  //   case 4:
  //     loopNfc(false);
  //     break;
  //   case 5:
  //     Serial.println(getLocalDateOrTime(true));
  //     break;
  //   case 6:
  //     Serial.println(getLocalDateOrTime(false));
  //     break;
  //   default:
  //     Serial.println("Opção inválida");
  //     break;
  // }

  // opcao = 0; // reseta a opção para o próximo loop
}