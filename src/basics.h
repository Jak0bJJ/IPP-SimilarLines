
#ifndef IPP_MALE_ZADANIE_BACISC_H
#define IPP_MALE_ZADANIE_BACISC_H

#include <stdbool.h>

//stałe wartości zapisane jako stringi
char max_neg_int[20];
char max_int_str[20];
char max_hex[18];
char max_oct[23];
char dbl_err_p[13];
char dbl_err_n[14];

//struktura do trzymania indeksów linii
struct str
{
    int ind;
    char* word;
};

//funkcja porownujaca dwa struct'y typu str
int strct_cmp(const void *a, const void *b);


//funkcja porownujaca dwa string'i
int strng_cmp(const void *a, const void *b);


//funkcja sprawdzająca czy dany znak jest na white listcie
bool check_char (int ch);

//funkcja wczytująca linie i dokonujaca pierwszych zmian w niej
char* get_line (int line_num, int *x);

#endif //IPP_MALE_ZADANIE_BACISC_H
