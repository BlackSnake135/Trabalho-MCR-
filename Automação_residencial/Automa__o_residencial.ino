#include <TFT_eSPI.h>
#include <SPI.h>
#include <WiFi.h>
#include <PubSubClient.h>
#include <Adafruit_Sensor.h>
#include "DHT.h"
TFT_eSPI tft = TFT_eSPI();

DHT my_sensor(5, DHT22);

float temperature, humity;   
const char* ssid = "ifsp-ibge-1";
const char* password = "ifspcatanduva";
const char* mqttServer = "broker.hivemq.com";
int port = 1883;
String stMac;
char mac[50];
char clientId[50];

WiFiClient espClient;
PubSubClient client(espClient);

const int Quarto = 21;
const int Quarto2 = 19;
const int Sala = 3;
const int Cozinha = 18;
const int DHTPIN = 5;
const int potpin = 39;
int potvalue = 0;
int ven = 22; 

void setup() {
  Serial.begin(115200);
  randomSeed(analogRead(0));

  delay(10);
  Serial.println();
  Serial.print("Connecting to ");
  Serial.println(ssid);
  tft.init();
  tft.setRotation(3);
  tft.fillScreen(TFT_BLACK);
  tft.setTextSize(2);
  tft.setCursor(40,20);
  tft.setTextColor(TFT_WHITE);
  tft.print("BEM VINDO");
  tft.setTextSize(2);
  tft.setCursor(40,40);
  tft.println("AUTOMACAO RESIDENCIAL");
  tft.setCursor(40,60);
  tft.println("GABRIEL SANTOS/TURTLE");
  tft.setCursor(40,80);
  tft.println("JOAO MARCIO/JAYB");
  my_sensor.begin();

  wifiConnect();

  Serial.println("");
  Serial.println("WiFi connected");
  Serial.println("IP address: ");
  Serial.println(WiFi.localIP());
  Serial.println(WiFi.macAddress());
  stMac = WiFi.macAddress();
  stMac.replace(":", "_");
  Serial.println(stMac);
  
  client.setServer(mqttServer, port);
  client.setCallback(callback);
  pinMode(Quarto, OUTPUT);
  pinMode(Quarto2, OUTPUT);
  pinMode(Sala, OUTPUT);
  pinMode(Cozinha, OUTPUT);
  pinMode(ven, OUTPUT);
  pinMode(potpin, INPUT_PULLUP);
}

void wifiConnect() {
  WiFi.mode(WIFI_STA);
  WiFi.begin(ssid, password);
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }
}

void mqttReconnect() {
  while (!client.connected()) {
    Serial.print("Attempting MQTT connection...");
    long r = random(1000);
    sprintf(clientId, "clientId-%ld", r);
    if (client.connect(clientId)) {
      Serial.print(clientId);
      Serial.println(" connected");
      client.subscribe("topic1/topic");
    } else {
      Serial.print("failed, rc=");
      Serial.print(client.state());
      Serial.println(" try again in 5 seconds");
      delay(5000);
    }
  }
}

