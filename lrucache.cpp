

//se uso unordered_map y vector como un queue
#include <iostream>
#include <unordered_map>
#include <vector>
#include <string>
using namespace std;

class LRUcache{
  int maxSize;
  unordered_map<string,int> cache;
  vector<pair<string,int>> lru;

  LRUcache(int size){
    maxSize=size;
  }
  void insertKeyValuePair(string key , int value){
    if(cache.count(key)==0){//la llave no existe
      if(cache.size()<maxSize){//el cache no esta lleno
        cache.insert(make_pair(key,value));
        lru.push_back(make_pair(key,value));
        return;
      }else{              //el cache si esta lleno
        cache.erase(lru.back().first);
        lru.pop_back();
        return;
      }      
    }
    //la llave si existe
    cache[key]=value;
    //falta hacer que ese elemento pase al mas recientemente usado
  }
  int getValueFromKey(string key){
    //falta hacer que ese elemento pase al mas recientemente usado
    return cache[key];
  }
  string getMostRecentKey(){
    return lru.front().first;
  }

};

int main(){

}