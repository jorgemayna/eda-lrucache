/*
  Se uso unordered_map y list.En la lista se guardo los nodos de manera que funcione como un queue(LRU). 
  Unordered_map se uso para obtener tiempos de acceso O(1) a travez de las keys 
  a los respectivos iteradores de la lista.

   insertKeyValuePair() tiempo O(1): 
            La key ya existe : se inserta un nuevo nodo con la actualizacion al comienzo de la lista(O(1)) y se
            elimian el anterior(Se elimina en O(1) ya que el mapa guarda el iterador, con el iterador se elimina de la
            lista en O(1) segun la documentacion)

            La key no existe, cache con espacio libre : simplemente se incerta un nuevo nodo al inicio O(1)

            La key no existe, cache lleno: se hace un pop_back a la lista(O(1)) y se incerta un nuevo nodo en top.

   getValueFromKey() tiempo O(1) : Se accede al valor guardado en la lista a travez del mapa
   getMostRecentKey() tiempo O(1) : se hace front() a la lista
*/
#include <iostream>
#include <unordered_map>
#include <list>
#include <string>
#include <optional> 
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
    unordered_map<T,typename list<Node<T,Y> *>::iterator > cache;
    list<Node<T,Y>*> lru;
  public:
    LRUcache(int size){
      maxSize=size;
    }

    void insertKeyValuePair(T key , Y value);      
    optional<Y> getValueFromKey(T key);
    T getMostRecentKey(){
      return lru.front()->key;      
    }

    void print_cache();
    void print_lru();      

};

template<class T,class Y>
void LRUcache<T,Y>::insertKeyValuePair(T key , Y value){
  if(cache.count(key)==0){//la llave no existe
    if(cache.size()==maxSize){//el cache esta lleno                                  
      cache.erase(lru.back()->key);
      delete lru.back();
      lru.pop_back();          
    }      
    lru.push_front(new Node<T,Y>(key,value));
    cache.insert(make_pair(key,lru.begin()));
    return;
  }
  lru.push_front(new Node<T,Y>(key,value));
  delete *cache[key];
  lru.erase(cache[key]);
  cache[key] = lru.begin();
}

template<class T,class Y>
optional<Y> LRUcache<T,Y>::getValueFromKey(T key){
  if(cache.count(key)==0)return{}; 
  lru.push_front(new Node<T,Y>(key,(*cache[key])->value));
  delete *cache[key];
  lru.erase(cache[key]);
  cache[key] = lru.begin();
  return (*cache[key])->value;
}

template<class T,class Y>
void LRUcache<T,Y>::print_cache(){
  cout<<"## Cache  ===="<<endl;
  for(auto it = cache.begin();it != cache.end();it++){
    cout << it->first<<" => ("<<(*it->second)->key<<", "<<(*it->second)->value<<")"<<endl;
  }
}

template<class T,class Y>
void LRUcache<T,Y>::print_lru(){
  cout<<"## LRU  ===="<<endl;
  for(auto it = lru.begin();it!=lru.end();it++){
    cout <<" ("<<(*it)->key<<", "<<(*it)->value<<")"<<endl;
  }
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
  
  cout<<*c1.getValueFromKey("c")<<endl; // retorna un optional<T>
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