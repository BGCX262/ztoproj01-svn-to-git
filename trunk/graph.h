#ifndef GRAPH_H_INCLUDED
#define GRAPH_H_INCLUDED
#include <vector>
#include <list>
#include <algorithm>
#include "edge.h"
#include "vertex.h"
#include "baza.h"
#include "sortedlist.h"

using namespace std;

template <typename T>
class graph{
private:
    typedef typename map<ID,T>::iterator mapIter;
    ID nextID;
    map<ID, T> vertDict;
    sortedList<edge> edges;

    ID innerAddVertex(T& v){
        bool done = false;
        do{
            try{
                v.WstawDane(v.getNextIDVal());
                vertDict.insert(pair<ID, T>(nextID,v));
                done = true;
            }
            catch(...)
            {}
        }while(!done);
        ++nextID;
        return nextID-1;
    }
public:
    graph(){
        nextID = 1;
        vertDict.clear();
    };

    ID addVertex(T& v){
        return innerAddVertex(v);
    };

    ID addVertex(T v){
        return innerAddVertex(v);
    };

    ID glueTogether(ID from,ID into){
        vector<ID> inEdges,outEdges;
        vector<ID> vertList = getVertexIDList();
        int newPersons;
        float newTime;
        for(int i=0;i<vertList.size();++i){
            if(isEdge(vertList[i],from))
                inEdges.push_back(vertList[i]);
            if(isEdge(from,vertList[i]))
                outEdges.push_back(vertList[i]);
        };

        newTime = vertDict[from].getHoursAmmount()*vertDict[from].getPersonCount()+
                  vertDict[into].getHoursAmmount()*vertDict[into].getPersonCount();
        newPersons = vertDict[from].getPersonCount() + vertDict[into].getPersonCount();
        newTime /= newPersons;
        vertDict[into].setHoursAmmount(newTime);
        vertDict[into].setPersonCount(newPersons);
        remVertex(from);

        for(int i=0;i<inEdges.size();++i)
            if(inEdges[i]!=into)
                addEdge(inEdges[i],into);
        for(int i=0;i<outEdges.size();++i)
            if(outEdges[i]!=into)
                addEdge(into,outEdges[i]);

        return into;
    };

    void printStructure(){
        vector<ID> vert = getVertexIDList();
        cout<<"------------------------------------"<<endl;
        for(int i=0;i<vert.size();++i)
            cout<<vert[i]<<" ["<<vertDict[vert[i]].getPersonCount()<<';'<<
                                 vertDict[vert[i]].getHoursAmmount()<<']'<<endl;
        cout<<" ==="<<endl;
        for(int i=0;i<vert.size();++i)
            for(int j=0;j<vert.size();++j)
                if(isEdge(vert[i],vert[j]))
                    cout<<vert[i]<<"-->"<<vert[j]<<endl;
    };
    void remVertex(ID vertID){
        mapIter i = vertDict.begin();
        while(i!=vertDict.end()){
            remEdge(vertID,i->first);
            remEdge(i->first,vertID);
            i++;
        };
        vertDict.erase(vertID);
    };

    void addEdge(ID from,ID to){
        if((isEdge(from,to))||(from == to))
            return;

        edges.insert(edge(from,to));
    };

    void remEdge(ID from,ID to){
        edges.remove(edge(from,to));
    };

    bool isEdge(ID from,ID to){
        return edges.contains(edge(from,to));
    };

    vector<ID> getVertexIDList(void){
        mapIter i = vertDict.begin();
        vector<ID> returnVector;
        while( i != vertDict.end()){
            returnVector.push_back(i->first);
            i++;
        };
        return returnVector;
    };

    ID getSourceVertexID(){
        vector<ID> vertVect = getVertexIDList();
        ID sourceVert;
        int i,j;
        for(i=0;i<vertVect.size();++i){
            for(j=0;j<vertVect.size();++j){
                if(isEdge(vertVect[j],vertVect[i]))
                    break;
            }
            if(j>=vertVect.size()){
                sourceVert = vertVect[i];
                break;
            };
        };
        return sourceVert;
    };
    vector<ID> getOutVertID(ID from){
        vector<ID> vertVect = getVertexIDList(), result;
        for(int i = 0;i < vertVect.size();++i){
            if(vertVect[i]!=from)
                if(isEdge(from,vertVect[i]))
                    result.push_back(vertVect[i]);
        };
        return result;
    };
    vector<ID> getInVertID(ID to){
        vector<ID> vertVect = getVertexIDList(), result;
        for(int i = 0;i < vertVect.size();++i){
            if(vertVect[i]!=to)
                if(isEdge(vertVect[i],to))
                    result.push_back(vertVect[i]);
        };
        return result;
    };

    graph(int vertNr,int pplMin = 1,int pplMax = 50,float timeMin = 1,float timeMax = 100);
    vector<ID> getCriticalPath(void);
};

