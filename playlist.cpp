#include "playlist.h"
#include <iostream>
#include <limits>
using namespace std;

// ============================================================
// IMPLEMENTASI STRUCT
// ============================================================
Lagu::Lagu(string j, string a, int d) {
    judul = j;
    artis = a;
    durasi = d;
    kiri = nullptr;
    kanan = nullptr;
}

Genre::Genre(string nama) {
    namaGenre = nama;
    rootLagu = nullptr;
    next = nullptr;
}

// ============================================================
// IMPLEMENTASI KELAS PLAYLISTMUSIK
// ============================================================

PlaylistMusik::PlaylistMusik() {
    headGenre = nullptr;
}

PlaylistMusik::~PlaylistMusik() {
    hapusSemuaGenre();
}

// ---------------- Helper MLL (Genre) ----------------

Genre* PlaylistMusik::cariAtauBuatGenre(string nama) {
    // 1. Jika list kosong
    if (headGenre == nullptr) {
        headGenre = new Genre(nama);
        return headGenre;
    }

    // 2. Cari apakah genre sudah ada
    Genre* temp = headGenre;
    Genre* prev = nullptr;
    while (temp != nullptr) {
        if (temp->namaGenre == nama) {
            return temp; // Ketemu
        }
        prev = temp;
        temp = temp->next;
    }

    // 3. Jika tidak ada, buat baru di akhir list
    prev->next = new Genre(nama);
    return prev->next;
}

Genre* PlaylistMusik::cariGenre(string nama) {
    Genre* temp = headGenre;
    while (temp != nullptr) {
        if (temp->namaGenre == nama) return temp;
        temp = temp->next;
    }
    return nullptr;
}

void PlaylistMusik::hapusSemuaGenre() {
    Genre* temp = headGenre;
    while (temp != nullptr) {
        hapusPohon(temp->rootLagu); // Hapus BST-nya dulu
        Genre* hapus = temp;
        temp = temp->next;
        delete hapus; // Hapus node Genre
    }
}

// ---------------- Helper BST (Lagu) ----------------

Lagu* PlaylistMusik::masukkanLaguHelper(Lagu* node, string judul, string artis, int durasi) {
    if (node == nullptr) {
        return new Lagu(judul, artis, durasi);
    }
    
    if (judul == node->judul) {
        cout << "Lagu '" << judul << "' sudah ada (Update Info).\n";
        node->artis = artis;
        node->durasi = durasi;
        return node;
    }
    
    if (judul < node->judul) {
        node->kiri = masukkanLaguHelper(node->kiri, judul, artis, durasi);
    } else {
        node->kanan = masukkanLaguHelper(node->kanan, judul, artis, durasi);
    }
    return node;
}

Lagu* PlaylistMusik::cariJudulHelper(Lagu* node, string judul) {
    if (node == nullptr || node->judul == judul) return node;
    
    if (judul < node->judul) return cariJudulHelper(node->kiri, judul);
    else return cariJudulHelper(node->kanan, judul);
}

void PlaylistMusik::cariArtisHelper(Lagu* node, string artis, string genre, int& jumlah) {
    if (node == nullptr) return;
    
    cariArtisHelper(node->kiri, artis, genre, jumlah);
    if (node->artis == artis) {
        tampilkanLagu(node, genre);
        jumlah++;
    }
    cariArtisHelper(node->kanan, artis, genre, jumlah);
}

Lagu* PlaylistMusik::hapusLaguHelper(Lagu* node, string judul, bool& terhapus) {
    if (node == nullptr) return nullptr;
    
    if (judul < node->judul) {
        node->kiri = hapusLaguHelper(node->kiri, judul, terhapus);
    } else if (judul > node->judul) {
        node->kanan = hapusLaguHelper(node->kanan, judul, terhapus);
    } else {
        terhapus = true;
        if (node->kiri == nullptr && node->kanan == nullptr) {
            delete node; return nullptr;
        } else if (node->kiri == nullptr) {
            Lagu* temp = node->kanan; delete node; return temp;
        } else if (node->kanan == nullptr) {
            Lagu* temp = node->kiri; delete node; return temp;
        } else {
            Lagu* pengganti = cariMin(node->kanan);
            node->judul = pengganti->judul;
            node->artis = pengganti->artis;
            node->durasi = pengganti->durasi;
            node->kanan = hapusLaguHelper(node->kanan, pengganti->judul, terhapus);
        }
    }
    return node;
}

Lagu* PlaylistMusik::cariMin(Lagu* node) {
    while (node->kiri != nullptr) node = node->kiri;
    return node;
}

void PlaylistMusik::inorder(Lagu* node) {
    if (node == nullptr) return;
    inorder(node->kiri);
    tampilkanLagu(node, "");
    inorder(node->kanan);
}

void PlaylistMusik::hapusPohon(Lagu* node) {
    if (node == nullptr) return;
    hapusPohon(node->kiri);
    hapusPohon(node->kanan);
    delete node;
}

// Statistik Helpers
int PlaylistMusik::hitungLagu(Lagu* node) {
    if (node == nullptr) return 0;
    return 1 + hitungLagu(node->kiri) + hitungLagu(node->kanan);
}

