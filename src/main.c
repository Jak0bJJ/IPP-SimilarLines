//Jakub Jakubowski

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include "basics.h"
#include "check_type.h"
#include "stand.h"


int main() {
    struct str* t = malloc(sizeof (struct str));
    int line_num=1, size=0, cap=1;
    char *line = NULL;
    struct str a;
    int end=0;
    while (!end)
    {
        line = get_line(line_num,&end);
        if (size+1>=cap)
        {
            cap*=2;
            if ((t = realloc(t, sizeof(struct str) * cap)) == NULL)
            {
                exit(1);
            }
        }
        if (line != NULL)
        {
            a.ind=line_num;
            a.word=stand_line(line);
            t[size]=a;
            ++size;
        }
        line_num++;
        free(line);
    }
    qsort(t, size, sizeof(struct str), strct_cmp);
    //porządkowanie otrzymanych danych
    int next[line_num];
    int vis[line_num];
    for (int i=1;i<=line_num;++i)
    {
        next[i]=-2;
        vis[i]=0;
    }
    for (int i=0;i<size;++i)
    {
        if (i==0)
        {
            next[t[i].ind]=-1;
        }
        else if (strcmp(t[i].word,t[i-1].word)==0)
        {
            next[t[i-1].ind]=t[i].ind;
            next[t[i].ind]=-1;
        }
        else
        {
            next[t[i].ind]=-1;
        }
    }
    //zwalnianie pamięci cd.
    for (int i=0;i<size;++i)
    {
        free(t[i].word);
    }
    free(t);
    bool is_not_first=0;
    int j=-1;
    int i=1;
    while (i<line_num)
    {
        if (j!=-1)
        {
            if (vis[j]==0)
            {
                if (next[j]!=-1)
                {
                    printf("%d ", j);
                }
                else
                {
                    printf("%d", j);
                }
                is_not_first=1;
                vis[j]=1;
                j=next[j];
            }
            else
            {
                j=-1;
            }
        }
        else
        {
            if (vis[i]==0&&next[i]!=-2)
            {
                if (is_not_first)
                {
                    printf("\n");
                }
                if (next[i]!=-1)
                {
                    printf("%d ", i);
                }
                else
                {
                    printf("%d", i);
                }
                is_not_first=1;
                vis[i]=1;
                j=next[i];
            }
            ++i;
        }
    }
    if (size!=0)
    {
        printf("\n");
    }
    return 0;
}
