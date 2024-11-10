#include "galeshapley.hpp"

galeShapley::galeShapley(int n){
    
    tamanho = n;
    male_list = vector<vector<int>>(n,vector<int>(n,0));
    female_list = vector<vector<int>>(n,vector<int>(n,0));
    vector<vector<int>> temp(n,vector<int>(n,0));

    for(int i = 0; i < tamanho; i++)
        for(int j = 0; j < tamanho; j++){
            cin >> male_list[i][j];
        }

    for(int i = 0; i < tamanho; i++)
        for(int j = 0; j < tamanho; j++){
            cin >> temp[i][j];
        }

    for (int i = 0; i < tamanho; i++) {
        for (int j = 0; j < tamanho; j++) {
            int preferencia = temp[i][j];
            female_list[i][preferencia] = j;
        }
    }

}

void galeShapley::matching(){
    
    int doct;
    hosp Dmachs[tamanho], current;
    
    stack<hosp> pilha;
    for (int i = 0; i < tamanho; i++) {
        hosp h(i,0);
        pilha.push(h);
    }

    while (!pilha.empty()) {
        current = pilha.top();  // Obtém o elemento do topo
        pilha.pop();             // Remove o elemento do topo

        doct = male_list[current.hospital][current.preferencia++];
        if (Dmachs[doct].hospital == -1) {
            Dmachs[doct] = current;
            cout << "Entra: (" << Dmachs[doct].hospital << ", " << doct << ")" << endl;
        } else {
            if (female_list[doct][Dmachs[doct].hospital] > female_list[doct][current.hospital]) {
                pilha.push(Dmachs[doct]);
                cout << "Sai: (" << Dmachs[doct].hospital << ", " << doct << ")" << endl;
                Dmachs[doct] = current;
                cout << "Entra: (" << Dmachs[doct].hospital << ", " << doct << ")" << endl;
            }else{
                pilha.push(current);
            }
        }
    }
    cout << endl << "Final: " << endl;
    for (int i = 0; i < tamanho; i++) {
        cout << "(" << Dmachs[i].hospital << ", " << i << ")" << endl;
    }
}