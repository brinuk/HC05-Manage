/* Basic Bluetooth sketch connects (at 38400) the HC05 BT device
  and communicate using the serial monitor at 115200.
  
  Try HC05.linkHC05Ver2() first and if problems use HC05.linkHC05Ver3()
  HC05.linkHC05Ver3() wil switch to the second command mode on version 3 BT modules.

  HC05.proceed is a flag set by all set commands, can be used to monitor result.
  
  Interropgates BT for settings and sets up ready for pairing to a know BT mac address
  Connect HC05 VCC to Arduino pin 12
  Connect HC05 EN to Arduino pin 11 through a voltage divider. 
  Connect the HC05 GND to GND
  Connect the HC-05 TX to Arduino pin 2 RX. 
  Connect the HC-05 RX to Arduino pin 3 TX through a voltage divider.

List of available BT commands
  begin(); setBaudRate(String rate); getBaudRate(); information();setToCommandMode(); void locate(); sendAtCommand(String command);readHC05();
  linkHC05Ver2(); linkHC05Ver3(); readReply()reads HC05 reply and sets proceed flag; proceed;// flag for proceeding to next step
  getVersion(); getPassword(); getRole(); getMode(); getMacAddress(); setToDefault(); setToMaster();setRemotePassword(String PW);reset();
  initialize(); forgetConnections(); pair(String macAddress); bind(String macAddress); link(String macAddress); setInquiryMode(); getStateOfCommandMode();
  getNameOfRemoteBT(); setAcceptFixedAddress(); NBDelay(unsigned long delayTime) non blocking delay;
  
*/

/*-----( Import needed libraries )-----*/

#include <HC05Manage.h>




/*-----( Declare Constants and Pin Numbers )-----*/



/*-----( Declare objects )-----*/
HC05Manage HC05;

/*-----( Declare Variables )-----*/



void setup()   /****** SETUP: RUNS ONCE ******/
{ 
  HC05.macAddress = "98d3,31,fd2280";//set mac address of BT device to connect to.
  HC05.password = "0000";//set password for other BT device
  HC05.baudRate = "57600,0,0";//set baud rate, no stop bit, no parity check for BT connection 
  HC05.proceed = false;//set flag
  HC05.begin();//start communication
  HC05.setToCommandMode();//set AT command mode
  HC05.locate();//check if accepting commands
  if(HC05.proceed)//BT in command mode
  {
    HC05.setBaudRate(HC05.baudRate);
    HC05.information();
    HC05.linkHC05Ver2();//select version
    //HC05.linkHC05Ver3();
  }

  
  


}
//----end setup----

void loop()   /****** LOOP: RUNS CONSTANTLY ******/

  {  
    
  }  

//--Loop Ends---



//*********Functions************************



 
//*********( THE END )***********
