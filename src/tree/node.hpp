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

#ifndef NODE_H_INCLUDED
#define NODE_H_INCLUDED
#include <unordered_map>
#define NAMED
#include <assert.h>
#include <memory>
#include <string>
#include "tree.hpp"
#include "symbol.hpp"

#include <sstream>

#define FALSE (0)
#define TRUE (1)
class UkkNode;
class UkkTree;
//typedef std::shared_ptr<UkkNode> UkkNodePtr;
//typedef std::shared_ptr<UkkTree> UkkTreePtr;

class UkkEdgeBase{
    public:
    int first;
    virtual int lenght (int textIndex) =0;
    virtual UkkNode *node ()=0;
      //return the next node if it is an internal edge
      // else return NULL
    void split(UkkNode *parent,int last_common_index,int leaf_bottom,UkkTree *T);
    virtual ~UkkEdgeBase()=0;
    };

typedef std::unordered_map<Symbol,UkkEdgeBase *> SymbolMap;
class UkkNode {
    public:
    UkkNode *father=NULL;
    SymbolMap edges = {};
    UkkNode * suffixLink=NULL;
    #ifdef NAMED
    UkkNode();
    int name;
    void pprint();
    #endif
    bool isRoot();
    ~UkkNode();
    };


class UkkLeaf : public UkkEdgeBase{
    public:
    UkkLeaf(int first);
    int lenght (int textIndex);
    UkkNode *node ();
    };
class UkkEdge : public UkkEdgeBase{
    public:
    int last;
    UkkNode *n=NULL;
    UkkEdge(int first,int last,UkkNode *node);
    UkkNode * node ();
    int lenght (int textIndex);
    virtual ~UkkEdge();
    };


#endif // NODE_H_INCLUDED
