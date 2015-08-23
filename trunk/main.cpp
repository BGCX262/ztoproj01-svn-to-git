#include <iostream>
#include <vector>
#include <map>
#include <cstdlib>
#include <time.h>
#include <list>
#include "random.h"
#include "exceptions.h"
#include "edge.h"
#include "vertex.h"
#include "graph.h"
#include "sortedList.h"
#include "baza.h"


///TODO:
/// - troche pozmienialem - przesunalem copy do sekcji private, usunalem try/catch i wyrzucilem
///   obowiazek try / catch na uzytkownikow klasy.. jest kilka komentarzy..
/// - oczywiscie cale mnostwo dziwnych rzeczy wyspecyfikowanych przez mistrza Prowadzacego... -UAEOJ :/

///Zasadnicze zmiany:
/// - naprawi³am nazwy wyj¹tków i dodalam klasy wyjatkow (konstruktor, assign(ment) :P, insert i select)
///     wszystkie w nag³owku exceptions.h
/// - do³ozy³am baze danych (baza.h)
/// - dolozylam do klasy vertex metody wstaw i pobierz dane (vertex korzysta z baza.h)
/// - dolozylam magiczna templatowa metode/funkcje to_string w exceptions.h

///Doskonala robota :)
/// - zastanawiam sie czy sorted list jest potrzebna.. :/ zobaczymy.. narazie niech zostanie skoro juz jest..
///   chodzi mi o to ze w tej chwili jej wykorzystanie wcale nie przyspiesza dzialania programu.. trzeba by
///   wstawic przeszukiwanie z logarytmicznym czasem.. ale to nie jest priorytet teraz.. w weekend postaram
///   sie przysiedziec wieczorami i porobic te rzeczy ktore sa mi przydzielone.. moze nawet w piatek..
/// - do czego sluzy ta wspaniala mega wypasiona metoda to_string??


///Co zmienilem:
/// - klasa edge ma calkowicie nowe i superasne operatory do porownywania.. po prostu boskie <lol>
/// - wypelnilem troche klase graph (dodawanie krawedzi i wierzcholkow) chwilowo bez czytajZBazy czy jak to tam
///Ogolne przemyslenia:
/// - przy obecnym ukladzie trudno bedzie zapewnic sortowanie listy (ktore nie jest w zasadzie konieczne)
///   krawedzi przy zmianach w krawedziach.. chociaz jesli to dobrze obudowac w graph to zadziala..
/// - trzeba wymyslic w jaki sposob chcemy zaprezentowac dzialanie kodu czyli co bedzie robic program..

using namespace std;

static void setPr()
{
    int p;
    cout << "Podaj prawdopodobieñstwa:" << endl;
    cout << "konstruktor kopiuj¹cy: ";

    cin >> p;
    ctorException().setProbability(p);

    cout << endl << "operator przypisania: ";
    cin >> p;
    assignException().setProbability(p);

    cout << endl << "operacja insert: ";
    cin >> p;
    insertException().setProbability(p);

    cout << endl << "operacja select: ";
    cin >> p;
    selectException().setProbability(p);
}

static void clearCount()
{
    ctorException().resetCount();
    assignException().resetCount();
    insertException().resetCount();
    selectException().resetCount();
}

static void printResult()
{
     cout<<endl<<"------------------------------------"<<endl;
    cout << "PODSUMOWANIE:" << endl;
    cout << "Wyjatek konstruktora: " << to_string(ctorException().getCount()-1) << endl;
    cout << "Wyjatek operacji przypisania: " << to_string(assignException().getCount()-1) << endl;
    cout << "Wyjatek bazy - operacja insert: " << to_string(insertException().getCount()-1) << endl;
    cout << "Wyjatek bazy - operacja select: " << to_string(selectException().getCount()-1) << endl;
}

int main()
{
    graph<vertex> G(8,2,50,1,88.5);
    G.printStructure();
    G.glueTogether(G.getVertexIDList()[0],G.getVertexIDList()[2]);
    cout<<"PO SKLEJENIU:"<<endl;
    G.printStructure();

    G.remVertex(G.getVertexIDList()[2]);
    cout<<"PO USUNIECIU:"<<endl;
    G.printStructure();

    G.getCriticalPath();

    setPr();
    clearCount();
    graph<vertex> H(20,2,50,1,88.5);
    printResult();
    clearCount();
    graph<vertex> I(50,2,50,1,88.5);
    printResult();
    clearCount();
    graph<vertex> J(100,2,50,1,88.5);
    printResult();
    return 0;
}
