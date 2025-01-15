#include <stdio.h>
#include <string.h>
#include <conio.h>

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


void namaFile();
void CRUDPaketBimbel();
void CreatePaket();
void ReadPaket();
void UpdatePaket();
void DeletePaket();

void namaFile() {
    strcpy(FPBFilename, "PaketBimbel.dat");
    strcpy(tempFilename, "temp.dat");
}

void CRUDPaketBimbel() {
    namaFile();
    do {
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
            case 3: ; break;
            case 4: ; break;
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
}

void ReadPaket() {
    FPB = fopen(FPBFilename, "rb");
    while (fread(&paket, sizeof(paket), 1, FPB) == 1) {
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

}