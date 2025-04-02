#include <stdio.h> //biblioteka koja sadrzi f-je za upisivanje i ispisivanje
#include <stdlib.h> //biblioteka za: alokaciju memorije, koverziju stringa, koriscenje f-je random, exit, system 
#include <string.h> //biblioteka za koriscenje f-ja nad stringom
#include <time.h> //biblioteka koja ti pomaze za rad sa vremenom
#include <windows.h> //biblioteka za SLEEP, HANDLE
#include <conio.h> //biblioteka za f-je u vezi sa input/output: cgets, cputs, clrscr (ciscenje ekrana)...


void loadingbar();
void cls(); //cls - ciscenje konzole
void br(int linija);
void razmak(int tab);
void ccolor(int clr); //bojenje outputa
void dobrodosli();
void glavni_meni();
void dodaj_novu_listu();
void dodaj_kafu();
void brisanje_kafe();
void izbrisi_prazne_redove();
void prikaz_liste_kafa();
int odredjivanje_broja_kafa();
void bubble_sort();
int provera_prazne_liste();
void izmena_podataka_o_kafi();
void porudzbine();
void pregled_porudzbina();
float ukupna_zarada();
void prikaz_liste_placanja();
void admin_panel();

struct Kafa {
	char naziv_kafe[50];
	int ID;
	int kolicina;
	float cena;
};

typedef struct element {
	struct Kafa k;
	struct element *next;
} Element;

Element* napravi_dinamicku_listu() {
	Element *head = NULL, *tail = head, *tmp;
	struct Kafa kafa;
	FILE *datoteka;

	datoteka = fopen("Spisak kafa.txt", "r");
	if(datoteka == NULL) {
		printf("Greska pri otvaranju datoteke!\n");
		exit(1);
	}
	while (fscanf(datoteka, "%[^:]:%d%d%f\n", kafa.naziv_kafe, &kafa.ID, &kafa.kolicina, &kafa.cena) != EOF) {
		tmp = (Element*) malloc(sizeof(Element));
		if (tmp == NULL) {
			printf("\nGreska prilikom alokacije memorije!");
			exit(1);
		}
		tmp->k = kafa;
		tmp->next = NULL;
		if (head == NULL) {
			head = tmp;
		}
		else {
			tail->next = tmp;
		}
		tail = tmp;
	}
	fclose(datoteka);
	return head;
}

Element* nadji_i_izbrisi_kafu (Element* head, int serial) {
	int count;
	int postoji = 0;
	Element *temp, *prev = NULL;
	temp = head;

	while (temp) {
		if(temp->k.ID == serial) {
			Element *old = temp; temp = temp->next;
			if (prev) prev->next = temp;
			else head = temp;
			free(old);
			cls();
			br(4); razmak(4);
			printf("    Brisanje kafe %d ", serial);
			for(count = 0; count < 4; count++) {printf(" ."); Sleep(400);}
			br(4); razmak(4);
			printf("    Brisanje uspesno!\n"); Sleep(1000);
			postoji = 1;
		}
		else {
			prev = temp; temp = temp->next;
		}

		if(temp == NULL && postoji == 0) {
			printf("\n\n\n\n\t\t   Kafa nije pronadjena! Unet pogresan ID. Pokusajte ponovo.\n"); Sleep(2500);
		}
	}
	return head;
}

Element* nadji_kafu(Element *head, int serial) {
	Element *temp;
	temp = head;
	while (temp) {
		if(temp->k.ID == serial) {
			return temp;
		}
		else {
			temp = temp->next;
		}
		if(temp == NULL) {
			return temp;
		}
	}
}

void oslobodi_memoriju(Element* head) {
	while(head) {
		Element *old = head; head = head->next;
		free(old);
	}
}

int main() {

	system("title Kafeterija"); //title prozora
	system("mode con: cols=96 lines=30"); //velicina prozora
	system("color 75"); //boja pozadine console i boja slova (prvi broj oznacava boju pozadine, drugi boju slova)

	loadingbar();
	cls();
	dobrodosli();
	cls(); 

	glavni_meni();
}

//f-ja za prikazivanje ucitavanja
void loadingbar() { 
	int i, j;
	ccolor(110);
	for(i=15; i<=100; i+=5) {
		cls();

		br(7);
		razmak(4);
	
		printf("     %d %% Ucitavanje...\n\n\t\t     ", i);

		for(j=0; j<i; j+=2) { 
			ccolor(160+j);    
			printf(" ");     
			ccolor(110); 
		} 

		Sleep(100); 
	}
}

void cls() {
	system("cls");
}

void br(int linija) {
	int i;
	for(i=0; i<linija; i++) {
		printf("\n");
	}
}

void razmak(int tab) {
	int i;
	for(i=0; i<tab; i++) {
		printf("\t");
	}
}

void ccolor(int clr) {
	HANDLE  hConsole;
	hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
	SetConsoleTextAttribute(hConsole, clr);
}

//funkcija za dobrodoslicu u aplikaciju
void dobrodosli() {
	int slovo;
	int slovo2;
	int slovo3;

	char dobrodosli[50] = "DOBRODOSLI";
	char dobrodosli2[50] = "U";
	char dobrodosli3[50] = "KAFETERIJU";

	ccolor(110);       
	br(10); razmak(4); printf("  ");
	for(slovo=0;slovo<strlen(dobrodosli);slovo++){
		
		printf(" %c", dobrodosli[slovo]);
		Sleep(100);
	}
	ccolor(110);
	printf("\n\n\t\t\t\t\t"); printf("  ");
	for(slovo2=0;slovo2<strlen(dobrodosli2);slovo2++){
		
		printf(" %c", dobrodosli2[slovo2]);
		Sleep(100);
	}
	ccolor(110);
	printf("\n\n\t\t\t\t"); printf("  ");
	for(slovo3=0;slovo3<strlen(dobrodosli3);slovo3++){
		
		printf(" %c", dobrodosli3[slovo3]);
		Sleep(100);                                      
	}
	ccolor(110);
}

