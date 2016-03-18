/*

Copyright (c) 2013, Ascending Technologies GmbH
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

#ifdef __cplusplus
extern "C"
 {
 #endif
#include "asctecCommIntf.h"

//internal global vars
unsigned int aciEngineRate=100;

//aci var table global variables
unsigned short aciVarTableLength=0;
unsigned short *aciRequestedPacketList=0;
unsigned short aciRequestedPacketListLength=0;
unsigned short aciRequestedPacketListTimeOut;

unsigned short aciRequestVarListTimeout=60000;
unsigned short aciRequestCmdListTimeout=60000;
unsigned short aciRequestParListTimeout=60000;

unsigned char aciCmdWithAck[MAX_VAR_PACKETS] = {0,0,0};

unsigned short * aciVarPacket[MAX_VAR_PACKETS];
unsigned char * aciVarPacketBuffer[MAX_VAR_PACKETS];
unsigned char * aciVarPacketContentBuffer[MAX_VAR_PACKETS];

unsigned char aciVarPacketContentBufferValid[MAX_VAR_PACKETS];
unsigned char aciVarPacketContentBufferInvalidCnt[MAX_VAR_PACKETS];

unsigned short aciVarPacketContentBufferLength[MAX_VAR_PACKETS];
unsigned short aciVarPacketLength[MAX_VAR_PACKETS]={0,0,0};
unsigned short aciUpdateVarPacketTimeOut[MAX_VAR_PACKETS]={0,0,0};
unsigned char aciVarPacketMagicCode[MAX_VAR_PACKETS]={0,0,0}; 
unsigned short aciVarPacketTransmissionRate[MAX_VAR_PACKETS]={100,10,1};

// Command
//internal global vars
unsigned short aciCmdTableLength=0;
unsigned short *aciRequestedCmdPacketList;
unsigned short aciRequestedCmdPacketListLength=0;
unsigned short aciRequestedCmdPacketListTimeOut;

unsigned char aciCmdPacketSendStatus[MAX_VAR_PACKETS]={0,0,0}; // 0 nothing to send, 1 something to send, 2 waiting for ACK
unsigned short *aciCmdPacket[MAX_VAR_PACKETS];
unsigned short aciCmdPacketLength[MAX_VAR_PACKETS]={0,0,0};
unsigned short aciUpdateCmdPacketTimeOut[MAX_VAR_PACKETS]={0,0,0};
unsigned char aciCmdPacketMagicCode[MAX_VAR_PACKETS]={0,0,0};
unsigned short aciCmdPacketContentBufferLength[MAX_VAR_PACKETS];

unsigned char * aciCmdPacketContentBuffer[MAX_VAR_PACKETS];

// Parameter
unsigned short aciParamTableLength=0;
unsigned short *aciRequestedParamPacketList;
unsigned short aciRequestedParamPacketListLength=0;
unsigned short aciRequestedParamPacketListTimeOut;

unsigned char aciParamPacketSendStatus[MAX_VAR_PACKETS]={0,0,0}; // 0 nothing to send, 1 something to send, 2 waiting for ACK
unsigned short *aciParamPacket[MAX_VAR_PACKETS];
unsigned short aciParamPacketLength[MAX_VAR_PACKETS]={0,0,0};
unsigned short aciUpdateParamPacketTimeOut[MAX_VAR_PACKETS]={0,0,0};
unsigned char aciParamPacketStatus[MAX_VAR_PACKETS]={0,0,0};
unsigned char aciParamPacketMagicCode[MAX_VAR_PACKETS]={0,0,0};
unsigned short aciParamPacketContentBufferLength[MAX_VAR_PACKETS];

unsigned char * aciParamPacketContentBuffer[MAX_VAR_PACKETS];

// unsigned short aciVarPacketCurrentSize[MAX_VAR_PACKETS]={0,0,0};
// unsigned short aciVarPacketNumberOfVars[MAX_VAR_PACKETS]={0,0,0};
unsigned char aciCmdPacketUpdated[MAX_VAR_PACKETS]={0,0,0};

///heart beat in HZ
unsigned short aciHeartBeatRate=10; 

///table to handle local ID to var connection
struct ACI_MEM_VAR_ASSIGN_TABLE * aciVarAssignTableStart;
struct ACI_MEM_VAR_ASSIGN_TABLE * aciVarAssignTableCurrent;

struct ACI_MEM_VAR_ASSIGN_TABLE * aciCmdAssignTableStart;
struct ACI_MEM_VAR_ASSIGN_TABLE * aciCmdAssignTableCurrent;

struct ACI_MEM_VAR_ASSIGN_TABLE * aciParamAssignTableStart;
struct ACI_MEM_VAR_ASSIGN_TABLE * aciParamAssignTableCurrent;

struct ACI_INFO aciInfo;

//RX global variables
unsigned char aciRxDataBuffer[ACI_RX_BUFFER_SIZE];
unsigned short aciRxDataCnt;

struct ACI_MEM_VAR_TABLE * aciMemVarTableStart;
struct ACI_MEM_VAR_TABLE * aciMemVarTableCurrent;

struct ACI_MEM_VAR_TABLE * aciMemCmdTableStart;
struct ACI_MEM_VAR_TABLE * aciMemCmdTableCurrent;

struct ACI_MEM_VAR_TABLE * aciMemParamTableStart;
struct ACI_MEM_VAR_TABLE * aciMemParamTableCurrent;

//aci helper prototypes
void aciFreeMemVarTable(struct ACI_MEM_VAR_TABLE * ptr);

///update CRC with 1 byte
unsigned short aciCrcUpdate (unsigned short crc, unsigned char data);
///update crc with multiple bytes
unsigned short aciUpdateCrc16(unsigned short crc, void * data, unsigned short cnt);

//aciRxHandler prototypes
void aciRxHandleMessage(unsigned char messagetype, unsigned short length);

// aci
void aciParamAck(unsigned char packet);

void aciStoreList();
void aciLoadHeaderList();
void aciLoadList();

//aci TX prototypes
void aciTxSendPacket(unsigned char aciMessageType, void * data, unsigned short cnt);
void (*aciSendData)(void * data, unsigned short cnt);
void (*aciVarListUpdateFinished)(void);
void (*aciCmdListUpdateFinished)(void);
void (*aciCmdAck)(unsigned char packet);
void (*aciParamListUpdateFinished)(void);
void (*aciInfoRec)(struct ACI_INFO);
void (*aciVarPacketRec)(unsigned char packet);
void (*aciParaStoredC) (void);
void (*aciParaLoadedC) (void);
void (*aciSingleReceivedC)(unsigned short id, void * data, unsigned char varType);
void (*aciSingleReqReceivedC)(unsigned short id, void * data, unsigned char varType);
int (*aciReadHDC)(void *data, int bytes);
int (*aciWriteHDC)(void *data, int bytes);
void (*aciResetHDC)();

unsigned short aciHeartBeatCnt=0;

unsigned short aciMagicCodeVarLoaded = 0;
unsigned short aciMagicCodeCmdLoaded = 0;
unsigned short aciMagicCodeParLoaded = 0;

unsigned short aciMagicCodeVar = 0x00FF;
unsigned short aciMagicCodeCmd = 0x00FF;
unsigned short aciMagicCodePar = 0x00FF;

unsigned short aciRequestMagicCodes = 0;

unsigned char aciMagicCodeOnHDFalse = 0;

/*
 * 0x01 var, 0x02 Cmd, 0x04 par
 * 0x10 var already loaded succesfully
 * 0x20 cmd already loaded succesfully
 * 0x40 par already loaded succesfully
 *
 */
unsigned char aciRequestListType=0;

/** Search for a variable in any created packet and returns its success.
 * @param ptrToVar Pointer to the variable, where the value will be stored. If there is no memory allocated for the pointer, there will be allocated with the size of varType. Make sure, that the size of allocated memory is the same as varType.
 * @param varType The type of the consigning pointer. This should be one of the defined \link #vartype variables type \endlink
 * @param id The id of the variable, which should be set in \a ptrToVar
 * @return If the value could be set, it returns 1 otherwise 0.
**/
char aciGetVarById(void * ptrToVar, const unsigned char varType, const unsigned short id);
     

//aci assignment table prototypes

void aciFreeMemVarTable(struct ACI_MEM_VAR_TABLE * ptr)
{
	if (ptr->next)
		aciFreeMemVarTable(ptr->next);
	free(ptr);
}

void aciCheckVerConf() {
	aciTxSendPacket(ACIMT_INFO_REQUEST,NULL,0);
}

void aciParamAck(unsigned char packet)
{
	aciParamPacketSendStatus[packet]=0;
}

