#ifndef TREE_H_INCLUDED
#define TREE_H_INCLUDED
#define NAMED
#include <string>
#include <utility>
#include <vector>
#include "node.hpp"
#include "symbol.hpp"
#include "options.hpp"
#include "query/query.hpp"
class UkkNode;
class UkkLeaf;
class UkkEdgeBase;
class UkkQuery;
typedef std::pair<int,UkkNode*> UkkTreeIndex;//index,node
class UkkTree {
    private:
    bool rule_3_used=(0!=0);
    public:
    //members
    UkkTreeOptions opt;
    std::vector<Symbol> text{};
    int text_index=-1;
    int n_leafs=0;
    UkkNode *root;
    UkkNode *last_leaf_node;
    UkkLeaf *last_leaf;
    //constructor
    UkkTree();
    //methods
    UkkTreeIndex location_downward(UkkNode *n,int index);
    UkkTreeIndex location_downward(UkkTreeIndex index);
    int edgeLenght( UkkEdgeBase *e);
    int common_substring_lenght(int from1,int from2);
    void split_edge(UkkNode *parent,
                UkkEdgeBase *edge,
                int last_common_index,
                int leaf_bottom);
    void add_substring_to_node(UkkNode *node,int from, int to);
    void add_substring_to_node_iterative(UkkNode *_node,int _from, int _to);
    void add_symbol(Symbol x);
    void add_symbol(char *x);
    void add_symbols(char *x);
    std::string substring(int from,int to);
    std::string leafString( UkkEdgeBase *e);
    std::string edgeString( UkkEdgeBase *e);
    //query
    UkkQuery query();
    bool search(std::vector<Symbol> queryText,UkkTreeIndex *answer);
    int count(UkkNode *n);
#ifdef NAMED
    void pptext();
    std::string JSON();
    std::string JSON(UkkNode* n);
    std::string JSON(UkkEdgeBase *e);
    std::string DOT();
    std::string DOT(UkkNode* n);
    std::string DOT(UkkEdgeBase *e,int father_name);
#endif //NAMED
    };


#endif
