# home_automation_telegram
Controlling of appliances using Telegram Bot and NodeMCU Wi-Fi module.

There are 3 steps involved to complete the automation/n
Step 1 - Creating a Bot
For this you need to visit bot named "BotFather" on telegram and create your-self a newbot with the command "/newbot". After naming the bot, you will receive a bot-token which you need to replace in the ino code provided. Later on change the SSID, Password in the ino file according to your network.

Step 2 - Uploading ino file into NodeMCU
Install required drivers for NodeMCU and then upload the code onto nodemcu

Step 3 - Connections
This code is written for two LED's and two sensors(Digital & Analog). Connect the LED's and Sensors according the respective pins(given in the code).

Now you are set to start the bot and experience it. Start off by entering the command "/start"

Commands
"/LED1ON " : to switch on LED-1

"/LED1OFF" : to switch off LED-1

"/LED2ON " : to switch on LED-2

"/LED2OFF" : to switch off LED-2

"/AnalogSensorValue" : Returns reading of Analog input pin

/DigitalSensorValue" : Returns reading of Digital input pin

"/ActivateTrigger " : Activates Digital Sensor Trigger

"/DeactivateTrigger" : Deactivates Digital Sensor Trigger

"/Reset" : To reset all components

"/Commands" : Returns all the commands available

"/Controls" : Returns control panel for LEDS

"/Status" : Returns the status of the Components

"/AboutMe" : To know more about this project (which will land you in this repository)

Thankyou !!😁
