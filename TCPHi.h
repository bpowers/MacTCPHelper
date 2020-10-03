#include "TCPRoutines.h"

#ifndef _TCPLOW_
#define _TCPLOW_

/* network initialization ------------------------------------------------------*/

OSErr InitNetwork(void);		/* opens the network driver */


/* connection stream creation/removal -------------------------------------------*/

OSErr CreateStream(				/* creates a stream needed to establish a connection*/
	unsigned long *stream,			/* stream identifier (returned)					*/
	unsigned long recvLen,			/* stream buffer length to be allocated			*/
	GiveTimePtr giveTimePtr,
	bool* cancel);
	
OSErr ReleaseStream(			/* disposes of an unused stream and its buffers		*/
	unsigned long stream,			/* stream identifier to dispose					*/
	GiveTimePtr giveTimePtr,
	bool* cancel);


/* connection opening/closing calls ---------------------------------------------*/

OSErr OpenConnection(			/* attempts to establish a connection w/remote host */
	unsigned long stream,			/* stream id to be used for connection			*/
	long remoteHost,				/* network number of remote host				*/
	short remotePort,				/* network port of remote port					*/
	Byte timeout,					/* timeout value for connection					*/
	GiveTimePtr giveTimePtr,
	bool* cancel);
	
OSErr WaitForConnection(		/* listens for a remote connection from a rem. port */
	unsigned long stream,			/* stream id to be used for connection			*/
	Byte timeout,					/* timeout value for open						*/
	short localPort,				/* local port to listen on						*/
	long *remoteHost,				/* remote host connected to (returned)			*/
	short *remotePort,				/* remote port connected to (returned)			*/
	GiveTimePtr giveTimePtr,
	bool* cancel);

void AsyncWaitForConnection(	/* same as above, except executed asynchronously	*/
	unsigned long stream,			/* stream id to be used for connection			*/
	Byte timeout,					/* timeout value for open						*/
	short localPort,				/* local port to listen on						*/
	long remoteHost,				/* remote host to listen for					*/
	short remotePort,				/* remote port to listen for					*/
	TCPiopb **returnBlock,			/* parameter block for call (returned)			*/
	GiveTimePtr giveTimePtr,
	bool* cancel);

OSErr AsyncGetConnectionData(	/* retrieves connection data for above call			*/
	TCPiopb *returnBlock,			/* parameter block for asyncwait call			*/
	long *remoteHost,				/* remote host connected to (returned)			*/
	short *remotePort);				/* remote port connected to (returned)			*/

OSErr CloseConnection(			/* closes an established connection					*/
	unsigned long stream,			/* stream id of stream used for connection		*/
	GiveTimePtr giveTimePtr,
	bool* cancel);
	
OSErr AbortConnection(			/* aborts a connection non-gracefully				*/
	unsigned long stream,			/* stream id of stream used for connection		*/
	GiveTimePtr giveTimePtr,
	bool* cancel);


/* data sending calls ----------------------------------------------------------*/

OSErr SendData(					/* sends data along an open connection				*/
	unsigned long stream,			/* stream used for connection					*/
	Ptr data,						/* pointer to data to send						*/
	unsigned short length,			/* length of data to send						*/
	Boolean retry,					/* if true, call continues until send successful*/
	GiveTimePtr giveTimePtr,
	bool* cancel);
	
OSErr SendMultiData(			/* sends multiple strings of data on a connection	*/
	unsigned long stream,			/* stream used for connection					*/
	Str255 data[],					/* array of send strings						*/	
	short numData,					/* number of strings to send					*/
	Boolean retry,					/* if true, call continues until send successful*/
	GiveTimePtr giveTimePtr,
	bool* cancel);

void SendDataAsync(				/* sends data asynchronously						*/
	unsigned long stream,			/* stream used for connection					*/
	Ptr data,						/* pointer to data to send						*/
	unsigned short length,			/* length of data to send						*/
	TCPiopb **returnBlock,			/* pointer to parameter block (returned)		*/
	GiveTimePtr giveTimePtr,
	bool* cancel);
	
OSErr SendAsyncDone(			/* called when SendDataAsync call completes			*/
	TCPiopb *returnBlock);			/* parameter block to complete connection		*/


/* data receiving calls --------------------------------------------------------*/

OSErr RecvData(					/* waits for data to be received on a connection	*/
	unsigned long stream,			/* stream used for connection					*/ 
	Ptr data,						/* pointer to memory used to hold incoming data	*/
	unsigned short *length,			/* length to data received (returned)			*/
	Boolean retry,					/* if true, call continues until successful		*/
	GiveTimePtr giveTimePtr,
	bool* cancel);
	
void RecvDataAsync(				/* receives data asynchronously						*/
	unsigned long stream,			/* stream used for connection					*/
	Ptr data,						/* pointer to memory used to hold incoming data	*/
	unsigned short length,			/* length of data requested						*/
	TCPiopb **returnBlock,			/* parameter block to complete connection		*/
	GiveTimePtr giveTimePtr,
	bool* cancel);
	
OSErr GetDataLength(			/* called when RecvDataAsync completes				*/
	TCPiopb *returnBlock,			/* parameter block used for receive				*/
	unsigned short *length);		/* length of data received (returned)			*/

#endif //_TCPLOW_