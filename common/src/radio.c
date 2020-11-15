/*******************************************************************************
 * Includes
 ******************************************************************************/
#include "xbee/wpan.h"
#include "radio.h"
#include <string.h>

/*******************************************************************************
 * Declarations
 ******************************************************************************/
int _xbee_handle_receive( xbee_dev_t *xbee, const void FAR *raw,
   uint16_t length, void FAR *context);

/*******************************************************************************
 * Definitions
 ******************************************************************************/


#define XBEE_FRAME_HANDLE_RX  \
   { XBEE_FRAME_RECEIVE, 0, _xbee_handle_receive, NULL }

const xbee_dispatch_table_entry_t xbee_frame_handlers[] =
{
    XBEE_FRAME_HANDLE_LOCAL_AT,
    XBEE_FRAME_MODEM_STATUS_DEBUG,
    XBEE_FRAME_HANDLE_RX, 
    XBEE_FRAME_TABLE_END
};

static int receive_packet_length;
static uint8_t receive_packet[256];

/*******************************************************************************
 * Implementations
 ******************************************************************************/

int _xbee_handle_receive( xbee_dev_t *xbee, const void FAR *raw,
        uint16_t length, void FAR *context){

    // this XBee frame handler (standard API) doesn't use the context parameter
    XBEE_UNUSED_PARAMETER( context);

    const xbee_frame_receive_t FAR *frame = raw;
    
    memcpy(receive_packet, &frame->payload, length);
    receive_packet_length = length - 
            offsetof( xbee_frame_receive_t, payload);
    return 0;
}

int radioReceive(xbee_dev_t * radio, uint8_t * packet){
    if(xbee_dev_tick(radio)){
        memcpy(packet, receive_packet, receive_packet_length);
        return receive_packet_length;
    }
    return 0;
}

void radioTxRequest(xbee_dev_t * radio, const uint8_t * buffer, 
            unsigned int length){
    
    xbee_header_transmit_t header;

	header.frame_id = xbee_next_frame_id(radio);
	header.frame_type = 0x10;

    /* Address of radio to send to. Right now set to the one labelled "Station" 
     * Note: being set bit by bit because of endianness issues */
    static addr64 addr;
    addr.b[0] = 0x00;
    addr.b[1] = 0x13;
    addr.b[2] = 0xA2;
    addr.b[3] = 0x0;
    addr.b[4] = 0x41;
    addr.b[5] = 0x67;
    addr.b[6] = 0x8F;
    addr.b[7] = 0xC0;
	header.ieee_address = addr;
	/* Note: there are some weird endianness issues, so this is actually
	 * transmitted as 0xFFFE. Not sure exactly what's up here, but as long as
	 * we assign the bytes manually for the 64 bit addresses above it should
	 * be fine */
	header.network_address_be = 0xFEFF;
	header.broadcast_radius = 0;
	/* Use no transmit options */
	header.options = 0;

    xbee_frame_write(radio, &header, sizeof(header), buffer, length, 
            XBEE_WRITE_FLAG_NONE);
}