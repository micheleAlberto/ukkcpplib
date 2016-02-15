import tree as T
from os import system
print "QUERY TEST"
A=T.UkkTree()
W=['a','aa','aaa','aaaa']
s="b".join(W) + '%'
A.add_symbols("abaabaaas")
with open("test.dot",'w') as f:
    f.write(A.DOT())
system("dot -Tpng:cairo -O "+"test.dot")
"""
print "using string : ",s
root_query= A.query()
print "root query is OK"
ab_query= root_query.add_suffix('ab')
print "query for 'ab' :",ab_query.label()
assert('ab'==ab_query.label())
aab_query= ab_query.add_prefix('aa')
print "query for 'aaab' adding a prefix : ",ab_query.label()
assert('aab'==aab_query.label())
print 'ab :',ab_query.instances()
print 'aab :',aab_query.instances()

def test(tree, q):
    print "--------------TEST:",q
    ts=''.join(tree.text)
    root_query= tree.query()
    query= root_query.add_suffix(q)
    assert (query.label() in ts)
    if q in ts:
        assert(query.label()==q),"{}/{}".format(query.label(),q)
    else:
        assert (query.label() in q)
    print "--------------PASS:",q

for w in W:
    test(A,w)
    test(A,w+'b')
    test(A,w+'c')

"""

