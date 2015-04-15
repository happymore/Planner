#ifndef VOCABULARY_H
#define VOCABULARY_H

#include "structs.h"
#include <cstdio>
#include <vector>
#include <map>

using namespace std;
/*
 * 字符表类，保存各种信息
 */
class Vocabulary {
private:
    unsigned int AtomId;
    vector<char*> AtomList;
private:
    Vocabulary();
    ~Vocabulary();
    
public:
    static Vocabulary& instance();
    void DumpVocabulary(FILE* _out);
    void ShowVocabulary();
    int AddAtom(char*);
    int ApSize();
    char* GetAtom(int id);
    int QueryAtom(char*);
    void GetMap(map<int,string> &m1, map<string,int> &m2, int &l,map<string,vector<int> > &ground, map<int,int> &id);
};

#endif
