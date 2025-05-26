#ifndef Digital_h
#define Digital_h

/*_____________________________ CADASTRO DE DIGITAL __________________________________________________________________*/
unsigned char getFingerprintEnroll();
unsigned char readnumber(void);
void setupFingerprintEnroll();
void loopFingerprint(int);
/*_____________________________ CADASTRO DE DIGITAL __________________________________________________________________*/

/*_____________________________ VERIFICACAO DE DIGITAL __________________________________________________________________*/
unsigned char getFingerprintID();
int getFingerprintIDez();
void setupFingerprintVerify();
void loopFingerprintVerify();
/*_____________________________ VERIFICACAO DE DIGITAL __________________________________________________________________*/

#endif // Digital_h