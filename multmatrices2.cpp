#include <iostream>
#include <chrono>
#include <vector>
#include <algorithm>

using namespace std;

int main() {
    int Ns[] = {100, 200, 250, 500, 1000};

    cout << "[AVISO] -> Tiempo en segundos" << endl;
    cout << "[AVISO] -> valores de tiempo muy cercano a cero seran imprimidos en notacion cientifica" << endl;
    cout << "Dimension\tOpClasica2\t\tOpBloque2" << endl;

    for (int N : Ns) {
        vector<vector<int>> A(N, vector<int>(N, 1));
        vector<vector<int>> B(N, vector<int>(N, 1));
        vector<vector<int>> res(N, vector<int>(N, 0));

        // Lambda para multiplicacion de matrices
        auto multMatrizClasica = [&]() {
            auto start = chrono::high_resolution_clock::now();
            for (int i = 0; i < N; i++) {
                for (int j = 0; j < N; j++) {
                    for (int k = 0; k < N; k++) {
                        res[i][j] += A[i][k] * B[k][j];
                    }
                }
            }
            auto end = chrono::high_resolution_clock::now();
            return chrono::duration<double>(end - start).count();
        };

        // Lambda para multiplicacion de matrices en bloques
        auto multMatrizBloque = [&]() {
            int S = 20;  
            auto start = chrono::high_resolution_clock::now();
            for (int ii = 0; ii < N; ii += S) {
                for (int jj = 0; jj < N; jj += S) {
                    for (int kk = 0; kk < N; kk += S) {
                        for (int i = ii; i < min(ii + S, N); ++i) {
                            for (int j = jj; j < min(jj + S, N); ++j) {
                                for (int k = kk; k < min(kk + S, N); ++k) {
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

        // Ejecutar
        double crono1 = multMatrizClasica();

        // Resetear matriz res
        for (auto& row : res) {
            fill(row.begin(), row.end(), 0);
        }

        double crono2 = multMatrizBloque();

        // Imprimir resultados con tabulaciones
        cout << N << "\t\t" << crono1 << "\t\t" << crono2 << endl;
    }

    return 0;
}
