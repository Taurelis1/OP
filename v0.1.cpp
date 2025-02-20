#include <iostream>
#include <string>
#include <iomanip>
#include <algorithm>
#include <vector>
#include <limits>
#include <cstdlib>
#include <ctime>

using std::string;
using std::cout;
using std::cin;
using std::endl;
using std::fixed;
using std::setprecision;
using std::setw;
using std::vector;

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

int main() {
    std::srand(std::time(0)); 

    vector<Studentas> studentai;
    char pasirinkimas;

    cout << "Pasirinkite veiksma (g - generuoti viska, i - ivesti duomenis, q - uzdaryti programa): ";
    while (!(cin >> pasirinkimas) || (pasirinkimas != 'g' && pasirinkimas != 'i' && pasirinkimas != 'q')) {
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
    }

    cout << "Pasirinkite galutinio balo skaiciavimo buda (v - vidurkis, m - mediana): ";
    while (!(cin >> pasirinkimas) || (pasirinkimas != 'v' && pasirinkimas != 'm')) {
        clearInput();
        cout << "Neteisinga ivestis. Bandykite dar karta: ";
    }

    if (pasirinkimas == 'v') {
        cout << setw(15) << "Vardas" << setw(15) << "Pavarde" << setw(20) << "Galutinis (Vid.)" << endl;
        cout << "---------------------------------------------------------------------" << endl;
    } else if (pasirinkimas == 'm') {
        cout << setw(15) << "Vardas" << setw(15) << "Pavarde" << setw(20) << "Galutinis (Med.)" << endl;
        cout << "---------------------------------------------------------------------" << endl;
    }

    for (const auto& student : studentai) {
        double galutinis = 0.0;
        if (pasirinkimas == 'v') {
            double vidurkis = 0.0;
            for (const auto& grade : student.nd) {
                vidurkis += grade;
            }
            vidurkis /= student.nd.size();
            galutinis = 0.4 * vidurkis + 0.6 * student.egz;
            cout << setw(15) << student.var << setw(15) << student.pav << setw(20) << fixed << setprecision(2) << galutinis << endl;
        } else if (pasirinkimas == 'm') {
            double mediana = Mediana(student.nd);
            galutinis = 0.4 * mediana + 0.6 * student.egz;
            cout << setw(15) << student.var << setw(15) << student.pav << setw(20) << fixed << setprecision(2) << galutinis << endl;
        }
    }

    return 0;
}