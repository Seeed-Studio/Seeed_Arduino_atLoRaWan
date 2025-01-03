/*
  LoRaWAN.cpp
  2013 Copyright (c) Seeed Technology Inc.  All right reserved.

  Author: Wayne Weng
  Date: 2016-10-17

  add rgb backlight fucnction @ 2013-10-15
  
  The MIT License (MIT)

  Permission is hereby granted, free of charge, to any person obtaining a copy
  of this software and associated documentation files (the "Software"), to deal
  in the Software without restriction, including without limitation the rights
  to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
  copies of the Software, and to permit persons to whom the Software is
  furnished to do so, subject to the following conditions:

  The above copyright notice and this permission notice shall be included in
  all copies or substantial portions of the Software.

  THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
  IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
  FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
  AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
  LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
  OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN
  THE SOFTWARE.1  USA
*/

#include "LoRaWan.h"


LoRaWanClass::LoRaWanClass(void)
{
    memset(_buffer, 0, 256);
}

void LoRaWanClass::init(void)
{
    SerialLoRa.begin(9600);
}

void LoRaWanClass::getVersion(char *buffer, short length, unsigned char timeout)
{
    if(buffer)
    {
        while(SerialLoRa.available())SerialLoRa.read();
        sendCommand("AT+VER=?\r\n");
        readBuffer(buffer, length, timeout);    
    }
}

void LoRaWanClass::getId(char *buffer, short length, unsigned char timeout)
{
    if(buffer)
    {
        while(SerialLoRa.available())SerialLoRa.read();
        sendCommand("AT+ID=?\r\n");
        readBuffer(buffer, length, timeout);    
    }
}

void LoRaWanClass::setId(char *DevAddr, char *DevEUI, char *AppEUI)
{
    char cmd[64];
    
    if(DevAddr)
    {
        memset(cmd, 0, 64);
        sprintf(cmd, "AT+ID=DevAddr,\"%s\"\r\n", DevAddr);
        sendCommand(cmd);
        delay(DEFAULT_TIMEWAIT);
    }
    
    if(DevEUI)
    {
        memset(cmd, 0, 64);
        sprintf(cmd, "AT+ID=DevEui,\"%s\"\r\n", DevEUI);
        sendCommand(cmd);
        delay(DEFAULT_TIMEWAIT);
    }
    
    if(AppEUI)
    {
        memset(cmd, 0, 64);
        sprintf(cmd, "AT+ID=AppEui,\"%s\"\r\n", AppEUI);
        sendCommand(cmd);
        delay(DEFAULT_TIMEWAIT);
    }
}

void LoRaWanClass::setKey(const char *NwkSKey,const char *AppSKey,const char *AppKey)
{
    char cmd[64];
    
    if(NwkSKey)
    {
        memset(cmd, 0, 64);
        sprintf(cmd, "AT+KEY=NWKSKEY,\"%s\"\r\n", NwkSKey);
        sendCommand(cmd);
#if _DEBUG_SERIAL_
        loraDebugPrint(DEFAULT_DEBUGTIME);
#endif
        delay(DEFAULT_TIMEWAIT);
    }

    if(AppSKey)
    {
        memset(cmd, 0, 64);
        sprintf(cmd, "AT+KEY=APPSKEY,\"%s\"\r\n", AppSKey);
        sendCommand(cmd);
#if _DEBUG_SERIAL_
        loraDebugPrint(DEFAULT_DEBUGTIME);
#endif
        delay(DEFAULT_TIMEWAIT);
    }

    if(AppKey)
    {
        memset(cmd, 0, 64);
        sprintf(cmd, "AT+KEY= APPKEY,\"%s\"\r\n", AppKey);
        sendCommand(cmd);
#if _DEBUG_SERIAL_
        loraDebugPrint(DEFAULT_DEBUGTIME);
#endif
        delay(DEFAULT_TIMEWAIT);
    }
}

