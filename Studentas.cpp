#include "Studentas.h"
#include "Mylib.h"
#include <fstream>
#include <iomanip>

char rikiavimas; // Define the global variable

double Mediana(const vector<int>& vec) {
    vector<int> sortedVec = vec;
    std::sort(sortedVec.begin(), sortedVec.end());
    int n = sortedVec.size();
    if (n % 2 == 0) {
        return (sortedVec[n / 2 - 1] + sortedVec[n / 2]) / 2.0;
    } else {
        return sortedVec[n / 2];
    }
}

void clearInput() {
    cin.clear();
    cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
}

string generuotiVarda() {
    const vector<string> vardai = {"Jonas", "Petras", "Tauras", "Antanas", "Marius", "Ugnius", "Vainius", "Darius", "Tomas", "Rokas", "Mantas", "Mindaugas", "Lukas", "Laurynas", "Karolis"};
    return vardai[std::rand() % vardai.size()];
}

string generuotiPavarde() {
    const vector<string> pavardes = {"Jonaitis", "Petraitis", "Kazlauskas", "Jankauskas", "Pavardenis", "Butkus", "Zukauskas", "Balciunas", "Stankevicius", "Urbonas", "Petrauskas"};
    return pavardes[std::rand() % pavardes.size()];
}

// Funkcija, skirta skaityti studentu duomenis is failo
bool skaitymas(vector<Studentas>& studentai, const string& failoPav) {
    ifstream inFile(failoPav);
    if (!inFile) {
        cerr << "Nepavyko atidaryti failo: " << failoPav << endl;
        return false;
    }

    string line;
    while (getline(inFile, line)) {
        istringstream iss(line);
        Studentas student;
        // Assume the file format is: vardas pavarde nd1 nd2 ... egz
        if (!(iss >> student.var >> student.pav)) {
            cerr << "Klaida skaitant studento duomenis" << endl;
            continue;
        }
        int nd;
        while (iss >> nd) {
            student.nd.push_back(nd);
        }
        if (!student.nd.empty()) {
            student.egz = student.nd.back();
            student.nd.pop_back();
        }
        studentai.push_back(student);

        // Process in chunks to avoid memory overflow
        if (studentai.size() >= 4000000) {
            // Process the current chunk
            sortAndOutputStudents(studentai);
            studentai.clear(); // Clear the vector to free memory
        }
    }

    // Process any remaining students
    if (!studentai.empty()) {
        sortAndOutputStudents(studentai);
    }

    return true;
}

// Funkcija, skirta spausdinti studentu duomenis
void spausdinti(const vector<Studentas>& studentai, std::ostream& out) {
    out << left << setw(15) << "Vardas" << setw(20) << "Pavarde" << setw(20) << "Galutinis (Vid.)" << setw(20) << "Galutinis (Med.)" << endl;
    out << "---------------------------------------------------------------------" << endl;

    for (const auto& student : studentai) {
        double galutinis1 = 0.0;
        double galutinis2 = 0.0;
        double vidurkis = 0.0;
        for (const auto& grade : student.nd) {
            vidurkis += grade;
        }
        vidurkis /= student.nd.size();
        galutinis1 = 0.4 * vidurkis + 0.6 * student.egz;
        double mediana = Mediana(student.nd);
        galutinis2 = 0.4 * mediana + 0.6 * student.egz;
        out << left << setw(15) << student.var << setw(20) << student.pav << setw(20) << fixed << setprecision(2) << galutinis1 << setw(20) << fixed << setprecision(2) << galutinis2 << endl;
    }
}

// Funkcija, skirta rusiavimui ir isvedimui
void sortAndOutputStudents(vector<Studentas>& studentai) {
    vector<Studentas> vargsai, kietakai;

    for (const auto& student : studentai) {
        double vidurkis = 0.0;
        for (const auto& grade : student.nd) {
            vidurkis += grade;
        }
        vidurkis /= student.nd.size();
        double galutinis = 0.4 * vidurkis + 0.6 * student.egz;

        if (galutinis < 5.0) {
            vargsai.push_back(student);
        } else {
            kietakai.push_back(student);
        }
    }

    auto sortFunction = [](const Studentas& a, const Studentas& b) {
        if (rikiavimas == 'a') {
            double avgA = 0.0, avgB = 0.0;
            for (const auto& grade : a.nd) avgA += grade;
            avgA = avgA / a.nd.size() * 0.4 + a.egz * 0.6;
            for (const auto& grade : b.nd) avgB += grade;
            avgB = avgB / b.nd.size() * 0.4 + b.egz * 0.6;
            return avgA < avgB;
        } else if (rikiavimas == 'm') {
            double medA = Mediana(a.nd) * 0.4 + a.egz * 0.6;
            double medB = Mediana(b.nd) * 0.4 + b.egz * 0.6;
            return medA < medB;
        }
        return false;
    };

    std::sort(vargsai.begin(), vargsai.end(), sortFunction);
    std::sort(kietakai.begin(), kietakai.end(), sortFunction);

    ofstream outFileVargsai("vargsai.txt", ios::app);
    ofstream outFileKietakai("kietakai.txt", ios::app);

    spausdinti(vargsai, outFileVargsai);
    spausdinti(kietakai, outFileKietakai);

    outFileVargsai.close();
    outFileKietakai.close();

    cout << "Failai vargsai.txt ir kietakai.txt sekmingai sukurti.\n";
}

// Funkcija, skirta ivesti studentu duomenis
void ivestiStudentus(vector<Studentas>& studentai) {
    char continueInput;
    do {
        Studentas student;
        cout << "Iveskite studento varda: ";
        cin >> student.var;
        cout << "Iveskite studento pavarde: ";
        cin >> student.pav;

        cout << "Ar norite generuoti atsitiktinius balus? (t - taip, n - ne): ";
        char pasirinkimas;
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
}

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

// Funkcija, skirta generuoti studentu failus
void generateStudentFiles() {
    const vector<int> studentCounts = {1000, 10000, 100000, 1000000, 10000000};
    for (int count : studentCounts) {
        auto start = high_resolution_clock::now(); // Start timing for each file

        string fileName = "studentai" + to_string(count) + ".txt";
        ofstream outFile(fileName);
        if (!outFile) {
            throw std::runtime_error("Nepavyko sukurti failo: " + fileName);
        }

        for (int i = 1; i <= count; ++i) {
            outFile << "Vardas" << i << " Pavarde" << i;
            int ndSkaicius = std::rand() % 10 + 1; // Generuojame nuo 1 iki 10 namu darbu
            for (int j = 0; j < ndSkaicius; ++j) {
                outFile << " " << std::rand() % 11; // Generuojame balus nuo 0 iki 10
            }
            outFile << " " << std::rand() % 11 << "\n"; // Generuojame egzamino bala nuo 0 iki 10
        }

        outFile.close();

        auto end = high_resolution_clock::now(); // End timing for each file
        auto duration = duration_cast<std::chrono::seconds>(end - start);
        cout << "Failas " << fileName << " sekmingai sukurtas per " << duration.count() << " s.\n";
    }
}

// Define the missing function
void rikiuotiStudentus(vector<Studentas>& studentai, char rikiavimas) {
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
}