/** has to be called ones during initialisation **/
void aciInit(void)
{
     int i;
    if (aciMemVarTableStart)
		aciFreeMemVarTable(aciMemVarTableStart);

    for (i=0;i<MAX_VAR_PACKETS;i++)
    {
        aciResetVarPacketContent(i);
        aciVarPacketContentBufferValid[i]=0;  
        aciVarPacketContentBufferInvalidCnt[i]=0;  
    }
    aciHeartBeatCnt=0;
    
    aciVarAssignTableStart=(struct ACI_MEM_VAR_ASSIGN_TABLE *) malloc(sizeof(struct ACI_MEM_VAR_ASSIGN_TABLE));
    aciVarAssignTableStart->next=NULL;
             
	aciMemVarTableStart=(struct ACI_MEM_VAR_TABLE *) malloc(sizeof(struct ACI_MEM_VAR_TABLE));

	aciMemVarTableStart->next=NULL;
    
    aciCmdAssignTableStart=(struct ACI_MEM_VAR_ASSIGN_TABLE *) malloc(sizeof(struct ACI_MEM_VAR_ASSIGN_TABLE));
    aciCmdAssignTableStart->next=NULL;
             
	aciMemCmdTableStart=(struct ACI_MEM_VAR_TABLE *) malloc(sizeof(struct ACI_MEM_VAR_TABLE));

	aciMemCmdTableStart->next=NULL;
    
    aciParamAssignTableStart=(struct ACI_MEM_VAR_ASSIGN_TABLE *) malloc(sizeof(struct ACI_MEM_VAR_ASSIGN_TABLE));
    aciParamAssignTableStart->next=NULL;
             
	aciMemParamTableStart=(struct ACI_MEM_VAR_TABLE *) malloc(sizeof(struct ACI_MEM_VAR_TABLE));

	aciMemParamTableStart->next=NULL;
    
    aciRequestedPacketList=NULL;

    aciInfo.verMajor=0;
    aciInfo.verMinor=0;
    aciInfo.maxNameLength=0;
    aciInfo.maxDescLength=0;
    aciInfo.maxUnitLength=0;
    aciInfo.maxVarPackets=0;
    aciInfo.memPacketMaxVars=0;
}

void aciResetRemote(void)
{
     //reset remote link
     aciTxSendPacket(ACIMT_RESETREMOTE,NULL,0);
}

void aciEngine(void)
{
    int i;
    static unsigned int aciParPacketCnt[MAX_VAR_PACKETS] = {0,0,0};
    static unsigned int aciCmdPacketCnt[MAX_VAR_PACKETS] = {0,0,0};
    unsigned short crc=0xff;
   // unsigned char heartbeat_to_send = 1;

    if(aciRequestMagicCodes) {
    	if(aciRequestMagicCodes==1) {
    		aciTxSendPacket(ACIMT_MAGICCODES,NULL,0);
    	} else if (aciRequestMagicCodes>aciEngineRate) aciRequestMagicCodes=1;
    	else aciRequestMagicCodes++;
    }

    if(aciRequestVarListTimeout!=60000)
    {
   	 aciHeartBeatCnt=0;
   	 if(aciRequestVarListTimeout) aciRequestVarListTimeout--;
   	 else {
   		 aciTxSendPacket(ACIMT_GETVARTABLEINFO, NULL, 0);
   		 aciRequestVarListTimeout=ACI_REQUEST_LIST_TIMEOUT;
   	 }
    }

    if(aciRequestCmdListTimeout!=60000)
    {
   	 aciHeartBeatCnt=0;
   	 if(aciRequestCmdListTimeout) aciRequestCmdListTimeout--;
   	 else {
   		 aciTxSendPacket(ACIMT_GETCMDTABLEINFO, NULL, 0);
   		 aciRequestCmdListTimeout=ACI_REQUEST_LIST_TIMEOUT;
   	 }
    }

    if(aciRequestParListTimeout!=60000)
    {
   	 aciHeartBeatCnt=0;
   	 if(aciRequestParListTimeout) aciRequestParListTimeout--;
   	 else {
   		 aciTxSendPacket(ACIMT_GETPARAMTABLEINFO, NULL, 0);
   		 aciRequestParListTimeout=ACI_REQUEST_LIST_TIMEOUT;
   	 }
    }



    if (aciRequestedPacketListLength)
    {
   	 aciHeartBeatCnt=0;
       if (aciRequestedPacketListTimeOut)
          aciRequestedPacketListTimeOut--;
       else
       {
               aciTxSendPacket(ACIMT_REQUESTVARTABLEENTRIES,aciRequestedPacketList,2);
               aciRequestedPacketListTimeOut=ACI_REQUEST_LIST_TIMEOUT;
       }

    }
    if (aciRequestedCmdPacketListLength)
    {
   	 aciHeartBeatCnt=0;
       if (aciRequestedCmdPacketListTimeOut)
       	aciRequestedCmdPacketListTimeOut--;
       else
       {
               aciTxSendPacket(ACIMT_REQUESTCMDTABLEENTRIES,aciRequestedCmdPacketList,2);
               aciRequestedCmdPacketListTimeOut=ACI_REQUEST_LIST_TIMEOUT;
       }

    }
    if (aciRequestedParamPacketListLength)
    {
   	 aciHeartBeatCnt=0;
       if (aciRequestedParamPacketListTimeOut)
       	aciRequestedParamPacketListTimeOut--;
       else
       {
               aciTxSendPacket(ACIMT_REQUESTPARAMTABLEENTRIES,aciRequestedParamPacketList,2);
               aciRequestedParamPacketListTimeOut=ACI_REQUEST_LIST_TIMEOUT;
       }

    }



    for (i=0;i<MAX_VAR_PACKETS;i++)
    {
        if (aciUpdateVarPacketTimeOut[i])
        {
         aciUpdateVarPacketTimeOut[i]--;
         if (!aciUpdateVarPacketTimeOut[i])
            {
               //packet was not acknoledged -> send again

                unsigned char * temp;
                crc=0xff;

                crc=aciUpdateCrc16(crc,aciVarPacket[i],aciVarPacketLength[i]*2);

                temp=(unsigned char*) malloc(aciVarPacketLength[i]*2+1);
                memcpy(&temp[1],aciVarPacket[i],aciVarPacketLength[i]*2);
                temp[0]=crc;
                aciVarPacketMagicCode[i]=crc;

                aciTxSendPacket(ACIMT_UPDATEVARPACKET+i,temp,aciVarPacketLength[i]*2+1);
                aciUpdateVarPacketTimeOut[i]=ACI_UPDATE_PACKET_TIMEOUT;
                free(temp);
            }
        }

        if (aciUpdateCmdPacketTimeOut[i])
        {
       	 aciHeartBeatCnt=0;
         aciUpdateCmdPacketTimeOut[i]--;
         if (!aciUpdateCmdPacketTimeOut[i])
            {
              // packet was not acknoledged -> send again
                unsigned char * temp;

            	crc = 0xff;
            	crc = aciUpdateCrc16(crc, aciCmdPacket[i],
            			aciCmdPacketLength[i] * 2);

            	temp = malloc(aciCmdPacketLength[i] * 2 + 2);
            	memcpy(&temp[2], aciCmdPacket[i], aciCmdPacketLength[i] * 2);
            	temp[0] = crc;
            	temp[1] = aciCmdWithAck[i];
                aciCmdPacketMagicCode[i]=crc;

                aciTxSendPacket(ACIMT_UPDATECMDPACKET+i,temp,aciCmdPacketLength[i]*2+2);
                aciUpdateCmdPacketTimeOut[i]=ACI_UPDATE_PACKET_TIMEOUT;
                free(temp);
            }
        }

        if (aciUpdateParamPacketTimeOut[i])
        {
       	 aciHeartBeatCnt=0;
         aciUpdateParamPacketTimeOut[i]--;
         if (!aciUpdateParamPacketTimeOut[i])
            {
               //packet was not acknoledged -> send again
                unsigned char * temp;
                crc=0xff;

                crc=aciUpdateCrc16(crc,aciParamPacket[i],aciParamPacketLength[i]*2);

                temp=(unsigned char*)malloc(aciParamPacketLength[i]*2+1);
                memcpy(&temp[1],aciParamPacket[i],aciParamPacketLength[i]*2);
                temp[0]=crc;
                aciParamPacketMagicCode[i]=crc;

                aciTxSendPacket(ACIMT_UPDATEPARAMPACKET+i,temp,aciParamPacketLength[i]*2+1);
                aciUpdateParamPacketTimeOut[i]=ACI_UPDATE_PACKET_TIMEOUT;
                free(temp);
            }
        }
    }

    for (i=0;i<MAX_VAR_PACKETS;i++)
	 {

		// Check Status, if packet for send is avaible.
		if ((aciCmdPacketSendStatus[i] == 1)) {
			aciHeartBeatCnt=0;
			// Send Commando
			unsigned char *temp;
			unsigned char cnt=0;
			temp = (unsigned char*)malloc(aciCmdPacketContentBufferLength[i]+1);
			temp[cnt++]=aciCmdPacketMagicCode[i];

			//add data to ringbuffer and calculate CRC
			for (int z = 0; z < aciCmdPacketLength[i]; z++) {
				memcpy(&temp[cnt],aciGetCommandItemById(aciCmdPacket[i][z])->ptrToVar,aciGetCommandItemById(aciCmdPacket[i][z])->varType >> 2);
				cnt+=(aciGetCommandItemById(aciCmdPacket[i][z])->varType >> 2);
			}
			aciTxSendPacket(ACIMT_CMDPACKET + i, &temp[0],	aciCmdPacketContentBufferLength[i] + 1);

			if(!aciCmdWithAck[i])
					aciCmdPacketSendStatus[i] = 0; // Commando sended, do not send it again
			else {
				aciCmdPacketSendStatus[i] = 2;
			}
			free(temp);
		}  else if (aciCmdPacketSendStatus[i] == 2) {
			aciCmdPacketCnt[i]++;
			if(aciCmdPacketCnt[i]%(aciEngineRate/2)==0)
				{
				aciCmdPacketCnt[i]=0;
				aciCmdPacketSendStatus[i] = 1;
				}
		}

		// Check Status, if packet for send is available.
		if (!aciParamPacketSendStatus[i])
			continue;
		else if (aciParamPacketSendStatus[i] == 1) {

			// Send Parameter
			unsigned char *temp;
			unsigned char cnt=0;
			temp = (unsigned char*)malloc(aciParamPacketContentBufferLength[i]+1);
			temp[cnt++]=aciParamPacketMagicCode[i];
			for (int z = 0; z < aciParamPacketLength[i]; z++) {
				memcpy(&temp[cnt],aciGetParameterItemById(aciParamPacket[i][z])->ptrToVar,aciGetParameterItemById(aciParamPacket[i][z])->varType >> 2);
				cnt+=(aciGetParameterItemById(aciParamPacket[i][z])->varType >> 2);
			}
			aciTxSendPacket(ACIMT_PARAMPACKET + i, &temp[0], aciParamPacketContentBufferLength[i] + 1);
			aciParamPacketSendStatus[i] = 2;
			free(temp);
		} else if (aciParamPacketSendStatus[i] == 2) {
			aciParPacketCnt[i]++;
			if(aciParPacketCnt[i]%(aciEngineRate/2)==0)
				{
				aciParPacketCnt[i]=0;
				aciParamPacketSendStatus[i] = 1;
				}
		}

	 }

    aciHeartBeatCnt++;

    if (aciHeartBeatCnt>=(aciEngineRate/aciHeartBeatRate))
    {
       aciHeartBeatCnt=0;
      aciTxSendPacket(ACIMT_HEARBEAT,NULL,0);
    }
}

