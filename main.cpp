#include "Studentas.h"
#include "Mylib.h"

int main() {
    try {
        auto start = high_resolution_clock::now(); // Start the timer

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
            ivestiStudentus(studentai);
        } else if (pasirinkimas == 'f') {
            string failoPav;
            bool success = false;
            do {
                cout << "Iveskite failo pavadinima: ";
                cin >> failoPav;
                auto start = high_resolution_clock::now(); // Start the timer for reading the file
                success = skaitymas(studentai, failoPav);
                auto end = high_resolution_clock::now(); // End the timer for reading the file
                std::chrono::duration<double> duration = std::chrono::duration_cast<std::chrono::duration<double>>(end - start);
                cout << "Failo nuskaitymo trukme: " << duration.count() << " s" << endl;
            } while (!success);
        }

        char rikiavimas;
        cout << "Pasirinkite rusiavimo buda (v - vardas, p - pavarde, a - galutinis vidurkis, m - galutinis mediana): ";
        while (!(cin >> rikiavimas) || (rikiavimas != 'v' && rikiavimas != 'p' && rikiavimas != 'a' && rikiavimas != 'm')) {
            clearInput();
            cout << "Neteisinga ivestis. Bandykite dar karta: ";
        }

        rikiuotiStudentus(studentai, rikiavimas);

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
                throw std::runtime_error("Nepavyko sukurti failo: " + outputFileName);
            } else {
                spausdinti(studentai, outFile);
                outFile.close();
                cout << "Duomenys sekmingai irasyti i faila: " << outputFileName << endl;
            }
        }

        auto end = high_resolution_clock::now(); // End the timer
        auto duration = duration_cast<std::chrono::seconds>(end - start);
        cout << "Programos vykdymo trukme: " << duration.count() << " ms" << endl;

    } catch (const std::exception& e) {
        cout << "Ivyko klaida: " << e.what() << endl;
    }

    return 0;
}