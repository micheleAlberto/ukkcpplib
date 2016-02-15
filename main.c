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

#include <stdio.h>
#include <stdlib.h>
#include "tree/tree.h"
#include "tree/node.h"
#include "print/graph.h"
#include "test/test.h"
#define FALSE 0
#define TRUE 1
int main() {
    printf("size of node %lu \n",sizeof(t_node));
    printf("size of edge %lu \n",sizeof(t_edge));

    test();   
    }
int main2(int argc, char *argv[])
{
    char word[1024];
    char *w2;
    tree_init();
    int online=TRUE;
    {
    int i;
    for (i=1;i<argc;i++)
        {
        if (strcmp(argv[i], "-ge")==0){
                options.graph_each_extension=TRUE;
                };
        if (strcmp(argv[i], "-gw")==0){
                options.graph_each_word=TRUE;
                };
        if (strcmp(argv[i], "-gn")==0){
                options.graph_name=strdup(argv[i+1]);
                i++;
                };
        if (strcmp(argv[i], "-t")==0){
                online=FALSE;
                w2=argv[i+1];
                i++;
                };
        if (strcmp(argv[i], "-pl")==0){
                options.print_labels=TRUE;
                };
         if (strcmp(argv[i], "-sl")==0){
                options.print_suffix_link=TRUE;
                };
        if (strcmp(argv[i], "-ol")==0){
                options.print_labels=TRUE;
                options.print_edge_indexs=FALSE;
                };

        };
    };



    if (online==TRUE) do {
        scanf("%s",word);
        add_word(word);
    }     while (word[0]!='#');
    else
    {
    options.graph_each_word=TRUE;
    add_word(w2);
    }

    return ;
}



