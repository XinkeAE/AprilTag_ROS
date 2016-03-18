/*

Copyright (c) 2012, Ascending Technologies GmbH
All rights reserved.

Redistribution and use in source and binary forms, with or without
modification, are permitted provided that the following conditions are met:

 * Redistributions of source code must retain the above copyright notice,
   this list of conditions and the following disclaimer.
 * Redistributions in binary form must reproduce the above copyright
   notice, this list of conditions and the following disclaimer in the
   documentation and/or other materials provided with the distribution.

THIS SOFTWARE IS PROVIDED BY THE AUTHOR AND CONTRIBUTORS ``AS IS'' AND ANY
EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED
WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE
DISCLAIMED. IN NO EVENT SHALL THE AUTHOR OR CONTRIBUTORS BE LIABLE FOR ANY
DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES
(INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR
SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER
CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT
LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY
OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH
DAMAGE.

 */

#ifndef ASCTECCOMMINTF_H_
#define ASCTECCOMMINTF_H_

#ifdef __cplusplus
extern "C"
 {
 #endif

#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include "asctecDefines.h"



/** Has to be called ones during initialisation
 * 	It setup all necessary varibales and struct.
 * **/
extern void aciInit(void);

/**
 * If you are not sure, if the version and configurations of the device is the same like the version of this SDK, you can check this with this function <br>
 *
 */
extern void aciCheckVerConf(void);


/** The aciReceiveHandler is fed by the uart rx function and decodes all necessary packets
*   @param receivedByte received Byte from uart.
*   @see aciSetSendDataCallback
**/
extern void aciReceiveHandler(unsigned char receivedByte);

/**
 *  Has to be called a specified number of times per second. You have to set the rate for the Engine and the heartbeat in aciSetEngineRate().<br>
 *  It handles the transmission to the device and send also a signal, that inform the device, that the remote is still alive and able to send data. If too much data would come from the device and would use the whole bandwidth, it may happen, that the remote cannot send any data. With the signal of a heartbeat, the host is informed, that it could get data from the remote.<br>
 *  After no getting any heartbeat from the remote for a while, the host stops to send data and will send again, if it receive a heartbeat.
 **/
extern void aciEngine(void);


/** Set's the number of time aciEngine is called per second and the heartbeat rate. It's important to make sure that the number of calls and this setting are fitting
 * The heartbeat rate is calculated by callsPerSecond/heartbeat. Make sure, that the hearbeat will send more than one time in 3 seconds (default value of stop sending of the host).
 * **/
extern void aciSetEngineRate(const unsigned short callsPerSecond, const unsigned short heartbeat);

/** resets remote interface to a zero variable packet configuration **/
extern void aciResetRemote(void);

/** Polls the device variable list. The variable list update finished function aciVarListUpdateFinished() is called on completion.<br>
 * Depends on your update rate and the number of available variables, this could take some time. Be sure, that you don't read the variable list before the variable list update finished function was executed<br>
 * You have to request the variable list one time only.
 *
 **/
extern void aciGetDeviceVariablesList(void);

/** Polls the device command list. The command list update finished function aciCmdListUpdateFinished() is called on completion.<br>
 * Depends on your update rate and the number of available commands, this could take some time. Be sure, that you don't read the command list before the command list update finished function was executed<br>
 * You have to request the command list one time only.
 **/
extern void aciGetDeviceCommandsList(void);

/** Polls the device parameter list. The parameter list update finished function aciParListUpdateFinished() is called on completion.<br>
 * Depends on your update rate and the number of available parameter, this could take some time. Be sure, that you don't read the parameter list before the parameter list update finished function was executed<br>
 * You have to request the parameter list one time only.
 **/
extern void aciGetDeviceParametersList(void);

/**
 * Send a signal to the device, that it shall save all parameters on the EEPROM.
 */
extern void aciSendParamStore();

/**
 * Send a signal to the device, that it shall load all parameters from the EEPROM.
 */
extern void aciSendParamLoad();

/**
 * Request the value of a parameter from the device. The content will be written in the assign variable for that parameter.
 * @param id The id of the parameter
 * @return none
 */
extern void aciGetParamFromDevice(unsigned short id);

/**
 * Return the information, if a parameter packet was updated
 * @param packetid The id of the packet
 * @return Return 1, if the packet with its parameters are already received, otherwise 0
 */
extern unsigned char aciGetParamPacketStatus(unsigned short packetid);
/** Get the ACI info packet.
 * @return If no packet was received, all variables in the ACI_INFO struct are 0, else it returns the values.
 * **/
extern struct ACI_INFO aciGetInfo(void);


/** Return the number of variables, you get after calling @See aciGetDeviceVariablesList(). <br>
 * @return It returns 0, if no variables are available (i.e. if @See aciGetDeviceVariablesList() were not called)
 * **/

extern unsigned short aciGetVarTableLength(void);

/** Find a variable by name <br>
 * Normally, you request a variable of the device by declaring a pointer on your own created variable. In this case, you can use @See aciSynchronizeVars() to copy the received buffer into your variable. <br>
 * Otherwise you can also access to the variable and all the information about it by using this function.
 * @param name The name of the variable you are looking for.
 * @return It returns a pointer on a struct, which contains all information about the variable. If the name of the variable doesn't exist, it returns NULL.
 **/
extern struct ACI_MEM_TABLE_ENTRY *aciGetVariableItemByName(char * name);

/** Find a variable by id <br>
 * Normally, you request a variable of the device by declaring a pointer on your own created variable. In this case, you can use @See aciSynchronizeVars() to copy the received buffer into your variable. <br>
 * Otherwise you can also access to the variable and all the information about it by using this function.
 * @param id The id of the variable you are looking for.
 * @return It returns a pointer on a struct (#ACI_MEM_TABLE_ENTRY), which contains all information about the variable. If the id of the variable doesn't exist, it returns NULL.
 **/
extern struct ACI_MEM_TABLE_ENTRY *aciGetVariableItemById(unsigned short id);

/** Find a command by id <br>
 * Normally, you create a command of the device by declaring a pointer on your own created variable. After setting your variable by the command, you want to send, you call aciUpdateCmdPacket() with its packet id to send it.<br>
 * Otherwise you can also access to the command and all the information about it by using this function.
 * @param id The id of the command you are looking for.
 * @return It returns a pointer on a struct, which contains all information about the command. If the id of the command doesn't exist, it returns NULL.
 **/
extern struct ACI_MEM_TABLE_ENTRY *aciGetCommandItemById(unsigned short id);

/** Get a command by index. The index of the command is defined, when the command was received after calling aciGetDeviceCommandsList().
 * @param index The index of the command in the list
 * @return It returns a pointer on a struct, which contains all information about the variable. If the id of the variable doesn't exist, it returns NULL.
 * **/
extern struct ACI_MEM_TABLE_ENTRY *aciGetCommandItemByIndex(unsigned short index);

/** Get a command by name. The name of the command is defined, when the command was received after calling aciGetDeviceCommandsList().
 * @param name The name of the command in the list
 * @return It returns a pointer on a struct, which contains all information about the variable. If the name of the variable doesn't exist, it returns NULL.
 * **/
extern struct ACI_MEM_TABLE_ENTRY *aciGetCommandItemByName(char * name);

/** Get a parameter by name. The name of the parameter is defined, when the parameter was received after calling aciGetDeviceParametersList().
 * @param name The name of the parameter in the list
 * @return It returns a pointer on a struct, which contains all information about the parameter. If the name of the parameter doesn't exist, it returns NULL.
 * **/
extern struct ACI_MEM_TABLE_ENTRY *aciGetParameterItemByName(char * name);

/** Find a parameter by id <br>
 * Normally, you create a parameter of the device by declaring a pointer on your own created variable. After setting your variable by the parameter, you can synchronize it with the device.<br>
 * Otherwise you can also access to the parameter and all the information about it by using this function.
 * @param id The id of the parameter you are looking for.
 * @return It returns a pointer on a struct, which contains all information about the parameter. If the id of the parameter doesn't exist, it returns NULL.
 **/
extern struct ACI_MEM_TABLE_ENTRY *aciGetParameterItemById(unsigned short id);

/** Get a variable by index. The index of the variable is defined, when the parameter was received after calling aciGetDeviceVariablesList().
 * @param index The index of the variable in the list
 * @return It returns a pointer on a struct, which contains all information about the variable. If the id of the variable doesn't exist, it returns NULL.
 * **/
extern struct ACI_MEM_TABLE_ENTRY *aciGetVariableItemByIndex(unsigned short index);

/** Get a parameter by index. The index of the parameter is defined, when the parameter was received after calling aciGetDeviceParametersList().
 * @param index The index of the parameter in the list
 * @return It returns a pointer on a struct, which contains all information about the parameter. If the id of the parameter doesn't exist, it returns NULL.
 * **/
extern struct ACI_MEM_TABLE_ENTRY *aciGetParameterItemByIndex(unsigned short index);

/** Reset variable packet content. Call @See aciSendVariablePacketConfiguration for changes to get effective
 * @param packetId The id of the packet you want to reset.
 * @return none
 * **/
extern void aciResetVarPacketContent(unsigned char packetId);

/** Reset command packet content. Call @See aciSendCommandPacketConfiguration for changes to get effective
 * @param packetId The id of the packet you want to reset.
 * @return none
 **/

extern void aciResetCmdPacketContent(unsigned char packetId);

/** Reset parameter packet content. Call @See aciSendParameterPacketConfiguration for changes to get effective
 * @param packetId The id of the packet you want to reset.
 * @return none
 **/
extern void aciResetParPacketContent(unsigned char packetId);

/** Get the length of a variable package
 * @param packetId The id of the package
 * @return The length of the package
 * **/
extern unsigned short aciGetVarPacketLength(unsigned char packetId);

/** Get the length of a command package
 * @param packetId The id of the package
 * @return The length of the package
 * **/
extern unsigned short aciGetCmdPacketLength(unsigned char packetId);

/** Get the length of a parameter package
 * @param packetId The id of the package
 * @return The length of the package
 * **/
extern unsigned short aciGetParPacketLength(unsigned char packetId);

/**Get a variable packet item by index.
 * @param packetId The id of the packet
 * @param index The index of the variable in the packet
 * @return Return the id of the item if exist, otherwise 0
 *  **/
extern unsigned short aciGetVarPacketItem(unsigned char packetId, unsigned short index);

/**Get a command packet item by index.
 * @param packetId The id of the packet
 * @param index The index of the coammand in the packet
 * @return Return the id of the item if exist, otherwise 0
 *  **/
extern unsigned short aciGetCmdPacketItem(unsigned char packetId, unsigned short index);

/**Get a parameter packet item by index.
 * @param packetId The id of the packet
 * @param index The index of the parameter in the packet
 * @return Return the id of the item if exist, otherwise 0
 *  **/
extern unsigned short aciGetParPacketItem(unsigned char packetId, unsigned short index);

/** Get the rate of a variable package. (Useful for aciGetVarPacketRateFromRemote() to check, which transmission rate is set on the device )
 * @param packetId The id of the package
 * @return the transmission rate of the packet
 * **/
unsigned short aciGetVarPacketRate(unsigned char packetId);

/** Request the transmission rate of every variable package on the device. After receiving the data, you get it over aciGetVarPacketRate().**/
void aciGetVarPacketRateFromDevice();

/** Adds content to packet. <br>
 * Call aciSendVariablePacketConfiguration() for changes to get effective
 * @param packetId Define the id of the packet, where the variable should be send. The first id is 0 and the numbers of packets is defined in #MAX_VAR_PACKETS (by default: 3)
 * @param id The id of the variable, which should be included in the packet
 * @param var_ptr a pointer to the variable, where the content shall be written after calling @See aciSynchronizeVars()
 * @return none
 **/
extern void aciAddContentToVarPacket(unsigned char packetId, unsigned short id, void *var_ptr);

/**
 * Send variables packet configuration to the device which shall be send to the remote.
 * @param packetId The id of the packet, which shall be received from the device.
 * @return none
 **/
extern void aciSendVariablePacketConfiguration(unsigned char packetId);

/**
 * Send command packet configuration to the device which shall be send to the device.
 * @param packetId The id of the packet, which includes the list of commands for sending.
 * @param with_ack If you set this not zero, it will send the last command until it gets an acknowledge.
 * @return none
 **/
extern void aciSendCommandPacketConfiguration(unsigned char packetId, unsigned char with_ack);

/**
 * Send parameter packet configuration to the device which shall be send/set to/on the device.
 * @param packetId The id of the packet, which includes the list of parameter for sending.
 * @return none
 **/
extern void aciSendParameterPacketConfiguration(unsigned char packetId);

/** Change transmission rate of the individual packages. Call aciVarPacketUpdateTransmissionRates() for changes to get effective.
 *  @param packetId The id of the packet you want to set the transmission rate
 *  @param rate The rate depends on the engine rate of the device (default 1000 calls per Second) and is calculated through (Engine rate of the device)/rate.
 *  @return none
 *
 * **/
extern void aciSetVarPacketTransmissionRate(unsigned char packetId, unsigned short rate);

/** updates the transmission data rates for all variable packets at once. Change the individual rates with aciSetVarPacketTransmissionRate() **/
extern void aciVarPacketUpdateTransmissionRates();

/* assign local variable to ID. By calling aciSynchronizeVars() the most recent content get's copied to all assigned variables **/
//extern unsigned char aciAssignVariableToId(void * ptrToVar, unsigned char varType, unsigned short id);

/** By calling aciSynchronizeVars() the content of all requested variables in every package will be updated from the content in the receiving buffer. */
extern void aciSynchronizeVars(void);


/** Adds content to command packet. <br>
 * @param packetId Define the id of the packet, where the command should be received by the device. The first id is 0 and the numbers of packets is defined in #MAX_VAR_PACKETS (by default: 3).
 * @param id The id of the command, which should be included in the packet.
 * @param ptr a pointer to the command, where the content to send is in.
 * @return none
 **/
extern void aciAddContentToCmdPacket(const unsigned char packetId, const unsigned short id, void *ptr);

/**
 * Send the content of the commands to the device
 * @param packetId The id of the packet
 * @return none
 */

extern void aciUpdateCmdPacket(const unsigned short packetId);
/**
 * Return the send status of a command package.
 * @param packetId The id of the packet
 * @return 0 for no command to send or command sended, 1 for a pending command to send, 2 for waiting acknowledge (if acknowledge for the package is set on).
 */

extern unsigned char aciGetCmdSendStatus(const unsigned short packetId);


/** Adds content to parameter packet. <br>
 * @param packetId Define the id of the packet, where the parameter shall be in. The first id is 0 and the numbers of packets is defined in #MAX_VAR_PACKETS (by default: 3)
 * @param id The id of the parameter, which should be included in the packet
 * @param ptr a pointer to the variable, where the content shall be written for sending and receiving.
 * @return none
 **/
extern void aciAddContentToParamPacket(unsigned char packetId, unsigned short id, void *ptr);

/**
 * Send the content of the parameters to the device
 * @param packetId The id of the packet
 * @return none
 */
extern void aciUpdateParamPacket(const unsigned short packetId);

/**
 * \ingroup callbacks
 * Set send data callback.<br>
 * The callback is called when the ACI want's to send a data packet. That happens i.e. in the @See aciEngine() function, where everytime a heartbeat will send to the host.
 **/
extern void aciSetSendDataCallback(void (*aciSendDataCallback_func)(void * data, unsigned short cnt));

/**
 * \ingroup callbacks
 * Set variable list update finished callback. <br>
 * The callback is called after the variable list was successfully received.
 **/
extern void aciSetVarListUpdateFinishedCallback(void (*aciVarListUpdateFinished_func)(void));

/**
 * \ingroup callbacks
 * Set command list update finished callback.<br>
 * The callback is called after the command list was successfully received.
 **/
extern void aciSetCmdListUpdateFinishedCallback(void (*aciCmdListUpdateFinished_func)(void));

/**
 * \ingroup callbacks
 * Set parameter list update finished callback.<br>
 * The callback is called after the parameters list was successfully received.
 **/
extern void aciSetParamListUpdateFinishedCallback(void (*aciParamListUpdateFinished_func)(void));

/**
 * \ingroup callbacks
 * Set parameter list update finished callback.<br>
 * The callback is called after the parameters list was successfully received.
 **/
extern void aciSetCmdAckCallback(void (*aciCmdAck_func)(unsigned char));

/**
 * \ingroup callbacks
 * Set version information received callback. <br>
 * The callback is called if you request the ACI info package and  It was received. It includes the version information of the device.  <br>
 **/
extern void aciInfoPacketReceivedCallback(void (*aciInfoRec_func)(struct ACI_INFO));

/**
 * \ingroup callbacks
 * Set version information received callback. <br>
 * The callback is called after a variable packet was received. The parameter is the packet number of the packet.
 **/
extern void aciVarPacketReceivedCallback(void (*aciVarPacketRec_func)(unsigned char));

/**
 * \ingroup callbacks
 * Set parameter saved callback. <br>
 * The callback is called after storing the parameters on the device.
 **/
extern void aciParPacketStoredCallback(void (*aciParPacketStored_func)(void));
/**
 * \ingroup callbacks
 * Set parameter saved callback. <br>
 * The callback is called after loading the parameters from the device.
 **/
extern void aciParPacketLoadedCallback(void (*aciParPacketLoaded_func)(void));

/**
 * \ingroup callbacks
 * Set the callback, that will be executed after receiving a single variable from the device. A single variable is a variable, that will be send instantly from the device to the remote. It is useful, if you want to commit a status update. The sending id depends on none of the ids in any list and is individual set by the user.
 * The AscTec SDK 3.0 doesn't include any single variable to send.
 *
 **/
extern void aciSetSingleReceivedCallback(void (*aciSingleReceived)(unsigned short id, void * data, unsigned char varType));

/**
 * \ingroup callbacks
 * Set the callback for a requested variable. <br>
 * After calling aciRequestSingleVariable, this function will be executed, when the requested variable was received.
 *
 **/
extern void aciSetSingleRequestReceivedCallback(void (*aciSingleReqReceived)(unsigned short id, void * data, unsigned char varType));

/**
 * \ingroup callbacks
 * Set the reading stored data callback. <br>
 * If you set this callback, ACI will try to read the lists from any storage device, you defined in the callback function.
 *
 **/
extern void aciSetReadHDCallback(int (*aciReadHD)(void *data, int bytes));

/**
 * \ingroup callbacks
 * Set the writing stored data callback. <br>
 * If you set this callback, ACI will store the lists on any storage device, you defined in the callback function.
 *
 **/
extern void aciSetWriteHDCallback(int (*aciWriteHD)(void *data, int bytes));

/**
 * \ingroup callbacks
 * Set the reset stored data callback. <br>
 * You maybe need this callback, if you set the reading and writing callback on the same device. It will be called, when it starts to write the data on the device.
 *
 **/
extern void aciSetResetHDCallback(void (*aciResetHD)());
/**
 * If you want to know the current value of a variable without putting it in a packet, you can use to function. It is useful for getting any status of a variable for one time. If you want all the time the current value, it is recommended to put the variable in a packet. After receiving the variable, the callback defined with aciSetSingleRequestReceivedCallback() will be executed.
 * @param id The id of the variable, you want to request
 * @return none
 *
 **/
void aciRequestSingleVariable(unsigned short id);

/**
 * If you call this function, the stored list of all variables, commands and parameters will be not loaded. You can also use it to request a list again.
 * Anyway, this function is useful, if you changed the descriptions of the variables, command or parameters. Otherwise, the lists will be updated by itself.
 *
 **/
void aciForceListRequestFromDevice();
                 

struct __attribute__((packed)) ACI_MEM_TABLE_ENTRY
{
	unsigned short id;
	char name[MAX_NAME_LENGTH];
	char description[MAX_DESC_LENGTH];
	char unit[MAX_UNIT_LENGTH];
	unsigned char varType;
	void * ptrToVar;
};

struct __attribute__((packed)) ACI_MEM_VAR_TABLE
{
	struct ACI_MEM_TABLE_ENTRY tableEntry;
	struct ACI_MEM_VAR_TABLE * next;
};


///this package is fixed and should never be changed!
struct __attribute__((packed)) ACI_INFO
{
	unsigned char verMajor;
	unsigned char verMinor;
	unsigned char maxNameLength;
	unsigned char maxDescLength;
	unsigned char maxUnitLength;
	unsigned char maxVarPackets;
	unsigned char memPacketMaxVars;
	unsigned short flags;
	unsigned short dummy[8];
};

struct __attribute__((packed)) ACI_MEM_VAR_ASSIGN_TABLE
{
	void * ptrToVar;
	unsigned char varType;
	unsigned short id;
	struct ACI_MEM_VAR_ASSIGN_TABLE * next;
};

extern struct ACI_MEM_VAR_TABLE * aciMemVarTableStart;
extern struct ACI_MEM_VAR_TABLE * aciMemVarTableCurrent;

extern struct ACI_MEM_VAR_TABLE * aciMemCmdTableStart;
extern struct ACI_MEM_VAR_TABLE * aciMemCmdTableCurrent;

extern struct ACI_MEM_VAR_TABLE * aciMemParamTableStart;
extern struct ACI_MEM_VAR_TABLE * aciMemParamTableCurrent;

#ifdef __cplusplus
}
#endif

#endif /* ASCTECCOMMINTF_H_ */
