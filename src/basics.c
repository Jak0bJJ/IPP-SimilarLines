
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include <ctype.h>

//trochę stałych
char max_neg_int[]="-9223372036854775808";
char max_int_str[]="18446744073709551615";
char max_hex[]="0xffffffffffffffff";
char max_oct[]="01777777777777777777777";
char dbl_err_p[]="1.#INF00e+000";
char dbl_err_n[]="-1.#INF00e+000";


struct str
{
    int ind;
    char* word;
};

//funkcja porownujaca dwa struct'y typu str
int strct_cmp(const void *a, const void *b)
{
    const struct str *ia = (const struct str *)a;
    const struct str *ib = (const struct str *)b;
    if (strcmp(ia->word, ib->word)==0)
    {
        if( ia->ind < ib->ind)
            return -1;
        else
            return 1;
    }
    else
    {
        return strcmp(ia->word, ib->word);
    }
}

//funkcja porownujaca dwa string'i
int strng_cmp(const void *a, const void *b)
{
    const char **ia = (const char **)a;
    const char **ib = (const char **)b;
    return strcmp(*ia, *ib);

}

//funkcja sprawdzająca czy dany znak jest na white list'cie
bool check_char (int ch)
{
    if (ch>=9&&ch<=13)
        return 1;
    if (ch>=32&&ch<=126)
        return 1;
    return 0;
}

//funkcja wczytująca linie i dokonujaca pierwszych zmian na niej
char* get_line (int line_num, int *fin)
{
    int ch;
    bool corr_line = true, comment = false, empty_line=1;
    char* line = malloc(sizeof (char));
    int size = 0;
    int cap = 1;
    while (((ch = getchar()) != '\n') && (ch != EOF))
    {
        //jeśli linia jest komentarzem
        if (size==0 && ch=='#')
        {
            comment=true;
        }
        //sprawdzamy czy linia posiada nie-pusty znak
        if (33<= ch && ch<=126)
        {
            empty_line=0;
        }
        //zwiększamy przydział pamięci
        if (size+1>=cap)
        {
            cap*=2;
            if( (line = realloc(line, cap)) == NULL )
            {
                exit(1);
            }
        }
        //zmieniamy NULL char na innego nielegalnego chara
        if (ch=='\0')
        {
            ch='\1';
        }
        //jeśli linia posiada błedny char oznaczmy ją jako błędną
        if (check_char(ch) == false)
        {
            corr_line = false;
        }
        line[size] = (char) tolower(ch);
        size++;
    }
    if (ch==EOF)
    {
        *fin = 1;
    }
    if (comment)
    {
        free(line);
        return NULL;
    }
    else if (corr_line == false)
    {
        fprintf (stderr, "ERROR %i\n",line_num);
        free(line);
        return NULL;
    }
    else if (empty_line)
    {
        free(line);
        return NULL;
    }
    line[size] = '\0';
    return line;
}