void glavni_meni() {
	int izbor;
	int admin_panel_izbor;

	cls();
	br(5); razmak(4); printf("   >> 1. Kupovina kafe"); Sleep(400);
	br(2); razmak(4); printf("   >> 2. Admin panel"); Sleep(400);
	br(2); razmak(4); printf("   >> 3. Kraj"); Sleep(400);
	br(2);

	br(2); razmak(4);
	printf("   Izaberite jednu opciju: ");
	fflush(stdin);
	scanf("%d", &izbor);
	if (izbor >= 1 && izbor <= 3) {
		if (izbor == 1) {
			int	unos;
			unos = provera_prazne_liste();
			if (unos == 0) {
				cls();
				br(4); razmak(1);
				printf("Lista kafa ne postoji. Porudzbine trenutno nisu moguce. Povratak u glavni meni.\n"); Sleep(3500);
				glavni_meni();
			} 
			porudzbine();
			do {
				br(2); razmak(2); printf(">> 0. Glavni meni"); Sleep(400);
				br(2); razmak(2); printf(">> 1. Napravite novu porudzbinu"); Sleep(400);
				br(2); razmak(2); printf("Unesite vas izbor: ");
				fflush(stdin); scanf("%d", &unos);
				if(unos == 0) {
					glavni_meni(); 
				}
				else if (unos == 1) {
					porudzbine(); 
				}
				if (unos != 0 && unos != 1) {
					cls();
					printf("\n\n\n\t\t\t\tPogresan unos. Pokusajte ponovo.\n"); Sleep(2000);
					cls();
				}
			} while (unos != 0 || unos != 1);
		}
		else if (izbor == 2) {
			do {
				cls(); br(4); razmak(2); printf("  1. Glavni meni\n\t"); Sleep(300); br(4); razmak(2);
				printf("  Molimo Vas unesite sifru ili 1 za povratak na glavni meni: ");

				fflush(stdin);
				scanf("%d", &admin_panel_izbor);

				if (admin_panel_izbor == 2201) {
					admin_panel();
				}
				else if (admin_panel_izbor == 1) {
					glavni_meni();
				}
				else if (admin_panel_izbor != 2201 || admin_panel_izbor != 1) {
					cls();
					printf("\n\n\n\t\t\t\tNeispravna sifra. Pokusajte ponovo.\n"); Sleep(2000);
				}
				cls();
			} while(admin_panel_izbor != 2201 || admin_panel_izbor != 1);
		}
		else if (izbor == 3) {
			cls();
			br(7);
			razmak(1);
			printf(" Hvala sto ste koristili sistem za vodjenje evidencije narucivanja u kafeteriji.");
			br(14); razmak(1); Sleep(1000);
			exit(1);
		}
	}
	else {
		cls();
		br(6); razmak(3);
		printf("   Molimo Vas izaberite opciju od 1 do 3."); Sleep(2000);
		glavni_meni();
	}

}

