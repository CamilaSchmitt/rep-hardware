#include "_Nfc.h"

#include <SPI.h>
#include <MFRC522.h> //biblioteca responsável pela comunicação com o módulo RFID-RC522

#define SS_PIN 21
#define RST_PIN 22

#define SIZE_BUFFER 18
#define MAX_SIZE_BLOCK 16

extern int pinVerde;    // pino do LED verde
extern int pinVermelho; // pino do LED vermelho

// esse objeto 'chave' é utilizado para autenticação
MFRC522::MIFARE_Key key;
// código de status de retorno da autenticação
MFRC522::StatusCode status;

// Definicoes pino modulo RC522
MFRC522 mfrc522(SS_PIN, RST_PIN);


char st[20];                          // string com 20 caracteres
String UID = "";                      // string da identificação UID

// faz a leitura dos dados do cartão/tag
void leituraDados()
{
  // imprime os detalhes tecnicos do cartão/tag
  mfrc522.PICC_DumpDetailsToSerial(&(mfrc522.uid));

  // Prepara a chave - todas as chaves estão configuradas para FFFFFFFFFFFFh (Padrão de fábrica).
  for (byte i = 0; i < 6; i++)
    key.keyByte[i] = 0xFF;

  // buffer para colocar os dados ligos
  byte buffer[SIZE_BUFFER] = {0};

  // bloco que faremos a operação
  byte bloco = 1;
  byte tamanho = SIZE_BUFFER;

  // faz a autenticação do bloco que vamos operar
  status = mfrc522.PCD_Authenticate(MFRC522::PICC_CMD_MF_AUTH_KEY_A, bloco, &key, &(mfrc522.uid)); // line 834 of MFRC522.cpp file
  if (status != MFRC522::STATUS_OK)
  {
    Serial.print(F("Authentication failed: "));
    Serial.println(mfrc522.GetStatusCodeName(status));
    digitalWrite(pinVermelho, HIGH);
    delay(1000);
    digitalWrite(pinVermelho, LOW);
    return;
  }

  // faz a leitura dos dados do bloco
  status = mfrc522.MIFARE_Read(bloco, buffer, &tamanho);
  if (status != MFRC522::STATUS_OK)
  {
    Serial.print(F("Reading failed: "));
    Serial.println(mfrc522.GetStatusCodeName(status));
    digitalWrite(pinVermelho, HIGH);
    delay(1000);
    digitalWrite(pinVermelho, LOW);
    return;
  }
  else
  {
    digitalWrite(pinVerde, HIGH);
    delay(1000);
    digitalWrite(pinVerde, LOW);
  }

  Serial.print(F("\nDados bloco ["));
  Serial.print(bloco);
  Serial.print(F("]: "));

  // imprime os dados lidos
  for (uint8_t i = 0; i < MAX_SIZE_BLOCK; i++)
  {
    Serial.write(buffer[i]);
  }
  Serial.println(" ");
}

