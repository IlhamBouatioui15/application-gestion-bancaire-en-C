#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <conio.h>
#define CMAX 30
int gererclient(int a);
int gerercompte(int a);
void gereroperation(int a);
int y;
int solde;
typedef struct SClient
{
  int Code_client;
  char Nom[CMAX];
  char Prenom[CMAX];
  
}SClient;

int comparer (const void* a, const void* b)
{
    const SClient *c1 = a ;
    const SClient *c2 = b ;
    return strcmp(c1->Nom, c2->Nom);
}

typedef struct Date
{
    int Jour;
    int Mois;
    int Annee;
}date;

typedef struct SCompte
{
    int Code_compte;
    int Code_client;
    int somme;
    struct Date date_compte;
}SCompte;


SClient clients[30];
SCompte comptes[30];

void menu()
{
	printf("\n\n\n\n");
	printf("                           1- Gestion des clients\n");
    printf("                           2- Gestion des comptes\n");
    printf("                           3- Gestion des operations\n");
    printf("                           4- Quitter le programme\n\n\n");
    //structure de saisie
    do
	{
	   printf("            Veuillez choisir un numero : ");
       scanf("%d",&y);
    }while(y<1||y>4);
    sousmenu(y);
}

int sousmenu(int a)
{
    if (a==1)
    {
        printf("                          1- Ajouter client\n");
        printf("                          2- Modifier client\n");
        printf("                          3- supprimer client\n");
        printf("                          4- afficher client\n");
        printf("                          5- Afficher la liste des clients par ordre alphabetique\n");
        printf("                          6- Menu\n\n\n");
        // controle de saisie
        do{
        	printf("          Veuillez choisir un numero : ");
			scanf("%d",&y);
		}while(y<1||y>6);
		gererclient(y);
    }
    else if (a==2)
    {
        printf("                        1- Creer un compte\n");
        printf("                        2- Rechercher un compte\n");
        printf("                        3- Afficher la liste des comptes\n");
        printf("                        4- Supprimer un compte\n");
        printf("                        5- Menu\n\n\n");
        do{
        	printf("          Veuillez choisir un numero : ");
			scanf("%d",&y);
		}while(y<1 &&y>5);
        gerercompte(y);
    }
    else if (a==3)
    {
        printf("                         1- Retrait d'argent\n");
        printf("                         2- Versement d'argent\n");
        printf("                         3- Menu\n\n\n");
        do{
        	printf("          Veuillez choisir un numero : ");
			scanf("%d",&y);
		}while(y<1||y>5);
        gereroperation(y);
    }
    else 
        return 0;

    return 0;
}

int gererclient(int a)
{
    if (a==1)
    {
        struct SClient client;
        FILE *infile;

        printf("\n                 Code Client : ");
        scanf("%d", &client.Code_client);
        printf("\n                 Prenom : ");
        scanf("%s", &client.Prenom);
        printf("\n                 Nom : ");
        scanf("%s", &client.Nom);

        infile = fopen("client.txt", "a");
        fwrite(&client, sizeof(client), 1, infile);

        if(fwrite )
            printf("                client ajoute avec succes !\n");
        else
            printf("               erreur! veuillez ajouter le client de nouveau !\n");
        fclose(infile);
    }
    else if (a==2)
    {
        struct SClient client;
        struct SClient nvClient;
        FILE *infile;

        printf("\n\n                   Code Client a modifier: ");
        scanf("%d", &nvClient.Code_client);
        printf("\n\n                   Nouveau Prenom : ");
        scanf("%s", &nvClient.Prenom);
        printf("\n\n                   Nouveau Nom : ");
        scanf("%s", &nvClient.Nom);

        infile = fopen("client.txt", "r");
        int i,nbClients = 0 ;
        while(fread(&client, sizeof(struct SClient), 1, infile)){
            clients[nbClients] = client;
            nbClients ++ ;
        }
        fclose(infile);
        remove("client.txt");
        FILE *nf;
        nf = fopen("nouveau.txt", "a");
        for(i=0;i<nbClients;i++)
        {
            if (clients[i].Code_client == nvClient.Code_client)
                fwrite(&nvClient, sizeof(clients[i]), 1, nf);
            else
                fwrite(&clients[i], sizeof(clients[i]), 1, nf);
        }
        fclose(nf);
        rename("nouveau.txt", "client.txt");
    }
    else if (a==3)
    {
        struct SClient client;
        int code_supp;
        FILE *infile;

        printf("\n\n                   Code Client a supprimer: ");
        scanf("%d", &code_supp);

        infile = fopen("client.txt", "r");
        int i,nbClients = 0 ;
        while(fread(&client, sizeof(struct SClient), 1, infile)){
            clients[nbClients] = client;
            nbClients ++ ;
        }
        fclose(infile);
        remove("client.txt");
        FILE *nf;
        nf = fopen("nv.txt", "a");
        for(i=0 ; i<nbClients ; i++)
        {
            if (clients[i].Code_client !=code_supp)
                fwrite(&clients[i], sizeof(clients[i]), 1, nf);
        }
        fclose(nf);
        rename("nv.txt", "client.txt");
    }
    else if(a==4)
	{
		FILE *infile;
        struct SClient client;
        infile = fopen ("client.txt", "r");
        int code;
        printf("                        Code client a afficher : ");
        scanf("%d",&code);
        while(fread(&client, sizeof(struct SClient), 1,infile)) 
		{
	         if(client.Code_client==code)
		    {
                printf("\n                        Code Client: %d", client.Code_client);
                printf("\n                        Nom: %s %s", client.Nom, client.Prenom);
                printf("\n");
            }
        fclose (infile);
		}
	}    

    else if (a==5)
    {
        FILE *infile;
        struct SClient client;
        infile = fopen ("client.txt", "r");
        int i,start = 0 ;
        while(fread(&client, sizeof(struct SClient), 1,infile)){
            clients[start] = client;
            start ++ ;
        }
        fclose (infile);
        qsort(clients, start, sizeof(SClient), comparer);
        for ( i=0 ; i<start ; i++)
        {
            printf("\n                        Code Client: %d", clients[i].Code_client);
            printf("\n                        Nom: %s %s", clients[i].Nom, clients[i].Prenom);
            printf("\n");
        }

    }
    else if (a==6)
        menu(); 
        
    return 0;
}

