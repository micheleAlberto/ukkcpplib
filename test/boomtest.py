import tree as T
from os import system


print "QUERY TEST"
s="abaabaaas"
for i in range(len(s)+1):
    ss=s[0:i]
    A=T.UkkTree()
    A.add_symbols(ss)
    with open("test/bo/"+ss+".dot",'w') as f:
        f.write(A.DOT())
    system("dot -Tpng:cairo -O test/bo/"+ss+".dot")
