#include "../inc/lcd.h"

uint8_t TabCon[] ={0x41,0xA0,0x42,0xA1,0xE0,0x45,0xA3,0xA4,
	0xA5,0xA6,0x4B,0xA7,0x4D,0x48,0x4F,0xA8,0x50,0x43,0x54,0xA9,
	0xAA,0x58,0xE1,0xAB,0xAC,0xE2,0xAD,0xAE,0x62,0xAF,0xB0,0xB1,
	0x61,0xB2,0xB3,0xB4,0xE3,0x65,0xB6,0xB7,0xB8,0xB9,0xBA,0xBB,
	0xBC,0xBD,0x6F,0xBE,0x70,0x63,0xBF,0x79,0x5C,0x78,0xE5,0xC0,
    0xC1,0xE6,0xC2,0xC3,0xC4,0xC5,0xC6,0xC7}; // Перекодировка для кириллицы

void LCD_cmd(uint8_t cmd) // Запись кодов в регистр команд ЖКИ
{ 
	//[]--------------------------------------------------[]
	//| Назначение: запись кодов в регистр команд ЖКИ |
	//| Входные параметры: cmd - код команды |
	//[]--------------------------------------------------[]
	DDRC = 0xFF; // Все разряды PORTC на выход
	DDRD |= ((1<<E)|(1<<RS));// Разряды PORTD на выход
	PORTD &= ~(1<<RS); // Выбор регистра команд RS=0
	PORTC = cmd; // Записать команду в порт PORTC
	PORTD |= (1<<E); // \ Сформировать на
	_delay_us(5); // | выводе E строб 1-0
	PORTD &= ~(1<<E);// / передачи команды
	_delay_ms(100); // Здержка для завершения записи
}

void LCD_data(uint8_t data) // Вывод символа на ЖКИ
 {
	//[]--------------------------------------------------[]
	//| Назначение: вывод символа на ЖКИ |
	//| Входные параметры: data - ASCII-код символа |
	//[]--------------------------------------------------[]
	DDRC = 0xFF; // Все разряды PORTC на выход
	DDRD |= ((1<<E)|(1<<RS));// Разряды PORTD на выход
	PORTD |= (1<<RS); // Выбор регистра команд RS=1
	PORTC = data; // Записать данные в порт PORTC
	PORTD |= (1<<E); // \ Сформировать на
	_delay_us(5); // | выводе E строб 1-0
	PORTD &= ~(1<<E);// / передачи команды
	_delay_ms(100); // Задержка для завершения записи
}

void LCD_init(void) // Инициализация ЖКИ
{
	//[]--------------------------------------------------[]
	//| Назначение: инициализация ЖКИ |
	//[]--------------------------------------------------[]
	DDRC = 0xFF; // Все разряды PORTC на выход
	DDRD |= ((1<<E)|(1<<RS)); // Разряды PORTD на выход
	_delay_ms (100); // Задержка для установления напряжения питания
	LCD_cmd(0x30); // \ Вывод
	LCD_cmd(0x30); // | трех
	LCD_cmd(0x30); // / команд 0x30
	LCD_cmd(0x38); // 8 разр.шина, 2 строки, 5 ? 7 точек
	LCD_cmd(0x0E); // Включить ЖКИ и курсор, без мерцания
	LCD_cmd(0x06); // Инкремент курсора, без сдвига экрана
	LCD_cmd(CLEAR); // Очистить экран, курсор в начало
}

uint8_t Code(uint8_t symb) // Перекодировка символов кириллицы
{
	//[]------------------------------------------------[]
	//| Назначение: перекодировка символов кириллицы |
	//| Входные параметры: symb – символ ASCII |
	//| Функция возвращает код отображения символа |
	//[]------------------------------------------------[]
	return (symb >= 192 ? TabCon[symb-192]: symb);
}

void LCD_number (int16_t a) // Вывод на экран трёхзначного числа
{
	//[]---------------------------------------------------[]
	//| Назначение: перевод целого трёхзначного числа в |
    //| массив типа char |
	//| a - целое десятичное число |
	//| Функция выводит на дисплей число a |
	//[]---------------------------------------------------[]
	char str[3]="";
	if (a<0) {LCD_data(45); a *= (-1);} // Проверка на отрицательное число
	int8_t i=0; // Счётчик цифр в числе a
	if (a==0) str[0]='0';
	else
	{
		while (a>0)
		{
			str[i] = a%10 +'0'; // Выделение последней цифры в числе a
			a/=10; // Отброс последней цифры
			i++;
		}
		i--;
	}
	for (;i>=0; i--) LCD_data(str[i]); // Вывод числа a
}

void LCD_vyvod (char *str) // Вывод на экран строки
{
	while (*str) {LCD_data(Code(*str)), *str++;}; // Вывести строку
}