
#include <stdbool.h>
#include "basics.h"

// funkcja sprawdzajaca czy dane slowo bedzie klasyfikowane
// jako potencjalna liczba całkowita w systemie szesnastkowym
bool is_hex (const char *word)
{
    int i=0;
    if (word[i]!='0'||word[i+1]!='x')
    {
        return false;
    }
    i+=2;
    while (word[i]!='\0')
    {
        if ( !( (word[i] >= '0' && word[i] <= '9') || (word[i]>='a' && word[i]<='f') ) )
        {
            return false;
        }
        ++i;
    }
    return true;
}
// funkcja sprawdzajaca czy dane slowo bedzie klasyfikowane
// jako potencjalna liczba całkowita w systemie ósemkowym
bool is_oct (const char *word)
{
    int i=0;
    if (word[i]!='0')
    {
        return false;
    }
    while (word[i]!='\0')
    {
        if (word[i] < '0' || word[i] > '7')
        {
            return false;
        }
        ++i;
    }
    return true;
}
// funkcja sprawdzajaca czy dane slowo bedzie klasyfikowane
// jako potencjalna liczba całkowita w systemie dziesiętnym
bool is_dec (const char *word)
{
    int i=0;
    int size=0;
    if (word[0]=='+'||word[0]=='-')
    {
        ++i;
    }
    while (word[i]!='\0')
    {
        size++;
        if (word[i] < '0' || word[i] > '9')
        {
            return false;
        }
        ++i;
    }
    if (size==0)
        return false;
    return true;
}
// funkcja sprawdzajaca czy dane slowo bedzie klasyfikowane
// jako potencjalna liczba zmiennoprzecinkowa
bool is_dbl (const char *word)
{
    unsigned long long i = 1, size = 0, counter = 0;
    bool was_dot=0, was_e=0, was_int=0;
    if (word[0]!='+'&&word[0]!='-' && word[0]!='.' && (word[0]<'0' || word[0]>'9'))
    {
        return false;
    }
    if (word[0]=='.')
    {
        was_dot=1;
    }
    else if (word[0]!='-' && word[0]!='0' && word[0]!='+')
    {
        size++;
        was_int=1;
    }
    if (word[0]=='0')
    {
        was_int=1;
    }
    while (size<8&&word[i]!='\0')
    {

        if (word[i]=='.')
        {
            if (was_dot||was_e)
                return false;
            else
            {
                was_dot = 1;
                size += counter;
                counter = 0;
            }
        }
        else if (word[i]=='e')
        {
            if (was_e || was_int==0)
                return false;
            else
            {
                if (word[i+1]=='+'||word[i+1]=='-')
                {
                    ++i;
                }
                was_int=0;
                was_e=1;
                size=0;
                counter=0;
            }
        }
        else if (word[i]=='0')
        {
            was_int=1;
            if (size!=0)
                counter++;
        }
        else if (word[i]>'0' && word[i]<='9')
        {
            was_int=1;
            size++;
            size+=counter;
            counter=0;
        }
        else
        {
            return false;
        }
        ++i;
    }
    if (size==0&&was_int==0)
        return false;
    if (was_e && was_int==0)
        return false;
    if (!was_e && !was_dot)
        return false;
    if (size>8&&!was_e)
        return false;

    return true;
}