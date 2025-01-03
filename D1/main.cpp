#include <iostream>
#include <fstream>
#include <sstream>
#include <algorithm>
#include <chrono>
#include "main.h"
#include <omp.h>

tuple<vector<int>,vector<int>> extract_data(const string& filename){
    ifstream file(filename);
    vector<int> first_vector;
    vector<int> second_vector;
    if (file.is_open()){
        string line;
        while(getline(file, line)){

            int val1;
            int val2;
            istringstream iss(line);
            iss >> val1 >> val2;

            if (iss.fail()) {
                std::cerr << "Erreur lors de la conversion." << std::endl;
            }

	    first_vector.push_back(val1);
            second_vector.push_back(val2);
	}
    }

    //Sort the vectors by ascending order                                                                                                                                               
    sort(first_vector.begin(), first_vector.end());
    sort(second_vector.begin(), second_vector.end());

    return make_tuple(first_vector, second_vector);
}

int parallel_sum_distances(vector<int> first_vector, vector<int> second_vector){
    size_t size = first_vector.size();
    vector<int> single_distances_vector(size);

    #pragma omp parallel for
    for (size_t i = 0; i < size; ++i){
        single_distances_vector[i] = abs(first_vector[i] - second_vector[i]);
    }

    int sum_distances = 0;
    #pragma omp parallel for reduction(+:sum_distances)
    for (auto& elt: single_distances_vector){
        sum_distances += elt;
    }

    return sum_distances;
}

int compute_similarity_elt(int elt, vector<int> second_vector){
    return count(second_vector.begin(), second_vector.end(), elt);
}

int parallel_compute_similarity_score(vector<int> first_vector, vector<int> second_vector){
    int similarity_score = 0;

    #pragma omp parallel for reduction(+:similarity_score)
    for (auto& elt: first_vector){
        similarity_score += compute_similarity_elt(elt, second_vector)*elt;
    }

    return similarity_score;
}

int main() {
    auto start = chrono::high_resolution_clock::now();

    const string filename = "input.txt";
    tuple<vector<int>,vector<int>> data_tuple = extract_data(filename);
    vector<int> first_vector = get<0>(data_tuple);
    vector<int> second_vector = get<1>(data_tuple);
    int sum_distances = parallel_sum_distances(first_vector, second_vector);
    cout << "Result part 1: " << sum_distances << endl;
    int similarity_score = parallel_compute_similarity_score(first_vector, second_vector);
    cout << "Result part 2: " << similarity_score << endl;

    auto end = chrono::high_resolution_clock::now();
    auto duration = chrono::duration_cast<chrono::milliseconds>(end - start);
    cout << "Time: " << duration.count() << " ms" << endl;
    return EXIT_SUCCESS;
}

