#include <iostream>
#include <chrono>
#include <algorithm>
#include <vector>

using namespace std;

int main() {
    vector<int> sizes = {100, 200, 400, 800, 1600, 3200, 6400, 12800, 25600};
    cout << "[AVISO] -> Tiempo en segundos" << endl;
    cout << "[AVISO] -> valores de tiempo muy cercano a cero seran imprimidos en notacion cientifica" << endl;
    cout << "Dimension\tTiempo Bucle1\tTiempo Bucle2" << endl;
    
    for (int s = 0; s < sizes.size(); s++) {
        int MAX = sizes[s];        
        vector<vector<double>> matrix(MAX, vector<double>(MAX, 1.0));
        vector<double> vector_x(MAX, 1.0);
        vector<double> vector_y(MAX, 0.0);

        // Lambda para bucle1
        auto bucle1 = [&]() {
            auto start = chrono::high_resolution_clock::now();
            for (int i = 0; i < MAX; i++)
                for (int j = 0; j < MAX; j++)
                    vector_y[i] += matrix[i][j] * vector_x[j];
            auto end = chrono::high_resolution_clock::now();
            return chrono::duration<double>(end - start).count();
        };

        // Lambda para bucle2
        auto bucle2 = [&]() {
            auto start = chrono::high_resolution_clock::now();
            for (int j = 0; j < MAX; j++)
                for (int i = 0; i < MAX; i++)
                    vector_y[i] += matrix[i][j] * vector_x[j];
            auto end = chrono::high_resolution_clock::now();
            return chrono::duration<double>(end - start).count();
        };

        double crono1 = bucle1();
        
        fill(vector_y.begin(), vector_y.end(), 0.0); // Resetear valores del vector Y

        double crono2 = bucle2();
        
        cout << MAX << "\t\t" << crono1 << "\t" << crono2 << endl;
    }

    return 0;
}
