#ifndef __LCD_H__
#define __ELCD_H__

//INCLUDE
#include "common.h"
//-------------------------------------------------------

//DEFINE
#define RS 7 // выбор регистра
#define E 6 // строб передачи
#define CLEAR 0x01 // Очистить экран
#define ADDRES 0x40 // Установка адреса DDRAM
//-------------------------------------------------------

//FUNCTION
void LCD_cmd(uint8_t cmd); // Запись кодов в регистр команд ЖКИ
void LCD_init(void); // Инициализация ЖКИ
void int_to_char (int8_t a); // Вывод на экран трёхзначного числа
void vyvod (char *str); // Вывод на экран строки
//-------------------------------------------------------

#endif