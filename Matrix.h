#include <iostream>

using namespace :: std;

template <typename T>
class Matrix;

template <typename T>
ostream& operator << (ostream &os, const Matrix<T> &matrix) {
    for (int i = 0; i < matrix.n; i++) {
        for (int j = 0; j < matrix.m; j++) {
            os << matrix.data[i][j] << ' ';
        }
        os << '\n';
    }
    return os;
}

template <typename T>
istream& operator >> (istream &is, Matrix<T> &matrix) {

    is >> matrix.n >> matrix.m;

    matrix.data = new T*[matrix.n];
    for (int i = 0; i < matrix.n; i++) {
        matrix.data[i] = new T[matrix.m];
        for (int j = 0; j < matrix.m; j++) {
            is >> matrix.data[i][j];

        }
    }
    return is;
}

template <typename T>
class Matrix {
public:
    T** data;

protected:
    int n{}, m{};

public:

    Matrix<T> () {
        this->n = 0;
        this->m = 0;
    }

    Matrix<T> ( int n, int m, T filler) {
        this->n = n;
        this->m = m;
        this->data = new T*[n];
        for (int i = 0; i < n; i++) {
            this->data[i] = new T[m];
            for (int j = 0; j < m; j++) {
                this->data[i][j] = filler;
            }
        }
    }

    Matrix<T> (int n, int m) {
        this->n = n;
        this->m = m;
        this->data = new T* [n];
        for (int i = 0; i < n; i++) {
            this->data[i] = new T[m];
            for (int j = 0; j < m; j++){
                this->data[i][j] = 13;
            }
        }
    }

    Matrix<T> (T* arr, int n, int m) {
        this->n = n;
        this->m = m;
        this->data = new T*[n];
        for (int i = 0; i < n; i++) {
            this->data[i] = new T[m];
            for (int j = 0; j < m; j++) {
                this->data[i][j] = arr[i * m + j];
            }
        }
    }

    Matrix<T> (Matrix <T> const &other) {
        this->n = other.getN();
        this->m = other.getM();
        this->data = new T*[n];
        for (int i = 0; i < n; i++) {
            this->data[i] = new T[m];
            for (int j = 0; j < m; j++) {
                this->data[i][j] = other.data[i][j];
            }
        }
    }

    Matrix<T> (Matrix<T> &&other)  noexcept {
        this->n = other.getN();
        this->m = other.getM();
        this->data = other.data;
        other.data = nullptr;
    }


    ~Matrix() {
        if (data != nullptr) {
            for (int i = 0; i < n; i++){
                delete[] data[i];
            }
            delete[] data;
        }
    }

    Matrix<T> & operator = (const Matrix <T> &other) {
        if (&other == this) {
            return *this;
        }
        if (data != nullptr) {
            for (int i = 0; i < n; i++){
                delete[] data[i];
            }
            delete[] data;
        }

        n = other.n;
        m = other.m;

        this->data = new T* [n];
        for (int i = 0; i < n; i++) {
            this->data[i] = new T[m];
        }

        for (int i = 0; i < n; i++){
            for (int j = 0; j < m; j++){
                (*this)(i, j) = other(i, j);
            }
        }
        return *this;
    }

    Matrix<T> & operator += (const Matrix <T> &other) {
        for (int i = 0; i < n; i++){
            for (int j = 0; j < m; j++){
                data[i][j] += other(i, j);
            }
        }
        return *this;
    }

    Matrix<T> & operator = (Matrix <T> &&other)  noexcept {
        if (this != &other) {
            this->n = other.getN();
            this->m = other.getM();
            this->data = other.data;
            other.data = nullptr;
        }
        return *this;
    }

    void resize(int n0, int m0, T filler) {
        for (int i = 0; i < this->n; i++){
            delete[] this->data[i];
        }
        delete[] this->data;
        this->n = n0;
        this->m = m0;
        this->data = new T*[n0];
        for (int i = 0; i < n0; i++) {
            this->data[i] = new T[m0];
            for (int j = 0; j < m0; j++) {
                this->data[i][j] = filler;
            }
        }
    }

    Matrix<T> delete_last_row(){
        delete[] data[n - 1];
        n--;
        return *this;
    }

