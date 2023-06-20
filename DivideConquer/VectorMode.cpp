#include <iostream>
#include <unordered_map>
#include <vector>

using namespace std;
typedef vector<pair<int,int>> vecPar;
/*
//esto puede reemplazar la función max
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
*/

//Importante! Funciona cuando está ordenado por el valor de elementos
//cuando se ingrese un vector que tenga diferentes valores, no los sumará y los tratará como elementos diferentes
//eg: {1,2},{5,5},{4,2},{2,13},{24,6},{3,4},{2,7},{3,9},{5,10}

void printAux(vecPar A)
{
        for(auto i: A)
            cout << i.first << "\t->\t" << i.second << endl;
}


vecPar vecModa(vecPar A)
{
    int max_freq = 0;
    vecPar resultado;

    // Encuentra la mayor frecuencia en el resultado
    for(auto p:A)
    {
        max_freq = max(max_freq,p.second);
    }

    // Crea un nuevo vector que solo contenga los valores con la mayor frecuencia
    for(auto p : A)
    {
        if(p.second == max_freq)
            resultado.push_back(p);
    }

    cout << "Resultado parcial:\n";
    printAux(resultado);

    return resultado;
}

vecPar moda(vecPar A)
{
    vecPar resultado;
    if(A[0].first == A[1].first)
    {
        resultado.emplace_back(A[0].first,A[0].second + A[1].second);
        return resultado;
    }
    return A;
}

vecPar moda(vecPar A, vecPar B)
{
    vecPar resultado;
    int i = 0, j = 0;

    while(i < A.size() && j < B.size())
    {
        //por lo general no se va a usar, no está preparada su implementación de esta forma
        // si los elementos son iguales
        if(A[i].first == B[j].first)
        {
            //si lo son se suman las frecuencias
            resultado.emplace_back(A[i].first, A[i].second + B[j].second);
            i++;
            j++;
        }
        
        // si A tiene mayor frecuencia que B
        else if(A[i].second > B[j].second)
        {
            resultado.push_back(A[i]);
            i++;
        }
        // lo contrario a lo anterior
        else if(B[j].second > A[i].second)
        {
            resultado.push_back(B[j]);
            j++;
        }
        // si son diferentes pero sus frecuencias son iguales
        // se mantienen y se pasa al siguiente
        else
        {
            resultado.push_back(A[i]);
            resultado.push_back(B[j]);
            i++;
            j++;
        }
    }
    //cuando solo queden valores en A
    while(i < A.size())
    {
        resultado.push_back(A[i]);
        i++;
    }
    //cuando solo queden valores en B
    while(j < B.size())
    {
        resultado.push_back(B[j]);
        j++;
    }

    return resultado;
}

vecPar calcModa(vecPar freq)
{
    int n = freq.size();
    if(n <= 1)
        return freq;
    if(n == 2)
    {
        return vecModa(moda(freq));
    }
    else
    {
        int m = n / 2;
        //partimos el vector
        vecPar A(freq.begin(), freq.begin() + m);
        vecPar B(freq.begin() + m, freq.end());

        cout << "Dividiendo el conjunto de datos en dos subconjuntos:" << endl;
        cout << "Subconjunto A:\n";
        printAux(A);
        cout << "Subconjunto B:\n";
        printAux(B);

        //llamamos de forma recursiva a calcModa
        A = calcModa(A);
        B = calcModa(B);

        cout << "Combinando los resultados de los dos subconjuntos:" << endl;
        //calculamos la moda
        vecPar resultado = moda(A,B);
        printAux(resultado);

        return vecModa(resultado);
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
    cout <<"-----------------------------------\n";
    cout << "La moda es:\n";
    printAux(resultado);

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

    
    vecPar ejemplo = {{1,2},{1,3},{6,8},{5,5},{4,2},{2,13},{24,6},{25,7},{3,4},
    {3,9},{3,3}};
    cout <<"-----------------------------------\n";
    showModa(ejemplo);
    
    return 0;
}