void LoRaWanClass::setDataRate(_data_rate_t dataRate, _physical_type_t physicalType)
{
    char cmd[32];
    
    if(physicalType == EU434)sendCommand("AT+DR=EU433\r\n");
    else if(physicalType == EU868)sendCommand("AT+DR=EU868\r\n");
    else if(physicalType == US915)sendCommand("AT+DR=US915\r\n");
    else if(physicalType == US915HYBRID)sendCommand("AT+DR=US915HYBRID\r\n");
    else if(physicalType == AU915)sendCommand("AT+DR=AU915\r\n");
	else if(physicalType == AU915OLD)sendCommand("AT+DR=AU915OLD\r\n");
    else if(physicalType == CN470)sendCommand("AT+DR=CN470\r\n");
    else if(physicalType == CN779)sendCommand("AT+DR=CN779\r\n");
    else if(physicalType == AS923)sendCommand("AT+DR=AS923\r\n");
    else if(physicalType == KR920)sendCommand("AT+DR=KR920\r\n");
    else if(physicalType == IN865)sendCommand("AT+DR=IN865\r\n");
	
#if _DEBUG_SERIAL_
    loraDebugPrint(DEFAULT_DEBUGTIME);
#endif
    delay(DEFAULT_TIMEWAIT);
    
    memset(cmd, 0, 32);
    sprintf(cmd, "AT+DR=%d\r\n", dataRate);
    sendCommand(cmd);
#if _DEBUG_SERIAL_
    loraDebugPrint(DEFAULT_DEBUGTIME);
#endif
    delay(DEFAULT_TIMEWAIT);
}
 
void LoRaWanClass::setPower(short power)
{
    char cmd[32];
    
    memset(cmd, 0, 32);
    sprintf(cmd, "AT+POWER=%d\r\n", power);
    sendCommand(cmd);
#if _DEBUG_SERIAL_
    loraDebugPrint(DEFAULT_DEBUGTIME);
#endif
    delay(DEFAULT_TIMEWAIT);
}

void LoRaWanClass::setPort(unsigned char port)
{
    char cmd[32];
    
    memset(cmd, 0, 32);
    sprintf(cmd, "AT+PORT=%d\r\n", port);
    sendCommand(cmd);
#if _DEBUG_SERIAL_
    loraDebugPrint(DEFAULT_DEBUGTIME);
#endif
    delay(DEFAULT_TIMEWAIT);
}

void LoRaWanClass::enableChannels(unsigned char fistChannel, unsigned char lastChannel)
{
    char cmd[32];

    memset(cmd, 0, 32);
    sprintf(cmd, "AT+CH=NUM,%d-%d\r\n", fistChannel, lastChannel);
    sendCommand(cmd);
#if _DEBUG_SERIAL_
    loraDebugPrint(DEFAULT_DEBUGTIME);
#endif
    delay(DEFAULT_TIMEWAIT);
}




void LoRaWanClass::setAdaptiveDataRate(bool command)
{
    if(command)sendCommand("AT+ADR=ON\r\n");
    else sendCommand("AT+ADR=OFF\r\n");
#if _DEBUG_SERIAL_
    loraDebugPrint(DEFAULT_DEBUGTIME);
#endif
    delay(DEFAULT_TIMEWAIT);
}

void LoRaWanClass::setChannel(unsigned char channel, float frequency)
{
    char cmd[32];
    
    memset(cmd, 0, 32);
    sprintf(cmd, "AT+CH=%d,%d.%d\r\n", channel, (short)frequency, short(frequency * 10) % 10);
    sendCommand(cmd);
#if _DEBUG_SERIAL_
    loraDebugPrint(DEFAULT_DEBUGTIME);
#endif
    delay(DEFAULT_TIMEWAIT);
}

void LoRaWanClass::setChannel(unsigned char channel, float frequency, _data_rate_t dataRata)
{
    char cmd[32];
    
    memset(cmd, 0, 32);
    sprintf(cmd, "AT+CH=%d,%d.%d,%d\r\n", channel, (short)frequency, short(frequency * 10) % 10, dataRata);
    sendCommand(cmd);
#if _DEBUG_SERIAL_
    loraDebugPrint(DEFAULT_DEBUGTIME);
#endif
    delay(DEFAULT_TIMEWAIT);
}

void LoRaWanClass::setChannel(unsigned char channel, float frequency, _data_rate_t dataRataMin, _data_rate_t dataRataMax)
{
    char cmd[32];
    
    memset(cmd, 0, 32);
    sprintf(cmd, "AT+CH=%d,%d.%d,%d,%d\r\n", channel, (short)frequency, short(frequency * 10) % 10, dataRataMin, dataRataMax);
    sendCommand(cmd);
#if _DEBUG_SERIAL_
    loraDebugPrint(DEFAULT_DEBUGTIME);
#endif
    delay(DEFAULT_TIMEWAIT);
}

    
    

