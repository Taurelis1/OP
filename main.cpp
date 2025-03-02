#include "Studentas.h"
#include "Mylib.h"

// Funkcija, skirta failo ivedimui
void handleFileInput(vector<Studentas>& studentai) {
    string failoPav;
    bool success = false;
    do {
        cout << "Iveskite failo pavadinima: ";
        cin >> failoPav;
        auto start = high_resolution_clock::now(); // Pradeti failo skaitymo laikmati
        success = skaitymas(studentai, failoPav);
        auto end = high_resolution_clock::now(); // Baigti failo skaitymo laikmati
        std::chrono::duration<double> duration = std::chrono::duration_cast<std::chrono::duration<double>>(end - start);
        cout << "Failo nuskaitymo trukme: " << duration.count() << " s" << endl;
    } while (!success);
}

// Funkcija, skirta studentu rusiavimui
void handleSorting(vector<Studentas>& studentai) {
    char rikiavimas;
    cout << "Pasirinkite rusiavimo buda (v - vardas, p - pavarde, a - galutinis vidurkis, m - galutinis mediana): ";
    while (!(cin >> rikiavimas) || (rikiavimas != 'v' && rikiavimas != 'p' && rikiavimas != 'a' && rikiavimas != 'm')) {
        clearInput();
        cout << "Neteisinga ivestis. Bandykite dar karta: ";
    }
    rikiuotiStudentus(studentai, rikiavimas);
}

// Funkcija, skirta studentu duomenu isvedimui
void handleOutput(const vector<Studentas>& studentai) {
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
}

int main() {
    try {
        auto start = high_resolution_clock::now(); // Pradeti laikmati

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
            handleFileInput(studentai);
        }

        handleSorting(studentai);
        handleOutput(studentai);

        auto end = high_resolution_clock::now(); // Baigti laikmati
        auto duration = duration_cast<std::chrono::seconds>(end - start);
        cout << "Programos vykdymo trukme: " << duration.count() << " ms" << endl;

    } catch (const std::exception& e) {
        cout << "Ivyko klaida: " << e.what() << endl;
    }

    return 0;
}