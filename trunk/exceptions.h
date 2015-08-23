#ifndef EXCEPTIONS_H_INCLUDED
#define EXCEPTIONS_H_INCLUDED

#define CTOREX() ctorException( __LINE__, __PRETTY_FUNCTION__)
#define ASSIGNEX() assignException(__LINE__,__PRETTY_FUNCTION__)
#define INSERTEX() insertException(__LINE__,__PRETTY_FUNCTION__)
#define SELECTEX() selectException(__LINE__,__PRETTY_FUNCTION__)

#include <sstream>

using namespace std;
//wyjatek do konstruktora kopiujacego i operatora przypisania
//rzucany z prawdopodobienstwem p

template <class T>
inline std::string to_string (const T& t)
{
std::stringstream ss;
ss << t;
return ss.str();
}

class exceptionsBase{
    private:
        int lineNum;
        string funName;
        int excode;
    public:
    exceptionsBase(){excode = 0;}
    exceptionsBase(int code) {excode = code;}
    exceptionsBase(int code, int line, string fun)
    {
        excode = code;
        lineNum = line;
        funName = fun;
    }
    string Msg(){
        if(funName!="")
            return "Exception! (code: " + to_string(excode) + " function: " + funName + " line: " + to_string(lineNum) + ")";
            else return "Exception " + to_string(excode) +"!" ;
            }

};

class ctorException : public exceptionsBase{
private:
    static int ctorExCount;
    static int ctorExProbability;

public:

        ctorException():exceptionsBase(1){ ctorExCount++; }
        ctorException(int line, string fun) : exceptionsBase(1, line, fun){ ctorExCount++; }

        static int getCount(){ return ctorExCount; }
        static int getProbability() { return ctorExProbability; }
        static void resetCount() { ctorExCount = 0; }
        static void setProbability(int p){ ctorExProbability = p; }
};

class assignException: public exceptionsBase{
private:
    static int assignExCount;
    static int assignExProbability;

public:
        assignException():exceptionsBase(2){ assignExCount++; }
        assignException(int line, string fun):exceptionsBase(2,line, fun){ assignExCount++; }
        static int getCount(){ return assignExCount; }
        static void resetCount() { assignExCount = 0; }
        static int getProbability() { return assignExProbability; }
        static void setProbability(int p){ assignExProbability = p; }
};

class insertException: public exceptionsBase{
private:
    static int insertExCount;
    static int insertExProbability;

public:
        insertException():exceptionsBase(3){ insertExCount++; }
        insertException(int line, string fun):exceptionsBase(3,line, fun){ insertExCount++; }
        static int getCount(){ return insertExCount; }
        static void resetCount() { insertExCount = 0; }
        static int getProbability() { return insertExProbability; }
        static void setProbability(int p){ insertExProbability = p; }
};

class selectException: public exceptionsBase{
private:
    static int selectExCount;
    static int selectExProbability;

public:
        selectException():exceptionsBase(4){ selectExCount++; }
        selectException(int line, string fun):exceptionsBase(4,line, fun){ selectExCount++; }
        static int getCount(){ return selectExCount; }
        static void resetCount() { selectExCount = 0; }
        static int getProbability() { return selectExProbability; }
        static void setProbability(int p){ selectExProbability = p; }
};

int ctorException::ctorExCount = 0;
int ctorException::ctorExProbability;
int assignException::assignExCount = 0;
int assignException::assignExProbability;
int insertException::insertExCount = 0;
int insertException::insertExProbability;
int selectException::selectExCount = 0;
int selectException::selectExProbability;

#endif // EXCEPTIONS_H_INCLUDED
