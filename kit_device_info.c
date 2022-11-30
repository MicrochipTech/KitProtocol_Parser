/**
 * \file
 *
 * \brief  CryptoAuth Device utility files
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

#include "kit_device_info.h"
#include <stdint.h>
#include <stddef.h>

//!
/*The 3rd and 4th byte are the actual device revision.
    Index 2 is the actual device code.
    Index 3 is the silicon revision.
 */
#define DEVICE_IDENTIFIER_LOCATION  1
#define DEVICE_PART_LOCATION        2
#define DEVICE_REVISION_LOCATION    3

const device_details ecc_sha_rng[] = 
{
    {DEVICE_TYPE_ECC204,       ECC204_DEVICE_ID,      ECC_REV_NUM},
    {DEVICE_TYPE_ECC206,       ECC206_DEVICE_ID,      ECC_REV_NUM},
    {DEVICE_TYPE_TA010,        TA010_DEVICE_ID,       ECC_REV_NUM},  
    {DEVICE_TYPE_RNG90,        RNG90_DEVICE_ID,       SHA_REV_NUM},  
    {DEVICE_TYPE_SHA104,       SHA104_DEVICE_ID,      SHA_REV_NUM},
    {DEVICE_TYPE_SHA105,       SHA105_DEVICE_ID,      SHA_REV_NUM},
    {DEVICE_TYPE_SHA106,       SHA106_DEVICE_ID,      SHA_REV_NUM},
};

const opcode_cmd_string_t ca_device_opcode_cmd_string[] =
{
    {ATCA_AES, aes_string},
    {ATCA_CHECKMAC, checkmac_string},
    {ATCA_COUNTER, counter_string},
    {ATCA_DERIVE_KEY, derivekey_string},
    {ATCA_ECDH, ecdh_string},
    {ATCA_GENDIG, gendig_string},
    {ATCA_GENKEY, genkey_string},
    {ATCA_INFO, info_string},
    {ATCA_KDF, kdf_string},
    {ATCA_LOCK, lock_string},
    {ATCA_MAC, mac_string},
    {ATCA_NONCE, nonce_string},
    {ATCA_PRIVWRITE, priv_write_string},
    {ATCA_RANDOM, random_string},
    {ATCA_READ, read_string},
    {ATCA_SECUREBOOT, secure_boot_string},
    {ATCA_SELFTEST, selftest_string},
    {ATCA_SIGN, sign_string},
    {ATCA_SHA, sha_string},
    {ATCA_UPDATE_EXTRA, update_extra_string},
    {ATCA_VERIFY, verify_string},
    {ATCA_WRITE, write_string},
};

const opcode_cmd_string_t ta_device_opcode_cmd_string[] =
{
    {ATCA_TA_AES, aes_string},
    {ATCA_TA_AUTHORIZE, authorize_string},
    {ATCA_TA_COUNTER, counter_string},
    {ATCA_TA_CREATE, create_string},
    {ATCA_TA_DELETE, delete_string},
    {ATCA_TA_DEVUPDATE, devupdate_string},
    {ATCA_TA_ECDH, ecdh_string},
    {ATCA_TA_EXPORT, export_string},
    {ATCA_TA_FCCONFIG, fcconfig_string},
    {ATCA_TA_IMPORT, import_string},
    {ATCA_TA_INFO, info_string},
    {ATCA_TA_KDF, kdf_string},
    {ATCA_TA_KEYGEN, genkey_string},
    {ATCA_TA_LOCK, lock_string},
    {ATCA_TA_MAC, mac_string},
    {ATCA_TA_MANAGECERT, managecert_string},
    {ATCA_TA_POWER, power_string},
    {ATCA_TA_RANDOM, random_string},
    {ATCA_TA_READ, read_string},
    {ATCA_TA_RSAENC, rsaenc_string},
    {ATCA_TA_SECUREBOOT, secure_boot_string},
    {ATCA_TA_SELFTEST, selftest_string},
    {ATCA_TA_SEQUENCE, sequence_string},
    {ATCA_TA_SHA, sha_string},
    {ATCA_TA_SIGN, sign_string},
    {ATCA_TA_VERIFY, verify_string},
    {ATCA_TA_WRITE, write_string},
};

