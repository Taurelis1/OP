#ifndef STUDENTAS_H
#define STUDENTAS_H

#include <iostream>
#include <list>
#include <string>
#include <algorithm>
#include <iomanip>
#include <fstream>
#include <sstream>
#include <stdexcept>
#include <chrono>
#include <limits>
#include <vector>
#include "Mylib.h"

using namespace std;
using namespace std::chrono;

struct Studentas {
    string var;
    string pav;
    list<int> nd;
    int egz;
};

extern char rikiavimas; // Declare as extern

double Mediana(const list<int>& vec);
void clearInput();
string generuotiVarda();
string generuotiPavarde();
bool skaitymas(list<Studentas>& studentai, const string& failoPav);
void spausdinti(const list<Studentas>& studentai, std::ostream& out);
void rikiuotiStudentus(list<Studentas>& studentai, char rikiavimas);
void ivestiStudentus(list<Studentas>& studentai);
void handleFileInput(list<Studentas>& studentai);
void handleSorting(list<Studentas>& studentai);
void handleOutput(const list<Studentas>& studentai);
void generateStudentFiles();
void sortAndOutputStudents(list<Studentas>& studentai);
void skaidyti2_list(list<Studentas>& studentai);
void skaidyti3_list(list<Studentas>& studentai);

#endif // STUDENTAS_H