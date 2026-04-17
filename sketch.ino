#include <Wire.h>
#include <LiquidCrystal_I2C.h>

// Адрес 0x27 стандартный для LCD I2C в Wokwi
LiquidCrystal_I2C lcd(0x27, 20, 4);

const int BUTTON_PIN = 2;

// 2. Рекурсивное вычисление числа Фибоначчи
unsigned long fibonacci(int n) {
  if (n <= 1) return n;
  return fibonacci(n - 1) + fibonacci(n - 2);
}

void setup() {
  pinMode(BUTTON_PIN, INPUT_PULLUP);
  
  lcd.init();
  lcd.backlight();
  
  // Инициализация генератора случайных чисел от свободного пина
  randomSeed(analogRead(0));

  lcd.setCursor(0, 0);
  lcd.print("Ready to start...");
}

void loop() {
  // Обработка нажатия (LOW из-за PULLUP)
  if (digitalRead(BUTTON_PIN) == LOW) {
    delay(50); // Простейший антидребезг
    if (digitalRead(BUTTON_PIN) == LOW) {
      lcd.clear();
      
      // 1. Генерация рандомного числа (от 5 до 30 включительно)
      int targetNumber = random(5, 31);
      lcd.setCursor(0, 0); // Строка №1
      lcd.print("Random: ");
      lcd.print(targetNumber);

      // 3. Замер чистого времени работы
      unsigned long startTime = micros();
      unsigned long result = fibonacci(targetNumber);
      unsigned long endTime = micros();

      // Вычисление времени в секундах
      double executionTime = (endTime - startTime) / 1000000.0;

      // Вывод времени в формате (Время: X.XXXXX сек.) на Строку №2
      lcd.setCursor(0, 1);
      lcd.print("time: ");
      lcd.print(executionTime, 5); 
      lcd.print(" sek.");

      // 4. Вывод числа Фибоначчи в формате (Число: X) на Строку №3
      lcd.setCursor(0, 2);
      lcd.print("number: ");
      lcd.print(result);

      // Ожидание отпускания кнопки, чтобы не зацикливать
      while (digitalRead(BUTTON_PIN) == LOW);
    }
  }
}
