#define MSG_BUFFER_SIZE 50

#ifndef variables

#define variables

unsigned long lastMsg = 0;

bool estadoMaquina = false;

char msg[MSG_BUFFER_SIZE];

int value = 0;

char *token;

String recepcion[3]={"","",""};

int pinesLimpieza[]={22,23};

int pinesAlarma[]={26,27};

int pinesMaquina[]={21,19};

int pinesAlerta[]={16,25};

int digitalPinsSensor[] = {18,35};
int analogPinsSensor[] = {32,33};

int samplingTime = 280;
int deltaTime = 40;
int sleepTime = 9680;

float voMeasured = 0;
float calcVoltage = 0;
float dustDensity = 0;

String topico_raiz = "4e8ltVoiCa2o8u5";

String modulos[] = {"Limpieza","Alarma","Maquina","Sensor","Alerta","Extractor"};

const byte tamanoModulos = sizeof(modulos) / sizeof(modulos[0]);

int tamanoPinesLimpieza = (sizeof(pinesLimpieza)/sizeof(pinesLimpieza[0]));
int tamanoPinesAlarma = (sizeof(pinesAlarma)/sizeof(pinesAlarma[0]));
int tamanoPinesMaquina = (sizeof(pinesMaquina)/sizeof(pinesMaquina[0]));
int tamanoPinesSensor = (sizeof(digitalPinsSensor)/sizeof(digitalPinsSensor[0]));
int tamanoPinesAlerta = (sizeof(pinesAlerta)/sizeof(pinesAlerta[0]));

#endif