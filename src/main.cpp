#include <Arduino.h>
// #include <Wire.h>
#include <_Nfc.h>
#include <_Wifi.h>
#include <_Time.h>
#include <_Fingerprint.h>


/*_____________________________ MENU ________________________________________________________________*/

// void setup() {
//   Serial.begin(115200);
//   Serial.println("Menu:");
//   Serial.println("1 - Cadastrar digital");
//   Serial.println("2 - Ler digital");
//   Serial.println("3 - Cadastrar cartão");
//   Serial.println("4 - Ler cartão");
//   Serial.println("5 - Cadastrar tag NFC");
//   Serial.println("6 - Ler tag NFC");
//   Serial.println("7 - Verificar horário");

//   while (!Serial.available()) {
//     delay(10);
//   }

//   int opcao = Serial.parseInt();

//   switch (opcao) {
//     case 1:
//       // Cadastrar digital
//       break;
//     case 2:
//       // Ler digital
//       break;
//     case 3:
//       // Cadastrar cartão
//       break;
//     case 4:
//       // Ler cartão
//       break;
//     case 5:
//       // Cadastrar tag NFC
//       break;
//     case 6:
//       // Ler tag NFC
//       break;
//     case 7:
//       // Verificar horário
//       break;
//     default:
//       Serial.println("Opção inválida");
//       break;
//   }
// }


/*_____________________________ CONECTAR NO WIFI e RECUPERAR HORA ________________________________________________________________*/

void setup() {
  // Inicia a comunicação serial
  Serial.begin(115200);
  delay(10);

  setupNfc();
  setupWifi();
  setupTime();
  setupFingerprintEnroll();
}

void loop() {
  printLocalTime();

  delay(1000);
}




