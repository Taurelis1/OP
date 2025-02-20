#include <iostream>
#include <string>
#include <iomanip>
#include <algorithm>
#include <vector>
#include <limits>

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

double Mediana(vector<int>& vec) {
    std::sort(vec.begin(), vec.end());
    int n = vec.size();
    if (n % 2 == 0) {
        return (vec[n / 2 - 1] + vec[n / 2]) / 2.0;
    } else {
        return vec[n / 2];
    }
}

void clearInput() {
    cin.clear();
    cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
}

int main() {
    int m = 0;
    cout << "Iveskite studentu skaiciu: ";
    while (!(cin >> m) || m <= 0) {
        clearInput();
        cout << "Neteisinga ivestis. Bandykite dar karta: ";
    }

    vector<Studentas> studentai(m);

    for (int i = 0; i < m; i++) {
        cout << "Iveskite studento varda: ";
        cin >> studentai[i].var;
        cout << "Iveskite studento pavarde: ";
        cin >> studentai[i].pav;

        int n = 0;
        cout << "Iveskite studento atliktu namu darbu skaiciu: ";
        while (!(cin >> n) || n <= 0) {
            clearInput();
            cout << "Neteisinga ivestis. Bandykite dar karta: ";
        }

        studentai[i].nd.resize(n);
        for (int j = 0; j < n; j++) {
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

    for (int i = 0; i < m; i++) {
        double galutinis = 0.0;
        if (pasirinkimas == 'v') {
            double vidurkis = 0.0;
            for (int j = 0; j < studentai[i].nd.size(); j++) {
                vidurkis += studentai[i].nd[j];
            }
            vidurkis /= studentai[i].nd.size();
            galutinis = 0.4 * vidurkis + 0.6 * studentai[i].egz;
            cout << setw(15) << studentai[i].var << setw(15) << studentai[i].pav << setw(20) << fixed << setprecision(2) << galutinis << endl;
        } else if (pasirinkimas == 'm') {
            double mediana = Mediana(studentai[i].nd);
            galutinis = 0.4 * mediana + 0.6 * studentai[i].egz;
            cout << setw(15) << studentai[i].var << setw(15) << studentai[i].pav << setw(20) << fixed << setprecision(2) << galutinis << endl;
        }
    }

    return 0;
}