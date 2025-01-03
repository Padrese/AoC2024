#ifndef MAIN
#define MAIN

#include <vector>
#include <tuple>
#include <string>
using namespace std;

tuple<vector<int>,vector<int>> extract_data(const string& filename);
int parallel_sum_distances(vector<int> first_vector, vector<int> second_vector);
int compute_similarity_elt(int elt, vector<int> second_vector);
int parallel_compute_similarity_score(vector<int> first_vector, vector<int> second_vector);

#endif