#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <stdbool.h>

// constante
const char LUNAR[] = {"1 luna"};
const int pretLUNAR = 800;
const char TRIMESTRIAL[] = {"3 luni"};
const int pretTRIMESTRIAL = 2000;
const char ANUAL[] = {"1 an"};
const int pretANUAL = 6600;

// char nume_fisier[20] = {"clienti.dat"}; //doar pentru testare
char nume_fisier[20];

typedef struct
{ // structura de stocat date

    int codClient;
    char nume[20];
    char tipAbonament[14];
    int pretAbonament;
    char instructor[20];
    char data[20];
} Client;

void mesajInitial() // mesaj principal
{

    printf("\t\t\t###########################################################################");
    printf("\n\t\t\t############                                                   ############");
    printf("\n\t\t\t############      Sistem gestiune clienti piscina in C         ############");
    printf("\n\t\t\t############                                                   ############");
    printf("\n\t\t\t###########################################################################");
    printf("\n\t\t\t---------------------------------------------------------------------------\n");
}

void creare() // creare fisier binar
{
    FILE *f;
    // char nume_fisier[20];
    printf("\n\t\t\tCum doriti sa denumiti fisierul (.dat): ");
    gets(nume_fisier);

    f = fopen(nume_fisier, "wb");
    if (!f)
        printf("\n\t\t\tFisierul nu a putut fi creat!\n");
    else
        printf("\n\t\t\tFisierul %s a fost creat cu succes!\n", nume_fisier);
    fclose(f);
}

void adaugare(char *fisier) // adaugare clienti
{
    FILE *f;
    Client a;
    int abonament = 0;

    f = fopen(fisier, "rb+");
    fseek(f, 0, SEEK_END);

    if (!f)
        printf("\n\t\t\tFisierul nu a putut fi deschis !");
    else
    {
        printf("\n\t\t\tCodul clientului: ");
        scanf("%d", &a.codClient);

        while (!feof(stdin))
        {
            printf("\n\t\t\tNume client:");
            getchar();
            gets(a.nume);
            printf("\n\t\t\tTip abonament (Alege 1 pentru lunar | 2 pentru trimestrial | 3 pentru anual):");
            scanf("%d", &abonament);
            if (abonament == 1)
            {
                strcpy(a.tipAbonament, LUNAR);
                a.pretAbonament = pretLUNAR;
            }
            else if (abonament == 2)
            {
                strcpy(a.tipAbonament, TRIMESTRIAL);
                a.pretAbonament = pretTRIMESTRIAL;
            }
            else
            {
                strcpy(a.tipAbonament, ANUAL);
                a.pretAbonament = pretANUAL;
            }
            printf("\n\t\t\tInstructor repartizat: ");
            getchar();
            gets(a.instructor);
            strcpy(a.data, __DATE__);
            fwrite(&a, sizeof(Client), 1, f);
            printf("\n\t\t\tCodul clientului: ");
            scanf("%d", &a.codClient);
        }
        fclose(f);
    }
}

void modificare_client_instructor(char *fisier)
// actualizare instructor client (dupa numele clientului)
{
    FILE *f;
    Client a;
    char nume[20];
    int i;

    f = fopen(fisier, "rb+");
    if (!f)
        printf("\n\t\t\tFisierul %s nu poate fi deschis", fisier);
    else
    {
        printf("\n\t\t\tNume client: ");
        gets(nume);
        while (!feof(stdin))
        {
            rewind(f);
            fread(&a, sizeof(Client), 1, f);
            i = false;
            while ((!feof(f)) && (!i)) //! false is true
            {
                if (strcmp(nume, a.nume) == 0)
                {
                    i = true;
                    printf("\n\t\t\tCod client:%d Nume: %s \n\t\t\tPret abonament: %d Tip abonament: %s Instructor: %s \n\t\t\tData start abonament: %s\n", a.codClient, a.nume, a.pretAbonament, a.tipAbonament, a.instructor, a.data);
                    printf("\n\t\t\tNoul instructor:");
                    gets(a.instructor);
                    fseek(f, ftell(f) - sizeof(Client), 0);
                    fwrite(&a, sizeof(Client), 1, f);
                    if (!feof(stdin))
                        printf("\n\t\t\tDatele au fost modificate cu success!\n");
                }
                fread(&a, sizeof(Client), 1, f);
            }
            if (!i)
            {
                printf("\n\t\t\tClientul nu a fost gasit.\n");
            }
            printf("\n\t\t\tNume client: ");
            gets(nume);
        }
        fclose(f);
    }
}

