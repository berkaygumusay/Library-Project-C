#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <conio.h>
#include <math.h>

typedef struct Ogrenci { 
	char ogrID[9]; 
	char ad[30]; 
	char soyad[30]; 
	int puan; 
	struct Ogrenci *next; 
	struct Ogrenci *prev;
}ogrenci;
typedef struct Yazar { 
	int yazarID; 
	char yazarAd[30]; 
	char yazarSoyad[30]; 
	struct Yazar *next;
}yazar;
typedef struct KitapOrnek{ 
	char EtiketNo[20]; 
	char Durum[8]; 
	struct KitapOrnek *next;
}kitapOrnek;
typedef struct Kitap {
	char kitapAdi[30]; 
	char ISBN[13];
	int adet; 
	struct Kitap *next; 
	struct KitapOrnek *head;
}kitap;
typedef struct KitapYazar{ 
	char ISBN[13]; 
	int YazarID;
}kitapYazar;
typedef struct Tarih{ 
	unsigned int gun:5; 
	unsigned int ay:4; 
	unsigned int yil:12;
}Tarih;
typedef struct KitapOdunc{ 
	char EtiketNo[20]; 
	char ogrID[9]; 
	unsigned int islemTipi:1; 
	struct Tarih islemTarihi;
}kitapOdunc;

// FONKSÝYON PROTOTÝPLERÝ BAÞLANGIÇ

// ÖÐRENCÝ FONKSÝYONLARI BAÞLANGIÇ
void dosyaOkuOgrenci(ogrenci **ogrenci);
void yazdirOgrenci(ogrenci *ogrenci);//fptr2
void dosyayaYazOgrenci(char* ogrID,char* ad,char* soyad,int puan);
void silOgrenci(ogrenci **head_ref,char* ogrID);
void dosyadanSilOgrenci(char* ogrID);
void ekleOgrenci(ogrenci **head_ref,char* ogrID,char* ad,char* soyad,int puan);
void guncelleOgrenci(ogrenci** ogrenci,char* ogrID,char* ad,char* soyad,int puan);
void dosyaGuncelleOgrenci(char* ogrID,char* ad,char* soyad,int puan,ogrenci* head_ref);
void ogrenciGoruntule(ogrenci* head_ref,char* tmp,kitap* head_ref_kitap);
void ogrenciKitapGoruntule(ogrenci* ogr,kitap* head_ref);
void kitapOduncListele(ogrenci* head_ref);
ogrenci* ogrID2ogr(char* ogrID,ogrenci* head_ref);
void dosyaOkuKitapOdunc(kitapOdunc*** KOArray);
int ogrenciAra(char* ogrID,ogrenci* head_ref);
char* ogrAd2ogrID(char* ogrAd,ogrenci* head_ref);
void kitapOduncDosyayaYaz(kitapOdunc*** KOArray,int diziBoyutu,char* EtiketNo,char* ogrID,int islemTipi,int gun,int ay,int yil);
void teslimSureKontrol(char* ogrID,char* EtiketNo,kitapOdunc** KOArray,int diziBoyutu,ogrenci* head_ref);
void LLDosyayaYazOgrenci(ogrenci* head_ref);
void cezaliListele(ogrenci* head_ref);
// ÖÐRENCÝ FONKSÝYONLARI BÝTÝÞ

// YAZAR FONKSÝYONLARI BAÞLANGIÇ
void dosyaOkuYazar(yazar **yazar);
void ekleYazar(yazar **head_ref,int yazarID,char* yazarAd,char* yazarSoyad,int control);
void yazdirYazar(yazar *yazar);
void dosyayaEkleYazar(int yazarID,char* yazarAd,char* yazarSoyad);
void dosyadanSilYazar(char* yazarAd,yazar* head_ref);
int silYazar(yazar **head_ref,char* yazarAd,char* yazarSoyad);
yazar* yazarBul(char* yazarAd,yazar* head_ref);
void yazarGoruntule(char* yazarAd,yazar* head_ref,kitapYazar** KYArray,int N,kitap* head_ref_kitap);
void LLDosyayaYazYazar(yazar *head_ref);
void guncelleYazar(yazar** head_ref,int yazarID,char* ad,char* soyAd);
void kitapYazarSil(kitapYazar*** KYArray,int N,int yazarID);
int kitapYazarKontrol(kitapYazar** KYArray,int diziBoyutu,char* yazarAd,char* kitapAd,yazar* head_ref_yazar,kitap* head_ref_kitap);
// YAZAR FONKSÝYONLARI BÝTÝÞ

// KÝTAP FONKSÝYONLARI BAÞLANGIÇ
void dosyaOkuKitap(kitap **kitap);
void dosyadanEkleKitap(kitap** head_ref,char* kitapAdi,char* ISBN,int adet);
void yazdirKitap(kitap* kitap);
void LLkitapEkle(char* kitapAd,kitap **head_ref);
void LLDosyayaYazKitap(kitap* head_ref);
void kitapGuncelle(kitap** head_ref,char* kitapAdi,char* ISBN,kitapOdunc** KOArray,int diziboyutu,ogrenci* head_ref_ogr);
void LLKitapSil(kitap** head_ref,char* kitapAdi,kitapOdunc** KOArray,int diziboyutu,ogrenci* head_ref_ogr,int control);
void kitapGoruntule(kitap* head_ref,char* kitapAdi,kitapOdunc** KOArray,int KOArrayBoyut,ogrenci* head_ref_ogr,int control);
char* rafKontrol(kitapOdunc** KOArray,int diziBoyutu,char* EtiketNo,ogrenci* head_ref);
void raftakiGoruntule(kitap* head_ref,kitapOdunc** KOArray,int M,ogrenci* head_ref_ogrenci);
void dosyaOkuKitapYazar(kitapYazar*** KYArray);
void yazarKitapEslestir(kitapYazar*** KYArray,int diziBoyut,kitap* head_ref_kitap,yazar* head_ref_yazar,char* kitapAdi,char* yazarAdi);
void kitapYazariGuncelle(kitapYazar*** KYArray,int diziBoyutu,char* kitapAdi,char* yazarAdiEski,char* yazarAdiYeni,kitap* head_ref_kitap,yazar* head_ref_yazar);
void LLDosyayaYazKitapYazar(kitapYazar** KYArray,int diziBoyutu);
void gecTeslimListele(kitapOdunc** KOArray,int diziBoyutu,kitap* head_ref_kitap,ogrenci* head_ref_ogr);
char* ISBN2BOOKNAME(kitap* head_ref,char* ISBN);
void freeKOandKY(kitapOdunc*** KOArray,kitapYazar*** KYArray,int boyut1,int boyut2);
// KÝTAP FONKSÝYONLARI BÝTÝÞ