int gerercompte(int a)
{
    if (a==1)
    {
        struct SCompte compte;
        struct SCompte compte0;
        FILE *infile;
        FILE *pf;
        printf("\n               Code Compte : ");
        scanf("%d", &compte.Code_compte);
        pf= fopen("compte.txt", "r");
        int found = 0;
        while(fread(&compte0, sizeof(struct SCompte), 1, pf) && found == 0) {
            if (compte0.Code_compte == compte.Code_compte)
                found = 1;
        }

        if(found == 1)
        {
            printf("\n            code existant");
            return 0;
        }
        printf("\n               Code Client: ");
        scanf("%d", &compte.Code_client);
        printf("\n               Date de creation du compte | ");
        printf("\n                                           Jour : ");
        scanf("%d",&compte.date_compte.Jour);
        printf("\n                                           Mois :");
        scanf("%d", &compte.date_compte.Mois);
        printf("\n                                           Annee : ");
        scanf("%d", &compte.date_compte.Annee);
        printf("\n               Somme : ");
        scanf("%d", &compte.somme);
        infile = fopen("compte.txt", "a");
        fwrite (&compte, sizeof(compte), 1, infile);
        if(fwrite != 0)
            printf("compte ajoute avec succes !\n");
        else
            printf("erreur! veuillez ajouter le client de nouveau !\n");

        fclose(infile);
        
    }
    else if (a==2)
    {
        struct SCompte compte;
        FILE *infile;
        int code;
        printf("\n                         Code compte a rechercher: ");
        scanf("%d", &code);

        infile = fopen("compte.txt", "r");
        int found = 0;
        while(fread(&compte, sizeof(struct SCompte), 1, infile) && found == 0) {
            if (compte.Code_compte ==code)
               {
                    printf("\n            Code compte : %d", compte.Code_compte);
                    printf("\n            Code client : %d", compte.Code_client);
                    printf("\n            Date creation: %d / %d / %d", compte.date_compte.Jour, compte.date_compte.Mois, compte.date_compte.Annee);
                    printf("\n            Somme: %d", compte.somme);
                    found = 1 ;
               }
        }
        if(found == 0)
            printf("\n                   code non existant\n");
        fclose(infile);
    }
    else if (a==3)
    {
        struct SCompte compte;
        FILE *infile;
        infile = fopen("compte.txt", "r");
        while(fread(&compte, sizeof(struct SCompte), 1, infile))
            {
                printf("\n               Code compte: %d", compte.Code_compte);
                printf("\n               Code client: %d", compte.Code_client);
                printf("\n               Date : %d/%d/%d", compte.date_compte.Jour, compte.date_compte.Mois, compte.date_compte.Annee);
                printf("\n               -----------------------------------------");
            }
        fclose(infile);
    }
    else if (a==4)
    {
        FILE *infile;
        struct SCompte compte;
        int code;
        printf("              Code Compte a supprimer : ");
        scanf("%d", &code);  
		infile = fopen("compte.txt", "r");
        int i,nb = 0;
        while(fread(&compte, sizeof(struct SCompte), 1,infile)) {
            comptes[nb] = compte;
            nb++;
        }
        fclose(infile);
        remove("compte.txt");

        FILE *nf;
        nf = fopen("nouveau.txt", "a");
        for (i=0 ; i<nb ; i++)
        {
            if (comptes[i].Code_compte != code)
                fwrite(&comptes[i], sizeof(comptes[i]), 1, nf);
        }
        fclose(nf);
        rename("nouveau.txt", "compte.txt");
    }
    else if (a==5)
        menu();
        
    return 0;
}

