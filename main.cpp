#include <iostream>
#include <string>
#include <limits>
using namespace std;

// ============================================================
// STRUKTUR NODE - Lagu dalam BST (Kunci: judul)
// ============================================================
struct Lagu {
    string judul;        // Kunci BST (harus unik)
    string artis;
    int durasi;          // dalam detik
    string tag[5];       // Array untuk genre/mood
    int jumlahTag;       // Jumlah tag yang tersimpan
    Lagu* kiri;
    Lagu* kanan;
    
    // Konstruktor
    Lagu(string j, string a, int d) {
        judul = j;
        artis = a;
        durasi = d;
        jumlahTag = 0;
        kiri = nullptr;
        kanan = nullptr;
    }
};

// ============================================================
// KELAS BST - Playlist Musik
// ============================================================
class PlaylistMusik {
private:
    Lagu* akar;
    
    // Helper: Masukkan lagu ke BST (berdasarkan perbandingan judul)
    Lagu* masukkanHelper(Lagu* node, string judul, string artis, int durasi) {
        // Kasus dasar: tempat kosong ditemukan, buat node baru
        if (node == nullptr) {
            cout << "Lagu '" << judul << "' berhasil ditambahkan!\n";
            return new Lagu(judul, artis, durasi);
        }
        
        // Jika judul sudah ada, kembalikan node yang ada (ditangani di fungsi publik)
        if (judul == node->judul) {
            return node;
        }
        
        // Logika BST: Masukkan kiri atau kanan berdasarkan perbandingan alfabetis
        if (judul < node->judul) {
            node->kiri = masukkanHelper(node->kiri, judul, artis, durasi);
        } else {
            node->kanan = masukkanHelper(node->kanan, judul, artis, durasi);
        }
        
        return node;
    }
    
    // Helper: Cari berdasarkan judul
    Lagu* cariJudul(Lagu* node, string judul) {
        if (node == nullptr || node->judul == judul) {
            return node;
        }
        
        if (judul < node->judul) {
            return cariJudul(node->kiri, judul);
        } else {
            return cariJudul(node->kanan, judul);
        }
    }
    
    // Helper: Cari berdasarkan artis (menemukan semua yang cocok)
    void cariArtis(Lagu* node, string artis, int& jumlah) {
        if (node == nullptr) return;
        
        cariArtis(node->kiri, artis, jumlah);
        
        if (node->artis == artis) {
            jumlah++;
            tampilkanLagu(node);
        }
        
        cariArtis(node->kanan, artis, jumlah);
    }
    
    // Helper: Temukan node dengan nilai minimum (paling kiri)
    Lagu* cariMin(Lagu* node) {
        while (node->kiri != nullptr) {
            node = node->kiri;
        }
        return node;
    }
    
    // Helper: Hapus lagu dari BST
    Lagu* hapusHelper(Lagu* node, string judul, bool& terhapus) {
        if (node == nullptr) {
            return nullptr;
        }
        
        // Cari node yang akan dihapus
        if (judul < node->judul) {
            node->kiri = hapusHelper(node->kiri, judul, terhapus);
        } else if (judul > node->judul) {
            node->kanan = hapusHelper(node->kanan, judul, terhapus);
        } else {
            // Node ditemukan! Tangani 3 kasus:
            terhapus = true;
            
            // Kasus 1: Node daun (tidak punya anak)
            if (node->kiri == nullptr && node->kanan == nullptr) {
                delete node;
                return nullptr;
            }
            // Kasus 2: Satu anak (kanan saja)
            else if (node->kiri == nullptr) {
                Lagu* temp = node->kanan;
                delete node;
                return temp;
            }
            // Kasus 3: Satu anak (kiri saja)
            else if (node->kanan == nullptr) {
                Lagu* temp = node->kiri;
                delete node;
                return temp;
            }
            // Kasus 4: Dua anak
            else {
                // Temukan successor inorder (min di subtree kanan)
                Lagu* pengganti = cariMin(node->kanan);
                
                // Salin data pengganti ke node saat ini
                node->judul = pengganti->judul;
                node->artis = pengganti->artis;
                node->durasi = pengganti->durasi;
                for (int i = 0; i < pengganti->jumlahTag; i++) {
                    node->tag[i] = pengganti->tag[i];
                }
                node->jumlahTag = pengganti->jumlahTag;
                
                // Hapus pengganti
                node->kanan = hapusHelper(node->kanan, pengganti->judul, terhapus);
            }
        }
        return node;
    }
    
    // Helper: Traversal Inorder (Kiri, Akar, Kanan) - Urutan terurut
    void inorder(Lagu* node) {
        if (node == nullptr) return;
        
        inorder(node->kiri);
        tampilkanLagu(node);
        inorder(node->kanan);
    }
    
    // Helper: Traversal Preorder (Akar, Kiri, Kanan)
    void preorder(Lagu* node) {
        if (node == nullptr) return;
        
        tampilkanLagu(node);
        preorder(node->kiri);
        preorder(node->kanan);
    }
    