// FONKSÝYON PROTOTÝPLERÝ BÝTÝÞ
int main() {
	srand(time(NULL));
	int run = 1,menu;
	
//	Öðrenci Deðiþkenleri Baþlangýç
	ogrenci *ogrenciMain = NULL;
	char ogrIDMain[9],adMain[30],soyadMain[30];
	int puanMain;
	int control;
	ogrenci *tmp;
	char* secim = (char*)malloc(15*sizeof(char));
	int islemTipi;
	int gun,ay,yil;
//	Öðrenci Deðiþkenleri Bitiþ

//  Yazar Deðiþkenleri Baþlangýç
	yazar* yazarMain = NULL;
	int yazarIDMain; 
	char yazarAdMain[30];
	char yazarAdMainV2[30];
	char yazarSoyadMain[30];
	yazar* tmpYazar;
//  Yazar Deðiþkenleri Bitiþ

//  Kitap Deðiþkenleri Baþlangýç
	kitap* kitap = NULL;
	char kitapAdiMain[30];
	char ISBNMain[13];
	int adetMain; 
	char EtiketNoMain[20]; 
//  Kitap Deðiþkenleri Bitiþ

//  Function Pointers Baþlangýç
	void(*ogrenci_fncptr[])(ogrenci**,char*,char*,char*,int) = {ekleOgrenci,guncelleOgrenci};
	void(*ogrenci_fncptr2[])(ogrenci*) = {yazdirOgrenci,kitapOduncListele,LLDosyayaYazOgrenci,cezaliListele};
	void(*yazar_fncptr[])(yazar*) = {yazdirYazar,LLDosyayaYazYazar};
//  Function Pointers Bitiþ

// 	Dosyalarý Okuma Ýþlemleri Baþlangýç
	dosyaOkuOgrenci(&ogrenciMain);
	dosyaOkuYazar(&yazarMain);
	dosyaOkuKitap(&kitap);

	int M = satirOku("KitapOdunc.csv");
	kitapOdunc** KOArray = (kitapOdunc**)malloc(M*sizeof(kitapOdunc*));
	dosyaOkuKitapOdunc(&KOArray);
	
	int N = satirOku("KitapYazar.csv"),i;
	kitapYazar** KYArray = (kitapYazar**)malloc(N*sizeof(kitapYazar*));
	dosyaOkuKitapYazar(&KYArray);
	
// 	Dosyalarý Okuma Ýþlemleri Bitiþ

	while(run){
		printf("----------------------------------------------- ANA MENU -----------------------------------------\n");
		printf("\n  1- Ogrenci Islemleri \n  2- Kitap Islemleri \n  3- Yazar Islemleri \n  4- Cikis\n  Secim: ");
		scanf("%d",&menu);
		(*ogrenci_fncptr2[2])(ogrenciMain);
		(*yazar_fncptr[1])(yazarMain);
		LLDosyayaYazKitap(kitap);
		LLDosyayaYazKitapYazar(KYArray,N);
		switch(menu){
			case(1):{ // ÖÐRENCÝ MENÜSÜ
				system("cls");
				printf("-------------------------------------------- OGRENCI MENUSU --------------------------------------\n\n");
				printf("  1- Ogrenci Ekle, Sil, Guncelle\n  2- Ogrenci Bilgisi Goruntuleme\n  3- Kitap Teslim Etmemis Ogrencileri Listele\n  4- Cezali Ogrencileri Listele\n  5- Tum Ogrencileri Listele\n  6- Kitap Odunc Al/Teslim Et\n  7-Geri\n  Secim: ");
				scanf("%d",&menu);
				system("cls");
				switch(menu){
					case(1):{
						printf("----------------------------------------- EKLE / SIL / GUNCLLE -----------------------------------\n\n");
						printf("  1- Ekle\n  2- Sil\n  3- Guncelle\n  4- Geri\n  nSecim: ");
						scanf("%d",&menu);
						system("cls");
						switch(menu){
							case(1):{// ÖÐRENCÝ EKLEME
								printf("--------------------------------------------- OGRENCI EKLE ---------------------------------------\n\n");
								printf("  Eklemek Istediginiz Ogrencinin Bilgileri\n---------------------------------------\n");
								printf("  Ogrenci ID : ");
								scanf("%s",ogrIDMain);
								printf("  Ogrencinin Ismi : ");
								scanf("%s",adMain);
								printf("  Ogrencinin Soyismi : ");
								scanf("%s",soyadMain);
								puanMain = 100;
								system("cls");
								printf("  Ogrenci Listesinin Guncel Hali :\n");
								(*ogrenci_fncptr[0])(&ogrenciMain,ogrIDMain,adMain,soyadMain,puanMain);
								dosyayaYazOgrenci(ogrIDMain,adMain,soyadMain,puanMain);
								printf("---------------------------------------- GUNCEL OGRENCI TABLOSU ----------------------------------\n\n");
								(*ogrenci_fncptr2[0])(ogrenciMain);
								printf("--------------------------------------------------------------------------------------------------\n\n");
								printf("\n  Devam Etmek Icin Enter'a Basiniz...");getch();system("cls");
								break;
							}
							case(2):{// ÖÐRENCÝ SÝLME
								printf("-------------------------------------------- OGRENCI SILME ---------------------------------------\n\n");
								printf("  Silmek Istediginiz Ogrencinin IDsini Girin: ");
								scanf("%s",ogrIDMain);
								dosyadanSilOgrenci(ogrIDMain);
								silOgrenci(&ogrenciMain,ogrIDMain);
								printf("---------------------------------------- GUNCEL OGRENCI TABLOSU ----------------------------------\n\n");
								(*ogrenci_fncptr2[0])(ogrenciMain);
								printf("--------------------------------------------------------------------------------------------------\n\n");
								printf("\n  Devam Etmek Icin Enter'a Basiniz...");getch();system("cls");
								break;
							}
							case(3):{//  ÖÐRENCÝ GÜNCELLEME
								printf("------------------------------------------- OGRENCI GUNCELLE --------------------------------------\n\n");
								printf("  Guncellemek Istediginiz Ogrencinin IDsini Giriniz : ");
								scanf("%s",ogrIDMain);
								
								printf("  Yeni Ogrenci Isim : ");
								scanf("%s",adMain);
								printf("  Yeni Ogrenci Soyisim: ");
								scanf("%s",soyadMain);
								printf("  Yeni Ogrenci Puan: ");
								scanf("%d",&puanMain);
								(*ogrenci_fncptr[1])(&ogrenciMain,ogrIDMain,adMain,soyadMain,puanMain);
								dosyaGuncelleOgrenci(ogrIDMain,adMain,soyadMain,puanMain,ogrenciMain);
								system("cls");
								printf("---------------------------------------- GUNCEL OGRENCI TABLOSU ----------------------------------\n\n");
								(*ogrenci_fncptr2[0])(ogrenciMain);
								printf("--------------------------------------------------------------------------------------------------\n\n");
								printf("\n  Devam Etmek Icin Enter'a Basiniz...");getch();system("cls");
								break;
							}
							
						}
						break;
					}
					case(2):{// ÖÐRENCÝ GÖRÜNTÜLEME
						printf("------------------------------------------ OGRENCI GORUNTULE -------------------------------------\n\n");
						printf("  Goruntulemek Istediginiz Ogrencinin IDsini veya Ismini Giriniz : ");scanf("%s",ogrIDMain);
						system("cls");
						printf("------------------------------------------ OGRENCI GORUNTULE -------------------------------------\n\n");
						ogrenciGoruntule(ogrenciMain,ogrIDMain,kitap);

						system("cls");
						break;
					}
					case(3):{// KÝTAP TESLÝM ETMEYEN ÖÐRENCÝLER
						printf("----------------------------------- KITAP TESLIM ETMEMIS OGRENCILER ------------------------------\n\n");
						(*ogrenci_fncptr2[1])(ogrenciMain);
						printf("--------------------------------------------------------------------------------------------------\n\n");
						printf("  Devam Etmek Icin Enter'a Basiniz...");
						getch();
						system("cls");
						break;
					}
					case(4):{// CEZALI ÖÐRENCÝLER
						printf("------------------------------------------ CEZALI OGRENCILER -------------------------------------\n\n");
						(*ogrenci_fncptr2[3])(ogrenciMain);
						printf("--------------------------------------------------------------------------------------------------\n\n");
						printf("  Devam Etmek Icin Enter'a Basiniz...");getch();system("cls");
						break;
					}
					case(5):{// TÜM ÖÐRENCÝLER
						printf("-------------------------------------------- TUM OGRENCILER ---------------------------------------\n\n");
						(*ogrenci_fncptr2[0])(ogrenciMain);
						printf("--------------------------------------------------------------------------------------------------\n\n");
						printf("  Devam Etmek Icin Enter'a Basiniz...");getch();system("cls");
						break;
					}
					case(6):{// KÝTAP ÖDÜNC ALMA/TESLÝM ETME
						fflush(stdin);
						printf("------------------------------------- KITAP ODUNC ALMA/TESLIM ETME --------------------------------\n\n");
						printf("  Ogrenci Numaranizi Giriniz : ");scanf("%s",ogrIDMain);
						if(ogrenciAra(ogrIDMain,ogrenciMain) == 0){
							printf("\n\n  !! Sistemde Boyle Bir Ogrenci Bulunmamaktadir !!\n");
							printf("  Devam Etmek Icin Enter'a Basiniz...");
							getch();
							system("cls");
						}
						else{
							printf("\n  1- Kitap Teslim Etme\n  2- Kitap Odunc Alma\n  Secim: ");scanf("%d",&menu);
							if(menu == 1){
								strcpy(secim,"Teslim Etmek");
								islemTipi = 1;
							}	
							else if(menu == 2){
								strcpy(secim,"Odunc Almak");
								islemTipi = 0;
							}
							printf("  %s Istediginiz Kitabin Ismini Giriniz :",secim);fflush(stdin);scanf("%[^\n]",kitapAdiMain);
							
							if(menu == 1){
								kitapGoruntule(kitap,kitapAdiMain,KOArray,M,ogrenciMain,2);
								printf("\n  %s Istediginiz Kitabin Etiket Numarasini Giriniz : ",secim);scanf("%s",EtiketNoMain);
								strcpy(adMain,rafKontrol(KOArray,M,EtiketNoMain,ogrenciMain));
								if((strcmp(rafKontrol(KOArray,M,EtiketNoMain,ogrenciMain),"Rafta") != 0) && (strcmp(ogrAd2ogrID(adMain,ogrenciMain),ogrIDMain) == 0)){
									printf("  Teslim Tarihi (GG.AA.YYYY) : ");scanf("%d.%d.%d",&gun,&ay,&yil);
									M++;
									KOArray = (kitapOdunc**)realloc(KOArray,M*sizeof(kitapOdunc*));
									kitapOduncDosyayaYaz(&KOArray,M,EtiketNoMain,ogrIDMain,islemTipi,gun,ay,yil);
									printf("  !! Kitap Teslim Islemi Basariyla Gerceklesti !!\n\n");
									teslimSureKontrol(ogrIDMain,EtiketNoMain,KOArray,M,ogrenciMain);
								}
								else{
									printf("\n!! Bu Kitabi Teslim Edemezsiniz !!\n");
								}
							}
							else if(menu == 2){
								kitapGoruntule(kitap,kitapAdiMain,KOArray,M,ogrenciMain,2);
								printf("\n  %s Istediginiz Kitabin Etiket Numarasini Giriniz : ",secim);scanf("%s",EtiketNoMain);
								if(ogrID2ogr(ogrIDMain,ogrenciMain)->puan < 0){
									printf("  !! Kitap Verilemez !!\n");
									printf("  Devam Etmek Icin Enter'a Basiniz...");
									getch();
									system("cls");
								}
								else{
									if(strcmp(rafKontrol(KOArray,M,EtiketNoMain,ogrenciMain),"Rafta") == 0){
										printf("  Teslim Tarihi (GG.AA.YYYY) : ");scanf("%d.%d.%d",&gun,&ay,&yil);
										M++;
										KOArray = (kitapOdunc**)realloc(KOArray,M*sizeof(kitapOdunc*));
										kitapOduncDosyayaYaz(&KOArray,M,EtiketNoMain,ogrIDMain,islemTipi,gun,ay,yil);
										printf("\n  !! Kitap Odunc Alma Islemi Basariyla Gerceklesti !!\n");
									}
									else{
										printf("\n  !! Bu Kitap Baska Bir Ogrencide !!\n");
									}	
								}
							}
							printf("  Devam Etmek Icin Enter'a Basiniz...");
							getch();
							system("cls");
						}
						
						break;
					}
					case(7):{// GERÝ
						break;
					}
				}
				break;
			}
			case(2):{// KÝTAP MENÜSÜ
				system("cls");
				printf("--------------------------------------------- KITAP MENUSU ---------------------------------------\n\n");
				printf("  1- Kitap Ekle, Sil, Guncelle\n  2- Kitap Bilgisi Goruntuleme\n  3- Raftaki Kitaplari Listele\n  4- Zamaninda Teslim Edilmeyen Kitaplari Listele\n  5- Kitap-Yazar Eslestir\n  6- Kitabin Yazarini Guncelle\n  7- Geri\n  Secim: ");scanf("%d",&menu);
				system("cls");
				switch(menu){
					case(1):{
						printf("----------------------------------------- EKLE / SIL / GUNCLLE -----------------------------------\n\n");
						printf("  1- Kitap Ekle\n  2- Sil\n  3- Guncelle\n  4- Geri\n  Secim: ");scanf("%d",&menu);
						system("cls");
						switch(menu){
							case(1):{// KÝTAPO EKLE
								fflush(stdin);
								printf("------------------------------------------- KITABIN BILGILERI -------------------------------------\n\n");
								printf("  Kitabin Adi : ");
								scanf("%[^\n]",kitapAdiMain);
								LLkitapEkle(kitapAdiMain,&kitap);
								printf("  Kitap Basariyla Eklendi !!\n");
								printf("  Devam Etmek Icin Enter'a Basiniz...");
								getch();
								system("cls");
								break;
							}
							case(2):{// KÝTAP SÝL
								fflush(stdin);
								printf("------------------------------------------- KITABIN BILGILERI -------------------------------------\n\n");
								printf("  Silmek Istediginiz Kitabýn Adi : ");
								scanf("%[^\n]",kitapAdiMain);
								LLKitapSil(&kitap,kitapAdiMain,KOArray,M,ogrenciMain,1);
								printf("  Devam Etmek Icin Enter'a Basiniz...");
								getch();
								system("cls");
								break;
							}
							case(3):{// KÝTAP GÜNCELLE
								printf("------------------------------------------- KITABIN BILGILERI -------------------------------------\n\n");
								printf("  Guncellemek Istediginiz Kitabin ISBN No'sunu Giriniz : ");scanf("%s",ISBNMain);fflush(stdin);
								printf("  Kitabin Yeni Ismini Giriniz : ");scanf("%[^\n]",kitapAdiMain);
								kitapGuncelle(&kitap,kitapAdiMain,ISBNMain,KOArray,M,ogrenciMain);
								printf("\n  Devam Etmek Icin Enter'a Basiniz...");
								getch();
								system("cls");
								break;
							}
							case(4):{// GERÝ
								break;
							}
						}
						break;
					}
					case(2):{// KÝTAP GÖRÜNTÜLE
						printf("------------------------------------------- KITABIN BILGILERI -------------------------------------\n\n");
						fflush(stdin);
						printf("  Goruntulemek Istediginiz Kitabýn Adi : ");
						scanf("%[^\n]",kitapAdiMain);
						kitapGoruntule(kitap,kitapAdiMain,KOArray,M,ogrenciMain,1);
						printf("\n  Devam Etmek Icin Enter'a Basiniz...");
						getch();
						system("cls");
						break;
					}
					case(3):{// RAFTAKÝ KÝTAPLARI GÖRÜNTÜLE
						raftakiGoruntule(kitap,KOArray,M,ogrenciMain);
						printf("  Devam Etmek Icin Enter'a Basiniz...");
						getch();
						system("cls");
						break;
					}
					case(4):{// ZAMANINDA TESLÝM EDÝLMEYEN KÝTAPLAR
						printf("---------------------------------- ZAMANINDA TESLIM EDILMEYEN KITAPLAR ----------------------------\n\n");
						gecTeslimListele(KOArray,M,kitap,ogrenciMain);
						printf("---------------------------------------------------------------------------------------------------\n\n");
						printf("  Devam Etmek Icin Enter'a Basiniz...");
						getch();
						system("cls");
						break;
					}
					case(5):{// KÝTAP-YAZAR EÞLEÞTÝRME
						printf("---------------------------------------- KITAP/YAZAR ESLESTIRME -----------------------------------\n\n");
						printf("  Eslestirmek Istediginiz Yazarin Ismi : ");
						scanf("%s",yazarAdMain);
						if(yazarKontrol(yazarMain,-1,yazarAdMain) == 1){
							fflush(stdin);
							printf("  Eslestirmek Istediginiz Kitabin Ismi : ");
							scanf("%[^\n]",kitapAdiMain);
							if(kitapKontrol(kitap,kitapAdiMain) == 1){
								printf("---------------------------------------------------------------------------------------------------\n\n");
								N++;
								KYArray = (kitapYazar**)realloc(KYArray,N*sizeof(kitapYazar*));
								printf("  %s - %s",yazarAdMain,kitapAdiMain);
								yazarKitapEslestir(&KYArray,N,kitap,yazarMain,kitapAdiMain,yazarAdMain);
								printf("  Eslestirme Islemi Basarili !!\n");
								printf("  %s - %d\n",KYArray[N-1]->ISBN,KYArray[N-1]->YazarID);
							}
							else{
								printf("\n  !! Sistemde Boyle Bir Kitap Bulunmamaktadir !!\n\n");
							}
						}
						else{
							printf("\n  !! Sistemde Boyle Bir Yazar Bulunmamaktadir !!\n");
						}
						
						printf("  Devam Etmek Icin Enter'a Basiniz...");
						getch();
						system("cls");
						break;
					}
					case(6):{// KÝTAP-YAZAR GÜNCELLEME
						fflush(stdin);
						printf("---------------------------------------- KITAP/YAZAR GUNCELLEME -----------------------------------\n\n");
						printf("  Yazarini Degistirmek Istediginiz Kitabin Ismi : ");
						scanf("%[^\n]",kitapAdiMain);
						if(kitapKontrol(kitap,kitapAdiMain) == 1){
							printf("  Eski Yazarin Ismi : ");
							scanf("%s",yazarAdMain);
							printf("  Yeni Yazarin Ismi : ");
							scanf("%s",yazarAdMainV2);
							printf("---------------------------------------------------------------------------------------------------\n\n");
							if((yazarKontrol(yazarMain,-1,yazarAdMain) == 1) && (yazarKontrol(yazarMain,-1,yazarAdMainV2) == 1)){
								if(kitapYazarKontrol(KYArray,N,yazarAdMain,kitapAdiMain,yazarMain,kitap) == 1){
									kitapYazariGuncelle(&KYArray,N,kitapAdiMain,yazarAdMain,yazarAdMainV2,kitap,yazarMain);
									printf("\n\n  !! Guncelleme Islemi Basariyla Yapildi !!\n\n");
								}
								else{
									printf("\n\n  !! Bu Kitabin Boyle Bir Yazari Bulunmamaktadir !!\n\n");
								}
							}
							else{
								printf("\n\n  !! Yazar Isimlerini Yanlis Girdiniz !!\n\n");
							}
						}
						else{
							printf("\n\n  !! Sistemde Boyle Bir Kitap Bulunmamaktadir !!\n\n");
						}
						printf("  Devam Etmek Icin Enter'a Basiniz...");
						getch();
						system("cls");
						break;
					}
					case(7):{// ÇIKIÞ
						break;
					}
				
				}
				
				break;
			}
			case(3):{ // YAZAR MENÜSÜ
				system("cls");
				printf("--------------------------------------------- YAZAR MENUSU ---------------------------------------\n\n");
				printf("  1- Yazar Ekle, Sil, Guncelle\n  2- Yazar Bilgisi Goruntuleme\n  3- Yazarlarin Listesi\n  4- Geri\n  Secim: ");
				scanf("%d",&menu);
				system("cls");
				switch(menu){
					
					case(1):{
						printf("----------------------------------------- EKLE / SIL / GUNCLLE -----------------------------------\n\n");
						printf("  1- Ekle\n  2- Sil\n  3- Guncelle\n  4- Geri\n  Secim: ");
						scanf("%d",&menu);
						switch(menu){
							case(1):{// YAZAR EKLEME
								system("cls");
								printf("--------------------------------------------- YAZAR EKLEME ---------------------------------------\n\n");
								printf("  Eklemek Istediginiz Yazarin Bilgileri\n---------------------------------------\n");
								printf("  Yazar ID : ");
								scanf("%d",&yazarIDMain);
								printf("  Yazarin Ismi : ");
								scanf("%s",yazarAdMain);
								printf("  Yazarin Soyismi : ");
								scanf("%s",yazarSoyadMain);
								system("cls");
								ekleYazar(&yazarMain,yazarIDMain,yazarAdMain,yazarSoyadMain,1);
								printf("----------------------------------------- GUNCEL YAZAR LISTESI -----------------------------------\n\n");
								(*yazar_fncptr[0])(yazarMain);
								printf("--------------------------------------------------------------------------------------------------\n\n");
								printf("  Devam Etmek Icin Enter'a Basiniz...");
								getch();
								system("cls");
								break;
							}
							case(2):{// YAZAR SÝLME
								system("cls");
								printf("--------------------------------------------- YAZAR SILME --------------------------------------\n\n");
								printf("  Silmek Istediginiz Yazarin Adini Giriniz : ");
								scanf("%s",yazarAdMain);
								printf("  Silmek Istediginiz Yazarin Soyadini Giriniz : ");
								scanf("%s",yazarSoyadMain);
								tmpYazar = yazarBul(yazarAdMain,yazarMain);
								if(silYazar(&yazarMain,yazarAdMain,yazarSoyadMain) == 1){
									kitapYazarSil(&KYArray,N,tmpYazar->yazarID);
								}
								printf("----------------------------------------- GUNCEL YAZAR LISTESI -----------------------------------\n\n");
								(*yazar_fncptr[0])(yazarMain);
								printf("--------------------------------------------------------------------------------------------------\n\n");
								printf("  Devam Etmek Icin Enter'a Basiniz...");
								getch();
								system("cls");
								break;
							}
							case(3):{// YAZAR GÜNCELLEME
								system("cls");
								printf("------------------------------------------- YAZAR GUNCELLEME -------------------------------------\n\n");
								printf("  Guncellemek Istediginiz Yazarin IDsini Giriniz : ");scanf("%d",&yazarIDMain);
								if(yazarKontrol(yazarMain,yazarIDMain,"") == 1){
									printf("  Yeni Yazar Ismi : ");scanf("%s",yazarAdMain);
									printf("  Yeni Yazar Soyismi : ");scanf("%s",yazarSoyadMain);
									guncelleYazar(&yazarMain,yazarIDMain,yazarAdMain,yazarSoyadMain);
									
								}
								system("cls");
								printf("----------------------------------------- GUNCEL YAZAR LISTESI -----------------------------------\n\n");
								(*yazar_fncptr[0])(yazarMain);
								printf("--------------------------------------------------------------------------------------------------\n\n");
								printf("  Devam Etmek Icin Enter'a Basiniz...");
								getch();
								system("cls");
								break;
							}				
						}
						break;
					}
					case(2):{// YAZAR GÖRÜNTÜLEME
						printf("------------------------------------------- YAZAR GORUNTULEME -------------------------------------\n\n");
						printf("  Goruntulemek Istediginiz Yazarýn Adini Giriniz : ");scanf("%s",yazarAdMain);
						yazarGoruntule(yazarAdMain,yazarMain,KYArray,N,kitap);
						printf("\n--------------------------------------------------------------------------------------------------\n\n");
						printf("  Devam Etmek Icin Enter'a Basiniz...");
						getch();
						system("cls");
						break;
					}
					case(3):{// YAZAR LÝSTESÝNÝ GÖRÜNTÜLEME
						printf("----------------------------------------- GUNCEL YAZAR LISTESI -----------------------------------\n\n");
						(*yazar_fncptr[0])(yazarMain);
						printf("--------------------------------------------------------------------------------------------------\n\n");
						printf("\n  Devam Etmek Icin Enter'a Basiniz...");
						getch();
						system("cls");
						break;
					}
					case(4):{// ÇIKIÞ
						break;
					}
				}
				break;
			}
			case(4):{ // CIKIS
				system("cls");
				printf("Cikis Yapildi ! Enter'a Basiniz...");
				run=0;
				break;
			}
		}
		system("cls");
		(*ogrenci_fncptr2[2])(ogrenciMain);
		(*yazar_fncptr[1])(yazarMain);
		LLDosyayaYazKitap(kitap);
		LLDosyayaYazKitapYazar(KYArray,N);
	}
	
	for(i=0;i<M;i++){
		free(KOArray[i]);
	}
	free(KYArray);
	for(i=0;i<N;i++){
		free(KYArray[i]);
	}
	free(KYArray);*/
	return 0;
}

