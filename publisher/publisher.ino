// MQTT yayımcı örnek uygulaması
//**********************
#include <ESP8266WiFi.h>
#include <MQTTClient.h>
#include "arduino_secrets.h"

WiFiClient wifi_istemci;    // wifi istemci nesnesi
MQTTClient mqtt_istemci;   // mqtt istemci nesnesi


void setup() 
{

  Serial.begin(9600); // seri portu başlat
  delay(200);    // 200 ms bekle    
  Serial.println("Wifi agina baglaniyoruz");  
  WiFi.mode(WIFI_STA);        // istasyon modunda calis       
  WiFi.begin(ssid, password);         // wifi agina baglan

  //--------- Wifi ağına bağlanıncaya kadar beklenilen kısım ------------
  while (WiFi.status() != WL_CONNECTED) 
  { 
    delay(500);         // Bu arada her 500 ms de bir seri ekrana yan yana noktalar yazdırılarak
    Serial.print(".");  //görsellik sağlanıyor.                       
  }
  //-------------------------------------------------------------------
  Serial.println("");    //Bir alt satıra geçiliyor.                       
  Serial.println("Bağlantı sağlandı...");    //seri ekrana bağlantının kurulduğu bilgisi gönderiliyor.    
  
  Serial.print("Alınan IP addresi: ");    // kablosuz ağdan alınan IP adresi       
  Serial.println(WiFi.localIP());        // kablosuz ağdan alınan IP adresi

  //mqtt_istemci.begin("no-ilk.cloud.shiftr.io",wifi_istemci); // mqtt istemciyi başlat, ilk parametre web veya IP adresi
mqtt_istemci.begin(MQTT_SERVER,wifi_istemci); // mqtt istemciyi başlat, ilk parametre web veya IP adresi

  
}
//************************
void loop()
{
  mqtt_istemci.loop();                  // MQTT bağlantısını aktif tut


  if (!mqtt_istemci.connected())       // Broker bağlantısı koparsa tekrar bağlan
  {
    baglan();
  }

  static unsigned long lastSend = 0;

  if (millis() - lastSend > 5000)
  {
    lastSend = millis();

    String mesaj = "202213171807:12, 202213171805:78, 202013171070:45, ";
    String mesajj = "202013171070";
    String mesajjj = "202049234";

    mqtt_istemci.publish("ogrenci/numarasi", mesaj.c_str());
    mqtt_istemci.publish("ogrenci/numarasi", mesajj.c_str());
    mqtt_istemci.publish("ogrenci/numarasi", mesajjj.c_str());
  }
}

void baglan()
{
  // 1. parametre gözükecek adınız, 2. parametre proje adı, 3. token

  while(!mqtt_istemci.connect(MQTT_CLIENT_NAME, MQTT_PROJECT_NAME, MQTT_TOKEN))//gözükecek isim, projenin adı, token
{
    Serial.print(".");
    delay(1000);
  }
  Serial.println("Baglandi");
  }
  //ÜÇ PARAMETRE ALIR: GÖNDEREN KİŞİNİN ADI, VERİNİN GÖNDERİLECEĞİ PROJENİN ADI/TOKEN