void admin_panel() {
	int admin_izbor;
	int broj_kafa;
	float zarada;
	int nazad4; //koristi se za povratak u glavni meni ili admin panel

	cls(); br(3); razmak(5); printf(" Admin Panel\n\n");
	razmak(3);
	printf("   >> 1. Dodajte potpuno novu listu kafa \n\n"); Sleep(250); razmak(3);
	printf("   >> 2. Dodajte kafu \n\n"); Sleep(250); razmak(3);
	printf("   >> 3. Izbrisite kafu \n\n"); Sleep(250); razmak(3);
	printf("   >> 4. Trenutna lista kafa \n\n"); Sleep(250); razmak(3);
	printf("   >> 5. Izmena podataka o kafi \n\n"); Sleep(250); razmak(3);
	printf("   >> 6. Pogledajte porudzbine \n\n"); Sleep(250); razmak(3);
	printf("   >> 7. Placanja karticom \n\n"); Sleep(250); razmak(3);		
	printf("   >> 8. Ukupan broj kafa \n\n"); Sleep(250); razmak(3);
	printf("   >> 9. Ukupna zarada \n\n"); Sleep(250); razmak(3);   
	printf("   >> 0. Glavni meni \n\n"); razmak(3);
	printf("Izaberite opciju od 1 do 9 (ili 0 za glavni meni): ");
	Sleep(250);

	fflush(stdin);
	scanf("%d", &admin_izbor);

	switch (admin_izbor) {
	case 1: 
			cls();
			dodaj_novu_listu();
			cls();
			do {
				br(3); razmak(2); printf("   <-- 0. Glavni meni     <-- 1. Admin panel\n"); 
				br(1); razmak(5);
				fflush(stdin);
				scanf("%d", &nazad4);
				cls();
				if (nazad4 != 0 && nazad4 != 1) {
					printf("\n\n\n\t\t\t\tPogresan unos. Pokusajte ponovo.\n"); Sleep(2000);
					cls();
				}
			} while (nazad4 != 0 && nazad4 != 1);
			if (nazad4 == 0) {glavni_meni();}
			else {admin_panel();}
	case 2: 
			cls();
			dodaj_kafu();
			do {
				br(3); razmak(3); printf("    <-- 0. Glavni meni     <-- 1. Admin panel\n");
				br(1); razmak(6);
				fflush(stdin); scanf("%d", &nazad4);
				cls();
				if (nazad4 != 0 && nazad4 != 1) {
					printf("\n\n\n\t\t\t\tPogresan unos. Pokusajte ponovo.\n"); Sleep(2000);
					cls();
				}
			} while (nazad4 != 0 && nazad4 != 1);
			if (nazad4 == 0) {glavni_meni();}
			else {admin_panel();}
	case 3:
			//Brisanje kafe iz liste
			cls();
			brisanje_kafe();
			do {
				br(3); razmak(3); printf("    <-- 0. Glavni meni     <-- 1. Admin panel\n");
				br(1); razmak(6);
				fflush(stdin); scanf("%d", &nazad4);
				cls();
				if (nazad4 != 0 && nazad4 != 1) {
					printf("\n\n\n\t\t\t\tPogresan unos. Pokusajte ponovo.\n"); Sleep(2000);
					cls();
				}
			} while (nazad4 != 0 && nazad4 != 1);
			if (nazad4 == 0) {glavni_meni();}
			else {admin_panel();}
	case 4:
			//Prikaz trenutne liste kafa
			cls();
			printf("\n\n\n\n\t\t\t          Trenutna lista kafa:");
			br(2); razmak(2);
			prikaz_liste_kafa(); Sleep(1500);
			do {
				br(3); razmak(3); printf("    <-- 0. Glavni meni     <-- 1. Admin panel\n");
				br(1); razmak(6);
				fflush(stdin); scanf("%d", &nazad4);
				cls();
				if (nazad4 != 0 && nazad4 != 1) {
					printf("\n\n\n\t\t\t\tPogresan unos. Pokusajte ponovo.\n"); Sleep(2000);
					cls();
				}
			} while (nazad4 != 0 && nazad4 != 1);
			if (nazad4 == 0) {glavni_meni();}
			else {admin_panel();}
	case 5:
			//Izmena podataka o kafi
			cls();
			izmena_podataka_o_kafi();
			do {
				br(3); razmak(3); printf("    <-- 0. Glavni meni     <-- 1. Admin panel\n");
				br(1); razmak(6);
				fflush(stdin); scanf("%d", &nazad4);
				cls();
				if (nazad4 != 0 && nazad4 != 1) {
					printf("\n\n\n\t\t\t\tPogresan unos. Pokusajte ponovo.\n"); Sleep(2000);
					cls();
				}
			} while (nazad4 != 0 && nazad4 != 1);
			if (nazad4 == 0) {glavni_meni();}
			else {admin_panel();}
	case 6:
			//pregled zavrsenih porudzbina iz datoteke
			cls();
			pregled_porudzbina();
			do {
				br(3); razmak(3); printf("    <-- 0. Glavni meni     <-- 1. Admin panel\n");
				br(1); razmak(6);
				fflush(stdin); scanf("%d", &nazad4);
				cls();
				if (nazad4 != 0 && nazad4 != 1) {
					printf("\n\n\n\t\t\t\tPogresan unos. Pokusajte ponovo.\n"); Sleep(2000);
					cls();
				}
			} while (nazad4 != 0 && nazad4 != 1);
			if (nazad4 == 0) {glavni_meni();}
			else {admin_panel();}
	case 7:
			//Ispis placanja karticama
			cls();
			prikaz_liste_placanja();
			do {
				br(3); razmak(3); printf("    <-- 0. Glavni meni     <-- 1. Admin panel\n");
				br(1); razmak(6);
				fflush(stdin); scanf("%d", &nazad4);
				cls();
				if (nazad4 != 0 && nazad4 != 1) {
					printf("\n\n\n\t\t\t\tPogresan unos. Pokusajte ponovo.\n"); Sleep(2000);
					cls();
				}
			} while (nazad4 != 0 && nazad4 != 1);
			if (nazad4 == 0) {glavni_meni();}
			else {admin_panel();}
	case 8:
			//Ispis koliko kafa ima u listi
			cls();
			broj_kafa = odredjivanje_broja_kafa();
			br(3); razmak(4); printf("  Broj kafa u listi kafa je %d.", broj_kafa);
			do {
				br(3); razmak(3); printf("    <-- 0. Glavni meni     <-- 1. Admin panel\n");
				br(1); razmak(6);
				fflush(stdin); scanf("%d", &nazad4);
				cls();
				if (nazad4 != 0 && nazad4 != 1) {
					printf("\n\n\n\t\t\t\tPogresan unos. Pokusajte ponovo.\n"); Sleep(2000);
					cls();
				}
			} while (nazad4 != 0 && nazad4 != 1);
			if (nazad4 == 0) {glavni_meni();}
			else {admin_panel();}
	case 9:
			cls();
			zarada = ukupna_zarada();
			br(3); razmak(4); printf("Ukupna zarada je: %0.2f rsd.", zarada);
			do {
				br(3); razmak(3); printf("    <-- 0. Glavni meni     <-- 1. Admin panel\n");
				br(1); razmak(6);
				fflush(stdin); scanf("%d", &nazad4);
				cls();
				if (nazad4 != 0 && nazad4 != 1) {
					printf("\n\n\n\t\t\t\tPogresan unos. Pokusajte ponovo.\n"); Sleep(2000);
					cls();
				}
			} while (nazad4 != 0 && nazad4 != 1);
			if (nazad4 == 0) {glavni_meni();}
			else {admin_panel();}
	case 0: glavni_meni();
	default : 
			cls(); br(6); razmak(3);
			printf("Pogresan unos. Izaberite ponovo."); Sleep(2000);
			admin_panel();
		}

}

