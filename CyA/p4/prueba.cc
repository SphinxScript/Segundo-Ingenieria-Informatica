#include <iostream>
#include <regex>
#include <string>

using namespace std;

int main() {
    // Target sequence
    string target_s = "I am looking for GeeksForGeeks articles ";

    // An object of regex for pattern to be searched
    regex expression("Geeks[a-zA-Z]+");

    // flag type for determining the matching behavior
    // here it is for matches on 'string' objects
    smatch matches;

    // regex_search() for searching the regex pattern
    // 'expression' in the string 'target_s'.
    // 'matches' is flag for determining matching behavior.
    regex_search(target_s, matches, expression);
    for (auto match : matches)
        cout << match << endl;
    return 0;
}
