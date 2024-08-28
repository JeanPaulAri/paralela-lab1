#include <iostream>
#include <chrono>
#include <vector>
#include <algorithm>

using namespace std;

int main() {
    vector<int> sizes = {10, 20, 40, 80, 160, 320, 640, 1280, 2560};
    cout << "[AVISO] -> Tiempo en segundos" << endl;
    cout << "[AVISO] -> valores de tiempo muy cercano a cero seran imprimidos en notacion cientifica" << endl;
    cout << "Dimension\tOpClasica\tOpBloque " << endl;

    for (int size : sizes) {
       
        vector<vector<int>> A(size, vector<int>(size));
        vector<vector<int>> B(size, vector<int>(size));
        vector<vector<int>> res(size, vector<int>(size, 0));

        
        int value = 1;
        for (int i = 0; i < size; ++i) {
            for (int j = 0; j < size; ++j) {
                A[i][j] = value++;
                B[i][j] = value++;
            }
        }

        // Lambda para multiplicacion clásica de matrices
        auto multMatrizClasica = [&]() {
            auto start = chrono::high_resolution_clock::now();
            for (int i = 0; i < size; ++i) {
                for (int j = 0; j < size; ++j) {
                    for (int k = 0; k < size; ++k) {
                        res[i][j] += A[i][k] * B[k][j];
                    }
                }
            }
            auto end = chrono::high_resolution_clock::now();
            return chrono::duration<double>(end - start).count();
        };

        // Lambda para multiplicacion de matrices en bloque
        auto multMatrizBloque = [&]() {
            int S = 80;
            auto start = chrono::high_resolution_clock::now();
            for (int ii = 0; ii < size; ii += S) {
                for (int jj = 0; jj < size; jj += S) {
                    for (int kk = 0; kk < size; kk += S) {
                        for (int i = ii; i < min(ii + S, size); ++i) {
                            for (int j = jj; j < min(jj + S, size); ++j) {
                                for (int k = kk; k < min(kk + S, size); ++k) {
                                    res[i][j] += A[i][k] * B[k][j];
                                }
                            }
                        }
                    }
                }
            }
            auto end = chrono::high_resolution_clock::now();
            return chrono::duration<double>(end - start).count();
        };

        // Ejecutar lambdas y medir tiempo
        double crono1 = multMatrizClasica();
        fill(res.begin(), res.end(), vector<int>(size, 0)); // Resetear matriz res 
        double crono2 = multMatrizBloque();

        cout << size << "\t\t" << crono1 << "\t" << crono2 << endl;
    }

    return 0;
}
