#include "tree.hpp"
#include <iostream>
UkkTree::UkkTree(){
    opt=UkkTreeOptions();
    root=new UkkNode();
    last_leaf_node=root;};

UkkQuery UkkTree::query(){return UkkQuery(this);};
UkkTreeIndex UkkTree::location_downward(UkkNode *n,int index){
        UkkTreeIndex query(index,n);
        return location_downward(query);};

/*
UkkTreeIndex =<int steps, UkkNode *node>
means "pointing <steps> character positions down from <node>"
UkkTreeIndex =<0,root>
means that no suffix link is found along the path from the input index to the root

called like this in add_symbol:
  UkkTreeIndex query(text_index-edgeLenght(last_leaf),last_leaf_node);
  UkkTreeIndex result=location_downward(query);
  UkkNode *node=result.second->suffixLink;
  //std::cout<<"[UkkTree::add_symbol] downward get to NODE "<<node->name<<std::endl;
  add_substring_to_node(node,result.first+1,text_index);


UkkTreeIndex=<int steps=text_index-edgeLenght(last_leaf), UkkNode *node=last_leaf_node>
if last_leaf_node.isRoot():
  return <no suffix link is found>
if last_leaf_node has suffix link:
  return index => text_index-edgeLenght(last_leaf) steps from last_leaf_node
else:
  steps=text_index-edgeLenght(last_leaf)
    +edgeLen(from index.second to index.second.father )
  from node:index.second->father
  query(index.first,index.second->father)

*/
UkkTreeIndex UkkTree::location_downward(UkkTreeIndex index){
        //traverse the tree from leafs toward the root looking for a suffix link
        if (index.second->isRoot())
            //no suffix link is found
            return UkkTreeIndex(0,root);
        if (index.second->suffixLink)
            return index;
        auto father=index.second->father;
        for (auto edge_it:father->edges)
        if (edge_it->second->node()==index.second){
            auto fatherToCurrent=edge_it->second;
            int lenght_of_the_edge_i_am_walinkg_back=edgeLenght(fatherToCurrent);
            UkkTreeIndex query(
              index.first+lenght_of_the_edge_i_am_walinkg_back,
              index.second->father);
            return location_downward(query); }
        std::cout<<"[UkkTree::location_downward] this part of code should not be reached!!!"<<std::endl;
        };

int UkkTree::edgeLenght( UkkEdgeBase *e){
        return e->lenght(text_index);}

int UkkTree::common_substring_lenght(int from1,int from2) {
        //std::cout << "[common_substring_lenght] " <<from1<<" "<<from2<<" <";
        int l=0;
        int i1=from1;
        int i2=from2;
        while ((text[i1]==text[i2])
           && (i1<=text_index)
           && (i2<=text_index)){
            //std::cout <<text[i1];
            i1++;
            i2++;
            l++;}
        //std::cout << "> l=" << l<<std::endl;
        return l;
        }

void UkkTree::split_edge(UkkNode *parent,
                UkkEdgeBase *edge,
                int last_common_index,
                int leaf_bottom){
        edge->split(parent,last_common_index,leaf_bottom,this);
        return;}

