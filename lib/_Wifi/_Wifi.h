#ifndef WIFI_H
#define WIFI_H

#include <WiFi.h>


// Credenciais da rede Wi-Fi
const char* ssid = "Galaxy";         // Substitua pelo nome da sua rede
const char* password = "txmy7010";   // Substitua pela senha da sua rede


void setupWifi() {
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

#endif // WIFI_H