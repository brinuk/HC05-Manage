

#ifndef HC05Manage_h
#define HC05Manage_h

/*-----( Import needed libraries )-----*/
#if (ARDUINO >= 100)
 #include "Arduino.h"
#else
 #include "WProgram.h"
#endif

#include "SoftwareSerial.h"

/*-----( Declare Constants and Pin Numbers )-----*/

#define HC05PowerPin 12 //power to HC05
#define HC05AtPin 11 //puts HC05 into command mode


class HC05Manage
{
/*-----( Declare Variables and functions )-----*/
  public:
    HC05Manage();
	bool begin();
	void setBaudRate(String rate);
	String getBaudRate();
	void information();//gprints settings of BT
	void setToCommandMode();
	void locate();//check if BT in command mode
	void sendAtCommand(String command);
	String readHC05();
	void linkHC05Ver2();
	void linkHC05Ver3();
	String password;
	String macAddress;
	String baudRate;
	String readReply();//reads HC05 reply and sets proceed flag
	bool proceed;// flag for proceeding to next step
	String getVersion();
	String getPassword();
	String getRole();
	String getMode();
	String getMacAddress();
	void setToDefault();
	void setToMaster();
	void setRemotePassword(String PW);
	void reset();
	void initialize();
	void forgetConnections();
	void pair(String macAddress);
	void bind(String macAddress);
	void link(String macAddress);
	void setInquiryMode();
	void getStateOfCommandMode();
	void getNameOfRemoteBT();
	void setAcceptFixedAddress();
	void NBDelay(unsigned long delayTime);
	
    
  private:
	String reply;
	char c;
	unsigned long startTime;
	void writeString(String stringData);
	
};

#endif
