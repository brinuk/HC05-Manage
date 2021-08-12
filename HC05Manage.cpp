/*
  HC05Manage.cpp - Library with HC05/6 BT devices connects at 38400 to the HC05/6 BT device
  and communicate using the serial monitor at 115200.
  Interrogates BT for settings and sets up ready for pairing to a known BT mac address
  Connect HC05 VCC to Arduino pin 12
  Connect HC05 EN to Arduino pin 11 through a voltage divider. 
  Connect the HC05 GND to GND
  Connect the HC-05 TX to Arduino pin 2 RX. 
  Connect the HC-05 RX to Arduino pin 3 TX through a voltage divider.
  Functions that use readReply() will set the proceed flag to True if OK is received from the BT
  Created by Brian Lambert.
  Released into the public domain.
*/

#include "Arduino.h"
#include "HC05Manage.h"


SoftwareSerial BTserial(2, 3); // RX | TX
// Connect the HC-05 TX to Arduino pin 2 RX. 
// Connect the HC-05 RX to Arduino pin 3 TX through a voltage divider.


HC05Manage::HC05Manage()
{
  
}

//Start up everything
boolean HC05Manage::begin()
{
  // start the serial communication with the host computer
    Serial.begin(115200);
    Serial.println(F("Comms with Arduino started at 115200"));
 // start communication with the HC-05 using 38400
    BTserial.begin(38400);  
    Serial.println(F("Comms with HC05 started at 38400"));
    pinMode(HC05AtPin, OUTPUT); //HC05 to command mode
    pinMode(HC05PowerPin, OUTPUT); //Power up HC05
}

//****check BT is in command mode****
  void HC05Manage::locate()
  {
    sendAtCommand("AT");
    Serial.print(readReply());
  }

String HC05Manage::getBaudRate()
{
    sendAtCommand("AT+UART?");
	return readHC05();
}

String HC05Manage::getVersion()
{
    sendAtCommand("AT+VERSION?");
    return readHC05();
}

String HC05Manage::getPassword()
{
    sendAtCommand("AT+PSWD?");
    return readHC05();
}

String HC05Manage::getRole()
{
    sendAtCommand("AT+ROLE?");
    return readHC05();
}

String HC05Manage::getMode()
{
    sendAtCommand("AT+CMODE?");
    return readHC05();
}


String HC05Manage::getMacAddress()
{
    sendAtCommand("AT+ADDR?");
    return readHC05();
}

void HC05Manage::setBaudRate(String rate)
{
    sendAtCommand("AT+UART="+rate);
    Serial.print(readReply());
}

void HC05Manage::setToDefault()
{
    sendAtCommand("AT+ORGL");//default
    Serial.print(readReply());
}

void HC05Manage::setToMaster()
{
  sendAtCommand("AT+ROLE=1");//set to master
  Serial.print(readReply());
}

void HC05Manage::setRemotePassword(String PW)
{
    sendAtCommand("AT+PSWD=\"" + PW + "\"");
    Serial.print(readReply());
}

void HC05Manage::reset()
{
    sendAtCommand("AT+RESET");//reset module
    Serial.print(readReply());
}

void HC05Manage::initialize()
{
 
  sendAtCommand("AT+INIT");//initialize module
  Serial.print(readReply());
}

void HC05Manage::forgetConnections()
{
 
  sendAtCommand("AT+RMAAD");//forget previous connections
  Serial.print(readReply());
}

void HC05Manage::pair(String macAddress)
{
 
  sendAtCommand("AT+PAIR=\"" + macAddress + "\",5");//pair master and slave
  Serial.print(readReply());
}

void HC05Manage::bind(String macAddress)
{
 
  sendAtCommand("AT+BIND=\"" + macAddress + "\"");//bind master and slave
  NBDelay(1000);
  Serial.print(readReply());
}

void HC05Manage::link(String macAddress)
{
 
  sendAtCommand("AT+LINK=\"" + macAddress + "\"");//bind master and slave
  NBDelay(1000);
  Serial.print(readReply());
}


void HC05Manage::setInquiryMode()
{
	sendAtCommand("AT+INQM=0,5,5");
    Serial.print(readReply());
}

void HC05Manage::getStateOfCommandMode()
{
	sendAtCommand("AT+STATE");
    Serial.print(readHC05());
}

void HC05Manage::getNameOfRemoteBT()
{
	sendAtCommand("AT+RNAME?" + macAddress);
    NBDelay(2000);
    Serial.print(readHC05());
}

void HC05Manage::setAcceptFixedAddress()
{
	sendAtCommand("AT+CMODE=0");
	Serial.print(readReply());
}




