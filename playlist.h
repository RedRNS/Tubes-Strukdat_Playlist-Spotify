#ifndef PLAYLIST_H
#define PLAYLIST_H

#include <string>
using namespace std;

// ============================================================
// STRUKTUR NODE CHILD - Lagu dalam BST (Kunci: judul)
// ============================================================
struct Lagu {
    string judul;        
    string artis;
    int durasi;          
    Lagu* kiri;
    Lagu* kanan;
    
    // Konstruktor
    Lagu(string j, string a, int d);
};

// ============================================================
// STRUKTUR NODE PARENT - Genre dalam Linked List (MLL)
// ============================================================
struct Genre {
    string namaGenre;
    Lagu* rootLagu;      // Pointer ke akar BST lagu untuk genre ini
    Genre* next;         // Pointer ke genre selanjutnya (Linked List)

    Genre(string nama);
};

// ============================================================
// KELAS APLIKASI MUSIK - Gabungan MLL & BST
// ============================================================
class PlaylistMusik {
private:
    Genre* headGenre; // Kepala dari Linked List Genre
    
    // --- HELPER BST (Bekerja pada node Lagu) ---
    Lagu* masukkanLaguHelper(Lagu* node, string judul, string artis, int durasi);
    Lagu* cariJudulHelper(Lagu* node, string judul);
    void cariArtisHelper(Lagu* node, string artis, string genre, int& jumlah);
    Lagu* cariMin(Lagu* node);
    Lagu* hapusLaguHelper(Lagu* node, string judul, bool& terhapus);
    
    // Traversal Helpers
    void inorder(Lagu* node);
    void preorder(Lagu* node);
    void postorder(Lagu* node);
    
    // Helper Statistik
    int hitungLagu(Lagu* node);
    void cariDurasiMaks(Lagu* node, Lagu*& laguMaks);
    void cariDurasiMin(Lagu* node, Lagu*& laguMin);
    
    // Helper Dealokasi
    void hapusPohon(Lagu* node);
    void hapusSemuaGenre();

    // --- HELPER MLL (Bekerja pada node Genre) ---
    Genre* cariAtauBuatGenre(string namaGenre);
    Genre* cariGenre(string namaGenre);

    // Helper Tampilan
    void tampilkanLagu(Lagu* lagu, string genreKonteks);

public:
    PlaylistMusik();
    ~PlaylistMusik();
    
    // MLL + BST Operations
    void tambahLagu(string genre, string judul, string artis, int durasi);
    
    // Operasi Pencarian (Global di semua genre)
    void cariLagu(string judul);
    void cariLaguByArtis(string artis);
    
    // Operasi Hapus
    void hapusLagu(string judul); // Mencari di semua genre lalu menghapus
    void hapusLaguDiGenre(string genre, string judul); // Hapus spesifik
    
    // Tampilkan Playlist (Traverse MLL lalu Traverse BST)
    void lihatSemuaLagu();
    void lihatLaguPerGenre(string genre);
    
    // Statistik
    void tampilkanStatistikGlobal();
};

#endif