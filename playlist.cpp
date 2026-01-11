#include "playlist.h"
#include <iostream>
#include <queue>
using namespace std;

// Konstruktor Lagu
Lagu::Lagu(string j, string a, int d) {
    judul = j;
    artis = a;
    durasi = d;
    kiri = nullptr;
    kanan = nullptr;
}

// Konstruktor Genre
Genre::Genre(string nama) {
    namaGenre = nama;
    rootLagu = nullptr;
    next = nullptr;
}

// Konstruktor & Destruktor PlaylistMusik
PlaylistMusik::PlaylistMusik() {
    headGenre = nullptr;
}

PlaylistMusik::~PlaylistMusik() {
    hapusSemuaGenre();
}

// ========== HELPER MLL ==========

Genre* PlaylistMusik::cariAtauBuatGenre(string nama) {
    if (headGenre == nullptr) {
        headGenre = new Genre(nama);
        return headGenre;
    }

    Genre* temp = headGenre;
    Genre* prev = nullptr;
    while (temp != nullptr) {
        if (temp->namaGenre == nama) return temp;
        prev = temp;
        temp = temp->next;
    }

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
        hapusPohon(temp->rootLagu);
        Genre* hapus = temp;
        temp = temp->next;
        delete hapus;
    }
}

int PlaylistMusik::hitungGenre() {
    int count = 0;
    Genre* temp = headGenre;
    while (temp != nullptr) {
        count++;
        temp = temp->next;
    }
    return count;
}

// ========== HELPER BST ==========

