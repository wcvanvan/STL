#include <string>
using std::string;

string* dec_to_bin(string *decs, int variable_number);
/*
put every minterm into the box according to number of 1s in the minterm
*/
void sort_into_box(string *minterms, string *box, int length, int *length_of_layers);

string *minimization(string *box, int *length_of_layers, int *new_length);

string *Quine_McCluskey(string *minterms, int length, int variable_number) {
    minterms = dec_to_bin(minterms, variable_number);
    string *box = new string[length];
    int *length_of_layers = new int[variable_number+1];
    sort_into_box(minterms, box, length, length_of_layers);
    int new_length = length;
    while (new_length == length) {
        box = minimization(box, length_of_layers, &new_length);
    }
    return box;
}