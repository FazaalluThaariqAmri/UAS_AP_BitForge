#include <iostream>
#include <cstdlib>
#include <ctime>
using namespace std;

// Class utama permainan Minesweeper
class Minesweeper {
private:
    int n, bom;                     // Ukuran papan dan jumlah bom
    int papan[10][10];              // Menyimpan isi papan (-1 = bom)
    bool buka[10][10], tanda[10][10]; // Status buka dan tanda
    time_t mulai;                   // Waktu mulai permainan

public:

    // Membuat papan dan menanam bom
    void buatGame(int ukuran, int jumlahBom) {
        n = ukuran;
        bom = jumlahBom;

        // Inisialisasi papan
        for(int i=0;i<10;i++)
            for(int j=0;j<10;j++) {
                papan[i][j]=0;
                buka[i][j]=false;
                tanda[i][j]=false;
            }

        // Menempatkan bom secara acak
        int terpasang=0;
        while(terpasang<bom) {
            int r=rand()%n, c=rand()%n;
            if(papan[r][c]!=-1) {
                papan[r][c]=-1;
                terpasang++;
            }
        }

        // Menghitung jumlah bom di sekitar setiap kotak
        for(int i=0;i<n;i++) {
            for(int j=0;j<n;j++) {

                if(papan[i][j]==-1) continue;

                int hitung=0;

                for(int dr=-1;dr<=1;dr++)
                    for(int dc=-1;dc<=1;dc++) {

                        int nr=i+dr,nc=j+dc;

                        if(nr>=0 && nr<n &&
                           nc>=0 && nc<n &&
                           papan[nr][nc]==-1)
                            hitung++;
                    }

                papan[i][j]=hitung;
            }
        }

        // Mulai timer permainan
        mulai=time(0);
    }

    // Menampilkan papan ke layar
    void tampil() {

#ifdef _WIN32
        system("cls");
#else
        system("clear");
#endif

        cout<<"\n===== MINESWEEPER++ =====\n";
        cout<<"Bom : "<<bom<<"\n";
        cout<<"Waktu : "<<time(0)-mulai<<" detik\n\n";

        cout<<"   ";
        for(int i=0;i<n;i++) cout<<i+1<<" ";
        cout<<"\n";

        for(int i=0;i<n;i++) {

            cout<<i+1<<"  ";

            for(int j=0;j<n;j++) {

                if(tanda[i][j]) cout<<"F ";      // Kotak ditandai
                else if(!buka[i][j]) cout<<"# "; // Belum dibuka
                else if(papan[i][j]==0) cout<<". ";
                else cout<<papan[i][j]<<" ";
            }
            cout<<"\n";
        }
    }

    // Membuka area kosong secara otomatis
    void flood(int r,int c) {

        if(r<0||r>=n||c<0||c>=n) return;
        if(buka[r][c]||tanda[r][c]) return;

        buka[r][c]=true;

        if(papan[r][c]!=0) return;

        for(int dr=-1;dr<=1;dr++)
            for(int dc=-1;dc<=1;dc++)
                if(dr||dc) flood(r+dr,c+dc);
    }

    // Membuka kotak yang dipilih pemain
    bool bukaKotak(int r,int c) {

        if(tanda[r][c]) return false;

        if(papan[r][c]==-1)
            return true; // Kena bom

        flood(r,c);
        return false;
    }

    // Memberi atau menghapus tanda bom
    void tandai(int r,int c) {

        if(!buka[r][c])
            tanda[r][c]=!tanda[r][c];
    }

    // Mengecek apakah pemain menang
    bool menang() {

        for(int i=0;i<n;i++)
            for(int j=0;j<n;j++) {

                if(papan[i][j]==-1 && !tanda[i][j])
                    return false;

                if(papan[i][j]!=-1 && tanda[i][j])
                    return false;
            }

        return true;
    }

    // Menampilkan semua bom saat kalah
    void tampilBom() {

        cout<<"\n";

        for(int i=0;i<n;i++) {

        for(int j=0;j<n;j++) {

        if(papan[i][j]==-1)
                    cout<<"* ";
                else
                    cout<<papan[i][j]<<" ";
            }

            cout<<"\n";
        }
    }

    // Menghitung lama permainan
    int waktu() {
        return time(0)-mulai;
    }
};

int main() {

    srand(time(0)); // Mengaktifkan random

    int menu;

    do {

        // Menu utama
        cout<<"\n===== MENU =====\n";
        cout<<"1. Main\n";
        cout<<"2. Keluar\n";
        cout<<"Pilih : ";
        cin>>menu;

        if(menu==1) {

            int ukuran,bom;

            // Input ukuran papan
            do {
                cout<<"Ukuran papan (4-10): ";
                cin>>ukuran;
            } while(ukuran<4||ukuran>10);

            // Input jumlah bom
            do {
                cout<<"Jumlah bom: ";
                cin>>bom;
            } while(bom<1||bom>=ukuran*ukuran);

            Minesweeper game;
            game.buatGame(ukuran,bom);

            bool selesai=false;

            // Loop permainan
            while(!selesai) {

                game.tampil();

                char aksi;
                int r,c;

                cout<<"\nB = Buka\n";
                cout<<"T = Tandai\n";
                cout<<"Pilihan : ";
                cin>>aksi;

                cout<<"Baris : ";
                cin>>r;

                cout<<"Kolom : ";
                cin>>c;

                r--;
                c--;

                // Validasi koordinat
                if(r<0||r>=ukuran||
                   c<0||c>=ukuran) {
                    cout<<"Koordinat salah!\n";
                    continue;
                }

                // Membuka kotak
                if(aksi=='B'||aksi=='b') {

                    if(game.bukaKotak(r,c)) {

                        game.tampil();

                        cout<<"\nBOOM!\n";
                        cout<<"GAME OVER\n";

                        game.tampilBom();

                        cout<<"\nWaktu : "
                            <<game.waktu()
                            <<" detik\n";

                        selesai=true;
                    }
                }

                // Menandai bom
                else if(aksi=='T'||aksi=='t') {

                    game.tandai(r,c);

                    if(game.menang()) {

                        game.tampil();

                        cout<<"\nSELAMAT!\n";
                        cout<<"SEMUA BOM BERHASIL DITANDAI\n";

                        cout<<"Waktu : "
                            <<game.waktu()
                            <<" detik\n";

                        selesai=true;
                    }
                }
            }
        }

    } while(menu!=2);

    cout<<"\nTerima kasih telah bermain!\n";
    return 0;
}