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
#include <deque>

using namespace std;
using namespace std::chrono;

struct Studentas {
    string var;
    string pav;
    deque<int> nd;
    int egz;
};

extern char rikiavimas; // Declare as extern

double Mediana(const deque<int>& vec);
void clearInput();
string generuotiVarda();
string generuotiPavarde();
bool skaitymas(deque<Studentas>& studentai, const string& failoPav);
void spausdinti(const deque<Studentas>& studentai, std::ostream& out);
void rikiuotiStudentus(deque<Studentas>& studentai, char rikiavimas);
void ivestiStudentus(deque<Studentas>& studentai);
void handleFileInput(deque<Studentas>& studentai);
void handleSorting(deque<Studentas>& studentai);
void handleOutput(const deque<Studentas>& studentai);
void generateStudentFiles();
void sortAndOutputStudents(deque<Studentas>& studentai);
void skaidyti2_deque(deque<Studentas>& studentai);

#endif // STUDENTAS_H