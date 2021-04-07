#include <bits/stdc++.h>
#include "genom.hpp"
#include "Random.hpp"
using namespace std;
//遺伝子情報の長さ
int GENOM_LENGTH = 100;
//遺伝子集団の大きさ
int MAX_GENOM_LIST = 100;
//遺伝子選択数
int SELECT_GENOM = 20;
//個体突然変異確率 @GitHubに上げたコードでは0.1の10%になってます
double INDIVIDUAL_MUTATION = 0.01;
//遺伝子突然変異確率 @GitHubに上げたコードでは0.1の10%になってます
double GENOM_MUTATION = 0.01;
//繰り返す世代数
int MAX_GENERATION = 40;


Genom createGenom();
Genom evaluation(Genom);
vector<Genom> select(Genom,int);
Genom crossover(Genom, Genom);
vector<Genom> createNextGene(vector<Genom>,vector<Genom>, vector<Genom>);



Genom createGenom(){
    Rand::Random rand;
    vector<int> temp(GENOM_LENGTH);
    for(int i = 0; i < GENOM_LENGTH; i++){
        temp[i] = rand.RandInt(0,1);
    }
    return Genom(temp,0);
}

Genom evaluation(Genom genom){
    int val = 0;
    vector<int> eval = genom.getGenom(); 
    for(int i = 0; i < GENOM_LENGTH; i++){
        if(eval[i] == 1)
            val++;
    }
    genom.setEval((double)val/GENOM_LENGTH);
    return genom;
}

