// MQTT abone örnek uygulaması
//****************************************************************
#include <ESP8266WiFi.h>
#include <MQTTClient.h>
#include "arduino_secrets.h"


char sifre2[3] = "";                         // Yeni şifre değişkeni (mesajdan gelecek "09" gibi kısa değerler için)

WiFiClient wifi_istemci;                     // Wi-Fi istemci nesnesi
MQTTClient mqtt_istemci;                     // MQTT istemci nesnesi
//****************************************************************
void setup() 
{
  Serial.begin(9600);                        // Seri portu başlat
  delay(200);                                // 200 ms bekle
  Serial.println("Wi-Fi ağına bağlanıyoruz");

  WiFi.mode(WIFI_STA);                       // İstasyon modunda çalış
  WiFi.begin(ssid, password);               // Wi-Fi ağına bağlan

  //------- Wi-Fi ağına bağlanıncaya kadar beklenilen kısım ------------
  while (WiFi.status() != WL_CONNECTED) 
  { 
    delay(500);                              // Bu arada her 500 ms'de bir seri ekrana yan yana noktalar yazdırılarak
    Serial.print(".");                       // Görsellik sağlanıyor.
  }
  //-------------------------------------------------------------------
  
  Serial.println("");                        // Bir alt satıra geçiliyor.
  Serial.println("Bağlantı sağlandı...");    // Seri ekrana bağlantının kurulduğu bilgisi gönderiliyor.

  Serial.print("Alınan IP adresi: ");        // Kablosuz ağdan alınan IP adresi
  Serial.println(WiFi.localIP());            // Kablosuz ağdan alınan IP adresi

  mqtt_istemci.begin(MQTT_SERVER, wifi_istemci); // MQTT istemciyi başlat
  mqtt_istemci.onMessage(mesaj_geldi);       // Mesaj geldiğinde gidilecek fonksiyon

  baglan(); 
  mqtt_istemci.subscribe(MQTT_TOPIC);
}
//****************************************************************
void loop() 
{
  mqtt_istemci.loop();                       // Broker'a mesaj göndermek için gerekli olan satır
  
  if (!mqtt_istemci.connected())             // Broker'a bağlandı mı?
    baglan();                                // Bağlanmamışsa, bağlan()

  delay(1000);
}
//****************************************************************
void baglan()
{
   while (!mqtt_istemci.connect(MQTT_CLIENT_NAME,MQTT_PROJECT_NAME,MQTT_TOKEN))  
   {
    Serial.print(",");
    delay(1000);
  }
   Serial.println("\nMQTT baglandi");
}
//****************************************************************
void mesaj_geldi(String &konu, String &veri) {
  Serial.println(konu + ": " + veri);        // Gelen veri ile konuyu ekrana yazdır
  
  // Veri "202013171070:09" formatında geliyor, "09" kısmını çekip 'sifre2'ye atayalım
  int pos = veri.indexOf(':');
  if (pos != -1 && pos + 2 < veri.length()) {
    veri.substring(pos + 1, pos + 3).toCharArray(sifre2, 3); // "09" kısmını 'sifre2' değişkenine atar
    Serial.print("sifre2 değişkenine atanan değer: ");
    Serial.println(sifre2);                   // Atanan değeri ekrana yazdır
  }
}
