#include <iostream>
#include <string>
#include <iomanip>
#include <algorithm>
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

struct Studentas {
    string var;
    string pav;
    int n;
    int* nd;
    int egz;
};

double Mediana(int arr[], int n) {
    std::sort(arr, arr + n);
    if (n % 2 == 0) {
        return (arr[n / 2 - 1] + arr[n / 2]) / 2.0;
    } else {
        return arr[n / 2];
    }
}

void clearInput() {
    cin.clear();
    cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
}

int main() {
    std::srand(std::time(0)); 

    Studentas* studentai = nullptr;
    int m = 0;
    char pasirinkimas;

    while (true) {
        Studentas* temp = new Studentas[m + 1];
        for (int i = 0; i < m; i++) {
            temp[i] = studentai[i];
        }
        delete[] studentai;
        studentai = temp;

        cout << "Iveskite studento varda (arba 'q' norint baigti): ";
        cin >> studentai[m].var;
        if (studentai[m].var == "q") break;
        cout << "Iveskite studento pavarde: ";
        cin >> studentai[m].pav;

        studentai[m].n = 0;
        studentai[m].nd = nullptr;
        int* tempNd = nullptr;
        int ndIvertinimas;

        cout << "Ar norite generuoti atsitiktinius balus? (t - taip, n - ne): ";
        while (!(cin >> pasirinkimas) || (pasirinkimas != 't' && pasirinkimas != 'n')) {
            clearInput();
            cout << "Neteisinga ivestis. Bandykite dar karta: ";
        }

        if (pasirinkimas == 't') {
            cout << "Iveskite norima namu darbu skaiciu: ";
            int ndSkaicius;
            while (!(cin >> ndSkaicius) || ndSkaicius <= 0) {
                clearInput();
                cout << "Neteisinga ivestis. Bandykite dar karta: ";
            }
            studentai[m].nd = new int[ndSkaicius];
            studentai[m].n = ndSkaicius;
            for (int j = 0; j < ndSkaicius; j++) {
                studentai[m].nd[j] = std::rand() % 11; // generavimas nuo 0 iki 10
            }
            studentai[m].egz = std::rand() % 11; // generavimas nuo 0 iki 10
        } else {
            cout << "Iveskite namu darbu ivertinimus (iveskite -1 norint baigti): " << endl;
            while (true) {
                cout << "Iveskite namu darbo ivertinima: ";
                while (!(cin >> ndIvertinimas) || ndIvertinimas < -1 || ndIvertinimas > 10) {
                    clearInput();
                    cout << "Neteisinga ivestis. Bandykite dar karta: ";
                }
                if (ndIvertinimas == -1) break;

                tempNd = new int[studentai[m].n + 1];
                for (int j = 0; j < studentai[m].n; j++) {
                    tempNd[j] = studentai[m].nd[j];
                }
                tempNd[studentai[m].n] = ndIvertinimas;
                delete[] studentai[m].nd;
                studentai[m].nd = tempNd;
                studentai[m].n++;
            }
            cout << "Iveskite studento egzamino ivertinima: ";
            while (!(cin >> studentai[m].egz) || studentai[m].egz < 0 || studentai[m].egz > 10) {
                clearInput();
                cout << "Neteisinga ivestis. Bandykite dar karta: ";
            }
        }

        m++;
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

    for (int i = 0; i < m; i++) {
        double galutinis = 0.0;
        if (pasirinkimas == 'v') {
            double vidurkis = 0.0;
            for (int j = 0; j < studentai[i].n; j++) {
                vidurkis += studentai[i].nd[j];
            }
            vidurkis /= studentai[i].n;
            galutinis = 0.4 * vidurkis + 0.6 * studentai[i].egz;
            cout << setw(15) << studentai[i].var << setw(15) << studentai[i].pav << setw(20) << fixed << setprecision(2) << galutinis << endl;
        } else if (pasirinkimas == 'm') {
            double mediana = Mediana(studentai[i].nd, studentai[i].n);
            galutinis = 0.4 * mediana + 0.6 * studentai[i].egz;
            cout << setw(15) << studentai[i].var << setw(15) << studentai[i].pav << setw(20) << fixed << setprecision(2) << galutinis << endl;
        }
    }

    for (int i = 0; i < m; i++) {
        delete[] studentai[i].nd;
    }
    delete[] studentai;

    return 0;
}