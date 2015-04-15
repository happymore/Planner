#ifndef INIT_H
#define	INIT_H

#include  <map>
#include <string>
#include "formulatab.h"
#include "structs.h"
#include "Vocabulary.h"
#include "Progression.h"
#include <string.h>

extern FILE *yyin;

extern _formula* init_f;
extern _formula* goal_f;
extern vector<_formula*> actions_f; 
//例化原子中原子号和类型的对照
extern map< string,vector<int> > grounding_map;
extern vector<OnticAction> ontic_actions;
extern vector<EpisAction> epis_actions;

extern int yyparse();

class Init{
public:
    Init();
    ~Init();
    
    void Exec(const char *domain, const char *p);//执行生成动作
    
    void GenActions();
    void GenOnticActions(const _formula*);//生成物理动作
    void GenObserveActions(const _formula*);//生成感知动作
    //通过前提公式获得pre类型前提，此类型为中间量目标是生成epis_CNF的前提条件
    pre GenPrecondition(const _formula*);
    //功能同上，适应例化中带变量，匹配生成新原子的情况
    pre GenPreconditionByMatch(const _formula*, const vector<string> &para_str, const vector<string> &match_str);
    //从公式获取感知动作效果
    vector<int> GenObserverActionEffect(const _formula*);
    vector<int> GenObserverActionEffectByMatch(const _formula* f, const vector<string> &para_str, const vector<string> &match_str);
    //从公式获取物理动作效果，三元组形式
    vector<ConEffect> GenConEffect(const _formula* f);
    vector<ConEffect> GenConEffectByMatch(const _formula* f, const vector<string> &para_str, const vector<string> &match_str);
   //获取该原子公式对应的原子，此处生成原子，存在单例atoms类中返回一个原子序号
    int GenAtomNumByState(_formula*);
    //获取该原子公式对应的用atoms中原子序号表示的vector<int>
    int GenVariableAtomNumByState(const _formula* f, const vector<string> &para_str, const vector<string> &match_str);
    _formula* GetVariableTypeMatchedFormula(const _formula* f, const vector<string> &para_str, const vector<string> &match_str);
    vector<int> GenVariableAtomNumVectorByState(const _formula* f, const vector<string> &para_str, const vector<string> &match_str);
    
	//生成变量类型的匹配映射
	void GetMatchStr(int pos, vector<string> &match_str, const vector<string> &para_str);
    bool IsUsedStr(string s, const vector<string> &v);//判断s是否在v中出现过
    string GetStrType(string s);//字符串识别，获取类型，字符串中'.'后面的部分
    bool MatchStringHead(char* a, string b);//匹配，a为b的头部即可匹配上
    bool CheckIfAddToVector(int i, const vector<int> &v);//判断是否已存在

    vector<int> GenAtomNums(const _formula* f);//建立当前公式里的原子在Atom中的对应关系，并返回其在Atom中的id集合。

    _formula* ConvertToCNF(_formula*& fml);//转换到CNF
    _formula* ConvertToDNF(_formula*& fml);//转换到DNF

    //原子号生成公式
    _formula* CompositeNumToAtom(int _atom_id);
	_formula* CompositeToAtomWithNega(int _atom_id);
	//组合两个公式
    _formula* CompositeByConnective(FORMULA_TYPE _formulaType, const _formula* _subformulaL, const _formula* _subformulaR);
    //复制，避免调用的时候修改了原公式
    _formula* copyFormula(const _formula* _fml);
	void DeleteFormula(_formula* _fml);
    
	//拆分CNF为子公式的vector,用以转化成目标结构体公式
	void DivideCNFFormula(const _formula* fml, vector<_formula*> &division);
    //拆分DNF为CNF公式的vector,用以转化成目标结构体公式
    void DivideDNFFormula(const _formula* fml, vector<_formula*> &division);
    //将vector<_formula*> 转换成 vector< set<int> > ,用以转化成目标结构体公式
    vector< set<int> > ConvertToVectorSetFormula(const vector<_formula*> &cnfDlp);
    //上面函数调用的子函数，每个公式转set<int>形式
    vector< set<int> > ConvertToDNFVectorSetFormula(const vector<_formula*> &cnfDlp);
    //上面函数调用的子函数,转化原子成int
    int ConvertAtomformulaToNum(const _formula* rule);
	//转化原子的CNF成set<int>
    void ConvertCNFformulaToNums(_formula* rule, set<int>& lits);

    //生成DNF或CNF后化简
    void Absorb(vector< set<int> >& l);
    //化简辅助函数，判断是否化简A
    int NeedToAbsorb(const set<int> &l1, const set<int> &l2);
    //检查是否存在自相矛盾，即1和-1并存，可消去
    bool CheckValue(const set<int> &l);
    
    //转换vector< set<int> >公式回到vector<_formula*>，用于K公式的数字化进行DNF之后再转换回公式
    vector<_formula*> VectorNumConvertToVectorFormula(vector< set<int> > l);
	//转换DNF的vector<_formula*>公式回到_formula*，用于K公式的数字化进行DNF之后再转换回公式
    _formula* VectorFormulaConvertToFormula(vector<_formula*> fl);

	EpisTerm GenEpisTerm(const _formula*);
    PropDNF GenPropDNF(const _formula*);
    //这里将cnf转成propterm，bitset中存储每个原子两个位置，
    //前一个表示正，后一个表示负，同1矛盾消去，同0表示此处该原子未被用
    PropTerm GetPropTerm(const set<int>&);
    PropTerm GetPropTermFromVector(const vector<int>&);

    //把中间类型pre生成episcnf的类型的前提
    EpisCNF GenEpisCNFByFormula(const _formula*);
    EpisClause GenEpisClausebyFormula(const _formula*);
    PropCNF GenPropCNFFromFormula(const _formula*);
    EpisCNF GetEpisCNF(pre);
	//此函数作用把EpisCNF具体每项里面的neg部分合并，
	//其实具体实现都只有一个neg，不需要进行合并，这里函数只转类型不合并
    EpisCNF DisDKCon(EpisCNF);

    EpisClause GenEpisClausePre(const vector<int> &, bool);
    void GenEpisiDNFInitAndGoal();
    void GenKDNFInit();
    vector<set<int> > Kand(const vector<set<int> > &vs);
    void GenActionPreCnd();
    //此处进行k后部分合取到dk后的操作，逻辑上的问题杨睿让这么写的
    void checkInit();
    
    vector<set<int> > GenDnfFromFormula(_formula*);
    vector<set<int> > GenDnfFromFormulaByVar(_formula* f, const vector<string> &para_str, const vector<string> &match_str);
    vector<set<int> > GenNegDnf(const vector<set<int> >&);
    PropDNF getPropDNFFromVS(const vector<set<int> >&);
    void ConvertConToPropTerm();
    void GenObaDnfAndNeg();
    void GenActConSingleNeg();
    void ShowGround(FILE *out)const;
    void ShowMaps(FILE *out) const;
    void Show(FILE *out, pre p)const;
    void Print_f(FILE *out, _formula* f) const;
    
    EpisDNF init;
    EpisCNF goal;
    vector<vector<string> > match_data;
};
#endif