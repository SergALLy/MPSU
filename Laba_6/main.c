include "inc/common.h"

#define DEV_ADDR 0b1100000 // адрес модуля по умолчанию 
#define W 0 // признак записи данных в матрицу
#define R 1 // признак чтения данных из матрицы 

#define COLUMN_DATA_REG 0x01 // регистр состояния диодов столбца 
#define UPDATE_COLUMN_REG 0x0C // регистр обновления состояния диодов столбца

void twiStart();
void twiStop();
void twiWrite(uint8_tdata);
void matrDrawPict(uint8_tdevAddr, uint8_t *dataBuf);
void matrInit(uint8_tdevAddr);

int main(void)
{
    uint8_t pict[] = {0b00111100, 0b01000010, 0b10011001, 0b10100001, 0b10100001, 0b10011001, 0b01000010, 0b00111100};//рисунок–значок копирайта © 
    matrInit(DEV_ADDR);
    matrDrawPict(DEV_ADDR, pict);
    while (1);
}

void twiStart(void)
{ // состояние СТАРТ
    TWCR = (1<<TWINT)|(1<<TWSTA)|(1<<TWEN);
    while(!(TWCR & (1<<TWINT)));
}
void twiStop(void)
{ // состояние СТОП 
    TWCR= (1<<TWINT)|(1<<TWEN)|(1<<TWSTO);
}
void twiWrite(uint8_tdata)
{ // передача данных в матрицу
    TWDR = data;
    TWCR = (1<<TWINT)|(1<<TWEN);
    while(!(TWCR& (1<<TWINT)));
}
//передача изображения по столбцам на матрицу с МК 
void matrDrawPict(uint8_t devAddr, uint8_t *dataBuf)
 {
    uint8_t i;
    twiStart();
    twiWrite((DEV_ADDR<<1)|W);
    for(i= 0; i<=7; i++)
    { // очередную часть рисунка кладём в очередной регистр 
    twiWrite(COLUMN_DATA_REG+i);
    twiWrite(dataBuf[i]);} // чтобы рисунок был выведен, обновляем регистр 0x0C 
    twiWrite(UPDATE_COLUMN_REG);
    twiWrite(0xFF);
    twiStop();
}
void matrInit(uint8_t devAddr)
{
    TWBR= 32; //200 кГц частота обмена
    /* настройки по умолчанию (матрица 8х8, без эквалайзера, 40мА тока)
     нам подходят, поэтому ничего не меняем и не перенастраиваем */
}