void callback(char* topic, byte* message, unsigned int length) {
  Serial.print("Mensagem recebida no topico: ");
  Serial.print(topic);
  Serial.print(". Messagem: ");
  String stMessage;
  
  for (int i = 0; i < length; i++) {
    Serial.print((char)message[i]);
    stMessage += (char)message[i];
  }
  Serial.println();

   if (String(topic) == "topic1/topic") {
    Serial.print("Saida alterada para ");
    if(stMessage == "Quarto"){
      tft.fillScreen(TFT_BLACK);
      tft.setTextSize(2);
      tft.setCursor(40,20);
      tft.setTextColor(TFT_WHITE);
      tft.println("AUTOMACAO RESIDENCIAL");
      tft.setTextSize(2);
      tft.setCursor(60,60);
      tft.setTextColor(TFT_YELLOW);
      tft.print("QUARTO: LIGADO");
      tft.setCursor(30,100);
      tft.setTextColor(TFT_BLUE);
      tft.println("Temperatura: ");
      tft.setCursor(30,120);
      tft.println(temperature);
      tft.setCursor(30,140);
      tft.println("Humidade: ");
      tft.setCursor(30,160);
      tft.println(humity);
      digitalWrite(Quarto, HIGH);
    }
    else if(stMessage == "Qoff"){
       tft.fillScreen(TFT_BLACK);
      tft.setTextSize(2);
      tft.setCursor(40,20);
      tft.setTextColor(TFT_WHITE);
      tft.println("AUTOMACAO RESIDENCIAL");
      tft.setTextSize(2);
      tft.setCursor(60,60);
      tft.setTextColor(TFT_YELLOW);
      tft.print("QUARTO: DESLIGADO");
      tft.setCursor(30,100);
      tft.setTextColor(TFT_BLUE);
      tft.println("Temperatura: ");
      tft.setCursor(30,120);
      tft.println(temperature);
      tft.setCursor(30,140);
      tft.println("Humidade: ");
      tft.setCursor(30,160);
      tft.println(humity);
      digitalWrite(Quarto, LOW);
    }
  }
   if (String(topic) == "topic1/topic") {
    Serial.print("Saida alterada para ");
    if(stMessage == "Quarto2"){
      tft.fillScreen(TFT_BLACK);
      tft.setTextSize(2);
      tft.setCursor(40,20);
      tft.setTextColor(TFT_WHITE);
      tft.println("AUTOMACAO RESIDENCIAL");
      tft.setTextSize(2);
      tft.setCursor(60,60);
      tft.setTextColor(TFT_YELLOW);
      tft.print("QUARTO 2: LIGADO");
      tft.setCursor(30,100);
      tft.setTextColor(TFT_BLUE);
      tft.println("Temperatura: ");
      tft.setCursor(30,120);
      tft.println(temperature);
      tft.setCursor(30,140);
      tft.println("Humidade: ");
      tft.setCursor(30,160);
      tft.println(humity);
      digitalWrite(Quarto2, HIGH);
    }
    else if(stMessage == "Q2off"){
       tft.fillScreen(TFT_BLACK);
      tft.setTextSize(2);
      tft.setCursor(40,20);
      tft.setTextColor(TFT_WHITE);
      tft.println("AUTOMACAO RESIDENCIAL");
      tft.setTextSize(2);
      tft.setCursor(60,60);
      tft.setTextColor(TFT_YELLOW);
      tft.print("QUARTO 2: DESLIGADO");
      tft.setCursor(30,100);
      tft.setTextColor(TFT_BLUE);
      tft.println("Temperatura: ");
      tft.setCursor(30,120);
      tft.println(temperature);
      tft.setCursor(30,140);
      tft.println("Humidade: ");
      tft.setCursor(30,160);
      tft.println(humity);
      digitalWrite(Quarto2, LOW);
    }
}
  if (String(topic) == "topic1/topic") {
    Serial.print("Saida alterada para ");
    if(stMessage == "Sala"){
      tft.fillScreen(TFT_BLACK);
      tft.setTextSize(2);
      tft.setCursor(40,20);
      tft.setTextColor(TFT_WHITE);
      tft.println("AUTOMACAO RESIDENCIAL");
      tft.setTextSize(2);
      tft.setCursor(60,60);
      tft.setTextColor(TFT_YELLOW);
      tft.print("SALA: LIGADA");
      tft.setCursor(30,100);
      tft.setTextColor(TFT_BLUE);
      tft.println("Temperatura: ");
      tft.setCursor(30,120);
      tft.println(temperature);
      tft.setCursor(30,140);
      tft.println("Humidade: ");
      tft.setCursor(30,160);
      tft.println(humity);
      digitalWrite(Sala, HIGH);
    }
    else if(stMessage == "Soff"){
       tft.fillScreen(TFT_BLACK);
      tft.setTextSize(2);
      tft.setCursor(40,20);
      tft.setTextColor(TFT_WHITE);
      tft.println("AUTOMACAO RESIDENCIAL");
      tft.setTextSize(2);
      tft.setCursor(60,60);
      tft.setTextColor(TFT_YELLOW);
      tft.print("SALA: DESLIGADA");
      tft.setCursor(30,100);
      tft.setTextColor(TFT_BLUE);
      tft.println("Temperatura: ");
      tft.setCursor(30,120);
      tft.println(temperature);
      tft.setCursor(30,140);
      tft.println("Humidade: ");
      tft.setCursor(30,160);
      tft.println(humity);
      digitalWrite(Sala, LOW);
    }
}
  if (String(topic) == "topic1/topic") {
    Serial.print("Saida alterada para ");
    if(stMessage == "Con"){
      tft.fillScreen(TFT_BLACK);
      tft.setTextSize(2);
      tft.setCursor(40,20);
      tft.setTextColor(TFT_WHITE);
      tft.println("AUTOMACAO RESIDENCIAL");
      tft.setTextSize(2);
      tft.setCursor(60,60);
      tft.setTextColor(TFT_YELLOW);
      tft.print("COZINHA: LIGADA");
      tft.setCursor(30,100);
      tft.setTextColor(TFT_BLUE);
      tft.println("Temperatura: ");
      tft.setCursor(30,120);
      tft.println(temperature);
      tft.setCursor(30,140);
      tft.println("Humidade: ");
      tft.setCursor(30,160);
      tft.println(humity);
      digitalWrite(Cozinha, HIGH);
    }
    else if(stMessage == "Coff"){
       tft.fillScreen(TFT_BLACK);
      tft.setTextSize(2);
      tft.setCursor(40,20);
      tft.setTextColor(TFT_WHITE);
      tft.println("AUTOMACAO RESIDENCIAL");
      tft.setTextSize(2);
      tft.setCursor(60,60);
      tft.setTextColor(TFT_YELLOW);
      tft.print("COZINHA: DESLIGADA");
      tft.setCursor(30,100);
      tft.setTextColor(TFT_BLUE);
      tft.println("Temperatura: ");
      tft.setCursor(30,120);
      tft.println(temperature);
      tft.setCursor(30,140);
      tft.println("Humidade: ");
      tft.setCursor(30,160);
      tft.println(humity);
      digitalWrite(Cozinha, LOW);
    }
  }
} //CALBACK

int estado =0;
void loop() {
  humity = my_sensor.readHumidity();
  temperature = my_sensor.readTemperature();
 
  delay(10);
  if (!client.connected()) {
    mqttReconnect();
  }
  client.loop();
  
  potvalue = analogRead(potpin);
  Serial.println(potvalue);
  digitalWrite(ven, potvalue);
    
}
