#include <Arduino.h>
#include <DHT.h>

#define DHTPIN 2 // Chân dữ liệu của DHT nối với D2 của Arduino
#define DHTTYPE DHT11 // Hoặc DHT22, tuỳ vào loại cảm biến bạn sử dụng

#define FAN_RELAY_PIN 3 // Chân điều khiển relay của quạt
#define MIST_RELAY_PIN 4 // Chân điều khiển relay của máy phun sương

DHT dht(DHTPIN, DHTTYPE);

void setup() {
  Serial.begin(9600);
  dht.begin();

  pinMode(FAN_RELAY_PIN, OUTPUT);
  pinMode(MIST_RELAY_PIN, OUTPUT);

  // Khởi động các relay ở trạng thái tắt
  digitalWrite(FAN_RELAY_PIN, LOW);
  digitalWrite(MIST_RELAY_PIN, LOW);
}

void loop() {
  float humidity = dht.readHumidity();
  float temperature = dht.readTemperature();

  if (isnan(humidity) || isnan(temperature)) {
    Serial.println("Failed to read from DHT sensor!");
    return;
  }

  Serial.print("Humidity: ");
  Serial.print(humidity);
  Serial.print(" %\t");
  Serial.print("Temperature: ");
  Serial.print(temperature);
  Serial.println(" *C");

  // Điều khiển quạt dựa trên nhiệt độ
  if (temperature > 30) {
    digitalWrite(FAN_RELAY_PIN, HIGH); // Bật quạt
  } else {
    digitalWrite(FAN_RELAY_PIN, LOW); // Tắt quạt
  }

  // Điều khiển máy phun sương dựa trên độ ẩm
  if (humidity < 60) {
    digitalWrite(MIST_RELAY_PIN, HIGH); // Bật máy phun sương
  } else {
    digitalWrite(MIST_RELAY_PIN, LOW); // Tắt máy phun sương
  }

  delay(2000); // Đọc dữ liệu mỗi 2 giây
}
