#include 
#include <string.h>
#include <stdlib.h>

// Array untuk menyimpan data kontak
char namaKontak[100][50];
char nomorTelepon[100][15];
char emailKontak[100][50];
char kelompokKontak[100][30];
int jumlahKontak = 0;

// Fungsi untuk menambah kontak
void tambahKontak(){
    if(jumlahKontak >= 100){
        printf("Database kontak penuh!\n");
        return;
    }
    
    printf("\n=== TAMBAH KONTAK BARU ===\n");
    printf("Nama: ");
    scanf(" %[^\n]", namaKontak[jumlahKontak]);
    
    printf("Nomor Telepon: ");
    scanf(" %[^\n]", nomorTelepon[jumlahKontak]);
    
    printf("Email: ");
    scanf(" %[^\n]", emailKontak[jumlahKontak]);
    
    printf("Kelompok (Keluarga/Teman/Kerja/Lainnya): ");
    scanf(" %[^\n]", kelompokKontak[jumlahKontak]);
    
    jumlahKontak++;
    printf("\nKontak berhasil ditambahkan!\n");
}

// Fungsi untuk menampilkan semua kontak
void tampilkanSemuaKontak(){
    printf("\n=== DAFTAR SEMUA KONTAK ===\n");
    
    if(jumlahKontak == 0){
        printf("Tidak ada kontak yang tersimpan.\n");
        return;
    }
    
    for(int i = 0; i < jumlahKontak; i++){
        printf("\n--- Kontak #%d ---\n", i+1);
        printf("Nama: %s\n", namaKontak[i]);
        printf("Telepon: %s\n", nomorTelepon[i]);
        printf("Email: %s\n", emailKontak[i]);
        printf("Kelompok: %s\n", kelompokKontak[i]);
    }
    
    printf("\nTotal: %d kontak\n", jumlahKontak);
}

// Fungsi untuk mencari kontak
void cariKontak(){
    printf("\n=== CARI KONTAK ===\n");
    
    if(jumlahKontak == 0){
        printf("Tidak ada kontak yang bisa dicari.\n");
        return;
    }
    
    char keyword[50];
    printf("Masukkan nama yang dicari: ");
    scanf(" %[^\n]", keyword);
    
    int ditemukan = 0;
    for(int i = 0; i < jumlahKontak; i++){
        if(strstr(namaKontak[i], keyword) != NULL){
            printf("\nKontak ditemukan:\n");
            printf("ID: %d\n", i+1);
            printf("Nama: %s\n", namaKontak[i]);
            printf("Telepon: %s\n", nomorTelepon[i]);
            printf("Email: %s\n", emailKontak[i]);
            printf("Kelompok: %s\n", kelompokKontak[i]);
            ditemukan = 1;
        }
    }
    
    if(ditemukan == 0){
        printf("Tidak ada kontak yang cocok.\n");
    }
}

// Fungsi untuk mengedit kontak
void editKontak(){
    printf("\n=== EDIT KONTAK ===\n");
    
    if(jumlahKontak == 0){
        printf("Tidak ada kontak yang bisa diedit.\n");
        return;
    }
    
    int id;
    printf("Masukkan ID kontak yang akan diedit (1-%d): ", jumlahKontak);
    scanf("%d", &id);
    
    if(id < 1 || id > jumlahKontak){
        printf("ID tidak valid!\n");
        return;
    }
    
    int index = id - 1;
    printf("\nMengedit kontak: %s\n", namaKontak[index]);
    
    printf("Nama Baru: ");
    scanf(" %[^\n]", namaKontak[index]);
    
    printf("Nomor Telepon Baru: ");
    scanf(" %[^\n]", nomorTelepon[index]);
    
    printf("Email Baru: ");
    scanf(" %[^\n]", emailKontak[index]);
    
    printf("Kelompok Baru: ");
    scanf(" %[^\n]", kelompokKontak[index]);
    
    printf("\nKontak berhasil diupdate!\n");
}