bool LoRaWanClass::transferPacketWithType(_packet_type_t packet_type,const char *buffer, unsigned char length,unsigned char timeout)
{
    if (length == 0) length = strlen(buffer);

    auto msgType = packet_type_lookup[packet_type];
    while(SerialLoRa.available()) SerialLoRa.read();

    char cmd[14+length];
    if(packet_type == _packet_type_t::TXLRSTR || packet_type == _packet_type_t::TXLRPKT)
    {
        sprintf(cmd, "AT+TEST=%s,\"%s\"\r\n", msgType, buffer);
    } else
    {
        sprintf(cmd, "AT+%s=\"%s\"\r\n", msgType, buffer);
    }

    sendCommand(cmd);
#if _DEBUG_SERIAL_
    SerialUSB.write(cmd);
#endif
    memset(_buffer, 0, BUFFER_LENGTH_MAX);
    readBuffer(_buffer, BUFFER_LENGTH_MAX, DEFAULT_TIMEOUT);
#if _DEBUG_SERIAL_    
    SerialUSB.print(_buffer);
#endif    
    char temp[32];
    if(packet_type == _packet_type_t::CMSG || packet_type == _packet_type_t::CMSGHEX)
        sprintf(temp, "+%s: ACK Received", msgType);
    else if(packet_type == _packet_type_t::TXLRSTR || packet_type == _packet_type_t::TXLRPKT)
        sprintf(temp, "+TEST: TX DONE");
    else
        sprintf(temp, "+%s: Done", msgType);

    if(strstr(_buffer, temp)) return true;
    return false;
}

bool LoRaWanClass::transferPacket(const char *buffer, unsigned char timeout)
{
    return transferPacketWithType(_packet_type_t::MSG,buffer, timeout);
}

bool LoRaWanClass::transferPacket(const unsigned char *buffer, unsigned char length, unsigned char timeout)
{
    char temp[length * 2 + 1];
    for(unsigned char i = 0; i < length; i ++)
    {
        sprintf(&temp[i*2],"%02x", buffer[i]);
    }

    return transferPacketWithType(_packet_type_t::MSGHEX, temp, timeout);
}

bool LoRaWanClass::transferPacketWithConfirmed(const char *buffer, unsigned char timeout)
{
    return transferPacketWithType(_packet_type_t::CMSG,buffer, timeout);
}

bool LoRaWanClass::transferPacketWithConfirmed(const unsigned char *buffer, unsigned char length,unsigned char timeout)
{
    char temp[length * 2 + 1];
    for(unsigned char i = 0; i < length; i ++)
    {
        sprintf(&temp[i*2],"%02x", buffer[i]);
    }

    return transferPacketWithType(_packet_type_t::CMSGHEX, temp, timeout);
}


short LoRaWanClass::receivePacket(char *buffer, short length, short *rssi)
{
    char *ptr;
    short number = 0;

    ptr = strstr(_buffer, "RSSI ");
    if(ptr) *rssi = (short) strtol(ptr + 5, nullptr, 10);
    else *rssi = -255;

    ptr = strstr(_buffer, "RX: \"");
    if(ptr)
    {        
        ptr += 5;

        uint8_t bitStep;
        if(*(ptr + 2) == ' ')bitStep = 3; // Firmware version 2.0.10
        else bitStep = 2;                   // Firmware version 2.1.15

        for(short i = 0; ; i ++)
        {
            char temp[2] = {0};
            unsigned char tmp = 0;
            unsigned char result = 0;

            temp[0] = *(ptr + i * bitStep);
            temp[1] = *(ptr + i * bitStep + 1);

            for(unsigned char j : temp)
            {
                if((temp[j] >= '0') && (temp[j] <= '9'))
                    tmp = temp[j] - '0';
                else if((temp[j] >= 'A') && (temp[j] <= 'F'))
                    tmp = temp[j] - 'A' + 10;
                else if((temp[j] >= 'a') && (temp[j] <= 'f'))
                    tmp = temp[j] - 'a' + 10;

                result = result * 16 + tmp;
            }

            if(i < length) buffer[i] = result;

            if(*(ptr + (i + 1) * bitStep) == '\"' && *(ptr + (i + 1) * bitStep + 1) == '\r' && *(ptr + (i + 1) * bitStep + 2) == '\n')
            {
                number = ++i;
                break;
            }
        }        
    }

    memset(_buffer, 0, BUFFER_LENGTH_MAX);

    return number;
}

