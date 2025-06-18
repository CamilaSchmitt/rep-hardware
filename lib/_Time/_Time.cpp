#include "_Time.h"

#include <time.h>

#define TIMEZONE (-3)
#define DAYSAVETIME (0) // <- sem horário de verão

void setupTime()
{
    Serial.println("Conexão ao servidor NTP");
    configTime(3600 * TIMEZONE, DAYSAVETIME * 3600, "time.nist.gov", "0.pool.ntp.org", "1.pool.ntp.org");
}

String getLocalDateAndTime()
{
    struct tm tmstruct;

    if (getLocalTime(&tmstruct))
    {
        char isoDateTime[30];
        snprintf(isoDateTime, sizeof(isoDateTime), "%04d-%02d-%02dT%02d:%02d:%02d.000",
                 tmstruct.tm_year + 1900,
                 tmstruct.tm_mon + 1,
                 tmstruct.tm_mday,
                 tmstruct.tm_hour,
                 tmstruct.tm_min,
                 tmstruct.tm_sec);

        return String(isoDateTime);
    }
    else
    {
        return "Falha ao obter data ou hora";
    }
}