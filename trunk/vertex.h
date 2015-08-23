#ifndef VERTEX_H_INCLUDED
#define VERTEX_H_INCLUDED
#include "baza.h"



class vertex{
private:
    static int nextIDVal;
    int _personCount;
    float _hoursAmmount;
    int _ID;
    bool _isValid;
//copyData prywatne zeby go nie uzywac z zewnatrz i wyrzuca wyjatek nie przejmujemy sie tym
//lapiemy dopiero w kodzie ktory uzywa tej klasy
    void copyData(const vertex& v) {
            if ((random()(0,10000)/100.0) <= ctorException::getProbability())
            throw CTOREX();

            _ID = v._ID;
            _personCount = v._personCount;
            _hoursAmmount = v._hoursAmmount;
            _isValid = v._isValid;
    }


public:

    vertex(int p=0, float h=0){
            _ID = nextIDVal;
            nextIDVal ++;
            _personCount = p;
            _hoursAmmount = h;
            _isValid = true;
    };

    //konstruktor kopiuj¹cy - gwarancja silna, rzuca wyj¹tkami z prawdpopodobieñstwem p
    vertex(const vertex& v){
            copyData(v);
    };

    vertex& operator=(const vertex& v){
        if ((random()(0,10000)/100.0) <= assignException::getProbability())
            throw ASSIGNEX();
        if(this != &v)
            copyData(v);
        return *this;
    };

    bool isValid(){ return _isValid; };
    void invalidate(){ _isValid = false; };
    void validate(){ _isValid = true; };
    int getPersonCount(){ return _personCount; };
    float getHoursAmmount(){ return _hoursAmmount; };
    void setPersonCount(int p){ _personCount = p; };
    void setHoursAmmount(float h){ _hoursAmmount = h; };
    int getID(){ return _ID; };
    static int getNextIDVal() { return nextIDVal; }
    void WstawDane(int i);
    void PobierzDane(int i);
};

int vertex::nextIDVal = 1;

void vertex::PobierzDane(int i){
    if ((random()(0,10000)/100.0) <= selectException::getProbability())
            throw SELECTEX();
    _personCount = baza[i].getN();
    _hoursAmmount = baza[i].getH();
}

//gwarancja silna wyjatki z prawdopodobieñstwem q
void vertex::WstawDane(int i){
    if ((random()(0,10000)/100.0) <= insertException::getProbability())
            throw INSERTEX();
    baza[i].setN(_personCount);
    baza[i].setH(_hoursAmmount);
}


#endif // VERTEX_H_INCLUDED