void UkkTree::add_substring_to_node(UkkNode *node,int from, int to){
        Symbol x=text[from];
        /*
        std::cout<<"[UkkTree::add_substring_to_node] node #"<<node->name<<" from="<<from<<" to="<<to;
        std::cout<<"["<<x<<"]:"<<substring(from,to+1)<<std::endl;
        DEBUG CODE*/
        int substring_lenght=to-from+1;
        /*
        std::cout<<"[UkkTree::add_substring_to_node] substring lenght :"<<substring_lenght<<std::endl;
        DEBUG CODE*/
        auto edge_it=node->edges.find(x);
        if (edge_it==node->edges.end()){// #CASE1 (finale)
            //RULE2: new leaf case
            /*
            std::cout<<"[UkkTree::add_substring_to_node] no edges[symbol]=>new leaf"<<std::endl;
            std::cout<<"[UkkTree::add_substring_to_node]<"<<from<<","<<to<<">RULE2 "<<std::endl;
            DEBUG CODE*/
            UkkLeaf *new_leaf= new UkkLeaf(from);
            node->edges[x]=new_leaf;
            last_leaf=new_leaf;
            n_leafs++;
            if (bool(last_leaf_node)
            && (! last_leaf_node->isRoot())
            && (! bool(last_leaf_node->suffixLink)))
                {last_leaf_node->suffixLink=node;};
            last_leaf_node=node;
            }
        else if (edgeLenght(edge_it->second)>=(substring_lenght))// #CASE2 (finale) //NOTE: il segno prima era >, diventato >=alle 19 di mercoledì
            {//the suffix to add is shorter than the label of current edge:
            UkkEdgeBase *edge=edge_it->second;
            /*
            std::cout << "edgeLenght(edge)="<<edgeLenght(edge_it->second) << std::endl;
            std::cout<<"[UkkTree::add_substring_to_node] found "<<node->name<<".edges[symbol]:"<<edgeString(edge)<<std::endl;
            DEBUG CODE*/
            int csl=common_substring_lenght(from,edge->first);
            /*
            std::cout<<"the suffix to add is shorter than the label of current edge"<<std::endl;
            std::cout<<" common:"<<csl<<std::endl;
            DEBUG CODE*/
            if (csl>=substring_lenght) {// #CASE2.1 (finale)
                //this extension will be implicit , use rule 3
                rule_3_used=TRUE;
                /*std::cout<<"[UkkTree::add_substring_to_node] ising RULE3"<<std::endl; DEBUG CODE*/
                //following extensions will also be implicit in this phase
                if (  bool(last_leaf_node)
                && (! last_leaf_node->isRoot())
                && (! bool(last_leaf_node->suffixLink)) )
                    { /*std::cout << "[UkkTree::add_substring_to_node] suffixlink ";
                      std::cout << last_leaf_node->name;
                      std::cout << "-->"<<node->name<<std::endl; DEBUG CODE*/
                      last_leaf_node->suffixLink=node;}
                else{
                      /*
                      std::cout << "[UkkTree::add_substring_to_node] NO suffixlink "<<std::endl;
                      if (!bool(last_leaf_node))
                        std::cout << "\tno last_leaf_node"<<std::endl;
                      if (bool(last_leaf_node)&&(last_leaf_node->isRoot()))
                        std::cout << "\tlast_leaf_node is root"<<std::endl;
                      if (bool(last_leaf_node)&&(last_leaf_node->suffixLink))
                        std::cout << "\tlast_leaf_node has suffixlink"<<std::endl;*/;
                };
                return;
                }
            else {// #CASE2.2
                //in this case common_substring_lenght<=substring_lenght
                  //this extension will split the the edge using RULE2
                /*
                if edge is a leaf
                    assert last_common_index<=text_index
                else
                    assert last_common_index< edge.last
                */

                /*
                std::cout<<"<"<<from<<","<<to<<">RULE2.2 => split"<<std::endl;
                std::cout<<"[UkkTree::add_substring_to_node] call split_edge"<<std::endl;
                std::cout<<"[UkkTree::add_substring_to_node] split_edge node:"<<node->name<<std::endl;
                std::cout<<"[UkkTree::add_substring_to_node] split_edge edges["<<text[edge->first]<<"]"<<std::endl;
                std::cout<<"[UkkTree::add_substring_to_node] split_edge csl:"<<csl<<std::endl;
                std::cout<<"[UkkTree::add_substring_to_node] split_edge to:"<<to<<std::endl;
                DEBUG CODE*/
                UkkEdgeBase *edge=edge_it->second;
                split_edge(
                    node,
                    edge,
                    csl,
                    to);
                return;
                };
            }
        else {//#CASE3 (ricorsivo lungo l' albero , cerca atro nodo)
            //in this case :
            //  edgeLenght(edge_it.second)<=substring_lenght
            //  recursively call the same function on the next node in the chain
            /*
            std::cout << "edgeLenght(edge)="<<edgeLenght(edge_it->second) << " is short , going down one node"<< std::endl;
            DEBUG CODE*/
            UkkNode *next_node=edge_it->second->node();
            int next_from=from+edgeLenght(edge_it->second);
            int next_to=to;
            add_substring_to_node(next_node,next_from, next_to);};
        return;};