    void subtraction_rows(int p, int q){
        for (int i = 0; i < getM(); i++){
            data[p][i] = data[p][i] - data[q][i];
        }
    }

    void multiplication_row(int p, double a){
        for (int i = 0; i < getM(); i++){
            data[p][i] = data[p][i] * a;
        }
    }

    void division_row (int p, double a){
        for (int i = 0; i < getM(); i++){
            data[p][i] = data[p][i] / a;
        }
    }

    void print_vector(){
        for (int i = 0; i < getN() - 1; i++){
            cout << "|" << -data[i][getM() - 1] << "|" << endl;
        }
        cout << "|" << 1 <<' ' <<' ' <<' ' <<' ' <<' ' <<' ' <<' ' <<  "|" <<  endl;
    }



    void resize(int n0, int m0) {
        for (int i = 0; i < this->n0; i++){
            delete[] this->data[i];
        }
        delete[] this->data;
        this->n = n0;
        this->m = m0;
        this->data = new T*[n0];
        for (int i = 0; i < n0; i++) {
            this->data[i] = new T[m0];
        }
    }

    Matrix<T> operator + (Matrix<T> const &other) const {
        Matrix<T> ans(this->n, this->m);
        for (int i = 0; i < this->n; i++) {
            for (int j = 0; j < this->m; j++) {
                ans(i, j) = this->data[i][j] + other(i, j);
            }
        }
        return ans;
    }

    Matrix<T> operator - (Matrix const &other) const {
        return (other * -1) + *this;
    }

    Matrix<T> operator * (Matrix const &other) const {

        Matrix<T> ans(n, other.getM());
        for (int i = 0; i < n; i++) {
            for (int j = 0; j < other.getM(); j++) {
                ans(i, j) = 0;
                for (int k = 0; k < m; k++) {
                    ans(i, j) += (data[i][k] * other(k, j));
                }
            }
        }
        return ans;
    }

    Matrix<T> operator * (double num) const {
        Matrix<T> ans(this->n, this->m);
        for (int i = 0; i < this->n; i++) {
            for (int j = 0; j < this->m; j++) {
                ans(i, j) = this->data[i][j] * num;
            }
        }
        return ans;
    }

    Matrix<T> operator / (double num) const {
        return *this * (1.0 / num);
    }

    Matrix<T> operator | (Matrix const &other) const {
        n = other.get_dimensions().first, m = other.get_dimensions().second;
        T arr[this->n][this->m + m];
        for (int i = 0; i < this->n; i++) {
            for (int j = 0; j < this->m; j++) {
                arr[i][j] = this->data[i][j];
            }
        }
        for (int i = 0; i < n; i++) {
            for (int j = 0; j < m; j++) {
                arr[i][j + this->m] = other.data[i][j];
            }
        }
        Matrix ans(*arr, this->n, this->m + m);
        return ans;
    }

    Matrix<T> operator ^ (Matrix const &other) const {
        int n0 = other.get_dimensions().first, m0 = other.get_dimensions().second;
        T arr[this->n + n0][this->m0];
        for (int i = 0; i < this->n; i++) {
            for (int j = 0; j < this->m; j++) {
                arr[i][j] = this->data[i][j];
            }
        }
        for (int i = 0; i < n0; i++) {
            for (int j = 0; j < m0; j++) {
                arr[i + this->n][j] = other.data[i][j];
            }
        }
        Matrix ans(*arr, this->n + n0, this->m);
        return ans;
    }

    T& operator()(int i, int j) const {
        return this->data[i][j];
    }

    T& operator()(int i) const {
        if (this->n == 1) {
            return this->data[0][i];
        }
        if (this->m == 1) {
            return this->data[i][0];
        }
    }

    void swap(int i, int j) {
        for (int c = 0; c < this->m; c++){
            auto tmp = data[j][c];
            data[j][c] = data[i][c];
            data[i][c] = tmp;
        }
    }

    int getN() const {
        return this->n;
    }

    int getM() const {
        return this->m;
    }

    bool is_square() const {
        if (this->n == this->m) {
            return true;
        }
        return false;
    }

