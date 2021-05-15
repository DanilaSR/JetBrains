#include <iostream>
#include "Matrix.h"
#include "Polynom.cpp"
#include "sturm.h"
#include "sturm.cpp"
#include "gauss.h"
#include <vector>


using namespace :: std;

int main() {
    Polynom x(2), p;
    x.koef[0] = 1;
    x.koef[1] = 0;

    Matrix<Polynom> M;
    freopen("C:/CLion/JetBrains/input_Matrix.txt", "r", stdin);
    cin >> M;
    fclose(stdin);

    Matrix<double> M1(M.getN(), M.getM());
    for (int i = 0; i < M1.getN(); i++){
        for (int j = 0; j < M1.getM(); j++){
            M1.data[i][j] = M.data[i][j].koef[0];
        }
    }

    cout << "Original matrix:" << endl;
    cout << M << endl;
    for (int i = 0; i < M.getN(); i++){
        for (int j = 0; j < M.getN(); j++){
            if (i == j){
                M.data[i][j] = M.data[i][j]  - x;
            }
        }
    }
    p = M.determinant();
    cout << "Determinant of the characteristic equation:" << endl;
    cout << p << endl;

    while (p.value(0) == 0){    //Избавляемся от нулевых корней
        p = p/x;
        int h = 0;
    }


    Sturm sturm;
    sturm.set_order(p.n - 1);

    for (auto i = p.n - 1 ; i >= 0; --i) {
        sturm.set_shturm_seq(p.koef[p.n - i - 1], i);
    }
    sturm.show_sturm_sequence(sturm.get_sturm_sequence());
    vector <double> a = sturm.get_real_roots();
    sturm.show_roots(a);


    vector<double> results(M.getN());
    for (int i = 0; i < M.getN(); i++){
        results[i] = 0;
    }

    for (int y = 0; y < a.size(); y++){
        Matrix<double> M2(M1.getN(), M1.getM());
        for (int i = 0; i < M1.getN(); i++){
            for (int j = 0; j < M1.getM(); j++){
                M2.data[i][j] = M1.data[i][j];
            }
        }
        for (int i = 0; i < M2.getN(); i++){
            for (int j = 0; j < M2.getN(); j++){
                if (i == j){
                    M2.data[i][j] = M2.data[i][j] - a[y];
                }
            }
        }
        cout << y + 1 << ' ' << "eigenvector:" << endl;
        gauss(M2, results).print_vector();

    }
}