void modificare_abonament_clienti(char *fisier)
// actualizare tip abonament clienti(dupa tipul de abonament)
{
    FILE *f;
    Client a;
    char abonament[20];
    int i, d;

    f = fopen(fisier, "rb+");
    if (!f)
        printf("\n\t\t\tFisierul %s nu a putut fi deschis", fisier);
    else
    {
        printf("\n\t\t\tTip abonament| 1 luna | 3 luni | 1 an| :");
        gets(abonament);
        while (!feof(stdin))
        {
            rewind(f); // ne mutam la inceputul fisierului
            fread(&a, sizeof(Client), 1, f);
            i = false;

            while (!feof(f))
            {
                if (strcmp(abonament, a.tipAbonament) == 0)
                {
                    i = true;
                    printf("\n\t\t\tClient %s cu abonament %s gasit.\n", a.nume, a.tipAbonament);
                    printf("\n\t\t\tNoul tip de abonament (Alege 1 pentru lunar | 2 pentru trimestrial | 3 pentru anual):");
                    scanf("%d", &d);
                    getchar();
                    if (d == 1)
                    {
                        strcpy(a.tipAbonament, LUNAR);
                        a.pretAbonament = pretLUNAR;
                    }
                    else if (d == 2)
                    {
                        strcpy(a.tipAbonament, TRIMESTRIAL);
                        a.pretAbonament = pretTRIMESTRIAL;
                    }
                    else
                    {
                        strcpy(a.tipAbonament, ANUAL);
                        a.pretAbonament = pretANUAL;
                    }
                    fseek(f, ftell(f) - sizeof(Client), 0);
                    fwrite(&a, sizeof(Client), 1, f);
                    fseek(f, 0, 1);
                    if (!feof(stdin))
                        printf("\n\t\t\tDatele au fost modificate cu success!\n");
                }
                fread(&a, sizeof(Client), 1, f);
            }
            if (i == false)
            {
                printf("\n\t\t\tNu a fost gasit nici un client cu acest tip de abonament");
            }
            printf("\n\t\t\tTip abonament| 1 luna | 3 luni | 1 an|:");
            gets(abonament);
        }
        fclose(f);
    }
}

void stergere_client(char *fisier) //stergere clienti
{
    FILE *f;
    FILE *tempf;
    Client a;
    int i = false;
    int j;

    f = fopen(fisier, "rb");
    if (!f)
        printf(("\n\t\t\tFisierul %s nu a putut fi deschis", fisier));
    tempf = fopen("temp.dat", "wb");
    if (!tempf)
        printf("\n\t\t\tFisierul temp.dat nu a putut fi creat!");
    printf("\n\t\t\tIntroduceti codul clientului de sters:");
    scanf("%d", &j);

    while (fread(&a, sizeof(Client), 1, f))
    {
        if (a.codClient != j)
        {
            fwrite(&a, sizeof(Client), 1, tempf);
        }
        else
        {
            i = true;
        }
    }
    (i) ? printf("\n\t\t\tClient sters cu succes.....\n") : printf("\n\t\t\tClientul cu codul %d nu exista", j);
    fclose(f);
    fclose(tempf);

    remove(fisier);
    rename("temp.dat", fisier);
}

void raport_integral(char *fisier) // creare raport fisier text
{
    {
        FILE *f, *t;
        Client a;
        int n;
        char fisierTxt[20];
        f = fopen(fisier, "rb");
        if (!f)
            printf("\n\t\t\tFisierul %s nu a putut fi deschis", fisier);
        else
        {
            printf("\n\t\t\tCum doriti sa numiti raportul:");
            gets(fisierTxt);
            t = fopen(fisierTxt, "w");
            fprintf(t, "\n Nr. Cod Nume cLient \t\tTip abonament \t\tPret RON \t\tData \t\t Instructor\n");
            fread(&a, sizeof(Client), 1, f);
            n = 0;

            while (!feof(f))
            {
                fprintf(t, "\n %-3d %-3d %-20s %-20s %-3d     %-16s %s", ++n, a.codClient, a.nume, a.tipAbonament, a.pretAbonament, a.data, a.instructor);
                fread(&a, sizeof(Client), 1, f);
            }
            printf("\n\t\t\tRaportul a fost creat cu succes!\n");
            fclose(t);
            fclose(f);
        }
    }
}