void dodaj_novu_listu() {
	int unos = 1;
	struct Kafa kafa;
	FILE *datoteka;
	Element *head, *pronadjen;
	int provera = 1;
	getchar();
	while (unos) {
		if (provera == 1) {
			datoteka = fopen("Spisak kafa.txt", "w");
			if(datoteka == NULL) {
				printf("Greska pri otvaranju datoteke!\n");
				exit(1);
			}
			printf("\n\tNaziv kafe : "); 
			gets(kafa.naziv_kafe);
			printf("\n\tID Kafe : ");
			scanf("%d", &kafa.ID);
			printf("\n\tKolicina : ");
			scanf("%d", &kafa.kolicina);
			printf("\n\tCena : ");
			scanf("%f", &kafa.cena);
			fprintf(datoteka, "%s: %d %d %0.2f\n", kafa.naziv_kafe, kafa.ID, kafa.kolicina, kafa.cena);
			fclose(datoteka);
			provera = 0;
		}
		else {
			head = napravi_dinamicku_listu();
			do {
				prikaz_liste_kafa();
				printf("\n\n\tNaziv kafe : "); 
				gets(kafa.naziv_kafe);
				printf("\n\tID Kafe : ");
				scanf("%d", &kafa.ID);
				printf("\n\tKolicina : ");
				scanf("%d", &kafa.kolicina);
				printf("\n\tCena : ");
				scanf("%f", &kafa.cena);
				pronadjen = nadji_kafu(head, kafa.ID);
				cls();
				if (pronadjen != NULL) {printf("\n\n\n\n\t\t   Kafa sa datim ID-jem vec postoji. Molimo Vas unesite drugi ID.\n"); Sleep(3500); cls(); getchar();}
			} while (pronadjen != NULL);
			datoteka = fopen("Spisak kafa.txt", "a+");
			if(datoteka == NULL) {
				printf("Greska pri otvaranju datoteke!\n");
				exit(1);
			}
			fprintf(datoteka, "%s: %d %d %0.2f\n", kafa.naziv_kafe, kafa.ID, kafa.kolicina, kafa.cena);
			oslobodi_memoriju(head);
			fclose(datoteka);
			bubble_sort();
		}
		do {
			printf("\n\tDa li zelite da nastavite unos: 1 <- DA    0 <- NE : ");
			scanf("%d", &unos);
			cls();
			if (unos != 1 && unos != 0) {
				printf("\n\n\n\t\t\t\tPogresan unos. Pokusajte ponovo.\n"); Sleep(2000);
				cls();
			}
		} while (unos != 1 && unos != 0);
		getchar();
	}
}

void dodaj_kafu() {
	int unos = 1;
	int postoji = 1;
	struct Kafa kafa;
	FILE *datoteka;
	Element *pronadjen, *head;

	//provera da li lista kafa postoji da bismo dodali novu kafu
	if ((datoteka = fopen("Spisak kafa.txt", "r")) == NULL) {
		br(2);
		printf("     Lista kafa ne postoji. Morate uneti novu listu preko opcije 1. u admin panelu.\n"); 
		postoji = 0;
	}
	else {
		fclose(datoteka);
	}

	if (postoji) {
		getchar();
		while (unos) {
			head = napravi_dinamicku_listu();
			datoteka = fopen("Spisak kafa.txt", "a+");
			if(datoteka == NULL) {
				printf("Greska pri otvaranju datoteke!\n");
				exit(1);
			}
			do {
				prikaz_liste_kafa(); 
				br(2); printf("\n\tNaziv kafe : ");
				gets(kafa.naziv_kafe);
				printf("\n\tID Kafe : ");
				scanf("%d", &kafa.ID);
				printf("\n\tKolicina : ");
				scanf("%d", &kafa.kolicina);
				printf("\n\tCena : ");
				scanf("%f", &kafa.cena);
				pronadjen = nadji_kafu(head, kafa.ID);
				cls();
				if (pronadjen != NULL) {printf("\n\n\n\n\t\t   Kafa sa datim ID-jem vec postoji. Molimo Vas unesite drugi ID.\n"); Sleep(3500); cls(); getchar();}
			} while (pronadjen != NULL);
			fprintf(datoteka, "%s: %d %d %0.2f\n", kafa.naziv_kafe, kafa.ID, kafa.kolicina, kafa.cena);

			do {
				printf("\n\n\t\t\tDa li zelite da nastavite unos: 1 <- DA    0 <- NE.\n");
				fflush(stdin); razmak(5); scanf("%d", &unos); 
				cls();
				if (unos != 1 && unos != 0) {
					printf("\n\n\n\t\t\t\tPogresan unos. Pokusajte ponovo.\n"); Sleep(2000);
					cls();
				}
			} while (unos != 1 && unos != 0);
			getchar();
			fclose(datoteka);
			bubble_sort();
			oslobodi_memoriju(head);
		}
	}
}

void brisanje_kafe() {
	FILE *datoteka;
	Element *head, *temp;
	struct Kafa kafa;
	int postoji;
	int unos = 1;
	int id;

	//provera da li je datoteka prazna ukoliko postoji datoteka
	postoji = provera_prazne_liste();
	if (postoji == 0) {br(2); razmak(1); printf(" Lista kafa ne postoji. Morate uneti novu listu preko opcije 1. u admin panelu.\n");}

	if (postoji) {

		prikaz_liste_kafa(); Sleep(500);

		while (unos) {	
			head = napravi_dinamicku_listu();
			br(3); razmak(3); 
			printf(" Unesite ID kafe koju zelite da izbrisete: ");
			fflush(stdin);
			scanf("%d", &id);

			head = nadji_i_izbrisi_kafu(head, id);
			datoteka = fopen("Spisak kafa.txt", "w+");
			if(datoteka == NULL) {
				printf("Greska pri otvaranju datoteke!\n");
				exit(1);
			}
			temp = head;
			while(temp) {
				fprintf(datoteka, "%s: %d %d %0.2f\n", temp->k.naziv_kafe, temp->k.ID, temp->k.kolicina, temp->k.cena);
				temp = temp->next;
			}
			fprintf(datoteka, "\n");
			fclose(datoteka);

			izbrisi_prazne_redove();
			oslobodi_memoriju(head);
			br(4); razmak(1);

			do {
				cls();
				prikaz_liste_kafa(); Sleep(500);
				printf("\n\n\t Da li zelite da nastavite brisanje kafa iz liste? 1 <- DA    0 <- NE. ");
				fflush(stdin);
				scanf("%d", &unos);
				if (unos != 1 && unos != 0) {
					cls(); br(4); razmak(4);
					printf("Pogresan unos. Pokusajte ponovo."); Sleep(1500); br(2);
				}
			} while (unos != 1 && unos != 0);
			postoji = provera_prazne_liste();
			if (postoji == 0) {br(2); razmak(1); printf(" Lista kafa ne postoji. Morate uneti novu listu preko opcije 1. u admin panelu.\n"); unos = 0;}
		}
	}
}

