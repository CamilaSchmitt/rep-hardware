#include "_Time.h"

#include <time.h>

#define TIMEZONE (-3)
#define DAYSAVETIME (1)

void setupTime()
{
    Serial.println("Conexão ao servidor NTP");
    configTime(3600 * TIMEZONE, DAYSAVETIME * 3600, "time.nist.gov", "0.pool.ntp.org", "1.pool.ntp.org");
}

String getLocalDateOrTime(bool isDate)
{
    struct tm tmstruct;

    if (getLocalTime(&tmstruct))
    {
        if (isDate)
        {
            // Obtém a data local
            String date = String((tmstruct.tm_mday)) + "/" + String((tmstruct.tm_mon) + 1) + "/" + String((tmstruct.tm_year + 1900)); // Formato dia-mês
            return date;
        }
        else
        {
            // Obtém o horário local
            String hour = String(tmstruct.tm_hour) + ":" + String(tmstruct.tm_min) + ":" + String(tmstruct.tm_sec);
            return hour;
        }
    }
    else
    {
        return "Falha ao obter data ou hora";
    }
}