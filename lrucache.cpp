/*

//se uso unordered_map y list 

*/
#include <iostream>
#include <unordered_map>
#include <list>
#include <string>
#include <optional> 
#include <functional>
using namespace std;

template<class TT,class YY>
class Node{  
  public:
    TT key;
    YY value;
    Node(TT key_ , YY value_){
      key=key_;
      value=value_;
    }
};

template<class T,class Y>
class LRUcache{
  private:
    int maxSize;
    unordered_map<T,typename list<Node<T,Y> >::iterator > cache;
    list<Node<T,Y>> lru;
  public:
    LRUcache(int size){
      maxSize=size;
    }

    void insertKeyValuePair(T key , Y value);      
    optional<Y> getValueFromKey(T key);
    T getMostRecentKey(){
      return lru.front().key;      
    }

    void print_cache(){
      cout<<"## Cache  ===="<<endl;
      for(auto it = cache.begin();it != cache.end();it++){
        cout << it->first<<" => ("<<it->second->key<<", "<<it->second->value<<")"<<endl;
      }
    }
    void print_lru(){
      cout<<"## LRU  ===="<<endl;
      for(auto it = lru.begin();it!=lru.end();it++){
        cout <<" ("<<it->key<<", "<<it->value<<")"<<endl;
      }
    }

};

template<class T,class Y>
void LRUcache<T,Y>::insertKeyValuePair(T key , Y value){
  if(cache.count(key)==0){//la llave no existe
    if(cache.size()==maxSize){//el cache esta lleno                                  
      cache.erase(lru.back().key);
      lru.pop_back();          
    }      
    lru.push_front(Node<T,Y>(key,value));
    cache.insert(make_pair(key,lru.begin()));
    return;
  }
  lru.push_front(Node<T,Y>(key,value));
  lru.erase(cache[key]);
  cache[key] = lru.begin();
}

template<class T,class Y>
optional<Y> LRUcache<T,Y>::getValueFromKey(T key){
  if(cache.count(key)==0)return{}; 
  lru.push_front(Node<T,Y>(key,cache[key]->value));
  lru.erase(cache[key]);
  cache[key] = lru.begin();
  return cache[key]->value;
}




int main(){
  LRUcache<string,int> c1(3);
  c1.insertKeyValuePair("b",2);
  c1.insertKeyValuePair("a",1);
  c1.insertKeyValuePair("c",3);

  c1.print_cache();
  cout<<endl;
  c1.print_lru();

  cout<<endl<<c1.getMostRecentKey()<<endl;
  
  cout<<(*c1.getValueFromKey("c"))<<endl;
  cout<<*c1.getValueFromKey("b")<<endl;
  cout<<*c1.getValueFromKey("a")<<endl;

  c1.print_cache();
  cout<<endl;
  c1.print_lru();

  c1.insertKeyValuePair("d",4);
  c1.insertKeyValuePair("e",5);

  c1.print_cache();
  cout<<endl;
  c1.print_lru();


  c1.insertKeyValuePair("d",2);
  cout<<c1.getMostRecentKey()<<endl;

  c1.print_cache();
  cout<<endl;
  c1.print_lru();
}