void prikaz_liste_kafa() {
	FILE *datoteka;
	struct Kafa kafa;
	char item_name[] = "Naziv kafe";
	char item_no[] = "ID Kafe";
	char item_price[] = "Cena";
	char item_stock[] = "Na stanju";
	int postoji;
	postoji = provera_prazne_liste();

	printf("\n\t"); ccolor(240);
	printf("________________________________________________________________________________"); 
	printf("\n\t"); ccolor(240);
	printf("|  %-8s  |   %-30s   |  %-10s  |  %-8s  |", item_no, item_name, item_price, item_stock); 
	printf("\n\t"); ccolor(240);
	printf("--------------------------------------------------------------------------------"); 

	datoteka = fopen("Spisak kafa.txt","r");
	if (datoteka == NULL || postoji == 0) {
		br(2);
		printf("\n\t"); ccolor(240);
		printf("Lista kafa ne postoji.  Morate uneti novu listu preko opcije 1. u admin panelu.\n"); 
		ccolor(110);
	}
	else {
		while(fscanf(datoteka, "%[^:]:%d%d%f\n", kafa.naziv_kafe, &kafa.ID, &kafa.kolicina, &kafa.cena) == 4) {
				printf("\n\t"); ccolor(62);
				printf("|  %-8d  |   %-30s   |  %-10.2f  |  %-8d   |", kafa.ID, kafa.naziv_kafe, kafa.cena, kafa.kolicina);
				ccolor(26);
				printf("\n\t"); ccolor(62);
				printf("--------------------------------------------------------------------------------");

				Sleep(100);
			}
			fclose(datoteka);
			ccolor(110);
	}
}

void izbrisi_prazne_redove() {
	char line[100];
	FILE *temp, *datoteka;
	
	datoteka = fopen("Spisak kafa.txt", "r");
	if(datoteka == NULL) {
		printf("Greska pri otvaranju datoteke!\n");
		exit(1);
	}

	temp = fopen("Spisak kafa temporary.txt", "w");
	if (temp == NULL) {
		printf("Greska pri otvaranju datoteke!\n");
		exit(1);
	}

	while (fgets(line, 100, datoteka) != NULL) {
		if (line[0] != '\n')
		fputs(line, temp);
	}

	fclose(datoteka);
	fclose(temp);

	remove("Spisak kafa.txt");
	rename("Spisak kafa temporary.txt", "Spisak kafa.txt");
}

int odredjivanje_broja_kafa() {
	FILE *datoteka;
	int postoji = 1;
	int broj_kafa = 0;
	char c;
	datoteka = fopen("Spisak kafa.txt","r");
	if (datoteka == NULL) {
		br(2);
		printf("\n\t");
		printf("Lista kafa ne postoji.  Morate uneti novu listu preko opcije 1. u admin panelu.\n"); 
		postoji = 0;
	}
	if (postoji) {
		for(c = getc(datoteka); c != EOF; c = getc(datoteka)) {
		if(c == '\n') {
			broj_kafa += 1;
			}
		}
	}

	fclose(datoteka);
	return broj_kafa;
}

void bubble_sort() {
	struct Kafa kafa;
	FILE *datoteka;
	int swapped;
	Element *head;
	Element *temp1, *temp2 = NULL;
	head = napravi_dinamicku_listu();

	do
    { 
        swapped = 0; 
        temp1 = head; 
  
        while (temp1->next != temp2) 
        { 
			if (temp1->k.ID > temp1->next->k.ID) 
            { 
				kafa = temp1->k;
				temp1->k = temp1->next->k;
				temp1->next->k = kafa;	 
                swapped = 1; 
            } 
            temp1 = temp1->next; 
        } 
        temp2 = temp1; 
    } while (swapped);

	datoteka = fopen("Spisak kafa.txt", "w");
	if(datoteka == NULL) {
		printf("Greska pri otvaranju datoteke!\n");
		exit(1);
	}
	temp1 = head;
	while(temp1) {
		fprintf(datoteka, "%s: %d %d %0.2f\n", temp1->k.naziv_kafe, temp1->k.ID, temp1->k.kolicina, temp1->k.cena);
		temp1 = temp1->next;
	}
	fclose(datoteka);
	izbrisi_prazne_redove();
	oslobodi_memoriju(head);
	
}

int provera_prazne_liste() {
	long size;
	FILE *datoteka;
	datoteka = fopen("Spisak kafa.txt", "r");
	if(datoteka == NULL) {
		return 0;
	}
	else {
		fseek (datoteka, 0, SEEK_END);
		size = ftell(datoteka);
		fclose(datoteka);
		if (size != 0) {
			return 1;
		}
		else return 0;
	}
}

