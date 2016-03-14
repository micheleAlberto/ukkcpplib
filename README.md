# ukkcpplib
Ukkcpplib is a library that implements Ukkonen linear time suffix tree construction algorithm.
The construction itself is coded in c++ and allows to export the tree as a JSON object or as graphviz graph.
A simple pattern substring search script in python is included along with a script to count occurrences of substrings.

##build it
```
sh build.sh
```
##use it
```
export PYTHONPATH=${PYTHONPATH}:bin/
python
```

```python
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
```

#licence
This library is released under the GNU general public licence. 