    // Helper: Traversal Postorder (Kiri, Kanan, Akar)
    void postorder(Lagu* node) {
        if (node == nullptr) return;
        
        postorder(node->kiri);
        postorder(node->kanan);
        tampilkanLagu(node);
    }
    
    // Helper: Hitung total lagu
    int hitungLagu(Lagu* node) {
        if (node == nullptr) return 0;
        return 1 + hitungLagu(node->kiri) + hitungLagu(node->kanan);
    }
    
    // Helper: Temukan lagu dengan durasi maksimal
    void cariDurasiMaks(Lagu* node, Lagu*& laguMaks) {
        if (node == nullptr) return;
        
        if (laguMaks == nullptr || node->durasi > laguMaks->durasi) {
            laguMaks = node;
        }
        
        cariDurasiMaks(node->kiri, laguMaks);
        cariDurasiMaks(node->kanan, laguMaks);
    }
    
    // Helper: Temukan lagu dengan durasi minimal
    void cariDurasiMin(Lagu* node, Lagu*& laguMin) {
        if (node == nullptr) return;
        
        if (laguMin == nullptr || node->durasi < laguMin->durasi) {
            laguMin = node;
        }
        
        cariDurasiMin(node->kiri, laguMin);
        cariDurasiMin(node->kanan, laguMin);
    }
    
    // Helper: Filter berdasarkan tag
    void filterTag(Lagu* node, string tag, int& jumlah) {
        if (node == nullptr) return;
        
        filterTag(node->kiri, tag, jumlah);
        
        // Cek apakah lagu ini memiliki tag tersebut
        bool punyaTag = false;
        for (int i = 0; i < node->jumlahTag; i++) {
            if (node->tag[i] == tag) {
                punyaTag = true;
                break;
            }
        }
        
        if (punyaTag) {
            jumlah++;
            tampilkanLagu(node);
        }
        
        filterTag(node->kanan, tag, jumlah);
    }
    
    // Helper: Filter berdasarkan jumlah tag
    void filterJumlahTag(Lagu* node, int targetJumlah, int& jumlah) {
        if (node == nullptr) return;
        
        filterJumlahTag(node->kiri, targetJumlah, jumlah);
        
        if (node->jumlahTag == targetJumlah) {
            jumlah++;
            tampilkanLagu(node);
        }
        
        filterJumlahTag(node->kanan, targetJumlah, jumlah);
    }
    
    // Helper: Tampilkan detail satu lagu
    void tampilkanLagu(Lagu* lagu) {
        cout << "\n-----------------------------------------\n";
        cout << "Judul    : " << lagu->judul << endl;
        cout << "Artis    : " << lagu->artis << endl;
        cout << "Durasi   : " << lagu->durasi << " detik (" 
             << lagu->durasi / 60 << "m " << lagu->durasi % 60 << "d)" << endl;
        cout << "Tag      : ";
        if (lagu->jumlahTag == 0) {
            cout << "(Tidak ada tag)";
        } else {
            for (int i = 0; i < lagu->jumlahTag; i++) {
                cout << lagu->tag[i];
                if (i < lagu->jumlahTag - 1) cout << ", ";
            }
        }
        cout << endl;
        cout << "-----------------------------------------\n";
    }
    
    // Helper: Dealokasi memori (penghapusan postorder)
    void hapusPohon(Lagu* node) {
        if (node == nullptr) return;
        hapusPohon(node->kiri);
        hapusPohon(node->kanan);
        delete node;
    }
    
public:
    // Konstruktor
    PlaylistMusik() {
        akar = nullptr;
    }
    
    // Destruktor
    ~PlaylistMusik() {
        hapusPohon(akar);
    }
    
    // Masukkan atau Update Lagu (overload untuk cek dulu tanpa durasi)
    bool masukkanAtauUpdate(string judul, string artis) {
        // Cek apakah lagu sudah ada
        Lagu* ada = cariJudul(akar, judul);
        
        if (ada != nullptr) {
            // Lagu sudah ada - tawarkan untuk menambah tag atau update durasi
            cout << "\nLagu '" << judul << "' sudah ada di playlist!\n";
            tampilkanLagu(ada);
            
            cout << "\nApa yang ingin Anda lakukan?\n";
            cout << "1. Tambah tag baru (maksimal 5 tag)\n";
            cout << "2. Update durasi\n";
            cout << "3. Batal\n";
            cout << "Pilihan: ";
            
            int pilihan;
            cin >> pilihan;
            
            if (pilihan == 1) {
                cin.ignore(numeric_limits<streamsize>::max(), '\n');
                if (ada->jumlahTag >= 5) {
                    cout << "Tidak bisa menambah tag lagi. Maksimal 5 tag sudah tercapai!\n";
                } else {
                    cout << "Masukkan tag baru: ";
                    string tagBaru;
                    getline(cin, tagBaru);
                    ada->tag[ada->jumlahTag] = tagBaru;
                    ada->jumlahTag++;
                    cout << "Tag berhasil ditambahkan!\n";
                }
            } else if (pilihan == 2) {
                cout << "Masukkan durasi baru (detik): ";
                int durasiBaru;
                cin >> durasiBaru;
                cin.ignore(numeric_limits<streamsize>::max(), '\n');
                ada->durasi = durasiBaru;
                cout << "Durasi berhasil diupdate!\n";
            } else {
                cin.ignore(numeric_limits<streamsize>::max(), '\n');
                cout << "Operasi dibatalkan.\n";
            }
            return true; // Lagu sudah ada
        }
        return false; // Lagu belum ada
    }
    