int satirOku(char* fileName){
	char x;
	int satirsayisi=1;
	FILE *file;
	file = fopen(fileName, "r");	
	if(!file){
		printf("\nDosya acilamadi.");
		return 0;
	}
	for( x = getc(file); x!= EOF; x = getc(file))
		if ( x == '\n')
			satirsayisi++;
	
	fclose(file);
	return satirsayisi;
}

void dosyaOkuOgrenci(ogrenci **ogrenci){
	int column = 0;
	char line[1000];
	char ogrID[8]; 
	char ad[30]; 
	char soyad[30];
	int puan;
	FILE* fOgr;
	fOgr = fopen("Ogrenciler.csv","r");
	while(fgets(line,sizeof(line),fOgr)){
		column = 0;
		char *value = strtok(line,",");
		while(value){
			if(column == 0){
				strcpy(ogrID,value);
			}
			else if(column == 1){
				strcpy(ad,value);
			}
			else if(column == 2){
				strcpy(soyad,value);
			}
			else if(column == 3){
				puan = atoi(value);
			}
			
			value = strtok(NULL,",");
			column++;
		}
		ekleOgrenci(ogrenci,ogrID,ad,soyad,puan);
	}
	fclose(fOgr);
}
void dosyayaYazOgrenci(char* ogrID,char* ad,char* soyad,int puan){
	FILE* fOgr = fopen("Ogrenciler.csv","a+");
	fprintf(fOgr,"\n%s,%s,%s,%d",ogrID,ad,soyad,puan);
	fclose(fOgr);
}
void ekleOgrenci(ogrenci **head_ref,char* ogrID,char* ad,char* soyad,int puan){
	ogrenci* yeniOgrenci = (ogrenci*) malloc(sizeof(ogrenci));
	ogrenci *son = *head_ref;
	strcpy(yeniOgrenci->ogrID,ogrID);
	strcpy(yeniOgrenci->ad,ad);
	strcpy(yeniOgrenci->soyad,soyad);
	yeniOgrenci->puan = puan;
	yeniOgrenci->next = NULL;
	
	if((*head_ref) == NULL){
		yeniOgrenci->prev = NULL;
		*head_ref = yeniOgrenci;
		return;
	}
	while(son->next != NULL){
		if(strcmp(ogrID,son->ogrID) == 0){
			system("cls");
			printf("!!! Bu Ogrenci Zaten Mevcut !!!\n");
			printf("Devam Etmek Icin Enter'a Basiniz...\n");
			getch();
			return;
		}
		if((strcmp(ogrID,son->ogrID) >= 0) && (strcmp(ogrID,son->next->ogrID) < 0) ){
			yeniOgrenci->next = son->next;
			yeniOgrenci->prev = son;
			son->next->next->prev = yeniOgrenci;
			son->next = yeniOgrenci;
			
			return;
		}
		son= son->next;
	}
	if(strcmp(ogrID,son->ogrID) == 0){
		system("cls");
		printf("!!! Bu Ogrenci Zaten Mevcut !!!\n");
		printf("Devam Etmek Icin Enter'a Basiniz...\n");
		getch();
		return;
	}
	yeniOgrenci->prev = son;
	son->next = yeniOgrenci;
}
void yazdirOgrenci(ogrenci *ogrenci){
	int i = 1;
	while(ogrenci != NULL){
		printf("  %d-) %s , %s , %s , %d\n",i,ogrenci->ogrID,ogrenci->ad,ogrenci->soyad,ogrenci->puan);
		i++;
		ogrenci = ogrenci->next;
	}
}
void silOgrenci(ogrenci **head_ref,char* ogrID){
	ogrenci *son = *head_ref;
	if(strcmp(son->ogrID,ogrID) == 0){
		*head_ref = (*head_ref)->next;
		printf("  !! Ogrenci Basariyla Silindi !!\n");
		sleep(2);
		return;	
	}
	while(son->next != NULL){
		if(strcmp(son->ogrID,ogrID) == 0){
			son->next->prev = son->prev;
			son->prev->next = son->next;
			printf("  !! Ogrenci Basariyla Silindi !!\n");
			sleep(2);
			return;	
		}
		son = son->next;
	}
	if(strcmp(son->ogrID,ogrID) == 0){
		son->prev->next = NULL;
		printf("!! Ogrenci Basariyla Silindi !!\n");
		sleep(2);
		return;	
	}
	printf("  !!! Boyle Bir Ogrenci Sistemde Bulunmamaktadýr !!!");
	
}
void dosyadanSilOgrenci(char* ogrID){
	int durum = 0;
	char line[100];
	char *buffer,*ptr;
	buffer = (char*)malloc(500*sizeof(char));
	memset(buffer,0,500*sizeof(char));
	ptr=buffer;
	FILE *fOgr;
	fOgr = fopen("Ogrenciler.csv","r");
	while(!feof(fOgr) && durum == 0){
		fgets(line,100,fOgr);
		if(strstr(line,ogrID) != NULL){
			durum = 1;
		}
		else{
			durum = 0;
		}
	}
	if(durum == 0){
		printf("Bu ID ye Sahip Bir Ogrenci Sistemde Bulunmamaktadýr\n");
		printf("Devam Etmek Icin Enter'a Basiniz...");
		getch();
		fclose(fOgr);
		return;
	}
	fclose(fOgr);
	fOgr = fopen("Ogrenciler.csv","r");
	while(!feof(fOgr)){
		fgets(line,100,fOgr);
		if((strstr(line,ogrID) == NULL)){
			strcpy(ptr,line);
			ptr += strlen(line);
		}

	}
	fclose(fOgr);
	sleep(1);
	fOgr = fopen("Ogrenciler.csv","w");
	fprintf(fOgr,"%s",buffer);
	fclose(fOgr);	
	free(buffer);
}
void guncelleOgrenci(ogrenci** head_ref,char* ogrID,char* ad,char* soyad,int puan){
	ogrenci *son = *head_ref;
	if(strcmp(son->ogrID,ogrID) == 0){
		strcpy(son->ad,ad);
		strcpy(son->soyad,soyad);
		son->puan = puan;
		return;
	}
	while(son->next != NULL){
		if(strcmp(son->ogrID,ogrID) == 0){
			strcpy(son->ad,ad);
			strcpy(son->soyad,soyad);
			son->puan = puan;
			return;
		}
		son = son->next;
	}
	if(strcmp(son->ogrID,ogrID) == 0){
		strcpy(son->ad,ad);
		strcpy(son->soyad,soyad);
		son->puan = puan;
		return;
	}
	printf("!!! Bu Bilgilere Sahip Bir Ogrenci Sistemde Bulunmamaktadýr !!!\n");
	printf("Devam Etmek Icin Enter'a Basiniz...");
	getch();
	return;
	
}
void dosyaGuncelleOgrenci(char* ogrID,char* ad,char* soyad,int puan,ogrenci* head_ref){
	int durum = 0;
	char line[100];
	char *buffer,*ptr;
	ogrenci* tmpOgr;
	buffer = (char*)malloc(500*sizeof(char));
	memset(buffer,0,500*sizeof(char));
	ptr=buffer;
	FILE *fOgr;
	fOgr = fopen("Ogrenciler.csv","r");
	while(!feof(fOgr) && durum == 0){
		fgets(line,100,fOgr);
		if(strstr(line,ogrID) != NULL){
			durum = 1;
		}
		else{
			durum = 0;
		}
	}
	if(durum == 0){
		printf("Bu ID ye Sahip Bir Ogrenci Sistemde Bulunmamaktadýr\n");
		printf("Devam Etmek Icin Enter'a Basiniz...");
		getch();
		fclose(fOgr);
		return;
	}
	fclose(fOgr);
	fOgr = fopen("Ogrenciler.csv","r");
	while(!feof(fOgr)){
		fgets(line,100,fOgr);
		if((strstr(line,ogrID) == NULL)){
			strcpy(ptr,line);
			ptr += strlen(line);
		}
	}
	fclose(fOgr);
//	printf("\nnBUFFER\n%s\nBUFFER\n",buffer);
	fOgr = fopen("Ogrenciler.csv","w");
	tmpOgr = ogrID2ogr(ogrID,head_ref);
	if(tmpOgr->next == NULL){
		fprintf(fOgr,"%s%s,%s,%s,%d",buffer,ogrID,ad,soyad,puan);
	}
	else{
		fprintf(fOgr,"%s\n%s,%s,%s,%d",buffer,ogrID,ad,soyad,puan);
	}
	fclose(fOgr);
	free(buffer);
}
void ogrenciGoruntule(ogrenci* head_ref,char* tmp,kitap* head_ref_kitap){
	ogrenci *son = head_ref;
	if((strcmp(son->ogrID,tmp) == 0) || (strcmp(son->ad,tmp) == 0)){
		printf("  Ogrencinin Ismi : %s\n  Ogrencinin Soyismi : %s\n  Ogrencinin Puani : %d\n\n",son->ad,son->soyad,son->puan);
		printf("--------------------------------------------------------------------------------------------------\n\n");
		ogrenciKitapGoruntule(son,head_ref_kitap);
		printf("--------------------------------------------------------------------------------------------------\n\n");
		printf("  Devam Etmek Icin Enter'a Basiniz...");
		getch();
		return;
	}
	while(son->next != NULL){
		if((strcmp(son->ogrID,tmp) == 0) || (strcmp(son->ad,tmp) == 0)){
			printf("  Ogrencinin Ismi : %s\n  Ogrencinin Soyismi : %s\n  Ogrencinin Puani : %d\n\n",son->ad,son->soyad,son->puan);
			printf("--------------------------------------------------------------------------------------------------\n\n");
			ogrenciKitapGoruntule(son,head_ref_kitap);
			printf("--------------------------------------------------------------------------------------------------\n\n");
			printf("  Devam Etmek Icin Enter'a Basiniz...");
			
			getch();
			return;
		}
		son = son->next;
	}
	if((strcmp(son->ogrID,tmp) == 0) || (strcmp(son->ad,tmp) == 0)){
		printf("Ogrencinin Ismi : %s\n  Ogrencinin Soyismi : %s\n  Ogrencinin Puani : %d\n\n",son->ad,son->soyad,son->puan);
		printf("--------------------------------------------------------------------------------------------------\n\n");
		ogrenciKitapGoruntule(son,head_ref_kitap);
		printf("--------------------------------------------------------------------------------------------------\n\n");
		printf("  Devam Etmek Icin Enter'a Basiniz...");
		getch();
		return;
	}
	printf("  !!! Boyle Bir Ogrenci Sistemde Bulunmamaktadi9r !!!\n");
	printf("--------------------------------------------------------------------------------------------------\n\n");
	printf("  Devam Etmek Icin Enter'a Basiniz...");
	getch();
	return;
}
void ogrenciKitapGoruntule(ogrenci* ogr,kitap* head_ref){
	printf("  %s Adli Ogrencinin Kitap Hareketleri :\n\n",ogr->ad);
	FILE* fKitapOdunc = fopen("KitapOdunc.csv","r");
	int run=0;
	char line[1000],EtiketNo[20],ogrID[9];
	int ay,gun,yil;
	int teslimINT;
	int i;
	
	char* teslim = (char*)malloc(20*sizeof(char));
	char* bookName = (char*)malloc(30*sizeof(char));
	while(fgets(line,sizeof(line),fKitapOdunc) != NULL){
		sscanf(line,"%[^/,],%[^/,],%d,%d.%d.%d",&EtiketNo,&ogrID,&teslimINT,&gun,&ay,&yil);
		if(strcmp(ogr->ogrID,ogrID) == 0){
			run =1;
			if(teslimINT == 1){
				strcpy(teslim,"Teslim Etti");
			}
			else if(teslimINT == 0){
				strcpy(teslim,"Odunc Aldi");
			}
			char* ISBN = (char*)calloc(13,sizeof(char));
			strncat(ISBN,EtiketNo,13);
			bookName = ISBN2BOOKNAME(head_ref,ISBN);
			printf("  - %s Isimli Kitabi %d.%d.%d Tarihinde %s\n",bookName,gun,ay,yil,teslim);
			free(ISBN);
		}
		
	}
	printf("\n");
	if(run == 0){
		printf("!! Bu Ogrencinin Herhangi Kitap Hareketi Bulunmamaktadir !!\n\n");
	}
}
void kitapOduncListele(ogrenci* head_ref){
	ogrenci* tmp;
	FILE* fKitapOdunc = fopen("KitapOdunc.csv","r");
	FILE* fKitapOdunc2;
	char line1[100],line2[100];
	char EtiketNo1[30],EtiketNo2[30],ogrID1[9],ogrID2[9];
	int gun,ay,yil;
	int teslimINT1,teslimINT2;
	int flag=1;
	while(fgets(line1,sizeof(line1),fKitapOdunc) != NULL){
		sscanf(line1,"%[^/,],%[^/,],%d,%d.%d.%d",&EtiketNo1,&ogrID1,&teslimINT1,&gun,&ay,&yil);
		flag = 1;
		fKitapOdunc2 = fopen("KitapOdunc.csv","r");
		if(teslimINT1 == 0){
			while((fgets(line2,sizeof(line2),fKitapOdunc2) != NULL) && (flag == 1)){
				sscanf(line2,"%[^/,],%[^/,],%d,%d.%d.%d",&EtiketNo2,&ogrID2,&teslimINT2,&gun,&ay,&yil);
				if((strcmp(EtiketNo1,EtiketNo2) == 0) && (strcmp(ogrID1,ogrID2) == 0) && (teslimINT2 == 1)){
					flag = 0;
				}
			}
			if(flag == 1){
				tmp = ogrID2ogr(ogrID1,head_ref);
				printf("- %s (%s)\n",tmp->ad,tmp->ogrID);
			}
		}
		fclose(fKitapOdunc2);
		
	}
	fclose(fKitapOdunc);
}
void dosyaOkuKitapOdunc(kitapOdunc*** KOArray){
	FILE* fKitapOdunc = fopen("KitapOdunc.csv","r");
	char line[100];
	char EtiketNo[20],ogrID[9];
	int gun,ay,yil;
	int teslimINT;
	int i = 0;
	
	while(fgets(line,sizeof(line),fKitapOdunc) != NULL){
		sscanf(line,"%[^/,],%[^/,],%d,%d.%d.%d",&EtiketNo,&ogrID,&teslimINT,&gun,&ay,&yil);
		kitapOdunc* tmp = (kitapOdunc*)malloc(sizeof(kitapOdunc));
		strcpy(tmp->EtiketNo,EtiketNo);
		strcpy(tmp->ogrID,ogrID);
		tmp->islemTipi= teslimINT;
		tmp->islemTarihi.gun = gun;
		tmp->islemTarihi.ay = ay;
		tmp->islemTarihi.yil = yil;
		(*KOArray)[i] = tmp;
		
		i++;
	}
	fclose(fKitapOdunc);
}	
ogrenci* ogrID2ogr(char* ogrID,ogrenci* head_ref){
	ogrenci* sonOgrenci = head_ref;
	while(sonOgrenci != NULL){
		if(strcmp(sonOgrenci->ogrID,ogrID) == 0){
			return sonOgrenci;
		}
		sonOgrenci = sonOgrenci->next;
	}
}
int ogrenciAra(char* ogrID,ogrenci* head_ref){
	ogrenci* sonOgrenci = head_ref;
	while(sonOgrenci != NULL){
		if(strcmp(sonOgrenci->ogrID,ogrID) == 0){
			return 1;
		}
		sonOgrenci = sonOgrenci->next;
	}
	return 0;
}
char* ogrAd2ogrID(char* ogrAd,ogrenci* head_ref){
	ogrenci* sonOgrenci = head_ref;
	char* ogrIsim;
	while(sonOgrenci != NULL){
		ogrIsim = (char*)malloc(40*sizeof(char));
		strcpy(ogrIsim,sonOgrenci->ad);
		strcat(ogrIsim," ");
		strcat(ogrIsim,sonOgrenci->soyad);
		if(strcmp(ogrIsim,ogrAd) == 0){
			return sonOgrenci->ogrID;
		}
		free(ogrIsim);
		sonOgrenci=sonOgrenci->next;
	}
}
void kitapOduncDosyayaYaz(kitapOdunc*** KOArray,int diziBoyutu,char* EtiketNo,char* ogrID,int islemTipi,int gun,int ay,int yil){
	FILE* fKitapOdunc = fopen("KitapOdunc.csv","w");
	int i;
	kitapOdunc* tmp = (kitapOdunc*)malloc(sizeof(kitapOdunc));
	strcpy(tmp->EtiketNo,EtiketNo);
	strcpy(tmp->ogrID,ogrID);
	tmp->islemTipi = islemTipi;
	tmp->islemTarihi.gun = gun;
	tmp->islemTarihi.ay = ay;
	tmp->islemTarihi.yil = yil;
	(*KOArray)[diziBoyutu-1] = tmp;
	for(i=0;i<diziBoyutu;i++){
		if(i == (diziBoyutu-1)){
			fprintf(fKitapOdunc,"%s,%s,%d,%d.%d.%d",(*KOArray)[i]->EtiketNo,(*KOArray)[i]->ogrID,(*KOArray)[i]->islemTipi,(*KOArray)[i]->islemTarihi.gun,(*KOArray)[i]->islemTarihi.ay,(*KOArray)[i]->islemTarihi.yil);
		}
		else{
			fprintf(fKitapOdunc,"%s,%s,%d,%d.%d.%d\n",(*KOArray)[i]->EtiketNo,(*KOArray)[i]->ogrID,(*KOArray)[i]->islemTipi,(*KOArray)[i]->islemTarihi.gun,(*KOArray)[i]->islemTarihi.ay,(*KOArray)[i]->islemTarihi.yil);
		}	
	}
	fclose(fKitapOdunc);
}
void teslimSureKontrol(char* ogrID,char* EtiketNo,kitapOdunc** KOArray,int diziBoyutu,ogrenci* head_ref){
	kitapOdunc* teslim = KOArray[diziBoyutu-1];
	kitapOdunc* odunc;
	ogrenci* tmpOgr;
	int gunO,ayO,yilO,gunT,ayT,yilT,i;
	for(i=0;i<diziBoyutu;i++){
		if((strcmp(KOArray[i]->ogrID,ogrID) == 0) && (strcmp(KOArray[i]->EtiketNo,EtiketNo) == 0) && (KOArray[i]->islemTipi == 0)){
			odunc = KOArray[i];
		}
	}
	gunO = odunc->islemTarihi.gun;ayO = odunc->islemTarihi.ay;yilO = odunc->islemTarihi.yil;
	gunT = teslim->islemTarihi.gun;ayT = teslim->islemTarihi.ay;yilT = teslim->islemTarihi.yil;
//	printf("Odunc: %d.%d.%d \nTeslim: %d.%d.%d",gunO,ayO,yilO,gunT,ayT,yilT);
	struct tm teslimTime = { 0 };
    struct tm oduncTime = { 0 };
	teslimTime.tm_year = yilT-1900;teslimTime.tm_mon = ayT-1;teslimTime.tm_mday = gunT;
	oduncTime.tm_year = yilO-1900;oduncTime.tm_mon = ayO-1;oduncTime.tm_mday = gunO;
	
	time_t teslimSure = mktime(&teslimTime);
	time_t oduncSure = mktime(&oduncTime);
	double aradakiZaman = difftime(teslimSure,oduncSure);
	int aradakiGun = round(aradakiZaman/86400);
	if(aradakiGun > 15){
		printf("  %d Gun Gecikmeli Teslim Edildi\n\n  -10 Puan Ceza Kesildi\n",aradakiGun);
		tmpOgr = ogrID2ogr(ogrID,head_ref);
		tmpOgr->puan = tmpOgr->puan-10;
		dosyaGuncelleOgrenci(tmpOgr->ogrID,tmpOgr->ad,tmpOgr->soyad,tmpOgr->puan,head_ref);
	}
	
}
void LLDosyayaYazOgrenci(ogrenci* head_ref){
	ogrenci* tmp = head_ref;
	FILE* fOgrenci = fopen("Ogrenciler.csv","w");
	while(tmp != NULL){
		fprintf(fOgrenci,"%s,%s,%s,%d\n",tmp->ogrID,tmp->ad,tmp->soyad,tmp->puan);
		tmp = tmp->next;
	}
	fclose(fOgrenci);
}
void cezaliListele(ogrenci* head_ref){
	int i=1;
	while(head_ref != NULL){
		if(head_ref->puan < 100){
			printf("%d -) %s %s (%s)\n",i,head_ref->ad,head_ref->soyad,head_ref->ogrID);
		}
		head_ref = head_ref->next;
	}
}