bool LoRaWanClass::transferProprietaryPacket(char *buffer, unsigned char timeout)
{
    return transferPacketWithType(_packet_type_t::PMSG,buffer);
}

bool LoRaWanClass::transferProprietaryPacket(unsigned char *buffer, unsigned char length, unsigned char timeout)
{
    char temp[length * 2 + 1];
    for(unsigned char i = 0; i < length; i ++)
    {
        sprintf(&temp[i*2],"%02x", buffer[i]);
    }

    return transferPacketWithType(_packet_type_t::PMSG,temp);
}

        
void LoRaWanClass::setUnconfirmedMessageRepeatTime(unsigned char time)
{
    char cmd[32];
    
    if(time > 15) time = 15;
    else if(time == 0) time = 1;
    
    memset(cmd, 0, 32);
    sprintf(cmd, "AT+REPT=%d\r\n", time);
    sendCommand(cmd);
#if _DEBUG_SERIAL_
    loraDebugPrint(DEFAULT_DEBUGTIME);
#endif
    delay(DEFAULT_TIMEWAIT);
}

void LoRaWanClass::setConfirmedMessageRetryTime(unsigned char time)
{
    char cmd[32];
    
    if(time > 15) time = 15;
    else if(time == 0) time = 1;
    
    memset(cmd, 0, 32);
    sprintf(cmd, "AT+RETRY=%d\r\n", time);
    sendCommand(cmd);
#if _DEBUG_SERIAL_
    loraDebugPrint(DEFAULT_DEBUGTIME);
#endif
    delay(DEFAULT_TIMEWAIT);    
}

void LoRaWanClass::setReceiceWindowFirst(bool command)
{
    if(command) sendCommand("AT+RXWIN1=ON\r\n");
    else sendCommand("AT+RXWIN1=OFF\r\n");
#if _DEBUG_SERIAL_
    loraDebugPrint(DEFAULT_DEBUGTIME);
#endif
    delay(DEFAULT_TIMEWAIT);
}

void LoRaWanClass::setReceiceWindowFirst(unsigned char channel, float frequency)
{
    char cmd[32];
    
    memset(cmd, 0, 32);
    sprintf(cmd, "AT+RXWIN1=%d,%d.%d\r\n", channel, (short)frequency, short(frequency * 10) % 10);
    sendCommand(cmd);
#if _DEBUG_SERIAL_
    loraDebugPrint(DEFAULT_DEBUGTIME);
#endif
    delay(DEFAULT_TIMEWAIT);
}

void LoRaWanClass::setReceiceWindowSecond(float frequency, _data_rate_t dataRate)
{
    char cmd[32];
    
    memset(cmd, 0, 32);
    sprintf(cmd, "AT+RXWIN2=%d.%d,%d\r\n", (short)frequency, short(frequency * 10) % 10, dataRate);
    sendCommand(cmd);
#if _DEBUG_SERIAL_
    loraDebugPrint(DEFAULT_DEBUGTIME);
#endif
    delay(DEFAULT_TIMEWAIT);
}

void LoRaWanClass::setReceiceWindowSecond(float frequency, _spreading_factor_t spreadingFactor, _band_width_t bandwidth)
{
    char cmd[32];
    
    memset(cmd, 0, 32);
    sprintf(cmd, "AT+RXWIN2=%d.%d,%d,%d\r\n", (short)frequency, short(frequency * 10) % 10, spreadingFactor, bandwidth);
    sendCommand(cmd);
#if _DEBUG_SERIAL_
    loraDebugPrint(DEFAULT_DEBUGTIME);
#endif
    delay(DEFAULT_TIMEWAIT);
}

void LoRaWanClass::setDutyCycle(bool command)
{
    if(command) sendCommand("AT+LW=DC, ON\r\n");
    else sendCommand("AT+LW=DC, OFF\r\n");  
#if _DEBUG_SERIAL_
    loraDebugPrint(DEFAULT_DEBUGTIME);
#endif
    delay(DEFAULT_TIMEWAIT);
}

