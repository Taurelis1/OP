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
                throw std::runtime_error("Nepavyko sukurti failo: " + outputFileName);
            } else {
                spausdinti(studentai, outFile);
                outFile.close();
                cout << "Duomenys sekmingai irasyti i faila: " << outputFileName << endl;
            }
        }

        auto end = high_resolution_clock::now(); // End the timer
        auto duration = duration_cast<milliseconds>(end - start);
        cout << "Programos vykdymo trukme: " << duration.count() << " ms" << endl;

    } catch (const std::exception& e) {
        cout << "Ivyko klaida: " << e.what() << endl;
    }

    return 0;
}