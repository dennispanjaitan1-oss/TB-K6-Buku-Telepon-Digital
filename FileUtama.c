#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <time.h>
#include <ctype.h>

#define LEBAR 80 

char namaKontak[100][50];
char nomorTelepon[100][15];
char emailKontak[100][50];
char kelompokKontak[100][30];
int favoritKontak[100];
int jumlahKontak = 0;

char riwayatAksi[500][100];
char riwayatWaktu[500][30];
int jumlahRiwayat = 0;

void cetakGaris(){
    for(int i = 0; i < LEBAR; i++){
        printf("=");
    }
    printf("\n");
}


void cetakGarisTipis(){
    for(int i = 0; i < LEBAR; i++){
        printf("-");
    }
    printf("\n");
}


void cetakTengah(const char *teks){
    int panjang = strlen(teks);
    int spasi = (LEBAR - panjang) / 2;
    for(int i = 0; i < spasi; i++){
        printf(" ");
    }
    printf("%s\n", teks);
}


void tampilkanHeader(const char *judul){
    printf("\n");
    cetakGaris();
    cetakTengah(judul);
    cetakGaris();
}


void tampilkanFooter(){
    int jumlahFavorit = 0;
    for(int i = 0; i < jumlahKontak; i++){
        if(favoritKontak[i] == 1){
            jumlahFavorit++;
        }
    }
    
    printf("\n");
    cetakGaris();
    char info[100];
    sprintf(info, "Total Kontak: %d | Favorit: %d", jumlahKontak, jumlahFavorit);
    cetakTengah(info);
    cetakGaris();
}


void tambahRiwayat(char aksi[]){
    if(jumlahRiwayat >= 500){
        return;
    }
    
    time_t waktuSekarang;
    struct tm *infoWaktu;
    time(&waktuSekarang);
    infoWaktu = localtime(&waktuSekarang);
    
    strcpy(riwayatAksi[jumlahRiwayat], aksi);
    strftime(riwayatWaktu[jumlahRiwayat], 30, "%d-%m-%Y %H:%M:%S", infoWaktu);
    jumlahRiwayat++;
}

int validasiNomorTelepon(char nohp[]){
    if(strlen(nohp) == 0) return 0;
    for(int i = 0; i < (int)strlen(nohp); i++){
        if(nohp[i] < '0' || nohp[i] > '9'){
            return 0; 
        }
    }
    return 1; 
}


int validasiNama(char nama[]){
    if(strlen(nama) == 0) return 0;
    for(int i = 0; i < (int)strlen(nama); i++){
        if(!isalpha((unsigned char)nama[i]) && nama[i] != ' '){
            return 0;
        }
    }
    return 1;
}


void tekanEnter(){
    printf("\nKlik Enter yaa untuk kembali");
    while(getchar() != '\n');
}

void bersihkanBuffer(){
    while(getchar() != '\n');
}

void toLowerStr(const char *src, char *dst){
    int i;
    for(i = 0; src[i] != '\0' && i < 100; i++){
        dst[i] = tolower((unsigned char)src[i]);
    }
    dst[i] = '\0';
}

