#include <iostream>
#include <unordered_map>
#include <vector>
#include <algorithm>

using namespace std;
typedef vector<pair<int,int>> vecPar;

vecPar moda(vecPar A, vecPar B)
{
    vecPar resultado;
    int i = 0, j = 0;
    while(i < A.size() && j < B.size())
    {
        if(A[i].first == B[j].first)
        {
            resultado.emplace_back(A[i].first, A[i].second + B[j].second);
            i++;
            j++;
        }
        else if(A[i].first < B[j].first)
        {
            resultado.push_back(A[i]);
            i++;
        }
        else
        {
            resultado.push_back(B[j]);
            j++;
        }
        cout << "La moda vecParcial:\n";
        for(auto i: resultado)
            cout << i.first << "\t->\t" << i.second << endl;
    }
    while(i < A.size())
    {
        resultado.push_back(A[i]);
        i++;
        cout << "La moda vecParcial:\n";
        for(auto i: resultado)
            cout << i.first << "\t->\t" << i.second << endl;
    }
    while(j < B.size())
    {
        resultado.push_back(B[j]);
        j++;
        cout << "La moda vecParcial:\n";
        for(auto i: resultado)
            cout << i.first << "\t->\t" << i.second << endl;
    }

    cout << "La moda vecParcial:\n";
        for(auto i: resultado)
            cout << i.first << "\t->\t" << i.second << endl;
    
    return resultado;
}


vecPar calcModa(vecPar freq)
{
    int n = freq.size();
    if(n <= 1)
        return freq;
    else
    {
        int m = n / 2;
        vecPar A(freq.begin(), freq.begin() + m);
        vecPar B(freq.begin() + m, freq.end());
        vecPar result = moda(A,B);
        
        // Encuentra la mayor frecuencia en el resultado
        int max_freq = 0;
        for(auto p : result)
            max_freq = max(max_freq, p.second);
        
        // Crea un nuevo vector que solo contenga los valores con la mayor frecuencia
        vecPar final_result;
        for(auto p : result)
        {
            if(p.second == max_freq)
                final_result.push_back(p);
        }
        
        return final_result;
    }
}

void showModa(vecPar freq)
{
    cout << "Elemento->Frecuencia" <<endl;
    
    for(auto i:freq)
    {
        cout << i.first << "\t->\t" << i.second << endl;
    }

    vecPar resultado = calcModa(freq);
    cout << "La moda es:\n";
    for(auto i: resultado)
    {
        cout << i.first << "\t->\t" << i.second << endl;
    }

}

int main()
{
    vector<int> numeros = {2,2,7,2,4,1,3,9,8,5,8,6,7,2,5};
    unordered_map<int,int> aux;

    for(int num: numeros)
    {
        aux[num]++;
    }
    vecPar freq;
    
    for(auto tmp:aux) 
    {
        freq.push_back(tmp);
    }

    showModa(freq);

    vecPar ejemplo = {{1,2},{5,5,},{4,2},{2,13},{24,6},{25,7},{3,4},
    {3,9}};
    cout <<"-----------------------------------\n";
    showModa(ejemplo);
    return 0;
}