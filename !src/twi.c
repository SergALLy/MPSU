# include "../inc/twi.h"

void twiStart(void)
{ // Состояние СТАРТ
    TWCR = (1<<TWINT)|(1<<TWSTA)|(1<<TWEN);
    while(!(TWCR & (1<<TWINT))); // Ждём когда TWI завершит задание
}

void twiStop(void)
{ // Состояние СТОП 
    TWCR= (1<<TWINT)|(1<<TWEN)|(1<<TWSTO);
}

void twiWrite(uint8_t data)
{ // Передача данных в матрицу
    TWDR = data;
    TWCR = (1<<TWINT)|(1<<TWEN);
    while(!(TWCR & (1<<TWINT))); // Ждём когда TWI завершит задание
}
// Передача изображения по столбцам на матрицу с МК 
void matrDrawPict(uint8_t devAddr, uint8_t *dataBuf)
 {
    uint8_t i;
    twiStart(); // Состояние СТАРТ
    twiWrite((DEV_ADDR<<1)|W); // Передача адреса и команды на запись
    for(i= 0; i<=7; i++)
    { // Очередную часть рисунка кладём в очередной регистр 
        twiWrite(COLUMN_DATA_REG+i);
        twiWrite(dataBuf[i]);
    } // Чтобы рисунок был выведен, обновляем регистр 0x0C 
    twiWrite(UPDATE_COLUMN_REG);
    twiWrite(0xFF);
    twiStop(); // Состояние СТОП
}

void init_twi(uint8_t devAddr)
{
    TWBR= 32; // 200 кГц частота обмена
// Настройки по умолчанию (матрица 8х8, без эквалайзера, 40мА тока)
}