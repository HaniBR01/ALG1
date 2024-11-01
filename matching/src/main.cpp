#include <iostream>
#include <stack>

using namespace std;

struct hosp{
    int pref [];
    int index;

}typedef hosp;

int main(){
    int hosp_list[][] = {{0,4,1,2,3},
                {2,1,4,3,0},
                {4,1,3,2,0},
                {0,3,1,4,2},
                {4,3,2,1,0}};

    hosp hosp_list_Q[5];
    for(int i = 0;i<5;i++){
        hosp_list_Q[i].pref = hosp_list[i];
        hosp_list_Q.index = 0;
    }

    int doct_list[][] = {{0,4,1,2,3},
                {2,1,4,3,0},
                {4,1,3,2,0},
                {0,3,1,4,2},
                {4,3,2,1,0}};
    
    int doct_list_T[5][5];
    for(int i=0;i<5;i++)
        for(int j=0;j<5;j++){
            preferencia = doct_list[i][j];
            doct_list_T[i][preferencia] = j;
        }

    int Dmachs[5] = {-1};

    stack<int> pilha;
    for(int i = 0; i<5; i++){
        pilha.push(i);
    }
    
    int current,doct;

    while(!pilha.empty()){
        current = pilha.pop();
        doct = hosp_list_Q[current].pref[hosp_list_Q.index++];
        if(Dmachs[doct]==-1){
            Dmachs[doct] = current;
        }else{
            if(doct_list_T[doct][Dmachs[doct]] > doct_list_T[doct][current]){
                pilha.push(Dmachs[doct]);
                Dmachs[doct] = current;
            }
        }
    }

    for(int i=0; i<5; i++){
        cout << "(" << Dmachs[i] << "," << i << ")" << endl;
    }

    return 0;
}