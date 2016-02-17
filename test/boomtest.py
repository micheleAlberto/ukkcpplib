import tree as T
from os import system

def t():
    print "\t\tQUERY TEST"
    s="trentatre_trentini_entrarono_a_trento_tutti_e_trentatre_di_tratto_in_tratto_trotterellandoW"
    for i in range(len(s)+1):
        ss=s[0:i]
        A=T.UkkTree()
        A.add_symbols(ss)
        print '\t\tPATTERN ',i,': ',ss
        with open("test/bo/"+str(i)+".dot",'w') as f:
            f.write(A.DOT())
        system("dot -Tpng:cairo -O test/bo/"+str(i)+".dot")

def t2():
    s="mississippi"
    ss=s+'_'
    A=T.UkkTree()
    A.add_symbols(ss)
    print '\t\tPATTERN : ',ss
    with open("test/bo/"+s+".dot",'w') as f:
        f.write(A.DOT())
    system("dot -Tpng:cairo -O test/bo/"+s+".dot")

t2()
    
