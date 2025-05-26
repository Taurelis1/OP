#include "Studentas.h"
#include "Mylib.h"
#include <iostream>
#include <list>
#include <chrono>
#include <ctime>
#include <vector>

using namespace std;
using namespace std::chrono;

const int MAX_STUDENTU_SKAICIUS = 10000000;

void promptForSortingMethod() {
    cout << "Pasirinkite rusiavimo buda (a - galutinis vidurkis, m - galutinis mediana): ";
    while (!(cin >> rikiavimas) || (rikiavimas != 'a' && rikiavimas != 'm')) {
        clearInput();
        cout << "Neteisinga ivestis. Bandykite dar karta: ";
    }
}

int main() {
    try {
        auto start = high_resolution_clock::now();

        std::srand(std::time(0));

        list<Studentas> studentai; // <-- changed from vector to list
        char pasirinkimas;

        cout << "Pasirinkite veiksma (s - generuoti studentu failus, g - generuoti viska, i - ivesti duomenis, f - skaityti is failo, q - uzdaryti programa): ";
        while (!(cin >> pasirinkimas) || (pasirinkimas != 's' && pasirinkimas != 'g' && pasirinkimas != 'i' && pasirinkimas != 'f' && pasirinkimas != 'q')) {
            clearInput();
            cout << "Neteisinga ivestis. Bandykite dar karta: ";
        }

        if (pasirinkimas == 'q') {
            return 0;
        } else if (pasirinkimas == 's') {
            generateStudentFiles();
        } else if (pasirinkimas == 'g') {
            int studentuSkaicius;
            cout << "Iveskite studentu skaiciu (maksimalus skaicius: " << MAX_STUDENTU_SKAICIUS << "): ";
            while (!(cin >> studentuSkaicius) || studentuSkaicius <= 0 || studentuSkaicius > MAX_STUDENTU_SKAICIUS) {
                clearInput();
                cout << "Neteisinga ivestis. Bandykite dar karta: ";
            }
            try {
                for (int i = 0; i < studentuSkaicius; i++) {
                    Studentas student;
                    student.var = generuotiVarda();
                    student.pav = generuotiPavarde();
                    int ndSkaicius = 15;
                    student.nd.resize(ndSkaicius);
                    auto it = student.nd.begin();
                    for (int j = 0; j < ndSkaicius; j++, ++it) {
                        *it = std::rand() % 10 + 1;
                    }
                    student.egz = std::rand() % 10 + 1;
                    studentai.push_back(student);
                }
                sortAndOutputStudents(studentai);
            } catch (const std::bad_alloc& e) {
                cout << "Nepavyko sukurti studentu: " << e.what() << endl;
                return 1;
            }
        } else if (pasirinkimas == 'i') {
            ivestiStudentus(studentai);
            sortAndOutputStudents(studentai);
        } else if (pasirinkimas == 'f') {
            promptForSortingMethod();
            handleFileInput(studentai);
        }

        auto end = high_resolution_clock::now();
        auto duration = duration_cast<std::chrono::seconds>(end - start);
        cout << "Programos vykdymo trukme: " << duration.count() << " s" << endl;

    } catch (const std::exception& e) {
        cout << "Ivyko klaida: " << e.what() << endl;
    }

    return 0;
}