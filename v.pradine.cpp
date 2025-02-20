#include <iostream>
#include <string>
#include <iomanip>
#include <algorithm>
#include <limits>

using std::string;
using std::cout;
using std::cin;
using std::endl;
using std::fixed;
using std::setprecision;
using std::setw;

const int MAX_STUD = 100; // Maximum number of students
const int MAX_ND = 10; // Maximum number of homework assignments

struct Studentas {
    string var;
    string pav;
    int n;
    int nd[MAX_ND];
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
    int n = 0;
    cout << "Iveskite studentu skaiciu: ";
    while (!(cin >> n) || n <= 0 || n > MAX_STUD) {
        clearInput();
        cout << "Neteisinga ivestis. Bandykite dar karta: ";
    }

    Studentas studentai[MAX_STUD];

    for (int i = 0; i < n; i++) {
        cout << "Iveskite studento varda: ";
        cin >> studentai[i].var;
        cout << "Iveskite studento pavarde: ";
        cin >> studentai[i].pav;
        cout << "Iveskite studento atliktu namu darbu skaiciu: ";
        while (!(cin >> studentai[i].n) || studentai[i].n <= 0 || studentai[i].n > MAX_ND) {
            clearInput();
            cout << "Neteisinga ivestis. Bandykite dar karta: ";
        }
        for (int j = 0; j < studentai[i].n; j++) {
            cout << "Iveskite " << j + 1 << " namu darbo ivertinima: ";
            while (!(cin >> studentai[i].nd[j]) || studentai[i].nd[j] < 0 || studentai[i].nd[j] > 10) {
                clearInput();
                cout << "Neteisinga ivestis. Bandykite dar karta: ";
            }
        }
        cout << "Iveskite studento egzamino ivertinima: ";
        while (!(cin >> studentai[i].egz) || studentai[i].egz < 0 || studentai[i].egz > 10) {
            clearInput();
            cout << "Neteisinga ivestis. Bandykite dar karta: ";
        }
    }

    char pasirinkimas;
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

    for (int i = 0; i < n; i++) {
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

    return 0;
}