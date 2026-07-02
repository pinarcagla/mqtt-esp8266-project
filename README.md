# ESP8266 MQTT IoT Projesi

## Proje Hakkında

Bu proje, ESP8266 mikrodenetleyicisi kullanılarak MQTT protokolü üzerinden veri gönderme (publisher) ve veri alma (subscriber) işlemlerini göstermektedir. Cihaz Wi-Fi ağına bağlanarak MQTT broker üzerinden haberleşir.

## Kullanılan Teknolojiler

- ESP8266 (NodeMCU)
- Arduino IDE
- MQTT Protokolü
- Wi-Fi haberleşmesi

## Proje Yapısı

mqtt-esp8266-project/

├── publisher/  
│   ├── publisher.ino  
│   └── arduino_secrets.h  
│  
├── subscriber/  
│   ├── subscriber.ino  
│   └── arduino_secrets.h  

## Güvenlik

Wi-Fi ve MQTT giriş bilgileri güvenlik nedeniyle `arduino_secrets.h` dosyasında tutulmuştur ve GitHub’a dahil edilmemelidir.

## Notlar

Bu proje eğitim amaçlı geliştirilmiştir. Publisher ve subscriber aynı MQTT broker üzerinden haberleşmektedir.

---

# ESP8266 MQTT IoT Project

## About the Project

This project demonstrates data transmission (publisher) and data reception (subscriber) using the MQTT protocol with an ESP8266 microcontroller. The device connects to a Wi-Fi network and communicates through an MQTT broker.

## Technologies Used

- ESP8266 (NodeMCU)
- Arduino IDE
- MQTT Protocol
- Wi-Fi communication

## Project Structure

mqtt-esp8266-project/

├── publisher/  
│   ├── publisher.ino  
│   └── arduino_secrets.h  
│  
├── subscriber/  
│   ├── subscriber.ino  
│   └── arduino_secrets.h  

## Security

Wi-Fi and MQTT credentials are stored in `arduino_secrets.h` for security reasons and are not included in the repository.

## Notes

This project is developed for educational purposes. Publisher and subscriber communicate via the same MQTT broker.
