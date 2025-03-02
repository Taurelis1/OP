#ifndef STUDENTAS_H
#define STUDENTAS_H

#include "Mylib.h"

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

#endif // STUDENTAS_H