void tambahKontak(){
    if(jumlahKontak >= 100){
        tampilkanHeader("TAMBAH KONTAK BARU");
        printf("\nYahh Database kontak penuh!\n");
        tekanEnter();
        return;
    }

    
    tampilkanHeader("TAMBAH KONTAK BARU");
    
    while(1){
        printf("\nNama: ");
        scanf(" %[^\n]", namaKontak[jumlahKontak]);
        bersihkanBuffer();
        if(!validasiNama(namaKontak[jumlahKontak])){
            printf("Nama hanya boleh berisi huruf dan spasi yaa, Silakan coba lagi.\n");
            continue;
        }
        break;
    }

    
    while(1){
        printf("Nomor Telepon: ");
        scanf(" %[^\n]", nomorTelepon[jumlahKontak]);
        bersihkanBuffer();
        if(!validasiNomorTelepon(nomorTelepon[jumlahKontak])){
            printf("Nomor telepon hanya boleh berisi angka yaa, Silakan coba lagi.\n");
            continue;
        }
        break;
    }

    
    while(1){
        printf("Email : ");
        scanf(" %[^\n]", emailKontak[jumlahKontak]);
        bersihkanBuffer();
        if(strstr(emailKontak[jumlahKontak], "@gmail.com") == NULL){
            printf("Email harus menggunakan @gmail.com yaa, Silakan coba lagi.\n");
            continue;
        }
        break;
    }

    
    while(1){
        printf("Kelompok (Keluarga/Teman/Kerja/Lainnya): ");
        scanf(" %[^\n]", kelompokKontak[jumlahKontak]);
        bersihkanBuffer();
        if(strcmp(kelompokKontak[jumlahKontak], "Keluarga") != 0 &&
           strcmp(kelompokKontak[jumlahKontak], "Teman") != 0 &&
           strcmp(kelompokKontak[jumlahKontak], "Kerja") != 0 &&
           strcmp(kelompokKontak[jumlahKontak], "Lainnya") != 0){
            
            printf("Kelompok harus sesuai pilihan yaa, Silakan coba lagi.\n");
            continue;
        }
        break;
    }
    
    favoritKontak[jumlahKontak] = 0;
    jumlahKontak++;
    
    char log[100];
    sprintf(log, "Tambah kontak: %s", namaKontak[jumlahKontak-1]);
    tambahRiwayat(log);
    
    printf("\nWihh, Kontak berhasil ditambahkan!\n");
    tekanEnter();
}


void tampilkanSemuaKontak(){
    tampilkanHeader("DAFTAR SEMUA KONTAK");
    
    if(jumlahKontak == 0){
        printf("\nYahh, Tidak ada kontak yang tersimpan.\n");
        tekanEnter();
        return;
    }
    
    for(int i = 0; i < jumlahKontak; i++){
        printf("\n");
        cetakGarisTipis();
        char header[100];
        sprintf(header, "Kontak #%d", i+1);
        cetakTengah(header);
        cetakGarisTipis();
        printf("  Nama      : %s", namaKontak[i]);
        if(favoritKontak[i] == 1){
            printf(" [FAVORIT]");
        }
        printf("\n");
        printf("  Telepon   : %s\n", nomorTelepon[i]);
        printf("  Email     : %s\n", emailKontak[i]);
        printf("  Kelompok  : %s\n", kelompokKontak[i]);
    }
    
    tampilkanFooter();
    tekanEnter();
}

void cariKontak(){
    tampilkanHeader("CARI KONTAK");
    
    if(jumlahKontak == 0){
        printf("\nYahh, Tidak ada kontak yang bisa dicari.\n");
        tekanEnter();
        return;
    }
    
    while(1){
        char katakunci[50];
        printf("\nTolong masukin nama yang mau dicari yaa: ");
        if(fgets(katakunci, sizeof(katakunci), stdin) == NULL){
            continue;
        }
        katakunci[strcspn(katakunci, "\n")] = 0;
        
        if(strlen(katakunci) == 0){
            printf("Nama tidak boleh kosong yaa, Silakan coba lagi.\n");
            continue;
        }
        
        char kataLower[100];
        toLowerStr(katakunci, kataLower);
        
        int ditemukan = 0;
        for(int i = 0; i < jumlahKontak; i++){
            char namaLower[100];
            toLowerStr(namaKontak[i], namaLower);
            if(strstr(namaLower, kataLower) != NULL){
                if(!ditemukan){
                    printf("\n");
                    cetakGarisTipis();
                    cetakTengah("HASIL PENCARIAN");
                    cetakGarisTipis();
                }
                printf("\n");
                printf("  ID        : %d\n", i+1);
                printf("  Nama      : %s", namaKontak[i]);
                if(favoritKontak[i] == 1){
                    printf(" [FAVORIT]");
                }
                printf("\n");
                printf("  Telepon   : %s\n", nomorTelepon[i]);
                printf("  Email     : %s\n", emailKontak[i]);
                printf("  Kelompok  : %s\n", kelompokKontak[i]);
                cetakGarisTipis();
                ditemukan = 1;
            }
        }
        
        if(!ditemukan){
            printf("\nYahh, ngga ada kontak yang cocok dengan '%s'.\n", katakunci);
            printf("Mau cari lagi? (y/n): ");
            char pilihan[10];
            if(fgets(pilihan, sizeof(pilihan), stdin) == NULL){
                return;
            }
            if(pilihan[0] == 'y' || pilihan[0] == 'Y'){
                continue;
            } else {
                return;
            }
        } else {
            tekanEnter();
            return;
        }
    }
}

