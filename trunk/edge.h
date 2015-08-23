#ifndef EDGE_H_INCLUDED
#define EDGE_H_INCLUDED

typedef unsigned int ID;

class edge{
private:
    ID _source,_dest;
    bool _isValid;

public:
    edge(ID s,ID d){
        _source = s;
        _dest = d;
        _isValid = true;
    };

    ID source(){ return _source; };
    ID dest(){ return _dest; };
    bool isValid(){ return _isValid; };
    void invalidate(){ _isValid = false; };
    void validate(){ _isValid = true; };
    bool operator==(const edge &other) const {
        return (other._source == _source)&&(other._dest == _dest)&&(other._isValid == _isValid);
    };
    bool operator!=(const edge &other) const {
        return !(*this == other);
    };

    bool operator<(const edge& other) const {
        if(other._isValid == _isValid){
            if(other._source == _source)
                return _dest < other._dest;
            else
                return _source < other._source;
        };//else //uzywane wierzcholki maja byc pierwsze :)
        //nie w sekcji else dlatego ze kompilator krzyczy ze potrzebuje returna a to i tak nie zmienia logiki
        return _isValid;
    };
    bool operator<=(const edge& other) const {
        return (*this < other) || (*this == other);
    };
    bool operator>(const edge& other) const {
        return !(*this <= other);
    };
    bool operator>=(const edge& other) const {
        return !(*this < other);
    };
};


#endif // EDGE_H_INCLUDED