// Fungsi untuk menghapus kontak
void hapusKontak(){
    printf("\n=== HAPUS KONTAK ===\n");
    
    if(jumlahKontak == 0){
        printf("Tidak ada kontak yang bisa dihapus.\n");
        return;
    }
    
    int id;
    printf("Masukkan ID kontak yang akan dihapus (1-%d): ", jumlahKontak);
    scanf("%d", &id);
    
    if(id < 1 || id > jumlahKontak){
        printf("ID tidak valid!\n");
        return;
    }
    
    int index = id - 1;
    printf("Apakah Anda yakin ingin menghapus kontak: %s? (y/n): ", namaKontak[index]);
    
    char konfirmasi;
    scanf(" %c", &konfirmasi);
    
    if(konfirmasi == 'y' || konfirmasi == 'Y'){
        // Geser semua data ke kiri
        for(int i = index; i < jumlahKontak - 1; i++){
            strcpy(namaKontak[i], namaKontak[i + 1]);
            strcpy(nomorTelepon[i], nomorTelepon[i + 1]);
            strcpy(emailKontak[i], emailKontak[i + 1]);
            strcpy(kelompokKontak[i], kelompokKontak[i + 1]);
        }
        jumlahKontak--;
        printf("Kontak berhasil dihapus!\n");
    } else {
        printf("Penghapusan dibatalkan.\n");
    }
}

// Fungsi untuk menyimpan ke file
void simpanKeFile(){
    FILE *file;
    file = fopen("data_kontak.txt", "w");
    
    if(file == NULL){
        printf("Gagal membuka file!\n");
        return;
    }
    
    fprintf(file, "%d\n", jumlahKontak);
    
    for(int i = 0; i < jumlahKontak; i++){
        fprintf(file, "%s\n", namaKontak[i]);
        fprintf(file, "%s\n", nomorTelepon[i]);
        fprintf(file, "%s\n", emailKontak[i]);
        fprintf(file, "%s\n", kelompokKontak[i]);
    }
    
    fclose(file);
    printf("Data berhasil disimpan ke file!\n");
}

// Fungsi untuk membaca dari file
void bacaDariFile(){
    FILE *file;
    file = fopen("data_kontak.txt", "r");
    
    if(file == NULL){
        printf("File data tidak ditemukan. Membuat database baru.\n");
        return;
    }
    
    fscanf(file, "%d\n", &jumlahKontak);
    
    for(int i = 0; i < jumlahKontak; i++){
        fgets(namaKontak[i], 50, file);
        namaKontak[i][strcspn(namaKontak[i], "\n")] = 0;
        
        fgets(nomorTelepon[i], 15, file);
        nomorTelepon[i][strcspn(nomorTelepon[i], "\n")] = 0;
        
        fgets(emailKontak[i], 50, file);
        emailKontak[i][strcspn(emailKontak[i], "\n")] = 0;
        
        fgets(kelompokKontak[i], 30, file);
        kelompokKontak[i][strcspn(kelompokKontak[i], "\n")] = 0;
    }
    
    fclose(file);
    printf("Data berhasil dimuat dari file! (%d kontak)\n", jumlahKontak);
}

// Fungsi untuk menampilkan statistik
void tampilkanStatistik(){
    printf("\n=== STATISTIK KONTAK ===\n");
    printf("Total Kontak: %d\n", jumlahKontak);
    
    if(jumlahKontak == 0){
        printf("Tidak ada data untuk dianalisis.\n");
        return;
    }
    
    int keluarga = 0, teman = 0, kerja = 0, lainnya = 0;
    
    for(int i = 0; i < jumlahKontak; i++){
        if(strstr(kelompokKontak[i], "Keluarga") != NULL){
            keluarga++;
        } else if(strstr(kelompokKontak[i], "Teman") != NULL){
            teman++;
        } else if(strstr(kelompokKontak[i], "Kerja") != NULL){
            kerja++;
        } else {
            lainnya++;
        }
    }
    
    printf("Keluarga: %d\n", keluarga);
    printf("Teman: %d\n", teman);
    printf("Kerja: %d\n", kerja);
    printf("Lainnya: %d\n", lainnya);
}

