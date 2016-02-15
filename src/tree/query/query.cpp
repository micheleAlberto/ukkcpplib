#include "query.hpp"
#define WITH_ECHO 1
#if WITH_ECHO
  #include <iostream>
#endif
#define ECHO if (WITH_ECHO) std::cout<<

UkkQuery::UkkQuery(UkkTree *T){
    _T=T;
    _node=T->root;
    xx={};
    _textIndex=-1;
  };
  std::string UkkQuery::label(){
    std::string str(xx.begin(),xx.end());
    return str;}
UkkQuery UkkQuery::path(SymbolList yy){
    ECHO "UkkQuery::path n:"<<yy.size()<<std::endl;
    UkkQuery q(_T);
    for (auto x:yy) q=q.add_suffix(x);
    return q;
  };
  int UkkQuery::lenght(){return xx.size();};
UkkQuery UkkQuery::add_suffix(Symbol x ){
    if (_textIndex==-1){
      ECHO "UkkQuery::add_suffix:"<<x<< " from root " <<std::endl;
      return add_suffix_when_branching(x);
    };
    if (isBranching()){
      ECHO "UkkQuery::add_suffix:"<<x<< " branching " <<std::endl;
      return add_suffix_when_branching(x );
    };
    /*(!isBranching())*/
    if (_T->text[_textIndex+1]==x) {
      ECHO "UkkQuery::add_suffix:"<<x<< " +1 " <<std::endl;
      UkkQuery q(*this);
      q._textIndex++;
      q.xx.push_back(x);
      return q;}
    else {
      ECHO "UkkQuery::add_suffix:"<<x<< " not found " <<std::endl;
      return UkkQuery(_T);};
  };

bool UkkQuery::isBranching(){
    auto e=current_edge();
    if (_textIndex==_T->edgeLenght(e)+e->first) return TRUE;
    else  return FALSE;
  };
UkkEdgeBase *UkkQuery::current_edge(){
    if (_textIndex==-1) return NULL;
    auto e_it=_node->edges.find(_edgeSymbol);
    auto end=_node->edges.end();
    if (e_it!=end) return e_it->second;
    return NULL;
  };
UkkQuery UkkQuery::add_suffix_when_branching(Symbol x ){
    ECHO "UkkQuery::add_suffix_when_branching"<<std::endl;
    UkkNode * next_node=NULL;
    if (_textIndex==-1)
      next_node=_T->root;
    else
      next_node=current_edge()->node();
    if (next_node)
    {
      auto edgeIt=next_node->edges.find(x);
      auto endIt =next_node->edges.end();
      bool noEdgeIsFound= (endIt==edgeIt);
      if (noEdgeIsFound)
        { ECHO "noEdgeIsFound :"<<edgeIt->first<<":["<<edgeIt->second<<"]"<<std::endl;
          if (WITH_ECHO) for (auto it:next_node->edges) ECHO it.first<< " ";
          ECHO std::endl;
          if (WITH_ECHO) for (auto it:next_node->edges) ECHO ((it.first==x)?"t":"f")<< " ";
          ECHO std::endl;
          return UkkQuery(_T);}
      else /*(EdgeIsFound)*/
        {
        UkkQuery q(*this);
        q._node=next_node;
        q._edgeSymbol=x;
        q._textIndex=edgeIt->second->first;
        q.xx.push_back(x);
        ECHO "edge with symbol: "<<x<< "\ntext index: "<<q._textIndex<<std::endl;
        return q;
        };
    }
    else
    //lookup at the end of a leaf :
    //current_edge()->node() == NULL
    //and isBranching()
    {
      ECHO "next node is NULL"<<std::endl;
      return UkkQuery(_T);};
  };

UkkQuery UkkQuery::rem_prefix(){
    int l=lenght();
    if (_textIndex==-1) return UkkQuery(_T);
    if ((_node==_T->root)&&(l==0)) return UkkQuery(_T);
    if ((_node==_T->root)&&(l> 0)) {
      SymbolList zz;
      for (auto it = xx.begin()+1; it<xx.end() ; it++) zz.push_back(*it);
      //std::copy(xx.begin()+1, xx.end(), zz);
      return path(zz);};
    if (_node->suffixLink){
      UkkQuery q(*this);
      int backward_steps= q._textIndex - q.current_edge()->first;
      q._node=q._node->suffixLink;
      auto e=q._node->edges[q._edgeSymbol];
      int el=q._T->edgeLenght(e);
      while (backward_steps>el){
        backward_steps-=el;
        q._edgeSymbol=q.xx[lenght()-backward_steps];
        q._node=e->node();
        e=q._node->edges[q._edgeSymbol];
        el=q._T->edgeLenght(e);}
      q._textIndex=e->first+backward_steps;
      q.xx.erase(q.xx.begin());
      return q;};
    return UkkQuery(_T);
    };
