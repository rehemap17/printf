#include "main.h"

/**
  * print_unsnd - Prints an unsigned number
  * @typ: List arguments
  * @buffer: Buffer array
  * @flg: active flags
  * @wid: get width
  * @p: Specifies Precision
  * @size:specifies Size
  * 
  * Return: Number of chars
  */

int print_unsnd(va_list typ, char buffer[],
	int flg, int wid, int p, int size)
{
	int e = BUFFER_SIZE - 2;
	unsigned long int num = va_arg(typ, unsigned long int);

	num = conv_size_unsnd(num, size);

	if (num == 0)
		buffer[e--] = '0';

	buffer[BUFFER_SIZE - 1] = '\0';

	while (num > 0)
	{
		buffer[e--] = (num % 10) + '0';
		num /= 10;
	}

	e++;

	return (write_unsnd(0, e, buffer, flg, wid, p, size));
}

/**
 * print_oct - Prints an unsigned number in octal notation
 * @typ: List arguments
 * @buffer: Buffer array
 * @flg: active flags
 * @wid: get width
 * @p: Precision specification
 * @size: Size specifier
 * 
 * Return: Number of chars printed
 */

int print_oct(va_list typ, char buffer[],
	int flg, int wid, int p, int size)
{

	int e = BUFFER_SIZE - 2;
	unsigned long int num = va_arg(typ, unsigned long int);
	unsigned long int init_num = num;

	UNUSED(wid);

	num = conv_size_unsnd(num, size);

	if (num == 0)
		buffer[e--] = '0';

	buffer[BUFFER_SIZE - 1] = '\0';

	while (num > 0)
	{
		buffer[e--] = (num % 8) + '0';
		num /= 8;
	}

	if (flg & F_HASH && init_num != 0)
		buffer[e--] = '0';

	e++;

	return (write_unsnd(0, e, buffer, flg, wid, p, size));
}

/**
 * print_hexadc - Prints an unsigned number in hexadecimal notation
 * @typ: List arguments
 * @buffer: Buffer array
 * @flg: active flags
 * @wid: width
 * @p: Specifies Precision
 * @size: specifies Size
 * 
 * Return: Number of chars printed
 */

int print_hexadc(va_list typ, char buffer[],
	int flg, int wid, int p, int size)
{
	return (print_hexa(typ, "0123456789abcdef", buffer,
		flg, 'X', wid, p, size));
}

/**
 * print_hexa_up - Prints an unsigned number in upper hexadecimal notation
 * @typ: List arguments
 * @buffer: Buffer array
 * @flg: active flags
 * @wid: width
 * @p: Specifies Precision
 * @size: specifies Size
 * 
 * Return: Number of chars printed
 */

int print_hexa_up(va_list typ, char buffer[],
	int flg, int wid, int p, int size)
{
	return (print_hexa(typ, "0123456789ABCDEF", buffer,
		flg, 'X', wid, p, size));
}

/**
 * print_hexa - Prints b hexadecimal number in lower or upper
 * @typ: List arguments
 * @map_t: Array of values to map to
 * @buffer: Buffer array
 * @flg: active flags
 * @flg_c: Calculates active flags
 * @wid: width
 * @p: specifies Precision
 * @size: Specifies size
 * @size: Size specification
 * 
 * Return: Number of chars printed
 */

int print_hexa(va_list typ, char map_t[],
		char buffer[], int flg, char flg_c, int wid, int p, int size)
{
	int b = BUFFER_SIZE - 2;
	unsigned long int num = va_arg(typ, unsigned long int);
	unsigned long int init_num = num;

	UNUSED(wid);

	num = conv_size_unsnd(num, size);

	if (num == 0)
		buffer[b--] = '0';

	buffer[BUFFER_SIZE - 1] = '\0';

	while (num > 0)
	{
		buffer[b--] = map_t[num % 16];
		num /= 16;
	}

	if (flg & F_HASH && init_num != 0)
	{
		buffer[b--] = flg_c;
		buffer[b--] = '0';
	}

	b++;

	return (write_unsnd(0, b, buffer, flg, wid, p, size));
}
