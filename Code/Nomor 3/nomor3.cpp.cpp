#include <iostream>
#include <vector>
#include <string>
#include <iomanip>

using namespace std;

struct Barang {
    string kodeBarang;
    string namaBarang;
    double hargaBarang;
    int stokBarang;
};

vector<Barang> daftarBarang;

void tambahBarang(vector<Barang>& daftarBarang)
{
    Barang barang;

    cout << "\n=== Tambah Barang ===\n";

    cout << "Kode Barang : ";
    cin >> barang.kodeBarang;

    cin.ignore();

    cout << "Nama Barang : ";
    getline(cin, barang.namaBarang);

    do
    {
        cout << "Harga : ";
        cin >> barang.hargaBarang;

        if(barang.hargaBarang < 0)
        {
            cout << "Error! Harga tidak boleh negatif.\n";
        }

    } while(barang.hargaBarang < 0);

    do
    {
        cout << "Stok : ";
        cin >> barang.stokBarang;

        if(barang.stokBarang < 0)
        {
            cout << "Error! Stok tidak boleh negatif.\n";
        }

    } while(barang.stokBarang < 0);

    daftarBarang.push_back(barang);

    cout << "Barang berhasil ditambahkan!\n";
}

void tampilkanBarang(const vector<Barang>& daftarBarang)
{
    cout << "\n=== Daftar Barang ===\n";

    if(daftarBarang.empty())
    {
        cout << "Belum ada data.\n";
        return;
    }

    cout << left
         << setw(15) << "Kode"
         << setw(25) << "Nama"
         << setw(15) << "Harga"
         << setw(10) << "Stok"
         << endl;

    cout << string(65,'-') << endl;

    for(const Barang& barang : daftarBarang)
    {
        cout << left
             << setw(15) << barang.kodeBarang
             << setw(25) << barang.namaBarang
             << setw(15) << barang.hargaBarang
             << setw(10) << barang.stokBarang
             << endl;
    }
}

void cariBarangTermahal(const vector<Barang>& daftarBarang)
{
    if(daftarBarang.empty())
    {
        cout << "Data kosong.\n";
        return;
    }

    Barang termahal = daftarBarang[0];

    for(const Barang& barang : daftarBarang)
    {
        if(barang.hargaBarang > termahal.hargaBarang)
        {
            termahal = barang;
        }
    }

    cout << "\n=== Barang Termahal ===\n";
    cout << "Kode  : " << termahal.kodeBarang << endl;
    cout << "Nama  : " << termahal.namaBarang << endl;
    cout << "Harga : " << termahal.hargaBarang << endl;
    cout << "Stok  : " << termahal.stokBarang << endl;
}

void hitungTotalInventaris(const vector<Barang>& daftarBarang)
{
    double total = 0;

    for(const Barang& barang : daftarBarang)
    {
        total += barang.hargaBarang * barang.stokBarang;
    }

    cout << "\nTotal Nilai Inventaris : Rp "
         << total << endl;
}

void cekRestock(const vector<Barang>& daftarBarang)
{
    cout << "\n=== Barang Perlu Restock ===\n";

    bool ditemukan = false;

    for(const Barang& barang : daftarBarang)
    {
        if(barang.stokBarang < 5)
        {
            cout << barang.kodeBarang
                 << " - "
                 << barang.namaBarang
                 << " (Stok: "
                 << barang.stokBarang
                 << ")\n";

            ditemukan = true;
        }
    }

    if(!ditemukan)
    {
        cout << "Tidak ada barang yang perlu restock.\n";
    }
}

void updateStok(vector<Barang>& daftarBarang)
{
    string kode;

    cout << "\nMasukkan kode barang : ";
    cin >> kode;

    for(Barang& barang : daftarBarang)
    {
        if(barang.kodeBarang == kode)
        {
            int* ptrStok = &barang.stokBarang;

            int perubahan;

            cout << "Stok saat ini : "
                 << *ptrStok << endl;

            cout << "Perubahan stok (+/-) : ";
            cin >> perubahan;

            *ptrStok += perubahan;

            if(*ptrStok < 0)
            {
                *ptrStok = 0;
            }

            cout << "Stok berhasil diperbarui.\n";
            return;
        }
    }

    cout << "Barang tidak ditemukan.\n";
}

int main()
{
    vector<Barang> daftarBarang;
    int pilihan;

    do
    {
        cout << "\n===== SISTEM INVENTARIS TOKO =====\n";
        cout << "1. Tambah Barang\n";
        cout << "2. Tampilkan Semua Barang\n";
        cout << "3. Cari Barang Termahal\n";
        cout << "4. Hitung Total Nilai Inventaris\n";
        cout << "5. Cek Restock\n";
        cout << "6. Update Stok\n";
        cout << "7. Keluar\n";
        cout << "Pilihan : ";
        if (!(cin >> pilihan))
        {
            cout << "Input tidak valid!\n";

            cin.clear();
            cin.ignore(1000, '\n');

            continue;
        }

        switch(pilihan)
        {
            case 1:
                tambahBarang(daftarBarang);
                break;

            case 2:
                tampilkanBarang(daftarBarang);
                break;

            case 3:
                cariBarangTermahal(daftarBarang);
                break;

            case 4:
                hitungTotalInventaris(daftarBarang);
                break;

            case 5:
                cekRestock(daftarBarang);
                break;

            case 6:
                updateStok(daftarBarang);
                break;

            case 7:
                cout << "Program selesai.\n";
                break;

            default:
                cout << "Pilihan tidak valid.\n";
        }

    } while(pilihan != 7);

    return 0;
}