void UkkTree::add_substring_to_node_iterative(UkkNode *_node,int _from, int _to){
        UkkNode *node=_node;
        int from=_from;
        int to=_to;
        while TRUE {
            Symbol x=text[from];
            int substring_lenght=to-from+1;
            auto edge_it=node->edges.find(x);
            if (edge_it==node->edges.end()){// #CASE1 (final)
                //RULE2: new leaf case
                UkkLeaf *new_leaf= new UkkLeaf(from);
                node->edges[x]=new_leaf;
                last_leaf=new_leaf;
                n_leafs++;
                if (bool(last_leaf_node)
                && (! last_leaf_node->isRoot())
                && (! bool(last_leaf_node->suffixLink)))
                    {last_leaf_node->suffixLink=node;};
                last_leaf_node=node;
                return;
                }
            else if (edgeLenght(edge_it->second)>(substring_lenght))// #CASE2 (finale)
                {//the suffix to add is shorter than the label of current edge:
                UkkEdgeBase *edge=edge_it->second;
                int csl=common_substring_lenght(from,edge->first);
                if (csl>substring_lenght) {// #CASE2.1 (finale)
                    //this extension will be implicit , use rule 3
                    rule_3_used=TRUE;
                    //following extensions will also be implicit in this phase
                    if (  bool(last_leaf_node)
                    && (! last_leaf_node->isRoot())
                    && (! bool(last_leaf_node->suffixLink)) )
                        last_leaf_node->suffixLink=node;
                    return;}
                else {// #CASE2.2
                    //in this case common_substring_lenght<=substring_lenght
                      //this extension will split the the edge using RULE2
                    /*
                    if edge is a leaf
                        assert last_common_index<=text_index
                    else
                        assert last_common_index< edge.last
                    */
                    UkkEdgeBase *edge=edge_it->second;
                    split_edge(
                        node,
                        edge,
                        csl,
                        to);
                    return;};
                }
            //#CASE3 (ricorsivo)
            //in this case :
            //  edgeLenght(edge_it.second)<=substring_lenght
            //  recursively call the same function on the next node in the chain
            node=edge_it->second->node();
            from=from+edgeLenght(edge_it->second);};
        return;};

std::string UkkTree::substring(int _from,int _to){
  int from=((_from!=-1)?_from:0);
  int to=((_to!=-1)?_to:text.size());
  std::stringstream ss;
  for (int i=from;i<to;i++)
    ss<<text[i];
  return ss.str();
};
std::string UkkTree::edgeString( UkkEdgeBase *e){
  int from=e->first;
  int to=from+edgeLenght(e);
  return substring( from, to);
};
std::string UkkTree::leafString( UkkEdgeBase *e){
  return substring( e->first, -1);};