void editKontak(){
    tampilkanHeader("EDIT KONTAK");
    
    if(jumlahKontak == 0){
        printf("\nYahh, ngga ada kontak yang bisa diedit.\n");
        tekanEnter();
        return;
    }
    
    int id;
    while(1){
        printf("\nTolong masukin ID kontak yang mau diedit yaa (1-%d): ", jumlahKontak);
        if(scanf("%d", &id) != 1){
            bersihkanBuffer();
            printf("Yahh, Input nya ngga valid! Masukkan angka ID.\n");
            continue;
        }
        bersihkanBuffer();
        if(id < 1 || id > jumlahKontak){
            printf("Yahh, ID nya ngga valid! Silakan coba lagi.\n");
            continue;
        }
        break;
    }
    
    int index = id - 1;
    char namaLama[50];
    strcpy(namaLama, namaKontak[index]);
    
    while(1){
        printf("\n");
        cetakGarisTipis();
        printf("Mengedit kontak: %s\n", namaKontak[index]);
        cetakGarisTipis();
        printf("Pilih data yang mau kamu edit yaa:\n");
        printf("  1. Nama\n");
        printf("  2. Nomor Telepon\n");
        printf("  3. Email\n");
        printf("  4. Kelompok\n");
        printf("  5. Selesai / Kembali\n");
        cetakGarisTipis();
        printf("Masukkan pilihan kamu yaa (1-5): ");
        
        int pilihan;
        if(scanf("%d", &pilihan) != 1){
            bersihkanBuffer();
            printf("\nYahh, Pilihan kamu ngga valid! Masukkan angka 1-5.\n");
            continue;
        }
        bersihkanBuffer();
        
        if(pilihan == 1){
            while(1){
                printf("Nama Baru: ");
                scanf(" %[^\n]", namaKontak[index]);
                bersihkanBuffer();
                if(!validasiNama(namaKontak[index])){
                    printf("Yahh, Nama nya ngga valid! Silakan coba lagi.\n");
                    continue;
                }
                char log[100];
                sprintf(log, "Edit kontak: %s -> nama menjadi %s", namaLama, namaKontak[index]);
                tambahRiwayat(log);
                strcpy(namaLama, namaKontak[index]);
                printf("\nNama berhasil diubah.\n");
                break;
            }
        } else if(pilihan == 2){
            while(1){
                printf("Nomor Telepon Baru: ");
                scanf(" %[^\n]", nomorTelepon[index]);
                bersihkanBuffer();
                if(!validasiNomorTelepon(nomorTelepon[index])){
                    printf("Yahh, nomor telepon nya ngga valid! Silakan coba lagi.\n");
                    continue;
                }
                char log[100];
                sprintf(log, "Edit kontak: %s -> nomor menjadi %s", namaKontak[index], nomorTelepon[index]);
                tambahRiwayat(log);
                printf("\nNomor nya udah berhasil diubah yaa.\n");
                break;
            }
        } else if(pilihan == 3){
            while(1){
                printf("Email Baru : ");
                scanf(" %[^\n]", emailKontak[index]);
                bersihkanBuffer();
                if(strstr(emailKontak[index], "@gmail.com") == NULL){
                    printf("Yahh, Email nya ngga valid! Silakan coba lagi.\n");
                    continue;
                }
                char log[100];
                sprintf(log, "Edit kontak: %s -> email menjadi %s", namaKontak[index], emailKontak[index]);
                tambahRiwayat(log);
                printf("\nYeyy, Email nya udah berhasil diubah yaa.\n");
                break;
            }
        } else if(pilihan == 4){
            while(1){
                printf("Kelompok Baru (Keluarga/Teman/Kerja/Lainnya): ");
                scanf(" %[^\n]", kelompokKontak[index]);
                bersihkanBuffer();
                if(strcmp(kelompokKontak[index], "Keluarga") != 0 &&
                   strcmp(kelompokKontak[index], "Teman") != 0 &&
                   strcmp(kelompokKontak[index], "Kerja") != 0 &&
                   strcmp(kelompokKontak[index], "Lainnya") != 0){
                    
                    printf("Yahh, Kelompok nya ngga valid! Silakan coba lagi.\n");
                    continue;
                }
                char log[100];
                sprintf(log, "Edit kontak: %s -> kelompok menjadi %s", namaKontak[index], kelompokKontak[index]);
                tambahRiwayat(log);
                printf("\nYeyy, Kelompok udah berhasil diubah yaa.\n");
                break;
            }
        } else if(pilihan == 5){
            printf("\nUdah siap mengedit kontak.\n");
            tekanEnter();
            return;
        } else {
            printf("\nYahh, Pilihan kamu ngga valid! Silakan pilih 1-5.\n");
        }
    }
}


