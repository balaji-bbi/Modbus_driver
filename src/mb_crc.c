/**
 * @file mb_crc.c
 * @author Balaji (Git -> balaji-bbi)
 * @brief
 * @version 0.1
 * @date 2026-11-02
 *
 * @copyright Copyright (c) 2026
 *
 */

#include "mb_crc.h"

/**
 * @brief Calculates CRC
 * @param buf Pointer to the byte array (Slave addr + PDU)
 * @param len Size of the bytes to be processed
 * @return uint16_t CRC value for MODBUS
 */
uint16_t mb_crc_compute(const uint8_t *buf, size_t len)
{
    uint16_t crc = 0xFFFF; // Loads Initial Value

    for (size_t i = 0; i < len; i++)
    {
        crc ^= buf[i]; // XOR byte into LSB of CRC
        for (uint8_t j = 0; j < 8; j++)
        {
            crc = (crc & 1) ? (crc >> 1) ^ 0xA001 : (crc >> 1);
            // Shift right and XOR polynomial or Just shift right
        }
    }

    return crc;
}

/**
 * @brief Calculate crc for the frame and checks with the received CRC
 * 
 * @param frame Pointer to the frame start
 * @param len Total length of the frame including crc
 * @return true if calculated CRC and received CRC matches
 * @return false if calculated CRC and received CRC not matches
 */
bool mb_crc_validate(const uint8_t *frame, size_t len)
{

    if ((frame == NULL) || (len <= 4U))
        return false;

    uint16_t crc = mb_crc16_compute(frame, len - 2);

    if ((frame[len - 2] == (uint8_t)crc) && (frame[len - 1] == (crc >> 8)))
        return true;
    else
        return false;
}

/**
 * @brief Appends CRC to the data frame at the end in the order of CRC_LOW, CRC_HIGH
 * 
 * @param buf Pointer to the byte data buffer (Slave addr + PDU)
 * @param len Size of the data
 * @return size_t total size of the frame (ADU - Slave addr + PDU + CRC)
 */
size_t mb_crc_append(uint8_t *buf, size_t len)
{

    if ((buf == NULL) || (len <= 4U))
        return 0;

    uint16_t crc = mb_crc_evaluate(buf, len);

    buf[len] = crc & 0xFF;
    buf[len + 1] = (crc >> 8) & 0xFF;

    return len + 2;
}