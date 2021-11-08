

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <limits.h>
#include "basics.h"
#include "check_type.h"

//funkcja standaryzująca dane słowo, zwraca NULL jeśli słowo
//na wejściu jest od razu zestandaryzowane
char *stand_word (char *word)
{
    char* pEnd;
    char *new_word;
    if ((new_word = malloc( (12+strlen(word))*sizeof(char )))==NULL)
    {
        exit(1);
    }
    strcpy(new_word,word);
    //przypadek, gdy na wejściu otrzymujemy nieskończoność
    if (strcmp("+inf",word)==0 || strcmp("+infinity",word)==0 || strcmp("infinity",word)==0 )
    {
        strcpy(new_word, "inf");
        return new_word;
    }
    if (strcmp("-infinity",word)==0 )
    {
        strcpy(new_word, "-inf");
        return new_word;
    }
    // potencjalna liczba zmienno-przecinkowa
    if (is_dbl(new_word))
    {
        double my_number =  strtod (new_word,&pEnd);
        //sprawdzenie czy double da się zapisać przy użyciu long long'a lub uns ll
        if (my_number ==  (double)(( long long) my_number ))
        {
            unsigned long long ll = ( long long ) my_number;
            sprintf(new_word,"%lld", ll);
        }
        else if (my_number ==  (double)((unsigned long long) my_number ))
        {
            unsigned long long ll = (unsigned long long ) my_number;
            sprintf(new_word,"%llu", ll);
        }
        //w przeciwnym wypadku zwracamy liczbe w notacji naukowej
        else
        {
            sprintf(new_word,"%le",my_number);
        }
        //przypadek gdy double zwraca inf
        if (strcmp(new_word,dbl_err_p)==0 || strcmp(new_word,dbl_err_n)==0 ||
            strcmp(new_word,"inf")==0 || strcmp(new_word,"-inf")==0)
        {
            free(new_word);
            return NULL;
        }
        return new_word;
    }
    //liczby dodatnie całkowite
    else if (new_word[0]!='-')
    {
        //liczby w systemie ósemkowym
        if (is_oct(new_word))
        {
            unsigned long long ll = strtoull(new_word, &pEnd, 8);
            //przypadek z max_oct'em lub większymi liczbami
            if (ll == ULLONG_MAX)
            {
                if (strcmp(new_word, max_oct) == 0)
                {
                    sprintf(new_word, "%llu", ll);
                    return new_word;
                }
                else
                {
                    free(new_word);
                    return NULL;
                }
            }
            sprintf(new_word, "%llu", ll);
            return new_word;
        }
        //liczby w systemie szesnastkowym
        else if (is_hex(new_word))
        {
            unsigned long long ll = strtoull(new_word, &pEnd, 16);
            //przypadek z max_hex'em lub większymi liczbami
            if (ll == ULLONG_MAX)
            {
                if (strcmp(new_word, max_hex) == 0)
                {
                    sprintf(new_word, "%llu", ll);
                    return new_word;
                }
                else
                {
                    free(new_word);
                    return NULL;
                }
            }
            sprintf(new_word, "%llu", ll);
            return new_word;
        }
        //liczby dziesiętne dodatnie
        else if (is_dec(new_word))
        {
            unsigned long long ll = strtoull(new_word, &pEnd, 10);
            //przypadek z max_uns_ll lub wiekszymi liczbami
            if (ll == ULLONG_MAX)
            {
                if (strcmp(new_word, max_int_str) == 0)
                {
                    sprintf(new_word, "%llu", ll);
                    return new_word;
                }
                else
                {
                    free(new_word);
                    return NULL;
                }
            }
            sprintf(new_word, "%llu", ll);
            return new_word;
        }
    }
    //liczby dziesiętne ujemne
    else if (is_dec(new_word))
    {
        long long ll = strtoll(new_word, &pEnd, 10);
        //przypadek z min_ll lub mniejszymi liczbami
        if (ll==LLONG_MIN)
        {
            if (strcmp(new_word,max_neg_int) == 0)
            {
                sprintf(new_word, "%lld", ll);
                return new_word;
            }
            else
            {
                free(new_word);
                return NULL;
            }
        }
        sprintf(new_word, "%lld", ll);
        return new_word;
    }
    //przypadek gdy słowo na wejściu jest nieliczbą
    else
    {
        free(new_word);
        return NULL;
    }
    free(new_word);
    return NULL;

}

//funkcja standaryzująca daną linijkę
char *stand_line (char *line)
{
    char** t = (char **) malloc(sizeof (char *));
    const char c[] = {'\31', '\0'};
    int size=0, cap=1;
    char *word = NULL;
    char separators[] = " \t\v\f\r";
    word = strtok(line,separators);
    //rozbicie linii na słowa
    while( word != NULL )
    {
        if (size+1>=cap)
        {
            cap*=2;
            if ((t = realloc(t, sizeof(char *) * cap))==NULL)
            {
                exit(1);
            }
        }
        char* new_word = stand_word(word);
        //przypadek gdy słowo z wejścia jest już zestandaryzowane
        if (new_word==NULL)
        {
            if ((t[size]=malloc(strlen(word)+1))==NULL)
            {
                exit(1);
            }
            strcpy(t[size],word);
        }
        else
        {
            t[size] = new_word;
        }
        size++;
        word = strtok(NULL, separators);
    }
    qsort(t, size, sizeof(char *), strng_cmp);
    // w tym miejscu używam calloca zamiast malloc, gdyż malloc powodował
    // niezliczoną ilość trudnych do wyjaśnienia błędów, podczas gdy
    // z jakiegoś powodu przy callocu wszystko działa
    char* new_line ;
    if ((new_line = calloc((3+strlen(t[0]))*sizeof(char ), 'a'))==NULL)
    {
        exit(1);
    }
    strcpy(new_line,t[0]);
    strcat(new_line,c);
    //doklejanie kolejnych słów w określonym porządku do
    //zestandaryzowanej linii, słowa odzielone są nielegalnym
    //znakiem przechowywanym w zmiennej c
    for (int i=1;i<size;++i)
    {
        if ((new_line=(char *)realloc(new_line, (strlen(new_line)+strlen(t[i])+4)*sizeof (char)))==NULL)
        {
            exit(1);
        }
        strcat(new_line,t[i]);
        strcat(new_line,c);
    }
    //zwalnianie pamięci
    for (int i=0;i<size;++i)
    {
        free(t[i]);
    }
    free(t);
    return new_line;
}