UkkQuery UkkQuery::rem_prefix(int n){
      UkkQuery q(*this);
      for (int i=0;i<n;i++) q=q.rem_prefix();
      return q;
    }
UkkQuery UkkQuery::add_suffix(SymbolList yy) {
      ECHO "UkkQuery::add_suffix(SymbolList yy):"<<yy.size()<<std::endl;
      UkkQuery q(*this);
      for (auto y:yy) q=q.add_suffix(y);
      return q;
    }
UkkQuery UkkQuery::add_suffix(char *yy) {
      ECHO "UkkQuery::add_suffix(char *yy)"<<std::endl;;
      UkkQuery q(*this);
      int count=0;
      char *y=yy;
      while (*y!='\0'){
        count++;
        q=q.add_suffix(*y);y++;};
      return q;
    }
UkkQuery UkkQuery::add_prefix(SymbolList yy ){
      ECHO "UkkQuery::add_prefix(SymbolList yy ) "<<std::endl;
      ECHO "yy.size:" <<yy.size()<<std::endl;
      ECHO "xx.size:" <<xx.size()<<std::endl;
      SymbolList zz(yy);
      for (auto x:xx) zz.push_back(x);
      ECHO "zz.size:" <<zz.size()<<std::endl;
      return path(zz);};
UkkQuery UkkQuery::add_prefix(char *yy ){
        ECHO "UkkQuery::add_prefix(char *yy )"<<std::endl;
        /*
        char *j = yy;
        int count =0;
        while (*j!='\0') ECHO "["<<count++<<"]"<< *(j++)<<std::endl;
        */
        SymbolList zz={};
        char *y = yy;
        while (*y!='\0') zz.push_back( *(y++));
        for (auto x:xx) zz.push_back(x);
        /*
        ECHO "xx.size:" <<xx.size()<<"-"<<label()<<std::endl;
        ECHO "zz.size:" <<zz.size()<<std::endl;
        */
        return path(zz);
        };
    UkkQuery UkkQuery::rem_suffix(){
      UkkQuery q(*this);
      int l = lenght();
      if (_textIndex==-1) return UkkQuery(_T);
      if ((_node==_T->root)&&(l==0)) return UkkQuery(_T);
      if (_textIndex==current_edge()->first) {
        q._node=_node->father;
        q._edgeSymbol=_T->text[_textIndex-1];
        auto e=q.current_edge();
        q._textIndex=e->first+_T->edgeLenght(e);
        q.xx.erase(q.xx.begin()+xx.size());
        return q;
      }
      q._textIndex--;
      return q;
    };
    UkkQuery UkkQuery::rem_suffix(int n){
      UkkQuery q(*this);
      for (int i=0;i<n;i++) q=q.rem_suffix();
      return q;
    }
  std::vector<int> UkkQuery::collectLeafs(UkkNode *n,int lenght){
      std::vector<int> ii;
      for (auto eit:n->edges)
        for (int l : collectLeafs(eit.second,lenght))
          ii.push_back(l);
      return ii;
    };
std::vector<int> UkkQuery::collectLeafs(UkkEdgeBase *e,int lenght){
      UkkNode *n=e->node();
      int l=lenght+_T->edgeLenght(e);
      if (n) return collectLeafs(n,l);
      std::vector<int> ii={l};
      return ii;
    };
int UkkQuery::n_instances(){return countLeafs(current_edge());};

int UkkQuery::countLeafs(UkkNode *n){
    int s=0;
    for (auto eit:n->edges) s+=countLeafs(eit.second);
    return s;};
int UkkQuery::countLeafs(UkkEdgeBase *e){
          UkkNode *n=e->node();
          if (n) return countLeafs(n);
          return 1;};
PatternInstance UkkQuery::walkToSlice(int d){
  int query_lenght=lenght();
  int last=_T->text_index-d;
  PatternInstance startEnd(last-query_lenght,last);
  return startEnd;
};
PatternInstanceList UkkQuery::instances(){
  auto ce=current_edge();
  PatternInstanceList pil;
  int stepFromFather= _textIndex - ce->first;
  int stepToNextNode= _T->edgeLenght(ce) - stepFromFather;
  int query_lenght=lenght();
  PatternInstanceList list;
  if (ce->node()==NULL){
    list.push_back(walkToSlice(stepToNextNode));
    return list;};
  for (int d:collectLeafs(ce->node(),stepToNextNode))
    list.push_back(walkToSlice(d));
  return list;
  }
