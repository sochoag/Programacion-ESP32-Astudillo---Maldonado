#define MSG_BUFFER_SIZE 50

#ifndef variables

#define variables

unsigned long lastMsg = 0;

char msg[MSG_BUFFER_SIZE];

int value = 0;

char *token;

String recepcion[3]={"","",""};

int pinesLimpieza[]={18,19,21,22,23};

int tamanoPinesLimpieza = (sizeof(pinesLimpieza)/sizeof(pinesLimpieza[0]));

#endif