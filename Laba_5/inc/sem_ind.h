#ifndef __SEM_IND_H__
#define __SEM_IND_H__

//INCLUDE
#include "common.h"
//-------------------------------------------------------

//DEFINE
//-------------------------------------------------------

//FUNCTION
void init_sem_ind (); // Инициализация семисегментного индикатора
uint8_t digit (int16_t d, int8_t m); // Поиск цифры 
uint8_t null_delete (int16_t d); // Поиск значащей цифры
void sem_ind_show (int16_t number); // Вывод на семисегментный индикатор числа
//-------------------------------------------------------

#endif