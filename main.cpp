#include <iostream>
#include <limits>
#include "playlist.h"
using namespace std;

void tampilkanMenu() {
    cout << "\n============================================\n";
    cout << "     PLAYLIST MUSIK (MLL + BST)           \n";
    cout << "============================================\n";
    cout << "1.  Tambah Lagu\n";
    cout << "2.  Update Lagu\n";
    cout << "3.  Hapus Lagu\n";
    cout << "4.  Cari Lagu (Judul)\n";
    cout << "5.  Cari Lagu (Artis)\n";
    cout << "6.  Cari Lagu (Durasi)\n";
    cout << "7.  Lihat Semua Playlist\n";
    cout << "8.  Lihat Playlist per Genre\n";
    cout << "9.  Lihat dengan Traversal (Pre/In/Post/Level)\n";
    cout << "10. Statistik Global\n";
    cout << "11. Statistik per Genre\n";
    cout << "0.  Keluar\n";
    cout << "============================================\n";
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
                
                cout << "Genre: ";
                getline(cin, genre);
                cout << "Judul: ";
                getline(cin, judul);
                cout << "Artis: ";
                getline(cin, artis);
                cout << "Durasi (detik): ";
                cin >> durasi;
                
                playlist.tambahLagu(genre, judul, artis, durasi);
                break;
            }
            case 2: {
                string judul, artis;
                int durasi;
                
                cout << "Judul lagu yang diupdate: ";
                getline(cin, judul);
                cout << "Artis baru: ";
                getline(cin, artis);
                cout << "Durasi baru (detik): ";
                cin >> durasi;
                
                playlist.updateLagu(judul, artis, durasi);
                break;
            }
            case 3: {
                string judul;
                cout << "Judul lagu yang dihapus: ";
                getline(cin, judul);
                playlist.hapusLagu(judul);
                break;
            }
            case 4: {
                string judul;
                cout << "Cari judul: ";
                getline(cin, judul);
                playlist.cariLagu(judul);
                break;
            }
            case 5: {
                string artis;
                cout << "Cari artis: ";
                getline(cin, artis);
                playlist.cariLaguByArtis(artis);
                break;
            }
            case 6: {
                int durasi;
                cout << "Cari durasi (detik): ";
                cin >> durasi;
                playlist.cariLaguByDurasi(durasi);
                break;
            }
            case 7:
                playlist.lihatSemuaLagu();
                break;
            case 8: {
                string genre;
                cout << "Nama genre: ";
                getline(cin, genre);
                playlist.lihatLaguPerGenre(genre);
                break;
            }
            case 9: {
                string genre;
                int mode;
                cout << "Nama genre: ";
                getline(cin, genre);
                cout << "Mode (1=Preorder, 2=Inorder, 3=Postorder, 4=LevelOrder): ";
                cin >> mode;
                playlist.lihatDenganTraversal(genre, mode);
                break;
            }
            case 10:
                playlist.tampilkanStatistikGlobal();
                break;
            case 11:
                playlist.tampilkanStatistikPerGenre();
                break;
            case 0:
                cout << "Keluar program.\n";
                return 0;
            default:
                cout << "Pilihan tidak valid.\n";
        }
    }
    return 0;
}