void aciSetEngineRate(const unsigned short callsPerSecond, const unsigned short heartbeat)
{
     aciEngineRate=callsPerSecond;
     aciHeartBeatRate=heartbeat;
}     

#ifdef __cplusplus
void aciSetSendDataCallback(void (*aciSendDataCallback_func)(unsigned char * data, unsigned short cnt))
#else
void aciSetSendDataCallback(void (*aciSendDataCallback_func)(void * data, unsigned short cnt))
#endif
{
 aciSendData=aciSendDataCallback_func; 
}


void aciResetVarPacketContent(unsigned char packetId)
{
    if (aciVarPacket[packetId])
       free(aciVarPacket[packetId]);
    aciVarPacket[packetId]=NULL;
    aciVarPacketLength[packetId]=0;
}

void aciResetCmdPacketContent(unsigned char packetId)
{
    if (aciCmdPacket[packetId])
       free(aciCmdPacket[packetId]);
    aciCmdPacket[packetId]=NULL;
    aciCmdPacketLength[packetId]=0;
}

void aciResetParPacketContent(unsigned char packetId)
{
    if (aciParamPacket[packetId])
       free(aciParamPacket[packetId]);
    aciParamPacket[packetId]=NULL;
    aciParamPacketLength[packetId]=0;
}

/** get length of ID list of Packet **/
unsigned short aciGetVarPacketLength(unsigned char packetId)
{
         return aciVarPacketLength[packetId];         
}

/* get length of ID list of Packet */
unsigned short aciGetCmdPacketLength(unsigned char packetId)
{
         return aciCmdPacketLength[packetId];
}

unsigned short aciGetParPacketLength(unsigned char packetId)
{
         return aciParamPacketLength[packetId];
}

/**get variable packet item by index **/
unsigned short aciGetVarPacketItem(unsigned char packetId, unsigned short index)
{
 if (index<aciGetVarPacketLength(packetId))
    return aciVarPacket[packetId][index];
 else
    return 0;         
}

unsigned short aciGetCmdPacketItem(unsigned char packetId, unsigned short index)
{
 if (index<aciGetCmdPacketLength(packetId))
    return aciCmdPacket[packetId][index];
 else
    return 0;
}

unsigned short aciGetParPacketItem(unsigned char packetId, unsigned short index)
{
 if (index<aciGetParPacketLength(packetId))
    return aciParamPacket[packetId][index];
 else
    return 0;
}

unsigned short aciGetVarPacketRate(unsigned char packetId)
{
	return aciVarPacketTransmissionRate[packetId];
}

void aciGetVarPacketRateFromDevice()
{
	 aciTxSendPacket(ACIMT_GETPACKETRATE,NULL,0);
}

void aciAddContentToVarPacket(unsigned char packetId, unsigned short id,  void *var_ptr)
{
	if(var_ptr==NULL) return;
	if(aciGetVariableItemById(id)==NULL) return;
	if(packetId>=MAX_VAR_PACKETS) return;
     if (aciVarPacket[packetId]==NULL)
        {
           aciVarPacket[packetId]=malloc(2);
           aciVarPacket[packetId][0]=id;
           aciVarPacketLength[packetId]=1;
           aciGetVariableItemById(id)->ptrToVar=var_ptr;
        } else {
           unsigned short * ptr;
           int i;
 
           //check for double entries
           for (i=0;i<aciVarPacketLength[packetId];i++)
               if (aciVarPacket[packetId][i]==id)
                  return;
                  
           aciVarPacketLength[packetId]++;
           ptr=malloc(2*aciVarPacketLength[packetId]);
           memcpy(ptr,aciVarPacket[packetId],(aciVarPacketLength[packetId]-1)*2);
           free(aciVarPacket[packetId]);
           aciVarPacket[packetId]=ptr;
           aciVarPacket[packetId][aciVarPacketLength[packetId]-1]=id;
           aciGetVariableItemById(id)->ptrToVar=var_ptr;
        }
}

void aciAddContentToCmdPacket(const unsigned char packetId,const unsigned short id, void *var_ptr)
{
	if(var_ptr==NULL) return;
	if(aciGetCommandItemById(id)==NULL) return;
	if(packetId>=MAX_VAR_PACKETS) return;
	if(packetId<MAX_VAR_PACKETS) {
		aciCmdPacketUpdated[packetId]=1;

     if (aciCmdPacket[packetId]==NULL)
        {
           aciCmdPacket[packetId]=malloc(2);
           aciCmdPacket[packetId][0]=id;
           aciCmdPacketLength[packetId]=1;
           if(aciGetCommandItemById(id)==NULL) return;
           aciGetCommandItemById(id)->ptrToVar=var_ptr;
        }
     else
        {
           unsigned short * ptr;
           int i;

           //check for double entries
           for (i=0;i<aciCmdPacketLength[packetId];i++)
               if (aciCmdPacket[packetId][i]==id)
                  return;

           aciCmdPacketLength[packetId]++;
           ptr=malloc(2*aciCmdPacketLength[packetId]);
           memcpy(ptr,aciCmdPacket[packetId],(aciCmdPacketLength[packetId]-1)*2);
           free(aciCmdPacket[packetId]);
           aciCmdPacket[packetId]=ptr;
           aciCmdPacket[packetId][aciCmdPacketLength[packetId]-1]=id;
           aciGetCommandItemById(id)->ptrToVar=var_ptr;
        }
	}
}

void aciAddContentToParamPacket(unsigned char packetId,unsigned short id, void *var_ptr) {
	if(var_ptr==NULL) return;
	if(aciGetParameterItemById(id)==NULL) return;
	if(packetId>=MAX_VAR_PACKETS) return;
	if(packetId<MAX_VAR_PACKETS) {

     if (aciParamPacket[packetId]==NULL)
        {
           aciParamPacket[packetId]=malloc(2);
           aciParamPacket[packetId][0]=id;
           aciParamPacketLength[packetId]=1;
           aciGetParameterItemById(id)->ptrToVar=var_ptr;
        }
     else
        {
           unsigned short * ptr;
           int i;

           //check for double entries
           for (i=0;i<aciParamPacketLength[packetId];i++)
               if (aciParamPacket[packetId][i]==id)
                  return;

           aciParamPacketLength[packetId]++;
           ptr=malloc(2*aciParamPacketLength[packetId]);
           memcpy(ptr,aciParamPacket[packetId],(aciParamPacketLength[packetId]-1)*2);
           free(aciParamPacket[packetId]);
           aciParamPacket[packetId]=ptr;
           aciParamPacket[packetId][aciParamPacketLength[packetId]-1]=id;
           aciGetParameterItemById(id)->ptrToVar=var_ptr;
        }
     aciTxSendPacket(ACIMT_PARAM, &id,2);
	}
}


struct ACI_MEM_VAR_ASSIGN_TABLE *aciVarGetAssignmentById(unsigned short id) {
	aciVarAssignTableCurrent = aciVarAssignTableStart;

	//check for existing variable assignments
	while (aciVarAssignTableCurrent->next) {
		aciVarAssignTableCurrent = aciVarAssignTableCurrent->next;
		if (aciVarAssignTableCurrent->id == id)
			return aciVarAssignTableCurrent;
	}
	return NULL;
}

void aciSetVarPacketTransmissionRate(unsigned char packetId, unsigned short callsPerSecond)
{
	if(packetId<MAX_VAR_PACKETS)
	{
		aciVarPacketTransmissionRate[packetId]=callsPerSecond;
	}
}

void aciVarPacketUpdateTransmissionRates(void)
{
	aciTxSendPacket(ACIMT_CHANGEPACKETRATE,&aciVarPacketTransmissionRate[0],sizeof(aciVarPacketTransmissionRate));
}




char aciGetVarById(void * ptrToVar, const unsigned char varType, const unsigned short id)
{
  int i;
  
  for (i=0;i<MAX_VAR_PACKETS;i++)
  {
      int z;
      unsigned char * ptr;
      if (!aciVarPacketContentBufferValid[i])
         continue;
      ptr=aciVarPacketContentBuffer[i];
      for (z=0;z<aciVarPacketLength[i];z++)
      {
          struct ACI_MEM_TABLE_ENTRY *entry;
          
          entry=aciGetVariableItemById(aciVarPacket[i][z]);
          if ((aciVarPacket[i][z]==id) && (entry))
          {

             if (entry->varType==varType)
             {
            	if(ptrToVar)
            		memcpy(ptrToVar,ptr,varType>>2);
            	else {
            		ptrToVar=malloc(varType>>2);
            		memcpy(ptrToVar,ptr,varType>>2);
            	}
                return 1;
             }
          }
          //entry should always exist!
          if (entry) {
             ptr+=entry->varType>>2;
          }
          else
             return 0; //otherwise stop sync!
      }
  } 
  return 0;

}

