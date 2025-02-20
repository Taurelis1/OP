#include <iostream>
#include <string>
#include <iomanip>
#include <algorithm>

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

int main() {
    int n = 0;
    cout << "Iveskite studentu skaiciu: ";
    cin >> n;
    Studentas studentai[MAX_STUD];

    for (int i = 0; i < n; i++) {
        cout << "Iveskite studento varda: ";
        cin >> studentai[i].var;
        cout << "Iveskite studento pavarde: ";
        cin >> studentai[i].pav;
        cout << "Iveskite studento atliktu namu darbu skaiciu: ";
        cin >> studentai[i].n;
        for (int j = 0; j < studentai[i].n; j++) {
            cout << "Iveskite " << j + 1 << " namu darbo ivertinima: ";
            cin >> studentai[i].nd[j];
        }
        cout << "Iveskite studento egzamino ivertinima: ";
        cin >> studentai[i].egz;
    }

    char pasirinkimas;
    cout << "Pasirinkite galutinio balo skaiciavimo buda (v - vidurkis, m - mediana): ";
    cin >> pasirinkimas;
    if (pasirinkimas == 'v') {
    cout << setw(15) << "Vardas" << setw(15) << "Pavarde" << setw(20) << "Galutinis (Vid.)" << endl;
    cout << "---------------------------------------------------------------------" << endl;
    } else if (pasirinkimas == 'm') {
    cout << setw(15) << "Vardas" << setw(15) << "Pavarde" << setw(20) << "Galutinis (Med.)" << endl;
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