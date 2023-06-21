#include <Arduino.h>
#include <WiFiClient.h>
#include <freertos/FreeRTOS.h>
#include <freertos/task.h>
#include <freertos/queue.h>
#include <freertos/semphr.h>
#include <Keypad.h>
#include <WiFi.h>
#include <BlynkSimpleEsp32.h>
#include <NTPClient.h>
#include <WiFiUdp.h>
#include <Arduino.h>
#include <esp32-hal-gpio.h>

WiFiUDP ntpUDP;
NTPClient timeClient(ntpUDP, "pool.ntp.org");

#define SENSOR_MOVIMENTO_PINO 33
#define SENSOR_ABERTURA_PINO 25
#define ALARME_PINO 26
#define LED_PIN 2
#define LED_STATUS 15
#define BLYNK_TEMPLATE_ID "TMPL26Ho-viur"
#define BLYNK_TEMPLATE_NAME "HomeSecurity"
#define BLYNK_AUTH_TOKEN "9rI6r170XR8QH_Z-oEfFyHU8eQgz8HwA"
#define BLYNK_PRINT Serial
#define ADC_MAX 4095
#define MAX_VOLTAGE_ADC 5.0

int ATIVADO = LOW;
String SenhaTeste = "**";

char auth[] = BLYNK_AUTH_TOKEN; // Token de autenticação
char ssid[] = "REDE";
char pass[] = "";

const byte LINHAS = 4;
const byte COLUNAS = 4;

char teclas[LINHAS][COLUNAS] = {
  {
    '1','2','3','A'
  },
  {
    '4','5','6','B'
  },
  {
    '7','8','9','C'
  },
  {
    '*','0','#','D'
  }
};

byte pinosLinhas[LINHAS] = {
  23,22,3,21
};
byte pinosColunas[COLUNAS] = {
  19,18,5,17
};

Keypad Customkeypad = Keypad(makeKeymap(teclas), pinosLinhas, pinosColunas, LINHAS, COLUNAS);

void tarefaSensorMovimento(void * arg);
void tarefaSenha(void * arg);
void TaskBlynk(void * arg);

void setup() {
  Serial.begin(9600);
  Blynk.begin(auth, ssid, pass);
  pinMode(ALARME_PINO, OUTPUT);
  pinMode(LED_PIN, OUTPUT);
  pinMode(LED_STATUS, OUTPUT);
  Blynk.virtualWrite(V0, LOW);
  Blynk.virtualWrite(V2, SenhaTeste);

  timeClient.setTimeOffset(-3 * 3600);
  timeClient.begin();
	
  xTaskCreate(tarefaSensorMovimento, "SensorMovimento", 8192, NULL, 3, NULL);
  xTaskCreate(tarefaSenha, "Senha", 8192, NULL, 4, NULL);
  xTaskCreatePinnedToCore(TaskBlynk, "TaskBlynk", 4048, NULL, 4, NULL, PRO_CPU_NUM);
}

void loop() {
  vTaskDelay(portMAX_DELAY);
}

time_t getTime() {
  return time(nullptr);
}

BLYNK_WRITE(V1) {
  ATIVADO = param.asInt();
}

BLYNK_WRITE(V2) {
  SenhaTeste = param.asStr();
}

void tarefaSensorMovimento(void * pvParameters) {
  pinMode(SENSOR_MOVIMENTO_PINO, INPUT);
  pinMode(SENSOR_ABERTURA_PINO, INPUT);

  while (1) {
    switch (ATIVADO) {
    case LOW:
      Blynk.virtualWrite(V0, LOW);
      Blynk.virtualWrite(V1, LOW);
      digitalWrite(ALARME_PINO, LOW);
      digitalWrite(LED_PIN, LOW);
      digitalWrite(LED_STATUS, LOW);
      break;

    case HIGH:
      Blynk.virtualWrite(V1, HIGH);
      digitalWrite(LED_STATUS, HIGH);

      if (digitalRead(SENSOR_MOVIMENTO_PINO) == HIGH || digitalRead(SENSOR_ABERTURA_PINO) == LOW) {
        Blynk.virtualWrite(V0, HIGH);
        digitalWrite(LED_PIN, HIGH);
        digitalWrite(ALARME_PINO, HIGH);

        timeClient.update();
        String formattedTime = timeClient.getFormattedTime();
        Blynk.virtualWrite(V3, formattedTime.c_str());

      }
      break;
    }
    vTaskDelay(pdMS_TO_TICKS(1000));
  }
}

void TaskBlynk(void * arg) {
  while (1) {
    Blynk.run();
    vTaskDelay(100);
  }
}

void tarefaSenha(void * pvParameters) {
  while (1) {
    String senhaDigitada;
    char tecla;
    while (true) {
      tecla = Customkeypad.getKey();

      if (tecla) {
        if (tecla == '#') {
          break;
        } else {
          senhaDigitada += tecla;
        }
      }
    }

    if (senhaDigitada == "123") {
      SenhaTeste = senhaDigitada;
      Blynk.virtualWrite(V2, SenhaTeste);
      switch (ATIVADO) {
      case LOW:
        ATIVADO = HIGH;
        digitalWrite(LED_STATUS, HIGH);
        break;

      case HIGH:
        ATIVADO = LOW;
        digitalWrite(LED_STATUS, LOW);
        break;
      }

    }

    if (senhaDigitada != "123") {
      SenhaTeste = senhaDigitada;
      Blynk.virtualWrite(V2, SenhaTeste);
      Blynk.virtualWrite(V0, HIGH);

      digitalWrite(LED_PIN, HIGH);
      digitalWrite(ALARME_PINO, HIGH);

      timeClient.update();
      String formattedTime = timeClient.getFormattedTime();
      Blynk.virtualWrite(V3, formattedTime.c_str());

    }
  }
}
