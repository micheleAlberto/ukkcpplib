#ifndef QUERY_HPP_INCLUDED
#define QUERY_HPP_INCLUDED
#include <string>
#include <vector>
#include "../tree.hpp"
typedef std::vector<Symbol> SymbolList;
typedef std::pair<int,int> PatternInstance;
typedef std::vector<PatternInstance> PatternInstanceList;
class UkkTree;
class UkkNode;
class UkkLeaf;
class UkkEdgeBase;
class UkkQuery{
    private:
      UkkTree *_T=NULL;
      UkkNode *_node=NULL;
      int _textIndex=-1;
      //index of current path in _T->text
      // for d in range(xx.size()) assert _T->Text[_textIndex-d]==Query.xx[xx.size()-d]
      // _textIndex>=current_edge()->first
      // _textIndex<=current_edge()->first+_T->edgeLenght(current_edge())
      Symbol _edgeSymbol=0;
      int lenght();
      UkkEdgeBase *current_edge();
      bool isBranching();
      //return true if the next suffix is uncertain in the tree
      //=bool(_textIndex==current_edge()->first+_T->edgeLenght(current_edge()))
    SymbolList xx={};
    public:
    std::string label();
    UkkQuery path(SymbolList);
    UkkQuery(UkkTree *T);
    //UkkQuery(UkkTree *T,SymbolList xx);

    UkkQuery add_suffix(Symbol x );
    UkkQuery add_suffix(SymbolList yy);
    UkkQuery add_suffix(char *yy);
    //Query(pattern).add_suffix(x)==Query(pattern+x)
    //follow the suffix tree toward the leafs following a the character x
    //specify future/present
    UkkQuery add_prefix(SymbolList yy );
    UkkQuery add_prefix(char *yy );
    //Query(pattern).add_prefix(p)==Query(p+pattern)
    // re-evauluate from root : return Query(p+pattern)
    // specify past
    UkkQuery rem_suffix();
    UkkQuery rem_suffix(int n);
    //Query(pattern+p).rem_suffix(p)==Query(pattern)
    // go from nodes toward their parent nodes , possible problem for leafs
    //generalize with respect to present
    UkkQuery rem_prefix();
    UkkQuery rem_prefix(int n);
    //Query(p+pattern).rem_prefix(p)==Query(pattern)
    //follow the suffix link
    //generalize with respect to past

    PatternInstance walkToSlice(int d);
    PatternInstanceList instances();
    int countLeafs(UkkNode *n);
    int countLeafs(UkkEdgeBase *e);
    std::vector<int> collectLeafs(UkkEdgeBase *e,int lenght);
    std::vector<int> collectLeafs(UkkNode *n,int lenght);
    int n_instances();
  private:
    UkkQuery add_suffix_when_branching(Symbol x );
    };
#endif
