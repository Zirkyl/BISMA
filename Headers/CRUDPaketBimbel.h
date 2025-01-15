#include <stdio.h>
#include <string.h>
#include <conio.h>

typedef enum {True = 1, False = 0} boolean;
typedef char string[255];
typedef struct {
    int id_paket;
    string nama_paket;
    int jenjang_paket;
    int harga_paket;
    string deskripsi;
    int status;
}PaketBimbel;
PaketBimbel paket;
FILE *FPB;
FILE *temp;
int i;

string FPBFilename;
string tempFilename;

int tempID;     // integer ID yang digunakan untuk repetition
boolean found;

void namaFile();            //untuk menentukan nama file yang akan digunakan
void CRUDPaketBimbel();     //prosedur utama untuk CRUD
void CreatePaket();         //prosedur create paket bimbel
void ReadPaket();           //prosedur read paket bimbel
void UpdatePaket();         //prosedur update paket bimbel
void UpdateChoice();        //prosedur pemilihan update dalam prosedur update
void DeletePaket();         //prosedur delete paket bimbel (mengubah status menjadi nonaktif)

void namaFile() {
    strcpy(FPBFilename, "PaketBimbel.dat");
    strcpy(tempFilename, "temp.dat");
}

void CRUDPaketBimbel() {
    namaFile();
    do {
        printf("\n");
        printf("1. Input Paket Bimbel\n");
        printf("2. Read Paket Bimbel\n");
        printf("3. Update Paket Bimbel\n");
        printf("4. Delete Paket Bimbel\n");
        printf("5. Keluar\n");
        printf("Masukkan Angka : "); scanf(" %d",&i);
        printf("\n");

        switch(i) {
            case 1: CreatePaket(); break;
            case 2: ReadPaket(); break;
            case 3: UpdatePaket(); break;
            case 4: DeletePaket(); break;
            case 5: return;
            default: printf("Input gagal\n");
        }
    } while (i != 5);
    getch();
}

void CreatePaket() {
    // DECLARATION
    char yesno;

    // ALGORITHM
    FPB = fopen(FPBFilename, "ab");
    do {
        printf("Masukkan Data\n");
        printf("ID Paket : "); scanf(" %d", &paket.id_paket);
        if (paket.id_paket == 0) {
            return;
        }
        printf("Nama Paket : "); scanf(" %[^\n]", &paket.nama_paket);
        printf("Jenjang Paket : "); scanf(" %d", &paket.jenjang_paket);
        printf("Harga Paket : "); scanf(" %d", &paket.harga_paket);
        printf("Deskripsi Paket : "); scanf(" %[^\n]", &paket.deskripsi);
        paket.status = 1;
        fwrite(&paket, sizeof(paket), 1, FPB);

        do {
            printf("\nApakah ingin menambah lagi [Y/N]: ");
            scanf(" %[^\n]", &yesno);
            if (yesno == 'Y' || yesno == 'y') {
                break;
            } else if (yesno == 'N' || yesno == 'n') {
                fclose(FPB);
                return;
            } else {
                printf("Input gagal\n");
            }
        } while (yesno != 'Y' || yesno != 'y');
    } while (yesno == 'Y' || yesno == 'y');
    fclose(FPB);
    printf("\n");
}

void ReadPaket() {
    FPB = fopen(FPBFilename, "rb");
    while (fread(&paket, sizeof(paket), 1, FPB) == 1 && paket.status == 1) {
        printf("ID Paket : %d\n", paket.id_paket);
        printf("Nama Paket : %s\n", paket.nama_paket);
        printf("Jenjang Paket : %d\n", paket.jenjang_paket);
        printf("Harga Paket : %d\n", paket.harga_paket);
        printf("Deskripsi : %s\n", paket.deskripsi);
        printf("\n");
    }
    fclose(FPB);
}

void UpdatePaket() {
    FPB = fopen(FPBFilename, "rb");
    temp = fopen(tempFilename, "wb");
    printf("ID Paket Bimbel Yang Dicari : ");
    scanf(" %d", &tempID);
    printf("\n");

    found = False;
    while (fread(&paket, sizeof(paket), 1, FPB) == 1) {
        if (tempID == paket.id_paket) {
            UpdateChoice();
            fwrite(&paket, sizeof(paket), 1, temp);
            found = True;
        } else {
            fwrite(&paket, sizeof(paket), 1, temp);
        }
    }
    if (found == False) {
        printf("Kode Paket Bimbel %d tidak ditemukan\n\n", tempID);
        fclose(temp);
        fclose(FPB);
        return;
    }
    fclose(temp);
    fclose(FPB);

    FPB = fopen(FPBFilename, "wb");
    temp = fopen(tempFilename, "rb");
    while (fread(&paket, sizeof(paket), 1, temp) == 1) {
        fwrite(&paket, sizeof(paket), 1, FPB);
    }
    fclose(temp);
    fclose(FPB);
    printf("\n");
}

void UpdateChoice() {
    do {
        printf("\nData apa yang ingin diubah?\n");
        printf("1. ID\n");
        printf("2. Nama\n");
        printf("3. Jenjang\n");
        printf("4. Harga\n");
        printf("5. Deskripsi\n");
        printf("6. Keluar\n");
        printf("Masukkan Angka : ");
        scanf(" %d", &i);
        printf("\n");

        switch (i) {
            case 1: printf("Masukkan ID baru : ");
                scanf(" %d", &paket.id_paket);
                printf("ID berhasil diperbaharui\n");
                break;
            case 2: printf("Masukkan nama baru : ");
                scanf(" %[^\n]", &paket.nama_paket);
                printf("Nama berhasil diperbaharui\n");
                break;
            case 3: printf("Masukkan jenjang baru : ");
                scanf(" %d", &paket.jenjang_paket);
                printf("Jenjang berhasil diperbaharui\n");
                break;
            case 4: printf("Masukkan harga baru : ");
                scanf(" %d", &paket.harga_paket);
                printf("Harga berhasil diperbaharui\n");
                break;
            case 5: printf("Masukkan deskripsi baru : ");
                scanf(" %[^\n]", &paket.deskripsi);
                printf("Deskripsi berhasil diperbaharui\n");
                break;
            case 6: return;
            default: printf("Input gagal\n");
        }
    } while (i != 6);
}

void DeletePaket() {
    FPB = fopen(FPBFilename, "rb");
    temp = fopen(tempFilename, "wb");
    printf("Masukkan ID Paket Bimbel yang ingin dihapus : ");
    scanf(" %d", &tempID);
    printf("\n");

    while (fread(&paket, sizeof(paket), 1, FPB) == 1) {
        if (tempID == paket.id_paket) {
            paket.status = 0;
            fwrite(&paket, sizeof(paket), 1, temp);
            found = True;
            printf("Paket Bimbel Berhasil dihapus\n\n");
        } else {
            fwrite(&paket, sizeof(paket), 1, temp);
        }
    }
    if (found == False) {
        printf("Kode Paket Bimbel %d tidak ditemukan\n\n", tempID);
        fclose(temp);
        fclose(FPB);
        return;
    }
    fclose(temp);
    fclose(FPB);

    FPB = fopen(FPBFilename, "wb");
    temp = fopen(tempFilename, "rb");
    while (fread(&paket, sizeof(paket), 1, temp) == 1) {
        fwrite(&paket, sizeof(paket), 1, FPB);
    }
    fclose(temp);
    fclose(FPB);
    printf("\n");
}