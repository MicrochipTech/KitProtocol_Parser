/**
 * \file
 *
 * \brief  Host Interface header file
 *
 * \copyright (c) 2018 Microchip Technology Inc. and its subsidiaries.
 *            You may use this software and any derivatives exclusively with
 *            Microchip products.
 *
 * \page License
 *
 * (c) 2018 Microchip Technology Inc. and its subsidiaries. You may use this
 * software and any derivatives exclusively with Microchip products.
 *
 * THIS SOFTWARE IS SUPPLIED BY MICROCHIP "AS IS". NO WARRANTIES, WHETHER
 * EXPRESS, IMPLIED OR STATUTORY, APPLY TO THIS SOFTWARE, INCLUDING ANY IMPLIED
 * WARRANTIES OF NON-INFRINGEMENT, MERCHANTABILITY, AND FITNESS FOR A
 * PARTICULAR PURPOSE, OR ITS INTERACTION WITH MICROCHIP PRODUCTS, COMBINATION
 * WITH ANY OTHER PRODUCTS, OR USE IN ANY APPLICATION.
 *
 * IN NO EVENT WILL MICROCHIP BE LIABLE FOR ANY INDIRECT, SPECIAL, PUNITIVE,
 * INCIDENTAL OR CONSEQUENTIAL LOSS, DAMAGE, COST OR EXPENSE OF ANY KIND
 * WHATSOEVER RELATED TO THE SOFTWARE, HOWEVER CAUSED, EVEN IF MICROCHIP HAS
 * BEEN ADVISED OF THE POSSIBILITY OR THE DAMAGES ARE FORESEEABLE. TO THE
 * FULLEST EXTENT ALLOWED BY LAW, MICROCHIPS TOTAL LIABILITY ON ALL CLAIMS IN
 * ANY WAY RELATED TO THIS SOFTWARE WILL NOT EXCEED THE AMOUNT OF FEES, IF ANY,
 * THAT YOU HAVE PAID DIRECTLY TO MICROCHIP FOR THIS SOFTWARE.
 *
 * MICROCHIP PROVIDES THIS SOFTWARE CONDITIONALLY UPON YOUR ACCEPTANCE OF THESE
 * TERMS.
 */

#ifndef KIT_HOST_INTERFACE_H
#define KIT_HOST_INTERFACE_H

#include <stdint.h>

#ifdef __cplusplus
extern "C" {
#endif // __cplusplus

struct kit_host_interface
{
    void (*host_init)(void);//The function initialize the host interface
    uint8_t (*send_device_response_to_host)(uint8_t*, uint16_t);//The function send a device message response to host
};

extern struct kit_host_interface g_kit_host_interface;

/** \brief This is parent method to be called to initialize  host side interface
 *             related buffers, their lengths, hardware init, send and receive apis
 *
 *  \param[in]    None
 *
 *  \param[out]   None
 *
 *  \param[inout] None
 *
 *  \return None
 */
void host_iface_init(void);

extern uint8_t* host_msg_buffer;                 //!< The host message buffer
extern uint16_t* host_msg_buffer_length;         //!< The hot message buffer length
extern uint8_t* host_message_received;           //!< Whether the host message was received

//!< Following variable instances to be created by the application.
//!< This module links these apis to Kitprotocol parser for reference
#if defined(USB_HID_INTERFACE)
extern uint8_t g_usb_message_received;
extern uint8_t g_usb_buffer[];
extern uint16_t g_usb_buffer_length;
extern void usb_hid_init(void);
extern uint8_t usb_send_message_response(uint8_t*, uint16_t);
#elif defined(UART_INTERFACE)
extern uint8_t g_uart_message_received;
extern uint8_t g_uart_buffer[];
extern uint16_t g_uart_buffer_length;
extern void host_uart_init(void);
extern uint8_t uart_send_message_response(uint8_t*, uint16_t);
#else
#error Invalid Host, Select host configuration properly
#endif

#ifdef __cplusplus
}
#endif // __cplusplus

#endif /* KIT_HOST_INTERFACE_H */