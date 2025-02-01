#include <Arduino.h>
// #include <Wire.h>
#include <_Nfc.h>
#include <_Wifi.h>
#include <_Time.h>
#include <_Fingerprint.h>

// Credenciais da rede Wi-Fi
const char* ssid = "Galaxy";         // Substitua pelo nome da sua rede
const char* password = "txmy7010";   // Substitua pela senha da sua rede

void setup()
{
  // Inicia a comunicação serial
  Serial.begin(115200);
  while (!Serial.available());

  setupWifi(ssid, password);
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
