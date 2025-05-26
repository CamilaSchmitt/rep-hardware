#include "_Fingerprint.h"

#include <Adafruit_Fingerprint.h>

#if (defined(__AVR__) || defined(ESP8266)) && !defined(__AVR_ATmega2560__)
// For UNO and others without hardware serial, we must use software serial...
// pin #2 is IN from sensor (GREEN wire)
// pin #3 is OUT from arduino  (WHITE wire)
// Set up the serial port to use softwareserial..
SoftwareSerial mySerial(2, 3);

#else
// On Leonardo/M0/etc, others with hardware serial, use hardware serial!
// #0 is green wire, #1 is white
#define mySerial Serial2

#endif

Adafruit_Fingerprint finger = Adafruit_Fingerprint(&mySerial);

uint8_t id;

/*_____________________________ CADASTRO DE DIGITAL __________________________________________________________________*/

uint8_t getFingerprintEnroll()
{

    int p = -1;
    Serial.print("Aguardando um dedo válido para cadastrar a digital #");
    Serial.println(id);
    while (p != FINGERPRINT_OK)
    {
        p = finger.getImage();
        switch (p)
        {
        case FINGERPRINT_OK:
            Serial.println("Imagem capturada");
            break;
        case FINGERPRINT_NOFINGER:
            Serial.print(".");
            break;
        case FINGERPRINT_PACKETRECIEVEERR:
            Serial.println("Erro de comunicação");
            break;
        case FINGERPRINT_IMAGEFAIL:
            Serial.println("Erro ao capturar imagem");
            break;
        default:
            Serial.println("Erro desconhecido");
            break;
        }
    }

    // OK success!

    p = finger.image2Tz(1);
    switch (p)
    {
    case FINGERPRINT_OK:
        Serial.println("Imagem convertida");
        break;
    case FINGERPRINT_IMAGEMESS:
        Serial.println("Imagem confusa");
        return p;
    case FINGERPRINT_PACKETRECIEVEERR:
        Serial.println("Erro de comunicação");
        return p;
    case FINGERPRINT_FEATUREFAIL:
        Serial.println("Não foi possível encontrar características da digital");
        return p;
    case FINGERPRINT_INVALIDIMAGE:
        Serial.println("Não foi possível encontrar características da digital");
        return p;
    default:
        Serial.println("Erro desconhecido");
        return p;
    }

    Serial.println("Remova o dedo...");
    delay(2000);
    p = 0;
    while (p != FINGERPRINT_NOFINGER)
    {
        p = finger.getImage();
    }
    Serial.print("ID ");
    Serial.println(id);
    p = -1;
    Serial.println("Aproxime o mesmo dedo novamente");
    while (p != FINGERPRINT_OK)
    {
        p = finger.getImage();
        switch (p)
        {
        case FINGERPRINT_OK:
            Serial.println("Imagem capturada");
            break;
        case FINGERPRINT_NOFINGER:
            Serial.print(".");
            break;
        case FINGERPRINT_PACKETRECIEVEERR:
            Serial.println("Erro de comunicação");
            break;
        case FINGERPRINT_IMAGEFAIL:
            Serial.println("Erro ao capturar imagem");
            break;
        default:
            Serial.println("Erro desconhecido");
            break;
        }
    }

    // OK success!

    p = finger.image2Tz(2);
    switch (p)
    {
    case FINGERPRINT_OK:
        Serial.println("Imagem convertida");
        break;
    case FINGERPRINT_IMAGEMESS:
        Serial.println("Imagem confusa");
        return p;
    case FINGERPRINT_PACKETRECIEVEERR:
        Serial.println("Erro de comunicação");
        return p;
    case FINGERPRINT_FEATUREFAIL:
        Serial.println("Não foi possível encontrar características da digital");
        return p;
    case FINGERPRINT_INVALIDIMAGE:
        Serial.println("Não foi possível encontrar características da digital");
        return p;
    default:
        Serial.println("Erro desconhecido");
        return p;
    }

    // OK converted!
    Serial.print("Criando modelo para ID #");
    Serial.println(id);

    p = finger.createModel();
    if (p == FINGERPRINT_OK)
    {
        Serial.println("Impressões coincidem!");
    }
    else if (p == FINGERPRINT_PACKETRECIEVEERR)
    {
        Serial.println("Erro de comunicação");
        return p;
    }
    else if (p == FINGERPRINT_ENROLLMISMATCH)
    {
        Serial.println("Impressões não coincidem");
        return p;
    }
    else
    {
        Serial.println("Erro desconhecido");
        return p;
    }

    Serial.print("ID ");
    Serial.println(id);
    p = finger.storeModel(id);
    if (p == FINGERPRINT_OK)
    {
        Serial.println("Digital armazenada com sucesso!");
    }
    else if (p == FINGERPRINT_PACKETRECIEVEERR)
    {
        Serial.println("Erro de comunicação");
        return p;
    }
    else if (p == FINGERPRINT_BADLOCATION)
    {
        Serial.println("Não foi possível armazenar nesta posição");
        return p;
    }
    else if (p == FINGERPRINT_FLASHERR)
    {
        Serial.println("Erro de gravação na memória flash");
        return p;
    }
    else
    {
        Serial.println("Erro desconhecido");
        return p;
    }

    return true;
}

// uint8_t readnumber(void)
// {
//     uint8_t num = 0;