void aciSynchronizeVars(void)
{
  int i;
  
  for (i=0;i<MAX_VAR_PACKETS;i++)
  {
      int z;
      unsigned char * ptr;
      if (!aciVarPacketContentBufferValid[i])
         continue;

      ptr=aciVarPacketContentBuffer[i];
      for (z=0;z<aciVarPacketLength[i];z++)
      {
          struct ACI_MEM_TABLE_ENTRY *entry;
          entry=aciGetVariableItemById(aciVarPacket[i][z]);
          if ((entry))
          {
             memcpy(entry->ptrToVar,ptr,entry->varType>>2);
          }
          //entry should always exist!
          if (entry)
             ptr+=entry->varType>>2;
          else
             return; //otherwise stop sync!
      }
  }
}

/**send variables packet configuration onboard**/
void aciSendVariablePacketConfiguration(unsigned char packetId) {

	if(packetId>=MAX_VAR_PACKETS) return;
	unsigned char * temp;
	unsigned short crc = 0xff;
	int i;
	unsigned short packetDataLength = 0;
	crc = 0xff;
	crc = aciUpdateCrc16(crc, aciVarPacket[packetId],
			aciVarPacketLength[packetId] * 2);

	temp = malloc(aciVarPacketLength[packetId] * 2 + 1);
	memcpy(&temp[1], aciVarPacket[packetId], aciVarPacketLength[packetId] * 2);
	temp[0] = crc;

	for (i = 0; i < aciVarPacketLength[packetId]; i++) {
		struct ACI_MEM_TABLE_ENTRY *entry;

		entry = aciGetVariableItemById(aciVarPacket[packetId][i]);
		packetDataLength += entry->varType >> 2;
	}

	aciVarPacketMagicCode[packetId] = crc;
	aciVarPacketContentBufferLength[packetId] = 0;

	//reallocate temporary buffer
	free(aciVarPacketContentBuffer[packetId]);
	aciVarPacketContentBuffer[packetId] = malloc(packetDataLength);
	aciVarPacketContentBufferLength[packetId] = packetDataLength;

	aciTxSendPacket(ACIMT_UPDATEVARPACKET + packetId, temp,
			aciVarPacketLength[packetId] * 2 + 1);
	aciUpdateVarPacketTimeOut[packetId] = ACI_UPDATE_PACKET_TIMEOUT;
	free(temp);

}

/**send command packet configuration onboard**/
void aciSendCommandPacketConfiguration(unsigned char packetId, unsigned char with_ack) {
	unsigned char * temp;
	unsigned short crc = 0xff;
	int i;
	unsigned short packetDataLength = 0;
	if(packetId>=MAX_VAR_PACKETS) return;
	crc = 0xff;
	crc = aciUpdateCrc16(crc, aciCmdPacket[packetId],
			aciCmdPacketLength[packetId] * 2);

	temp = malloc(aciCmdPacketLength[packetId] * 2 + 2);
	memcpy(&temp[2], aciCmdPacket[packetId], aciCmdPacketLength[packetId] * 2);
	temp[0] = crc;
	temp[1] = with_ack;

	for (i = 0; i < aciCmdPacketLength[packetId]; i++) {
		struct ACI_MEM_TABLE_ENTRY *entry;

		entry = aciGetCommandItemById(aciCmdPacket[packetId][i]);
		packetDataLength += entry->varType >> 2;
	}

	aciCmdPacketMagicCode[packetId] = crc;
	aciCmdPacketContentBufferLength[packetId] = 0;

	aciCmdWithAck[packetId]=with_ack;
	//reallocate temporary buffer
	free(aciCmdPacketContentBuffer[packetId]);
	aciCmdPacketContentBuffer[packetId] = malloc(packetDataLength);
	aciCmdPacketContentBufferLength[packetId] = packetDataLength;

	aciTxSendPacket(ACIMT_UPDATECMDPACKET + packetId, temp,
			aciCmdPacketLength[packetId] * 2 + 2);
	aciUpdateCmdPacketTimeOut[packetId] = ACI_UPDATE_PACKET_TIMEOUT;
	free(temp);
}

/**send command packet configuration onboard**/
void aciSendParameterPacketConfiguration(unsigned char packetId) {
	unsigned char * temp;
	unsigned short crc = 0xff;
	int i;
	unsigned short packetDataLength = 0;
	crc = 0xff;
	crc = aciUpdateCrc16(crc, aciParamPacket[packetId],
			aciParamPacketLength[packetId] * 2);

	temp = malloc(aciParamPacketLength[packetId] * 2 + 1);
	memcpy(&temp[1], aciParamPacket[packetId], aciParamPacketLength[packetId] * 2);
	temp[0] = crc;

	for (i = 0; i < aciParamPacketLength[packetId]; i++) {
		struct ACI_MEM_TABLE_ENTRY *entry;

		entry = aciGetParameterItemById(aciParamPacket[packetId][i]);
		packetDataLength += entry->varType >> 2;
	}

	aciParamPacketMagicCode[packetId] = crc;
	aciParamPacketContentBufferLength[packetId] = 0;

	//reallocate temporary buffer
	free(aciParamPacketContentBuffer[packetId]);
	aciParamPacketContentBuffer[packetId] = malloc(packetDataLength);
	aciParamPacketContentBufferLength[packetId] = packetDataLength;

	aciTxSendPacket(ACIMT_UPDATEPARAMPACKET + packetId, temp,
			aciParamPacketLength[packetId] * 2 + 1);
	aciUpdateParamPacketTimeOut[packetId] = ACI_UPDATE_PACKET_TIMEOUT;
	free(temp);
}


void aciSetVarListUpdateFinishedCallback(void(*aciVarListUpdateFinished_func)(void)) {
	aciVarListUpdateFinished = aciVarListUpdateFinished_func;
}

void aciSetCmdListUpdateFinishedCallback(void(*aciCmdListUpdateFinished_func)(void)) {
	aciCmdListUpdateFinished = aciCmdListUpdateFinished_func;
}

void aciSetParamListUpdateFinishedCallback(void(*aciParamListUpdateFinished_func)(void)) {
	aciParamListUpdateFinished = aciParamListUpdateFinished_func;
}
void aciSetCmdAckCallback(void (*aciCmdAck_func)(unsigned char)) {
	aciCmdAck = aciCmdAck_func;
}

void aciInfoPacketReceivedCallback(void (*aciInfoRec_func)(struct ACI_INFO)) {
	aciInfoRec = aciInfoRec_func;
}

void aciVarPacketReceivedCallback(void (*aciVarPacketRec_func)(unsigned char)) {
	aciVarPacketRec = aciVarPacketRec_func;
}

void aciParPacketStoredCallback(void (*aciParPacketStored_func)(void)) {
	aciParaStoredC=aciParPacketStored_func;
}

void aciParPacketLoadedCallback(void (*aciParPacketLoaded_func)(void)) {
	aciParaLoadedC=aciParPacketLoaded_func;
}

void aciTxSendPacket(unsigned char aciMessageType, void * data,
		unsigned short cnt) {
	unsigned char startstring[3] = { '!', '#', '!' };
	unsigned short crc = 0xFF;
	unsigned char packetTxBuffer[ACI_TX_RINGBUFFER_SIZE];
	int pos = 0;

	if (cnt + 10 >= ACI_TX_RINGBUFFER_SIZE)
		return;

	//add header to ringbuffer
	memcpy(&packetTxBuffer[pos], &startstring, 3);
	pos += 3;
	//add message type to ringbuffer
	memcpy(&packetTxBuffer[pos], &aciMessageType, 1);
	pos += 1;
	crc = aciUpdateCrc16(crc, &aciMessageType, 1);

	//add data size to ringbuffer
	memcpy(&packetTxBuffer[pos], &cnt, 2);
	pos += 2;
	crc = aciUpdateCrc16(crc, &cnt, 2);

	memcpy(&packetTxBuffer[pos], data, cnt);
	pos += cnt;
	crc = aciUpdateCrc16(crc, data, cnt);

	//add CRC to ringbuffer
	memcpy(&packetTxBuffer[pos], &crc, 2);
	pos += 2;

	if (aciSendData)
		aciSendData(&packetTxBuffer[0], pos);

}

void aciGetDeviceVariablesList(void) {

	if(!(aciRequestListType&0x10)) {
		if(aciReadHDC && !aciMagicCodeOnHDFalse) {
			aciRequestListType|=0x01;
			aciRequestMagicCodes=1;
		} else {
			aciRequestVarListTimeout=0;
		}
	}
}

void aciGetDeviceCommandsList(void) {

	if(!(aciRequestListType&0x20)) {
		if(aciReadHDC && !aciMagicCodeOnHDFalse) {
			aciRequestListType|=0x02;
			aciRequestMagicCodes=1;
		} else {
			aciRequestCmdListTimeout=0;
		}
	}
}

void aciGetDeviceParametersList(void) {
	if(!(aciRequestListType&0x40)) {
		if(aciReadHDC && !aciMagicCodeOnHDFalse) {
			aciRequestListType|=0x04;
			aciRequestMagicCodes=1;
		} else {
			aciRequestParListTimeout=0;
		}
	}
}

