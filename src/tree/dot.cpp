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

std::string UkkTree::JSON(){
  std::stringstream ss;
  ss<<"{";
  ss<<JSON(root);
  ss<<"}\n";
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

std::string UkkTree::JSON(UkkNode* n){
    std::stringstream ss;
    ss<<" "<<n->name<< ": {"<<"\n";
    for (auto edgeMapIt:n->edges){
        ss<<"    \"" <<edgeMapIt.first<<"\" :    "<< JSON(edgeMapIt.second)<<",\n";
    };
    if (n->suffixLink)
      ss <<"     -1 : "<<n->suffixLink->name<<"\n";
    ss<<"},\n";
    for (auto edgeMapIt:n->edges)   if (edgeMapIt.second->node())
      ss<<JSON(edgeMapIt.second->node());
    return ss.str();
};
std::string UkkTree::JSON(UkkEdgeBase *e){
    std::stringstream ss;
    UkkNode* next=e->node();
    if (next){
      int from=e->first;
      int to=from+edgeLenght(e);
      ss << "("<<from<<", "<<to<<", "<<(next->name)<<")";
    }
    else {
      ss << e->first;
    };
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
      ss << father_name <<" -> \""<<edgeString(e)<<"\";\n";
      //ss << father_name <<" -> \""<<e->first<<"."<<edgeString(e)<<"\";\n";
    };
    return ss.str();
};


#endif
