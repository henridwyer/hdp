#ifndef UTILS_H
#define UTILS_H

#include <stdio.h>
#include <stdlib.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <unistd.h>
#include <dirent.h>
#include <memory.h>
#include <time.h>

#include <math.h>
#include <gsl/gsl_rng.h>
#include <gsl/gsl_randist.h>
#include <gsl/gsl_permutation.h>
#include <gsl/gsl_sf_psi.h>
#include <gsl/gsl_sf_gamma.h>

#include <vector>
#include <set>
using namespace std;

typedef vector<long> vct_long; // define the vector of long
typedef set<long> set_long; // define the set of long
typedef vector<double> vct; // define the vector of double

long compare (const void * a, const void * b);

inline double safe_log(double x) {
  if (x <= 0)
    return(-10000);
  else 
    return(log(x));
}

double log_sum(double log_a, double log_b);
double log_subtract(double log_a, double log_b);
double log_factorial(long n, double a);

bool file_exists(const char * filename);
bool dir_exists(const char * directory);
void make_directory(const char* name);


double log_normalize(vct* x);
double vct_normalize(vct* x);
void vct_log(vct* x);
void vct_exp(vct* x);

// find the max and argmax in a vector
template <typename T> T vct_max(const vector<T>& v, long* argmax) {
  size_t size = v.size();
  *argmax = 0;
  T max_val = v[0];
  for (size_t i = 1; i < size; ++i)
    if (v[i] > max_val) {
      max_val = v[i];
      *argmax = i;
    }
  return max_val;
}

// find the sum in a vector
template <typename T> T vct_sum(const vector<T>& v) {
  T sum_val = 0;
  size_t size = v.size();
  for (size_t i = 0; i < size; ++i)
    sum_val += v[i];
  return sum_val;
}

// swap two elements in vector
template <typename T > void vct_swap_elements(vector<T>* v, long i, long j) {
  if (i == j) return; // no need to swap
  T a = v->at(i);
  v->at(i) = v->at(j);
  v->at(j) = a;
}

template <typename T> void vct_ptr_push_back(vector <T* >* v, long length) {
  T* ptr = new T[length];
  memset(ptr, 0, length * sizeof(T));
  v->push_back(ptr);
}

template <typename T> void vct_ptr_resize(vector <T* >* v, size_t new_size, long length=0) {
  size_t size = v->size();
  if (size == new_size) {
    return;
  } else if (size > new_size) {
    for (size_t i = new_size; i < size; ++i) {
      T* ptr = v->at(i);
      delete [] ptr;
    }
    v->resize(new_size);
  } else {
    v->resize(new_size, NULL);
    for (size_t i = size; i < new_size; ++i) {
      T* ptr = new T[length];
      memset(ptr, 0, length * sizeof(T));
      v->at(i) = ptr;
    }
  }
}

template <typename T> void vct_ptr_free(vector <T* >* v) {
  long size = v->size();
  for (long i = 0; i < size; ++i) {
    T* ptr = v->at(i);
    delete [] ptr;
  }
  v->clear();
}

/// gsl_wrappers
double digamma(double x);
unsigned long rmultinomial(const vct& v, double tot = -1.0);
double rgamma(double a, double b);
double rbeta(double a, double b);
unsigned long rbernoulli(double p);
double runiform();
void rshuffle (void* base, size_t n, size_t size);
unsigned long long runiform_long(unsigned long long n);
void choose_k_from_n(long k, long n, long* result, long* src);
void sample_k_from_n(long k, long n, vct_long* result);

// new and free random number generator
gsl_rng* new_random_number_generator(long seed);
void free_random_number_generator(gsl_rng * random_number_generator);

#endif
