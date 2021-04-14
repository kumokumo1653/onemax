#include <bits/stdc++.h>
#include "genom.hpp"
#include "Random.hpp"
using namespace std;
//遺伝子情報の長さ
int GENOM_LENGTH = 10;
//遺伝子集団の大きさ
int MAX_GENOM_LIST = 10;
//遺伝子選択数
int SELECT_GENOM = 5;
//個体突然変異確率 
double INDIVIDUAL_MUTATION = 0.01;
//遺伝子突然変異確率 
double GENOM_MUTATION = 0.01;
//繰り返す世代数
int MAX_GENERATION = 5;

Rand::Random r;

Genom createGenom();
double evaluation(Genom);
vector<Genom> select(vector<Genom>,int);
vector<Genom> crossover(Genom, Genom);
vector<Genom> createNextGene(vector<Genom>,vector<Genom>, vector<Genom>);
void  mutation(vector<Genom> &, double, double);

int main (void) {
    vector<Genom> currentGroup(MAX_GENOM_LIST);
    vector<Genom> nextGroup(MAX_GENOM_LIST);

    for(int i = 0; i < MAX_GENOM_LIST;i++){
        currentGroup[i] = createGenom();
    }

    for (int j = 0;j < MAX_GENERATION; j++){

        //現行遺伝子の評価
        for(int i = 0; i < MAX_GENOM_LIST; i++){
            double result = evaluation(currentGroup[i]);
            currentGroup[i].setEval(result);
        }

        //エリート集団の選択
        vector<Genom> elites = select(currentGroup, SELECT_GENOM);

        vector<Genom> progeny;
        //エリート集団の交叉
        for(int i = 1; i < SELECT_GENOM; i++){
            vector<Genom> temp;
            temp = crossover(elites[i - 1], elites[i]);
            progeny.push_back(temp[0]);
            progeny.push_back(temp[1]);
        }


        //次世代を現行世代，エリート世代，子孫世代から作成
        nextGroup = createNextGene(currentGroup, elites, progeny);
        //全てに突然変異処理
        mutation(nextGroup, INDIVIDUAL_MUTATION, GENOM_MUTATION);


        //評価
        double min = 1;
        double max = 0;
        double avg = 0;
        for(int i = 0; i < MAX_GENOM_LIST;i++){
            min = min > currentGroup[i].getEval() ? currentGroup[i].getEval() : min;
            max = max < currentGroup[i].getEval() ? currentGroup[i].getEval() : max;
            avg += currentGroup[i].getEval();
        }
        avg /= MAX_GENOM_LIST;
        printf("----------------------------%d世代の結果---------------------------\n", j + 1);
        printf("min:%lf\n", min); 
        printf("max:%lf\n", max); 
        printf("avg:%lf\n", avg); 
    }
    return 0;
}

Genom createGenom(){
    vector<int> temp(GENOM_LENGTH);
    for(int i = 0; i < GENOM_LENGTH; i++){
        temp[i] = ::r.RandInt(0,1);
    }
    return Genom(temp,0);
}

double evaluation(Genom genom){
    int val = 0;
    vector<int> eval = genom.getGenom(); 
    for(int i = 0; i < GENOM_LENGTH; i++){
        if(eval[i] == 1)
            val++;
    }
    return ((double)val)/GENOM_LENGTH;
}

vector<Genom> select(vector<Genom> genom,int len){
    //降順ソート
    sort(genom.begin(), genom.end(), []( Genom &a,  Genom &b) {
        return a.getEval() > b.getEval();
    });

    vector <Genom> temp;
    for(int i = 0; i < len; i++){
        temp.push_back(genom[i]);
    }
    
    return temp;
}
vector<Genom> crossover(Genom a_genom, Genom b_genom){
    int cross1 = ::r.RandInt(0, GENOM_LENGTH);
    int cross2 = ::r.RandInt(cross1, GENOM_LENGTH);

    vector<int> a = a_genom.getGenom();
    vector<int> b = b_genom.getGenom();
    vector<int> cross_a;
    vector<int> cross_b;
    vector<Genom> temp;
    //cross1,cross2で遺伝子を分けて交叉
    for (int i = 0; i < cross1;i++){
        cross_a.push_back(a[i]);
        cross_b.push_back(b[i]);
    }
    for (int i = cross1; i < cross2;i++){
        cross_a.push_back(b[i]);
        cross_b.push_back(a[i]);
    }
    for (int i = cross2; i < GENOM_LENGTH;i++){
        cross_a.push_back(a[i]);
        cross_b.push_back(b[i]);
    }
    temp.push_back(Genom(cross_a, 0));
    temp.push_back(Genom(cross_b, 0));
    return temp;
}
//世代交代
vector<Genom> createNextGene(vector<Genom>genom,vector<Genom>elite, vector<Genom>progeny){
    
    //昇順ソート
    sort(genom.begin(), genom.end(), []( Genom &a,  Genom &b) {
        return a.getEval() < b.getEval();
    });

    //エリートと子孫の追加
    for(int i = 0; i < elite.size() + progeny.size();i++){
        if(i < elite.size())
            genom[i] = elite[i];
        else
            genom[i] = progeny[i - elite.size()];
    }
    return genom;

}
//突然変異
void  mutation(vector<Genom> &genom, double individual_rate, double genom_rate){

    for (int i = 0; i < genom.size();i++){
        //確率で突然変異
        if(::r.RandBool(individual_rate)){
            
            vector <int> gene = genom[i].getGenom();
            for(int j = 0; j < gene.size(); j++){
                if(::r.RandBool(genom_rate)){
                    gene[i] = ::r.RandInt(0,1);
                }
            }

            genom[i].setGenom(gene);
            genom[i].setEval(evaluation(genom[i]));
        } 
        
    }

}