void hapusKontak(){
    tampilkanHeader("HAPUS KONTAK");
    
    if(jumlahKontak == 0){
        printf("\nYahh, ngga ada kontak yang bisa dihapus.\n");
        tekanEnter();
        return;
    }
    
    int id;
    while(1){
        printf("\nMasukkan ID kontak yang mau dihapus yaa (1-%d): ", jumlahKontak);
        if(scanf("%d", &id) != 1){
            bersihkanBuffer();
            printf("Yahh, input nya ngga valid! Masukkan angka ID.\n");
            continue;
        }
        bersihkanBuffer();
        if(id < 1 || id > jumlahKontak){
            printf("Yahh, ID nya ngga valid! Silakan coba lagi.\n");
            continue;
        }
        break;
    }
    
    int index = id - 1;
    
    printf("\n");
    cetakGarisTipis();
    char konfirmasiMsg[100];
    sprintf(konfirmasiMsg, "Hapus kontak: %s?", namaKontak[index]);
    cetakTengah(konfirmasiMsg);
    cetakGarisTipis();
    
    char konfirmasi;
    while(1){
        printf("Konfirmasi (y/n): ");
        scanf(" %c", &konfirmasi);
        bersihkanBuffer();
        if(konfirmasi == 'y' || konfirmasi == 'Y' || konfirmasi == 'n' || konfirmasi == 'N'){
            break;
        }
        printf("Yahh, Pilihan kamu ngga valid! Masukkan 'y' atau 'n' yaa\n");
    }
    
    if(konfirmasi == 'y' || konfirmasi == 'Y'){
        char log[100];
        sprintf(log, "Hapus kontak: %s", namaKontak[index]);
        tambahRiwayat(log);
        
        for(int i = index; i < jumlahKontak - 1; i++){
            strcpy(namaKontak[i], namaKontak[i + 1]);
            strcpy(nomorTelepon[i], nomorTelepon[i + 1]);
            strcpy(emailKontak[i], emailKontak[i + 1]);
            strcpy(kelompokKontak[i], kelompokKontak[i + 1]);
            favoritKontak[i] = favoritKontak[i + 1];
        }
        jumlahKontak--;
        printf("\nYeyy, Kontak berhasil dihapus!\n");
    } else {
        printf("\nYeyy, Penghapusan dibatalkan.\n");
    }
    
    tekanEnter();
}

