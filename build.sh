echo "generate python interface"
rm src/python/python_wrapper.cxx
swig -python -c++ -v -Wall -o src/python/python_wrapper.cxx src/python/tree.i2
echo "compile query"
rm src/tree/query/query.o
g++ -std=gnu++11 -fPIC -c src/tree/query/query.cpp -o src/tree/query/query.o
echo "compile node.cpp"
rm src/tree/node.o
g++ -std=gnu++11 -fPIC -c src/tree/node.cpp -o src/tree/node.o
echo "compile tree.cpp"
rm src/tree/tree.o
g++ -std=gnu++11 -fPIC -c src/tree/tree.cpp -o src/tree/tree.o
echo "compile utils"
rm src/utils/utils.o
g++ -std=gnu++11 -fPIC -c src/utils/utils.cpp -o src/utils/utils.o
echo "compile dot.cpp"
rm src/tree/dot.o
g++ -std=gnu++11 -fPIC -c src/tree/dot.cpp -o src/tree/dot.o
echo "compile python interface"
g++ -std=gnu++11 -fPIC -c src/python/python_wrapper.cxx -I/usr/include/python2.7 -I/usr/include/x86_64-linux-gnu/python2.7  -fno-strict-aliasing -D_FORTIFY_SOURCE=2 -g -fstack-protector --param=ssp-buffer-size=4 -Wformat -Werror=format-security  -DNDEBUG -g -fwrapv -O2 -Wall -fPIC -o src/python/python_wrapper.o



echo "compile app"
rm bin/app
g++ -std=gnu++11 src/tree/node.o src/tree/query/query.o src/tree/tree.o src/tree/dot.o src/utils/utils.o src/app/app.cpp -o bin/app
echo "compile buildTree"
rm bin/buildTree
g++ -std=gnu++11 src/tree/node.o src/tree/query/query.o src/tree/tree.o src/tree/dot.o src/utils/utils.o src/app/buildTree.cpp -o bin/buildTree
echo "compile python module"
rm bin/_tree.so
rm bin/tree.py
g++ -shared -fPIC src/tree/node.o src/tree/query/query.o src/tree/tree.o src/tree/dot.o src/utils/utils.o src/python/python_wrapper.o -o bin/_tree.so -std=gnu++11 -I/usr/include/python2.7 -I/usr/include/x86_64-linux-gnu/python2.7  -fno-strict-aliasing -D_FORTIFY_SOURCE=2 -g -fstack-protector --param=ssp-buffer-size=4 -Wformat -Werror=format-security  -DNDEBUG -g -fwrapv -O2 -Wall
mv src/python/tree.py bin/tree.py