const device_cmd_string_t device_cmd_string_info[] =
{
    {DEVICE_TYPE_SHA204, sha204_string},
    {DEVICE_TYPE_SHA204A, sha204a_string},
    {DEVICE_TYPE_AES132, aes132_string},
    {DEVICE_TYPE_AES132A, aes132a_string},
    {DEVICE_TYPE_ECC108, ecc108_string},
    {DEVICE_TYPE_ECC108A, ecc108a_string},
    {DEVICE_TYPE_ECC508A, ecc508a_string},
    {DEVICE_TYPE_ECC608A, ecc608a_string},
    {DEVICE_TYPE_ECC608B, ecc608b_string},
    {DEVICE_TYPE_SHA206A, sha206a_string},
    {DEVICE_TYPE_TA100, ta100_string},
    {DEVICE_TYPE_ECC204, ecc204_string},
    {DEVICE_TYPE_TA010, ta010_string},
    {DEVICE_TYPE_ECC206, ecc206_string},
    {DEVICE_TYPE_RNG90, rng90_string},
    {DEVICE_TYPE_SHA104, sha104_string},
    {DEVICE_TYPE_SHA105, sha105_string},
    {DEVICE_TYPE_SHA106, sha106_string},
};

const char* get_command_string(device_type_t device, uint8_t opcode)
{
    const char* cmd_string = NULL;
    uint8_t opcode_index;
    const opcode_cmd_string_t* opcode_cmd_string;
    uint8_t opcode_count;

    if ((device < DEVICE_TYPE_SHA204) || (device == DEVICE_TYPE_AES132) || (device == DEVICE_TYPE_AES132A))
    {
        opcode_cmd_string=NULL;
        opcode_count=0;
    }
    else if (device == DEVICE_TYPE_TA100)
    {
        opcode_cmd_string = ta_device_opcode_cmd_string;
        opcode_count = sizeof(ta_device_opcode_cmd_string)/sizeof(ta_device_opcode_cmd_string[0]);
    }
    else
    {
        opcode_cmd_string = ca_device_opcode_cmd_string;
        opcode_count = sizeof(ca_device_opcode_cmd_string)/sizeof(ca_device_opcode_cmd_string[0]);
    }

    for(opcode_index = 0; opcode_index < opcode_count; opcode_index++)
    {
        if (opcode_cmd_string[opcode_index].opcode == opcode)
        {
            cmd_string = opcode_cmd_string[opcode_index].cmd_string;
            break;
        }
    }

    return cmd_string;
}

const char* get_device_string(device_type_t device)
{
    const char* device_string = NULL;
    uint8_t dev_index;

    for(dev_index=0; dev_index<sizeof(device_cmd_string_info)/sizeof(device_cmd_string_info[0]); dev_index++)
    {
        if (device_cmd_string_info[dev_index].device == device)
        {
            device_string = device_cmd_string_info[dev_index].device_string;
            break;
        }
    }

    return device_string;
}
device_type_t sha_ecc_device_type(const uint8_t* dev_rev)
{
    device_type_t device;

    switch (dev_rev[DEVICE_PART_LOCATION])
    {
    case 0x00:
        device = DEVICE_TYPE_SHA204;
        if ((dev_rev[DEVICE_REVISION_LOCATION] >= 0x07 && dev_rev[DEVICE_REVISION_LOCATION] <= 0x09))
        {
            device = DEVICE_TYPE_SHA204A;
        }
        break;

    case 0x10:
        device = DEVICE_TYPE_ECC108;
        if (dev_rev[DEVICE_REVISION_LOCATION] >= 0x02 && dev_rev[DEVICE_REVISION_LOCATION] <= 0x06)
        {
            device = DEVICE_TYPE_ECC108A;
        }
        break;

    case 0x50:
        device = DEVICE_TYPE_ECC508A;
        break;

    case 0x60:
        device = DEVICE_TYPE_ECC608A;
        if (dev_rev[DEVICE_REVISION_LOCATION] > 0x02)
        {
            device = DEVICE_TYPE_ECC608B;
        }
        break;

    case 0x40:
        device = DEVICE_TYPE_SHA206A;
        break;

    case 0x20:
        device = get_device_type(dev_rev[DEVICE_REVISION_LOCATION], dev_rev[DEVICE_IDENTIFIER_LOCATION]);
        break;

    default:
        device = DEVICE_TYPE_UNKNOWN;
        break;
    }

    return device;
}

device_type_t get_device_type(const uint8_t dev_rev, const uint8_t dev_id)
{
    uint8_t i = 0;
    uint8_t device = DEVICE_TYPE_UNKNOWN;
    size_t max_device_count = sizeof(ecc_sha_rng) / sizeof(ecc_sha_rng[0]);
            
    if (dev_rev == 0x00)
    {
        device = DEVICE_TYPE_ECC204;
    }
    else
    {
        for (i = 0; i < max_device_count; i++)
        {            
            if (ecc_sha_rng[i].device_identifier == dev_id &&              \
                    ecc_sha_rng[i].product_family_and_revision == dev_rev)
            {
                device = ecc_sha_rng[i].device_type;
                break;
            }
        }
    }
    
    return device;
}

