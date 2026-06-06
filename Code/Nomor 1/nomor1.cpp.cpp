#include <iostream>
#include <vector>
#include <string>
#include <ctime>
#include <iomanip>
#include <cstdlib>

using namespace std;

const int MAX_PARKIR = 15;

struct Mobil {
    string plat;
    string merk;
    string warna;
    time_t waktuMasuk;
};

struct Petugas {
    string nama;
    string id;
};

vector<Mobil> daftarMobil;
Petugas petugas;

void garis() {
    cout << "==========================================================\n";
}

void tampilHeader() {
    garis();
    cout << "               SISTEM PARKIR MOBIL MALL USU\n";
    garis();
}

void dataPetugas() {
    tampilHeader();
    cout << "\nSilakan masukkan data petugas yang bertugas hari ini\n\n";
    cout << "Nama Petugas : ";
    getline(cin, petugas.nama);
    cout << "ID Petugas   : ";
    getline(cin, petugas.id);
    cout << "\nData berhasil disimpan!\n";
}

void tampilMenu() {
    int sisaSlot = MAX_PARKIR - daftarMobil.size();
    tampilHeader();
    cout << "Petugas : " << petugas.nama << endl;
    cout << "ID      : " << petugas.id << endl;
    cout << "\nKapasitas Parkir : " << MAX_PARKIR << " Mobil";
    cout << "\nMobil Terparkir  : " << daftarMobil.size() << " Mobil";
    cout << "\nSisa Slot        : " << sisaSlot << " Mobil\n";
    garis();
    cout << "\n[1] Tambah Kendaraan";
    cout << "\n[2] Lihat Kendaraan Terparkir";
    cout << "\n[3] Pembayaran Kendaraan";
    cout << "\n[4] Data Petugas";
    cout << "\n[5] Keluar Program";
    cout << "\n\nMasukkan Pilihan : ";
}

void tambahMobil() {
    int jumlah;
    garis();
    cout << "              TAMBAH DATA KENDARAAN\n";
    garis();
    cout << "\nJumlah kendaraan yang akan diparkir : ";
    cin >> jumlah;
    if (daftarMobil.size() + jumlah > MAX_PARKIR) {
        garis();
        cout << "PARKIRAN PENUH!\n";
        cout << "Maaf, kapasitas parkir Mall USU hanya\n";
        cout << "dapat menampung 15 kendaraan.\n";
        garis();
        return;
    }
    cin.ignore();
    for (int i = 0; i < jumlah; i++) {
        Mobil mobil;
        cout << "\n------------- Mobil Ke-" << i + 1 << " -------------\n";
        cout << "Plat Nomor  : ";
        getline(cin, mobil.plat);
        cout << "Merk Mobil  : ";
        getline(cin, mobil.merk);
        cout << "Warna Mobil : ";
        getline(cin, mobil.warna);
        mobil.waktuMasuk = time(0);
        daftarMobil.push_back(mobil);
    }
    cout << "\nData kendaraan berhasil ditambahkan!\n";
}

void tampilMobil() {
    garis();
    cout << "           DAFTAR KENDARAAN TERPARKIR\n";
    garis();
    if (daftarMobil.empty()) {
        cout << "\nBelum ada kendaraan yang parkir.\n";
        return;
    }
    cout << left
         << setw(5) << "No"
         << setw(15) << "Plat"
         << setw(20) << "Merk"
         << setw(12) << "Warna"
         << "Durasi\n";
    garis();
    for (int i = 0; i < daftarMobil.size(); i++) {
        time_t sekarang = time(0);
        int durasi = sekarang - daftarMobil[i].waktuMasuk;
        int jam = durasi / 3600;
        int menit = (durasi % 3600) / 60;
        int detik = durasi % 60;
        cout << left
             << setw(5) << i + 1
             << setw(15) << daftarMobil[i].plat
             << setw(20) << daftarMobil[i].merk
             << setw(12) << daftarMobil[i].warna
             << jam << "j "
             << menit << "m "
             << detik << "d"
             << endl;
    }
    garis();
}

void pembayaran() {
    garis();
    cout << "                 PEMBAYARAN PARKIR\n";
    garis();
    if (daftarMobil.empty()) {
        cout << "\nTidak ada kendaraan yang parkir.\n";
        return;
    }
    string cariPlat;
    cin.ignore();
    cout << "\nMasukkan Plat Nomor : ";
    getline(cin, cariPlat);
    bool ditemukan = false;
    for (int i = 0; i < daftarMobil.size(); i++) {
        Mobil *ptr = &daftarMobil[i];
        if (ptr->plat == cariPlat) {
            ditemukan = true;
            time_t sekarang = time(0);
            int durasi = sekarang - ptr->waktuMasuk;
            int jam = durasi / 3600;
            int biaya;
            if (jam <= 1)
                biaya = 5000;
            else
                biaya = 5000 + ((jam - 1) * 3000);
            cout << "\nData Kendaraan Ditemukan\n";
            cout << "\nPlat Nomor : " << ptr->plat;
            cout << "\nMerk       : " << ptr->merk;
            cout << "\nWarna      : " << ptr->warna;
            cout << "\n\nDurasi Parkir : " << jam << " Jam";
            cout << "\nBiaya Parkir  : Rp" << biaya << endl;
            daftarMobil.erase(daftarMobil.begin() + i);
            cout << "\nPembayaran Berhasil!\n";
            cout << "Terima Kasih.\n";
            break;
        }
    }
    if (!ditemukan) {
        cout << "\nPlat kendaraan tidak ditemukan!\n";
    }
}

int main() {
    system("cls");
    dataPetugas();
    int pilihan;
    do {
        tampilMenu();
        cin >> pilihan;
        switch (pilihan) {
            case 1:
                tambahMobil();
                break;
            case 2:
                tampilMobil();
                break;
            case 3:
                pembayaran();
                break;
            case 4:
                garis();
                cout << "DATA PETUGAS\n";
                garis();
                cout << "Nama : " << petugas.nama << endl;
                cout << "ID   : " << petugas.id << endl;
                break;
            case 5:
                garis();
                cout << "Terima kasih telah menggunakan\n";
                cout << "Sistem Parkir Mobil Mall USU\n";
                garis();
                break;
            default:
                cout << "\nPilihan tidak tersedia!\n";
        }
        if (pilihan != 5) {
            cout << "\n\nTekan Enter untuk kembali ke menu...";
            cin.ignore();
            cin.get();
        }
    } while (pilihan != 5);
    return 0;
}
