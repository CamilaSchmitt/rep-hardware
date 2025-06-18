#include <Arduino.h>
#include "_Buzzer.h"

#define BeepsLiberado 1                       // 1 bip = acesso liberado
#define BeepsNegado 2                         // 2 bips = acesso negado 
#define AcionaBuzzer 7                        // buzzer = D7 Arduino

void BuzzerBeeps(int NumeroBeeps)
{
  int i;
  for (i = 0; i < NumeroBeeps; i++)
  {
    digitalWrite(AcionaBuzzer, 1);
    delay(150);                            // atraso de 0,15 segundos
    digitalWrite(AcionaBuzzer, 0);
    delay(150);                            // atraso de 0,15 segundos
  }
}