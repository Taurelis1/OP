#include <iostream>
#include <string>
#include <iomanip>
#include <algorithm>
#include <vector>
#include <limits>
#include <cstdlib>
#include <ctime>
#include <fstream>
#include <sstream>

using std::string;
using std::cout;
using std::cin;
using std::endl;
using std::fixed;
using std::setprecision;
using std::setw;
using std::left;
using std::vector;
using std::ifstream;
using std::ofstream;
using std::istringstream;

struct Studentas {
    string var;
    string pav;
    vector<int> nd;
    int egz;
};

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
    ifstream inFile(failoPav);
    if (!inFile) {
        cout << "Nepavyko atidaryti failo: " << failoPav << endl;
        return false;
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

int main() {
    std::srand(std::time(0)); 

    vector<Studentas> studentai;
    char pasirinkimas;

    cout << "Pasirinkite veiksma (g - generuoti viska, i - ivesti duomenis, f - skaityti is failo, q - uzdaryti programa): ";
    while (!(cin >> pasirinkimas) || (pasirinkimas != 'g' && pasirinkimas != 'i' && pasirinkimas != 'f' && pasirinkimas != 'q')) {
        clearInput();
        cout << "Neteisinga ivestis. Bandykite dar karta: ";
    }

    if (pasirinkimas == 'q') {
        return 0;
    } else if (pasirinkimas == 'g') {
        int studentuSkaicius = std::rand() % 10 + 1; // Generuojame nuo 1 iki 10 studentu
        for (int i = 0; i < studentuSkaicius; i++) {
            Studentas student;
            student.var = generuotiVarda();
            student.pav = generuotiPavarde();
            int ndSkaicius = std::rand() % 10 + 1; // Generuojame nuo 1 iki 10 namu darbu
            student.nd.resize(ndSkaicius);
            for (int j = 0; j < ndSkaicius; j++) {
                student.nd[j] = std::rand() % 11; // Generuojame balus nuo 0 iki 10
            }
            student.egz = std::rand() % 11; // Generuojame egzamino bala nuo 0 iki 10
            studentai.push_back(student);
        }
    } else if (pasirinkimas == 'i') {
        char continueInput;
        do {
            Studentas student;
            cout << "Iveskite studento varda: ";
            cin >> student.var;
            cout << "Iveskite studento pavarde: ";
            cin >> student.pav;

            cout << "Ar norite generuoti atsitiktinius balus? (t - taip, n - ne): ";
            while (!(cin >> pasirinkimas) || (pasirinkimas != 't' && pasirinkimas != 'n')) {
                clearInput();
                cout << "Neteisinga ivestis. Bandykite dar karta: ";
            }

            if (pasirinkimas == 't') {
                int n = std::rand() % 11; 
                student.nd.resize(n);
                for (int j = 0; j < n; j++) {
                    student.nd[j] = std::rand() % 11; 
                }
                student.egz = std::rand() % 11; 
            } else {
                char continueNdInput;
                do {
                    int grade;
                    cout << "Iveskite namu darbo ivertinima: ";
                    while (!(cin >> grade) || grade < 0 || grade > 10) {
                        clearInput();
                        cout << "Neteisinga ivestis. Bandykite dar karta: ";
                    }
                    student.nd.push_back(grade);

                    cout << "Ar norite prideti dar viena namu darba? (t - taip, n - ne): ";
                    while (!(cin >> continueNdInput) || (continueNdInput != 't' && continueNdInput != 'n')) {
                        clearInput();
                        cout << "Neteisinga ivestis. Bandykite dar karta: ";
                    }
                } while (continueNdInput == 't');

                cout << "Iveskite studento egzamino ivertinima: ";
                while (!(cin >> student.egz) || student.egz < 0 || student.egz > 10) {
                    clearInput();
                    cout << "Neteisinga ivestis. Bandykite dar karta: ";
                }
            }

            studentai.push_back(student);

            cout << "Ar norite prideti dar viena studenta? (t - taip, n - ne): ";
            while (!(cin >> continueInput) || (continueInput != 't' && continueInput != 'n')) {
                clearInput();
                cout << "Neteisinga ivestis. Bandykite dar karta: ";
            }
        } while (continueInput == 't');
    } else if (pasirinkimas == 'f') {
        string failoPav;
        bool success = false;
        do {
            cout << "Iveskite failo pavadinima: ";
            cin >> failoPav;
            success = skaitymas(studentai, failoPav);
        } while (!success);
    }

    char rikiavimas;
    cout << "Pasirinkite rusiavimo buda (v - vardas, p - pavarde, a - galutinis vidurkis, m - galutinis mediana): ";
    while (!(cin >> rikiavimas) || (rikiavimas != 'v' && rikiavimas != 'p' && rikiavimas != 'a' && rikiavimas != 'm')) {
        clearInput();
        cout << "Neteisinga ivestis. Bandykite dar karta: ";
    }

    if (rikiavimas == 'v') {
        std::sort(studentai.begin(), studentai.end(), [](const Studentas& a, const Studentas& b) {
            return a.var < b.var;
        });
    } else if (rikiavimas == 'p') {
        std::sort(studentai.begin(), studentai.end(), [](const Studentas& a, const Studentas& b) {
            return a.pav < b.pav;
        });
    } else if (rikiavimas == 'a') {
        std::sort(studentai.begin(), studentai.end(), [](const Studentas& a, const Studentas& b) {
            double avgA = 0.0, avgB = 0.0;
            for (const auto& grade : a.nd) avgA += grade;
            avgA = avgA / a.nd.size() * 0.4 + a.egz * 0.6;
            for (const auto& grade : b.nd) avgB += grade;
            avgB = avgB / b.nd.size() * 0.4 + b.egz * 0.6;
            return avgA < avgB;
        });
    } else if (rikiavimas == 'm') {
        std::sort(studentai.begin(), studentai.end(), [](const Studentas& a, const Studentas& b) {
            double medA = Mediana(a.nd) * 0.4 + a.egz * 0.6;
            double medB = Mediana(b.nd) * 0.4 + b.egz * 0.6;
            return medA < medB;
        });
    }

    char outputChoice;
    cout << "Pasirinkite isvedimo buda (s - isvedimas i ekrana, f - isvedimas i faila): ";
    while (!(cin >> outputChoice) || (outputChoice != 's' && outputChoice != 'f')) {
        clearInput();
        cout << "Neteisinga ivestis. Bandykite dar karta: ";
    }

    if (outputChoice == 's') {
        spausdinti(studentai, cout);
    } else if (outputChoice == 'f') {
        string outputFileName;
        cout << "Iveskite failo pavadinima: ";
        cin >> outputFileName;
        ofstream outFile(outputFileName);
        if (!outFile) {
            cout << "Nepavyko sukurti failo: " << outputFileName << endl;
        } else {
            spausdinti(studentai, outFile);
            outFile.close();
            cout << "Duomenys sekmingai irasyti i faila: " << outputFileName << endl;
        }
    }

    return 0;
}