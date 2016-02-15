#include <stdio.h>
#include "../tree/tree.hpp"
#include "../utils/utils.hpp"
#include <iostream>
#include <vector>
#include <ctype.h>
using namespace std;

UkkTree T;
void foo(vector<Symbol> q){
  cout<<T.search(q,NULL)<<", ";
}

vector<Symbol> str2vec(string str){
    vector<Symbol> vec;
    for (char t: str) vec.push_back(t);
    return vec;
};
int main(int argc, char* argv[]){
  std::vector<std::string> arguments(argv + 1, argv + argc);
  string filename="";
  if (arguments.size()>0)
    filename=arguments[0];
  else return 1;
  std::filebuf fb;
  //std::cout<<"FILENAME:"<<filename<<std::endl;
  if (fb.open (filename,std::ios::in)) {
    std::istream is(&fb);
    while (is){
      char t= char(is.get());
      if (isgraph ( t )){
      //cout<<"ADD :"<<t<<" "<<int(t)<<"\n";
      T.add_symbol(t);}
    };
    fb.close();
  }
  save("graph",T.DOT());
  //cout<<"LOOKUP"<<"\n";
  for (int i=1;i<arguments.size();i++) {
    vector<Symbol> q(str2vec(arguments[i]));
    foo(q);};
  cout<<"\n";
}