void LoRaWanClass::setJoinDutyCycle(bool command)
{
    if(command) sendCommand("AT+LW=JDC,ON\r\n");
    else sendCommand("AT+LW=JDC,OFF\r\n");  
#if _DEBUG_SERIAL_
    loraDebugPrint(DEFAULT_DEBUGTIME);
#endif
    delay(DEFAULT_TIMEWAIT);
}

void LoRaWanClass::setReceiceWindowDelay(_window_delay_t command, unsigned short _delay)
{
    char cmd[32];
    
    memset(cmd, 0, 32);
    if(command == RECEIVE_DELAY1) sprintf(cmd, "AT+DELAY=RX1,%d\r\n", _delay);
    else if(command == RECEIVE_DELAY2) sprintf(cmd, "AT+DELAY=RX2,%d\r\n", _delay);
    else if(command == JOIN_ACCEPT_DELAY1) sprintf(cmd, "AT+DELAY=JRX1,%d\r\n", _delay);
    else if(command == JOIN_ACCEPT_DELAY2) sprintf(cmd, "AT+DELAY=JRX2,%d\r\n", _delay); 
    sendCommand(cmd);
#if _DEBUG_SERIAL_
    loraDebugPrint(DEFAULT_DEBUGTIME);
#endif
    delay(DEFAULT_TIMEWAIT);
}

void LoRaWanClass::setClassType(_class_type_t type)
{
    if(type == CLASS_A) sendCommand("AT+CLASS=A\r\n");
    else if(type == CLASS_C) sendCommand("AT+CLASS=C\r\n");
#if _DEBUG_SERIAL_
    loraDebugPrint(DEFAULT_DEBUGTIME);
#endif
    delay(DEFAULT_TIMEWAIT);
}

void LoRaWanClass::setDeciveMode(_device_mode_t mode)
{
    if(mode == LWABP) sendCommand("AT+MODE=LWABP\r\n");
    else if(mode == LWOTAA) sendCommand("AT+MODE=LWOTAA\r\n");
#if _DEBUG_SERIAL_
    loraDebugPrint(DEFAULT_DEBUGTIME);
#endif
    delay(DEFAULT_TIMEWAIT);
}

bool LoRaWanClass::setOTAAJoin(_otaa_join_cmd_t command, unsigned char timeout)
{
    char *ptr;
    static bool waitingForJoin = false;
    if (!waitingForJoin)
    {
        if(command == JOIN) sendCommand("AT+JOIN\r\n");
        else if(command == FORCE) sendCommand("AT+JOIN=FORCE\r\n");
    }

    delay(DEFAULT_TIMEWAIT);

    memset(_buffer, 0, BUFFER_LENGTH_MAX);
    auto bufferI = readBuffer(_buffer, BUFFER_LENGTH_MAX, timeout);
#if _DEBUG_SERIAL_    
    SerialUSB.print("read buffer i is: ");
    SerialUSB.println(bufferI);
    SerialUSB.print(_buffer);
#endif  

    ptr = strstr(_buffer, "+JOIN: Network joined");
    if(ptr)
    {
        waitingForJoin = false;
        return true;
    }

    ptr = strstr(_buffer, "+JOIN: Join failed");
    if(ptr)return false;

    ptr = strstr(_buffer, "+JOIN: LoRaWAN modem is busy");
    if(ptr)
    {
        waitingForJoin = true;
        return false;
    }

    return false;
}

void LoRaWanClass::setDeviceLowPower(void)
{
    sendCommand("AT+LOWPOWER\r\n");
#if _DEBUG_SERIAL_
    loraDebugPrint(DEFAULT_DEBUGTIME);
#endif
    delay(DEFAULT_TIMEWAIT);

    inLowPowerMode = true;
}

void LoRaWanClass::wakeUp(void)
{
    if(inLowPowerMode)
    {
        char temp[3] = {0xff,0xff,0xff};
        SerialLoRa.write(temp, 3);
        delay(DEFAULT_TIMEWAIT);
        inLowPowerMode = false;
    }
}

void LoRaWanClass::setDeviceReset(void)
{
    sendCommand("AT+RESET\r\n");
#if _DEBUG_SERIAL_
    loraDebugPrint(DEFAULT_DEBUGTIME);
#endif
    delay(DEFAULT_TIMEWAIT);
}

