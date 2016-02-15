
import tree as T
print "TREE TEST"
#import is OK
A=T.UkkTree()
print "initialization/construction is OK"
A.add_symbol('b')
print "add_symbol is OK"
A.add_symbols("ababbaababbabb")
print "add_symbols is OK"
A.add_symbol('%')
print "added a terminator"


