#include "node.hpp"
#include <iostream>

#ifdef NAMED
int nameReg=2;
UkkNode::UkkNode(){
  name=nameReg;
  nameReg++;};
void UkkNode::pprint(){
      std::cout << "node #" <<name<<std::endl;
      if (isRoot())
        std::cout << "\t is root"<<std::endl;
      else
        std::cout << "\t father #" <<father->name<<std::endl;
      if (suffixLink)
        std::cout << "\t suffixLink #" <<suffixLink->name<<std::endl;
      std::cout << "\t edges :"<<edges.size()<<std::endl;
      for (auto meit:edges){
        if (meit.second->node()){
          std::cout << "\t E["<<meit.first<<"]:";
          std::cout << (meit.second->first)<<",";
          std::cout << (meit.second->lenght(0));
          std::cout <<" #"<<(meit.second->node()->name)<<std::endl;}
        else
          std::cout << "\t L["<<meit.first<<"]:"<<(meit.second->first)<<std::endl;
      };
  };
#endif
#ifndef NAMED
#endif
bool UkkNode::isRoot(){return bool(father==NULL);};
UkkLeaf::UkkLeaf(int first_index){first=first_index;};
int UkkLeaf::lenght (int textIndex) {return 1+textIndex-first;};
UkkNode *UkkLeaf::node () {return NULL;};
UkkEdgeBase::~UkkEdgeBase(){};
UkkEdge::UkkEdge(int first_index,int last_index,UkkNode *node){
    first=first_index;
    last=last_index;
    n=node;};
UkkNode *UkkEdge::node () {return n;};
int UkkEdge::lenght (int textIndex) {return 1+last-first;};
UkkEdge::~UkkEdge(){
  n->~UkkNode();
  delete n;};
UkkNode::~UkkNode(){
  for (auto eit:edges) {
    eit.second->~UkkEdgeBase();
    delete eit.second;};
};
void UkkEdgeBase::split(UkkNode *parent,int last_common_index,int leaf_bottom,UkkTree *T){
        /*
        situazione iniziale:
            NP->this->
        situazione finale:
            NP->nie->NN->this
                       ->nl
            LLN-suffix->NN

        this edge: questo edge
        new internal edge: nodo da creare e collegare tra parent e nuovo nodo
        new leaf: nuova stringa
        nodo parent NP: ora regge il lato
        nuovo nodo NN: nuovo nodo interno
        Last Leaf Node LLN: il nodo cui stata aggiunta l' ultima foglia

        variabile di supporto per non sporcare a caso this.first
            int subtree_index=PREVIOUS(this.first)
        CHECKS:
        this edge
            .first =last common index+PRE(this.first) è il primo indice non comune tra vecchio e nuovo branch , lato vecchio branch
            .last, .link non toccare : la foglia resta foglia
        new leaf
            .first=leaf_bottom
        NN
            father=parent
            edges={x:this,y:new_leaf}
                x=text[last common index+PRE(this.first)]
                y=text[leaf_bottom]
        new internal edge:
            .first =PRE(this.first)
            .last  =last common index-1+PRE(this.first)
            .link  =NN
        NP parent node:
            z=text[PRE(this.first)]
            edges[PRE(this.first)]=new internal edge
        LLN suffix link:
            se LLN
            1-è definito
            2-non è la radice
            3-il suo suffix link non è ancora definito
                LLN.suffix_link=NN
        garbage collection:
            no object is deleted
            everything is recycled
            zero-wasted-bytes policy
        then update the TREE:
            last_leaf_node->NN
            last_leaf->new leaf
            n_leafs++
        */
        int subtree_index=this->first;
        //this
        this->first=subtree_index+last_common_index;
        //new leaf
        UkkLeaf *new_leaf=new UkkLeaf(leaf_bottom);
        //NN new node
        UkkNode *new_internal_node=new UkkNode();
        new_internal_node->father=parent;
            Symbol x=T->text[subtree_index+last_common_index];
            Symbol y=T->text[leaf_bottom];
        (new_internal_node->edges)[y]=new_leaf;
        (new_internal_node->edges)[x]=this; //x e y(nella riga sopra) sono stati scambiati @giovedì 18:00
        //new internal edge
        int nie_first=subtree_index;
        int nie_last =nie_first+last_common_index-1;
        UkkEdge *new_internal_edge=new UkkEdge(nie_first,nie_last,new_internal_node);
        //NP parent node
        Symbol z=T->text[subtree_index];
        if (parent->edges[z]!=this ) {
          std::cout << "splitting"<<std::endl;
          std::cout << "this :"<<this<<std::endl;
          std::cout << "Z :"<<z<<std::endl;
          std::cout << "(old) parent->edges[z] :"<< parent->edges[z] <<std::endl;
          std::cout << "(new) parent->edges[z] :"<< new_internal_edge <<std::endl;
          assert(parent->edges[z]==this);
        };
        parent->edges[z]=new_internal_edge;
        //LLN suffix link:
        if (bool(T->last_leaf_node)
        && (T->last_leaf_node!=T->root)
        && (!bool(T->last_leaf_node->suffixLink)))
            T->last_leaf_node->suffixLink=new_internal_node;
        //update the TREE:
        T->n_leafs++;
        T->last_leaf=new_leaf;
        T->last_leaf_node=new_internal_node;
        //std::cout << "[split]::DOT" << std::endl<< T->DOT();
        return ;
        };