void gereroperation(int a)
{
    if (a==1)
    {
        struct SCompte compte;
        int code,montant;
        FILE *infile;

        printf("\n                    Code Compte : ");
        scanf("%d", &code);

        infile = fopen("compte.txt", "r");

        int i,nb = 0;

        while(fread(&compte, sizeof(struct SCompte), 1, infile)) {
            comptes[nb] = compte;
            nb++;
        }
        fclose(infile);
        remove("compte.txt");
        FILE *nf;
        nf = fopen("nouveau.txt", "a");
        for ( i=0 ; i<nb ; i++)
        {
            if (comptes[i].Code_compte == code)
            {
                do{
                    printf("\n           Montant a retirer : ");
                    scanf("%d", &montant);
                    if (montant>500)
                        printf("\n       Le montant ne doit pas depasser 500 dhs");
                    solde = comptes[i].somme - montant;
                    if (solde<50)
                        printf("\n       Le solde ne doit pas etre inferieur a 50 dhs");
                }while(montant>500 || solde<50);
                comptes[i].somme = solde;
                printf("\n                       Code compte %d", comptes[i].Code_compte);
                printf("\n                       Code client %d", comptes[i].Code_client);
                printf("\n                       Nv somme : %d", comptes[i].somme);
                printf("\n                       Date creation : %d / %d / %d", compte.date_compte.Jour, compte.date_compte.Mois, compte.date_compte.Annee);
                printf("\n                       -----------------------------------------");
            }
            fwrite(&comptes[i], sizeof(comptes[i]), 1, nf);
        }
        fclose(nf);
        rename("nouveau.txt", "compte.txt");
    }
    else if (a==2)
    {
        struct SCompte compte;
        FILE *infile;
        int code1,code2,montant;
        
        
        printf("\n                 Code Compte de depart : ");
        scanf("%d", &code1);

        printf("\n                 Code compte d'arrivee : ");
        scanf("%d", &code2);
        
        infile = fopen ("compte.txt", "r");
        int nb = 0 ;
        while(fread(&compte, sizeof(struct SCompte), 1, infile)){
            comptes[nb] = compte;
            nb ++ ;
		}
        fclose(infile);
        remove("compte.txt");
        int i;
        FILE *nf;
        nf = fopen("nouveau.txt", "a");
        for ( i=0 ; i<nb ; i++)
        {
            if (comptes[i].Code_compte == code1)
            {
                        do{
                            printf("\n                 montant : ");
                            scanf("%d", &montant);
                            if (montant>500)
                                printf("\n            le montant ne doit pas depasser 500 Dhs");
                            solde = comptes[i].somme - montant;
                            if (solde<50)
                                printf("\n            le solde ne doit pas etre inferieur a 50 Dhs");
                        }while(montant>500 || solde<50);
                comptes[i].somme = comptes[i].somme - montant;
                printf("\n                             compte depart : ");
                printf("\n                            code compte %d", comptes[i].Code_compte);
                printf("\n                            code client %d", comptes[i].Code_client);
                printf("\n                            nouvelle somme : %d", comptes[i].somme);
                printf("\n                            Date creation: %d / %d / %d", compte.date_compte.Jour, compte.date_compte.Mois, compte.date_compte.Annee);
                printf("\n                            -----------------------------------------");
            }
        }
        for ( i=0 ; i<nb ; i++)
        {
            if (comptes[i].Code_compte == code2)
            {
                comptes[i].somme = comptes[i].somme + montant;
                printf("\n                             compte d'arrivee :");
                printf("\n                            code compte: %d", comptes[i].Code_compte);
                printf("\n                            code client: %d", comptes[i].Code_client);
                printf("\n                            nouvelle somme : %d", comptes[i].somme);
                printf("\n                            Date creation: %d / %d / %d", compte.date_compte.Jour, compte.date_compte.Mois, compte.date_compte.Annee);
                printf("\n                           -----------------------------------------");
            }
            fwrite(&comptes[i], sizeof(comptes[i]), 1, nf);
        }
        fclose(nf);
        rename("nouveau.txt", "compte.txt");
    }
}
void main()
{
	printf("\n\n\n\n");
	printf("        ");printf("**************************************************************************************************");printf("\n");
	printf("        ");printf("**                                                                                              **");printf("\n");
	printf("        ");printf("**              @@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@                 **");printf("\n");
	printf("        ");printf("**              @                                                             @                 **");printf("\n");
	printf("        ");printf("**              @                                                             @                 **");printf("\n");
	printf("        ");printf("**              @                   BIENVENUE A NOTRE BANQUE ILMA             @                 **");printf("\n");
	printf("        ");printf("**              @                                                             @                 **");printf("\n");
	printf("        ");printf("**              @                                                             @                 **");printf("\n");
	printf("        ");printf("**              @@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@                 **");printf("\n");
	printf("        ");printf("**                                                                                              **");printf("\n");
	printf("        ");printf("**************************************************************************************************");printf("\n");
	printf("\n\n\n\n");
	printf("                                       <<<<<<<<<<<toucher une cle :>>>>>>>>>>>>>>>                               ");printf("\n");
	getch();
    menu();
}
