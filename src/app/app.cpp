#include <stdio.h>
#include "../tree/tree.hpp"
#include "../utils/utils.hpp"
#include <iostream>
#include <vector>
using namespace std;

UkkTree T;
void foo(vector<Symbol> q){
  cout<<"query: ";
  for (auto i: q)
    std::cout << int(i) << ' ';
  cout<<" result:"<<T.search(q,NULL)<<"\n";
}

vector<Symbol> str2vec(string str){
    vector<Symbol> vec;
    for (char t: str) vec.push_back(t);
    return vec;
};
int main(int argc, char* argv[]){
  vector<Symbol> tt;
  std::vector<std::string> arguments(argv + 1, argv + argc);
  string text="abba!";
  if (arguments.size()>0)
    text=arguments[0];
  for (auto t:text){
    cout<<"ADD :"<<t<<" "<<int(t)<<"\n";
    //T.root->pprint();
    //T.pptext();
    T.add_symbol(t);
    cout<<T.DOT()<<"\n";
  }
  save(T.substring(-1,-1),T.DOT());
  cout<<"LOOKUP"<<"\n";
  for (int i=1;i<arguments.size();i++) {
    vector<Symbol> q(str2vec(arguments[i]));
    foo(q);};
}