    Matrix<T> get_submatrix(int start_str, int start_col, int n0, int m0) const {
        T ans[n0][m0];
        for (int i = 0; i < n; i++) {
            for (int j = 0; j < m; j++) {
                ans[i][j] = this->data[start_str + i][start_col + j];
            }
        }
        Matrix submatrix(*ans, n0, m0);
        return submatrix;
    }

    T algebraic_addition(int i, int j) const {

        if (this->n == 1) {
            T a;
            a =1;
            return a;
        }
        double sign = -1;
        if ((i + j) % 2 == 0) {
            sign = 1;
        }
        return (this->minor(i, j).determinant()) * sign;
    }

    Matrix<T> transpose() const{
        Matrix <T> ans(*this);
        for (int i = 0; i < this->n; i++) {
            for (int j = 0; j < i; j++) {
                T a1 = ans(i, j), a2 = ans(j, i);
                ans(i, j) = a2;
                ans(j, i) = a1;
            }
        }
        return ans;
    }

    Matrix<T> inverse() const {
        T det = this->determinant();
        T arr[this->n][this->m];
        for (int i = 0; i < this->n; i++) {
            for (int j = 0; j < this->m; j++) {
                arr[i][j] = this->algebraic_addition(i, j) / det;
            }
        }
        Matrix ans(*arr, this->n, this->m);
        return ans.transpose();
    }

    Matrix<T> minor(int i, int j) const {
        T arr[this->n - 1][this->m - 1];
        int str = 0, col = 0;
        for (int _i = 0; _i < this->n; _i++) {
            if (_i == i) {
                str = 1;
                continue;
            }
            for (int _j = 0; _j < this->m; _j++) {
                if (_j == j) {
                    col = 1;
                    continue;
                }
                arr[_i - str][_j - col] = this->data[_i][_j];
            }
            col = 0;
        }
        Matrix ans(*arr, this->n - 1, this->m - 1);
        return ans;
    }

    Matrix<T> makeL() const {
        Matrix<T> L;
        for (auto i = 0; i < m; i++) {
            for (auto j = i + 1; j < n; j++){
                L(i, j) = data[i][j];
            }
        }
        return L;
    }

    T norm() const {
        T sum = 0;
        for(size_t i = 0; i < m; ++i){
            sum += data[1][i] * data[1][i];
        }
        return sqrt(sum);
    }

    T determinant() const {
        if (this->n == 1 && this->m == 1) {
            return this->data[0][0];
        }
        T ans;
        ans = 0;
        for (int i = 0; i < this->m; i++) {
            ans += (this->algebraic_addition(0, i)) * this->data[0][i];
        }
        return ans;
    }

    friend ostream& operator << <T>(ostream &os, const Matrix &matrix);
    friend istream& operator >> <T>(istream &is, Matrix &matrix);

};

template <typename T>
Matrix<T> operator * (double num, Matrix<T> const &M) {
    return M * num;
}

template <typename T>
T norm(const Matrix<T>& a){
    T sum = 0;
    for(auto i = 0; i < a.getN(); ++i){
        sum += a(i, 0) * a(i, 0);
    }
    return sqrt(sum);
}

template <typename T>
class Matrix_U: public Matrix<T> {
public:
    explicit Matrix_U <T> (Matrix<T> A) {
        this->n = A.getN();
        this->m = A.getM();
        this->data = new T*[this->n];
        for (int i = 0; i < this->n; i++) {
            this->data[i] = new T[this->m];
        }
        for (size_t i = 0; i < A.getN(); i++){
            for (size_t j = 0; j < A.getM(); j++){
                if (i > j) this->data[i][j] = A(i, j);
                else this->data[i][j] = 0;
            }
        }
    }
};

template <typename T>
class Matrix_L: public Matrix<T> {
public:
    explicit Matrix_L <T> (Matrix<T> A) {
        this->n = A.getN();
        this->m = A.getM();
        this->data = new T*[this->n];
        for (int i = 0; i < this->n; i++) {
            this->data[i] = new T[this->m];
        }
        for (size_t i = 0; i < A.getN(); i++){
            for (size_t j = 0; j < A.getM(); j++){
                if (i <= j) this->data[i][j] = A(i, j);
                else this->data[i][j] = 0;
            }
        }
    }
};