template <typename T>
graph<T>::graph(int vertCnt,int pplMin,int pplMax,float timeMin,float timeMax){
    int timeMin100=100*(int)timeMin, timeMax100=100*(int)timeMax;
    vector<ID> layer1,layer2,allID;
    random R;

    int curLayerVertCnt,tmpInd,additionalEdgesCount;
    int rnd1,rnd2;
    ID sourceID, destinationID, curID;
//sytuacje wyjatkowe
    if(vertCnt < 1)
        return;
    if(vertCnt == 1){
        addVertex(T(R(pplMin,pplMax),R(timeMin100,timeMax100)));
        return;
    };
    sourceID = addVertex(T(R(pplMin,pplMax),0.01*R(timeMin100,timeMax100)));
    destinationID = addVertex(T(R(pplMin,pplMax),0.01*R(timeMin100,timeMax100)));
    allID.push_back(sourceID);
    allID.push_back(destinationID);

    if(vertCnt == 2){
        addEdge(sourceID,destinationID);
        return;
    };
    vertCnt -= 2;

    layer1.clear();
    layer2.clear();
//wstawiamy jako warstwe wierzcholek zrodlowy zeby w pierwszej iteracji polaczyc go z wszystkimi
//wierzcholkami z pierwszej warstwy
    layer2.push_back(sourceID);
//ukladamy kolejne warstwy
    while(vertCnt >0){
        layer1 = layer2;
        layer2.clear();
        curLayerVertCnt = R(1,vertCnt);
        vertCnt -= curLayerVertCnt;
//losujemy wierzcholki w dodawanej warstwie
        for(int i = 0;i<curLayerVertCnt;++i){
            curID = addVertex(T(R(pplMin,pplMax),0.01*R(timeMin100,timeMax100)));
            layer2.push_back(curID);
            allID.push_back(curID);
        };
//upewniamy sie zeby kazdy wierzcholek z warstwy nizszej mial polaczenie z jakims z wyzszej
        for(unsigned int i = 0;i<layer1.size();++i){
            tmpInd = R(0,layer2.size()-1);
            addEdge(layer1[i],layer2[tmpInd]);
        };
//upewniamy sie aby do kazdego wierzcholka z warstwy wyzszej dochodzila jakas krawedz z nizszej warstwy
        for(unsigned int i = 0;i<layer2.size();++i){
            tmpInd = R(0,layer1.size()-1);
            addEdge(layer1[tmpInd],layer2[i]);
        };
    };
//laczymy kazdy wierzcholek z ostatniej warstwy z wierzcholkiem docelowym
    for(unsigned int i = 0;i<layer2.size();++i)
        addEdge(layer2[i],destinationID);

    additionalEdgesCount = R(0,vertCnt*(vertCnt-1)/2);
    for(int i = 0;i<additionalEdgesCount;++i){
        rnd1 = R(0,allID.size()-1);
        rnd2 = R(rnd1+1,allID.size()-1);
        addEdge(allID[rnd1],allID[rnd2]);
    };
};
template <typename T>
vector<ID> graph<T>::getCriticalPath(void){
    vector<ID> criticalPath;
    vector<ID> nextVerts;
    map<ID, float> weights;
    list<ID> q;
    ID currentVert;

    nextVerts = getVertexIDList();
    for(int i = 0;i<nextVerts.size();++i)
        weights[nextVerts[i]] = vertDict[nextVerts[i]].getHoursAmmount();
    nextVerts.clear();

    q.push_back(getSourceVertexID());
    while(!q.empty()){
        currentVert = q.front();
        q.pop_front();
        nextVerts = getOutVertID(currentVert);
        for(int i = 0;i < nextVerts.size(); ++i)
            q.push_back(nextVerts[i]);
        for(int i=0;i<nextVerts.size();++i){
            if(weights[nextVerts[i]]<vertDict[nextVerts[i]].getHoursAmmount()+vertDict[currentVert].getHoursAmmount())
                weights[nextVerts[i]] = vertDict[nextVerts[i]].getHoursAmmount()+vertDict[currentVert].getHoursAmmount();
        };
    };
    criticalPath.push_back(currentVert);
    nextVerts = getInVertID(currentVert);
    while(!nextVerts.empty()){
        ID maxVert = nextVerts[0];
        float maxVal=weights[nextVerts[0]];
        for(int i = 1;i<nextVerts.size();++i)
            if( maxVal < weights[nextVerts[i]]){
                maxVal = weights[nextVerts[i]];
                maxVert = nextVerts[i];
            };
        criticalPath.push_back(maxVert);
        nextVerts = getInVertID(maxVert);
        reverse(criticalPath.begin(),criticalPath.end());
        return criticalPath;
    };
};

#endif // GRAPH_H_INCLUDED