// Fungsi untuk export ke file teks
void exportKeFileTeks(){
    if(jumlahKontak == 0){
        printf("Tidak ada data untuk di-export.\n");
        return;
    }
    
    FILE *file;
    file = fopen("export_kontak.txt", "w");
    
    if(file == NULL){
        printf("Gagal membuat file!\n");
        return;
    }
    
    fprintf(file, "DAFTAR KONTAK\n");
    fprintf(file, "=============\n");
    fprintf(file, "Total: %d kontak\n\n", jumlahKontak);
    
    for(int i = 0; i < jumlahKontak; i++){
        fprintf(file, "Kontak #%d\n", i+1);
        fprintf(file, "Nama: %s\n", namaKontak[i]);
        fprintf(file, "Telepon: %s\n", nomorTelepon[i]);
        fprintf(file, "Email: %s\n", emailKontak[i]);
        fprintf(file, "Kelompok: %s\n", kelompokKontak[i]);
        fprintf(file, "------------------------\n");
    }
    
    fclose(file);
    printf("Data berhasil di-export ke 'export_kontak.txt'\n");
}

// Fungsi untuk deteksi duplikat
void deteksiDuplikat(){
    printf("\n=== DETEKSI DUPLIKAT ===\n");
    
    if(jumlahKontak == 0){
        printf("Tidak ada data untuk dianalisis.\n");
        return;
    }
    
    int adaDuplikat = 0;
    
    for(int i = 0; i < jumlahKontak; i++){
        for(int j = i + 1; j < jumlahKontak; j++){
            if(strcmp(namaKontak[i], namaKontak[j]) == 0 || 
               strcmp(nomorTelepon[i], nomorTelepon[j]) == 0){
                
                printf("Duplikat ditemukan:\n");
                printf("   Kontak %d: %s (%s)\n", i+1, namaKontak[i], nomorTelepon[i]);
                printf("   Kontak %d: %s (%s)\n", j+1, namaKontak[j], nomorTelepon[j]);
                adaDuplikat = 1;
            }
        }
    }
    
    if(adaDuplikat == 0){
        printf("Tidak ada duplikat ditemukan.\n");
    }
}

// Fungsi menu utama
int tampilkanMenu(){
    int pilihan;
    printf("\n=== BUKU TELEPON DIGITAL ===\n");
    printf("1. Tambah Kontak Baru\n");
    printf("2. Tampilkan Semua Kontak\n");
    printf("3. Cari Kontak\n");
    printf("4. Edit Kontak\n");
    printf("5. Hapus Kontak\n");
    printf("6. Simpan Data ke File\n");
    printf("7. Load Data dari File\n");
    printf("8. Tampilkan Statistik\n");
    printf("9. Export ke File Teks\n");
    printf("10. Deteksi Duplikat\n");
    printf("0. Keluar\n");
    printf("Pilih menu (0-10): ");
    scanf("%d", &pilihan);
    return pilihan;
}

// Fungsi main
int main(){
    printf("=========================================\n");
    printf("    SISTEM MANAJEMEN KONTAK v1.0\n");
    printf("=========================================\n");
    
    bacaDariFile();
    
    int pilihan;
    
    while(1){
        pilihan = tampilkanMenu();
        
        if(pilihan == 1){
            tambahKontak();
        } else if(pilihan == 2){
            tampilkanSemuaKontak();
        } else if(pilihan == 3){
            cariKontak();
        } else if(pilihan == 4){
            editKontak();
        } else if(pilihan == 5){
            hapusKontak();
        } else if(pilihan == 6){
            simpanKeFile();
        } else if(pilihan == 7){
            bacaDariFile();
        } else if(pilihan == 8){
            tampilkanStatistik();
        } else if(pilihan == 9){
            exportKeFileTeks();
        } else if(pilihan == 10){
            deteksiDuplikat();
        } else if(pilihan == 0){
            printf("\nMenyimpan data sebelum keluar...\n");
            simpanKeFile();
            printf("Terima kasih telah menggunakan Sistem Manajemen Kontak!\n");
            printf("=========================================\n");
            break;
        } else {
            printf("Pilihan tidak valid! Silakan pilih 0-10.\n");
        }
        
        printf("\nTekan Enter untuk melanjutkan...");
        getchar();
        getchar();
    }
    
    return 0;

}
