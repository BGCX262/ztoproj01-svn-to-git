#ifndef BAZA_H_INCLUDED
#define BAZA_H_INCLUDED

#define DATABASE_SIZE 100000


class record{
    private:
        int n;
        float h;
    public:
        int getN(){return n;}
        float getH() {return h;}
        void setN(int x){n=x;}
        void setH(float x) {h=x;}
};

static record baza[DATABASE_SIZE];

#endif // BAZA_H_INCLUDED
