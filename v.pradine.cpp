#include <iostream>
#include <string>
#include <iomanip>

using std::string;
using std::cout;
using std::cin;
using std::endl;
using std::fixed;
using std::setprecision;

const int MAX_STUD = 100; // Maximum number of students
const int MAX_ND = 10; // Maximum number of homework assignments

struct Studentas {
    string var;
    string pav;
    int n;
    int nd[MAX_ND];
    int egz;
};

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
	cout << "Vardas Pavarde Galutinis (Vid.)" << endl;
	cout << "--------------------------------" << endl;
    for (int i = 0; i < n; i++) {
        double vidurkis = 0.0;
        for (int j = 0; j < studentai[i].n; j++) {
            vidurkis += studentai[i].nd[j];
        }
        vidurkis /= studentai[i].n;
        double galutinis = 0.4 * vidurkis + 0.6 * studentai[i].egz;
        cout << studentai[i].var << " " << studentai[i].pav << " " << fixed << setprecision(2) << galutinis << endl;
    }

    return 0;
}
