#include <iostream>
#include <string>
#include <vector>
#include <map>

using namespace std;

// Function to find repeated sequences in the ciphertext
vector<pair<string, int>> findRepeatedSequences(const string& ciphertext, int min_length, int max_length) {
    vector<pair<string, int>> repeated_sequences;
    map<string, vector<int>> sequence_positions;

    // Iterate over the ciphertext
    for (int i = 0; i < ciphertext.length(); ++i) {
        for (int j = min_length; j <= max_length; ++j) {
            // Extract substrings of length j
            string substring = ciphertext.substr(i, j);
            // Check if this substring has been seen before
            if (sequence_positions.find(substring) != sequence_positions.end()) {
                // Calculate the distance between the occurrences
                for (int pos : sequence_positions[substring]) {
                    int distance = i - pos;
                    // Ignore distances shorter than the minimum length
                    if (distance >= min_length) {
                        repeated_sequences.push_back({substring, distance});
                    }
                }
            }
            // Record the position of this substring
            sequence_positions[substring].push_back(i);

        }
    }
    return repeated_sequences;
}

// Function to find the greatest common divisor
int gcd(int a, int b) {
    if (b == 0)
        return a;
    return gcd(b, a % b);
}

// Function to find the key length using Kasiski examination
int findKeyLength(const vector<pair<string, int>>& repeated_sequences) {
    vector<int> distances;
    // Extract distances from the repeated sequences
    for (const auto& seq : repeated_sequences) {
        distances.push_back(seq.second);
    }
    // Find the most common divisor of the distances
    int key_length = distances[0];
    for (int i = 1; i < distances.size(); ++i) {
        key_length = gcd(key_length, distances[i]);
        cout<<distances[i]<<"\n";
    }
    return key_length;
}




int main() {
    // Example ciphertext
    string ciphertext = "WCZOUQNAHYYEDBLWOSHMAUCERCELVELXSSUZLQWBSVYXAEEMJFIAWFNAHBZOUQNAHULKHGYLWQISTBHWLJCYZEIYWVYJPFNTQQYYIRNPHSHZORWBSVYXAEEMJFIAWF";
    // Find repeated sequences
    vector<pair<string, int>> repeated_sequences = findRepeatedSequences(ciphertext, 3, 15);
    // Find the key length
    int key_length = findKeyLength(repeated_sequences);
    // Output the result
    cout << "Estimated key length: " << key_length << "\n";
    return 0;
}