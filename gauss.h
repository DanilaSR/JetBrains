#ifndef APPROXIMATION_GAUSS_H
#define APPROXIMATION_GAUSS_H
#include <vector>

template<typename T>
auto tolerance = static_cast<T>(1e-10);

template<typename T>
T Tabs(const T& a){
    if(a < T(0)) return -a;
    else return a;
}

template<typename T>
int col_nonzero(const Matrix<T>& A, int col){
    if(Tabs(A(col, col)) > tolerance<T>) return col;
    else {
        for(auto i = col + 1; i < A.getN(); ++i){
            if(Tabs( A(i, col) ) > tolerance<T>) return i;
        }
    }
    return col;
}

template<typename T>
void triangulation(Matrix<T>& A, std::vector<T>& b){

    for(auto i = 0; i < A.getN()-1; ++i){
        auto iNonZero = col_nonzero(A, i);
        if(Tabs(A(iNonZero, i)) > tolerance<T>){
            A.swap(i, iNonZero);
            std::swap(b[i], b[iNonZero]);
        }
        for(auto k = i + 1; k < A.getN(); ++k){
            auto coef = A(k, i) / A(i, i);
            for(auto j = 0; j < A.getN(); ++j){
                A(k, j) -= A(i, j) * coef;
            }
            b[k] -= b[i] * coef;
        }
    }



}
template<typename T>
Matrix<T> gauss(Matrix<T> M, std::vector<T> b){
    triangulation(M, b);
    double f;
    M.division_row(0, M.data[0][0]);
    for (int i = 0; i < M.getM() - 1; i++){
        for (int j = 0; j < M.getN() - 1 - i; j++){
            if ((M.data[M.getN() - i - 1][M.getM() - 1 - i] < rel_error) && (M.data[M.getN() - i - 1][M.getM() - 1 - i] > -rel_error) ){
                i++;
            }
            f = M.data[M.getN() - i - 2 - j][M.getM() - 1 - i]/M.data[M.getN() - i - 1][M.getM() - 1 - i];
            M.multiplication_row(M.getN() - i - 1, f);
            M.subtraction_rows(M.getN() - i - 2 - j, M.getN() - i - 1);
            M.division_row(M.getN() - i - 1, M.data[M.getN() - i - 1][M.getM() - 1 - i]);
        }
    }
    return M;
}

#endif //APPROXIMATION_GAUSS_H
