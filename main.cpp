// this program calculates the product of two matrixes.
// the following parameters can be changed according to preference: sizes of matrixes, type of the matrix,
// and range of random numbers (x0, x) for randomly filled matrixes

#include <random>
#include <iostream>
#include <vector>
#include <iterator>
#include <chrono>

const double x0 = 0;
const double x = 1;

using namespace std;

vector <double> product(vector <double> A, vector <double> B, int n, int m, int l);
vector<double> product_other(vector<double> &A, int str1, vector<double> &B, int str2);
void fill_random(vector<double> &A, double num1, double num2);
void fill_one(vector<double> &A, int str);
void fill_tr(vector<double> &A, int str);
void print_matr(const vector<double> &A, int column);


int main()
{
    int str1 = 1000, clm1 = 10000, str2 = 10000, clm2 = 10000; // size of matrix A[str1 x clm1] and B[str2 x clm2]
    vector<double> RES(str1 * clm2, 0);  // the resulting matrix
    vector<double> B(str2*clm2, 0);
    vector<double> A(str1*clm1, 0);

    fill_one(B, str2);
    fill_one(A, str1);

    std::chrono::time_point<std::chrono::system_clock> tic, tac;
    tic = std :: chrono :: system_clock :: now();  //this function will help us calculate the time
    RES = product(A, B, str1, clm1, clm2);
    tac = std :: chrono :: system_clock :: now();

    std:: chrono :: duration<double> elapsedt = tac - tic;

    std :: cout << "\nTHIS PROGRAM WAS DONE IN " << elapsedt.count() << " sec";

    A.clear();
    B.clear();

    return 0;
}


vector <double> product(vector <double> A, vector <double> B, int n, int m, int l)
    {
        vector <double> vsc(n * l, 0);
#pragma omp parallel for
        for (int i = 0; i < n; i++){
            for (int j = 0; j < l; j++){
                for (int k = 0; k < m; k++){
                    vsc[i * l + j] += A[i * m + k] * B[k * l + j];
                }
            }
        }
        return vsc;
    }



vector<double> product_other(const vector<double> &A, size_t str1, const vector<double> &B, int str2)
{
    int clmn1 = A.size() / str1;
    int clmn2 = B.size() / str2;
    vector<double> vsc(str1 * clmn2, 0);
#pragma omp parallel for
    for(int i = 0; i < str1; i++){
        for(int j = 0; j < clmn2; j++){
            int i2 = i * clmn1;
            for(int n = 0; n < clmn1; n++){
                vsc[i2 + j] += A[i2 + n] * B[j + n * clmn2];
            }
        }
    }
    return vsc;
}



void fill_random(vector<double> &A, double num1, double num2)
{
    random_device rd;
    mt19937 mt(rd());
    for(int i = 0; i < A.size(); i++){
            uniform_real_distribution<double> dist(num1, num2);
            double rnd = dist(mt);
            A[i] = rnd;
    }
}


void fill_tr(vector<double> &A, int str)
{
    int clm;
    clm = A.size() / str;
    for (int i = 0; i < str;i++) {
        for (int j = 0; j <= i;j++) {
            A[i * clm + j] = 1;
        }
    }
}


void fill_one(vector<double> &A, int str)
{
    int clm = A.size() / str;
    vector<double> vsc(str*clm, 0);

    for(int i = 0; i < str; i++) {
        for (int j = 0; j < clm; j++) {
                A[str * i + i] = 1;
        }
    }
}


void print_matr(const vector<double> &A, int column)
{
    cout << "\nmatrix\n";
    for(int i = 0; i < A.size(); ){
        cout << "| ";
        for(int j = 0; j < column; j++) {
            printf("%5.2f", A[i]);
            i++;
        }
        cout << " |\n";
    }
}
