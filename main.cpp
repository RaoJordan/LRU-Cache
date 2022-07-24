#include<bits/stdc++.h>
using namespace std;

//Node to store the data(Linked list)
class Node{
    public:
    string key;
    int value;
    Node(string key, int value)
    {
        this->key = key;
        this->value = value;
    }
};

class LRUcache{
    public:
    int maxSize;
    list<Node> l;
    unordered_map<string,list<Node>::iterator > m;

    LRUcache(int maxSize){
        this->maxSize = maxSize > 1 ? maxSize : 1;
    }

    void insertKeyValue(string key,int value){
        //..
        if(m.count(key)!=0){
            //that is the key is present in cache memory
            //replace the old value and update 
            auto it = m[key];
            it->value = value;
        }
        else{
            //now we don't have key in cache 
            // we will check if cache is full or not
            if(l.size() == maxSize)
            {
                Node last = l.back();
                m.erase(last.key); // remove from hashmap
                l.pop_back(); // remove from Linked list;
            }
            //now we have space so we will insert key
            Node n(key,value);
            l.push_front(n);//insert in list
            m[key] = l.begin();//insert in map;
        }
        return;
    }

    int* getValue(string key)
    {
        if(m.count(key)!=0){
            auto it = m[key];
            int val = it->value;
            l.push_front(*it);
            l.erase(it);
            m[key] = l.begin();
            return &l.begin()->value;
        }
        return NULL;
    }

    string mostRecentKey(){
        return l.front().key;
    }

};

int main()
{
    LRUcache lru(3);
    lru.insertKeyValue("mango",10);
    lru.insertKeyValue("apple",20);
    lru.insertKeyValue("guava",30);

    cout<<lru.mostRecentKey()<<endl;

    lru.insertKeyValue("mango",40);
    cout<<lru.mostRecentKey()<<endl;

    lru.insertKeyValue("banana",50);

    int *orders = lru.getValue("mango");
    if(orders!=NULL){
        cout<<"order of Mangoes"<<*orders<<endl;
    }
    if(lru.getValue("apple")==NULL)
    {
        cout<<"apple doesn't exit"<<endl;
    }

    if(lru.getValue("mango")==NULL)
    {
        cout<<"mango doesn't exit"<<endl;
    }
    if(lru.getValue("banana")==NULL)
    {
        cout<<"banana doesn't exit"<<endl;
    }
    if(lru.getValue("guava")==NULL)
    {
        cout<<"guava doesn't exit"<<endl;
    }
    return 0;
}