void tandaiFavorit(){
    tampilkanHeader("KELOLA FAVORIT");
    
    if(jumlahKontak == 0){
        printf("\nYahh, ngga ada kontak yang tersedia nihh\n");
        tekanEnter();
        return;
    }
    
    int id;
    while(1){
        printf("\nMasukkan ID kontak (1-%d): ", jumlahKontak);
        if(scanf("%d", &id) != 1){
            bersihkanBuffer();
            printf("Yahh, Input kamu ngga valid! Masukkan angka ID.\n");
            continue;
        }
        bersihkanBuffer();
        if(id < 1 || id > jumlahKontak){
            printf("Yahh, ID nya ngga valid! Silakan coba lagi.\n");
            continue;
        }
        break;
    }
    
    int index = id - 1;
    
    if(favoritKontak[index] == 0){
        favoritKontak[index] = 1;
        printf("\nYeyy, Kontak '%s' ditandai sebagai favorit!\n", namaKontak[index]);
        
        char log[100];
        sprintf(log, "Tandai favorit: %s", namaKontak[index]);
        tambahRiwayat(log);
    } else {
        char konfirmasi;
        while(1){
            printf("\nKontak '%s' sudah masuk favorit nih. Mau hapus dari favorit kah? (y/n): ", namaKontak[index]);
            scanf(" %c", &konfirmasi);
            bersihkanBuffer();
            if(konfirmasi == 'y' || konfirmasi == 'Y' || konfirmasi == 'n' || konfirmasi == 'N'){
                break;
            }
            printf("Yahh, Pilihan kamu ngga valid! Masukkan 'y' atau 'n'.\n");
        }
        if(konfirmasi == 'y' || konfirmasi == 'Y'){
            favoritKontak[index] = 0;
            printf("\nYeyy, Kontak '%s' dihapus dari favorit!\n", namaKontak[index]);
            char log[100];
            sprintf(log, "Hapus favorit: %s", namaKontak[index]);
            tambahRiwayat(log);
        } else {
            printf("\nYeyy, Operasi batal. Kontak tetap di favorit yaa.\n");
        }
    }
    
    tekanEnter();
}


void tampilkanFavorit(){
    tampilkanHeader("KONTAK FAVORIT");
    
    int adaFavorit = 0;
    
    for(int i = 0; i < jumlahKontak; i++){
        if(favoritKontak[i] == 1){
            printf("\n");
            cetakGarisTipis();
            char header[100];
            sprintf(header, "Kontak #%d", i+1);
            cetakTengah(header);
            cetakGarisTipis();
            printf("  Nama      : %s\n", namaKontak[i]);
            printf("  Telepon   : %s\n", nomorTelepon[i]);
            printf("  Email     : %s\n", emailKontak[i]);
            printf("  Kelompok  : %s\n", kelompokKontak[i]);
            adaFavorit = 1;
        }
    }

    
    if(!adaFavorit){
        printf("\nBelum ada kontak favorit.\n");
    }
    
    tekanEnter();
}

void statistikKontak(){
    tampilkanHeader("STATISTIK KONTAK");
    
    if(jumlahKontak == 0){
        printf("\nYahh, ngga ada data yang bisa ditampilin, karena data kamu kosong\n");
        tekanEnter();
        return;
    }
    
    int jumlahKeluarga = 0;
    int jumlahTeman = 0;
    int jumlahKerja = 0;
    int jumlahLainnya = 0;
    int jumlahFavorit = 0;
    
    for(int i = 0; i < jumlahKontak; i++){
        if(strcmp(kelompokKontak[i], "Keluarga") == 0){
            jumlahKeluarga++;
        } else if(strcmp(kelompokKontak[i], "Teman") == 0){
            jumlahTeman++;
        } else if(strcmp(kelompokKontak[i], "Kerja") == 0){
            jumlahKerja++;
        } else if(strcmp(kelompokKontak[i], "Lainnya") == 0){
            jumlahLainnya++;
        }
        
        if(favoritKontak[i] == 1){
            jumlahFavorit++;
        }
    }
    
    printf("\n");
    char total[50];
    sprintf(total, "Total Kontak: %d", jumlahKontak);
    cetakTengah(total);   

    printf("\n");
    cetakTengah("BERDASARKAN KELOMPOK");
    cetakGarisTipis();
    printf("  Keluarga  : %d kontak\n", jumlahKeluarga);
    printf("  Teman     : %d kontak\n", jumlahTeman);
    printf("  Kerja     : %d kontak\n", jumlahKerja);
    printf("  Lainnya   : %d kontak\n", jumlahLainnya);
    cetakGarisTipis();
    
    printf("\n");
    char fav[50];
    sprintf(fav, "Kontak Favorit: %d", jumlahFavorit);
    cetakTengah(fav);
    
    tekanEnter();
}