    // Masukkan lagu baru dengan durasi
    void masukkanLaguBaru(string judul, string artis, int durasi) {
        akar = masukkanHelper(akar, judul, artis, durasi);
    }
    
    // Cari berdasarkan judul
    void cari(string judul) {
        Lagu* hasil = cariJudul(akar, judul);
        
        if (hasil == nullptr) {
            cout << "\nLagu '" << judul << "' tidak ditemukan di playlist.\n";
        } else {
            cout << "\nLagu ditemukan!";
            tampilkanLagu(hasil);
        }
    }
    
    // Cari berdasarkan artis
    void cariMenurutArtis(string artis) {
        cout << "\n========================================\n";
        cout << "Lagu oleh '" << artis << "':\n";
        cout << "========================================\n";
        
        int jumlah = 0;
        cariArtis(akar, artis, jumlah);
        
        if (jumlah == 0) {
            cout << "Tidak ada lagu yang ditemukan dari artis ini.\n";
        } else {
            cout << "\nTotal lagu oleh " << artis << ": " << jumlah << endl;
        }
    }
    
    // Hapus lagu
    void hapusLagu(string judul) {
        bool terhapus = false;
        akar = hapusHelper(akar, judul, terhapus);
        
        if (terhapus) {
            cout << "\nLagu '" << judul << "' berhasil dihapus!\n";
        } else {
            cout << "\nLagu '" << judul << "' tidak ditemukan di playlist.\n";
        }
    }
    
    // Lihat playlist (traversal)
    void lihatPlaylist(int tipeTraversal) {
        if (akar == nullptr) {
            cout << "\nPlaylist kosong!\n";
            return;
        }
        
        cout << "\n========================================\n";
        
        if (tipeTraversal == 1) {
            cout << "TRAVERSAL INORDER (Terurut Alfabetis):\n";
            cout << "========================================\n";
            inorder(akar);
        } else if (tipeTraversal == 2) {
            cout << "TRAVERSAL PREORDER:\n";
            cout << "========================================\n";
            preorder(akar);
        } else if (tipeTraversal == 3) {
            cout << "TRAVERSAL POSTORDER:\n";
            cout << "========================================\n";
            postorder(akar);
        }
    }
    
    // Statistik
    void tampilkanStatistik() {
        if (akar == nullptr) {
            cout << "\nPlaylist kosong!\n";
            return;
        }
        
        int total = hitungLagu(akar);
        
        Lagu* laguMaks = nullptr;
        cariDurasiMaks(akar, laguMaks);
        
        Lagu* laguMin = nullptr;
        cariDurasiMin(akar, laguMin);
        
        cout << "\n========================================\n";
        cout << "STATISTIK PLAYLIST\n";
        cout << "========================================\n";
        cout << "Total Lagu: " << total << endl;
        
        cout << "\nLagu Terpanjang:";
        tampilkanLagu(laguMaks);
        
        cout << "\nLagu Terpendek:";
        tampilkanLagu(laguMin);
    }
    
    // Filter berdasarkan tag/genre
    void filterBerdasarkanTag(string tag) {
        if (akar == nullptr) {
            cout << "\nPlaylist kosong!\n";
            return;
        }
        
        cout << "\n========================================\n";
        cout << "Lagu dengan tag '" << tag << "':\n";
        cout << "========================================\n";
        
        int jumlah = 0;
        filterTag(akar, tag, jumlah);
        
        if (jumlah == 0) {
            cout << "Tidak ada lagu yang ditemukan dengan tag ini.\n";
        } else {
            cout << "\nTotal lagu dengan tag '" << tag << "': " << jumlah << endl;
        }
    }
    
    // Filter berdasarkan jumlah tag
    void filterBerdasarkanJumlahTag(int targetJumlah) {
        if (akar == nullptr) {
            cout << "\nPlaylist kosong!\n";
            return;
        }
        
        cout << "\n========================================\n";
        cout << "Lagu dengan tepat " << targetJumlah << " tag:\n";
        cout << "========================================\n";
        
        int jumlah = 0;
        filterJumlahTag(akar, targetJumlah, jumlah);
        
        if (jumlah == 0) {
            cout << "Tidak ada lagu yang ditemukan dengan " << targetJumlah << " tag.\n";
        } else {
            cout << "\nTotal lagu dengan " << targetJumlah << " tag: " << jumlah << endl;
        }
    }
};

// ============================================================
// SISTEM MENU UTAMA
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
