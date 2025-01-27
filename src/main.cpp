#include <Arduino.h>
#include <Adafruit_Fingerprint.h>
#include <SPI.h>
#include <Wire.h>
#include <WiFi.h>

/*_____________________________ CONECTAR NO WIFI __________________________________________________________________*/

// Credenciais da rede Wi-Fi
const char* ssid = "Galaxy";         // Substitua pelo nome da sua rede
const char* password = "txmy7010";   // Substitua pela senha da sua rede

void setup() {
  // Inicia a comunicação serial
  Serial.begin(115200);
  delay(10);

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

void loop() {
  // Código principal
}

/*_____________________________ LEITURA DE DIGITAL __________________________________________________________________*/

// /***************************************************
//   This is an example sketch for our optical Fingerprint sensor

//   Designed specifically to work with the Adafruit BMP085 Breakout
//   ----> http://www.adafruit.com/products/751

//   These displays use TTL Serial to communicate, 2 pins are required to
//   interface
//   Adafruit invests time and resources providing this open source code,
//   please support Adafruit and open-source hardware by purchasing
//   products from Adafruit!

//   Written by Limor Fried/Ladyada for Adafruit Industries.
//   BSD license, all text above must be included in any redistribution
//  ****************************************************/


// #if (defined(__AVR__) || defined(ESP8266)) && !defined(__AVR_ATmega2560__)
// // For UNO and others without hardware serial, we must use software serial...
// // pin #2 is IN from sensor (GREEN wire)
// // pin #3 is OUT from arduino  (WHITE wire)
// // Set up the serial port to use softwareserial..
// SoftwareSerial mySerial(2, 3);

// #else
// // On Leonardo/M0/etc, others with hardware serial, use hardware serial!
// // #0 is green wire, #1 is white
// #define mySerial Serial2

// #endif


// Adafruit_Fingerprint finger = Adafruit_Fingerprint(&mySerial);

// uint8_t getFingerprintID();

// void setup()
// {
//   Serial.begin(9600);
//   while (!Serial);  // For Yun/Leo/Micro/Zero/...
//   delay(100);
//   Serial.println("\n\nAdafruit finger detect test");

//   // set the data rate for the sensor serial port
//   finger.begin(57600);
//   delay(5);
//   if (finger.verifyPassword()) {
//     Serial.println("Found fingerprint sensor!");
//   } else {
//     Serial.println("Did not find fingerprint sensor :(");
//     while (1) { delay(1); }
//   }

//   Serial.println(F("Reading sensor parameters"));
//   finger.getParameters();
//   Serial.print(F("Status: 0x")); Serial.println(finger.status_reg, HEX);
//   Serial.print(F("Sys ID: 0x")); Serial.println(finger.system_id, HEX);
//   Serial.print(F("Capacity: ")); Serial.println(finger.capacity);
//   Serial.print(F("Security level: ")); Serial.println(finger.security_level);
//   Serial.print(F("Device address: ")); Serial.println(finger.device_addr, HEX);
//   Serial.print(F("Packet len: ")); Serial.println(finger.packet_len);
//   Serial.print(F("Baud rate: ")); Serial.println(finger.baud_rate);

//   finger.getTemplateCount();

//   if (finger.templateCount == 0) {
//     Serial.print("Sensor doesn't contain any fingerprint data. Please run the 'enroll' example.");
//   }
//   else {
//     Serial.println("Waiting for valid finger...");
//       Serial.print("Sensor contains "); Serial.print(finger.templateCount); Serial.println(" templates");
//   }
// }

// void loop()                     // run over and over again
// {
//   getFingerprintID();
//   delay(50);            //don't ned to run this at full speed.
// }

// uint8_t getFingerprintID() {
//   uint8_t p = finger.getImage();
//   switch (p) {
//     case FINGERPRINT_OK:
//       Serial.println("Image taken");
//       break;
//     case FINGERPRINT_NOFINGER:
//       Serial.println("No finger detected");
//       return p;
//     case FINGERPRINT_PACKETRECIEVEERR:
//       Serial.println("Communication error");
//       return p;
//     case FINGERPRINT_IMAGEFAIL:
//       Serial.println("Imaging error");
//       return p;
//     default:
//       Serial.println("Unknown error");
//       return p;
//   }

//   // OK success!

//   p = finger.image2Tz();
//   switch (p) {
//     case FINGERPRINT_OK:
//       Serial.println("Image converted");
//       break;
//     case FINGERPRINT_IMAGEMESS:
//       Serial.println("Image too messy");
//       return p;
//     case FINGERPRINT_PACKETRECIEVEERR:
//       Serial.println("Communication error");
//       return p;
//     case FINGERPRINT_FEATUREFAIL:
//       Serial.println("Could not find fingerprint features");
//       return p;
//     case FINGERPRINT_INVALIDIMAGE:
//       Serial.println("Could not find fingerprint features");
//       return p;
//     default:
//       Serial.println("Unknown error");
//       return p;
//   }

//   // OK converted!
//   p = finger.fingerSearch();
//   if (p == FINGERPRINT_OK) {
//     Serial.println("Found a print match!");
//   } else if (p == FINGERPRINT_PACKETRECIEVEERR) {
//     Serial.println("Communication error");
//     return p;
//   } else if (p == FINGERPRINT_NOTFOUND) {
//     Serial.println("Did not find a match");
//     return p;
//   } else {
//     Serial.println("Unknown error");
//     return p;
//   }

//   // found a match!
//   Serial.print("Found ID #"); Serial.print(finger.fingerID);
//   Serial.print(" with confidence of "); Serial.println(finger.confidence);

//   return finger.fingerID;
// }

// // returns -1 if failed, otherwise returns ID #
// int getFingerprintIDez() {
//   uint8_t p = finger.getImage();
//   if (p != FINGERPRINT_OK)  return -1;

//   p = finger.image2Tz();
//   if (p != FINGERPRINT_OK)  return -1;

//   p = finger.fingerFastSearch();
//   if (p != FINGERPRINT_OK)  return -1;

//   // found a match!
//   Serial.print("Found ID #"); Serial.print(finger.fingerID);
//   Serial.print(" with confidence of "); Serial.println(finger.confidence);
//   return finger.fingerID;
// }


/*_____________________________ CADASTRO DE DIGITAL __________________________________________________________________*/

// /***************************************************
//   This is an example sketch for our optical Fingerprint sensor

//   Designed specifically to work with the Adafruit BMP085 Breakout
//   ----> http://www.adafruit.com/products/751

//   These displays use TTL Serial to communicate, 2 pins are required to
//   interface
//   Adafruit invests time and resources providing this open source code,
//   please support Adafruit and open-source hardware by purchasing
//   products from Adafruit!

//   Written by Limor Fried/Ladyada for Adafruit Industries.  
//   Small bug-fix by Michael cochez

//   BSD license, all text above must be included in any redistribution
//  ****************************************************/


// #if (defined(__AVR__) || defined(ESP8266)) && !defined(__AVR_ATmega2560__)
// // For UNO and others without hardware serial, we must use software serial...
// // pin #2 is IN from sensor (GREEN wire)
// // pin #3 is OUT from arduino  (WHITE wire)
// // Set up the serial port to use softwareserial..
// SoftwareSerial mySerial(2, 3);

// #else
// // On Leonardo/M0/etc, others with hardware serial, use hardware serial!
// // #0 is green wire, #1 is white
// #define mySerial Serial2

// #endif

// Adafruit_Fingerprint finger = Adafruit_Fingerprint(&mySerial);

// uint8_t id;

// uint8_t getFingerprintEnroll();

// void setup()
// {
//   Serial.begin(9600);
//   while (!Serial);  // For Yun/Leo/Micro/Zero/...
//   delay(100);
//   Serial.println("\n\nAdafruit Fingerprint sensor enrollment");

//   // set the data rate for the sensor serial port
//   finger.begin(57600);

//   if (finger.verifyPassword()) {
//     Serial.println("Found fingerprint sensor!");
//   } else {
//     Serial.println("Did not find fingerprint sensor :(");
//     while (1) { delay(1); }
//   }

//   Serial.println(F("Reading sensor parameters"));
//   finger.getParameters();
//   Serial.print(F("Status: 0x")); Serial.println(finger.status_reg, HEX);
//   Serial.print(F("Sys ID: 0x")); Serial.println(finger.system_id, HEX);
//   Serial.print(F("Capacity: ")); Serial.println(finger.capacity);
//   Serial.print(F("Security level: ")); Serial.println(finger.security_level);
//   Serial.print(F("Device address: ")); Serial.println(finger.device_addr, HEX);
//   Serial.print(F("Packet len: ")); Serial.println(finger.packet_len);
//   Serial.print(F("Baud rate: ")); Serial.println(finger.baud_rate);
// }

// uint8_t readnumber(void) {
//   uint8_t num = 0;

//   while (num == 0) {
//     while (! Serial.available());
//     num = Serial.parseInt();
//   }
//   return num;
// }

// void loop()                     // run over and over again
// {
//   Serial.println("Ready to enroll a fingerprint!");
//   Serial.println("Please type in the ID # (from 1 to 127) you want to save this finger as...");
//   id = readnumber();
//   if (id == 0) {// ID #0 not allowed, try again!
//      return;
//   }
//   Serial.print("Enrolling ID #");
//   Serial.println(id);

//   while (! getFingerprintEnroll() );
// }

// uint8_t getFingerprintEnroll() {

//   int p = -1;
//   Serial.print("Waiting for valid finger to enroll as #"); Serial.println(id);
//   while (p != FINGERPRINT_OK) {
//     p = finger.getImage();
//     switch (p) {
//     case FINGERPRINT_OK:
//       Serial.println("Image taken");
//       break;
//     case FINGERPRINT_NOFINGER:
//       Serial.print(".");
//       break;
//     case FINGERPRINT_PACKETRECIEVEERR:
//       Serial.println("Communication error");
//       break;
//     case FINGERPRINT_IMAGEFAIL:
//       Serial.println("Imaging error");
//       break;
//     default:
//       Serial.println("Unknown error");
//       break;
//     }
//   }

//   // OK success!

//   p = finger.image2Tz(1);
//   switch (p) {
//     case FINGERPRINT_OK:
//       Serial.println("Image converted");
//       break;
//     case FINGERPRINT_IMAGEMESS:
//       Serial.println("Image too messy");
//       return p;
//     case FINGERPRINT_PACKETRECIEVEERR:
//       Serial.println("Communication error");
//       return p;
//     case FINGERPRINT_FEATUREFAIL:
//       Serial.println("Could not find fingerprint features");
//       return p;
//     case FINGERPRINT_INVALIDIMAGE:
//       Serial.println("Could not find fingerprint features");
//       return p;
//     default:
//       Serial.println("Unknown error");
//       return p;
//   }

//   Serial.println("Remove finger");
//   delay(2000);
//   p = 0;
//   while (p != FINGERPRINT_NOFINGER) {
//     p = finger.getImage();
//   }
//   Serial.print("ID "); Serial.println(id);
//   p = -1;
//   Serial.println("Place same finger again");
//   while (p != FINGERPRINT_OK) {
//     p = finger.getImage();
//     switch (p) {
//     case FINGERPRINT_OK:
//       Serial.println("Image taken");
//       break;
//     case FINGERPRINT_NOFINGER:
//       Serial.print(".");
//       break;
//     case FINGERPRINT_PACKETRECIEVEERR:
//       Serial.println("Communication error");
//       break;
//     case FINGERPRINT_IMAGEFAIL:
//       Serial.println("Imaging error");
//       break;
//     default:
//       Serial.println("Unknown error");
//       break;
//     }
//   }

//   // OK success!

//   p = finger.image2Tz(2);
//   switch (p) {
//     case FINGERPRINT_OK:
//       Serial.println("Image converted");
//       break;
//     case FINGERPRINT_IMAGEMESS:
//       Serial.println("Image too messy");
//       return p;
//     case FINGERPRINT_PACKETRECIEVEERR:
//       Serial.println("Communication error");
//       return p;
//     case FINGERPRINT_FEATUREFAIL:
//       Serial.println("Could not find fingerprint features");
//       return p;
//     case FINGERPRINT_INVALIDIMAGE:
//       Serial.println("Could not find fingerprint features");
//       return p;
//     default:
//       Serial.println("Unknown error");
//       return p;
//   }

//   // OK converted!
//   Serial.print("Creating model for #");  Serial.println(id);

//   p = finger.createModel();
//   if (p == FINGERPRINT_OK) {
//     Serial.println("Prints matched!");
//   } else if (p == FINGERPRINT_PACKETRECIEVEERR) {
//     Serial.println("Communication error");
//     return p;
//   } else if (p == FINGERPRINT_ENROLLMISMATCH) {
//     Serial.println("Fingerprints did not match");
//     return p;
//   } else {
//     Serial.println("Unknown error");
//     return p;
//   }

//   Serial.print("ID "); Serial.println(id);
//   p = finger.storeModel(id);
//   if (p == FINGERPRINT_OK) {
//     Serial.println("Stored!");
//   } else if (p == FINGERPRINT_PACKETRECIEVEERR) {
//     Serial.println("Communication error");
//     return p;
//   } else if (p == FINGERPRINT_BADLOCATION) {
//     Serial.println("Could not store in that location");
//     return p;
//   } else if (p == FINGERPRINT_FLASHERR) {
//     Serial.println("Error writing to flash");
//     return p;
//   } else {
//     Serial.println("Unknown error");
//     return p;
//   }

//   return true;
// }

/*_____________________________ CÓDIGO DO NFC __________________________________________________________________*/

// #include <MFRC522.h> //biblioteca responsável pela comunicação com o módulo RFID-RC522

// #define SS_PIN    21
// #define RST_PIN   22

// #define SIZE_BUFFER     18
// #define MAX_SIZE_BLOCK  16

// #define pinVerde     12
// #define pinVermelho  32

// //esse objeto 'chave' é utilizado para autenticação
// MFRC522::MIFARE_Key key;
// //código de status de retorno da autenticação
// MFRC522::StatusCode status;

// // Definicoes pino modulo RC522
// MFRC522 mfrc522(SS_PIN, RST_PIN); 

// //faz a leitura dos dados do cartão/tag
// void leituraDados()
// {
//   //imprime os detalhes tecnicos do cartão/tag
//   mfrc522.PICC_DumpDetailsToSerial(&(mfrc522.uid)); 

//   //Prepara a chave - todas as chaves estão configuradas para FFFFFFFFFFFFh (Padrão de fábrica).
//   for (byte i = 0; i < 6; i++) key.keyByte[i] = 0xFF;

//   //buffer para colocar os dados ligos
//   byte buffer[SIZE_BUFFER] = {0};

//   //bloco que faremos a operação
//   byte bloco = 1;
//   byte tamanho = SIZE_BUFFER;


//   //faz a autenticação do bloco que vamos operar
//   status = mfrc522.PCD_Authenticate(MFRC522::PICC_CMD_MF_AUTH_KEY_A, bloco, &key, &(mfrc522.uid)); //line 834 of MFRC522.cpp file
//   if (status != MFRC522::STATUS_OK) {
//     Serial.print(F("Authentication failed: "));
//     Serial.println(mfrc522.GetStatusCodeName(status));
//     digitalWrite(pinVermelho, HIGH);
//     delay(1000);
//     digitalWrite(pinVermelho, LOW);
//     return;
//   }

//   //faz a leitura dos dados do bloco
//   status = mfrc522.MIFARE_Read(bloco, buffer, &tamanho);
//   if (status != MFRC522::STATUS_OK) {
//     Serial.print(F("Reading failed: "));
//     Serial.println(mfrc522.GetStatusCodeName(status));
//     digitalWrite(pinVermelho, HIGH);
//     delay(1000);
//     digitalWrite(pinVermelho, LOW);
//     return;
//   }
//   else{
//       digitalWrite(pinVerde, HIGH);
//       delay(1000);
//       digitalWrite(pinVerde, LOW);
//   }

//   Serial.print(F("\nDados bloco ["));
//   Serial.print(bloco);Serial.print(F("]: "));

//   //imprime os dados lidos
//   for (uint8_t i = 0; i < MAX_SIZE_BLOCK; i++)
//   {
//       Serial.write(buffer[i]);
//   }
//   Serial.println(" ");
// }

// //faz a gravação dos dados no cartão/tag
// void gravarDados()
// {
//   //imprime os detalhes tecnicos do cartão/tag
//   mfrc522.PICC_DumpDetailsToSerial(&(mfrc522.uid)); 
//   // aguarda 30 segundos para entrada de dados via Serial
//   Serial.setTimeout(30000L) ;     
//   Serial.println(F("Insira os dados a serem gravados com o caractere '#' ao final\n[máximo de 16 caracteres]:"));

//   //Prepara a chave - todas as chaves estão configuradas para FFFFFFFFFFFFh (Padrão de fábrica).
//   for (byte i = 0; i < 6; i++) key.keyByte[i] = 0xFF;

//   //buffer para armazenamento dos dados que iremos gravar
//   byte buffer[MAX_SIZE_BLOCK] = "";
//   byte bloco; //bloco que desejamos realizar a operação
//   byte tamanhoDados; //tamanho dos dados que vamos operar (em bytes)

//   //recupera no buffer os dados que o usuário inserir pela serial
//   //serão todos os dados anteriores ao caractere '#'
//   tamanhoDados = Serial.readBytesUntil('#', (char*)buffer, MAX_SIZE_BLOCK);
//   //espaços que sobrarem do buffer são preenchidos com espaço em branco
//   for(byte i=tamanhoDados; i < MAX_SIZE_BLOCK; i++)
//   {
//     buffer[i] = ' ';
//   }
 
//   bloco = 1; //bloco definido para operação
//   String str = (char*)buffer; //transforma os dados em string para imprimir
//   Serial.println(str);

//   //Authenticate é um comando para autenticação para habilitar uma comuinicação segura
//   status = mfrc522.PCD_Authenticate(MFRC522::PICC_CMD_MF_AUTH_KEY_A,
//                                     bloco, &key, &(mfrc522.uid));

//   if (status != MFRC522::STATUS_OK) {
//     Serial.print(F("PCD_Authenticate() failed: "));
//     Serial.println(mfrc522.GetStatusCodeName(status));
//     digitalWrite(pinVermelho, HIGH);
//     delay(1000);
//     digitalWrite(pinVermelho, LOW);
//     return;
//   }
//   //else Serial.println(F("PCD_Authenticate() success: "));
 
//   //Grava no bloco
//   status = mfrc522.MIFARE_Write(bloco, buffer, MAX_SIZE_BLOCK);
//   if (status != MFRC522::STATUS_OK) {
//     Serial.print(F("MIFARE_Write() failed: "));
//     Serial.println(mfrc522.GetStatusCodeName(status));
//     digitalWrite(pinVermelho, HIGH);
//     delay(1000);
//     digitalWrite(pinVermelho, LOW);
//     return;
//   }
//   else{
//     Serial.println(F("MIFARE_Write() success: "));
//     digitalWrite(pinVerde, HIGH);
//     delay(1000);
//     digitalWrite(pinVerde, LOW);
//   }
 
// }

// //menu para escolha da operação
// int menu()
// {
//   Serial.println(F("\nEscolha uma opção:"));
//   Serial.println(F("0 - Leitura de Dados"));
//   Serial.println(F("1 - Gravação de Dados\n"));

//   //fica aguardando enquanto o usuário nao enviar algum dado
//   while(!Serial.available()){};

//   //recupera a opção escolhida
//   int op = (int)Serial.read();
//   //remove os proximos dados (como o 'enter ou \n' por exemplo) que vão por acidente
//   while(Serial.available()) {
//     if(Serial.read() == '\n') break; 
//     Serial.read();
//   }
//   return (op-48);//do valor lido, subtraimos o 48 que é o ZERO da tabela ascii
// }

// void setup() {
//   // Inicia a serial
//   Serial.begin(115200);
//   SPI.begin(); // Init SPI bus

//   pinMode(pinVerde, OUTPUT);
//   pinMode(pinVermelho, OUTPUT);
  
//   // Inicia MFRC522
//   mfrc522.PCD_Init(); 
//   // Mensagens iniciais no serial monitor
//   Serial.println("Aproxime o seu cartao do leitor...");
//   Serial.println();

// }

// void loop() 
// {
//    // Aguarda a aproximacao do cartao
//   if ( ! mfrc522.PICC_IsNewCardPresent()) 
//   {
//     return;
//   }
//   // Seleciona um dos cartoes
//   if ( ! mfrc522.PICC_ReadCardSerial()) 
//   {
//     return;
//   }

//     // Dump debug info about the card; PICC_HaltA() is automatically called
// //  mfrc522.PICC_DumpToSerial(&(mfrc522.uid));

//   //chama o menu e recupera a opção desejada
//   int opcao = menu();
//    // verifica se ainda está com o cartão/tag
// //  if ( ! mfrc522.PICC_IsNewCardPresent()) 
// //  {
// //    return;
// //  }
  
//   if(opcao == 0) 
//     leituraDados();
//   else if(opcao == 1) 
//     gravarDados();
//   else {
//     Serial.println(F("Opção Incorreta!"));
//     return;
//   }
 
//   // instrui o PICC quando no estado ACTIVE a ir para um estado de "parada"
//   mfrc522.PICC_HaltA(); 
//   // "stop" a encriptação do PCD, deve ser chamado após a comunicação com autenticação, caso contrário novas comunicações não poderão ser iniciadas
//   mfrc522.PCD_StopCrypto1();  
// }

