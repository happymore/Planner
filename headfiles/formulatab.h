#include "structs.h"
#include <vector>

#ifndef FORMULATAB_H
#define	FORMULATAB_H

class Formulatab {
private:
    vector<_formula*> FormulaList;
private:
    Formulatab();
    ~Formulatab();
    
public:
    static Formulatab& instance();
    int AddFormula(_formula*);
    _formula* GetFormula(int id);
    vector<_formula*> GetFormulaList() const;
};




#endif	/* FORMULATAB_H */

