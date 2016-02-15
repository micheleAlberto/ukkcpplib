#include "tree.hpp"
#include <iostream>
#ifdef NAMED
std::string UkkTree::DOT(){
  std::stringstream ss;
  if (text.size()<10)
    ss<<"digraph "<<substring(-1,-1)<<" {";
  else
    ss<<"digraph "<<" ukktree "<<" {";
  ss<<DOT(root);
  ss<<"}\n\n";
  return ss.str();
};

std::string UkkTree::DOT(UkkNode* n){
    std::stringstream ss;
    ss<<"//begin node "<<n->name<<"\n";
    for (auto edgeMapIt:n->edges)
      ss<<"/*" << edgeMapIt.first<<"*/"<<DOT(edgeMapIt.second,n->name);
    if (n->suffixLink)
      ss <<"/*SUFFIX*/"<<(n->name)<<" -> "<<n->suffixLink->name<<" [style=dotted];\n";
    ss<<"//end node "<<n->name<<"\n";
    return ss.str();
};
std::string UkkTree::DOT(UkkEdgeBase *e,int father_name){
    std::stringstream ss;
    UkkNode* next=e->node();
    if (next){
      ss << father_name <<" -> "<<(next->name)<<"[label=\""<< edgeString(e) <<"\"];\n";
      ss << DOT(next);
    }
    else {
      ss << father_name <<" -> \""<<e->first<<"."<<edgeString(e)<<"\";\n";
    };
    return ss.str();
};


#endif
