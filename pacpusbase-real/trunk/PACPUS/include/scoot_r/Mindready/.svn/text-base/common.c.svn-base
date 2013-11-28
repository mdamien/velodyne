/*******************************************************************************
*
*	PROJECT:	Common library for HLA examples
*
*	FILE:		common.c
*
*	CONTENT:	Contains many differents function that could be used in the
*               HLA examples.
*
*
*	COPYRIGTH:	2001, Mindready Solutions Inc, All rights reserved.
*
*/

#include <sdnet2.h>
#include "stdio.h"
#include "common.h"
#include "Windows.h"




/*******************************************************************************
*
* BecomeTheRoot - Try to get the root using the "set force root" flag.
*
* INPUT:	hDevice:  ptr to a sednet device
*           maxRetry: Maximum retry to get the root
*
* RETURNS:	None
*			
*/
int BecomeTheRoot(SDNET2_HANDLE *hDevice, UINT32 maxRetry)
{
	SDNET2_STATUS	 status;
	SDNET2_NODEID    nodeID;
	SDNET2_PHYCONFIG phyConfPk;
	SDNET2_PHYSTAT   phyStatus;


	status = sdNET2_IOControl(hDevice, SDNET2_IOC_GET_NODE_ID, &nodeID);
	if (status != SD_SUCCESS)
	{
		printf("ERROR: SDNET2_IOC_GET_NODE_ID failed\n");
		printf("ERROR: ERRNO = 0x%X meaning %s\n", ERRNO, sdNet2Error(ERRNO));
		return -1;
	}

	status = sdNET2_IOControl(hDevice, 
							  SDNET2_IOC_GET_GENERATION_COUNT, 
							  &phyConfPk.generationCount);
	if (status != SD_SUCCESS)
	{
		printf("ERROR: SDNET2_IOC_GET_GENERATION_COUNT failed\n");
		printf("ERROR: ERRNO = 0x%X meaning %s\n", ERRNO, sdNet2Error(ERRNO));
		return -1;
	}

	phyConfPk.gapCount    = 0;
	phyConfPk.setGapCount = 0;
	phyConfPk.forceRoot = 1;
	phyConfPk.phyId     = nodeID.nodeNumber;
	status = sdNET2_SendPacket(hDevice,
							   (SDNET2_PACKET) &phyConfPk,
							   NULL,                          /* confirmation */
							   NULL,                          /* callback     */
							   NULL,                          /* user context */
							   SDNET2_PHY_CONFIG);
	if (status != SD_SUCCESS)
	{
		printf("ERROR: sdNET2_SendPacket (phyConfig) failed\n");
		printf("ERROR: ERRNO = 0x%X meaning %s\n", ERRNO, sdNet2Error(ERRNO));
		return -1;
	}



	status = sdNET2_IOControl(hDevice, SDNET2_IOC_RESET_BUS, NULL);
	if (status != SD_SUCCESS)
	{
		printf("ERROR: SDNET2_IOC_RESET_BUS failed\n");
		printf("ERROR: ERRNO = 0x%X meaning %s\n", ERRNO, sdNet2Error(ERRNO));
		return -1;
	}

	/* Wait until the bus reset has completed */
	Sleep(10);



	/* Clear the force root flag for next bus reset */
	status = sdNET2_IOControl(hDevice, SDNET2_IOC_CLEAR_FORCE_ROOT, NULL);
	if (status != SD_SUCCESS)
	{
		printf("ERROR: SDNET2_IOC_CLEAR_FORCE_ROOT failed\n");
		printf("ERROR: ERRNO = 0x%X meaning %s\n", ERRNO, sdNet2Error(ERRNO));
		return -1;
	}



	/*
	** Check if we are the root using the present status registry
	*/
	status = sdNET2_IOControl (hDevice,
				    		   SDNET2_IOC_PRESENT_STATUS,
						       &phyStatus);
	if(status != SD_SUCCESS) 
	{
		printf("ERROR: SDNET2_IOC_PRESENT_STATUS failed\n");
		printf("ERROR: ERRNO = 0x%X meaning %s\n", ERRNO, sdNet2Error(ERRNO));
		return -1;
	}

	/* Check if we are the bus root now */
	if ( ! phyStatus.busRoot )
	{
		return -1;
	}

	return 0;
}