// faz a gravação dos dados no cartão/tag
void gravarDados()
{
  // imprime os detalhes tecnicos do cartão/tag
  mfrc522.PICC_DumpDetailsToSerial(&(mfrc522.uid));
  // aguarda 30 segundos para entrada de dados via Serial
  Serial.setTimeout(30000L);
  Serial.println(F("Insira os dados a serem gravados com o caractere '#' ao final\n[máximo de 16 caracteres]:"));

  // Prepara a chave - todas as chaves estão configuradas para FFFFFFFFFFFFh (Padrão de fábrica).
  for (byte i = 0; i < 6; i++)
    key.keyByte[i] = 0xFF;

  // buffer para armazenamento dos dados que iremos gravar
  byte buffer[MAX_SIZE_BLOCK] = "";
  byte bloco;        // bloco que desejamos realizar a operação
  byte tamanhoDados; // tamanho dos dados que vamos operar (em bytes)

  // recupera no buffer os dados que o usuário inserir pela serial
  // serão todos os dados anteriores ao caractere '#'
  tamanhoDados = Serial.readBytesUntil('#', (char *)buffer, MAX_SIZE_BLOCK);
  // espaços que sobrarem do buffer são preenchidos com espaço em branco
  for (byte i = tamanhoDados; i < MAX_SIZE_BLOCK; i++)
  {
    buffer[i] = ' ';
  }

  bloco = 1;                   // bloco definido para operação
  String str = (char *)buffer; // transforma os dados em string para imprimir
  Serial.println(str);

  // Authenticate é um comando para autenticação para habilitar uma comuinicação segura
  status = mfrc522.PCD_Authenticate(MFRC522::PICC_CMD_MF_AUTH_KEY_A,
                                    bloco, &key, &(mfrc522.uid));

  if (status != MFRC522::STATUS_OK)
  {
    Serial.print(F("PCD_Authenticate() failed: "));
    Serial.println(mfrc522.GetStatusCodeName(status));
    digitalWrite(pinVermelho, HIGH);
    delay(1000);
    digitalWrite(pinVermelho, LOW);
    return;
  }
  // else Serial.println(F("PCD_Authenticate() success: "));

  // Grava no bloco
  status = mfrc522.MIFARE_Write(bloco, buffer, MAX_SIZE_BLOCK);
  if (status != MFRC522::STATUS_OK)
  {
    Serial.print(F("MIFARE_Write() failed: "));
    Serial.println(mfrc522.GetStatusCodeName(status));
    digitalWrite(pinVermelho, HIGH);
    delay(1000);
    digitalWrite(pinVermelho, LOW);
    return;
  }
  else
  {
    Serial.println(F("MIFARE_Write() success: "));
    digitalWrite(pinVerde, HIGH);
    delay(1000);
    digitalWrite(pinVerde, LOW);
  }
}


void getUID()
{
  Serial.print("UID da tag NFC : ");                            // imprime no monitor serial
  for (byte i = 0; i < mfrc522.uid.size; i++)                   // leitura da identificação UID da NFC
  {
    Serial.print(mfrc522.uid.uidByte[i] < 0x10 ? " 0" : " ");   // imprime os bytes
    Serial.print(mfrc522.uid.uidByte[i], HEX);                  // imprime UID em hexadecimal
    if ( mfrc522.uid.uidByte[i] < 0x10)                         // se byte menor do que 16
      UID.concat(" 0");                                         // insere um zero
    else                                                        // senão
      UID.concat(" ");                                          // insere um espaço
    UID.concat(String(mfrc522.uid.uidByte[i], HEX));            // concatena todos os bytes da UID
  }
  UID.toUpperCase();                                            // converte em maiusculos
  Serial.println(" ");                                          // imprime espaço

  Serial.println(UID);
}


void setupNfc()
{
  SPI.begin(); // Init SPI bus

  // Inicia MFRC522
  mfrc522.PCD_Init();
  // mostra as informções do modulo RC522
  mfrc522.PCD_DumpVersionToSerial();     
  
  Serial.println("Lendo a etiqueta NTAG213 =  UID, SAK, tipo e blocos de dados...");               
}

void loopNfc(bool gravar)
{
  // Aguarda a aproximacao do cartao
  if (!mfrc522.PICC_IsNewCardPresent())
  {
    return;
  }
  // Seleciona um dos cartoes
  if (!mfrc522.PICC_ReadCardSerial())
  {
    return;
  }
  UID = "";                            // limpa o registro de identificação UID
  getUID();                            // lê e formata a identificação UID


  // Dump debug info about the card; PICC_HaltA() is automatically called
  //  mfrc522.PICC_DumpToSerial(&(mfrc522.uid));

  // chama o menu e recupera a opção desejada
// int gravar = menu();
  // verifica se ainda está com o cartão/tag
  //  if ( ! mfrc522.PICC_IsNewCardPresent())
  //  {
  //    return;
  //  }

 
 
 
  // if (gravar == 0)
  //   leituraDados();
  // else if (gravar == 1)
  //   gravarDados();
  // else
  // {
  //   Serial.println(F("Opção Incorreta!"));
  //   return;
  // }

  // // instrui o PICC quando no estado ACTIVE a ir para um estado de "parada"
  // mfrc522.PICC_HaltA();
  // // "stop" a encriptação do PCD, deve ser chamado após a comunicação com autenticação, caso contrário novas comunicações não poderão ser iniciadas
  // mfrc522.PCD_StopCrypto1();
}