#include <exception>
#include "IteratorDictionar.h"
#include "Dictionar.h"

using namespace std;

//constructorul primeste o referinta catre Container
//iteratorul va referi primul element din container
IteratorDictionar::IteratorDictionar(const Dictionar& d) : dict(d) {
    curent = dict.prim;
}

//reseteaza pozitia iteratorului la inceputul containerului
void IteratorDictionar::prim() {
    curent = dict.prim;
}

//muta iteratorul in container
   // arunca exceptie daca iteratorul nu e valid
void IteratorDictionar::urmator() {
    if (!valid())
        throw std::exception();
    curent = dict.urmator[curent];
}


//returneaza valoarea elementului din container referit de iterator
   //arunca exceptie daca iteratorul nu e valid
TElem IteratorDictionar::element() const {
    if (!valid())
        throw std::exception();
    return dict.elemente[curent];
}


bool IteratorDictionar::valid() const {
    return curent != -1;
}