void aciForceListRequestFromDevice() {
	aciMagicCodeOnHDFalse=1;
	aciRequestListType=0;
}

void aciGetParamFromDevice(unsigned short id) {
	aciTxSendPacket(ACIMT_PARAM, &id, 2);
}

/** get list item by index **/
struct ACI_MEM_TABLE_ENTRY *aciGetVariableItemByIndex(unsigned short index) {
	unsigned short i = 0;
	aciMemVarTableCurrent = aciMemVarTableStart;
	while (aciMemVarTableCurrent->next) {
		aciMemVarTableCurrent = aciMemVarTableCurrent->next;
		if (i == index)
			return (&aciMemVarTableCurrent->tableEntry);
		i++;
	}
	return NULL;
}

/** try to find a list item by id **/
struct ACI_MEM_TABLE_ENTRY *aciGetVariableItemById(unsigned short id) {
	aciMemVarTableCurrent = aciMemVarTableStart;
	while (aciMemVarTableCurrent->next) {
		aciMemVarTableCurrent = aciMemVarTableCurrent->next;
		if (aciMemVarTableCurrent->tableEntry.id == id)
			return (&aciMemVarTableCurrent->tableEntry);
	}
	return NULL;
}

/** try to find a list item by name **/
struct ACI_MEM_TABLE_ENTRY *aciGetVariableItemByName(char * name) {
	if(name==NULL) return NULL;
	aciMemVarTableCurrent = aciMemVarTableStart;
	while (aciMemVarTableCurrent->next) {
		aciMemVarTableCurrent = aciMemVarTableCurrent->next;
		if (strcmp(&(aciMemVarTableCurrent->tableEntry.name[0]), name))
			return (&aciMemVarTableCurrent->tableEntry);
	}
	return NULL;
}

/**get length of var table**/
unsigned short aciGetVarTableLength(void) {
	unsigned short length = 0;

	aciMemVarTableCurrent = aciMemVarTableStart;
	while (aciMemVarTableCurrent->next) {
		length++;
		aciMemVarTableCurrent = aciMemVarTableCurrent->next;
	}
	return length;
}


struct ACI_INFO aciGetInfo(void)
{
	return aciInfo;
}

/** get list item by index **/
struct ACI_MEM_TABLE_ENTRY *aciGetParameterItemByIndex(unsigned short index) {
	unsigned short i = 0;
	aciMemParamTableCurrent = aciMemParamTableStart;
	while (aciMemParamTableCurrent->next) {
		aciMemParamTableCurrent = aciMemParamTableCurrent->next;
		if (i == index)
			return (&aciMemParamTableCurrent->tableEntry);
		i++;
	}
	return NULL;
}

/** try to find a list item by id **/
struct ACI_MEM_TABLE_ENTRY *aciGetParameterItemById(unsigned short id) {
	aciMemParamTableCurrent = aciMemParamTableStart;
	while (aciMemParamTableCurrent->next) {
		aciMemParamTableCurrent = aciMemParamTableCurrent->next;
		if (aciMemParamTableCurrent->tableEntry.id == id)
			return (&aciMemParamTableCurrent->tableEntry);
	}
	return NULL;
}

/** try to find a list item by name **/
struct ACI_MEM_TABLE_ENTRY *aciGetParameterItemByName(char * name) {
	if(name==NULL) return NULL;
	aciMemParamTableCurrent = aciMemParamTableStart;
	while (aciMemParamTableCurrent->next) {
		aciMemParamTableCurrent = aciMemParamTableCurrent->next;
		if (strcmp(&(aciMemParamTableCurrent->tableEntry.name[0]), name))
			return (&aciMemParamTableCurrent->tableEntry);
	}
	return NULL;
}

/**get length of var table**/
unsigned short aciGetParamTableLenth(void) {
	unsigned short length = 0;

	aciMemParamTableCurrent = aciMemParamTableStart;
	while (aciMemParamTableCurrent->next) {
		length++;
		aciMemParamTableCurrent = aciMemParamTableCurrent->next;
	}
	return length;
}

/** get list item by index **/
struct ACI_MEM_TABLE_ENTRY *aciGetCommandItemByIndex(unsigned short index) {
	unsigned short i = 0;
	aciMemCmdTableCurrent = aciMemCmdTableStart;
	while (aciMemCmdTableCurrent->next) {
		aciMemCmdTableCurrent = aciMemCmdTableCurrent->next;
		if (i == index)
			return (&aciMemCmdTableCurrent->tableEntry);
		i++;
	}
	return NULL;
}

/** try to find a list item by id **/
struct ACI_MEM_TABLE_ENTRY *aciGetCommandItemById(unsigned short id) {
	aciMemCmdTableCurrent = aciMemCmdTableStart;
	while (aciMemCmdTableCurrent->next) {
		aciMemCmdTableCurrent = aciMemCmdTableCurrent->next;
		if (aciMemCmdTableCurrent->tableEntry.id == id)
			return (&aciMemCmdTableCurrent->tableEntry);
	}
	return NULL;
}

/** try to find a list item by name **/
struct ACI_MEM_TABLE_ENTRY *aciGetCommandItemByName(char * name) {
	if(name==NULL) return NULL;
	aciMemCmdTableCurrent = aciMemCmdTableStart;
	while (aciMemCmdTableCurrent->next) {
		aciMemCmdTableCurrent = aciMemCmdTableCurrent->next;
		if (strcmp(&(aciMemCmdTableCurrent->tableEntry.name[0]), name))
			return (&aciMemCmdTableCurrent->tableEntry);
	}
	return NULL;
}

/**get length of var table**/
unsigned short aciGetCmdTableLenth(void) {
	unsigned short length = 0;

	aciMemCmdTableCurrent = aciMemCmdTableStart;
	while (aciMemCmdTableCurrent->next) {
		length++;
		aciMemCmdTableCurrent = aciMemCmdTableCurrent->next;
	}
	return length;
}

void aciUpdateCmdPacket(const unsigned short packetId)
{
	aciCmdPacketSendStatus[packetId]=1;
}

void aciUpdateParamPacket(const unsigned short packetId)
{
	aciParamPacketSendStatus[packetId]=1;
}

unsigned char aciGetCmdSendStatus(const unsigned short packetId)
{
	return aciCmdPacketSendStatus[packetId];
}