void dosyaOkuYazar(yazar **yazar){
	int column = 0;
	char line[1000];
	int yazarID;
	char yazarAd[30]; 
	char yazarSoyad[30];
	FILE* fOgr;
	fOgr = fopen("Yazarlar.csv","r");
	while(fgets(line,sizeof(line),fOgr)){
		column = 0;
		char *value = strtok(line,",");
		while(value){
			if(column == 0){
				yazarID = atoi(value);
			}
			else if(column == 1){
				strcpy(yazarAd,value);
			}
			else if(column == 2){
				strcpy(yazarSoyad,value);
			}
			value = strtok(NULL,",");
			column++;
		}
		ekleYazar(yazar,yazarID,yazarAd,yazarSoyad,0);
	}
	fclose(fOgr);
}
void ekleYazar(yazar **head_ref,int yazarID,char* yazarAd,char* yazarSoyad,int control){
	yazar* yeniYazar = (yazar*) malloc(sizeof(yazar));
	yazar *son = *head_ref;
	yeniYazar->yazarID = yazarID;
	strcpy(yeniYazar->yazarAd,yazarAd);
	strcpy(yeniYazar->yazarSoyad,yazarSoyad);
	yeniYazar->next = NULL;
	if(strchr(yeniYazar->yazarSoyad,'\n') == 0){
		strcat(yeniYazar->yazarSoyad,"\n");
	}
	if((*head_ref) == NULL){
		*head_ref = yeniYazar;
		return;
	}
	if(son->yazarID < (*head_ref)->yazarID){
		son->next = *head_ref;
		*head_ref = son;
	}
	while(son->next != NULL){
		if(yazarID == son->yazarID && control == 1){
			system("cls");
			printf("!!! Bu Yazar Zaten Mevcut !!!\n");
			sleep(2);
			return;
		}
		if((yazarID > son->yazarID) && (yazarID < son->next->yazarID)){
			yeniYazar->next = son->next;
			son->next = yeniYazar;
			return;
		}
		son = son->next;
	}
	if(yazarID == son->yazarID && control == 1){
		system("cls");
		printf("!!! Bu Yazar Zaten Mevcut !!!\n");
		sleep(2);
		return;
	}
	son->next = yeniYazar;
}
void yazdirYazar(yazar *yazar){
	while(yazar != NULL){
		printf("  %d-) %s | %s\n",yazar->yazarID,yazar->yazarAd,yazar->yazarSoyad);
		yazar = yazar->next;
	}
}

