#include <iostream>
#include <vector>
#include <cmath>
#include "utils.h" //Load my header file of utility functions.

// Using a template allows the same function to be used with single, double or
// extended precision floats.
template<typename T>
T accuracy_bound (T value, T divisor, T initial_guess) {
    /**
     * function accuracy_bound
     * Returns an upper bound for the machine accuracy.
     *
     * By repeatedly divising by a divisor, finds an upper bound for the machine
     * accuracy, where machine accuracy is defined as the smallest number that
     * can meaningfully be added to some value.
     *
     * Parameters:
     *   T value: A value of type T about which the accuracy is defined.
     *   T divisor: A value of type T to repeatedly divide the guess by.
     *   T initial_guess: An initial guess for the machine accuracy.
     *
     * Returns:
     *   T: The smallest value of type T that could be meaingfully added to
     *      value.
     */

    // Set the initial guess.
    T epsilon = initial_guess;

    // Continue running until comparing value + epsilon with epsilon returns True.
    while (value + epsilon != value) {
        // Each loop, divide by the divisor.
        epsilon /= divisor;
    }

    // The last value tested did not meaningfully succeed, so is less than the
    // machine accuracy, so return the second last value.
    return epsilon * divisor;
}

template<typename T>
std::vector<T> accuracy_vector(T value, const std::vector<T> & divisors, T initial_guess){
    /**
     * function accuracy_vector
     * Runs accuracy_bound repeatedly using a list of divisors.
     *
     * Runs accuracy_bound to obtain an upper bound, then uses this upper bound
     * with the next divisor to obtain a new, lower, upper bound.
     *
     * Parameters:
     *   T value: A value of type T about which the machine accuracy is defined.
     *   std::vector<T> divisors: A vector of divisors, in order of use (probably largest to smallest).
     *   initial_guess: An initial guess for the machine accuracy to use with the first divisor.
     *
     * Returns:
     *   std::vector<T>; A vector of type T containing the results in the order they are obtained.
     */

    // Extract the number of times to run accuracy_bound from the size of the
    // divisors vector.
    const unsigned size = divisors.size();

    // Initialise the output vector.
    std::vector<T> output(size);

    // Initialise a variable of type T to store the current guess.
    // This is used instead of just referring directly to the previous result so
    // that the initial guess can be used on the first iteration.

    T guess = initial_guess;

    // Loop through the algorithm the correct number of times.
    for (unsigned i = 0; i < size; ++i) {
        // Obtain an upper bound using the ith divisor and store in the output vector.
        output[i] = accuracy_bound<T>(value, divisors[i], guess);
        // Store the result to the guess variable.
        guess = output[i];
    }

    // Return the output vector.
    return output;
}

int main(int argc, char ** argv) {

    // Store a list of divisors in float, double, and long double forms.
    // Note the definition of these data types is compiler-dependent,
    // particularly the definition of long double, which using my g++ compiler
    // is an 80 bit not quadruple precision float.
    std::vector<float> single_divisors = {2.0, 1.1, 1.01, 1.001, 1.0001, 1.00001};
    std::vector<double> double_divisors(single_divisors.begin(), single_divisors.end());
    std::vector<long double> extended_divisors(single_divisors.begin(), single_divisors.end());

    // Calculate a vector of estimates using the divisor lists for floats,
    // doubles, and long doubles.
    std::vector<float> single_vector = accuracy_vector<float>(1.0, single_divisors, 1.0);
    std::vector<double> double_vector = accuracy_vector<double>(1.0, double_divisors, 1.0);
    std::vector<long double> extended_vector = accuracy_vector<long double>(1.0, extended_divisors, 1.0);

    // Print the values to the console, and compare with theoretical values from
    // IEEE Std 754-2008 and the GCC documentation 2017.
    std::cout << "Single precision accuracy upper bound: " << single_vector[single_vector.size() - 1]
              << ", compared with a theoretical value of " << pow(2, -24)
              << '.' << std::endl;

    std::cout << "Double precision accuracy upper bound: " << double_vector[double_vector.size() - 1]
              << ", compared with a theoretical value of " << pow(2, -53)
              << '.' << std::endl;

    std::cout << "Extended precision accuracy upper bound: " << extended_vector[extended_vector.size() - 1]
              << ", compared with a theoretical value of " << pow(2, -64)
              << '.' << std::endl;

    // Create an output file.
    std::ofstream output("output.txt");

    // Store the vectors to the file using the vector_to_file function from
    // utils.h, to be imported to python for plotting.
    utils::vector_to_file(output, single_vector);
    utils::vector_to_file(output, double_vector);
    utils::vector_to_file(output, extended_vector);

}
