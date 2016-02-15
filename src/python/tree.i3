%module tree
%{
#include "../tree/tree.hpp"
#include "../tree/node.hpp"
//lol
#include "../tree/symbol.hpp"
#include "../tree/query/query.hpp"
%}

class UkkTree {
    public:
    std::vector<Symbol> text{};
    int text_index=-1;
    int n_leafs=0;
    UkkTree();
    int edgeLenght( UkkEdgeBase *e);
    void add_symbol(Symbol x);
    void add_symbol(char *x);
    void add_symbols(char *x);
    std::string substring(int from,int to);
    int count(UkkNode *n);
    void pptext();
    std::string DOT();
    std::string DOT(UkkNode* n);
    std::string DOT(UkkEdgeBase *e,int father_name);
    UkkQuery query();
};

class UkkQuery{
    public:
    UkkQuery path(SymbolList);
    SymbolList xx={};
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

    PatternInstanceList instances();
    int n_instances();
};
