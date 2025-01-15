#include <stdio.h>
#include <string.h>
#include <conio.h>

typedef enum {True = 1, False = 0} boolean;
typedef char string[255];
typedef struct {
    int id_diskon;
    string nama_diskon;
    int nilai_diskon;
    string deskripsi;
    int status;
}Discount;
Discount diskon;
FILE *DiscFile;
FILE *temp;
int i;

string DiscFilename;
string tempFilename;

int tempID;     // integer ID yang digunakan untuk repetition
boolean found;

void namaFile();            //untuk menentukan nama file yang akan digunakan
void CRUDDiskon();     //prosedur utama untuk CRUD
void CreateDiskon();         //prosedur create diskon
void ReadDiskon();           //prosedur read diskon
void UpdateDiskon();         //prosedur update diskon
void UpdateChoice();        //prosedur pemilihan update dalam prosedur update
void DeleteDiskon();         //prosedur delete diskon (mengubah status menjadi nonaktif)

void namaFile() {
    strcpy(DiscFilename, "Diskon.dat");
    strcpy(tempFilename, "temp.dat");
}

void CRUDDiskon() {
    namaFile();
    do {
        printf("\n");
        printf("1. Input Diskon\n");
        printf("2. Read Diskon\n");
        printf("3. Update Diskon\n");
        printf("4. Delete Diskon\n");
        printf("5. Keluar\n");
        printf("Masukkan Angka : "); scanf(" %d",&i);
        printf("\n");

        switch(i) {
            case 1: CreateDiskon(); break;
            case 2: ReadDiskon(); break;
            case 3: UpdateDiskon(); break;
            case 4: DeleteDiskon(); break;
            case 5: return;
            default: printf("Input gagal\n");
        }
    } while (i != 5);
    getch();
}

void CreateDiskon() {
    // DECLARATION
    char yesno;

    // ALGORITHM
    DiscFile = fopen(DiscFilename, "ab");
    do {
        printf("Masukkan Data\n");
        printf("ID diskon : "); scanf(" %d", &diskon.id_diskon);
        if (diskon.id_diskon == 0) {
            return;
        }
        printf("Nama diskon : "); scanf(" %[^\n]", &diskon.nama_diskon);
        printf("Nilai diskon (persen) : "); scanf(" %d", &diskon.nilai_diskon);
        printf("Deskripsi diskon : "); scanf(" %[^\n]", &diskon.deskripsi);
        diskon.status = 1;
        fwrite(&diskon, sizeof(diskon), 1, DiscFile);

        do {
            printf("\nApakah ingin menambah lagi [Y/N]: ");
            scanf(" %[^\n]", &yesno);
            if (yesno == 'Y' || yesno == 'y') {
                break;
            } else if (yesno == 'N' || yesno == 'n') {
                fclose(DiscFile);
                return;
            } else {
                printf("Input gagal\n");
            }
        } while (yesno != 'Y' || yesno != 'y');
    } while (yesno == 'Y' || yesno == 'y');
    fclose(DiscFile);
    printf("\n");
}

void ReadDiskon() {
    DiscFile = fopen(DiscFilename, "rb");
    while (fread(&diskon, sizeof(diskon), 1, DiscFile) == 1 && diskon.status == 1) {
        printf("ID Diskon : %d\n", diskon.id_diskon);
        printf("Nama Diskon : %s\n", diskon.nama_diskon);
        printf("Nilai Diskon (persen) : %d\n", diskon.nilai_diskon);
        printf("Deskripsi : %s\n", diskon.deskripsi);
        printf("\n");
    }
    fclose(DiscFile);
}

void UpdateDiskon() {
    DiscFile = fopen(DiscFilename, "rb");
    temp = fopen(tempFilename, "wb");
    printf("ID Diskon Bimbel Yang Dicari : ");
    scanf(" %d", &tempID);
    printf("\n");

    found = False;
    while (fread(&diskon, sizeof(diskon), 1, DiscFile) == 1) {
        if (tempID == diskon.id_diskon) {
            UpdateChoice();
            fwrite(&diskon, sizeof(diskon), 1, temp);
            found = True;
        } else {
            fwrite(&diskon, sizeof(diskon), 1, temp);
        }
    }
    if (found == False) {
        printf("Kode Diskon Bimbel %d tidak ditemukan\n\n", tempID);
        fclose(temp);
        fclose(DiscFile);
        return;
    }
    fclose(temp);
    fclose(DiscFile);

    DiscFile = fopen(DiscFilename, "wb");
    temp = fopen(tempFilename, "rb");
    while (fread(&diskon, sizeof(diskon), 1, temp) == 1) {
        fwrite(&diskon, sizeof(diskon), 1, DiscFile);
    }
    fclose(temp);
    fclose(DiscFile);
    printf("\n");
}

void UpdateChoice() {
    do {
        printf("\nData apa yang ingin diubah?\n");
        printf("1. ID\n");
        printf("2. Nama\n");
        printf("3. Nilai Diskon\n");
        printf("4. Deskripsi\n");
        printf("5. Keluar\n");
        printf("Masukkan Angka : ");
        scanf(" %d", &i);
        printf("\n");

        switch (i) {
            case 1: printf("Masukkan ID baru : ");
            scanf(" %d", &diskon.id_diskon);
            printf("ID berhasil diperbaharui\n");
            break;
            case 2: printf("Masukkan nama baru : ");
            scanf(" %[^\n]", &diskon.nama_diskon);
            printf("Nama berhasil diperbaharui\n");
            break;
            case 3: printf("Masukkan nilai baru (persen) : ");
            scanf(" %d", &diskon.nilai_diskon);
            printf("Nilai Diskon berhasil diperbaharui\n");
            break;
            case 4: printf("Masukkan deskripsi baru : ");
            scanf(" %[^\n]", &diskon.deskripsi);
            printf("Deskripsi berhasil diperbaharui\n");
            break;
            case 5: return;
            default: printf("Input gagal\n");
        }
    } while (i != 5);
}

void DeleteDiskon() {
    DiscFile = fopen(DiscFilename, "rb");
    temp = fopen(tempFilename, "wb");
    printf("Masukkan ID Diskon Bimbel yang ingin dihapus : ");
    scanf(" %d", &tempID);
    printf("\n");

    while (fread(&diskon, sizeof(diskon), 1, DiscFile) == 1) {
        if (tempID == diskon.id_diskon) {
            diskon.status = 0;
            fwrite(&diskon, sizeof(diskon), 1, temp);
            found = True;
            printf("Diskon Bimbel Berhasil dihapus\n\n");
        } else {
            fwrite(&diskon, sizeof(diskon), 1, temp);
        }
    }
    if (found == False) {
        printf("Kode Diskon Bimbel %d tidak ditemukan\n\n", tempID);
        fclose(temp);
        fclose(DiscFile);
        return;
    }
    fclose(temp);
    fclose(DiscFile);

    DiscFile = fopen(DiscFilename, "wb");
    temp = fopen(tempFilename, "rb");
    while (fread(&diskon, sizeof(diskon), 1, temp) == 1) {
        fwrite(&diskon, sizeof(diskon), 1, DiscFile);
    }
    fclose(temp);
    fclose(DiscFile);
    printf("\n");
}