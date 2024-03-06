#include "Dictionar.h"
#include <iostream>
#include "IteratorDictionar.h"

///CONSTRUCTOR
//COMPLEXITATE
//Best O(capacitate)
//Worst O(capacitate)
//Overall O(capacitate)
Dictionar::Dictionar() {
    capacitate = 100;
    size = 0;
    primLiber = 0;
    elemente = new TElem[capacitate];
    urmator = new int[capacitate];
    precedent = new int[capacitate];
    prim = -1;
    for (int i = 0; i < capacitate; i++)
        urmator[i] = i + 1;
    urmator[capacitate - 1] = -1;
    for (int i = 0; i < capacitate; i++)
        precedent[i] = i - 1;
    precedent[0] = -1;

}

Dictionar::~Dictionar() {
    delete[] elemente;
    delete[] urmator;
    delete[] precedent;
}

//COMPLEXITATE
//Best O(1) cand perechea cheie-valoare exista deja in dictionar
//Worst O(n) cand perechea cheie-valoare nu exista in dictionar
//Overall theta(n)
TValoare Dictionar::adauga(TCheie c, TValoare v) {
    //Adaugam o pereche (cheie, valoare) in dictionar.
    //Daca exista deja cheia in dictionar, inlocuieste valoarea asociata cheii si returneaza vechea valoare.
    //Daca nu exista cheia, adauga perechea si returneaza null: NULL_TVALOARE.
    int i = prim;
    while (i != -1 && elemente[i].first != c)
        i = urmator[i];
    if (i != -1) {
        TValoare old = elemente[i].second;
        elemente[i].second = v;
        return old;
    }
    else {
        if (primLiber == -1)
            redimensionare();
        int j = primLiber;
        primLiber = urmator[primLiber];
        elemente[j].first = c;
        elemente[j].second = v;
        urmator[j] = prim;
        precedent[j] = -1;
        if (prim != -1)
            precedent[prim] = j;
        prim = j;
        size++;
        return NULL_TVALOARE;
    }

}



//COMPLEXITATE
//Best O(1)
//Worst O(n)
//Overall theta(n)
//cauta o cheie si returneaza valoarea asociata (daca dictionarul contine cheia) sau null
TValoare Dictionar::cauta(TCheie c) const {
    int i = prim;
    while (i != -1 && elemente[i].first != c)
        i = urmator[i];
    if (i != -1)
        return elemente[i].second;
    else
        return NULL_TVALOARE;
}


//COMPLEXITATE
//Best O(1)
//Worst O(n)
//Overall theta(n)
TValoare Dictionar::sterge(TCheie c) {
    //Sterge o cheie si returneaza valoarea asociata (daca exista) sau null: NULL_TVALOARE.
    int i = prim;
    while (i != -1 && elemente[i].first != c)
        i = urmator[i];
    if (i != -1) {
        TValoare old = elemente[i].second;
        if (precedent[i] == -1)
            prim = urmator[i];
        else
            urmator[precedent[i]] = urmator[i];
        if (urmator[i] != -1)
            precedent[urmator[i]] = precedent[i];
        urmator[i] = primLiber;
        primLiber = i;
        size--;
        return old;
    }
    else
        return NULL_TVALOARE;

}


int Dictionar::dim() const {
    //returneaza numarul de perechi (cheie, valoare) din dictionar
    return size;
}

bool Dictionar::vid() const {
    //verifica daca dictionarul e vid
    return size == 0;
}


IteratorDictionar Dictionar::iterator() const {
    return  IteratorDictionar(*this);
}

//COMPLEXITATE
//Best O(n)
//Worst O(n)
//Overall O(n)
//Un array pt perechile cheie-valoare si 2 array uri auxiliare pentru a tine legatura dintre perechi
//Se copiaza perechile si legaturile dintre ele in noul array
//Setez  urmatorul element liber la primul element nou, iar precedentul element vechi il setez la -1
void Dictionar::redimensionare() {
    TElem* elementeNou = new TElem[capacitate * 2];
    int* urmatorNou = new int[capacitate * 2];
    int* precedentNou = new int[capacitate * 2];
    for (int i = 0; i < capacitate; i++)
        elementeNou[i] = elemente[i];
    for (int i = 0; i < capacitate; i++)
        urmatorNou[i] = urmator[i];
    for (int i = 0; i < capacitate; i++)
        precedentNou[i] = precedent[i];

    for (int i = capacitate; i < capacitate * 2; i++)
        urmatorNou[i] = i + 1;
    urmatorNou[capacitate * 2 - 1] = -1;
    for (int i = capacitate; i < capacitate * 2; i++)
        precedentNou[i] = i - 1;
    precedentNou[capacitate] = -1;
    primLiber = capacitate;
    capacitate = capacitate * 2;
    delete[] elemente;
    delete[] urmator;
    delete[] precedent;
    elemente = elementeNou;
    urmator = urmatorNou;
    precedent = precedentNou;

}

int Dictionar::aloca() {
    int i = primLiber;
    primLiber = urmator[primLiber];
    return i;
}

void Dictionar::dealoca(int i) {
    urmator[i] = primLiber;
    primLiber = i;
}

//COMPLEXITATE
//Best O(1)
//Worst O(n)
//Overall O(n)
//daca nu am un index liber, fac redimensionare
//perechea cheie-valoare o stochex in index, iar urmator si precedent le setez la -1
int Dictionar::creeazaNod(TElem e) {
    int i = aloca();
    if (i == -1)
        redimensionare();
    elemente[i] = e;
    urmator[i] = -1;
    precedent[i] = -1;
    return i;
}

//FCT NOUA
//COMPLEXITATE
//overall theta(n) parcurge mereu tot
//pseudocod
/*algoritm filtreaza(Conditie cond)
*  int i;
*  i<-prim
*  cat timp i!=-1 executa
*   daca(!cond(elemente[i].first)) atunci
*     i<-sterge(elemente[i].first)
*   altfel i<-urmator[i]
*   sfd
*  sfc
* sfa
 */

void Dictionar::filtreaza(Conditie cond)
{
    int i = prim;
    while (i != -1) {
        if (!cond(elemente[i].first))
            i = sterge(elemente[i].first);
        else
            i = urmator[i];
    }
}