void PlaylistMusik::cariDurasiMaks(Lagu* node, Lagu*& laguMaks) {
    if (node == nullptr) return;
    if (laguMaks == nullptr || node->durasi > laguMaks->durasi) laguMaks = node;
    cariDurasiMaks(node->kiri, laguMaks);
    cariDurasiMaks(node->kanan, laguMaks);
}

void PlaylistMusik::cariDurasiMin(Lagu* node, Lagu*& laguMin) {
    if (node == nullptr) return;
    if (laguMin == nullptr || node->durasi < laguMin->durasi) laguMin = node;
    cariDurasiMin(node->kiri, laguMin);
    cariDurasiMin(node->kanan, laguMin);
}

void PlaylistMusik::tampilkanLagu(Lagu* lagu, string genreKonteks) {
    cout << "- " << lagu->judul << " (" << lagu->artis << ") [" 
         << lagu->durasi / 60 << "m" << lagu->durasi % 60 << "s]";
    if (!genreKonteks.empty()) cout << " [Genre: " << genreKonteks << "]";
    cout << endl;
}

// ---------------- PUBLIC METHODS ----------------

void PlaylistMusik::tambahLagu(string genre, string judul, string artis, int durasi) {
    // 1. Cari atau Buat Node Genre (MLL)
    Genre* g = cariAtauBuatGenre(genre);
    
    // 2. Masukkan Lagu ke BST milik genre tersebut
    g->rootLagu = masukkanLaguHelper(g->rootLagu, judul, artis, durasi);
}

void PlaylistMusik::cariLagu(string judul) {
    cout << "\n--- Mencari '" << judul << "' di semua genre ---\n";
    Genre* curr = headGenre;
    bool found = false;
    
    while (curr != nullptr) {
        Lagu* hasil = cariJudulHelper(curr->rootLagu, judul);
        if (hasil != nullptr) {
            cout << "Ditemukan di Genre: " << curr->namaGenre << endl;
            tampilkanLagu(hasil, curr->namaGenre);
            found = true;
        }
        curr = curr->next;
    }
    
    if (!found) cout << "Lagu tidak ditemukan di genre manapun.\n";
}

void PlaylistMusik::cariLaguByArtis(string artis) {
    cout << "\n--- Mencari Artis '" << artis << "' ---\n";
    Genre* curr = headGenre;
    int total = 0;
    
    while (curr != nullptr) {
        cariArtisHelper(curr->rootLagu, artis, curr->namaGenre, total);
        curr = curr->next;
    }
    
    if (total == 0) cout << "Tidak ada lagu dari artis tersebut.\n";
}

void PlaylistMusik::hapusLagu(string judul) {
    Genre* curr = headGenre;
    bool terhapusGlobal = false;
    
    while (curr != nullptr) {
        bool terhapusLokal = false;
        curr->rootLagu = hapusLaguHelper(curr->rootLagu, judul, terhapusLokal);
        if (terhapusLokal) {
            cout << "Dihapus dari Genre: " << curr->namaGenre << endl;
            terhapusGlobal = true;
        }
        curr = curr->next;
    }
    
    if (!terhapusGlobal) cout << "Lagu tidak ditemukan untuk dihapus.\n";
}

void PlaylistMusik::lihatSemuaLagu() {
    if (headGenre == nullptr) {
        cout << "Playlist Kosong.\n";
        return;
    }
    
    Genre* curr = headGenre;
    while (curr != nullptr) {
        cout << "\n[ GENRE: " << curr->namaGenre << " ]\n";
        if (curr->rootLagu == nullptr) {
            cout << "(Kosong)\n";
        } else {
            inorder(curr->rootLagu);
        }
        curr = curr->next;
    }
}

void PlaylistMusik::lihatLaguPerGenre(string genre) {
    Genre* g = cariGenre(genre);
    if (g == nullptr) {
        cout << "Genre '" << genre << "' tidak ditemukan.\n";
        return;
    }
    
    cout << "\n[ GENRE: " << g->namaGenre << " ]\n";
    inorder(g->rootLagu);
}

void PlaylistMusik::tampilkanStatistikGlobal() {
    Genre* curr = headGenre;
    int totalLagu = 0;
    Lagu* globalMax = nullptr;
    Lagu* globalMin = nullptr;
    
    while (curr != nullptr) {
        totalLagu += hitungLagu(curr->rootLagu);
        
        Lagu* localMax = nullptr;
        cariDurasiMaks(curr->rootLagu, localMax);
        if (localMax) {
            if (!globalMax || localMax->durasi > globalMax->durasi) globalMax = localMax;
        }
        
        Lagu* localMin = nullptr;
        cariDurasiMin(curr->rootLagu, localMin);
        if (localMin) {
            if (!globalMin || localMin->durasi < globalMin->durasi) globalMin = localMin;
        }
        
        curr = curr->next;
    }
    
    cout << "\n=== STATISTIK GLOBAL ===\n";
    cout << "Total Lagu (Semua Genre): " << totalLagu << endl;
    if (globalMax) {
        cout << "Lagu Terpanjang: " << globalMax->judul << " (" << globalMax->durasi << "s)\n";
    }
    if (globalMin) {
        cout << "Lagu Terpendek : " << globalMin->judul << " (" << globalMin->durasi << "s)\n";
    }
}