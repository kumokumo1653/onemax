#include "genom.hpp"

Genom::Genom(){}
Genom::Genom(vector<int> list, double eval){
    Genom::eval = eval;
    Genom::list = list;
}

vector<int> Genom::getGenom() {
    return list;
}
double Genom::getEval(){
    return eval;
}
void Genom::setGenom(vector<int>list){
    Genom::list = list;
}
void Genom::setEval(double eval){
    Genom::eval = eval;
}