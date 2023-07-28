
#include <ESP8266WiFi.h>
#include <WiFiClientSecure.h>
#include <UniversalTelegramBot.h>

char ssid[] = "Replace Your SSID Here";     // your network SSID (name)
char password[] = "Replace your Password Here"; // your network key

// Initialize Telegram BOT
#define BOTtoken "Replace the bot token over here" // your Bot Token (Get from Botfather)

WiFiClientSecure client;
UniversalTelegramBot bot(BOTtoken, client);

int botRequestDelay = 500;
unsigned long lastTimeBotRan;

int LED_1_STATUS = 0;
int LED_1_PIN = D1;


int LED_2_STATUS = 0;
int LED_2_PIN = D2;


int ANALOG_SENSOR_PIN = D3;
int DIGITAL_SENSOR_PIN = D4;

int TRIGGER = 0;

int auth=0;



void handleNewMessages(int numNewMessages) {
  
  
  Serial.println("handleNewMessages");
  Serial.println(String(numNewMessages));


  

  for (int i=0; i<numNewMessages; i++) {
    String chat_id = String(bot.messages[i].chat_id);

    Serial.print("ChatID :");
    Serial.println(chat_id);
    
    String text = bot.messages[i].text;

    String from_name = bot.messages[i].from_name;
    
    if (from_name == "") 
    from_name = "Guest";
    
    
    if (text == "/LED1ON" || text=="/led1on") {
      digitalWrite(LED_1_PIN,HIGH);
      LED_1_STATUS = 1;
      bot.sendMessage(chat_id, "LED-1 is Now 'ON'", "");
    }

    else if (text == "/LED1OFF" || text=="/led1off") {
      digitalWrite(LED_1_PIN,LOW);
      LED_1_STATUS = 0;
      bot.sendMessage(chat_id, "LED-1 is Now 'OFF'", "");
    }

    else if (text == "/LED2ON" || text=="/led2on") {
      digitalWrite(LED_2_PIN,HIGH);
      LED_2_STATUS = 1;
      bot.sendMessage(chat_id, "LED-2 is Now 'ON'", "");
    }

    else if (text == "/LED2OFF" || text=="/led2off") {
      digitalWrite(LED_2_PIN,LOW);
      LED_2_STATUS = 0;
      bot.sendMessage(chat_id, "LED-2 is Now 'OFF'", "");
    }


    else if (text == "/AnalogSensorValue" || text=="/analogsensorvalue") {
      String reply_with = "Analog Sensor Value: ";
      reply_with += analogRead(ANALOG_SENSOR_PIN);
      bot.sendMessage(chat_id, reply_with, "");
    }

    else if (text == "/DigitalSensorValue" || text=="/digitalsensorvalue") {
      String reply_with = "Digital Sensor Value: ";
      reply_with += digitalRead(DIGITAL_SENSOR_PIN);
      bot.sendMessage(chat_id, reply_with, "");
    }
    
    

      else if (text == "/ActivateTrigger" || text=="/activatetrigger")
      {
      bot.sendMessage(chat_id, " \"Trigger activated\" for digital sensor, sends text message when sensor value is HIGH \n", "");
      TRIGGER=1;
      }

    else if (text == "/DeactivateTrigger" || text=="/deactivatetrigger")
      {
      bot.sendMessage(chat_id, "Trigger is de-activated for digital sensor\n", "");
      TRIGGER=0;
      }

    
    else if (text == "/Status" || text=="/status") {

      String status_message;

      status_message +="Here is the status update \n\n";
      
      if(LED_1_STATUS){
        status_message +="LED-1 is ON\n";
      } else {
        status_message +="LED-1 is OFF\n";
      }

      if(LED_2_STATUS){
        status_message +="LED-2 is ON\n";
      } else {
        status_message +="LED-2 is OFF\n";
      }

      if(TRIGGER){
        status_message +="Trigger is Active\n";
      } else {
        status_message +="Trigger is Inactive\n";
      }

      bot.sendMessage(chat_id, status_message, "");
      
    }


     else if (text == "/Reset" || text =="/reset")
      {
        LED_1_STATUS = 0;
        LED_2_STATUS = 0;
        digitalWrite(LED_1_PIN,LOW);
        digitalWrite(LED_2_PIN,LOW);
        TRIGGER=0;
       
        bot.sendMessage(chat_id, "Reset Done\n", "");
      }

      

    else if (text == "/Start" || text == "/start") {
      String welcome_message = "Hello " + from_name + ",\n" + "Welcome to home automation control bot. \n\n";
      
      welcome_message += "To start off with, here are the commands for automation! \n\n";
      
      welcome_message += "/LED1ON : to switch on LED-1\n";
      welcome_message += "/LED1OFF : to switch off LED-1\n";
      welcome_message += "/LED2ON : to switch on LED-2\n";
      welcome_message += "/LED2OFF : to switch off LED-2\n\n";
      
      welcome_message += "/AnalogSensorValue : Returns reading of Analog input pin\n";
      welcome_message += "/DigitalSensorValue : Returns reading of Digital input pin\n\n";
      
      welcome_message += "/ActivateTrigger : Activates Digital Sensor Trigger\n";
      welcome_message += "/DeactivateTrigger : Deactivates Digital Sensor Trigger\n\n";
      
      welcome_message += "/Status : Returns the status of the Components\n\n";

      welcome_message += "/Reset : To reset all components\n\n";
      
      welcome_message += "You can also access commands panel using /Controls\n\n";
      
      welcome_message += "You can know about the project by using /AboutMe command\n\n";
      bot.sendMessage(chat_id, welcome_message, "Markdown");

      
    }

    else if(text=="/Commands" || text =="/commands" || text == "/commandslist")
    {
      String commands = "Here is the list of commands.\n\n";
      commands += "/LED1ON : to switch on LED-1\n";
      commands += "/LED1OFF : to switch off LED-1\n";
      commands += "/LED2ON : to switch on LED-2\n";
      commands += "/LED2OFF : to switch off LED-2\n\n";
      
      commands += "/AnalogSensorValue : Returns reading of Analog input pin\n";
      commands += "/DigitalSensorValue : Returns reading of Digital input pin\n\n";
      
      commands += "/ActivateTrigger : Activates Digital Sensor Trigger\n";
      commands += "/DeactivateTrigger : Deactivates Digital Sensor Trigger\n\n";

      commands += "/Reset : To reset all components\n\n";
      
      commands += "/Commands : Returns all the commands available\n";
      commands += "/Controls : Returns control panel for LEDS\n";
      
      commands += "/Status : Returns the status of the Components\n\n";
      
      commands += "/AboutMe : To know more about me\n";
      bot.sendMessage(chat_id, commands, "Markdown");
    }

     else if(text=="/Help" || text=="/help")
    {
      String welcome = "Hi There! This is home automation controlling bot using telegram. \n\n";

      welcome += "Inorder to start off press /Start which will guide you. \n\nStuck at any point? type /Commands or   /Controls for more help!";
      bot.sendMessage(chat_id, welcome, "Markdown");
    }

    else if (text == "/Controls" || text=="/controls")
      {
        
      String ControlPadJson = "[[\"/LED1ON\", \"/LED1OFF\"],[\"/LED2ON\", \"/LED2OFF\"],[\"/AnalogSensorValue\", \"/DigitalSensorValue\"],[\"/ActivateTrigger\", \"/DeactivateTrigger\"],[\"/Reset\", \"/Status\"]]";                  
      bot.sendMessageWithReplyKeyboard(chat_id, "Here is your control panel !", "", ControlPadJson, true);
      }


    
    else if(text == "/AboutMe" || text=="/aboutme")
    {
      String AboutMeJson = "[[{ \"text\" : \"Open URL\", \"url\" : \"https://github.com/harshithtunuguntla/HomeAutomation-TelegramBot\" }]]";
      bot.sendMessageWithInlineKeyboard(chat_id, "Please follow the link to know more about me 😁", "", AboutMeJson);
    }


    
  }
}