void aciRxHandleMessage(unsigned char messagetype, unsigned short length) {
	int i;
	unsigned char packetSelect;
	unsigned char temp_ack;
	unsigned char switch_type;
	unsigned short temp_id;

	static char magicCodeAlreadyRequested = 0; // It may happen, that it will get it 2 times in a row and that is bad for loading/saving

	if((messagetype >= ACIMT_VARPACKET) && (messagetype <= ACIMT_VARPACKET + 0x0f)) switch_type = ACIMT_VARPACKET;
	else if((messagetype >= ACIMT_CMDPACKET) && (messagetype <= ACIMT_CMDPACKET + 0x0f)) switch_type = ACIMT_UPDATECMDPACKET;
	else switch_type=messagetype;

	switch (switch_type) {

	case ACIMT_INFO_REQUEST:
		aciInfo.verMajor = ACI_VER_MAJOR;
		aciInfo.verMinor = ACI_VER_MINOR;
		aciInfo.maxDescLength = MAX_DESC_LENGTH;
		aciInfo.maxNameLength = MAX_NAME_LENGTH;
		aciInfo.maxUnitLength = MAX_UNIT_LENGTH;
		aciInfo.maxVarPackets = MAX_VAR_PACKETS;
		aciInfo.flags = 0;
		for (i = 0; i < 8; i++)
			aciInfo.dummy[i] = 0;
		aciTxSendPacket(ACIMT_INFO_REPLY, &aciInfo, sizeof(aciInfo));

		break;

	case ACIMT_INFO_REPLY:
		if (length == sizeof(struct ACI_INFO)) {
			memcpy(&aciInfo,&aciRxDataBuffer[0],length);
			if(aciInfoRec) aciInfoRec(aciInfo);
		}
		break;
	case ACIMT_SENDVARTABLEINFO:
		if (length >= 2) {
			aciVarTableLength = (aciRxDataBuffer[1] << 8) | aciRxDataBuffer[0];

			if (length == aciVarTableLength * 2 + 2) {
				aciRequestedPacketList = malloc(sizeof(unsigned short)*aciVarTableLength);
				aciRequestedPacketListLength = aciVarTableLength;
				for (i = 0; i < aciVarTableLength; i++) {
					aciRequestedPacketList[i] = (aciRxDataBuffer[3 + i * 2] << 8) | aciRxDataBuffer[2 + i * 2];
				}
				//request first entry
				aciTxSendPacket(ACIMT_REQUESTVARTABLEENTRIES, aciRequestedPacketList, 2);
				aciRequestedPacketListTimeOut = ACI_REQUEST_LIST_TIMEOUT;
				aciRequestVarListTimeout=60000;
			}

		}
		break;

	case ACIMT_SENDVARTABLEENTRY:
		if ((length == (sizeof(struct ACI_MEM_TABLE_ENTRY))-sizeof(void*)) && (aciRequestedPacketListLength)) {
			unsigned short id = (aciRxDataBuffer[1] << 8) | (aciRxDataBuffer[0]);
			unsigned char idAlreadyExists = 0;

			aciMemVarTableCurrent = aciMemVarTableStart;
			while (aciMemVarTableCurrent->next) {
				aciMemVarTableCurrent = aciMemVarTableCurrent->next;
				if (aciMemVarTableCurrent->tableEntry.id == id)
					idAlreadyExists = 1;
			}

			if (!idAlreadyExists) {
				aciMemVarTableCurrent->next = malloc(sizeof(struct ACI_MEM_VAR_TABLE));
				aciMemVarTableCurrent = aciMemVarTableCurrent->next;
				memcpy(&(aciMemVarTableCurrent->tableEntry), &aciRxDataBuffer[0], sizeof(struct ACI_MEM_TABLE_ENTRY)-sizeof(void*));
				aciMagicCodeVarLoaded++;
				aciMagicCodeVar  = aciUpdateCrc16(aciMagicCodeVar,&aciMemVarTableCurrent->tableEntry.id,2);
				aciMagicCodeVar = aciUpdateCrc16(aciMagicCodeVar,&aciMemVarTableCurrent->tableEntry.varType,1);
				aciMemVarTableCurrent->next = NULL;
			}

			for (i = 0; i < aciRequestedPacketListLength; i++)
				if (aciRequestedPacketList[i] == id) {
					int z;

					for (z = i; z < aciRequestedPacketListLength - 1; z++)
						aciRequestedPacketList[z] = aciRequestedPacketList[z + 1];

					aciRequestedPacketListLength--;
					if (!aciRequestedPacketListLength) {
						free(aciRequestedPacketList);
						aciRequestListType|=0x10;
						if((aciRequestListType&0x10)&&(aciRequestListType&0x20)&&(aciRequestListType&0x40)&&(aciWriteHDC)&&(aciResetHDC)) aciStoreList();
						if (aciVarListUpdateFinished)
							aciVarListUpdateFinished();
					}
					break;
				}
			if (aciRequestedPacketListLength) {
				//request next entry
				aciTxSendPacket(ACIMT_REQUESTVARTABLEENTRIES, aciRequestedPacketList, 2);
				aciRequestedPacketListTimeOut = ACI_REQUEST_LIST_TIMEOUT;
			}
		}

		break;

	case ACIMT_SENDVARTABLEENTRYINVALID:
	case ACIMT_SENDCMDTABLEENTRYINVALID:
	case ACIMT_SENDPARAMTABLEENTRYINVALID:
		// printf("Invalid Table Entry\n");

		break;
	case ACIMT_SENDCMDTABLEINFO:
		if (length >= 2) {
			aciCmdTableLength = (aciRxDataBuffer[1] << 8) | aciRxDataBuffer[0];

			if (length == aciCmdTableLength * 2 + 2) {
				aciRequestCmdListTimeout=60000;
				if (aciRequestedCmdPacketList)
					free(aciRequestedCmdPacketList);
				aciRequestedCmdPacketList = (unsigned short*) malloc(aciCmdTableLength * 2);
				aciRequestedCmdPacketListLength = aciCmdTableLength;
				for (i = 0; i < aciCmdTableLength; i++)
					aciRequestedCmdPacketList[i] = (aciRxDataBuffer[3 + i * 2] << 8) | aciRxDataBuffer[2 + i * 2];
				//request first entry
				aciTxSendPacket(ACIMT_REQUESTCMDTABLEENTRIES, aciRequestedCmdPacketList, 2);
				aciRequestedCmdPacketListTimeOut = ACI_REQUEST_LIST_TIMEOUT;
			}
		}
		break;

	case ACIMT_SENDCMDTABLEENTRY:

		if ((length == (sizeof(struct ACI_MEM_TABLE_ENTRY))-sizeof(void*)) && (aciRequestedCmdPacketListLength)) {
			unsigned short id = (aciRxDataBuffer[1] << 8) | (aciRxDataBuffer[0]);
			unsigned char idAlreadyExists = 0;

			aciMemCmdTableCurrent = aciMemCmdTableStart;
			while (aciMemCmdTableCurrent->next) {
				aciMemCmdTableCurrent = aciMemCmdTableCurrent->next;
				if (aciMemCmdTableCurrent->tableEntry.id == id)
					idAlreadyExists = 1;
			}
			if (!idAlreadyExists) {

				aciMemCmdTableCurrent->next = malloc(sizeof(struct ACI_MEM_VAR_TABLE));
				aciMemCmdTableCurrent = aciMemCmdTableCurrent->next;
				memcpy(&(aciMemCmdTableCurrent->tableEntry), &aciRxDataBuffer[0], sizeof(struct ACI_MEM_TABLE_ENTRY)-sizeof(void*));
				aciMagicCodeCmdLoaded++;
				aciMagicCodeCmd  = aciUpdateCrc16(aciMagicCodeCmd,&aciMemCmdTableCurrent->tableEntry.id,2);
				aciMagicCodeCmd = aciUpdateCrc16(aciMagicCodeCmd,&aciMemCmdTableCurrent->tableEntry.varType,1);
				aciMemCmdTableCurrent->next = NULL;
			}

			//remove entry from requestedPacketList
			for (i = 0; i < aciRequestedCmdPacketListLength; i++)
				if (aciRequestedCmdPacketList[i] == id) {
					//remove from list
					int z;

					for (z = i; z < aciRequestedCmdPacketListLength - 1; z++)
						aciRequestedCmdPacketList[z] = aciRequestedCmdPacketList[z + 1];

					aciRequestedCmdPacketListLength--;
					if (!aciRequestedCmdPacketListLength) {
						free(aciRequestedCmdPacketList);
						aciRequestListType|=0x20;
						if((aciRequestListType&0x10)&&(aciRequestListType&0x20)&&(aciRequestListType&0x40)&&(aciWriteHDC)&&(aciResetHDC)) aciStoreList();
						if (aciCmdListUpdateFinished)
							aciCmdListUpdateFinished();
					}
					break;
				}

			if (aciRequestedCmdPacketListLength) {
				//request next entry

				aciTxSendPacket(ACIMT_REQUESTCMDTABLEENTRIES, aciRequestedCmdPacketList, 2);
				aciRequestedCmdPacketListTimeOut = ACI_REQUEST_LIST_TIMEOUT;
			}
		}

		break;

	case ACIMT_SENDPARAMTABLEINFO:
		if (length >= 2) {
			aciParamTableLength = (aciRxDataBuffer[1] << 8) | aciRxDataBuffer[0];
			if (length == aciParamTableLength * 2 + 2) {
				aciRequestParListTimeout=60000;
				aciRequestedParamPacketList = (unsigned short*)  malloc(aciParamTableLength * 2);
				aciRequestedParamPacketListLength = aciParamTableLength;
				for (i = 0; i < aciParamTableLength; i++)
					aciRequestedParamPacketList[i] = (aciRxDataBuffer[3 + i * 2] << 8) | aciRxDataBuffer[2 + i * 2];
				//request first entry
				if(aciParamTableLength==0){
					aciRequestListType|=0x40;
					if((aciRequestListType&0x10)&&(aciRequestListType&0x20)&&(aciRequestListType&0x40)&&(aciWriteHDC)&&(aciResetHDC)) aciStoreList();
					if (aciParamListUpdateFinished)
						aciParamListUpdateFinished();
				} else {
					aciTxSendPacket(ACIMT_REQUESTPARAMTABLEENTRIES, aciRequestedParamPacketList, 2);
					aciRequestedParamPacketListTimeOut = ACI_REQUEST_LIST_TIMEOUT;
				}
			}
		}
		break;

	case ACIMT_SENDPARAMTABLEENTRY:

		if ((length == ((sizeof(struct ACI_MEM_TABLE_ENTRY))-sizeof(void*))) && (aciRequestedParamPacketListLength)) {
			unsigned short id = (aciRxDataBuffer[1] << 8) | (aciRxDataBuffer[0]);
			unsigned char idAlreadyExists = 0;

			aciMemParamTableCurrent = aciMemParamTableStart;
			while (aciMemParamTableCurrent->next) {
				aciMemParamTableCurrent = aciMemParamTableCurrent->next;
				if (aciMemParamTableCurrent->tableEntry.id == id)
					idAlreadyExists = 1;
			}
			if (!idAlreadyExists) {

				aciMemParamTableCurrent->next = malloc(sizeof(struct ACI_MEM_VAR_TABLE));
				aciMemParamTableCurrent = aciMemParamTableCurrent->next;
				memcpy(&(aciMemParamTableCurrent->tableEntry), &aciRxDataBuffer[0], (sizeof(struct ACI_MEM_TABLE_ENTRY))-sizeof(void*));
				aciMagicCodeParLoaded++;
				aciMagicCodePar  = aciUpdateCrc16(aciMagicCodePar,&aciMemParamTableCurrent->tableEntry.id,2);
				aciMagicCodePar = aciUpdateCrc16(aciMagicCodePar,&aciMemParamTableCurrent->tableEntry.varType,1);
				aciMemParamTableCurrent->next = NULL;
			}

			//remove entry from requestedPacketList
			for (i = 0; i < aciRequestedParamPacketListLength; i++)
				if (aciRequestedParamPacketList[i] == id) {
					//remove from list
					int z;

					for (z = i; z < aciRequestedParamPacketListLength - 1; z++)
						aciRequestedParamPacketList[z] = aciRequestedParamPacketList[z + 1];

					aciRequestedParamPacketListLength--;
					if (!aciRequestedParamPacketListLength) {
						free(aciRequestedParamPacketList);
						aciRequestListType|=0x40;
						if((aciRequestListType&0x10)&&(aciRequestListType&0x20)&&(aciRequestListType&0x40)&&(aciWriteHDC)&&(aciResetHDC)) aciStoreList();
						if (aciParamListUpdateFinished)
							aciParamListUpdateFinished();
					}
					break;
				}

			if (aciRequestedParamPacketListLength) {
				//request next entry
				aciTxSendPacket(ACIMT_REQUESTPARAMTABLEENTRIES, aciRequestedParamPacketList, 2);
				aciRequestedParamPacketListTimeOut = ACI_REQUEST_LIST_TIMEOUT;
			}
		}

		break;

	case ACIMT_VARPACKET:
		//check magic code to see that the packet fits the desired configuration
		packetSelect = messagetype - ACIMT_VARPACKET;
		if (packetSelect >= MAX_VAR_PACKETS)
			break;
		if ((aciVarPacketMagicCode[packetSelect] == aciRxDataBuffer[0]) && (aciVarPacketContentBufferLength[packetSelect] == length - 1)) {
			//copy packet data to temporary buffer
			memcpy(aciVarPacketContentBuffer[packetSelect], &aciRxDataBuffer[1], length - 1);
			aciVarPacketContentBufferValid[packetSelect] = 1;
			aciVarPacketContentBufferInvalidCnt[packetSelect] = 0;

			if(aciVarPacketRec) aciVarPacketRec(packetSelect);

		} else {
			aciVarPacketContentBufferValid[packetSelect] = 0;
			aciVarPacketContentBufferInvalidCnt[packetSelect]++;
			if (aciVarPacketContentBufferInvalidCnt[packetSelect] == TIMEOUT_INVALID_PACKET) {
				aciVarPacketContentBufferInvalidCnt[packetSelect]--;
				aciUpdateVarPacketTimeOut[packetSelect] = 1; //trigger resend packet configuration
			}
		}
		break;

	case ACIMT_PARAM:
		temp_id = (aciRxDataBuffer[1] << 8) | aciRxDataBuffer[0];

		if(((short)(aciGetParameterItemById(temp_id)->varType>>2))==(length-2))
			memcpy(aciGetParameterItemById(temp_id)->ptrToVar,&aciRxDataBuffer[2],length-2);


		break;

	case ACIMT_PACKETRATEINFO:
		memcpy(&aciVarPacketTransmissionRate[0], &aciRxDataBuffer[0], MAX_VAR_PACKETS*2);
		break;

	case ACIMT_SAVEPARAM:
		if(length==2){
			if(aciParaStoredC) aciParaStoredC();
		}
		break;

	case ACIMT_SINGLESEND:
		if(length>4) {
		temp_id = (aciRxDataBuffer[1] << 8) | aciRxDataBuffer[0];
		if(temp_id!=0) aciTxSendPacket(ACIMT_SINGLESEND, &temp_id, 2);
		temp_id = (aciRxDataBuffer[3] << 8) | aciRxDataBuffer[2];
		temp_ack = aciRxDataBuffer[4];

		if(aciSingleReceivedC) aciSingleReceivedC(temp_id,&aciRxDataBuffer[5],temp_ack);
		}
		break;

	case ACIMT_SINGLEREQ:
		if(length>3) {
		temp_id = (aciRxDataBuffer[1] << 8) | aciRxDataBuffer[0];
		temp_ack = aciRxDataBuffer[2];

		if(aciSingleReqReceivedC) aciSingleReqReceivedC(temp_id, &aciRxDataBuffer[3],temp_ack);

		}
		break;

	case ACIMT_MAGICCODES:
		if((length==12) && (magicCodeAlreadyRequested==0)) {
			magicCodeAlreadyRequested=1;
			aciRequestMagicCodes=0;

			unsigned short tempMagicVar, tempMagicCmd, tempMagicPar;
			unsigned short tempVarCount, tempCmdCount, tempParCount;

			tempMagicVar = (aciRxDataBuffer[1] << 8) | aciRxDataBuffer[0];
			tempMagicCmd = (aciRxDataBuffer[3] << 8) | aciRxDataBuffer[2];
			tempMagicPar = (aciRxDataBuffer[5] << 8) | aciRxDataBuffer[4];

			tempVarCount = (aciRxDataBuffer[7] << 8) | aciRxDataBuffer[6];
			tempCmdCount = (aciRxDataBuffer[9] << 8) | aciRxDataBuffer[8];
			tempParCount = (aciRxDataBuffer[11] << 8) | aciRxDataBuffer[10];

			aciLoadHeaderList();

			if( (tempMagicVar==aciMagicCodeVar) && (tempMagicCmd==aciMagicCodeCmd) && (tempMagicPar==aciMagicCodePar) && (tempVarCount==aciMagicCodeVarLoaded) && (tempCmdCount==aciMagicCodeCmdLoaded) && (tempParCount==aciMagicCodeParLoaded))
			{
				aciLoadList();
				aciRequestListType=0x70;
				if(aciVarListUpdateFinished) aciVarListUpdateFinished();
				if(aciCmdListUpdateFinished)  aciCmdListUpdateFinished();
				if(aciParamListUpdateFinished) aciParamListUpdateFinished();

			} else {
				aciMagicCodeVarLoaded = 0;
				aciMagicCodeCmdLoaded = 0;
				aciMagicCodeParLoaded = 0;

				aciMagicCodeVar = 0x00FF;
				aciMagicCodeCmd = 0x00FF;
				aciMagicCodePar = 0x00FF;

				aciMagicCodeOnHDFalse=1;

				if(aciRequestListType&0x01) {
					aciRequestVarListTimeout=0;
					aciRequestListType&=~0x01;
				} else 	if(aciRequestListType&0x02) {
					aciRequestCmdListTimeout=0;
					aciRequestListType&=~0x02;
				} else 	if(aciRequestListType&0x04) {
					aciRequestParListTimeout=0;
					aciRequestListType&=~0x04;
				}
			}

		}
		break;

	case ACIMT_LOADPARAM:
		if(length==2) {
			if(aciParaLoadedC) aciParaLoadedC();
		}
		break;

	case ACI_DBG:
		if(length==1) printf("ACI DEVICE DEBUG L1: %d\n", aciRxDataBuffer[0]);
		else if(length==2){
			unsigned short temp_sh = (aciRxDataBuffer[1] << 8) | aciRxDataBuffer[0];
			printf("ACI DEVICE DEBUG L2: %d\n",temp_sh);
		}
		else if(length==4){
			int temp_int = 0;
			memcpy(&temp_int,&aciRxDataBuffer[0],4);
			printf("ACI DEVICE DEBUG L4: %d\n",temp_int);
		}
		break;

	case ACIMT_ACK:
		if ((aciRxDataBuffer[0] >= ACI_ACK_UPDATEVARPACKET) && (aciRxDataBuffer[0] <= ACI_ACK_UPDATEVARPACKET + 0x0f))
			temp_ack = ACI_ACK_UPDATEVARPACKET;
		else if ((aciRxDataBuffer[0] >= ACI_ACK_UPDATECMDPACKET) && (aciRxDataBuffer[0] <= ACI_ACK_UPDATECMDPACKET + 0x0f))
			temp_ack = ACI_ACK_UPDATECMDPACKET;
		else if ((aciRxDataBuffer[0] >= ACIMT_UPDATEPARAMPACKET) && (aciRxDataBuffer[0] <= ACIMT_UPDATEPARAMPACKET + 0x0f))
			temp_ack = ACIMT_UPDATEPARAMPACKET;
		else if ((aciRxDataBuffer[0] >= ACIMT_CMDACK) && (aciRxDataBuffer[0] <= ACIMT_CMDACK + 0x0f))
			temp_ack = ACIMT_CMDACK;
		else if ((aciRxDataBuffer[0] >= ACIMT_PARAMPACKET) && (aciRxDataBuffer[0] <= ACIMT_PARAMPACKET + 0x0f))
			temp_ack = ACIMT_PARAMPACKET;

		switch (temp_ack) {
		case ACI_ACK_UPDATEVARPACKET:
			packetSelect = aciRxDataBuffer[0] - ACI_ACK_UPDATEVARPACKET;

			if (packetSelect > MAX_VAR_PACKETS)
				break;
			if (aciRxDataBuffer[1] == ACI_ACK_OK)
				aciUpdateVarPacketTimeOut[packetSelect] = 0;
			else if (aciRxDataBuffer[1] == ACI_ACK_PACKET_TOO_LONG) {
				// Variable packet too long
				//printf("Variable packet too long\n");
			} else
				aciUpdateVarPacketTimeOut[packetSelect] = 1; //resend with next engine cycle
			break;
		case ACI_ACK_UPDATECMDPACKET:
			packetSelect = aciRxDataBuffer[0] - ACI_ACK_UPDATECMDPACKET;
			if (packetSelect > MAX_VAR_PACKETS)
				break;
			if (aciRxDataBuffer[1] == ACI_ACK_OK)
				aciUpdateCmdPacketTimeOut[packetSelect] = 0;
			else if (aciRxDataBuffer[1] == ACI_ACK_PACKET_TOO_LONG) {
				// Command packet too long
				//	printf("Command packet too long\n");
				} else
				aciUpdateCmdPacketTimeOut[packetSelect] = 1; //resend with next engine cycle
			break;

		case ACIMT_CMDACK:
			packetSelect = aciRxDataBuffer[0] - ACIMT_CMDACK;
			aciCmdPacketSendStatus[packetSelect]=0;
			if(aciCmdAck) aciCmdAck(packetSelect);
			break;



		case ACIMT_PARAMPACKET:
			packetSelect = aciRxDataBuffer[0] - ACIMT_PARAMPACKET;
			aciParamAck(packetSelect);
			break;

		case ACIMT_UPDATEPARAMPACKET:
			packetSelect = aciRxDataBuffer[0] - ACIMT_UPDATEPARAMPACKET;
			if (packetSelect > MAX_VAR_PACKETS)
				break;
			if (aciRxDataBuffer[1] == ACI_ACK_OK) {
				aciUpdateParamPacketTimeOut[packetSelect] = 0;
				aciParamPacketStatus[packetSelect] = 1;
			}
			else if (aciRxDataBuffer[1] == ACI_ACK_PACKET_TOO_LONG) {
					//printf("Parameter packet too long\n");
			} else
				aciUpdateParamPacketTimeOut[packetSelect] = 1; //resend with next engine cycle
			break;
		}
		break;
	}

}

