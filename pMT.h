#pragma once

#include "bTREE.h"
#include <string>
using namespace std;

#ifndef pMT_H
#define pMT_H

class pMT
{
private:
    int selectedHash;
    bTREE myMerkle;

    string hash_1(string);
    string hash_2(string);
    string hash_3(string);

    bool inorderSearch(bTREE::treeNode * tree, string, int, bool&);

    int counterFind;

    void overloadedCaratHelper(pMT&, bTREE::treeNode*, pMT&);

public:
    void helper2(pMT&, pMT&, pMT&);
    
    pMT(int hashSelect);
    ~pMT();

    int insert(string, int);

    int find(string, int, int);
    int findHash(string);

    string locateData(string);
    string locateHash(string);

    void rehash(bTREE::treeNode * tree);

    friend bool operator==(const pMT& lhs, const pMT& rhs);

    friend bool operator!=(const pMT& lhs, const pMT& rhs);

    friend pMT operator^(pMT& lhs, pMT& rhs);

    friend std::ostream& operator<<(std::ostream& out, const pMT& p);

};

#endif
