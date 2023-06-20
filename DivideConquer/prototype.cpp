#include <iostream>
#include <unordered_map>
#include <vector>

using namespace std;

typedef pair<vector<int>,vector<int>> par;

par moda(par A, par B)
{
    par result;
    int i = 0, j = 0;
    while(i < A.first.size() && j < B.first.size())
    {
        if(A.first[i] == B.first[j])
        {
            result.first.push_back(A.first[i]);
            result.second.push_back(A.second[i] + B.second[j]);
            i++;
            j++;
        }
        else if(A.second[i] > B.second[j])
        {
            result.first.push_back(A.first[i]);
            result.second.push_back(A.second[i]);
            i++;
        }
        else if(B.second[j] > A.second[i])
        {
            result.first.push_back(B.first[j]);
            result.second.push_back(B.second[j]);
            j++;
        }
        else
        {
            i++;
            j++;
        }
    }
    while(i < A.first.size())
    {
        result.first.push_back(A.first[i]);
        result.second.push_back(A.second[i]);
        i++;
    }
    while(j < B.first.size())
    {
        result.first.push_back(B.first[j]);
        result.second.push_back(B.second[j]);
        j++;
    }
    return result;
}

int findMax(vector<int> v)
{
    int max_val = v[0];
    for(int i = 1; i < v.size(); i++)
    {
        if(v[i] > max_val)
            max_val = v[i];
    }
    return max_val;
}

par calcModa(par freq)
{
    int n = freq.first.size();
    if(n<=1)
        return freq;
    else
    {
        int m = n/2;
        par A,B;
        A.first.assign(freq.first.begin(),freq.first.begin()+m);
        A.second.assign(freq.second.begin(),freq.second.begin()+m);
        B.first.assign(freq.first.begin()+m,freq.first.end());
        B.second.assign(freq.second.begin()+m,freq.second.end());
        par result = moda(A,B);
        
        // Encuentra la mayor frecuencia en el resultado
        int max_freq = findMax(result.second);
        
        // Crea un nuevo par que solo contenga los valores con la mayor frecuencia
        //si se quita y solo se devuelve result, tendremos todas las frecuencias
        par final_result;
        for(int i = 0; i < result.first.size(); i++)
        {
            if(result.second[i] == max_freq)
            {
                final_result.first.push_back(result.first[i]);
                final_result.second.push_back(result.second[i]);
            }
        }
        
        return final_result;
    }
}

int main()
{
    vector<int> numeros = {2,2,7,5,4,1,3,9,8,5,8,6,7,2,5};
    unordered_map<int,int> aux;

    for(int num: numeros)
    {
        aux[num]++;
    }
    par freq;
    
    for(auto tmp:aux) 
    {
        freq.first.push_back(tmp.first);
        freq.second.push_back(tmp.second);
    }
    
    par resultado = calcModa(freq);
    cout << "La moda es:\n";
    for(int i=0;i<resultado.first.size();i++)
    {
        cout << resultado.first[i] << ": ";
        cout << resultado.second[i] << endl;
    }
}

/*
    //Implementación alternativa usando biblioteca algorithm
    transform(aux.begin(), aux.end(), back_inserter(freq.first), [](const auto& p){ return p.first; });
    transform(aux.begin(), aux.end(), back_inserter(freq.second), [](const auto& p){ return p.second; });
*/