void aciSetSingleReceivedCallback(void (*aciSingleReceived)(unsigned short id, void * data, unsigned char varType)) {
	aciSingleReceivedC=aciSingleReceived;
}

void aciSetSingleRequestReceivedCallback(void (*aciSingleReqReceived)(unsigned short id, void * data, unsigned char varType)) {
	aciSingleReqReceivedC=aciSingleReqReceived;
}

void aciSetReadHDCallback(int (*aciReadHD)(void *data, int bytes)) {
	aciReadHDC = aciReadHD;
}

void aciSetWriteHDCallback(int (*aciWriteHD)(void *data, int bytes)) {
	aciWriteHDC = aciWriteHD;
}

void aciSetResetHDCallback(void (*aciResetHD)()) {
	aciResetHDC = aciResetHD;
}

void aciRequestSingleVariable(unsigned short id) {
	if(aciRequestListType&0x10)
	aciTxSendPacket(ACIMT_SINGLEREQ, &id, 2);
}

void aciSendParamStore(){
	aciTxSendPacket(ACIMT_SAVEPARAM, NULL, 0);
}

void aciSendParamLoad(){
	aciTxSendPacket(ACIMT_LOADPARAM, NULL, 0);
}



unsigned char aciGetParamPacketStatus(unsigned short packetid)
{
	if(packetid<MAX_VAR_PACKETS)
	return aciParamPacketStatus[packetid];
	else return 0;
}


