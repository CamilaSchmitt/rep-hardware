#ifndef Time_h
#define Time_h

#include <time.h>

long timezone = -3;
byte daysavetime = 1;


void setupTime()
{
    Serial.println("Conecção ao servidor NTP");
    configTime(3600 * timezone, daysavetime * 3600, "time.nist.gov", "0.pool.ntp.org", "1.pool.ntp.org");
}

void printLocalTime()
{

    struct tm tmstruct;
    
    // Obtém o horário local
    if (getLocalTime(&tmstruct))
    {                                                                                                                             // Verifica se conseguiu obter o tempo
        String date = String((tmstruct.tm_mday)) + "-" + String((tmstruct.tm_mon) + 1) + "-" + String((tmstruct.tm_year + 1900)); // Formato dia-mês
        String hour = String(tmstruct.tm_hour) + ":" + String(tmstruct.tm_min) + ":" + String(tmstruct.tm_sec);

        Serial.println("Data: " + date + " - Hora: " + hour);
    }
    else
    {
        Serial.println("Falha ao obter horário");
    }
}

#endif // Time_h