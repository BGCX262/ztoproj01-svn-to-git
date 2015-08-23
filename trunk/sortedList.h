#ifndef SORTEDLIST_H_INCLUDED
#define SORTEDLIST_H_INCLUDED
#include <list>

using namespace std;

template<typename T>
class sortedList{
public:
    typedef typename list<T>::iterator iterator;
private:
    iterator lastFound;
    list<T> elem;

    void innerInsert(T& item){
            iterator i = elem.begin();

            while((i!=elem.end())&&((*i)<item))
                ++i;
            if((i==elem.end())||(item<(*i)))
                elem.insert(i,item);
    };

    void innerRemove(T& item){
        elem.remove(item);
    };

    iterator findItem(T& item){
        iterator i = elem.begin();
        while((i!=elem.end())&&(*i<item)&&(*i!=item))
            ++i;
        return i;
    };

    bool innerContains(T& item){
        iterator i = findItem(item);

        return (*i!=item)?false:true;
    };
public:
    sortedList(){
        elem.clear();
    };
    void insert(T item){
        innerInsert(item);
    };
    void insert(T& item){
        innerInsert(item);
    };
    void remove(T item){
        innerRemove(item);
    };
    void remove(T& item){
        innerRemove(item);
    };
    bool contains(T item){
        return innerContains(item);
    };
    bool contains(T& item){
        return innerContains(item);
    };

 //   void print(){ iterator i = elem.begin(); cout<<elem.size()<<endl; for(;i!=elem.end();++i) cout<<*i<<endl;};
    iterator begin(){return elem.begin();};
    iterator end(){return elem.end();};
};

#endif // SORTEDLIST_H_INCLUDED