void raport_partial(char *fisier) // creare raport partial text
{
    FILE *f, *t;
    Client a;
    int n;
    char fisierTxt[20];
    char nume_instr[20];
    f = fopen(fisier, "rb");
    if (!f)
        printf("\n\t\t\tFisierul %s nu a putut fi deschis", fisier);
    else
    {
        printf("\n\t\t\tRaport clienti ce au instructor pe:");
        gets(nume_instr);
        while (!feof(stdin))
        {
            rewind(f);
            printf("\n\t\t\tCum doriti sa numiti raportul:");
            gets(fisierTxt);
            t = fopen(fisierTxt, "w");
            fprintf(t, "\n Nr. Cod Nume cLient \t\tTip abonament \t\tPret RON \t\tData \t\t Instructor\n");

            fread(&a, sizeof(Client), 1, f);
            n = 1;
            while (!feof(f))
            {
                if (strcmp(nume_instr, a.instructor) == 0)
                {
                    fprintf(t, "\n %-3d %-3d %-20s %-20s %-3d     %-16s %s", n++, a.codClient, a.nume, a.tipAbonament, a.pretAbonament, a.data, a.instructor);
                }
                fread(&a, sizeof(Client), 1, f);
            }
            if (n > 1)
                printf("\n\t\t\tRaportul %s a fost creat cu succes!\n", fisierTxt);
            else if (n == 1)
            {
                printf("\n\t\t\tNu exista client cu instructorul %s!", nume_instr);
                fclose(t); // nu merge sters fisierul daca nu este inchis
                remove(fisierTxt);
            }
            // printf("\n\t\t\tNu exista client cu instructorul %s!", nume_instr);
            printf("\n\t\t\tRaport clienti ce au instructor pe:");
            gets(nume_instr);
            fclose(t);
        }
        fclose(f);
    }
}

void raport_ecran(char *fisier) // afisare client pe ecran in functie de codul sau
{
    FILE *f;
    Client a;
    int n;
    int i;

    f = fopen(fisier, "rb");
    if (!f)
        printf("\n\t\t\tFisierul %s nu a putut fi deschis", fisier);
    else
    {
        printf("\n\t\t\tIntroduceti codul clientului dorit:");
        scanf("%d", &n);

        while (!feof(stdin))
        {
            rewind(f);
            fread(&a, sizeof(Client), 1, f);
            i = false;
            while (!feof(f) && !i)
            {
                if (n == a.codClient)
                {
                    i = true;
                    printf("\n\t\t\tCod:%d Nume:%s Tip abonament:%s \n\n\t\t\tPret abonament:%d Data:%s Instructor:%s", a.codClient, a.nume, a.tipAbonament, a.pretAbonament, a.data, a.instructor);
                }
                fread(&a, sizeof(Client), 1, f);
            }
            if (!i)
                printf("\n\t\t\tNu exista clientul cu codul:%d!", n);
            printf("\n\t\t\tIntroduceti codul clientului dorit:");
            scanf("%d", &n);
        }
        fclose(f);
    }
}

void meniu() //afisare meniu
{
    int optiune = 0;
    do
    {
        printf("\n\n");
        mesajInitial();
        printf("\n\n\n\t\t\t1.Creare fisier binar");
        printf("\n\t\t\t2.Adaugare clienti");
        printf("\n\t\t\t3.Modificarea instructorului repartizat unui client");
        printf("\n\t\t\t4.Modificare abonamente grup clienti");
        printf("\n\t\t\t5.Stergerea unui client");
        printf("\n\t\t\t6.Raport fisier text clienti");
        printf("\n\t\t\t7.Raport partial fisier text clienti (in functie de instructor)");
        printf("\n\t\t\t8.Afisare client dupa codul de inregistrare");
        printf("\n\t\t\t0.Iesire program");

        printf("\n\n\t\t\tOptiune -->:");
        scanf("%d", &optiune);
        fflush(stdin);

        switch (optiune)
        {
        case 1:
            creare();
            system("PAUSE");
            break;
        case 2:
            adaugare(nume_fisier);
            system("PAUSE");
            break;
        case 3:
            modificare_client_instructor(nume_fisier);
            system("PAUSE");
            break;
        case 4:
            modificare_abonament_clienti(nume_fisier);
            system("PAUSE");
            break;
        case 5:
            stergere_client(nume_fisier);
            system("PAUSE");
            break;
        case 6:
            raport_integral(nume_fisier);
            system("PAUSE");
            break;
        case 7:
            raport_partial(nume_fisier);
            system("PAUSE");
            break;
        case 8:
            raport_ecran(nume_fisier);
            system("PAUSE");
            break;
        case 0:
            printf("\n\n\n\t\t\t\tMultumesc, o zi buna!!!\n\n\n\n\n");
            break;
        default:
            printf("\n\n\n\t\t\tAlegerea nu este valida!!! Reincercati...");
            system("PAUSE");
            break;
        }
    } while (optiune != 0);
}

void main() // functie principala
{
    meniu();
}