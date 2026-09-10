#include <iostream>
#include <vector>
#include <cmath>
#include <climits>
#include <chrono>
#include <cstdlib>
using namespace std;
using namespace std::chrono;

void intercambiar(int* a, int* b) {
    int temp = *a;
    *a = *b;
    *b = temp;
}

void insertionSort(vector<int>& A, int p, int r) {

    for (int i = p + 1; i <= r; i++) {

        int j = i;

        while (j > p && A[j - 1] > A[j]) {

            intercambiar(&A[j - 1], &A[j]);

            j--;
        }
    }
}

void merge(vector<int>& A, int p, int q, int r) {

    int n1 = q - p + 1;
    int n2 = r - q;

    vector<int> L(n1 + 1);
    vector<int> R(n2 + 1);

    for (int i = 0; i < n1; i++) {
        L[i] = A[p + i];
    }

    for (int j = 0; j < n2; j++) {
        R[j] = A[q + 1 + j];
    }

    L[n1] = INT_MAX;
    R[n2] = INT_MAX;

    int i = 0;
    int j = 0;

    for (int x = p; x <= r; x++) {

        if (L[i] <= R[j]) {

            A[x] = L[i];
            i++;

        } else {

            A[x] = R[j];
            j++;
        }
    }
}

void mergeSortHibrido(vector<int>& A, int p, int r, int k) {

    if (p < r) {

        if ((r - p + 1) <= k) {

            insertionSort(A, p, r);

            return;
        }

        int q = floor((p + r) / 2.0);

        mergeSortHibrido(A, p, q, k);

        mergeSortHibrido(A, q + 1, r, k);

        merge(A, p, q, r);
    }
}

int main() {

    int n = 1000000;

    vector<int> original(n);

    for (int i = 0; i < n; i++) {

        original[i] = rand();
    }

    int valoresK[] = {
        1, 2, 4, 8, 16, 32, 64, 128
    };

    long long mejorTiempo = LLONG_MAX;
    int mejorK = 0;

    for (int x = 0; x < 8; x++) {

        int k = valoresK[x];

        vector<int> A = original;
        
        auto inicio =
            high_resolution_clock::now();

        mergeSortHibrido( A, 0, n - 1, k);

        auto fin =
            high_resolution_clock::now();

        auto duracion =
            duration_cast<microseconds>(
                fin - inicio
            );

        cout << "k = " << k
             << " | Tiempo = "
             << duracion.count()
             << " us"
             << endl;

        if (duracion.count() < mejorTiempo) {

            mejorTiempo = duracion.count();

            mejorK = k;
        }
    }
    cout << endl;

    cout << "Mejor k = "
         << mejorK
         << " | Tiempo = "
         << mejorTiempo
         << " us"
         << endl;

    return 0;
}