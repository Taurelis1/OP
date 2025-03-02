#ifndef STUDENTAS_H
#define STUDENTAS_H

#include <iostream>
#include <vector>
#include <string>
#include <algorithm>
#include <iomanip>
#include <fstream>
#include <sstream>
#include <stdexcept>
#include <chrono>
#include <limits>

using namespace std;
using namespace std::chrono;

struct Studentas {
    string var;
    string pav;
    vector<int> nd;
    int egz;
};

double Mediana(const vector<int>& vec);
void clearInput();
string generuotiVarda();
string generuotiPavarde();
bool skaitymas(vector<Studentas>& studentai, const string& failoPav);
void spausdinti(const vector<Studentas>& studentai, std::ostream& out);
void rikiuotiStudentus(vector<Studentas>& studentai, char rikiavimas);
void ivestiStudentus(vector<Studentas>& studentai);
void handleFileInput(vector<Studentas>& studentai); // Prideti deklaracija
void handleSorting(vector<Studentas>& studentai); // Prideti deklaracija
void handleOutput(const vector<Studentas>& studentai); // Prideti deklaracija

#endif // STUDENTAS_H