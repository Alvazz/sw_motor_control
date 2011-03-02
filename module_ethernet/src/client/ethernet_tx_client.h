/**
 * Module:  module_ethernet
 * Version: 1v4
 * Build:   d3c5347cdae4e3489ef0484a98cf3e6824343bb6
 * File:    ethernet_tx_client.h
 *
 * The copyrights, all other intellectual and industrial 
 * property rights are retained by XMOS and/or its licensors. 
 * Terms and conditions covering the use of this code can
 * be found in the Xmos End User License Agreement.
 *
 * Copyright XMOS Ltd 2010
 *
 * In the case where this code is a modification of existing code
 * under a separate license, the separate license terms are shown
 * below. The modifications to the code are still covered by the 
 * copyright notice above.
 *
 **/                                   
/*************************************************************************
 *
 * Ethernet MAC Layer Implementation
 * IEEE 802.3 MAC Client Interface (Send)
 *
 *
 *
 * This implement Ethernet frame sending client interface.
 *
 *************************************************************************/

#ifndef _ETHERNET_TX_CLIENT_H_
#define _ETHERNET_TX_CLIENT_H_ 1
#include <xccompat.h>

#define ETH_BROADCAST (-1)

/** Sends an ethernet frame. Frame includes dest/src MAC address(s), type
 *  and payload.
 *
 *
 *  \param c_mac     channel end to tx server.
 *  \param buffer[]  byte array containing the ethernet frame. *This must
 *                   be word aligned*
 *  \param nbytes    number of bytes in buffer
 *  \param ifnum     the number of the eth interface to transmit to 
 *                   (use ETH_BROADCAST transmits to all ports)
 *
 */
void mac_tx(chanend c_mac, unsigned int buffer[], int nbytes, int ifnum);

#define ethernet_send_frame mac_tx
#define ethernet_send_frame_getTime mac_tx_timed


/** Sends an ethernet frame. Frame includes dest/src MAC address(s), type
 *  and payload.
 *
 *
 *  \param c_mac     channel end to tx server.
 *  \param buffer[]  byte array containing the ethernet frame. *This must
 *                   be word aligned*
 *  \param nbytes    number of bytes in buffer
 *  \param ifnum     the number of the eth interface to transmit to 
 *                   (use ETH_BROADCAST transmits to all ports)
 *
 */
void mac_tx_offset2(chanend c_mac, unsigned int buffer[], int nbytes, int ifnum);

#define ethernet_send_frame_offset2 mac_tx_offset2

/** Sends an ethernet frame and gets the timestamp of the send. 
 *  Frame includes dest/src MAC address(s), type
 *  and payload.
 *
 *  This is a blocking call and returns the *actual time* the frame
 *  is sent to PHY according to the XCore 100Mhz 32-bit timer on the core
 *  the ethernet server is running.
 *
 *  \param c_mac     channel end connected to ethernet server.
 *  \param buffer[]  byte array containing the ethernet frame. *This must
 *                   be word aligned*
 *  \param nbytes    number of bytes in buffer
 *  \param ifnum     the number of the eth interface to transmit to 
 *                   (use ETH_BROADCAST transmits to all ports)
 *  \param time      A reference paramater that is set to the time the
 *                   packet is sent to the phy
 *
 *  NOTE: This function will block until the packet is sent to PHY.
 */
#ifdef __XC__ 
void mac_tx_timed(chanend c_mac, unsigned int buffer[], int nbytes, unsigned int &time, int ifnum);
#else
void mac_tx_timed(chanend c_mac, unsigned int buffer[], int nbytes, unsigned int *time, int ifnum);
#endif

/** Get the device MAC address.
 *
 *  This function gets the MAC address of the device (the address passed
 *  into the ethernet_server() function.
 *
 *  \param   c_mac chanend end connected to ethernet server
 *  \param   macaddr[] an array of type char where the MAC address is placed 
 *                     (in network order).
 *  \return zero on success and non-zero on failure.
 */

int mac_get_macaddr(chanend c_mac, unsigned char macaddr[]);

#define ethernet_get_my_mac_adrs mac_get_macaddr


/** This function sets the transmit 
 *  bandwidth restriction on a link to the mac server.
 *
 *  \param   c_mac chanend connected to ethernet server
 *  \param   bandwidth The allowed bandwidth of the link in Mbps
 *
 */
int mac_set_bandwidth(chanend c_mac, unsigned int bandwidth);

#define ethernet_set_bandwidth mac_set_bandwidth

#endif