void izmena_podataka_o_kafi() {
	FILE *datoteka;
	Element *head, *pronadjen;
	int id, izbor, nova_kolicina, unos;
	float nova_cena;
	int postoji;
	postoji = provera_prazne_liste();
	if ((datoteka = fopen("Spisak kafa.txt", "r")) == NULL || postoji == 0) {
		br(2);
		printf("     Lista kafa ne postoji. Morate uneti novu listu preko opcije 1. u admin panelu.\n"); 
		postoji = 0;
	}
	else {fclose(datoteka);}
	while (postoji) {
		cls();
		prikaz_liste_kafa();
		printf("\n\n\t\t Izaberite ID kafe za koju zelite da promenite podatke: ");
		fflush(stdin);
		scanf("%d", &id);
		head = napravi_dinamicku_listu();
		pronadjen = nadji_kafu(head, id);

		if (pronadjen != NULL) {
			do {
				cls();
				prikaz_liste_kafa(); Sleep(400);
				br(3); razmak(4); printf("   >> 1. Izmena imena"); Sleep(400);
				br(2); razmak(4); printf("   >> 2. Izmena kolicine"); Sleep(400);
				br(2); razmak(4); printf("   >> 3. Izmena cene"); Sleep(400);
				br(2); razmak(4); printf("   >> 4. Otkazi izmene"); Sleep(400);
				printf("\n\n\t\t  Izaberite opciju koju zelite da promenite za kafu sa ID-jem %d: ", id);
				fflush(stdin);
				scanf("%d", &izbor);
				if (izbor == 1) {
					printf("\n\n\t\t  Unesite novo ime kafe umesto postojeceg imena %s: ", pronadjen->k.naziv_kafe);
					getchar();
					gets(pronadjen->k.naziv_kafe);
					break;
				}
				else if (izbor == 2) {
					printf("\n\n\t\t  Unesite novu kolicinu za kafu %s: ", pronadjen->k.naziv_kafe);
					fflush(stdin);
					scanf("%d", &nova_kolicina);
					pronadjen->k.kolicina = nova_kolicina;
					break;
				}
				else if (izbor == 3) {
					printf("\n\n\t\t  Unesite novu cenu za kafu %s: ", pronadjen->k.naziv_kafe);
					fflush(stdin);
					scanf("%f", &nova_cena);
					pronadjen->k.cena = nova_cena;
					break;
				}
				else if (izbor == 4) {break;}
				else {
					cls(); br(6); razmak(4);
					printf("Pogresan unos. Izaberite ponovo."); Sleep(2000);
				}
			} while (izbor != 1 && izbor != 2 && izbor != 3 && izbor != 4);
			pronadjen = head;
			datoteka = fopen("Spisak kafa.txt", "w");
			if (datoteka == NULL) {printf ("\n\n\t\tGreska prilikom otvaranja datoteke.\n"); exit(1);}
			while(pronadjen) {
				fprintf(datoteka, "%s: %d %d %0.2f\n", pronadjen->k.naziv_kafe, pronadjen->k.ID, pronadjen->k.kolicina, pronadjen->k.cena);
				pronadjen = pronadjen->next;
			}
			fclose(datoteka);
		}
		else {printf("\n\n\n\n\t\t   Kafa nije pronadjena! Unet pogresan ID. Pokusajte ponovo.\n"); Sleep(2500);}

		izbrisi_prazne_redove();
		oslobodi_memoriju(head);
		free(pronadjen);       

		do {
			cls();
			printf("\n\n\t Da li zelite da nastavite izmenu podataka o kafama iz liste? 1 <- DA    0 <- NE. ");
			fflush(stdin);
			scanf("%d", &unos);
			if (unos != 1 && unos != 0) {
				cls(); br(4); razmak(4);
				printf("Pogresan unos. Pokusajte ponovo."); Sleep(1500); br(2);
				cls();
			}
			else if (unos == 0) {postoji = 0;}
		} while (unos != 1 && unos != 0);
	}
}