//******get information from BT*************
void HC05Manage::information()
{
	  Serial.print("Version ");
      Serial.print(getVersion());
	  Serial.print("Password ");
      Serial.print(getPassword());
	  Serial.print("Role 1-master, 0-slave ");
      Serial.print(getRole());
	  Serial.print("Mode 1-any device, 0-fixed address ");
      Serial.print(getMode());
	  Serial.print("Baud rate ");
      Serial.print(getBaudRate());
	  Serial.print("Mac address ");
      Serial.print(getMacAddress());
}

//******put HC05 into AT cammand mode******
  void HC05Manage::setToCommandMode()
    {
      digitalWrite(HC05AtPin, HIGH);//set HC05 to Command Mode
      NBDelay(500);
      digitalWrite(HC05PowerPin, HIGH);
      NBDelay(1500);
      digitalWrite(HC05AtPin, LOW);
      Serial.println(F("HC05 set to AT command mode"));
    Serial.println("****************");
    }

   //*****send AT command to HC05****//
void HC05Manage::sendAtCommand(String command)
    {
   writeString(command);
    NBDelay(1000);
    }
    
 //**END send AT command*******//

//***************Read HC05 ******************//
String HC05Manage::readHC05()
  {
    String response = "";
    char c ="";
    while (BTserial.available())
    {  
        c = BTserial.read();
        response = response + c;
    }
	//Serial.print(response);
    return response;
  }
//*****END ReadHC05******//

//**************** serially push out a String to BT***************//

void HC05Manage::writeString(String stringData)
{ 

  for (int i = 0; i < stringData.length(); i++)
  {
    BTserial.write(stringData[i]);   // Push each char 1 by 1 on each loop pass
  }
  BTserial.write("\r\n");

}
//**** end writeString****

//****link HC05 version 2 to BT module of known address

void HC05Manage::linkHC05Ver2()
{
  //Serial.print("Set to default ");
  //setToDefault();
  //NBDelay(500);
  Serial.print("Set to Master ");
  setToMaster();
   //NBDelay(500);
  Serial.print("set remote password ");
  setRemotePassword(password);
  Serial.print("set to accept fixed address ");
  setAcceptFixedAddress();
  Serial.print("Forget connections ");
  forgetConnections();
  Serial.print("Bind ");
  bind(macAddress);
  NBDelay(2000);
  Serial.print("Reset ");
  reset();
  Serial.println("If bound, LED will flash twice every 3 seconds");
}
//****End link HC05 version 2 to BT module of known address

//**link a HC05 version 3******

 void HC05Manage::linkHC05Ver3()
 {
  Serial.print("clear saved connections   ");
  forgetConnections();
  Serial.print("set to master ");
  setToMaster();
  digitalWrite(HC05AtPin,HIGH);
  Serial.println("Simulating button pressed");
  Serial.print("Reset ");
  reset();
  NBDelay(3000);
  Serial.print(readReply());
  digitalWrite(HC05AtPin,LOW);
  Serial.println("Simulating button released");
  Serial.print("set to accept fixed address ");
  setAcceptFixedAddress();
  Serial.print("enquiry in standard mode 5 connections in 5 secs ");
  setInquiryMode();
  Serial.print("set password ");
  setRemotePassword(password);
  Serial.print("set baudrate ");
  setBaudRate(baudRate);
  Serial.println("setting Arduino serial baud rate to 9600");
  Serial.println("*************SET SCREEN TO 9600 AND IGNORE RUBBISH*************");
  NBDelay(5000);
  Serial.begin(9600);//arduino restarts
  Serial.println();
  Serial.println("Changing to new command Mode");
  Serial.println("powering down HC05 ");
  digitalWrite(HC05PowerPin, LOW);
  NBDelay(4000);
  digitalWrite(HC05AtPin,LOW);
  Serial.println("Simulating button released");
  Serial.println("powering up HC05 without button pressed");
  digitalWrite(HC05PowerPin, HIGH);
  digitalWrite(HC05AtPin,HIGH);
  Serial.println("Simulating button pressed");
  Serial.println("in new command mode");
  NBDelay(4000);
  readHC05();//clear buffer
  Serial.print("Pair ");
  pair(macAddress);
  Serial.print("Bind ");
  bind(macAddress);
  NBDelay(2000);
  digitalWrite(HC05AtPin,LOW);
  Serial.println("Simulating button released");
  Serial.print("Reset ");
  reset();
  Serial.println("If bound LED blicks twice every 3 seconds");
 }

 //****returns reply from BT and sets proceed flag****
  String HC05Manage::readReply()
  {
	proceed = false;
    reply = readHC05();
    if(reply.indexOf("OK") >= 0)
      {
		proceed = true;
      }
	return reply;
  }

  void HC05Manage::NBDelay(unsigned long delayTime)
{
      startTime = millis();
      while(millis() - startTime <= delayTime)
        {
          yield();
        }
}