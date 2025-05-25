
#include <Arduino.h>
#include "_Wifi.h"

#include <WiFi.h>
#include <ESPmDNS.h> // resolução de nomes de domínio


void setupWifi(const char *ssid, const char *password) 
{
  // Conectando ao Wi-Fi
  Serial.println("Conectando ao Wi-Fi...");
  WiFi.begin(ssid, password);

  // Aguarda até estar conectado
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }

  // Quando conectado
  Serial.println("");
  Serial.println("Wi-Fi conectado!");
  Serial.print("Endereço IP: ");
  Serial.println(WiFi.localIP()); // Imprime o IP obtido
}

String resolve(const char *host) 
{
   // Inicializa mDNS para o ESP32
   if (!MDNS.begin("esp32")) {
    Serial.println("Erro ao iniciar mDNS. Reiniciando...");
    delay(1000);
    ESP.restart();
  }

  Serial.println("Resolvendo mDNS para Lenovo_Legion_5.local...");
  IPAddress resolvedIP = MDNS.queryHost(host); // sem o ".local"

  if (resolvedIP) {
    Serial.print("IP resolvido: ");
    Serial.println(resolvedIP);
    return resolvedIP.toString();
  }

  Serial.println("Falha ao resolver via mDNS.");
  return "";
}