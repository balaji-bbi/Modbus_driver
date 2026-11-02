/**
 * @file mb_crc.h
 * @author Balaji (Git -> balaji-bbi)
 * @brief 
 * @version 0.1
 * @date 2026-11-02
 * 
 * @copyright Copyright (c) 2026
 * 
 */

 #ifndef MB_CRC_H
 #define MB_CRC_H

 #include "stdint.h"
 #include "stddef.h"
 #include "stdbool.h"

 uint16_t mb_crc_compute(const uint8_t* buf, size_t len);
 bool mb_crc_validate(const uint8_t* frame, size_t len);
 size_t mb_crc_append(uint8_t *buf, size_t len);
 
 #endif