Lagu* PlaylistMusik::masukkanLaguHelper(Lagu* node, string judul, string artis, int durasi) {
    if (node == nullptr) {
        return new Lagu(judul, artis, durasi);
    }
    
    if (judul == node->judul) {
        cout << "Lagu '" << judul << "' sudah ada, data diupdate.\n";
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
    return cariJudulHelper(node->kanan, judul);
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

void PlaylistMusik::cariDurasiHelper(Lagu* node, int durasi, string genre, int& jumlah) {
    if (node == nullptr) return;
    
    cariDurasiHelper(node->kiri, durasi, genre, jumlah);
    if (node->durasi == durasi) {
        tampilkanLagu(node, genre);
        jumlah++;
    }
    cariDurasiHelper(node->kanan, durasi, genre, jumlah);
}

Lagu* PlaylistMusik::hapusLaguHelper(Lagu* node, string judul, bool& terhapus) {
    if (node == nullptr) return nullptr;
    
    if (judul < node->judul) {
        node->kiri = hapusLaguHelper(node->kiri, judul, terhapus);
    } else if (judul > node->judul) {
        node->kanan = hapusLaguHelper(node->kanan, judul, terhapus);
    } else {
        terhapus = true;
        // node tanpa anak atau 1 anak
        if (node->kiri == nullptr) {
            Lagu* temp = node->kanan;
            delete node;
            return temp;
        } else if (node->kanan == nullptr) {
            Lagu* temp = node->kiri;
            delete node;
            return temp;
        }
        // node dengan 2 anak
        Lagu* pengganti = cariMin(node->kanan);
        node->judul = pengganti->judul;
        node->artis = pengganti->artis;
        node->durasi = pengganti->durasi;
        node->kanan = hapusLaguHelper(node->kanan, pengganti->judul, terhapus);
    }
    return node;
}

Lagu* PlaylistMusik::cariMin(Lagu* node) {
    while (node->kiri != nullptr) node = node->kiri;
    return node;
}

// ========== TRAVERSAL BST ==========

void PlaylistMusik::inorder(Lagu* node) {
    if (node == nullptr) return;
    inorder(node->kiri);
    tampilkanLagu(node, "");
    inorder(node->kanan);
}

void PlaylistMusik::preorder(Lagu* node) {
    if (node == nullptr) return;
    tampilkanLagu(node, "");
    preorder(node->kiri);
    preorder(node->kanan);
}

void PlaylistMusik::postorder(Lagu* node) {
    if (node == nullptr) return;
    postorder(node->kiri);
    postorder(node->kanan);
    tampilkanLagu(node, "");
}

void PlaylistMusik::levelorder(Lagu* node) {
    if (node == nullptr) return;
    
    queue<Lagu*> q;
    q.push(node);
    
    while (!q.empty()) {
        Lagu* curr = q.front();
        q.pop();
        tampilkanLagu(curr, "");
        
        if (curr->kiri) q.push(curr->kiri);
        if (curr->kanan) q.push(curr->kanan);
    }
}

void PlaylistMusik::hapusPohon(Lagu* node) {
    if (node == nullptr) return;
    hapusPohon(node->kiri);
    hapusPohon(node->kanan);
    delete node;
}

// ========== HELPER STATISTIK ==========

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
    int menit = lagu->durasi / 60;
    int detik = lagu->durasi % 60;
    cout << "  - " << lagu->judul << " | " << lagu->artis << " | " << menit << "m" << detik << "s";
    if (!genreKonteks.empty()) cout << " [" << genreKonteks << "]";
    cout << endl;
}

// ========== FUNGSI PUBLIK ==========

void PlaylistMusik::tambahLagu(string genre, string judul, string artis, int durasi) {
    Genre* g = cariAtauBuatGenre(genre);
    g->rootLagu = masukkanLaguHelper(g->rootLagu, judul, artis, durasi);
    cout << "Lagu '" << judul << "' ditambahkan ke genre " << genre << ".\n";
}

void PlaylistMusik::updateLagu(string judul, string artisBaru, int durasiBaru) {
    Genre* curr = headGenre;
    while (curr != nullptr) {
        Lagu* hasil = cariJudulHelper(curr->rootLagu, judul);
        if (hasil != nullptr) {
            hasil->artis = artisBaru;
            hasil->durasi = durasiBaru;
            cout << "Lagu '" << judul << "' berhasil diupdate.\n";
            return;
        }
        curr = curr->next;
    }
    cout << "Lagu '" << judul << "' tidak ditemukan.\n";
}

void PlaylistMusik::cariLagu(string judul) {
    cout << "\n>> Mencari '" << judul << "'...\n";
    Genre* curr = headGenre;
    bool found = false;
    
    while (curr != nullptr) {
        Lagu* hasil = cariJudulHelper(curr->rootLagu, judul);
        if (hasil != nullptr) {
            cout << "Ditemukan di genre: " << curr->namaGenre << endl;
            tampilkanLagu(hasil, "");
            found = true;
        }
        curr = curr->next;
    }
    
    if (!found) cout << "Lagu tidak ditemukan.\n";
}

void PlaylistMusik::cariLaguByArtis(string artis) {
    cout << "\n>> Mencari artis '" << artis << "'...\n";
    Genre* curr = headGenre;
    int total = 0;
    
    while (curr != nullptr) {
        cariArtisHelper(curr->rootLagu, artis, curr->namaGenre, total);
        curr = curr->next;
    }
    
    if (total == 0) cout << "Tidak ada lagu dari artis tersebut.\n";
    else cout << "Total: " << total << " lagu ditemukan.\n";
}

void PlaylistMusik::cariLaguByDurasi(int durasi) {
    cout << "\n>> Mencari durasi " << durasi << " detik...\n";
    Genre* curr = headGenre;
    int total = 0;
    
    while (curr != nullptr) {
        cariDurasiHelper(curr->rootLagu, durasi, curr->namaGenre, total);
        curr = curr->next;
    }
    
    if (total == 0) cout << "Tidak ada lagu dengan durasi tersebut.\n";
    else cout << "Total: " << total << " lagu ditemukan.\n";
}

void PlaylistMusik::hapusLagu(string judul) {
    Genre* curr = headGenre;
    bool terhapusGlobal = false;
    
    while (curr != nullptr) {
        bool terhapusLokal = false;
        curr->rootLagu = hapusLaguHelper(curr->rootLagu, judul, terhapusLokal);
        if (terhapusLokal) {
            cout << "Lagu '" << judul << "' dihapus dari genre " << curr->namaGenre << ".\n";
            terhapusGlobal = true;
        }
        curr = curr->next;
    }
    
    if (!terhapusGlobal) cout << "Lagu tidak ditemukan.\n";
}

void PlaylistMusik::hapusLaguDiGenre(string genre, string judul) {
    Genre* g = cariGenre(genre);
    if (g == nullptr) {
        cout << "Genre '" << genre << "' tidak ada.\n";
        return;
    }
    
    bool terhapus = false;
    g->rootLagu = hapusLaguHelper(g->rootLagu, judul, terhapus);
    
    if (terhapus) cout << "Lagu '" << judul << "' dihapus dari genre " << genre << ".\n";
    else cout << "Lagu tidak ditemukan di genre tersebut.\n";
}

void PlaylistMusik::lihatSemuaLagu() {
    if (headGenre == nullptr) {
        cout << "Playlist kosong.\n";
        return;
    }
    
    cout << "\n========== SEMUA PLAYLIST ==========\n";
    Genre* curr = headGenre;
    while (curr != nullptr) {
        cout << "\n[" << curr->namaGenre << "] - " << hitungLagu(curr->rootLagu) << " lagu\n";
        if (curr->rootLagu == nullptr) {
            cout << "  (kosong)\n";
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
    
    cout << "\n[" << g->namaGenre << "] - " << hitungLagu(g->rootLagu) << " lagu\n";
    if (g->rootLagu == nullptr) {
        cout << "  (kosong)\n";
    } else {
        inorder(g->rootLagu);
    }
}

void PlaylistMusik::lihatDenganTraversal(string genre, int mode) {
    Genre* g = cariGenre(genre);
    if (g == nullptr) {
        cout << "Genre '" << genre << "' tidak ditemukan.\n";
        return;
    }
    
    if (g->rootLagu == nullptr) {
        cout << "Genre " << genre << " kosong.\n";
        return;
    }
    
    cout << "\n[" << g->namaGenre << "] ";
    switch (mode) {
        case 1:
            cout << "- Preorder:\n";
            preorder(g->rootLagu);
            break;
        case 2:
            cout << "- Inorder:\n";
            inorder(g->rootLagu);
            break;
        case 3:
            cout << "- Postorder:\n";
            postorder(g->rootLagu);
            break;
        case 4:
            cout << "- Level Order:\n";
            levelorder(g->rootLagu);
            break;
        default:
            cout << "Mode tidak valid.\n";
    }
}

void PlaylistMusik::tampilkanStatistikGlobal() {
    if (headGenre == nullptr) {
        cout << "Playlist kosong.\n";
        return;
    }
    
    Genre* curr = headGenre;
    int totalLagu = 0;
    int totalGenre = 0;
    Lagu* globalMax = nullptr;
    Lagu* globalMin = nullptr;
    
    while (curr != nullptr) {
        totalGenre++;
        totalLagu += hitungLagu(curr->rootLagu);
        
        Lagu* localMax = nullptr;
        Lagu* localMin = nullptr;
        cariDurasiMaks(curr->rootLagu, localMax);
        cariDurasiMin(curr->rootLagu, localMin);
        
        if (localMax && (!globalMax || localMax->durasi > globalMax->durasi)) 
            globalMax = localMax;
        if (localMin && (!globalMin || localMin->durasi < globalMin->durasi)) 
            globalMin = localMin;
        
        curr = curr->next;
    }
    
    cout << "\n========== STATISTIK GLOBAL ==========\n";
    cout << "Total Genre   : " << totalGenre << endl;
    cout << "Total Lagu    : " << totalLagu << endl;
    if (globalMax) {
        cout << "Lagu Terpanjang: " << globalMax->judul << " (" << globalMax->durasi << " detik)\n";
    }
    if (globalMin) {
        cout << "Lagu Terpendek : " << globalMin->judul << " (" << globalMin->durasi << " detik)\n";
    }
}

void PlaylistMusik::tampilkanStatistikPerGenre() {
    if (headGenre == nullptr) {
        cout << "Playlist kosong.\n";
        return;
    }
    
    cout << "\n========== STATISTIK PER GENRE ==========\n";
    Genre* curr = headGenre;
    
    while (curr != nullptr) {
        int jumlah = hitungLagu(curr->rootLagu);
        Lagu* lMax = nullptr;
        Lagu* lMin = nullptr;
        cariDurasiMaks(curr->rootLagu, lMax);
        cariDurasiMin(curr->rootLagu, lMin);
        
        cout << "\n[" << curr->namaGenre << "]\n";
        cout << "  Jumlah Lagu: " << jumlah << endl;
        if (lMax) cout << "  Terpanjang : " << lMax->judul << " (" << lMax->durasi << "s)\n";
        if (lMin) cout << "  Terpendek  : " << lMin->judul << " (" << lMin->durasi << "s)\n";
        
        curr = curr->next;
    }
}