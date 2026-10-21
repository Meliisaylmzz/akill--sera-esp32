# Akıllı Sera İklim Kontrolü (ESP32)

ESP32 ile sera sıcaklığını izleyen ve sıcaklık eşiği aşılınca havalandırma penceresini otomatik açan gömülü sistem projesi. Donanım Wokwi simülatöründe çalıştırıldı, ölçümler Streamlit panelinde görselleştirildi.

## Ne yapıyor?
- DHT22 sensörü ile sıcaklık ve nemi okur (2 saniyede bir).
- Sıcaklık 30 °C'yi aşarsa servo motoru 90° çevirerek pencereyi açar ve uyarı LED'ini yakar.
- Sıcaklık 30 °C'nin altına inince pencereyi kapatır ve LED'i söndürür.
- Değerleri LCD ekranda ve seri portta gösterir.
- Seri porttan alınan veriler `veri.txt` dosyasına kaydedilir ve Streamlit panelinde grafik olarak gösterilir.

## Kullanılan bileşenler
| Parça | ESP32 pini |
|---|---|
| DHT22 sıcaklık/nem sensörü | GPIO15 |
| Servo motor (pencere) | GPIO18 |
| Kırmızı LED (direnç ile) | GPIO4 |
| LCD1602 I2C ekran | SDA: GPIO21, SCL: GPIO22 |

## Dosyalar
- `sketch.ino`: ESP32 Arduino (C++) kodu
- `app.py`: Streamlit paneli
- `veri.txt`: Simülasyondan alınan örnek ölçümler (`sicaklik,nem,pencere`)

## Çalıştırma
1. `sketch.ino` kodunu Wokwi'de ESP32 projesine yapıştır, gerekli kütüphaneleri ekle (DHT sensor library, ESP32Servo, LiquidCrystal I2C).
2. Panel için: `pip install streamlit pandas`
3. Aynı klasörde: `streamlit run app.py`

## Teknolojiler
ESP32, Arduino C++, Wokwi, Python, Streamlit, Pandas
