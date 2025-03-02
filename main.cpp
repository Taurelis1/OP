#include "Studentas.h"
#include "Mylib.h"

// Funkcija, skirta failo įvedimui
void handleFileInput(vector<Studentas>& studentai) {
    string failoPav;
    bool success = false;
    do {
        cout << "Įveskite failo pavadinimą: ";
        cin >> failoPav;
        auto start = high_resolution_clock::now(); // Pradėti failo skaitymo laikmatį
        success = skaitymas(studentai, failoPav);
        auto end = high_resolution_clock::now(); // Baigti failo skaitymo laikmatį
        std::chrono::duration<double> duration = std::chrono::duration_cast<std::chrono::duration<double>>(end - start);
        cout << "Failo nuskaitymo trukmė: " << duration.count() << " s" << endl;
    } while (!success);
}

// Funkcija, skirta studentų rūšiavimui
void handleSorting(vector<Studentas>& studentai) {
    char rikiavimas;
    cout << "Pasirinkite rūšiavimo būdą (v - vardas, p - pavardė, a - galutinis vidurkis, m - galutinis mediana): ";
    while (!(cin >> rikiavimas) || (rikiavimas != 'v' && rikiavimas != 'p' && rikiavimas != 'a' && rikiavimas != 'm')) {
        clearInput();
        cout << "Neteisinga įvestis. Bandykite dar kartą: ";
    }
    rikiuotiStudentus(studentai, rikiavimas);
}

// Funkcija, skirta studentų duomenų išvedimui
void handleOutput(const vector<Studentas>& studentai) {
    char outputChoice;
    cout << "Pasirinkite išvedimo būdą (s - išvedimas į ekraną, f - išvedimas į failą): ";
    while (!(cin >> outputChoice) || (outputChoice != 's' && outputChoice != 'f')) {
        clearInput();
        cout << "Neteisinga įvestis. Bandykite dar kartą: ";
    }

    if (outputChoice == 's') {
        spausdinti(studentai, cout);
    } else if (outputChoice == 'f') {
        string outputFileName;
        cout << "Įveskite failo pavadinimą: ";
        cin >> outputFileName;
        ofstream outFile(outputFileName);
        if (!outFile) {
            throw std::runtime_error("Nepavyko sukurti failo: " + outputFileName);
        } else {
            spausdinti(studentai, outFile);
            outFile.close();
            cout << "Duomenys sėkmingai įrašyti į failą: " << outputFileName << endl;
        }
    }
}

int main() {
    try {
        auto start = high_resolution_clock::now(); // Pradėti laikmatį

        std::srand(std::time(0)); 

        vector<Studentas> studentai;
        char pasirinkimas;

        cout << "Pasirinkite veiksmą (g - generuoti viską, i - įvesti duomenis, f - skaityti iš failo, q - uždaryti programą): ";
        while (!(cin >> pasirinkimas) || (pasirinkimas != 'g' && pasirinkimas != 'i' && pasirinkimas != 'f' && pasirinkimas != 'q')) {
            clearInput();
            cout << "Neteisinga įvestis. Bandykite dar kartą: ";
        }

        if (pasirinkimas == 'q') {
            return 0;
        } else if (pasirinkimas == 'g') {
            int studentuSkaicius = std::rand() % 10 + 1; // Generuojame nuo 1 iki 10 studentų
            for (int i = 0; i < studentuSkaicius; i++) {
                Studentas student;
                student.var = generuotiVarda();
                student.pav = generuotiPavarde();
                int ndSkaicius = std::rand() % 10 + 1; // Generuojame nuo 1 iki 10 namų darbų
                student.nd.resize(ndSkaicius);
                for (int j = 0; j < ndSkaicius; j++) {
                    student.nd[j] = std::rand() % 11; // Generuojame balus nuo 0 iki 10
                }
                student.egz = std::rand() % 11; // Generuojame egzamino balą nuo 0 iki 10
                studentai.push_back(student);
            }
        } else if (pasirinkimas == 'i') {
            ivestiStudentus(studentai);
        } else if (pasirinkimas == 'f') {
            handleFileInput(studentai);
        }

        handleSorting(studentai);
        handleOutput(studentai);

        auto end = high_resolution_clock::now(); // Baigti laikmatį
        auto duration = duration_cast<std::chrono::seconds>(end - start);
        cout << "Programos vykdymo trukmė: " << duration.count() << " ms" << endl;

    } catch (const std::exception& e) {
        cout << "Įvyko klaida: " << e.what() << endl;
    }

    return 0;
}