#define MSG_BUFFER_SIZE 50

#ifndef variables

#define variables

unsigned long lastMsg = 0;

bool estadoMaquina = false;

char msg[MSG_BUFFER_SIZE];

int value = 0;

char *token;

String recepcion[3]={"","",""};

int pinesLimpieza[]={18,19,21,22,23};

int pinesAlarma[]={1,2,3,4,5,6,7,8,9,10};

int tamanoPinesLimpieza = (sizeof(pinesLimpieza)/sizeof(pinesLimpieza[0]));
int tamanoPinesAlarma = (sizeof(pinesAlarma)/sizeof(pinesAlarma[0]));

#endif