void LoRaWanClass::setDeviceDefault()
{
    sendCommand("AT+FDEFAULT=RISINGHF\r\n");
#if _DEBUG_SERIAL_
    loraDebugPrint(DEFAULT_DEBUGTIME);
#endif
    delay(DEFAULT_TIMEWAIT);
}

void LoRaWanClass::initP2PMode()
{
    sendCommand("AT+MODE=TEST\r\n");
#if _DEBUG_SERIAL_
    loraDebugPrint(DEFAULT_DEBUGTIME);
#endif
    delay(DEFAULT_TIMEWAIT);
    sendCommand("AT+TEST=?\r\n");
#if _DEBUG_SERIAL_
    loraDebugPrint(DEFAULT_DEBUGTIME);
#endif
    delay(DEFAULT_TIMEWAIT);
    sendCommand("AT+TEST=RFCFG\r\n");
#if _DEBUG_SERIAL_
    loraDebugPrint(DEFAULT_DEBUGTIME);
#endif
    delay(DEFAULT_TIMEWAIT);
    sendCommand("AT+TEST=RXLRPKT\r\n");
#if _DEBUG_SERIAL_
    loraDebugPrint(DEFAULT_DEBUGTIME);
#endif
    delay(DEFAULT_TIMEWAIT);
}

void LoRaWanClass::initP2PMode(unsigned short frequency, _spreading_factor_t spreadingFactor, _band_width_t bandwidth, 
        unsigned char txPreamble, unsigned char rxPreamble, short power)
{
    char cmd[64] = {0,};
    sprintf(cmd, "AT+TEST=RFCFG,%d,%d,%d,%d,%d,%d\r\n", frequency, spreadingFactor, bandwidth, txPreamble, rxPreamble, power);

    sendCommand("AT+MODE=TEST\r\n");
    delay(DEFAULT_TIMEWAIT);
    sendCommand("AT+TEST=?\r\n");
    delay(DEFAULT_TIMEWAIT);
    sendCommand(cmd);
    delay(DEFAULT_TIMEWAIT);
    sendCommand("AT+TEST=RXLRPKT\r\n");

#if _DEBUG_SERIAL_
    loraDebugPrint(DEFAULT_DEBUGTIME);
#endif
    delay(DEFAULT_TIMEWAIT);
}

bool LoRaWanClass::transferPacketP2PMode(const char *buffer, unsigned char timeout)
{
    return transferPacketWithType(_packet_type_t::TXLRSTR, buffer);
    
//  unsigned char length = strlen(buffer);
//  sendCommand("AT+TEST=TXLRSTR,\"");
//  for(unsigned char i = 0; i < length; i ++)sendChar(buffer[i]);
//  sendCommand("\"\r\n");
    
    // memset(_buffer, 0, BEFFER_LENGTH_MAX);
    // readBuffer(_buffer, BEFFER_LENGTH_MAX, timeout);

    // if(strstr(_buffer, "+TEST: TX DONE"))return true;
    // return false;
}

bool LoRaWanClass::transferPacketP2PMode(const unsigned char *buffer, unsigned char length, unsigned char timeout)
{
//  char temp[3] = {0};
//
//  sendCommand("AT+TEST=TXLRPKT,\"");
//  for(unsigned char i = 0; i < length; i ++)
//    {
//      sprintf(temp,"%02x", buffer[i]);
//      sendCommand(temp);
//    }
//  sendCommand("\"\r\n");

    // memset(_buffer, 0, BEFFER_LENGTH_MAX);
    // readBuffer(_buffer, BEFFER_LENGTH_MAX, timeout);

    // if(strstr(_buffer, "+TEST: TX DONE"))return true;
    // return false;
    char temp[length * 2 + 1];
    for(unsigned char i = 0; i < length; i ++)
    {
        sprintf(&temp[i*2],"%02x", buffer[i]);
    }

    return transferPacketWithType(_packet_type_t::TXLRPKT, temp);
}

