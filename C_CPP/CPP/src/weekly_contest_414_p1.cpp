// Problem: Weekly Contest 414 Problem 1
#include <string>
#include <vector>
#include <bitset>
using namespace std;

class Solution {
public:
    // TODO: Add your function declaration here
    // Example:
    // ReturnType solutionFunction(ParamType1 param1, ParamType2 param2) {
    //     // Implementation
    // }

    string convertDateToBinary(string date) {
        auto bin = [](int x) -> string {
            string s = bitset<32>(x).to_string();
            return s.substr(s.find('1'));  // Remove leading zeros
        };
        return bin(stoi(date.substr(0, 4))) + "-" +
               bin(stoi(date.substr(5, 2))) + "-" +
               bin(stoi(date.substr(8, 2)));
    }
};
