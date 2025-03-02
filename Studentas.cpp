#include "Studentas.h"
#include "Mylib.h"

double Mediana(const vector<int>& vec) {
    vector<int> sortedVec = vec;
    std::sort(sortedVec.begin(), sortedVec.end());
    int n = sortedVec.size();
    if (n % 2 == 0) {
        return (sortedVec[n / 2 - 1] + sortedVec[n / 2]) / 2.0;
    } else {
        return sortedVec[n / 2];
    }
}

void clearInput() {
    cin.clear();
    cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
}

string generuotiVarda() {
    const vector<string> vardai = {"Jonas", "Petras", "Tauras", "Antanas", "Marius", "Ugnius", "Vainius", "Darius", "Tomas", "Rokas", "Mantas", "Mindaugas", "Lukas", "Laurynas", "Karolis"};
    return vardai[std::rand() % vardai.size()];
}

string generuotiPavarde() {
    const vector<string> pavardes = {"Jonaitis", "Petraitis", "Kazlauskas", "Jankauskas", "Pavardenis", "Butkus", "Zukauskas", "Balciunas", "Stankevicius", "Urbonas", "Petrauskas"};
    return pavardes[std::rand() % pavardes.size()];
}

bool skaitymas(vector<Studentas>& studentai, const string& failoPav) {
    try {
        ifstream inFile(failoPav);
        if (!inFile) {
            throw std::runtime_error("Nepavyko atidaryti failo: " + failoPav);
        }

        string line;
        getline(inFile, line); // pirmos eilutes praleidimas

        while (getline(inFile, line)) {
            istringstream iss(line);
            Studentas student;
            iss >> student.var >> student.pav;
            int grade;
            while (iss >> grade) {
                student.nd.push_back(grade);
            }
            student.egz = student.nd.back();
            student.nd.pop_back();
            studentai.push_back(student);
        }
        inFile.close();
        return true;
    } catch (const std::exception& e) {
        cout << e.what() << endl;
        return false;
    }
}

void spausdinti(const vector<Studentas>& studentai, std::ostream& out) {
    out << left << setw(15) << "Vardas" << setw(20) << "Pavarde" << setw(20) << "Galutinis (Vid.)" << setw(20) << "Galutinis (Med.)" << endl;
    out << "---------------------------------------------------------------------" << endl;

    for (const auto& student : studentai) {
        double galutinis1 = 0.0;
        double galutinis2 = 0.0;
        double vidurkis = 0.0;
        for (const auto& grade : student.nd) {
            vidurkis += grade;
        }
        vidurkis /= student.nd.size();
        galutinis1 = 0.4 * vidurkis + 0.6 * student.egz;
        double mediana = Mediana(student.nd);
        galutinis2 = 0.4 * mediana + 0.6 * student.egz;
        out << left << setw(15) << student.var << setw(20) << student.pav << setw(20) << fixed << setprecision(2) << galutinis1 << setw(20) << fixed << setprecision(2) << galutinis2 << endl;
    }
}