//     while (num == 0)
//     {
//         while (!Serial.available())
//             ;
//         num = Serial.parseInt();
//     }
//     return num;
// }

void setupFingerprintEnroll()
{
    Serial.println("\n\nCadastro de digitais - Sensor de Impressão Digital Adafruit");

    // set the data rate for the sensor serial port
    finger.begin(57600);
    delay(5);
    if (finger.verifyPassword())
    {
        Serial.println("Sensor de impressão digital encontrado!");
    }
    else
    {
        Serial.println("Não foi possível encontrar o sensor de impressão digital :(");
        while (1)
        {
            delay(1);
        }
    }

    Serial.println(F("Lendo parâmetros do sensor de impressão digital..."));
    finger.getParameters();
    Serial.print(F("Status: 0x"));
    Serial.println(finger.status_reg, HEX);
    Serial.print(F("ID do sistema: 0x"));
    Serial.println(finger.system_id, HEX);
    Serial.print(F("Capacidade: "));
    Serial.println(finger.capacity);
    Serial.print(F("Nível de segurança: "));
    Serial.println(finger.security_level);
    Serial.print(F("Endereço do dispositivo: "));
    Serial.println(finger.device_addr, HEX);
    Serial.print(F("Tamanho do pacote: "));
    Serial.println(finger.packet_len);
    Serial.print(F("Taxa de transmissão (baud rate): "));
    Serial.println(finger.baud_rate);
}

void loopFingerprint(int identificador)
{
    id = identificador;
    
    Serial.println("Pronto para cadastrar uma digital!");
    // Serial.println("Digite o número do ID (de 1 a 127) que você deseja atribuir a esta digital...");
    // id = readnumber();
    // if (id == 0)
    // { // ID #0 not allowed, try again!
    //     return;
    // }
    Serial.print("Cadastrando digital com ID #");
    Serial.println(id);

    while (!getFingerprintEnroll())
        ;
}

/*_____________________________ CADASTRO DE DIGITAL __________________________________________________________________*/

/*_____________________________ VERIFICACAO DE DIGITAL __________________________________________________________________*/

uint8_t getFingerprintID()
{
    uint8_t p = finger.getImage();
    switch (p)
    {
    case FINGERPRINT_OK:
        Serial.println("Imagem capturada");
        break;
    case FINGERPRINT_NOFINGER:
        Serial.println("Nenhum dedo detectado");
        return p;
    case FINGERPRINT_PACKETRECIEVEERR:
        Serial.println("Erro de comunicação");
        return p;
    case FINGERPRINT_IMAGEFAIL:
        Serial.println("Erro ao capturar imagem");
        return p;
    default:
        Serial.println("Erro desconhecido");
        return p;
    }

    // OK success!

    p = finger.image2Tz();
    switch (p)
    {
    case FINGERPRINT_OK:
        Serial.println("Imagem convertida");
        break;
    case FINGERPRINT_IMAGEMESS:
        Serial.println("Imagem confusa");
        return p;
    case FINGERPRINT_PACKETRECIEVEERR:
        Serial.println("Erro de comunicação");
        return p;
    case FINGERPRINT_FEATUREFAIL:
        Serial.println("Não foi possível encontrar características da digital");
        return p;
    case FINGERPRINT_INVALIDIMAGE:
        Serial.println("Não foi possível encontrar características da digital");
        return p;
    default:
        Serial.println("Erro desconhecido");
        return p;
    }

    // OK converted!
    p = finger.fingerSearch();
    if (p == FINGERPRINT_OK)
    {
        Serial.println("Impressão encontrada!");
    }
    else if (p == FINGERPRINT_PACKETRECIEVEERR)
    {
        Serial.println("Erro de comunicação");
        return p;
    }
    else if (p == FINGERPRINT_NOTFOUND)
    {
        Serial.println("Nenhuma impressão encontrada");
        return p;
    }
    else
    {
        Serial.println("Erro desconhecido");
        return p;
    }

    // found a match!
    Serial.print("ID encontrado #");
    Serial.print(finger.fingerID);
    Serial.print(" com nível de confiança de ");
    Serial.println(finger.confidence);

    return finger.fingerID;
}

// returns -1 if failed, otherwise returns ID #
int getFingerprintIDez()
{
    uint8_t p = finger.getImage();
    if (p != FINGERPRINT_OK)
        return -1;

    p = finger.image2Tz();
    if (p != FINGERPRINT_OK)
        return -1;

    p = finger.fingerFastSearch();
    if (p != FINGERPRINT_OK)
        return -1;

    // found a match!
    Serial.print("ID encontrado: #");
    Serial.print(finger.fingerID);
    Serial.print(" com nível de confiança de ");
    Serial.println(finger.confidence);
    return finger.fingerID;
}

void setupFingerprintVerify()
{
    setupFingerprintEnroll();

    finger.getTemplateCount();

    if (finger.templateCount == 0)
    {
        Serial.print("Não há digitais cadastradas! Cadastrar uma digital primeiro.");
    }
    else
    {
        Serial.println("Aguardando um dedo válido...");
        Serial.print("O sensor contém ");
        Serial.print(finger.templateCount);
        Serial.println(" impressões disponíveis.");
    }
}

void loopFingerprintVerify()
{
    getFingerprintID();
    delay(50);
}

/*_____________________________ VERIFICACAO DE DIGITAL __________________________________________________________________*/