int silYazar(yazar **head_ref,char* yazarAd,char* yazarSoyad){
	yazar *son = *head_ref;
	strcat(yazarSoyad,"\n");
	if((strcmp(son->yazarAd,yazarAd) == 0) && (strcmp(son->yazarSoyad,yazarSoyad) == 0)){
		*head_ref = (*head_ref)->next;
		printf("!! Yazar Basariyla Silindi !!\n");
		return 1;	
	}
	while(son->next->next != NULL){
		if((strcmp(son->next->yazarAd,yazarAd) == 0) && (strcmp(son->next->yazarSoyad,yazarSoyad) == 0)){
			son->next = son->next->next;
			printf("!! Yazar Basariyla Silindi !!\n");
			return 1;	
		}
		son = son->next;
	}
	if((strcmp(son->next->yazarAd,yazarAd) == 0) && (strcmp(son->next->yazarSoyad,yazarSoyad) == 0)){
		son->next = NULL;
		printf("!! Yazar Basariyla Silindi !!\n");
		return 1;	
	}
	printf("  !!! Boyle Bir Yazar Sistemde Bulunmamaktadýr !!!\n\n");
	printf("  Devam Etmek Icin Enter'a Basiniz...\n");
	getch();
	system("cls");
	return 0;
}
void dosyadanSilYazar(char* yazarAd,yazar* head_ref){
	yazar* tmpYazar;
	
	int durum = 0,tmp,i;
	char line[100];
	char *buffer,*ptr;
	buffer = (char*) malloc(500*sizeof(char));
	memset(buffer,0,500*sizeof(char));
	ptr = buffer;
	FILE* fYaz = fopen("Yazarlar.csv","r");
	while(!feof(fYaz)){
		fgets(line,100,fYaz);
		if(strstr(line,yazarAd) == NULL){
			strcpy(ptr,line);
			ptr+= strlen(line);
			tmp = strlen(line);
		}
		else{
			durum = 1;
		}
	}
	if(durum == 0){
		printf("Bu ID ye Sahip Bir Yazar Sistemde Bulunmamaktadýr\n");
		printf("Devam Etmek Icin Enter'a Basiniz...");
		getch();
		fclose(fYaz);
		return;
	}
	fclose(fYaz);
	fYaz = fopen("Yazarlar.csv","w");
	fprintf(fYaz,"%s",buffer);
	fseek(fYaz,(-1*tmp)-1,SEEK_END);
	for(i=0;i<tmp;i++){
		fprintf(fYaz," ");
	}
	fclose(fYaz);
	memset(buffer,0,500*sizeof(char));
	free(buffer);
}
void LLDosyayaYazYazar(yazar *head_ref){
	yazar* tmp = head_ref;
	FILE* fYaz = fopen("Yazarlar.csv","w");
	while(tmp != NULL){
		
		fprintf(fYaz,"%d,%s,%s",tmp->yazarID,tmp->yazarAd,tmp->yazarSoyad);
		
		tmp = tmp->next;
	}
	fclose(fYaz);
}

