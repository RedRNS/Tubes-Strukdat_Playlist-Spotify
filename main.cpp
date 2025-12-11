#include <iostream>
#include <limits>
#include "playlist.h"
using namespace std;

// ============================================================
// SISTEM MENU UTAMA (DRIVER - ADT INTERFACE)
// ============================================================
void tampilkanMenu() {
    cout << "\n========================================\n";
    cout << "   SISTEM MANAJEMEN PLAYLIST MUSIK\n";
    cout << "========================================\n";
    cout << "1. Tambah Lagu / Update Lagu yang Ada\n";
    cout << "2. Lihat Playlist (Traversal)\n";
    cout << "3. Cari Lagu berdasarkan Judul\n";
    cout << "4. Cari Lagu berdasarkan Artis\n";
    cout << "5. Hapus Lagu\n";
    cout << "6. Statistik (Total, Terpanjang, Terpendek)\n";
    cout << "7. Filter Lagu\n";
    cout << "8. Keluar\n";
    cout << "========================================\n";
    cout << "Masukkan pilihan Anda: ";
}

int main() {
    PlaylistMusik playlist;
    int pilihan;
    
    cout << "Selamat Datang di Pengelola Playlist Musik!\n";
    cout << "Menggunakan Struktur Data Binary Search Tree\n";
    
    while (true) {
        tampilkanMenu();
        cin >> pilihan;
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
        
        switch (pilihan) {
            case 1: {
                // Tambah atau Update Lagu
                string judul, artis;
                
                cout << "\n--- Tambah Lagu Baru / Update Lagu ---\n";
                cout << "Masukkan judul lagu: ";
                getline(cin, judul);
                
                cout << "Masukkan nama artis: ";
                getline(cin, artis);
                
                // Cek dulu apakah lagu sudah ada
                bool sudahAda = playlist.masukkanAtauUpdate(judul, artis);
                
                // Jika lagu belum ada, baru tanyakan durasi
                if (!sudahAda) {
                    int durasi;
                    cout << "Masukkan durasi (detik): ";
                    cin >> durasi;
                    cin.ignore(numeric_limits<streamsize>::max(), '\n');
                    playlist.masukkanLaguBaru(judul, artis, durasi);
                }
                
                break;
            }
            
            case 2: {
                // Lihat Playlist
                cout << "\n--- Lihat Playlist ---\n";
                cout << "1. Inorder (Terurut Alfabetis)\n";
                cout << "2. Preorder\n";
                cout << "3. Postorder\n";
                cout << "Pilih tipe traversal: ";
                
                int pilihanTraversal;
                cin >> pilihanTraversal;
                cin.ignore(numeric_limits<streamsize>::max(), '\n');
                
                playlist.lihatPlaylist(pilihanTraversal);
                
                break;
            }
            
            case 3: {
                // Cari berdasarkan Judul
                string judul;
                cout << "\n--- Cari berdasarkan Judul ---\n";
                cout << "Masukkan judul lagu: ";
                getline(cin, judul);
                
                playlist.cari(judul);
                
                break;
            }
            
            case 4: {
                // Cari berdasarkan Artis
                string artis;
                cout << "\n--- Cari berdasarkan Artis ---\n";
                cout << "Masukkan nama artis: ";
                getline(cin, artis);
                
                playlist.cariMenurutArtis(artis);
                
                break;
            }
            
            case 5: {
                // Hapus Lagu
                string judul;
                cout << "\n--- Hapus Lagu ---\n";
                cout << "Masukkan judul lagu yang akan dihapus: ";
                getline(cin, judul);
                
                playlist.hapusLagu(judul);
                
                break;
            }
            
            case 6: {
                // Statistik
                playlist.tampilkanStatistik();
                
                break;
            }
            
            case 7: {
                // Filter Lagu
                cout << "\n--- Filter Lagu ---\n";
                cout << "1. Filter berdasarkan Tag/Genre\n";
                cout << "2. Filter berdasarkan Jumlah Tag\n";
                cout << "Pilih tipe filter: ";
                
                int pilihanFilter;
                cin >> pilihanFilter;
                cin.ignore(numeric_limits<streamsize>::max(), '\n');
                
                if (pilihanFilter == 1) {
                    string tag;
                    cout << "Masukkan tag/genre untuk filter: ";
                    getline(cin, tag);
                    playlist.filterBerdasarkanTag(tag);
                } else if (pilihanFilter == 2) {
                    int jumlahTag;
                    cout << "Masukkan jumlah tag (0-5): ";
                    cin >> jumlahTag;
                    cin.ignore(numeric_limits<streamsize>::max(), '\n');
                    playlist.filterBerdasarkanJumlahTag(jumlahTag);
                } else {
                    cout << "Pilihan tidak valid!\n";
                }
                
                break;
            }
            
            case 8: {
                // Keluar
                cout << "\nTerima kasih telah menggunakan Pengelola Playlist Musik!\n";
                cout << "Sampai jumpa!\n";
                return 0;
            }
            
            default: {
                cout << "\nPilihan tidak valid! Silakan coba lagi.\n";
                break;
            }
        }
    }
    
    return 0;
}
