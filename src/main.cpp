#include <Arduino.h>
// #include <Wire.h>
#include <_Nfc.h>
#include <_Wifi.h>
#include <_Time.h>
#include <_Fingerprint.h>
#include <HTTPClient.h>


// Credenciais da rede Wi-Fi
const char* ssid = "Gabriel";         // Substitua pelo nome da sua rede
const char* password = "4012229401ap";   // Substitua pela senha da sua rede

// Your Domain name with URL path or IP address with path
// Inserção do URI (URL + URN) a acessar
// String uri = "http://192.168.185.143:3002/rep/";
const char *host = "Lenovo_Legion_5";
String uri = "http://" + String(host) + ":3002/rep/";

void setup()
{
  // Inicia a comunicação serial
  Serial.begin(115200);

  setupWifi(ssid, password);
  String resolvedIP = resolve(host);
  
  if(resolvedIP != "") {

    HTTPClient http;
    String url = "http://" + resolvedIP + ":3002/rep/usuarios";
    http.begin(url);
    int httpResponseCode = http.GET();

    if (httpResponseCode > 0) {
      Serial.print("Resposta HTTP: ");
      Serial.println(httpResponseCode);
      Serial.println(http.getString());
    } else {
      Serial.print("Erro HTTP: ");
      Serial.println(httpResponseCode);
    }

    http.end();
  }

  setupNfc();
  setupTime();
  setupFingerprintVerify();
  
}

void loop()
{

  Serial.println("Menu:");
  Serial.println("1 - Cadastrar digital");
  Serial.println("2 - Ler digital");
  Serial.println("3 - Cadastrar tag NFC");
  Serial.println("4 - Ler tag NFC");
  Serial.println("5 - Verificar data");
  Serial.println("6 - Verificar hora");
  Serial.println("Digite a opção desejada:");
  int opcao = Serial.parseInt();

  switch (opcao) {
    case 1:
      // Cadastrar digital
      loopFingerprint();
      break;
    case 2:
      // Ler digital
      loopFingerprintVerify();
      break;
    case 3:
      // Cadastrar tag NFC
      loopNfc(true);
      break;
    case 4:
      // Ler tag NFC
      loopNfc(false);
      break;
    case 5:
      // Verificar data
      getLocalDateOrTime(true);
      break;
    case 6:
      // Verificar hora
      getLocalDateOrTime(false);
      break;
    default:
      Serial.println("Opção inválida");
      break;
  }
}
