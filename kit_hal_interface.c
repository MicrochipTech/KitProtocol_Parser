/**
 * \file
 *
 * \brief  Low-Level HAL - methods used to setup indirection to physical layer interface
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

#include "kit_hal_interface.h"

static device_info_t device_info[MAX_DISCOVER_DEVICES];
struct kit_hal_interface g_kit_hal_interface;
static const char *ext_header_string[] = {"EXT1 ", "EXT2 ", "EXT3 ", "MICROBUS"};

enum kit_protocol_status hal_iface_init(interface_id_t iface)
{
    enum kit_protocol_status status = KIT_STATUS_INVALID_PARAM;

    switch (iface)
    {
    case DEVKIT_IF_I2C:
#ifdef KIT_HAL_I2C
        g_kit_hal_interface.init = &hal_i2c_init;
        g_kit_hal_interface.deinit = &hal_i2c_deinit;
        g_kit_hal_interface.discover = &hal_i2c_discover;
        g_kit_hal_interface.wake = &hal_i2c_wake;
        g_kit_hal_interface.idle = &hal_i2c_idle;
        g_kit_hal_interface.sleep = &hal_i2c_sleep;
        g_kit_hal_interface.talk = &hal_i2c_talk;
        g_kit_hal_interface.send = &hal_i2c_send;
        g_kit_hal_interface.receive = &hal_i2c_receive;
        status = KIT_STATUS_SUCCESS;
#endif
        break;

    case DEVKIT_IF_SWI:
#ifdef KIT_HAL_SWI
        g_kit_hal_interface.init = &hal_swi_init;
        g_kit_hal_interface.deinit = &hal_swi_deinit;
        g_kit_hal_interface.discover = &hal_swi_discover;
        g_kit_hal_interface.wake = &hal_swi_wake;
        g_kit_hal_interface.idle = &hal_swi_idle;
        g_kit_hal_interface.sleep = &hal_swi_sleep;
        g_kit_hal_interface.talk = &hal_swi_talk;
        g_kit_hal_interface.send = &hal_swi_send;
        g_kit_hal_interface.receive = &hal_swi_receive;
        status = KIT_STATUS_SUCCESS;
#endif
        break;

    case DEVKIT_IF_SPI:
#ifdef KIT_HAL_SPI
        g_kit_hal_interface.init = &hal_spi_init;
        g_kit_hal_interface.deinit = &hal_spi_deinit;
        g_kit_hal_interface.discover = &hal_spi_discover;
        g_kit_hal_interface.wake = &hal_spi_wake;
        g_kit_hal_interface.idle = &hal_spi_idle;
        g_kit_hal_interface.sleep = &hal_spi_sleep;
        g_kit_hal_interface.talk = &hal_spi_talk;
        g_kit_hal_interface.send = &hal_spi_send;
        g_kit_hal_interface.receive = &hal_spi_receive;
        status = KIT_STATUS_SUCCESS;
#endif
        break;

    case DEVKIT_IF_SWI2:
#ifdef KIT_HAL_SWI2
        g_kit_hal_interface.init = &hal_gpio_init;
        g_kit_hal_interface.deinit = &hal_gpio_deinit;
        g_kit_hal_interface.discover = &hal_gpio_discover;
        g_kit_hal_interface.wake = &hal_gpio_wake;
        g_kit_hal_interface.idle = &hal_gpio_idle;
        g_kit_hal_interface.sleep = &hal_gpio_sleep;
        g_kit_hal_interface.talk = &hal_gpio_talk;
        g_kit_hal_interface.send = &hal_gpio_send;
        g_kit_hal_interface.receive = &hal_gpio_receive;
        status = KIT_STATUS_SUCCESS;
#endif
        break;

    case DEVKIT_IF_LAST:
    case DEVKIT_IF_UART:
    case DEVKIT_IF_UNKNOWN:
    default:
        break;
    }
    return status;
}

device_info_t *get_device_info(uint8_t index)
{
    device_info_t *p_dev_info = NULL;

    if (index < sizeof(device_info) / sizeof(device_info[0]))
    {
        p_dev_info = &device_info[index];
    }
    return p_dev_info;
}

interface_id_t hardware_interface_discover(void)
{
    uint8_t total_device_count = 0;
    uint8_t device_count = 0;
    const char *device_string;
    const char *header_string;

    // Adding below to avoid compilation error on UART with NO printf support
    (void)device_string;
    (void)header_string;

    memset(device_info, 0, sizeof(device_info));

#ifdef KIT_HAL_SWI
    hal_iface_init(DEVKIT_IF_SWI);
    g_kit_hal_interface.init();
    g_kit_hal_interface.discover(&device_info[total_device_count], &device_count);
    total_device_count += device_count;
    device_count = 0;
#endif

#ifdef KIT_HAL_I2C
    hal_iface_init(DEVKIT_IF_I2C);
    g_kit_hal_interface.init();
    g_kit_hal_interface.discover(&device_info[total_device_count], &device_count);
    total_device_count += device_count;
    device_count = 0;
#endif

#ifdef KIT_HAL_SPI
    hal_iface_init(DEVKIT_IF_SPI);
    g_kit_hal_interface.init();
    g_kit_hal_interface.discover(&device_info[total_device_count], &device_count);
    total_device_count += device_count;
    device_count = 0;
#endif

#ifdef KIT_HAL_SWI2
    hal_iface_init(DEVKIT_IF_SWI2);
    g_kit_hal_interface.init();
    g_kit_hal_interface.discover(&device_info[total_device_count], &device_count);
    total_device_count += device_count;
    device_count = 0;
#endif

    for (uint8_t device_index = 0; device_index < total_device_count; device_index++)
    {
        switch (device_info[device_index].bus_type)
        {
        case DEVKIT_IF_SWI:
            device_string = get_device_string(device_info[device_index].device_type);
            header_string = get_header_string(device_info[device_index].header);
            printf("\nSWI %s %s\r", device_string, header_string);
            break;

        case DEVKIT_IF_I2C:
            device_string = get_device_string(device_info[device_index].device_type);
            printf("\nI2C %s %02X\r", device_string, device_info[device_index].address);
            break;

        case DEVKIT_IF_SPI:
            device_string = get_device_string(device_info[device_index].device_type);
            header_string = get_header_string(device_info[device_index].header);
            printf("\nSPI %s %s\r", device_string, header_string);
            break;

        case DEVKIT_IF_SWI2:
            device_string = get_device_string(device_info[device_index].device_type);
            printf("\nSWI %s %02X\r", device_string, device_info[device_index].address);
            break;
        default:
            break;
        }
    }
    return device_info[0].bus_type;
}

enum kit_protocol_status select_interface(interface_id_t interface)
{
    enum kit_protocol_status status;

    g_kit_hal_interface.deinit();
    status = hal_iface_init(interface);

    return status;
}

const char *get_header_string(ext_header header)
{
    const char *ext_name = NULL;

    if (header <= EXT3_HEADER)
    {
        ext_name = ext_header_string[header];
    }
    else
    {
        ext_name = "";
    }
    return ext_name;
}