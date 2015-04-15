#ifndef ATOMS_H
#define	ATOMS_H


#include <iostream>
#include <string>
#include <string.h>
#include <vector>
#include <cstdio>
#include "structs.h"
#include "Vocabulary.h"
using namespace std;

class Atoms{
public:
    Atoms();
    ~Atoms();
    vector<string> AtomsName;
    int length;
    map<int,int> VocabularyNumToAtomNum;
public:
    
    static Atoms& instance();
    int QueryAtom(string);
    int AddAtom(string);
    string GetAtom_string(int);
    inline int AtomsLength() const { return length; }
    void show(FILE *out) const;
    void GenVocToAtom();
    int GetTrueNum(int);
};

#endif
