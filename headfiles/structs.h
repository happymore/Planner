#ifndef STRUCTS_H
#define	STRUCTS_H

#define MAX_ATOM_LENGTH 512
#define MAX_ATOM_NUMBER 1024

#include <string>
#include <vector>
#include <set>

using namespace std;
// Type definition
////////////////////////////////////////////////////////////////////////////////

enum FORMULA_TYPE {
    STATE_F = 0,	//atom
    ONE_ATOM_STATE_F,
    VARS_F,
    VAR_F,
    NEGA_F,		//negation
    AND_F,
    OR_F,
    CONOBSERVE_F,
    OBSERVE_F,
    ACTION_F,
    PARAMETERS_F,
    PRECONDITION_F ,
    EFFECT_F,
    CONEFFECT_F,
    EMPTY_F,
    TRUE_F,
    FALSE_F,
    ONEOF_F,
    THREE_ATOM_F,
    THREE_ATOMS_F,
    THREE_ATOM_BEHIND_F,
    MULTI_THREE_ATOMS,
    K_F,
    DK_F,
    ACTION_CONTEXT_F,
    KATOM_F,
             
};

typedef struct __formula {
    FORMULA_TYPE formula_type;
    int count;
    union {
        __formula* subformula_l;   //NEGA,CONJ,DISJ,IMPL
        int pid;                 //ATOM
        int pidlist[11];
    };
    __formula* subformula_r;   //CONJ,DISJ,IMPL
}_formula;

struct pre {
    vector<int> k;
    vector<vector<int> > dk; 
};

enum SearchType {
    kHeuristic = 0,
    kDepthFirst = 1,
    kWidthFirst = 2,
};

enum STATE_TYPE {
    kToBeExplore = 0,
    kExplored,
    kDead,
    kGoal
};

//物理动作中的effect（效果三元组）
struct ConEffect
{
    vector<int> condition; //效果中的条件
    vector<int> add; //add集合存储的变量代表做完该动作之后，这些变量需要变为True
    vector<int> del; //del集合存储的变量代表做完该动作之后，这些变量需要变为False
};

//物理动作的描述
struct OnticAction
{
    string name; //动作的名称
    int act_num; //动作的编号
    EpisCNF pre_con; //动作执行的前置条件
    pre pre_f; //将前置条件转换为EpisCNF的承接存储
    vector<ConEffect> con_eff; //效果三元组
    vector<PropTerm> con; //use it to replace vector<int> condition
    vector<string> para_match;
};

//观察动作的描述
struct EpisAction
{
    string name; //动作的名称
    int act_num; //动作的编号
    EpisCNF pre_con; //动作执行的前置条件
    pre pre_f; //将前置条件转换为EpisCNF的承接存储
    vector<set<int> > observe; //需要观察的“公式”
    vector<string> para_match;

    PropDNF pos_res; //将所需要观察的“公式”化为DNF形式， 为了好做演进 positive result
    PropDNF neg_res; //将所需要观察的“公式”化为DNF形式， 为了好做演进 negative result  
};



//搜索算法中的结点
struct Node
{
    EpisDNF kb; //结点的知识库
    //下面两个变量分别是在搜索过程中所需要的两中标记
    STATE_TYPE flag;
    bool isolated;
    Node(){};
    Node(STATE_TYPE s, bool b, EpisDNF ed, int n){flag = s; isolated = b; kb = ed; /*num = n;*/};
    ~Node(){};
};

struct Transition
{
    int preNode; //前一个结点
    int nextNode;  //后一个结点
    bool isObserveAction; //是否为观察动作
    bool isTrue; //是否为感知动作的+
    int actionNumber;  //动作的编号
};

#endif