short LoRaWanClass::receivePacketP2PMode(unsigned char *buffer, short length, short *rssi, unsigned char timeout)
{
    char *ptr;
    short number;

    sendCommandAndWaitForResponse("AT+TEST=RXLRPKT\r\n", "+TEST: RXLRPKT", 2);

    while(SerialLoRa.available()) SerialLoRa.read();
    memset(_buffer, 0, BUFFER_LENGTH_MAX);
    readBuffer(_buffer, BUFFER_LENGTH_MAX, timeout);

    ptr = strstr(_buffer, "LEN");
    if(ptr) number = static_cast<short>(strtol(ptr + 4, nullptr, 10));
    else number = 0;

    if(number <= 0)return 0;

    ptr = strstr(_buffer, "RSSI:");
    if(ptr)
    {
        *rssi = static_cast<short>(strtol(ptr + 5, nullptr, 10));
    }
    else
        *rssi = -255;

    ptr = strstr(_buffer, "RX \"");
    if(ptr)
    {
        ptr += 4;

        uint8_t bitStep = 0;
        if(*(ptr + 2) == ' ')bitStep = 3; // Firmware version 2.0.10
        else bitStep = 2;                   // Firmware version 2.1.15

        for(short i = 0; i < number; i ++)
        {
            char temp[2] = {0};
            unsigned char tmp, result = 0;

            temp[0] = *(ptr + i * bitStep);
            temp[1] = *(ptr + i * bitStep + 1);

            for(char j : temp)
            {
                if((j >= '0') && (j <= '9'))
                    tmp = j - '0';
                else if((j >= 'A') && (j <= 'F'))
                    tmp = j - 'A' + 10;
                else if((j >= 'a') && (j <= 'f'))
                    tmp = j - 'a' + 10;

                result = result * 16 + tmp;
            }

            if(i < length)buffer[i] = result;
        }
    }

    memset(_buffer, 0, BUFFER_LENGTH_MAX);

    return number;
}

short LoRaWanClass::getBatteryVoltage()
{
    uint32_t battery;

    pinMode(CHARGE_STATUS_PIN, OUTPUT);
    digitalWrite(CHARGE_STATUS_PIN, LOW);
    delay(DEFAULT_TIMEWAIT);
    battery = (analogRead(BATTERY_POWER_PIN) * 3300 * 11) >> 10;
    pinMode(CHARGE_STATUS_PIN, INPUT);

    return (short)(battery);
}

void LoRaWanClass::loraDebug(void)
{
    if(SerialUSB.available()) SerialLoRa.write(SerialUSB.read());
    if(SerialLoRa.available()) SerialUSB.write(SerialLoRa.read());
}

#if _DEBUG_SERIAL_
void LoRaWanClass::loraDebugPrint(unsigned char timeout)
{
    unsigned long timerStart, timerEnd;

    timerStart = millis();

    while(true)
    {
        while(SerialLoRa.available()) SerialUSB.write(SerialLoRa.read());

        timerEnd = millis();
        if(timerEnd - timerStart > 1000 * timeout) break;
    }
}
#endif



void LoRaWanClass::sendCommand(const char *command)
{
    if(inLowPowerMode) wakeUp();
    // wait for SerialLoRa to be available for writing
    while(!SerialLoRa.availableForWrite());
    SerialLoRa.write(command);
}

void LoRaWanClass::sendChar(const char command)
{
    SerialLoRa.write(command);
}

short LoRaWanClass::readBuffer(char *buffer, short length, unsigned char timeout)
{
    short i = 0;
    unsigned long timerStart, timerEnd;

    timerStart = millis();

    while(true)
    {
        if(i < length)
        {
            while(SerialLoRa.available())
            {
                char c = SerialLoRa.read();  
                buffer[i ++] = c;
            }  
        }

        timerEnd = millis();
        if((timerEnd - timerStart) > (1000 * timeout))break;
    }

    return i;
}

bool LoRaWanClass::waitForResponse(const char *response, unsigned char timeout)
{
    auto len = (short)(strlen(response));
    short sum = 0;
    unsigned long timerStart, timerEnd;

    timerStart = millis();

    while(true)
    {
        if(SerialLoRa.available())
        {
            char c = SerialLoRa.read();

            c == response[sum] ? sum++ : sum = 0;
            if(sum == len)break;
        }

        timerEnd = millis();
        if(timerEnd - timerStart > 1000 * timeout) return false;
    }

    return true;
}

bool LoRaWanClass::sendCommandAndWaitForResponse(const char *command, const char *response, unsigned char timeout)
{
    sendCommand(command);
    
    return waitForResponse(response, timeout);
}

LoRaWanClass lora;
char LoRaWanClass::_buffer[BUFFER_LENGTH_MAX] = {0};
bool LoRaWanClass::inLowPowerMode = false;
