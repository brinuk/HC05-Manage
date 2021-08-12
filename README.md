# HC05-Manage
Easily manage the setup and binding of Version 2 or version 3 Bluetooth modules

  Bluetooth library connects (at 38400) to the HC05 BT device
  and communicates using the serial monitor at 115200.
  Interrogates BT for settings and sets up BT ready for binding to a known BT mac address
  
  List of available BT commands
  
  begin(); setBaudRate(String rate); getBaudRate(); information();setToCommandMode(); void locate(); sendAtCommand(String command);readHC05();
  linkHC05Ver2(); linkHC05Ver3(); readReply()reads HC05 reply and sets proceed flag; proceed;// flag for proceeding to next step
  getVersion(); getPassword(); getRole(); getMode(); getMacAddress(); setToDefault(); setToMaster();setRemotePassword(String PW);reset();
  initialize(); forgetConnections(); pair(String macAddress); bind(String macAddress); link(String macAddress); setInquiryMode(); getStateOfCommandMode();
  getNameOfRemoteBT(); setAcceptFixedAddress(); NBDelay(unsigned long delayTime) non blocking delay;
  
  See example - Try HC05.linkHC05Ver2() first and if problems use HC05.linkHC05Ver3()
  HC05.linkHC05Ver3() will switch to the second command mode on version 3 BT modules.

  HC05.proceed is a flag set by all "set" commands, can be used to monitor the result.
 
  Connect HC05 VCC to Arduino pin 12
  Connect HC05 EN to Arduino pin 11 through a voltage divider. 
  Connect the HC05 GND to GND
  Connect the HC-05 TX to Arduino pin 2 RX. 
  Connect the HC-05 RX to Arduino pin 3 TX through a voltage divider.
  
