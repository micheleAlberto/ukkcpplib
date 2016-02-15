/*
Copyright (c) 2012, Michele Alberto
All rights reserved.

Redistribution and use in source and binary forms, with or without
modification, are permitted provided that the following conditions are met:
    * Redistributions of source code must retain the above copyright
      notice, this list of conditions and the following disclaimer.
    * Redistributions in binary form must reproduce the above copyright
      notice, this list of conditions and the following disclaimer in the
      documentation and/or other materials provided with the distribution.
    * Neither the name of the <organization> nor the
      names of its contributors may be used to endorse or promote products
      derived from this software without specific prior written permission.

THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS" AND
ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED
WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE
DISCLAIMED. IN NO EVENT SHALL MICHELE ALBERTO OR POLITECNICO DI MILANO BE LIABLE FOR ANY
DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES
(INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES;
LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND
ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT
(INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS
SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
*/

#include "../tree/tree.h"
#include "../search/search.h"
#include "../search/match.h"
#include <stdio.h>
#include <stdlib.h>
#define TEST_FAILED
#define TEST_OK

extern name_index;

int test_search
    (char* my_text ,
     char **pattern_array,
     int pat_num
    )
    {

        int i;
        t_match* m;
        tree_init();
        add_word_safe(my_text,strlen(my_text));
        {
            int c_e=count_edges(root);
            int c_n=name_index;
            printf("nodes created : %d size : %lu \n",c_n,c_n*sizeof(t_node));
            printf("edges created : %d size : %lu \n",c_e,c_e*sizeof(t_edge));
        }



        #pragma omp parallel
            {
                #pragma omp for schedule(dynamic, 1) nowait
                for (i=0;i<pat_num;i++)
                {
                    t_match* heada=NULL;
                    search_5(root,pattern_array[i],0,strlen(pattern_array[i])-1,&heada);
                    printf("pattern matches %d \n",match_list_count(heada) );
                    free_match_list(heada);
                }

            }
        //search_oracle(my_text,my_text,pattern,&headb);
        /*for (m=heada; m!=NULL;m=m->link)
        if (match_list_search(heada,m->first)==NULL)
            {
                printf("error: match not found : (%d,%d) \n trace of the matches:\n",m->first,m->last);
                printf("      using program \n");
                print_match_list(heada);
                printf("      using strstr \n");
                print_match_list(headb);
                return TEST_FAILED;
            }*/

        //getchar();
        return TEST_OK;
    }


search_oracle (char *my_text,char *current_text, char *pattern , t_match **head)
{
    int pattern_lenght=strlen(pattern);
    char* ip=strstr(current_text,pattern);
    int ii=ip-my_text;
    int ie=ii+pattern_lenght-1;
    if (ip==NULL) return;
    t_match *match= new_match();
    match->first=ii;
    match->last=ie;
    match_list_add(head,match);
    search_oracle(my_text,ip+1,pattern,head);
    return;
}


char * string_generator(int size,int alphabet);

int test()
{
    /*char T[]="abbbbabbbabaabbabbabbabbbbabbbabbabbaabaaaaaaababaaababbabaabbabaabaababbaabaabbababbaaabbabbaabbbaabbbbabbababababbbabbaabababbbabababbbbababbbabbabaaabbaabbabababbaaabbbaabbbbaabbbbabbababababbbabbaaba#\n";
    char P[]="bb";*/
    int size=20000000;
    int patnum=8;
    char *T=string_generator(size,64);
    T[size-1]='#';
    char *PA[patnum];
    int i;
    for (i=0;i<patnum;i++) PA[i]=string_generator(3,64);

    test_search(T,PA,patnum);
    return;
}

char char_generator(int alphabet) {
char zero='A';
int c=rand()%alphabet;
return (char)zero+c;
}

char * string_generator(int size,int alphabet)
{
char *s =malloc((sizeof(char))*(size+1));
int i=0;
for (i=0;i<size;i++) s[i]= char_generator( alphabet);
s[size]='\0';
return s;
}


int count_edges (t_node *n)
{
    if (n==NULL) return 0;
    int sum=0;
    int i;
    for (i=0;i<n->n_edges;i++) sum+= count_edges(n->edges[i].link);
    sum+=n->n_edges;
    return sum;
}