/*******************************************************************************
*
* BecomeTheRoot - Try to get the root using the "set force root" flag.
*
* INPUT:	hDevice:  ptr to a sednet device
*           maxRetry: Maximum retry to get the root
*
* RETURNS:	None
*			
*/
int BecomeTheRoot_Alternative(SDNET2_HANDLE *hDevice, UINT32 maxRetry)
{

	SDNET2_PHYSTAT phyStatus;
	SDNET2_STATUS  status;
	UINT32         retryNbr = maxRetry;
	UINT8          sdNET2Err=0;

	if (maxRetry < 1)
	{
		printf("ERROR: BecomeTheRoot(X): X should be at least 1\n");
		return -1;
	}
	while (retryNbr > 0)
	{
		retryNbr--;

		/*
		** Set the force root hardware flag.
		*/
		status = sdNET2_IOControl(hDevice, SDNET2_IOC_SET_FORCE_ROOT, NULL);
		if(status != SD_SUCCESS) 
		{
			if (ERRNO == SDERR_NODE_ALONE_ON_BUS)
			{
				/* Node alone on the bus --> already the root */
				/* But do a bus reset...*/
				status = sdNET2_IOControl(hDevice, SDNET2_IOC_RESET_BUS, NULL);
				if(status != SD_SUCCESS) 
				{
					printf("ERROR: SDNET2_IOC_SET_FORCE_ROOT failed\n");
					printf("ERROR: ERRNO = 0x%X meaning %s\n", ERRNO, sdNet2Error(ERRNO));
					return -1;
				}
				printf("I am alone on the bus so I am the root\n");
				return 0;
			}


			printf("ERROR: SDNET2_IOC_SET_FORCE_ROOT failed\n");
			printf("ERROR: ERRNO = 0x%X meaning %s\n", ERRNO, sdNet2Error(ERRNO));
			sdNET2Err=1;
			break;
		}


		/*
		** Do a Bus reset in order to get the root.
		*/
		status = sdNET2_IOControl(hDevice, SDNET2_IOC_RESET_BUS, NULL);
		if(status != SD_SUCCESS) 
		{
			printf("ERROR: SDNET2_IOC_SET_FORCE_ROOT failed\n");
			printf("ERROR: ERRNO = 0x%X meaning %s\n", ERRNO, sdNet2Error(ERRNO));
			sdNET2Err=1;
			break;
		}

		/* Let enough time to the bus reset to complete */
		Sleep(10);


		/*
		** Check if we are the root using the present status registry
		*/
		status = sdNET2_IOControl (hDevice,
				    		       SDNET2_IOC_PRESENT_STATUS,
						           &phyStatus);
		if(status != SD_SUCCESS) 
		{
			printf("ERROR: SDNET2_IOC_PRESENT_STATUS failed\n");
			printf("ERROR: ERRNO = 0x%X meaning %s\n", ERRNO, sdNet2Error(ERRNO));
			sdNET2Err=1;
			break;
		}

		/* If we are the root, we exit the retry loop */
		if (phyStatus.busRoot)
		{
			break;
		}

	}

	
	
	/*
	** Do not forget to clean the force root bit!  Otherwise on next bus reset
	** there could be conflict with other nodes...
	*/
	status = sdNET2_IOControl(hDevice, SDNET2_IOC_CLEAR_FORCE_ROOT, NULL);
	if(status != SD_SUCCESS) 
	{
			printf("ERROR: SDNET2_IOC_SET_FORCE_ROOT failed\n");
			printf("ERROR: ERRNO = 0x%X meaning %s\n", ERRNO, sdNet2Error(ERRNO));
			sdNET2Err=1;
	}



	if ( phyStatus.busRoot == 0 ||
		 sdNET2Err         == 1)
	{
		return -1;
	}
	else
	{
		return 0;
	}
}



