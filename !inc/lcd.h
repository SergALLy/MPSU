#ifndef __LCD_H__
#define __ELCD_H__

//INCLUDE
#include "common.h"
//-------------------------------------------------------

//DEFINE
#define RS 7 // выбор регистра
#define E 6 // строб передачи
#define lenght 3 // Максимальный размер числа
#define CLEAR 0x01 // Очистить экран
#define ADDRES 1<<7 // Установка адреса DDRAM
//-------------------------------------------------------

//FUNCTION
void lcd_cmd(uint8_t cmd); // Запись кодов в регистр команд ЖКИ
void lcd_data(uint8_t data); // Вывод символа на ЖКИ
void init_lcd(void); // Инициализация ЖКИ
void lcd_number (int16_t a); // Вывод на экран трёхзначного числа
void lcd_vyvod (char *str); // Вывод на экран строки
//-------------------------------------------------------

#endif