#include <Arduino.h>
#include <LowPower.h>

// Пины
const int PWR_BTN = 2;
const int BUZZER  = 3;

void setup() {
  // Настройка пинов
  pinMode(PWR_BTN, OUTPUT);
  pinMode(BUZZER, OUTPUT);

  // Сброс в безопасное состояние
  digitalWrite(PWR_BTN, LOW);
  digitalWrite(BUZZER, LOW);

  // Ждём после старта
  delay(2000);

  // Имитация нажатия кнопки
  digitalWrite(PWR_BTN, HIGH);
  delay(400);
  digitalWrite(PWR_BTN, LOW);
  
  delay(100);

  // Звуковой сигнал
  digitalWrite(BUZZER, HIGH);
  delay(200);
  digitalWrite(BUZZER, LOW);

  // Переход в глубокий сон
  LowPower.powerDown(SLEEP_FOREVER, ADC_OFF, BOD_OFF);
}

void loop() {
  // Пусто — ничего не делаем
}
