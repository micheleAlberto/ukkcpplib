from tree import UkkTree
from os import system
"""
from search import UkkTree,substring_search
s="trentatre_trentini_entrarono_a_trento_tutti_e_trentatre_di_tratto_in_tratto_trotterellando"
#Create the Tree
A=UkkTree()
#Add some symbols to the tree 
A.add_symbols(s)
#Remember to add a terminator
A.add_symbols("X")
#the tree can be exported as JSON
#in JSON the tree is encoded as an object that maps
#   'root' to the root node
#   'text' to the string of symbols
#   (int) to nodes
#each node is an object that maps
# each symbol to an edge
# -1 to an integer that identify the suffix link of the node
#each edge is represented as a tuple of 3 integer:
#   the index of the first symbol in the text
#   the index of the last symbol in the text
#   the identifier of the node connected
#leaf are encoded as the index of the first symbol of the leaf in the text
print A.JSON()
#can be converted in a python datastructure
suffix_tree=eval(A.JSON())
#or exported as .dot, the graphviz graph format
print A.DOT()
#the tree can be queried for a pattern
pattern='trento'
print substring_search(suffix_tree,suffix_tree['text'], suffix_tree['root'],pattern)
"""
def suffix_count(st,node_id,counter):
    c=0
    for e in st[node_id]:
        if e==-1:
            #this is a suffix link
            pass
        elif type(st[node_id][e]) is int:
            #this is a leaf
            c+=1
        elif type(st[node_id][e]) is tuple:
            #this is another node
            next_node=st[node_id][e][2]
            c+=suffix_count(st,next_node,counter)
    counter[node_id]=c
    return c

def substring_search(st,text,node_id,pattern):
    if len(pattern)==0:
        return True
    p0=pattern[0] 
    if p0 in st[node_id]:
        if type(st[node_id][p0]) is int:
            #leaf case:
            leaf_start=st[node_id][p0]
            leaf_end=len(text)
            for pattern_index,text_index in enumerate(range(leaf_start,leaf_end)):
                if pattern_index==len(pattern):
                    return True
                if text[text_index]!=pattern[pattern_index]:
                    return False
        else:
            #edge case:
            edge_start,edge_end,next_node=st[node_id][p0]
            for pattern_index,text_index in enumerate(range(edge_start,edge_end)):
                if pattern_index==len(pattern):
                    return True
                if text[text_index]!=pattern[pattern_index]:
                    return False
            return substring_search(st,text,next_node,pattern[pattern_index+1:])
    else:
        return False

from itertools import combinations

def test(s):
    A=UkkTree()
    A.add_symbols(s)
    suffix_tree=eval(A.JSON())
    print '--------------------------------------------'
    def oracle(p):
        return p in s
    for i,j in combinations(range(len(s)-1),2):
        p=s[i:j]
        ukk=substring_search(suffix_tree,suffix_tree['text'], suffix_tree['root'],p)
        o=oracle(p)
        print p,o,ukk

#test(s)