void UkkTree::add_symbol(Symbol x){
        text_index++;
        text.push_back(x);
        int extension=n_leafs;
        rule_3_used=FALSE;
        std::cout<<"ADD:"<<x<<std::endl;
        /*
        std::cout<<"[UkkTree::add_symbol] RULE1 "<<n_leafs<<"times"<<std::endl;
        std::cout<<"[UkkTree::add_symbol] text index :"<<text_index;
        std::cout<<"\text :"<<extension;
        std::cout<<"\tkeep_extending :"<<(text_index>=extension)<<std::endl;
        //std::cout<<"[UkkTree::add_symbol] ((!rule_3_used) && (text_index>=extension)) :"<<((!rule_3_used) && (text_index>=extension))<<std::endl;
        DEBUG CODE*/
        while ((!rule_3_used) && (text_index>=extension)){
            /*
            td::cout<<"[UkkTree::add_symbol] 3used :"<<rule_3_used;;
            std::cout<<"\text:"<<extension<<std::endl;
            DEBUG CODE*/
            if (last_leaf_node==root){
                //std::cout<<"[UkkTree::add_symbol] LLF node ==ROOT "<<std::endl; DEBUG CODE*/
                add_substring_to_node (root,extension,text_index);}
            else {
                //std::cout<<"[UkkTree::add_symbol] LLF node !=ROOT #"<<last_leaf_node->name<<std::endl; DEBUG CODE*/
                UkkTreeIndex query(text_index-edgeLenght(last_leaf),last_leaf_node);
                //UkkTreeIndex query(last_leaf.first-1,last_leaf_node)
                UkkTreeIndex result=location_downward(query);
                if (result.second->isRoot()){
                    //std::cout<<"[UkkTree::add_symbol] downward get to ROOT "<<std::endl; DEBUG CODE*/
                    add_substring_to_node (root,extension,text_index);
                    }
                else {
                    //TODO:controllare qui e in location_downward
                    // forse "location_downward" non aggiorna bene l' indice numerico nel caso ricorsivo
                    UkkNode *node=result.second->suffixLink;
                    //std::cout<<"[UkkTree::add_symbol] downward get to NODE "<<node->name<<std::endl; DEBUG CODE*/
                    add_substring_to_node(node,result.first+1,text_index);
                    }
                }
            extension++;
            };
        }
void UkkTree::add_symbol(char *x){
  char *xx=x;
  while ((*xx)!='\0') {add_symbol(*xx);xx++;};
};
void UkkTree::add_symbols(char *x){
  add_symbol(x);
};
int UkkTree::count(UkkNode *n){
          if (n==NULL) {std::cout<<"L";return 1;};
          int sum=0;
          for (auto nn:n->edges) sum+=count(nn.second->node());
          return sum;
        };
bool UkkTree::search(std::vector<Symbol> queryText,UkkTreeIndex *answer){
    int queryTextIndex=0;
    int queryTextLimit=queryText.size();
    UkkNode *nodeIt=root;
    while TRUE { //this loop skip through nodes, one edge per iteration
        SymbolMap::const_iterator edgeIt=nodeIt->edges.find(queryText[queryTextIndex]);
        SymbolMap::const_iterator endIt =nodeIt->edges.end();
        bool noEdgeIsFound= (endIt==edgeIt);
        if (noEdgeIsFound){
          //std::cout<<"No edge found on node #"<<nodeIt->name<<" whith symbol "<<queryText[queryTextIndex]<<std::endl;
          return FALSE;};
        int edgeIndex= edgeIt->second->first;
        int el=edgeLenght(edgeIt->second);
        //std::cout<<"on node #"<<nodeIt->name<<" whith symbol "<<queryText[queryTextIndex]<<" found "<< edgeString(edgeIt->second)<<std::endl;
        bool EndOfEdge=FALSE;
        while (!EndOfEdge) { //this loop process a single edge, one symbol per iteration
            bool textMatchQuery= (queryText[queryTextIndex] == text[edgeIndex]);
            if (!textMatchQuery) {
              std::cout<<"<"<<queryText[queryTextIndex]<<","<<text[edgeIndex]<<">\n";
              return FALSE;}
            //pop query and edge
            std::cout<<queryText[queryTextIndex];
            queryTextIndex+=1;
            edgeIndex+=1;
            el-=1;
            EndOfEdge  = (el==0);
            bool endOfQuery= (queryTextIndex==queryTextLimit);
            if (endOfQuery) {
              if (answer){
                answer->first=edgeIndex-edgeIt->second->first;
                answer->second=nodeIt;}
              return count(edgeIt->second->node());}
            if (EndOfEdge ) {
              //std::cout<<"\neo edge\n";
              //return FALSE;
              };
            };
        nodeIt=edgeIt->second->node();//get the next node in the tree
        if (! nodeIt) return FALSE;
        };
};


void UkkTree::pptext(){
  //std::cout <<"Text:";
  for (auto t : text) std::cout <<t;
  std::cout << std::endl;
};
