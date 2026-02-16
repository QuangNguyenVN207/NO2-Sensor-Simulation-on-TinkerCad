// C++ code
//
#define MQ135_PIN A0
#define RL 10.0          // điện trở tải (kΩ)
#define ADC_MAX 1023.0
#define VCC 5.0

// ===== THAM SỐ HIỆU CHUẨN NO2 (ƯỚC LƯỢNG) =====
float A_NO2 = 110.0;
float B_NO2 = -2.7;

// R0 – đo trong không khí sạch (sau khi preheat)
float R0 = 10.0;   // kΩ (bạn phải đo lại!)

void setup() {
  Serial.begin(9600);
  Serial.println("MQ-135 NO2 ppm measurement");
}

void loop() {
  int adc = analogRead(MQ135_PIN);
  float voltage = adc * VCC / ADC_MAX;

  // Tính Rs
  float Rs = (VCC - voltage) * RL / voltage;

  // Tỉ số Rs/R0
  float ratio = Rs / R0;

  // Tính ppm NO2
  float ppm_NO2 = A_NO2 * pow(ratio, B_NO2);

  Serial.print("ADC: "); Serial.print(adc);
  Serial.print(" | Rs: "); Serial.print(Rs, 2);
  Serial.print(" kOhm | NO2: ");
  Serial.print(ppm_NO2, 2);
  Serial.println(" ppm");

  delay(1000);
}