yazar* yazarBul(char* yazarAd,yazar* head_ref){
	yazar* find = head_ref;
	while(find != NULL){
		if(strcmp(find->yazarAd,yazarAd) == 0){
			return find;
		}
		find = find->next;
	}
	return NULL;
}
void yazarGoruntule(char* yazarAd,yazar* head_ref,kitapYazar** KYArray,int N,kitap* head_ref_kitap){
	int i;
	char* bookName = (char*)malloc(30*sizeof(char));
	yazar* tmp = yazarBul(yazarAd,head_ref);
	if(tmp != NULL){
		printf("\n  Yazarin Ismi : %s\n  Yazarin Soyismi : %s\n  Yazdigi Kitaplar :\n",tmp->yazarAd,tmp->yazarSoyad);
		for(i=0;i<N;i++){
			if(KYArray[i]->YazarID == tmp->yazarID){
				bookName = ISBN2BOOKNAME(head_ref_kitap,KYArray[i]->ISBN);
				printf("  - %s\n",bookName);
			}
		}
	}
	else{
		printf("\n  !! Sistemde Boyle Bir Yazar Yok !!\n\n");
	}
	free(bookName);
	
}
char* ISBN2BOOKNAME(kitap* head_ref,char* ISBN){
	char* bookName = (char*)malloc(30*sizeof(char));
	kitap* sonKitap = head_ref;
	while(sonKitap != NULL){
		if(strcmp(sonKitap->ISBN,ISBN) == 0){
			strcpy(bookName,sonKitap->kitapAdi);
			return bookName;
		}
		sonKitap=sonKitap->next;
	}
}
void guncelleYazar(yazar** head_ref,int yazarID,char* ad,char* soyAd){
	yazar* sonYazar = *head_ref;
	while(sonYazar != NULL){
		if (sonYazar->yazarID == yazarID){
			strcpy(sonYazar->yazarAd,ad);
			strcpy(sonYazar->yazarSoyad,soyAd);
			strcat(sonYazar->yazarSoyad,"\n");
			printf("  !! Guncelleme Islemi Basarili !!\n");
			return;
		}
		sonYazar = sonYazar->next;
	}
}
void kitapYazarSil(kitapYazar*** KYArray,int N,int yazarID){
	int i;
	for(i=0 ; i<N ; i++){
		if((*KYArray)[i]->YazarID == yazarID){
			(*KYArray)[i]->YazarID = -1;
		}
	}
}
int yazarKontrol(yazar* head_ref,int yazarId,char* yazarAd){
	while(head_ref != NULL){
		if((strcmp(head_ref->yazarAd,yazarAd) == 0) || (head_ref->yazarID == yazarId)){
			return 1;
		}
		head_ref = head_ref->next;
	}
	return 0;
}