/*******************************************************************************
*
* PrintError - Prints the SedNet2 error code.  The error code is available via
*              the ERRNO variable.  The function directly prints the error on 
*              the screen.
*
* RETURNS:	None
*			
*/
void PrintError(int error)
{

	printf ("error = 0x%X --> %s\n", error, sdNet2Error(error));

}


/*******************************************************************************
*
* PrintError - Prints the SedNet2 error code.  The error code is available via
*              the ERRNO variable.  The function returns the error as a string.
*              the screen.
*
* RETURNS:	String description of the SedNet2 error.
*			
*/
char* sdNet2Error(int error)
{
	static char strErr[128];


	switch(error)
	{

		// General Error code
		case SDERR_HW_ACCESS_FAILED:   sprintf( strErr, "SDERR_HW_ACCESS_FAILED");  break;
		case SDERR_NOT_ISR_CALLABLE:   sprintf( strErr, "SDERR_NOT_ISR_CALLABLE");  break;
		case SDERR_NOT_SUPPORTED_BY_HW: sprintf( strErr, "SDERR_NOT_SUPPORTED_BY_HW"); break;
		case SDERR_NODE_ALONE_ON_BUS:  sprintf( strErr, "SDERR_NODE_ALONE_ON_BUS"); break;
		case SDERR_SYS_UNAVAILABLE:    sprintf( strErr, "SDERR_SYS_UNAVAILABLE");   break;
		case SDERR_INVALID_GEN_COUNT:  sprintf( strErr, "SDERR_INVALID_GEN_COUNT"); break;
		case SDERR_INVALID_CHAN_LIST:  sprintf( strErr, "SDERR_INVALID_CHAN_LIST"); break;
		case SDERR_NOT_BUS_ROOT:       sprintf( strErr, "SDERR_NOT_BUS_ROOT");   break;
		case SDERR_INVALID_ADDR:       sprintf( strErr, "SDERR_INVALID_ADDR");   break;
		case SDERR_UNSUPPORTED:        sprintf( strErr, "SDERR_UNSUPPORTED");    break;
		case SDERR_INVALID_HANDLE:     sprintf( strErr, "SDERR_INVALID_HANDLE"); break;
		case SDERR_INVALID_CMD:        sprintf( strErr, "SDERR_INVALID_CMD");    break;
		case SDERR_INVALID_PACKET:     sprintf( strErr, "SDERR_INVALID_PACKET"); break;
		case SDERR_TOO_MUCH_CBACK:     sprintf( strErr, "SDERR_TOO_MUCH_CBACK"); break;
		case SDERR_INVALID_DESC:       sprintf( strErr, "SDERR_INVALID_DESC");   break;
		case SDERR_COMM_DISABLED:      sprintf( strErr, "SDERR_COMM_DISABLED");  break;
		case SDERR_INVALID_PARAM:      sprintf( strErr, "SDERR_INVALID_PARAM");  break;
		case SDERR_BUFFER_EMPTY:       sprintf( strErr, "SDERR_BUFFER_EMPTY");   break;
		case SDERR_CHAN_UNAVAILABLE:   sprintf( strErr, "SDERR_CHAN_UNAVAILABLE");   break;
		case SDERR_MULTI_CHAN_UNAVAIL: sprintf( strErr, "SDERR_MULTI_CHAN_UNAVAIL"); break;
		case SDERR_CTX_UNAVAILABLE:    sprintf( strErr, "SDERR_CTX_UNAVAILABLE");    break;
		case SDERR_INVALID_ADP_INDEX:  sprintf( strErr, "SDERR_INVALID_ADP_INDEX");  break;
		case SDERR_DEV_UNAVAILABLE:    sprintf( strErr, "SDERR_DEV_UNAVAILABLE");    break;



		// HLA error code range rom 0x2001 to 0x2FFF
		case SDERR_INVALID_NODE_NB:         sprintf( strErr, "SDERR_INVALID_NODE_NB"); break;
		case SDERR_INVALID_BUS_NB:          sprintf( strErr, "SDERR_INVALID_BUS_NB");  break;
		case SDERR_INVALID_TLABEL:          sprintf( strErr, "SDERR_INVALID_TLABEL");  break;
		case SDERR_INVALID_OFFLOW:          sprintf( strErr, "SDERR_INVALID_OFFLOW");  break;
		case SDERR_INVALID_RCODE:           sprintf( strErr, "SDERR_INVALID_RCODE");   break;
		case SDERR_INVALID_DATALEN:         sprintf( strErr, "SDERR_INVALID_DATALEN"); break;
		case SDERR_INVALID_XTCODE:          sprintf( strErr, "SDERR_INVALID_XTCODE");  break;
		case SDERR_INVALID_TCODE:           sprintf( strErr, "SDERR_INVALID_TCODE");   break;
		case SDERR_INVALID_CHANNEL:         sprintf( strErr, "SDERR_INVALID_CHANNEL"); break;
		case SDERR_INVALID_TAG:             sprintf( strErr, "SDERR_INVALID_TAG");     break;
		case SDERR_INVALID_SPEED:           sprintf( strErr, "SDERR_INVALID_SPEED");   break;
		case SDERR_OUT_OF_MEMORY:           sprintf( strErr, "SDERR_OUT_OF_MEMORY");   break;
		case SDERR_DRIVER_FAILED:           sprintf( strErr, "SDERR_DRIVER_FAILED");   break;
		case SDERR_CANT_OPEN_DEV:           sprintf( strErr, "SDERR_CANT_OPEN_DEV");   break;
		case SDERR_INVALID_GAP_COUNT:       sprintf( strErr, "SDERR_INVALID_GAP_COUNT");  break;
		case SDERR_INVALID_RESP_CODE:       sprintf( strErr, "SDERR_INVALID_RESP_CODE");  break;
		case SDERR_INVALID_PRIORITY:        sprintf( strErr, "SDERR_INVALID_PRIORITY");   break;
		case SDERR_INVALID_DATA_PTR:        sprintf( strErr, "SDERR_INVALID_DATA_PTR");   break;
		case SDERR_INVALID_ARGUMENT:        sprintf( strErr, "SDERR_INVALID_ARGUMENT");   break;
		case SDERR_INVALID_PHY_ID:          sprintf( strErr, "SDERR_INVALID_PHY_ID");     break;
		case SDERR_INVALID_FORCE_ROOT:      sprintf( strErr, "SDERR_INVALID_FORCE_ROOT"); break;
		case SDERR_INVALID_SYNCHRO:         sprintf( strErr, "SDERR_INVALID_SYNCHRO");    break;
		case SDERR_INVALID_SET_GAP_COUNT:   sprintf( strErr, "SDERR_INVALID_SET_GAP_COUNT");   break;
		case SDERR_CBACK_PENDING:           sprintf( strErr, "SDERR_CBACK_PENDING");           break;
		case SDERR_INVALID_FLAGS:           sprintf( strErr, "SDERR_INVALID_FLAGS");           break;
		case SDERR_NO_RX_ISO_CHANNEL_FOUND: sprintf( strErr, "SDERR_NO_RX_ISO_CHANNEL_FOUND"); break;
		case SDERR_NO_RX_ISO_AVAILABLE:     sprintf( strErr, "SDERR_NO_RX_ISO_AVAILABLE");     break;
		case SDERR_INVALID_DEV_NAME:        sprintf( strErr, "SDERR_INVALID_DEV_NAME");        break;

		default:      sprintf( strErr, "UNKNOWN ERROR!!!");
	}

	return strErr;
}
