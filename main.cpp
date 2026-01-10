#include <iostream>
#include <limits>
#include "playlist.h"
using namespace std;

void tampilkanMenu() {
    cout << "\n==============================================\n";
    cout << "   SISTEM PLAYLIST (MLL: GENRE + BST: LAGU)\n";
    cout << "==============================================\n";
    cout << "1. Tambah Lagu (Input Genre)\n";
    cout << "2. Lihat Semua Playlist (Per Genre)\n";
    cout << "3. Lihat Playlist Genre Tertentu\n";
    cout << "4. Cari Lagu (Judul)\n";
    cout << "5. Cari Lagu (Artis)\n";
    cout << "6. Hapus Lagu (Dari semua genre)\n";
    cout << "7. Statistik Global\n";
    cout << "8. Keluar\n";
    cout << "==============================================\n";
    cout << "Pilihan: ";
}

int main() {
    PlaylistMusik playlist;
    int pilihan;
    
    while (true) {
        tampilkanMenu();
        cin >> pilihan;
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
        
        switch (pilihan) {
            case 1: {
                string genre, judul, artis;
                int durasi;
                
                cout << "Genre (ex: Pop, Rock): ";
                getline(cin, genre);
                cout << "Judul Lagu: ";
                getline(cin, judul);
                cout << "Nama Artis: ";
                getline(cin, artis);
                cout << "Durasi (detik): ";
                cin >> durasi;
                
                playlist.tambahLagu(genre, judul, artis, durasi);
                break;
            }
            case 2:
                playlist.lihatSemuaLagu();
                break;
            case 3: {
                string genre;
                cout << "Masukkan nama genre: ";
                getline(cin, genre);
                playlist.lihatLaguPerGenre(genre);
                break;
            }
            case 4: {
                string judul;
                cout << "Masukkan judul dicari: ";
                getline(cin, judul);
                playlist.cariLagu(judul);
                break;
            }
            case 5: {
                string artis;
                cout << "Masukkan nama artis: ";
                getline(cin, artis);
                playlist.cariLaguByArtis(artis);
                break;
            }
            case 6: {
                string judul;
                cout << "Hapus lagu berjudul: ";
                getline(cin, judul);
                playlist.hapusLagu(judul);
                break;
            }
            case 7:
                playlist.tampilkanStatistikGlobal();
                break;
            case 8:
                return 0;
            default:
                cout << "Input salah.\n";
        }
    }
    return 0;
}