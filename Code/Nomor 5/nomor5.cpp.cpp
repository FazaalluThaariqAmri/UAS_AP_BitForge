#include <iostream>
#include <string>
#include <cstdlib>
#include <ctime>
using namespace std;

struct Negara {
    string nama;
    string hint;
};

string buatHint(string nama) {
    string hint = nama;
    int panjang = nama.length();
        
    int jumlahSembunyi = panjang / 2;

    for (int i = 0; i < jumlahSembunyi; i++) {
        int posisi;
        do {
            posisi = rand() % panjang;
        } while (hint[posisi] == '_' || posisi == 0); 
        hint[posisi] = '_';
    }

    return hint;
}

string toLower(string s) {
    for (int i = 0; i < s.length(); i++) {
        if (s[i] >= 'A' && s[i] <= 'Z') {
            s[i] = s[i] + 32;
        }
    }
    return s;
}

int main() {
    srand(time(0));

    const int TOTAL_NEGARA = 20;
    Negara dataNegara[TOTAL_NEGARA];

    dataNegara[0].nama  = "indonesia";
    dataNegara[1].nama  = "malaysia";
    dataNegara[2].nama  = "singapura";
    dataNegara[3].nama  = "thailand";
    dataNegara[4].nama  = "vietnam";
    dataNegara[5].nama  = "filipina";
    dataNegara[6].nama  = "brunei";
    dataNegara[7].nama  = "myanmar";
    dataNegara[8].nama  = "kamboja";
    dataNegara[9].nama  = "laos";
    dataNegara[10].nama = "norway";
    dataNegara[11].nama = "sweden";
    dataNegara[12].nama = "denmark";
    dataNegara[13].nama = "jerman";
    dataNegara[14].nama = "prancis";
    dataNegara[15].nama = "jepang";
    dataNegara[16].nama = "china";
    dataNegara[17].nama = "india";
    dataNegara[18].nama = "brazil";
    dataNegara[19].nama = "mesir";

    for (int i = 0; i < TOTAL_NEGARA; i++) {
        dataNegara[i].hint = buatHint(dataNegara[i].nama);
    }

    int skor = 0;
    string jawaban;
    char lanjut;

    while (true) {
        
        int index = rand() % TOTAL_NEGARA;
        Negara dipilih = dataNegara[index];

        
        dipilih.hint = buatHint(dipilih.nama);

        cout << "Tebak negara: " << dipilih.hint << endl;
        cout << "Jawaban: ";
        cin >> jawaban;
        jawaban = toLower(jawaban);

        if (jawaban == dipilih.nama) {
            skor++;
            cout << "Selamat! Anda benar." << endl;
            cout << "Skor Anda: " << skor << endl;
            cout << endl;
            
        } else {
            cout << "Maaf, jawaban Anda salah." << endl;
            cout << "Jawaban yang benar: " << dipilih.nama << endl;
            cout << "Skor Anda: " << skor << endl;
            cout << "Ingin bermain lagi? (y/n): ";
            cin >> lanjut;
            cout << endl;
            if (lanjut == 'n' || lanjut == 'N') {
                break;
            } else {
                skor = 0; 
                cout << "Skor direset. Mulai dari awal!" << endl;
                cout << endl;
            }
        }
    }

    cout << "Game Selesai" << endl;
    cout << "Skor akhir Anda: " << skor << endl;

    return 0;
}