void urutkanKontak(){
    tampilkanHeader("URUTKAN KONTAK");
    
    if(jumlahKontak == 0){
        printf("\nYahh, ngga ada kontak yang mau diurutin\n");
        tekanEnter();
        return;
    }

    
    int pilihan;
    while(1){
        printf("\nPilih urutan:\n");
        printf("  1. Berdasarkan Nama (A-Z)\n");
        printf("  2. Berdasarkan Kelompok\n");
        cetakGarisTipis();
        printf("Masukkan pilihan kamu yaa: ");
        if(scanf("%d", &pilihan) != 1){
            bersihkanBuffer();
            printf("Yahh, Pilihan ngga valid! Masukkan angka 1 atau 2 yaa\n");
            continue;
        }
        bersihkanBuffer();
        if(pilihan != 1 && pilihan != 2){
            printf("Yahh, Pilihan ngga valid! Masukkan angka 1 atau 2 yaa\n");
            continue;
        }
        break;
    }
    
    if(pilihan == 1){
        for(int i = 0; i < jumlahKontak - 1; i++){
            for(int j = i + 1; j < jumlahKontak; j++){
                if(strcmp(namaKontak[i], namaKontak[j]) > 0){
                    char tempNama[50], tempTelepon[15], tempEmail[50], tempKelompok[30];
                    int tempFavorit;
                    
                    strcpy(tempNama, namaKontak[i]);
                    strcpy(tempTelepon, nomorTelepon[i]);
                    strcpy(tempEmail, emailKontak[i]);
                    strcpy(tempKelompok, kelompokKontak[i]);
                    tempFavorit = favoritKontak[i];
                    
                    strcpy(namaKontak[i], namaKontak[j]);
                    strcpy(nomorTelepon[i], nomorTelepon[j]);
                    strcpy(emailKontak[i], emailKontak[j]);
                    strcpy(kelompokKontak[i], kelompokKontak[j]);
                    favoritKontak[i] = favoritKontak[j];
                    
                    strcpy(namaKontak[j], tempNama);
                    strcpy(nomorTelepon[j], tempTelepon);
                    strcpy(emailKontak[j], tempEmail);
                    strcpy(kelompokKontak[j], tempKelompok);
                    favoritKontak[j] = tempFavorit;
                }
            }
        }
        printf("\nYeyy, Kontak udah berhasil diurutin berdasarkan nama yaa!\n");
        tambahRiwayat("Urutkan kontak berdasarkan nama");
        
    } else {
        for(int i = 0; i < jumlahKontak - 1; i++){
            for(int j = i + 1; j < jumlahKontak; j++){
                if(strcmp(kelompokKontak[i], kelompokKontak[j]) > 0){
                    char tempNama[50], tempTelepon[15], tempEmail[50], tempKelompok[30];
                    int tempFavorit;
                    
                    strcpy(tempNama, namaKontak[i]);
                    strcpy(tempTelepon, nomorTelepon[i]);
                    strcpy(tempEmail, emailKontak[i]);
                    strcpy(tempKelompok, kelompokKontak[i]);
                    tempFavorit = favoritKontak[i];
                    
                    strcpy(namaKontak[i], namaKontak[j]);
                    strcpy(nomorTelepon[i], nomorTelepon[j]);
                    strcpy(emailKontak[i], emailKontak[j]);
                    strcpy(kelompokKontak[i], kelompokKontak[j]);
                    favoritKontak[i] = favoritKontak[j];
                    
                    strcpy(namaKontak[j], tempNama);
                    strcpy(nomorTelepon[j], tempTelepon);
                    strcpy(emailKontak[j], tempEmail);
                    strcpy(kelompokKontak[j], tempKelompok);
                    favoritKontak[j] = tempFavorit;
                }
            }
        }
        printf("\nYeyy Kontak udah berhasil diurutin berdasarkan kelompok yaa!\n");
        tambahRiwayat("Urutkan kontak berdasarkan kelompok");
    }
    
    tekanEnter();
}

