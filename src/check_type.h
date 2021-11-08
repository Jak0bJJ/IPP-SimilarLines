
#ifndef IPP_MALE_ZADANIE_CHECK_TYPE_H
#define IPP_MALE_ZADANIE_CHECK_TYPE_H

#include <stdbool.h>

bool is_hex (const char *word);


bool is_oct (const char *word);


bool is_dec (const char *word);


// funkcja sprawdzajaca czy dane slowo bedzie klasyfikowane
// jako potencjalna liczba zmiennoprzecinkowa
bool is_dbl (const char *word);



#endif //IPP_MALE_ZADANIE_CHECK_TYPE_H
