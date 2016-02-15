#include "node.hpp"
#define FALSE 0
#define TRUE 1
void UkkEdgeBase::split(UkkNodePtr parent,int last_common_index,int leaf_bottom,UkkTreePtr T){
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
        int subtree_index=this.first
        //this
        this->first=subtree_index+last_common_index
        //new leaf
        UkkLeaf new_leaf(leaf_bottom);
        //NN new node
        UkkNodePtr new_internal_node(new UkkNode());
        new_internal_node.father(parent);
            Symbol x=T.text[subtree_index+last_common_index];
            Symbol y=T.text[leaf_bottom]
        new_internal_node.edges[x]=new_leaf;
        new_internal_node.edges[y]=this;
        //new internal edge 
        int nie_first=subtree_index;
        int nie_last =nie_first+last_common_index-1;
        UkkEdge new_internal_edge=UkkEdge(nie_first,nie_last,new_internal_node);
        //NP parent node
        Symbol z=T.text[subtree_index];
        assert(&parent.edges[z]==this);
        parent.edges[z]=new_internal_edge;
        //LLN suffix link:
        if (bool(T.last_leaf_node)
        && (T.last_leaf_node!=T.root)
        && (!bool(T.suffixLink)))
            T.suffixLink(new_internal_node);
        //update the TREE:
        T.n_leafs++;
        T.last_leaf=new_leaf;
        T.last_leaf_node(new_internal_node);
        return ;
        };

