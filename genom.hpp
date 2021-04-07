#pragma once
#include <bits/stdc++.h>
using namespace std;
class Genom{
    private:
        vector<int> list;
        double eval;
    public:
        Genom(vector<int>,double);
        vector<int> getGenom();
        double getEval();
        void setGenom(vector<int>);
        void setEval(double);
};