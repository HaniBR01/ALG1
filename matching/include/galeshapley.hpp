#ifndef GALESHAPLEY_HPP
#define GALESHAPLEY_HPP

#include<iostream>
#include<stack>
#include<vector>

using namespace std;

struct hosp {
    int hospital;
    int preferencia;

    hosp() : hospital(-1), preferencia(0) {}
    hosp(int h, int p) : hospital(h), preferencia(p) {}

};

class galeShapley{
    private:
        int tamanho;
        vector<vector<int>> male_list;
        vector<vector<int>> female_list;
    
    public:
        galeShapley(int n);
        void matching();
};

#endif