void porudzbine() {
	int broj_kartice;
	int pin;
	int izbor_kafe = 1, unos1, postoji = 0, unos2;
	char niz_imena[50][50];
	int niz_trazenih_kolicina[50];
	float niz_cena[50];
	int niz_id[50];
	int i = 0, j; //brojaci
	FILE *datoteka, *datoteka_porudzbine, *datoteka_placanja;
	Element *head, *pronadjen;
	int trazena_kolicina;
	float ukupna_cena = 0;
	time_t t;
	time(&t);

	head = napravi_dinamicku_listu();
	do {
		cls();
		prikaz_liste_kafa();
		br(2); razmak(2); printf("=> 0. Povratak nazad");
		br(2); razmak(1); printf("Unesite ID kafe koju zelite da porucite (0 za povratak nazad): ");
		fflush(stdin); scanf("%d", &izbor_kafe);
		if (izbor_kafe == 0) {izbor_kafe = 0; oslobodi_memoriju(head);}
		else {
			pronadjen = nadji_kafu(head, izbor_kafe);
			if (pronadjen != NULL) {
				do {
					br(2); razmak(2); printf("Unesite kolicinu izabrane kafe sa ID-jem %d: ", pronadjen->k.ID); 
					fflush(stdin); scanf("%d", &trazena_kolicina);
					if (pronadjen->k.kolicina < trazena_kolicina) {
						br(2); razmak(3); printf("  Nema dovoljno izabrene kafe na stanju.\n"); Sleep(2500); cls(); 
						prikaz_liste_kafa();
					}
					else if (trazena_kolicina == 0 || trazena_kolicina < 0) {br(2); razmak(1); printf("Izabrali ste nepostojecu kolicinu za dati proizvod. Molimo unesite broj veci od nule."); Sleep(2500); cls(); prikaz_liste_kafa();}
				} while (pronadjen->k.kolicina < trazena_kolicina || trazena_kolicina == 0 || trazena_kolicina < 0);		
				ukupna_cena = ukupna_cena + (pronadjen->k.cena * trazena_kolicina);
				strcpy(niz_imena[i], pronadjen->k.naziv_kafe);
				niz_trazenih_kolicina[i] = trazena_kolicina;
				niz_cena[i] = pronadjen->k.cena;
				niz_id[i] = pronadjen->k.ID;
				pronadjen = NULL;
				i++;
				if (i == 50) {
					cls();
					br(3); razmak(2); printf("List sa racunima je popunjen. Ubacite novi list za nastavak dalje.");
					izbor_kafe = 0;
				}
				do {
					cls();
					br(4); razmak(2); printf(">> 1. Potvrdite i zavrsite porudzbinu"); Sleep(400);
					br(2); razmak(2); printf(">> 2. Nastavite kupovinu"); Sleep(400);
					br(2); razmak(2); printf("Izaberite opciju za nastavak: ");
					fflush(stdin); scanf("%d", &unos1);
					if (unos1 != 1 && unos1 != 2) {
						br(4); razmak(4);
						printf("Pogresan unos. Pokusajte ponovo."); Sleep(1500); br(2);
						continue;
					}
					else if (unos1 == 1) {
						cls();
						do {
							br(2); razmak(2); printf(">> 1. Placanje gotovinom"); Sleep(400);
							br(2); razmak(2); printf(">> 2. Placanje karticom"); Sleep(400);
							br(2); razmak(2); printf("Izaberite opciju placanja: ");
							fflush(stdin); scanf("%d", &unos2);
						} while(unos2 != 1 && unos2 != 2);
						if (unos2 == 1) {

							datoteka = fopen("Spisak kafa.txt", "w");
							if (datoteka == NULL) {printf ("\n\n\t\tGreska prilikom otvaranja datoteke.\n"); exit(1);}
							for (j = 0; j < i; j++) {
								pronadjen = nadji_kafu(head, niz_id[j]);
								pronadjen->k.kolicina = pronadjen->k.kolicina - niz_trazenih_kolicina[j];
							}
							pronadjen = head;
							while (pronadjen) {
								fprintf(datoteka, "%s: %d %d %0.2f\n", pronadjen->k.naziv_kafe, pronadjen->k.ID, pronadjen->k.kolicina, pronadjen->k.cena);
								pronadjen = pronadjen->next;
							}
							fclose(datoteka);

							datoteka_placanja = fopen("Placanja.txt", "a+");      
							if (datoteka_placanja == NULL) {printf("\nGreska prilikom otvaranja datoteke."); exit(1);}
							cls(); br(4); razmak(4);  printf("===>HVALA VAM<===");
							br(2); razmak(4); printf("Porudzbina uspesno izvrsena ..."); Sleep(4000);
							cls();
							datoteka_porudzbine = fopen("Porudzbine.txt", "a+");
							if(datoteka_porudzbine == NULL) {printf("\n\tGreska prilikom otvaranja datoteke."); exit(1);}
							br(3); razmak(5); printf("Vas racun: ");
							br(2); razmak(2); printf("Porudzbina --------------------------------");
							fputs("Porudzbina --------------------------------", datoteka_porudzbine);
							for (j = 0; j < i; j++) {
								br(2); razmak(2); printf("%s %0.2f x %d --- %0.2f rsd", niz_imena[j], niz_cena[j], niz_trazenih_kolicina[j], niz_cena[j] * niz_trazenih_kolicina[j]);
								fprintf(datoteka_porudzbine, "\n%s %0.2f x %d --- %0.2f rsd", niz_imena[j], niz_cena[j], niz_trazenih_kolicina[j], niz_cena[j] * niz_trazenih_kolicina[j]);		
							} 
							fprintf(datoteka_placanja, "Nacin placanja placeno-kesom Iznos %0.2f rsd\n", ukupna_cena);
							br(2); razmak(2); printf("Ukupna cena vase porudzbine je: %0.2f rsd.", ukupna_cena);
							fputs("\nUkupna cena porudzbine je: ", datoteka_porudzbine);
							fprintf(datoteka_porudzbine, "%0.2f rsd.", ukupna_cena);
							br(2); razmak(2); printf("Datum izdavanja racuna : %s\n", ctime(&t)); 
							fputs("\nDatum porudzbine : ", datoteka_porudzbine);
							fprintf(datoteka_porudzbine, "%s\n", ctime(&t));
							fclose(datoteka_porudzbine);
							oslobodi_memoriju(head);
							fclose(datoteka_placanja);
							izbor_kafe = 0;
						}
						else {

							datoteka = fopen("Spisak kafa.txt", "w");
							if (datoteka == NULL) {printf ("\n\n\t\tGreska prilikom otvaranja datoteke.\n"); exit(1);}
							for (j = 0; j < i; j++) {
								pronadjen = nadji_kafu(head, niz_id[j]);
								pronadjen->k.kolicina = pronadjen->k.kolicina - niz_trazenih_kolicina[j];
							}
							pronadjen = head;
							while (pronadjen) {
								fprintf(datoteka, "%s: %d %d %0.2f\n", pronadjen->k.naziv_kafe, pronadjen->k.ID, pronadjen->k.kolicina, pronadjen->k.cena);
								pronadjen = pronadjen->next;
							}
							fclose(datoteka);

							datoteka_placanja = fopen("Placanja.txt", "a+");       
							if (datoteka_placanja == NULL) {printf("\nGreska prilikom otvaranja datoteke."); exit(1);} 
							cls(); br(4); razmak(4); printf("Unesite broj kartice: ");
							fflush(stdin); scanf("%d", &broj_kartice);
							br(2); razmak(2); printf("Unesite Vas pin [Nikad ne cuvamo pinove]: ");
							fflush(stdin); scanf("%d", &pin);
							cls(); br(4); razmak(4);  printf("===>HVALA VAM<===");
							br(2); razmak(4); printf("Porudzbina uspesno izvrsena ..."); Sleep(4000);
							cls();
							datoteka_porudzbine = fopen("Porudzbine.txt", "a+");
							if(datoteka_porudzbine == NULL) {printf("\n\tGreska prilikom otvaranja datoteke."); exit(1);}
							br(3); razmak(5); printf("Vas racun: ");
							br(2); razmak(2); printf("Porudzbina --------------------------------");
							fputs("Porudzbina --------------------------------", datoteka_porudzbine);
							for (j = 0; j < i; j++) {
								br(2); razmak(2); printf("%s %0.2f x %d --- %0.2f rsd", niz_imena[j], niz_cena[j], niz_trazenih_kolicina[j], niz_cena[j] * niz_trazenih_kolicina[j]);
								fprintf(datoteka_porudzbine, "\n%s %0.2f x %d --- %0.2f rsd", niz_imena[j], niz_cena[j], niz_trazenih_kolicina[j], niz_cena[j] * niz_trazenih_kolicina[j]);		
							} 
							fprintf(datoteka_placanja, "Nacin placanja %d Iznos %0.2f rsd\n", broj_kartice, ukupna_cena);
							br(2); razmak(2); printf("Ukupna cena vase porudzbine je: %0.2f rsd.", ukupna_cena);
							fputs("\nUkupna cena porudzbine je: ", datoteka_porudzbine);
							fprintf(datoteka_porudzbine, "%0.2f rsd.", ukupna_cena);
							br(2); razmak(2); printf("Datum izdavanja racuna : %s\n", ctime(&t)); 
							fputs("\nDatum porudzbine : ", datoteka_porudzbine);
							fprintf(datoteka_porudzbine, "%s\n", ctime(&t));
							fclose(datoteka_porudzbine);
							oslobodi_memoriju(head);
							fclose(datoteka_placanja);
							izbor_kafe = 0;
						}
					}
				} while (unos1 != 1 && unos1 != 2);	
			}
			else {printf("\n\n\n\n\t\t   Kafa nije pronadjena! Unet pogresan ID. Pokusajte ponovo.\n"); Sleep(2500);}
		}
	} while (izbor_kafe != 0 && pronadjen == NULL);
}