/** the aciReceiveHandler is fed by the uart rx function and decodes all neccessary packets  **/
void aciReceiveHandler(unsigned char rxByte)
{
	static unsigned char aciRxState=ARS_IDLE;
	static unsigned char aciRxMessageType;
	static unsigned short aciRxLength;
	static unsigned short aciRxCrc;
	static unsigned short aciRxReceivedCrc;


	switch (aciRxState)
	{
		case ARS_IDLE:
			if (rxByte=='!')
				aciRxState=ARS_STARTBYTE1;
		break;
		case ARS_STARTBYTE1:
			if (rxByte=='#')
				aciRxState=ARS_STARTBYTE2;
			else
				aciRxState=ARS_IDLE;

		break;
		case ARS_STARTBYTE2:
			if (rxByte=='!')
			{
                aciRxState=ARS_MESSAGETYPE;
            }
			else
				aciRxState=ARS_IDLE;

		break;
		case ARS_MESSAGETYPE:
			aciRxMessageType=rxByte;
			aciRxCrc=0xff;
			aciRxCrc=aciCrcUpdate(aciRxCrc,rxByte);
			aciRxState=ARS_LENGTH1;
		break;
		case ARS_LENGTH1:
			aciRxLength=rxByte;
			aciRxCrc=aciCrcUpdate(aciRxCrc,rxByte);
			aciRxState=ARS_LENGTH2;
		break;
		case ARS_LENGTH2:
			aciRxLength|=rxByte<<8;
			if (aciRxLength>ACI_RX_BUFFER_SIZE)
				aciRxState=ARS_IDLE;
			else
			{
			    aciRxCrc=aciCrcUpdate(aciRxCrc,rxByte);
                aciRxDataCnt=0;
			    if (aciRxLength)
				   aciRxState=ARS_DATA;
			    else
				    aciRxState=ARS_CRC1;
            }
		break;
		case ARS_DATA:
			aciRxCrc=aciCrcUpdate(aciRxCrc,rxByte);
			aciRxDataBuffer[aciRxDataCnt++]=rxByte;
			if ((aciRxDataCnt)==aciRxLength)
				aciRxState=ARS_CRC1;
		break;
		case ARS_CRC1:
			aciRxReceivedCrc=rxByte;
			aciRxState=ARS_CRC2;
		break;
		case ARS_CRC2:
			aciRxReceivedCrc|=rxByte<<8;
			if (aciRxReceivedCrc==aciRxCrc)
			{
				aciRxHandleMessage(aciRxMessageType,aciRxLength);
			}
			aciRxState=ARS_IDLE;

		break;
	}
}

void aciStoreList() {
	aciResetHDC();
	unsigned char buffer[12];

	memcpy(&buffer[0],&aciMagicCodeVar,2);
	memcpy(&buffer[2],&aciMagicCodeCmd,2);
	memcpy(&buffer[4],&aciMagicCodePar,2);

	memcpy(&buffer[6],  &aciMagicCodeVarLoaded,2);
	memcpy(&buffer[8],  &aciMagicCodeCmdLoaded,2);
	memcpy(&buffer[10], &aciMagicCodeParLoaded,2);

	aciWriteHDC(buffer,12);

	for(int i=0;i<aciMagicCodeVarLoaded;i++) {
		if(aciGetVariableItemByIndex(i)==NULL) {
			return;
		}
		aciWriteHDC(aciGetVariableItemByIndex(i),sizeof(struct ACI_MEM_TABLE_ENTRY));
	}

	for(int i=0;i<aciMagicCodeCmdLoaded;i++) {
		if(aciGetCommandItemByIndex(i)==NULL) {
			return;
		}
		aciWriteHDC(aciGetCommandItemByIndex(i),sizeof(struct ACI_MEM_TABLE_ENTRY));
	}

	for(int i=0;i<aciMagicCodeParLoaded;i++) {
		if(aciGetParameterItemByIndex(i)==NULL) {
			return;
		}
		aciWriteHDC(aciGetParameterItemByIndex(i),sizeof(struct ACI_MEM_TABLE_ENTRY));
	}

}


void aciLoadHeaderList() {

	unsigned char buffer[12];
	if(aciReadHDC(buffer,12)<=0) {
		return;
	}

	memcpy(&aciMagicCodeVar,&buffer[0],2);
	memcpy(&aciMagicCodeCmd,&buffer[2],2);
	memcpy(&aciMagicCodePar,&buffer[4],2);

	memcpy(&aciMagicCodeVarLoaded,  &buffer[6],2);
	memcpy(&aciMagicCodeCmdLoaded,  &buffer[8],2);
	memcpy(&aciMagicCodeParLoaded, &buffer[10],2);

}

void aciLoadList() {

	unsigned char buffer[sizeof(struct ACI_MEM_TABLE_ENTRY)];

	aciMemVarTableCurrent = aciMemVarTableStart;
	aciMemCmdTableCurrent = aciMemCmdTableStart;
	aciMemParamTableCurrent = aciMemParamTableStart;

	for(int i=0;i<aciMagicCodeVarLoaded;i++) {
		aciMemVarTableCurrent->next = malloc(sizeof(struct ACI_MEM_VAR_TABLE));
		aciMemVarTableCurrent = aciMemVarTableCurrent->next;
		aciReadHDC(buffer,sizeof(struct ACI_MEM_TABLE_ENTRY));
		memcpy(&(aciMemVarTableCurrent->tableEntry), &buffer[0], sizeof(struct ACI_MEM_TABLE_ENTRY));
		aciMemVarTableCurrent->next=NULL;
	}

	for(int i=0;i<aciMagicCodeCmdLoaded;i++) {
		aciMemCmdTableCurrent->next = malloc(sizeof(struct ACI_MEM_VAR_TABLE));
		aciMemCmdTableCurrent = aciMemCmdTableCurrent->next;
		aciReadHDC(buffer,sizeof(struct ACI_MEM_TABLE_ENTRY));
		memcpy(&(aciMemCmdTableCurrent->tableEntry), &buffer[0], sizeof(struct ACI_MEM_TABLE_ENTRY));
		aciMemCmdTableCurrent->next=NULL;
	}

	for(int i=0;i<aciMagicCodeParLoaded;i++) {
		aciMemParamTableCurrent->next = malloc(sizeof(struct ACI_MEM_VAR_TABLE));
		aciMemParamTableCurrent = aciMemParamTableCurrent->next;
		aciReadHDC(buffer,sizeof(struct ACI_MEM_TABLE_ENTRY));
		memcpy(&(aciMemParamTableCurrent->tableEntry), &buffer[0], sizeof(struct ACI_MEM_TABLE_ENTRY));
		aciMemParamTableCurrent->next=NULL;
	}


}

/*
 *
 * ACI Helper functions
 *
 *
 */

unsigned short aciCrcUpdate (unsigned short crc, unsigned char data)
     {
         data ^= (crc & 0xff);
         data ^= data << 4;

         return ((((unsigned short )data << 8) | ((crc>>8)&0xff)) ^ (unsigned char )(data >> 4)
                 ^ ((unsigned short )data << 3));
     }

unsigned short aciUpdateCrc16(unsigned short crc, void * data, unsigned short cnt)
{
	unsigned short crcNew=crc;
	unsigned char * chrData=(unsigned char *)data;
    int i;
    
	for (i=0;i<cnt;i++)
		crcNew=aciCrcUpdate(crcNew,chrData[i]);

	return crcNew;
}

#ifdef __cplusplus

 }
 #endif