uint8_t get_eccx08_response_size(uint8_t *command)
{
    // Get the Opcode and Param1
    uint8_t op_code = command[ECC108_OPCODE_IDX];
    uint8_t param1 = command[ECC108_PARAM1_IDX];
    uint8_t response_size;

    // Return the expected response size
    switch (op_code)
    {
    case ECC108_CHECKMAC:
        response_size = CHECKMAC_RSP_SIZE;
        break;

    case ECC108_DERIVE_KEY:
        response_size = DERIVE_KEY_RSP_SIZE;
        break;

    case ECC108_INFO:
        response_size = INFO_RSP_SIZE;
        break;

    case ECC108_GENDIG:
        response_size = GENDIG_RSP_SIZE;
        break;

    case ECC108_GENKEY:
        response_size = (param1 & GENKEY_MODE_DIGEST)
                        ? ECC108_RSP_SIZE_MIN : GENKEY_RSP_SIZE_LONG;
        break;

    case ECC108_HMAC:
        response_size = HMAC_RSP_SIZE;
        break;

    case ECC108_LOCK:
        response_size = LOCK_RSP_SIZE;
        break;

    case ECC108_MAC:
        response_size = MAC_RSP_SIZE;
        break;

    case ECC108_NONCE:
        response_size = ((param1 & NONCE_MODE_MASK) == NONCE_MODE_PASSTHROUGH
                         ? NONCE_RSP_SIZE_SHORT : NONCE_RSP_SIZE_LONG);
        break;

    case ECC108_PAUSE:
        response_size = PAUSE_RSP_SIZE;
        break;

    case ECC108_PRIVWRITE:
        response_size = PRIVWRITE_RSP_SIZE;
        break;

    case ECC108_RANDOM:
        response_size = RANDOM_RSP_SIZE;
        break;

    case ECC108_READ:
        response_size = (param1 & ECC108_ZONE_COUNT_FLAG
                         ? READ_32_RSP_SIZE : READ_4_RSP_SIZE);
        break;

    case ECC108_SIGN:
        response_size = SIGN_RSP_SIZE;
        break;


    case ECC108_UPDATE_EXTRA:
        response_size = UPDATE_RSP_SIZE;
        break;

    case ECC108_VERIFY:
        response_size = ECC108_RSP_SIZE_MAX;
        break;

    case ECC108_WRITE:
        response_size = WRITE_RSP_SIZE;
        break;

    default:
        // Return the max size and execution time for commands
        // that might be missing in the cases above.
        response_size = 110;
        break;
    }
    return response_size;
}

uint16_t get_ecc204_opcode_execution_delay(uint8_t opcode)
{
    switch (opcode)
    {
    case ECC204_COUNTER:
        return ECC204_COUNTER_EXEC_DELAY;
        break;
    case ECC204_DELETE:
        return ECC204_DELETE_EXEC_DELAY;
        break;
    case ECC204_GENKEY:
        return ECC204_GENKEY_EXEC_DELAY;
        break;
    case ECC204_INFO:
        return ECC204_INFO_EXEC_DELAY;
        break;
    case ECC204_LOCK:
        return ECC204_LOCK_EXEC_DELAY;
        break;
    case ECC204_NONCE:
        return ECC204_NONCE_EXEC_DELAY;
        break;
    case ECC204_READ:
        return ECC204_READ_EXEC_DELAY;
        break;
    case ECC204_SELFTEST:
        return ECC204_SELFTEST_EXEC_DELAY;
        break;
    case ECC204_SHA:
        return ECC204_SHA_EXEC_DELAY;
        break;
    case ECC204_SIGN:
        return ECC204_SIGN_EXEC_DELAY;
        break;
    case ECC204_WRITE:
        return ECC204_WRITE_EXEC_DELAY;
        break;
    default:
        return ECC204_DEFAULT_EXEC_DELAY;
        break;
    }
}

bool check_idle_support(device_type_t device_type)
{
    switch (device_type)
    {
        case DEVICE_TYPE_ECC204:
            /* fall-through */
        case DEVICE_TYPE_TA010:
            /* fall-through */
        case DEVICE_TYPE_SHA104:
            /* fall-through */
        case DEVICE_TYPE_SHA105:
            /* fall-through */
        case DEVICE_TYPE_SHA106:
            /* fall-through */
        case DEVICE_TYPE_RNG90:
            /* fall-through */
        case DEVICE_TYPE_ECC206:
            return false;
            break;
        default:
            return true;
            break;
    }
}