void pregled_porudzbina() {
	FILE *datoteka;
	char linija[100];
	datoteka = fopen("Porudzbine.txt", "r");
	if (datoteka == NULL) {
		br(2); razmak(3); printf("Datoteka sa porudzbinama ne postoji. Cekamo prvu porudzbinu!\n");
	}
	else {
		while(fgets(linija, sizeof linija, datoteka) != NULL) {
			fprintf(stdout,"%s", linija); 
		}
		fclose(datoteka);
	}
}

float ukupna_zarada() {
	int postoji;
	float ukupna_zarada = 0;
	float temp;
	char string1[100];
	char string2[100];
	char string3[100];
	char string4[100];
	char string5[100];
	FILE *datoteka_placanja;
	datoteka_placanja = fopen("Placanja.txt","r");
	if (datoteka_placanja == NULL) {
		br(2); razmak(2); printf("Datoteka sa izvrsenim placanjima ne postoji. Cekamo prvu porudzbinu!\n");
	}
	else {
		while (fscanf(datoteka_placanja, "%s %s %s %s %f %s", string1, string2, string3, string4, &temp, string5) != EOF) {
			ukupna_zarada = ukupna_zarada + temp;
		}
		fclose(datoteka_placanja);
	}
	return ukupna_zarada;
}

void prikaz_liste_placanja() {
	FILE *datoteka_placanja;
	char string1[100];
	char string2[100];
	char string3[100];
	char string4[100];
	char string5[100];
	float zarada;
	char item_name1[] = "Broj kartice";
	char item_name2[] = "Iznos $";
	int i;
	int broj_kartice;
	int *niz_kartica;
	float *niz_zarada;
	int provera;
	int brojac = 0;

	datoteka_placanja = fopen("Placanja.txt", "r");
	if (datoteka_placanja == NULL) {br(3); razmak(3); printf("Datoteka sa izvrsenim placanjima ne postoji jos uvek!");}
	else { 
		niz_kartica = (int*) malloc(1 * sizeof(int));
		if (niz_kartica == NULL) {printf("\nNeuspesna alokacija memorije."); exit(1);}
		niz_zarada = (float*) malloc(1 * sizeof(float));
		if (niz_zarada == NULL) {printf("\nNeuspesna alokacija memorije."); exit(1);}
	
		datoteka_placanja = fopen("Placanja.txt", "r");
		if (datoteka_placanja == NULL) {printf("\nGreska prilikom otvaranja datoteke."); exit(1);}
		while (fscanf(datoteka_placanja, "%s %s %s %s %f %s", string1, string2, string3, string4, &zarada, string5) != EOF) {
			provera = strcmp(string3, "placeno-kesom");
			if (provera == 0) {
				continue;
			}
			else {
				niz_zarada[brojac] = zarada;
				broj_kartice = atoi(string3);
				niz_kartica[brojac] = broj_kartice;
				brojac++;
				niz_kartica = (int*) realloc(niz_kartica, (brojac+1) * sizeof(int));
				if (niz_kartica == NULL) {printf("\nNeuspesna alokacija memorije."); exit(1);} 
				niz_zarada = (float*) realloc(niz_zarada, (brojac+1) * sizeof(float));
				if (niz_zarada == NULL) {printf("\nNeuspesna alokacija memorije."); exit(1);}
			}
		}
		br(3); razmak(5); printf("Placanja karticom:");
		br(2); razmak(3); printf("    _______________________________________\n");
		razmak(3); printf("   |    %-15s|      %-13s|\n", item_name1, item_name2);
		razmak(3); printf("    ---------------------------------------\n"); Sleep(150);
		for (i = 0; i < brojac; i++) {
			razmak(3); printf("   |  %-15d  |  %-15.2f  |\n", niz_kartica[i], niz_zarada[i]); 
			razmak(3); printf("   ----------------------------------------\n"); 
			Sleep(150);
		}

		free(niz_kartica);
		free(niz_zarada);
		fclose(datoteka_placanja);
	}
}