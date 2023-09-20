#include "main.h"

/**
* print_char - shows character
* @typ: lists arguments
* @buffer: buffer array
* @flg: active flags
* @wid: width
* @p: specifies precision
* @size: specifies size

* Return: number of charaters displayed
*/

int print_char(va_list typ, char buffer[],
int flg, int wid, int p, int size)
{
char c = va_arg(typ, int);

return (write_char(c, buffer, flg, wid, p, size));
}

/**
* print_str - shows a string
* @typ: lists arguments
* @buffer: buffer array
* @flg: active flags
* @wid: width
* @p: specifies precision
* @size: specifies size
*
* Return: number of characters displayed
*/

int print_str(va_list typ, char buffer[],
int flg, int wid, int p, int size)
{
int len = 0, l;
char *st = va_arg(typ, char *);

UNUSED(buffer);
UNUSED(flg);
UNUSED(wid);
UNUSED(p);
UNUSED(size);
if (st == NULL)
{
st = "(null)";
if (p > 7)
st = "      ";
}
while (st[len] != '\0')
len++;
if (p >= 0 && p < len)
len = p;
if (wid > len)
{
if (flg & F_MINUS)
{
write(1, &st[0], len);
for (l = wid - len; l > 0; l--)
write(1, " ", 1);
return (wid);
}
else
{
	for (l = wid - len; l > 0; l--)
		write(1, " ", 1);
	write(1, &st[0], len);
	return (wid);
}
}
return (write(1, st, len));
}

/**
* print_per - prints percent sign
* @typ: lists arguments
* @buffer: buffer array
* @flg: active flags
* @wid: width
* @p: specifies precision
* @size: specifies size
*
* Return: number of characters displayed
*/

int print_per(va_list typ, char buffer[],
int flg, int wid, int p, int size)
{
	UNUSED(typ);
	UNUSED(buffer);
	UNUSED(flg);
	UNUSED(wid);
	UNUSED(p);
	UNUSED(size);
	return (write(1, "%%", 1));
}

/**
  * print_int - Prints integers
  * @typ: List of arguments
  * @buffer: buffer array
  * @flg: active flags
  * @wid: width
  * @p: specifies precision
  * @size: Specifies size
  * 
  * Return: number of characters displayed
  */

int print_int(va_list typ, char buffer[],
		int flg, int wid, int p, int size)
{
int l = BUFFER_SIZE - 2;
int is_neg = 0;
long int n = va_arg(typ, long int);
unsigned long int num;

n = conv_size_num(n, size);

if (n == 0)
buffer[l--] = '0';

buffer[BUFFER_SIZE - 1] = '\0';
num = (unsigned long int)n;

if (n < 0)
{
num = (unsigned long int)((-1) * n);
is_neg = 1;
}

while (num > 0)
{
buffer[l--] = (num % 10) + '0';
num /= 10;
}
l++;
return (write_num(is_neg, l, buffer, flg, wid, p, size));
}

/**
* print_bin - Prints unsigned number
* @typ: lists arguments
* @buffer: buffer array
* @flg: active flags
* @wid: width
* @p: specifies precision
* @size: specifies size
*
* Return: number of characters displayed
*/

int print_bin(va_list typ, char buffer[], int flg, int wid, int p, int size)
{
    unsigned int g, h;
    int i[32]; 
    int count = 0; 

    UNUSED(buffer);
    UNUSED(flg);
    UNUSED(wid);
    UNUSED(p);
    UNUSED(size);

    g = va_arg(typ, unsigned int);
    h = 2147483648;

    i[0] = g / h;

    for (int j = 1; j < 32; j++) 
    {
        h /= 2;
        i[j] = (g & h) ? 1 : 0; 
    }

    for (int k = 0; k < 32; k++)
    {
        count += i[k];

        if (count || k == 31)
        {
            char m = '0' + i[k];

            write(1, &m, 1);
        }
    }

    return count;
}
