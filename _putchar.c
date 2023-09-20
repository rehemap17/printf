#include "main.h"

/**
 * _putchar - prints a character.
 * @chr: character to be printed.
 * 
 * Return: 1 on success, otherwise -1.
 */

int _putchar(int chr)
{
	return (write(1, &chr, 1));
}
