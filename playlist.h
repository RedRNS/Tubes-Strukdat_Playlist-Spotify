#ifndef PLAYLIST_H
#define PLAYLIST_H

#include <string>
using namespace std;

// Node BST untuk menyimpan data lagu
struct Lagu {
    string judul;        
    string artis;
    int durasi;          
    Lagu* kiri;
    Lagu* kanan;
    
    Lagu(string j, string a, int d);
};

// Node MLL untuk menyimpan genre (linked list)
struct Genre {
    string namaGenre;
    Lagu* rootLagu;  // root BST lagu
    Genre* next;     // pointer ke genre berikutnya

    Genre(string nama);
};

// Kelas utama playlist
class PlaylistMusik {
private:
    Genre* headGenre;
    
    // Helper BST
    Lagu* masukkanLaguHelper(Lagu* node, string judul, string artis, int durasi);
    Lagu* cariJudulHelper(Lagu* node, string judul);
    void cariArtisHelper(Lagu* node, string artis, string genre, int& jumlah);
    void cariDurasiHelper(Lagu* node, int durasi, string genre, int& jumlah);
    Lagu* cariMin(Lagu* node);
    Lagu* hapusLaguHelper(Lagu* node, string judul, bool& terhapus);
    
    // Traversal BST
    void inorder(Lagu* node);
    void preorder(Lagu* node);
    void postorder(Lagu* node);
    void levelorder(Lagu* node);
    
    // Helper statistik
    int hitungLagu(Lagu* node);
    void cariDurasiMaks(Lagu* node, Lagu*& laguMaks);
    void cariDurasiMin(Lagu* node, Lagu*& laguMin);
    
    // Dealokasi
    void hapusPohon(Lagu* node);
    void hapusSemuaGenre();

    // Helper MLL
    Genre* cariAtauBuatGenre(string namaGenre);
    Genre* cariGenre(string namaGenre);

    void tampilkanLagu(Lagu* lagu, string genreKonteks);

public:
    PlaylistMusik();
    ~PlaylistMusik();
    
    // CRUD
    void tambahLagu(string genre, string judul, string artis, int durasi);
    void updateLagu(string judul, string artisBaru, int durasiBaru);
    void hapusLagu(string judul);
    void hapusLaguDiGenre(string genre, string judul);
    
    // Pencarian
    void cariLagu(string judul);
    void cariLaguByArtis(string artis);
    void cariLaguByDurasi(int durasi);
    
    // Tampil data
    void lihatSemuaLagu();
    void lihatLaguPerGenre(string genre);
    void lihatDenganTraversal(string genre, int mode); // 1=pre, 2=in, 3=post, 4=level
    
    // Statistik
    void tampilkanStatistikGlobal();
    void tampilkanStatistikPerGenre();
    int hitungGenre();
};

#endif