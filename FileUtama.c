#include <stdio.h>
#include <string.h>
#include <stdlib.h>

char namaKontak[100][50];
char nomorTelepon[100][15];
char emailKontak[100][50];
char kelompokKontak[100][30];
int jumlahKontak = 0;

int validasiNomorTelepon(char nohp[]){
    for(int i = 0; i < strlen(nohp); i++){
        if(nohp[i] < '0' || nohp[i] > '9'){
            return 0; 
        }
    }
    return 1; 
}


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

    if(!validasiNomorTelepon(nomorTelepon[jumlahKontak])){
        printf("Nomor telepon hanya boleh berisi angka!\n");
        printf("Data gagal ditambahkan!\n");
        return;
    }

    printf("Email (....@gmail.com): ");
    scanf(" %[^\n]", emailKontak[jumlahKontak]);
    
    if(strstr(emailKontak[jumlahKontak], "@gmail.com") == NULL){
        printf("Email harus menggunakan @gmail.com\n");
        printf("Data gagal ditambahkan!\n");
        return;
    }

    printf("Kelompok (Keluarga/Teman/Kerja/Lainnya): ");
    scanf(" %[^\n]", kelompokKontak[jumlahKontak]);

    if(strcmp(kelompokKontak[jumlahKontak], "Keluarga") != 0 &&
       strcmp(kelompokKontak[jumlahKontak], "Teman") != 0 &&
       strcmp(kelompokKontak[jumlahKontak], "Kerja") != 0 &&
       strcmp(kelompokKontak[jumlahKontak], "Lainnya") != 0){
        
        printf("Kelompok harus sesuai pilihan: Keluarga / Teman / Kerja / Lainnya\n");
        printf("Data gagal ditambahkan!\n");
        return;
    }
    
    jumlahKontak++;
    printf("\nKontak berhasil ditambahkan!\n");
}

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

void cariKontak(){
    printf("\n=== CARI KONTAK ===\n");
    
    if(jumlahKontak == 0){
        printf("Tidak ada kontak yang bisa dicari.\n");
        return;
    }
    
    char katakunci[50];
    printf("Masukkan nama yang dicari: ");
    scanf(" %[^\n]", katakunci);
    
    int ditemukan = 0;
    for(int i = 0; i < jumlahKontak; i++){
        if(strstr(namaKontak[i], katakunci) != NULL){
            printf("\nKontak ditemukan:\n");
            printf("ID: %d\n", i+1);
            printf("Nama: %s\n", namaKontak[i]);
            printf("Telepon: %s\n", nomorTelepon[i]);
            printf("Email: %s\n", emailKontak[i]);
            printf("Kelompok: %s\n", kelompokKontak[i]);
            ditemukan = 1;
        }
    }
    
    if(!ditemukan){
        printf("Tidak ada kontak yang cocok.\n");
    }
}

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

    if(!validasiNomorTelepon(nomorTelepon[index])){
        printf("Nomor telepon tidak valid! Edit dibatalkan.\n");
        return;
    }
    
    printf("Email Baru (@gmail.com): ");
    scanf(" %[^\n]", emailKontak[index]);

    if(strstr(emailKontak[index], "@gmail.com") == NULL){
        printf("Email tidak valid! Edit dibatalkan.\n");
        return;
    }

    printf("Kelompok Baru (Keluarga/Teman/Kerja/Lainnya): ");
    scanf(" %[^\n]", kelompokKontak[index]);

    if(strcmp(kelompokKontak[index], "Keluarga") != 0 &&
       strcmp(kelompokKontak[index], "Teman") != 0 &&
       strcmp(kelompokKontak[index], "Kerja") != 0 &&
       strcmp(kelompokKontak[index], "Lainnya") != 0){
        
        printf("Kelompok tidak valid! Edit dibatalkan.\n");
        return;
    }
    
    printf("\nKontak berhasil diupdate!\n");
}

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

void simpanKeFile(){
    FILE *file = fopen("data_kontak.txt", "w");
    
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

void bacaDariFile(){
    FILE *file = fopen("data_kontak.txt", "r");
    
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

void exportKeFileTeks(){
    FILE *file = fopen("export_kontak.txt", "w");

    if(file == NULL){
        printf("Gagal membuat file!\n");
        return;
    }

    if(jumlahKontak == 0){
        fprintf(file, "DAFTAR KONTAK\n=============\nTotal: 0 kontak\n\n");
        fclose(file);
        printf("File export kosong berhasil dibuat (0 kontak)\n");
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

int tampilkanMenu(){
    int pilihan;
    printf("\n=== BUKU TELEPON DIGITAL ===\n");
    printf("1. Tambah Kontak Baru\n");
    printf("2. Tampilkan Semua Kontak\n");
    printf("3. Cari Kontak\n");
    printf("4. Edit Kontak\n");
    printf("5. Hapus Kontak\n");
    printf("6. Simpan Data ke File\n");
    printf("7. Export ke File Teks\n");
    printf("8. Deteksi Duplikat\n");
    printf("0. Keluar\n");
    printf("Pilih menu (0-8): ");
    scanf("%d", &pilihan);
    return pilihan;
}


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
            exportKeFileTeks();
        } else if(pilihan == 8){
            deteksiDuplikat();
        } else if(pilihan == 0){
            printf("\nKeluar tanpa menyimpan otomatis.\n");
            printf("Terima kasih telah menggunakan Sistem Manajemen Kontak!\n");
            printf("=========================================\n");
            break;
        } else {
            printf("Pilihan tidak valid! Silakan pilih 0-8.\n");
        }
        
        printf("\nTekan Enter untuk melanjutkan...");
        getchar();
        getchar();
    }
    
    return 0;
}












