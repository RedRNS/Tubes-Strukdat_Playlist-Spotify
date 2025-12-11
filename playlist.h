#ifndef PLAYLIST_H
#define PLAYLIST_H

#include <string>
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
    Lagu(string j, string a, int d);
};

// ============================================================
// KELAS BST - Playlist Musik (ADT SPECIFICATION)
// ============================================================
class PlaylistMusik {
private:
    Lagu* akar;
    
    // Helper: Masukkan lagu ke BST (berdasarkan perbandingan judul)
    Lagu* masukkanHelper(Lagu* node, string judul, string artis, int durasi);
    
    // Helper: Cari berdasarkan judul
    Lagu* cariJudul(Lagu* node, string judul);
    
    // Helper: Cari berdasarkan artis (menemukan semua yang cocok)
    void cariArtis(Lagu* node, string artis, int& jumlah);
    
    // Helper: Temukan node dengan nilai minimum (paling kiri)
    Lagu* cariMin(Lagu* node);
    
    // Helper: Hapus lagu dari BST
    Lagu* hapusHelper(Lagu* node, string judul, bool& terhapus);
    
    // Helper: Traversal Inorder (Kiri, Akar, Kanan) - Urutan terurut
    void inorder(Lagu* node);
    
    // Helper: Traversal Preorder (Akar, Kiri, Kanan)
    void preorder(Lagu* node);
    
    // Helper: Traversal Postorder (Kiri, Kanan, Akar)
    void postorder(Lagu* node);
    
    // Helper: Hitung total lagu
    int hitungLagu(Lagu* node);
    
    // Helper: Temukan lagu dengan durasi maksimal
    void cariDurasiMaks(Lagu* node, Lagu*& laguMaks);
    
    // Helper: Temukan lagu dengan durasi minimal
    void cariDurasiMin(Lagu* node, Lagu*& laguMin);
    
    // Helper: Filter berdasarkan tag
    void filterTag(Lagu* node, string tag, int& jumlah);
    
    // Helper: Filter berdasarkan jumlah tag
    void filterJumlahTag(Lagu* node, int targetJumlah, int& jumlah);
    
    // Helper: Tampilkan detail satu lagu
    void tampilkanLagu(Lagu* lagu);
    
    // Helper: Dealokasi memori (penghapusan postorder)
    void hapusPohon(Lagu* node);
    
public:
    // Konstruktor
    PlaylistMusik();
    
    // Destruktor
    ~PlaylistMusik();
    
    // Masukkan atau Update Lagu (overload untuk cek dulu tanpa durasi)
    bool masukkanAtauUpdate(string judul, string artis);
    
    // Masukkan lagu baru dengan durasi
    void masukkanLaguBaru(string judul, string artis, int durasi);
    
    // Cari berdasarkan judul
    void cari(string judul);
    
    // Cari berdasarkan artis
    void cariMenurutArtis(string artis);
    
    // Hapus lagu
    void hapusLagu(string judul);
    
    // Lihat playlist (traversal)
    void lihatPlaylist(int tipeTraversal);
    
    // Statistik
    void tampilkanStatistik();
    
    // Filter berdasarkan tag/genre
    void filterBerdasarkanTag(string tag);
    
    // Filter berdasarkan jumlah tag
    void filterBerdasarkanJumlahTag(int targetJumlah);
};

#endif
