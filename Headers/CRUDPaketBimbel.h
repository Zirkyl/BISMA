#include <stdio.h>
#include <string.h>

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
    
}

void CreatePaket() {

}