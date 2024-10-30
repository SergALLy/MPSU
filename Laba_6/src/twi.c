# include "../inc/twi.h"

void twiStart(void)
{ // состояние СТАРТ
    TWCR = (1<<TWINT)|(1<<TWSTA)|(1<<TWEN);
    while(!(TWCR & (1<<TWINT)));
}

void twiStop(void)
{ // состояние СТОП 
    TWCR= (1<<TWINT)|(1<<TWEN)|(1<<TWSTO);
}

void twiWrite(uint8_t data)
{ // передача данных в матрицу
    TWDR = data;
    TWCR = (1<<TWINT)|(1<<TWEN);
    while(!(TWCR & (1<<TWINT)));
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
        twiWrite(dataBuf[i]);
    } // чтобы рисунок был выведен, обновляем регистр 0x0C 
    twiWrite(UPDATE_COLUMN_REG);
    twiWrite(0xFF);
    twiStop();
}

void init_twi(uint8_t devAddr)
{
    TWBR= 32; //200 кГц частота обмена
    /* настройки по умолчанию (матрица 8х8, без эквалайзера, 40мА тока)
     нам подходят, поэтому ничего не меняем и не перенастраиваем */
}