void tampilkanRiwayat(){
    tampilkanHeader("RIWAYAT PERUBAHAN");
    
    if(jumlahRiwayat == 0){
        printf("\nYahh, Belum ada aktivitas yang tercatat nih\n");
        tekanEnter();
        return;
    }
    
    int batasTampil = jumlahRiwayat > 20 ? 20 : jumlahRiwayat;
    
    char info[100];
    sprintf(info, "Menampilkan %d aktivitas terakhir", batasTampil);
    printf("\n");
    cetakTengah(info);
    printf("\n");
    
    for(int i = jumlahRiwayat - 1; i >= jumlahRiwayat - batasTampil; i--){
        printf("[%s] %s\n", riwayatWaktu[i], riwayatAksi[i]);
    }
    
    tekanEnter();
}

void simpanKeFile(){
    FILE *file = fopen("data_kontak.txt", "w");
    
    if(file == NULL){
        printf("\nYahh, Gagal membuka file!\n");
        tekanEnter();
        return;
    }
    
    fprintf(file, "Jumlah Kontak    : %d\n", jumlahKontak);
    
    for(int i = 0; i < jumlahKontak; i++){
        fprintf(file, "Nama             : %s\n", namaKontak[i]);
        fprintf(file, "Nomor Telepon    : %s\n", nomorTelepon[i]);
        fprintf(file, "Email            : %s\n", emailKontak[i]);
        fprintf(file, "Kelompok         : %s\n", kelompokKontak[i]);
        fprintf(file, "Favorit          : %d\n", favoritKontak[i]);
        fprintf(file, "\n");
    }
    
    fclose(file);
    
    FILE *fileRiwayat = fopen("riwayat_kontak.txt", "w");
    if(fileRiwayat != NULL){
        fprintf(fileRiwayat, "%d\n", jumlahRiwayat);
        for(int i = 0; i < jumlahRiwayat; i++){
            fprintf(fileRiwayat, "%s\n", riwayatAksi[i]);
            fprintf(fileRiwayat, "%s\n", riwayatWaktu[i]);
        }
        fclose(fileRiwayat);
    }
    
    printf("\nYeyy, data udah berhasil disimpan ke file yaa!\n");
    tambahRiwayat("Simpan data ke file");
    tekanEnter();
}

void bacaDariFile(){
    FILE *file = fopen("data_kontak.txt", "r");
    
    if(file == NULL){
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
        
        fscanf(file, "%d\n", &favoritKontak[i]);
    }
    
    fclose(file);
    
    FILE *fileRiwayat = fopen("riwayat_kontak.txt", "r");
    if(fileRiwayat != NULL){
        fscanf(fileRiwayat, "%d\n", &jumlahRiwayat);
        for(int i = 0; i < jumlahRiwayat; i++){
            fgets(riwayatAksi[i], 100, fileRiwayat);
            riwayatAksi[i][strcspn(riwayatAksi[i], "\n")] = 0;
            
            fgets(riwayatWaktu[i], 30, fileRiwayat);
            riwayatWaktu[i][strcspn(riwayatWaktu[i], "\n")] = 0;
        }
        fclose(fileRiwayat);
    }
}


void exportKeFileTeks(){
    FILE *file = fopen("export_kontak.txt", "w");

    if(file == NULL){
        printf("\nYahh, gagal membuat file!\n");
        tekanEnter();
        return;
    }

    if(jumlahKontak == 0){
        fprintf(file, "DAFTAR KONTAK\n");
        for(int i = 0; i < LEBAR; i++) fprintf(file, "=");
        fprintf(file, "\nTotal: 0 kontak\n\n");
        fclose(file);
        printf("\nYeyy, File export kosong udah berhasil dibuat yaa (0 kontak)\n");
        tekanEnter();
        return;
    }

    fprintf(file, "DAFTAR KONTAK\n");
    for(int i = 0; i < LEBAR; i++) fprintf(file, "=");
    fprintf(file, "\nTotal: %d kontak\n\n", jumlahKontak);

    for(int i = 0; i < jumlahKontak; i++){
        fprintf(file, "Kontak #%d\n", i+1);
        for(int j = 0; j < LEBAR; j++) fprintf(file, "-");
        fprintf(file, "\n");
        fprintf(file, "Nama      : %s", namaKontak[i]);
        if(favoritKontak[i] == 1){
            fprintf(file, " [FAVORIT]");
        }
        fprintf(file, "\n");
        fprintf(file, "Telepon   : %s\n", nomorTelepon[i]);
        fprintf(file, "Email     : %s\n", emailKontak[i]);
        fprintf(file, "Kelompok  : %s\n", kelompokKontak[i]);
        fprintf(file, "\n");
    }

    fclose(file);
    printf("\nYeyy, data sudah berhasil di-export ke 'export_kontak.txt' yaa\n");
    tambahRiwayat("Export data ke file teks");
    tekanEnter();
}

