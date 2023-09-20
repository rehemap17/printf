#ifndef MAIN_H
#define MAIN_H

/* Includes standard libraries */
#include <stdio.h>
#include <unistd.h>
#include <stdarg.h>
#include <unistd.h>
#include <limits.h>

#define UNUSED(x) (void)(x)
#define BUFF_SIZE 1024

/* FLAGS */
#define F_MINUS 1
#define F_PLUS 2
#define F_ZERO 4
#define F_HASH 8
#define F_SPACE 16

/* SIZES */
#define S_LONG 2
#define S_SHORT 1

/**
 * struct fmt - Struct op
 *
 * @fmt: Format.
 * @fn: Function associated.
 */

struct fmt
{
	char fmt;
	int (*fn)(va_list, char[], int, int, int, int);
};

/**
 * typedef struct fmt fmt_t - Struct op
 *
 * @fmt: The format.
 * @fm_t: The function associated.
 */

typedef struct fmt fmt_t;

int _printf(const char *format, ...);
int handle_print(const char *fmt, int *ind,
va_list list, char buffer[], int flags, int wid, int precision, int size);

/* Funtions prints chars and strings */
int print_char(va_list types, char buffer[],
	int flags, int wid, int precision, int size);
int print_string(va_list types, char buffer[],
	int flags, int wid, int precision, int size);
int print_percent(va_list types, char buffer[],
	int flags, int wid, int precision, int size);

/* Functions prints numbers */
int print_int(va_list types, char buffer[],
	int flags, int wid, int precision, int size);
int print_binary(va_list types, char buffer[],
	int flags, int wid, int precision, int size);
int print_unsigned(va_list types, char buffer[],
	int flags, int wid, int precision, int size);
int print_octal(va_list types, char buffer[],
	int flags, int wid, int precision, int size);
int print_hexadecimal(va_list types, char buffer[],
	int flags, int wid, int precision, int size);
int print_hexa_upper(va_list types, char buffer[],
	int flags, int wid, int precision, int size);

int print_hexa(va_list types, char map_to[],
char buffer[], int flags, char flag_ch, int wid, int precision, int size);

/* Functions prints non printable characters */
int print_non_printable(va_list types, char buffer[],
int flags, int wid, int precision, int size);

/* Funcion prints memory address */
int print_pointer(va_list types, char buffer[],
	int flags, int wid, int precision, int size);

/* Funciotns handle's other specifiers */
int get_flags(const char *format, int *a);
int get_width(const char *format, int *d, va_list list);
int get_precision(const char *format, int *b, va_list list);
int get_size(const char *format, int *c);

/*Function prints string in reverse*/
int print_reverse(va_list types, char buffer[],
	int flags, int wid, int precision, int size);

/*Function prints a string in rot 13*/
int print_rot13string(va_list types, char buffer[],
	int flags, int wid, int precision, int size);

/* width handler's */
int handle_write_char(char c, char buffer[],
	int flags, int wid, int precision, int size);
int write_number(int is_positive, int ind, char buffer[],
	int flags, int wid, int precision, int size);
int write_num(int ind, char bff[], int flags, int wid, int precision,
	int length, char padd, char extra_c);
int write_pointer(char buffer[], int ind, int length,
	int wid, int flags, char padd, char extra_c, int padd_start);

int write_unsgnd(int is_negative, int ind,
char buffer[],
	int flags, int wid, int precision, int size);

/* UTILS */
int is_printable(char);
int append_hexa_code(char, char[], int f);
int is_digit(char);

long int convert_size_number(long int num, int size);
long int convert_size_unsgnd(unsigned long int num, int size);
void print_buffer(char buffer[], int *buff_ind);

#endif