void setup() {
  Serial.begin(115200);

  pinMode(ANALOG_SENSOR_PIN,INPUT);
  pinMode(DIGITAL_SENSOR_PIN,INPUT);

  pinMode(LED_1_PIN, OUTPUT);
  pinMode(LED_2_PIN,OUTPUT);
  delay(10);
  digitalWrite(LED_1_PIN, LOW);
  digitalWrite(LED_2_PIN, LOW);


  

  client.setInsecure();

  WiFi.mode(WIFI_STA);
  WiFi.disconnect();
  delay(100);

  Serial.print("Connecting Wifi: ");
  Serial.println(ssid);
  WiFi.begin(ssid, password);

  while (WiFi.status() != WL_CONNECTED) {
    Serial.print(".");
    delay(500);
  }

  Serial.println("");
  Serial.println("WiFi connected");
  Serial.print("IP address: ");
  Serial.println(WiFi.localIP());

  digitalWrite(LED_1_PIN,HIGH);
  delay(500);
  digitalWrite(LED_2_PIN,HIGH);
  delay(500);
  digitalWrite(LED_1_PIN,LOW);
  digitalWrite(LED_2_PIN,LOW);
  delay(50);
  digitalWrite(LED_1_PIN,HIGH);
  digitalWrite(LED_2_PIN,HIGH);
  delay(50);
  digitalWrite(LED_1_PIN,LOW);
  digitalWrite(LED_2_PIN,LOW);
  
}

void loop() {
  if (millis() > lastTimeBotRan + botRequestDelay)  {
    Serial.println("New ITER");
    int numNewMessages = bot.getUpdates(bot.last_message_received + 1);

    while(numNewMessages) {
      Serial.println("got response");
      handleNewMessages(numNewMessages);
      numNewMessages = bot.getUpdates(bot.last_message_received + 1);
    }
    String chat_id = String(bot.messages[0].chat_id);

    //triggering message
    if(TRIGGER)
    {
    if(digitalRead(DIGITAL_SENSOR_PIN)==1)
    bot.sendMessage(chat_id, "TRIGGER ALERT : SENSOR VALUE READ HIGH", "");
    }

    lastTimeBotRan = millis();
  }
}