void deteksiDuplikat(){
    tampilkanHeader("DETEKSI DUPLIKAT");
    
    if(jumlahKontak == 0){
        printf("\nYahh, ngga ada data yang mau dianalisis.\n");
        tekanEnter();
        return;
    }
    
    int adaDuplikat = 0;
    
    for(int i = 0; i < jumlahKontak; i++){
        for(int j = i + 1; j < jumlahKontak; j++){
            if(strcmp(namaKontak[i], namaKontak[j]) == 0 || 
               strcmp(nomorTelepon[i], nomorTelepon[j]) == 0){
                
                printf("\nYeyy, Duplikat ditemukan:\n");
                printf("  Kontak %d: %s (%s)\n", i+1, namaKontak[i], nomorTelepon[i]);
                printf("  Kontak %d: %s (%s)\n", j+1, namaKontak[j], nomorTelepon[j]);
                adaDuplikat = 1;
            }
        }
    }
    
    if(adaDuplikat == 0){
        printf("\nYahh, ngga ada duplikat ditemukan.\n");
    }
    
    tekanEnter();
}


int tampilkanMenu(){
    int pilihan;
    
    printf("\n");
    cetakGaris();
    cetakTengah("BUKU TELEPON DIGITAL");
    cetakGaris();
    printf(" 1.  Tambah Kontak Baru\n");
    printf(" 2.  Tampilkan Semua Kontak\n");
    printf(" 3.  Cari Kontak\n");
    printf(" 4.  Edit Kontak\n");
    printf(" 5.  Hapus Kontak\n");
    printf(" 6.  Kelola Favorit\n");
    printf(" 7.  Tampilkan Kontak Favorit\n");
    printf(" 8.  Statistik Kontak\n");
    printf(" 9.  Urutkan Kontak\n");
    printf(" 10. Riwayat Perubahan\n");
    printf(" 11. Simpan Data ke File\n");
    printf(" 12. Export ke File Teks\n");
    printf(" 13. Deteksi Duplikat\n");
    printf(" 0.  Keluar\n");
    cetakGarisTipis();
    printf("Masukkan pilihan Anda (0-13): ");
    if(scanf("%d", &pilihan) != 1){
        bersihkanBuffer();
        return -1;
    }
    bersihkanBuffer();
    return pilihan;
}

int main(){
    printf("\n");
    cetakGaris();
    cetakTengah("SISTEM MANAJEMEN KONTAK");
    cetakTengah("Kami Membantu Mengelola Kontak Anda dengan Mudah");
    cetakGaris();
    
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
            tandaiFavorit();
        } else if(pilihan == 7){
            tampilkanFavorit();
        } else if(pilihan == 8){
            statistikKontak();
        } else if(pilihan == 9){
            urutkanKontak();
        } else if(pilihan == 10){
            tampilkanRiwayat();
        } else if(pilihan == 11){
            simpanKeFile();
        } else if(pilihan == 12){
            exportKeFileTeks();
        } else if(pilihan == 13){
            deteksiDuplikat();
        } else if(pilihan == 0){
            printf("\n");
            cetakGarisTipis();
            cetakTengah("Terima kasih yaa udah menggunakan");
            cetakTengah("Sistem Manajemen Kontak Kami, See You!");
            cetakGarisTipis();
            printf("\n");
            break;
        } else {
            printf("\nYahh, Pilihan kamu ngga valid! Silakan pilih 0-13 yaa\n");
            tekanEnter();
        }
    }
    
    return 0;
}











