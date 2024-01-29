#pragma once

#define SERIAL_USART_FULL_DUPLEX
#define SERIAL_USART_TX_PIN GP12
#define SERIAL_USART_RX_PIN GP13
#define SPLIT_HAND_PIN GP21

#define I2C_DRIVER I2CD1
#define OLED_UPDATE_INTERVAL 50
#define I2C1_SDA_PIN GP6
#define I2C1_SCL_PIN GP7

#ifndef OLED_FONT_H
#  define OLED_FONT_H "keyboards/crkbd/lib/glcdfont.c"
#endif