void gecTeslimListele(kitapOdunc** KOArray,int diziBoyutu,kitap* head_ref_kitap,ogrenci* head_ref_ogr){
	int i,j;
	kitapOdunc* tmp;
	int sira=1;
	char* ISBN;
	for(i=0;i<diziBoyutu;i++){
		if(KOArray[i]->islemTipi == 1){
			for(j=0;j<i;j++){
				if((strcmp(KOArray[i]->EtiketNo,KOArray[j]->EtiketNo) == 0) && (strcmp(KOArray[i]->ogrID,KOArray[j]->ogrID) == 0) && (KOArray[j]->islemTipi == 0)){
					tmp = KOArray[j];
				}
			}
			struct tm teslimTime = { 0 };
		    struct tm oduncTime = { 0 };
			teslimTime.tm_year = KOArray[i]->islemTarihi.yil-1900;teslimTime.tm_mon = KOArray[i]->islemTarihi.ay-1;teslimTime.tm_mday = KOArray[i]->islemTarihi.gun;
			oduncTime.tm_year = tmp->islemTarihi.yil-1900;oduncTime.tm_mon = tmp->islemTarihi.ay-1;oduncTime.tm_mday = tmp->islemTarihi.gun;
			
			time_t teslimSure = mktime(&teslimTime);
			time_t oduncSure = mktime(&oduncTime);
			double aradakiZaman = difftime(teslimSure,oduncSure);
			int aradakiGun = round(aradakiZaman/86400);
			if(aradakiGun > 15){
				ISBN = (char*)calloc(13,sizeof(char));
				strncat(ISBN,KOArray[i]->EtiketNo,13);
		//		printf("\n%s\n",ISBN);
				printf("%d -)  %s | %s | %s %s\n\n",sira,ISBN2BOOKNAME(head_ref_kitap,ISBN),KOArray[i]->EtiketNo,ogrID2ogr(KOArray[i]->ogrID,head_ref_ogr)->ad,ogrID2ogr(KOArray[i]->ogrID,head_ref_ogr)->soyad);
				sira++;
				free(ISBN);
			}
			
		}
	}
}
void dosyaOkuKitap(kitap **head_ref){
	kitap* yeniKitap;
	kitap* sonKitap;
	//---------------------------------
	kitapOrnek* yeniOrnek;
	kitapOrnek* sonOrnek;
	//---------------------------------
	//kitap örneklerini dizme
	char* num = (char*)malloc(sizeof(char));
	int column = 0,i;
	char line[1000];
	char kitapAdi[30]; 
	char ISBN[13];
	int adet; 
	FILE* fKitap;
	fKitap = fopen("Kitaplar.csv","r");
	while(fgets(line,sizeof(line),fKitap) != NULL){
		sscanf(line,"%[^/,],%[^/,],%d",&kitapAdi,&ISBN,&adet);
		yeniKitap = (kitap*)malloc(sizeof(kitap));
		strcpy(yeniKitap->kitapAdi,kitapAdi);
		strcpy(yeniKitap->ISBN,ISBN);
		yeniKitap->adet = adet;
		yeniKitap->head = NULL;
		for(i=1;i<=adet;i++){
			yeniOrnek = (kitapOrnek*)malloc(sizeof(kitapOrnek));
			strcpy(yeniOrnek->Durum,"Rafta");
			strcpy(yeniOrnek->EtiketNo,ISBN);
			strcat(yeniOrnek->EtiketNo,"_");
			*num = 48+i;
			strncat(yeniOrnek->EtiketNo,num,1);
			yeniOrnek->next = NULL;
			if(yeniKitap->head == NULL){
				yeniKitap->head = yeniOrnek;
			}
			sonOrnek = yeniKitap->head;
			while(sonOrnek->next != NULL){
				sonOrnek = sonOrnek->next;
			}
			sonOrnek->next = yeniOrnek;
			sonOrnek->next->next=NULL;
		}
		yeniKitap->next=NULL;
		if(*head_ref == NULL){
			*head_ref = yeniKitap;
		}
		sonKitap = *head_ref;
		while(sonKitap->next != NULL){
			sonKitap = sonKitap->next;
		}
		sonKitap->next = yeniKitap;
		sonKitap->next->next = NULL;
//		dosyadanEkleKitap(kitap,kitapAdi,ISBN,adet);
	}
	fclose(fKitap);
}
void LLkitapEkle(char* kitapAd,kitap **head_ref){
	int i ;
	char ISBN[13];
	char* num =(char*)malloc(sizeof(char));
	kitap* yeniKitap = (kitap*)malloc(sizeof(kitap));
	kitap* son = *head_ref;	
	kitapOrnek* son2;
	while(son != NULL){
		if(strcmp(son->kitapAdi,kitapAd) == 0 ){
			son2 = son->head;
			son->adet +=1;
			kitapOrnek* yeniOrnek = (kitapOrnek*)malloc(sizeof(kitapOrnek));
			strcpy(yeniOrnek->Durum,"Rafta");
			strcpy(yeniOrnek->EtiketNo,son->ISBN);
			strcat(yeniOrnek->EtiketNo,"_");
			*num = 48+(son->adet);
			strncat(yeniOrnek->EtiketNo,num,1);
			yeniOrnek->next = NULL;
			while(son2->next != NULL){
				son2 = son2->next;
			}
			son2->next = yeniOrnek;
			return;
		}
		son = son->next;
	}
	printf("  Kitap ISBN No Giriniz :");
	scanf("%s",ISBN);
	yeniKitap->next = NULL;
	yeniKitap->adet = 1;
	yeniKitap->head = (kitapOrnek*)malloc(sizeof(kitapOrnek));
	strcpy(yeniKitap->ISBN,ISBN);
	strcpy(yeniKitap->kitapAdi,kitapAd);
	strcpy(yeniKitap->head->Durum,"Rafta");
	strcpy(yeniKitap->head->EtiketNo,ISBN);
	strcat(yeniKitap->head->EtiketNo,"_1");
	yeniKitap->head->next = NULL;
	son->next = yeniKitap;
	free(num);
}
void LLDosyayaYazKitap(kitap* head_ref){
	kitap* tmp = head_ref;
	FILE* fKitap = fopen("Kitaplar.csv","w");
	while(tmp != NULL){
		fprintf(fKitap,"%s,%s,%d\n",tmp->kitapAdi,tmp->ISBN,tmp->adet);
		tmp = tmp->next;
	}
	fclose(fKitap);
}
void LLKitapSil(kitap** head_ref,char* kitapAdi,kitapOdunc** KOArray,int diziboyutu,ogrenci* head_ref_ogr,int control){
	kitap* sonKitap = *head_ref;
	kitapOrnek* ornek;
	int flag=2;
	int loop=1;
	while(sonKitap != NULL && loop==1){
//		printf("a");
		if(strcmp(sonKitap->kitapAdi,kitapAdi) == 0){
			loop = 0;
			if(sonKitap->head == NULL){
				if(control == 1){
					printf("  !! Rafta Bu Kitaptan Yok !!\n\n");
				}
				return;
			}
			if(strcmp(rafKontrol(KOArray,diziboyutu,sonKitap->head->EtiketNo,head_ref_ogr),"Rafta") == 0){
				sonKitap->adet = sonKitap->adet -1;
				if(control == 1){
					printf("  No : %s\n",sonKitap->head->EtiketNo);
					printf("  Kitap Basariyla Silindi !!\n\n");
				}
				sonKitap->head = sonKitap->head->next;
				
				return;
			}
			else{
				
				ornek = sonKitap->head;
				if(ornek->next == NULL){
					if(control == 1){
						printf("  !! Rafta Bu Kitaptan Yok !!\n\n");
					}
					return;
				}
				while(ornek->next->next != NULL){
		//			printf("b");
					if(strcmp(rafKontrol(KOArray,diziboyutu,ornek->next->EtiketNo,head_ref_ogr),"Rafta") == 0){
						sonKitap->adet = sonKitap->adet -1;
						if(control == 1){
							printf("  No : %s\n",ornek->next->EtiketNo);
							printf("  Kitap Basariyla Silindi !!\n\n");
						}
						ornek->next = ornek->next->next;
						return;
					}
					ornek=ornek->next;
				}
				if(strcmp(rafKontrol(KOArray,diziboyutu,ornek->next->EtiketNo,head_ref_ogr),"Rafta") == 0){
					sonKitap->adet = sonKitap->adet -1;
					if(control == 1){
						printf("  No : %s\n",ornek->next->EtiketNo);
						printf("  Kitap Basariyla Silindi !!\n\n");
					}
					ornek->next = NULL;
					
					return;
				}
			}

		}
		sonKitap = sonKitap->next;
	}
	
	if(flag == 2 && control == 1){
		printf("  !! Sistemde Bu Kitaptan Yok !!\n\n");
	}
}
void kitapGuncelle(kitap** head_ref,char* kitapAdi,char* ISBN,kitapOdunc** KOArray,int diziboyutu,ogrenci* head_ref_ogr){
	kitap* sonKitap = *head_ref;
	kitap* sonKitap2 = *head_ref;
	kitap* yeniKitap = (kitap*)malloc(sizeof(kitap));
	kitapOrnek* sonOrnek;
	kitapOrnek* yeniOrnek = (kitapOrnek*)malloc(sizeof(kitapOrnek));
	int run=1;
	int tmp,i;
	char ISBNtmp[13];
	char* tmpchr = (char*)malloc(sizeof(char));
	char name[30];
	while((sonKitap2 != NULL) && run==1){
		if(strcmp(sonKitap2->ISBN,ISBN) == 0){
			strcpy(name,sonKitap2->kitapAdi);
			run = 0;
		}
		sonKitap2 = sonKitap2->next;
	}
	LLKitapSil(head_ref,name,KOArray,diziboyutu,head_ref_ogr,0);
	while(sonKitap->next != NULL){
		if(strcmp(sonKitap->kitapAdi,kitapAdi) == 0){
			sonKitap->adet = sonKitap->adet +1;
			i=1;
			sonOrnek = sonKitap->head;
			while(sonOrnek->next != NULL){
				i++;
				sonOrnek=sonOrnek->next;
			}
			strcpy(yeniOrnek->Durum,"Rafta");
			strcpy(yeniOrnek->EtiketNo,sonKitap->ISBN);
			strcpy(ISBNtmp,sonOrnek->EtiketNo);
			*tmpchr = i+48+1;
			strcat(yeniOrnek->EtiketNo,"_");
			strncat(yeniOrnek->EtiketNo,tmpchr,1);
			sonOrnek->next = yeniOrnek;
			sonOrnek->next->next = NULL;
			printf("\n\n  !! Guncelleme Basarili !!\n");
			return;
		}
		sonKitap=sonKitap->next;
	}
	if(strcmp(sonKitap->kitapAdi,kitapAdi) == 0){
		sonKitap->adet = sonKitap->adet +1;
		i=1;
		sonOrnek = sonKitap->head;
		while(sonOrnek->next != NULL){
			i++;
			sonOrnek=sonOrnek->next;
		}
		strcpy(yeniOrnek->Durum,"Rafta");
		strcpy(yeniOrnek->EtiketNo,sonKitap->ISBN);
		strcpy(ISBNtmp,sonOrnek->EtiketNo);
		*tmpchr = i+48+1;
		strcat(yeniOrnek->EtiketNo,"_");
		strncat(yeniOrnek->EtiketNo,tmpchr,1);
		sonOrnek->next = yeniOrnek;
		sonOrnek->next->next = NULL;
		printf("\n\n  !! Guncelleme Basarili !!\n");
		return;
	}
	printf("  ISBN No. Giriniz : ");scanf("%s",ISBNtmp);
	strcpy(yeniKitap->ISBN,ISBNtmp);
	strcpy(yeniKitap->kitapAdi,kitapAdi);
	yeniKitap->adet = 1;
	yeniKitap->head = (kitapOrnek*)malloc(sizeof(kitapOrnek));
	strcpy(yeniKitap->head->Durum,"Rafta");
	strcpy(yeniKitap->head->EtiketNo,ISBN);
	strcat(yeniKitap->head->EtiketNo,"_1");
	yeniKitap->head->next = NULL;
	sonKitap->next = yeniKitap;
	sonKitap->next->next = NULL;
	LLDosyayaYazKitap(*head_ref);
	printf("\n\n  !! Guncelleme Basarili !!\n");
	return;
}
void kitapGoruntule(kitap* head_ref,char* kitapAdi,kitapOdunc** KOArray,int KOArrayBoyut,ogrenci* head_ref_ogr,int control){
	kitap* sonKitap = head_ref;
	kitapOrnek* ornek1;
	int i;
	while(sonKitap != NULL){
		if(strcmp(sonKitap->kitapAdi,kitapAdi) == 0){
			ornek1 = sonKitap->head;
			if(control == 1 || control == 2){
				for(i=0;i<(sonKitap->adet);i++){
					printf("  %d -) %s |",i+1,ornek1->EtiketNo,rafKontrol(KOArray,KOArrayBoyut,ornek1->EtiketNo,head_ref_ogr));
					if(control == 2){
						if(strcmp(rafKontrol(KOArray,KOArrayBoyut,ornek1->EtiketNo,head_ref_ogr),"Rafta") == 0){
							printf(" Rafta\n");
						}
						else{
							printf(" Ogrencide\n");
						}
					}
					else{
						printf(" %s\n",rafKontrol(KOArray,KOArrayBoyut,ornek1->EtiketNo,head_ref_ogr));
					}
					ornek1 = ornek1->next;
				}
				return;
			}
			
			
		}
		sonKitap = sonKitap->next;
	}
	if(control != 2){
		printf("\n!! Bu Kitap Sistemde Bulunmuyor !!\n");
	}
}
char* rafKontrol(kitapOdunc** KOArray,int diziBoyutu,char* EtiketNo,ogrenci* head_ref){
	char* Durum = (char*)malloc(7*sizeof(char));
	int i;
	int control = 0;
	char* OgrenciNo ;
	ogrenci* ogr;
	char* Ogrenci;
	for(i=0;i<diziBoyutu;i++){
		if((strcmp(KOArray[i]->EtiketNo,EtiketNo) == 0)&& KOArray[i]->islemTipi == 1){
			
			control = 0;
		}
		else if((strcmp(KOArray[i]->EtiketNo,EtiketNo) == 0)&& KOArray[i]->islemTipi == 0){
			OgrenciNo = (char*)calloc(9,sizeof(char));
			strcpy(OgrenciNo,KOArray[i]->ogrID);
			ogr = ogrID2ogr(OgrenciNo,head_ref);
			control = 1;
		}
	}
	if(control == 1){
		Ogrenci = (char*)calloc(30,sizeof(char));
		strcpy(Ogrenci,ogr->ad);
		strcat(Ogrenci," ");
		strcat(Ogrenci,ogr->soyad);
		return Ogrenci;
	}
	else if(control == 0){
		strcpy(Durum,"Rafta");
		return Durum;
	}
}
void raftakiGoruntule(kitap* head_ref,kitapOdunc** KOArray,int M,ogrenci* head_ref_ogrenci){
	int i = 0;
	
	kitap* sonKitap = head_ref;
	kitapOrnek* ornek;
	printf("---------------------------------------------- RAFTAKI KITAPLAR ----------------------------------------\n\n");
	while(sonKitap != NULL){
		
		
		ornek = sonKitap->head;
		
		printf("  %s :\n\n",sonKitap->kitapAdi);
		while(ornek != NULL){
			if(strcmp(rafKontrol(KOArray,M,ornek->EtiketNo,head_ref_ogrenci),"Rafta") == 0){
				printf("  %s\n",ornek->EtiketNo);
			}
			ornek = ornek->next;
		}printf("\n---------------------------------------------------------------------------------------------------\n");
		sonKitap = sonKitap->next;
	}
}
void dosyaOkuKitapYazar(kitapYazar*** KYArray){
	FILE* kitapYazarFile = fopen("KitapYazar.csv","r");
	char line[1000];
	int i = 0,column;
	
	while(fgets(line,sizeof(line),kitapYazarFile)){
		(*KYArray)[i] = (kitapYazar*)malloc(sizeof(kitapYazar));
		column = 0;
		char *value = strtok(line,",");
		while(value){
			if(column == 0){
				strcpy(((*KYArray)[i])->ISBN,value);
			}
			else if(column == 1){
				((*KYArray)[i])->YazarID = atoi(value);
			}
			value = strtok(NULL,",");
			column++;
		}
//		
		i++;
//		free(tmp);
	}
}
void yazarKitapEslestir(kitapYazar*** KYArray,int diziBoyut,kitap* head_ref_kitap,yazar* head_ref_yazar,char* kitapAdi,char* yazarAdi){
	kitap* sonKitap = head_ref_kitap;
	yazar* sonYazar = head_ref_yazar;
	kitapYazar* sonuc = (kitapYazar*)malloc(sizeof(kitapYazar));
	char ISBN[13];
	int YazarID;
	int run =1;
//	*diziBoyut +=1;
//	(*KYArray) 	= (kitapYazar**)realloc((*KYArray),(*diziBoyut)*sizeof(kitapYazar));
	while((sonKitap != NULL) && run == 1){
		if(strcmp(sonKitap->kitapAdi,kitapAdi) == 0){
			strcpy(sonuc->ISBN,sonKitap->ISBN);
			run =0;
		}
		sonKitap=sonKitap->next;
	}
	
	run =1;
	while((sonYazar != NULL) && run == 1){
		if(strcmp(sonYazar->yazarAd,yazarAdi) == 0){
			sonuc->YazarID = sonYazar->yazarID;
			run =0;
		}
		sonYazar = sonYazar->next;
	}
	(*KYArray)[diziBoyut-1] = sonuc;
}
void kitapYazariGuncelle(kitapYazar*** KYArray,int diziBoyutu,char* kitapAdi,char* yazarAdiEski,char* yazarAdiYeni,kitap* head_ref_kitap,yazar* head_ref_yazar){
	kitap* sonKitap = head_ref_kitap;
	yazar* sonYazar = head_ref_yazar;
	kitapYazar* sonuc = (kitapYazar*)malloc(sizeof(kitapYazar));
	char ISBN[13];
	int YazarID;
	int run =1,i,yeniID;
//	*diziBoyut +=1;
//	(*KYArray) 	= (kitapYazar**)realloc((*KYArray),(*diziBoyut)*sizeof(kitapYazar));
	while((sonKitap != NULL) && run == 1){
		if(strcmp(sonKitap->kitapAdi,kitapAdi) == 0){
			strcpy(sonuc->ISBN,sonKitap->ISBN);
			run =0;
		}
		sonKitap=sonKitap->next;
	}
	run =1;
	while((sonYazar != NULL)){
		if(strcmp(sonYazar->yazarAd,yazarAdiEski) == 0){
			sonuc->YazarID = sonYazar->yazarID;
	
		}
		if(strcmp(sonYazar->yazarAd,yazarAdiYeni) == 0){
			yeniID = sonYazar->yazarID;
		}
		sonYazar = sonYazar->next;
	}

	for(i=0;i<diziBoyutu;i++){
		if((strcmp((*KYArray)[i]->ISBN,sonuc->ISBN) == 0) && ((*KYArray)[i]->YazarID == sonuc->YazarID)){
			(*KYArray)[i]->YazarID = yeniID;
		}
	}

}
void LLDosyayaYazKitapYazar(kitapYazar** KYArray,int diziBoyutu){
	int i;
	FILE* fKitapYazar = fopen("KitapYazar.csv","w");
	for(i=0;i<diziBoyutu;i++){
		if(i == diziBoyutu-1){
			fprintf(fKitapYazar,"%s,%d",KYArray[i]->ISBN,KYArray[i]->YazarID);
		}
		else{
			fprintf(fKitapYazar,"%s,%d\n",KYArray[i]->ISBN,KYArray[i]->YazarID);
		}
		
	}
	fclose(fKitapYazar);
}
int kitapKontrol(kitap* head_ref,char* kitapAdi){
	while(head_ref != NULL){
		if(strcmp(head_ref->kitapAdi,kitapAdi) == 0){
			return 1;
		}
		head_ref = head_ref->next;
	}
	return 0;
}
int kitapYazarKontrol(kitapYazar** KYArray,int diziBoyutu,char* yazarAd,char* kitapAd,yazar* head_ref_yazar,kitap* head_ref_kitap){
	int i;
	yazar* tmpYazar;
	char* bookName;
	for(i=0;i<diziBoyutu;i++){
		tmpYazar = yazarBul(yazarAd,head_ref_yazar);
		bookName = ISBN2BOOKNAME(head_ref_kitap,KYArray[i]->ISBN);
		if((KYArray[i]->YazarID == tmpYazar->yazarID) && (strcmp(bookName,kitapAd) == 0)){
			return 1;
		}
	}
	return 0;
}

