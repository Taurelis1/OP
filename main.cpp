#include "Studentas.h"
#include "Mylib.h"

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
            int studentuSkaicius;
            cout << "Iveskite studentu skaiciu: ";
            while (!(cin >> studentuSkaicius) || studentuSkaicius <= 0) {
                clearInput();
                cout << "Neteisinga ivestis. Bandykite dar karta: ";
            }
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