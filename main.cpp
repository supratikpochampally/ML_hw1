// Name: Supratik Pochampally
// Net ID: srp180012

#include <iostream>
#include <fstream>
#include <vector>
#include <cmath>

using namespace std;

/**
 * Function a: sum function definition
 * @param v (vector)
 * @return (sum of numeric vector)
 */
float sum(vector<float> &v) {
    float sum = 0.0;
    for (float i : v) {
        sum += i;
    }
    return sum;
}

/**
 * Function b: mean function definition
 * @param v (vector)
 * @param n (size of vector)
 * @return (mean of numeric vector)
 */
float mean(vector<float> &v, int n) {
    return sum(v) / (float) n;
}

/**
 * Function c: median function definition
 * @param v (vector)
 * @param n (size of vector)
 * @return (median of numeric vector)
 */
float median(vector<float> &v, int n) {
    sort(v.begin(), v.end()); //Sort vector elements
    if (n % 2 == 1) { //Return middle element if size is odd
        return v.at(n / 2);
    }
    //If size is even, return average of middle two elements
    return ((v.at((n / 2) - 1)) + (v.at(n / 2))) / 2;
}

/**
 * Function d: range function definition
 * @param v (vector)
 * @param n (size of vector)
 * @param name (name of vector)
 * @print (minimum value, maximum value, and range of numeric vector)
 */
void range(vector<float> &v, int n, const string& name) {
    sort(v.begin(), v.end()); //Sort vector elements
    cout << "Minimum of " << name << " = " << v.at(0) << endl;
    cout << "Maximum of " << name << " = " << v.at(n - 1) << endl;
    cout << "Range of " << name << " = " << v.at(n - 1) - v.at(0) << endl;
}

/**
 * Function e: covariance function definition
 * @param v1 (first vector)
 * @param v2 (second vector)
 * @param n (size of vectors)
 * @return (covariance between two numeric vectors)
 */
float cov(vector<float> &v1, vector<float> &v2, int n) {
    float numerator = 0.0;
    //Initialize means
    float v1_mean = mean(v1, n);
    float v2_mean = mean(v2, n);
    //for-loop to calculate summation
    for (int i = 0; i < n; i++) {
        numerator += ((v1.at(i) - v1_mean) * (v2.at(i) - v2_mean));
    }
    return numerator / (float) (n - 1);
}

/**
 * Function f: correlation function definition
 * @param v1 (first vector)
 * @param v2 (second vector)
 * @param n (size of vectors)
 * @return (correlation between two numeric vectors)
 */
float corr(vector<float> &v1, vector<float> &v2, int n) {
    //Shortcut for standard deviation of v1 and v2
    float v1_stdev = sqrt(cov(v1, v1, n));
    float v2_stdev = sqrt(cov(v2, v2, n));
    return cov(v1, v2, n) / (v1_stdev * v2_stdev);
}

//main function definition
int main() {
    ifstream inFS;                  //Initialize input file stream object
    string line;
    string rm_in, medv_in;          //String to read in strings of rm and medv values
    const int MAX_LEN = 1000;       //Large maximum length of vectors
    //Initialize rm and medv vectors
    vector<float> rm(MAX_LEN);
    vector<float> medv(MAX_LEN);

//    Opening file debug statement
//    cout << "Opening file Boston.csv" << endl;
    inFS.open("Boston.csv");
    if (!inFS.is_open()) {
        cout << "Could not open file Boston.csv." << endl;
        return 1;
    }

//    Reading line 1 debug statement
//    cout << "Reading line 1" << endl;

//    Read and print headings debug statement
    getline(inFS, line);
//    cout << "heading: " << line << endl;

    //Initialize numObservations as 0
    int numObservations = 0;
    while(inFS.good()) {
        //Read next line and parse by comma into rm_in and medv_in strings
        getline(inFS, rm_in, ',');
        getline(inFS, medv_in, '\n');

        //Add float value of rm and medv to respective vectors
        rm.at(numObservations) = stof(rm_in);
        medv.at(numObservations) = stof(medv_in);

        //Incremement number of observations
        numObservations++;
    }

    //Resize vectors to number of rows (numObservations)
    rm.resize(numObservations);
    medv.resize(numObservations);

    //Function calls
    float sum_rm = sum(rm);
    float sum_medv = sum(medv);
    float mean_rm = mean(rm, numObservations);
    float mean_medv = mean(medv, numObservations);
    float covariance = cov(rm, medv, numObservations);
    float correlation = corr(rm, medv, numObservations);
    float median_rm = median(rm, numObservations);
    float median_medv = median(medv, numObservations);

    //Print statements for results of each function
    cout << "---------------------------" << endl;
    cout << "Function a:" << endl;
    cout << "Sum of rm = " << sum_rm << endl;
    cout << "Sum of medv = " << sum_medv << endl;
    cout << "---------------------------" << endl;
    cout << "Function b:" << endl;
    cout << "Mean of rm = " << mean_rm << endl;
    cout << "Mean of medv = " << mean_medv << endl;
    cout << "---------------------------" << endl;
    cout << "Function c:" << endl;
    cout << "Median of rm = " << median_rm << endl;
    cout << "Median of medv = " << median_medv << endl;
    cout << "---------------------------" << endl;
    cout << "Function d:" << endl;
    range(rm, numObservations, "rm");
    range(medv, numObservations, "medv");
    cout << "---------------------------" << endl;
    cout << "Function e:" << endl;
    cout << "Covariance between rm and medv = " << covariance << endl;
    cout << "---------------------------" << endl;
    cout << "Function f:" << endl;
    cout << "Correlation between rm and medv = " << correlation << endl;
    cout << "---------------------------" << endl;

    return 0;
}