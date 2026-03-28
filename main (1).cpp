#include <iostream>
using namespace std;

/* =====================================================
   1. ORDONARE SIR DE CARACTERE
   ===================================================== */
void ordonare_sir_de_caractere()
{
    int n;
    char s[100];

    cout << "Numar caractere: ";
    cin >> n;

    cout << "Introduceti caracterele:\n";
    for(int i=0;i<n;i++)
        cin >> s[i];

    for(int i=0;i<n-1;i++)
        for(int j=i+1;j<n;j++)
            if(s[i] > s[j])
            {
                char aux = s[i];
                s[i] = s[j];
                s[j] = aux;
            }

    cout << "Sir ordonat: ";
    for(int i=0;i<n;i++)
        cout << s[i] << " ";
    cout << endl << endl;
}

/* =====================================================
   2. ORDONARE SIR DE CUVINTE
   ===================================================== */
int compara(char a[50], char b[50])
{
    int i=0;
    while(a[i]!='\0' && b[i]!='\0')
    {
        if(a[i] > b[i]) return 1;
        if(a[i] < b[i]) return -1;
        i++;
    }
    if(a[i]=='\0' && b[i]!='\0') return -1;
    if(a[i]!='\0' && b[i]=='\0') return 1;
    return 0;
}

void copiere(char d[50], char s[50])
{
    int i=0;
    while(s[i]!='\0') { d[i]=s[i]; i++; }
    d[i]='\0';
}

void ordonare_sir_de_cuvinte()
{
    int n;
    char v[20][50];

    cout << "Numar cuvinte: ";
    cin >> n;

    cout << "Introduceti cuvintele:\n";
    for(int i=0;i<n;i++)
        cin >> v[i];

    for(int i=0;i<n-1;i++)
        for(int j=i+1;j<n;j++)
            if(compara(v[i], v[j]) > 0)
            {
                char aux[50];
                copiere(aux, v[i]);
                copiere(v[i], v[j]);
                copiere(v[j], aux);
            }

    cout << "Cuvinte ordonate:\n";
    for(int i=0;i<n;i++)
        cout << v[i] << " ";
    cout << endl << endl;
}

/* =====================================================
   3. RADIX SORT 
   ===================================================== */
void Radix_cu_cozi()
{
    int n, v[100], max=0;

    cout << "Numar elemente: ";
    cin >> n;

    cout << "Introduceti elementele:\n";
    for(int i=0;i<n;i++)
    {
        cin >> v[i];
        if(v[i]>max) max=v[i];
    }

    int cozi[10][100];
    int dim[10];

    for(int exp=1; max/exp>0; exp*=10)
    {
        for(int i=0;i<10;i++) dim[i]=0;

        for(int i=0;i<n;i++)
        {
            int cifra = (v[i]/exp)%10;
            cozi[cifra][ dim[cifra] ] = v[i];
            dim[cifra]++;
        }

        int k=0;
        for(int i=0;i<10;i++)
            for(int j=0;j<dim[i];j++)
            {
                v[k]=cozi[i][j];
                k++;
            }
    }

    cout << "Sir ordonat: ";
    for(int i=0;i<n;i++) cout<<v[i]<<" ";
    cout << endl << endl;
}

/* =====================================================
   4. INTERCLASARE DOUA LISTE
   ===================================================== */
struct Nod
{
    int info;
    Nod* next;
};

void adauga_final(Nod* &cap, int x)
{
    Nod* p = new Nod;
    p->info = x;
    p->next = NULL;
    if(cap==NULL)
        cap=p;
    else
    {
        Nod* t=cap;
        while(t->next!=NULL) t=t->next;
        t->next=p;
    }
}

void interclasare_liste()
{
    Nod *L1=NULL, *L2=NULL, *L=NULL;
    int n,x;

    cout<<"Nr elemente lista 1 (ordonata): ";
    cin>>n;
    for(int i=0;i<n;i++){ cin>>x; adauga_final(L1,x); }

    cout<<"Nr elemente lista 2 (ordonata): ";
    cin>>n;
    for(int i=0;i<n;i++){ cin>>x; adauga_final(L2,x); }

    Nod *p1=L1, *p2=L2;
    while(p1!=NULL && p2!=NULL)
    {
        if(p1->info < p2->info){ adauga_final(L,p1->info); p1=p1->next; }
        else{ adauga_final(L,p2->info); p2=p2->next; }
    }

    while(p1!=NULL){ adauga_final(L,p1->info); p1=p1->next; }
    while(p2!=NULL){ adauga_final(L,p2->info); p2=p2->next; }

    cout<<"Lista interclasata crescator: ";
    for(Nod* p=L;p!=NULL;p=p->next) cout<<p->info<<" ";
    cout<<endl<<endl;
}

/* =====================================================
   5. LISTA CIRCULARA DUBLU INLANTUITA
   ===================================================== */
struct NodD
{
    int info;
    NodD *next, *prev;
};

void adauga_inceput(NodD* &cap, NodD* &ult, int x)
{
    NodD* p = new NodD;
    p->info = x;
    if(cap==NULL){ cap=ult=p; p->next=p->prev=p; }
    else
    {
        p->next=cap; p->prev=ult;
        cap->prev=p; ult->next=p;
        cap=p;
    }
}

void adauga_final(NodD* &cap, NodD* &ult, int x)
{
    NodD* p = new NodD;
    p->info=x;
    if(cap==NULL){ cap=ult=p; p->next=p->prev=p; }
    else
    {
        p->next=cap; p->prev=ult;
        ult->next=p; cap->prev=p;
        ult=p;
    }
}

void adauga_dupa(NodD* cap, NodD* &ult, int val, int x)
{
    if(cap==NULL) return;
    NodD* p=cap;
    do{
        if(p->info==val)
        {
            NodD* q = new NodD;
            q->info=x;
            q->next=p->next; q->prev=p;
            p->next->prev=q; p->next=q;
            if(p==ult) ult=q;
            return;
        }
        p=p->next;
    }while(p!=cap);
}

void sterge_inceput(NodD* &cap, NodD* &ult)
{
    if(cap==NULL) return;
    if(cap==ult){ delete cap; cap=ult=NULL; }
    else{ NodD* p=cap; cap=cap->next; cap->prev=ult; ult->next=cap; delete p; }
}

void sterge_final(NodD* &cap, NodD* &ult)
{
    if(cap==NULL) return;
    if(cap==ult){ delete cap; cap=ult=NULL; }
    else{ NodD* p=ult; ult=ult->prev; ult->next=cap; cap->prev=ult; delete p; }
}

void sterge_element(NodD* &cap, NodD* &ult, int val)
{
    if(cap==NULL) return;
    NodD* p=cap;
    do{
        if(p->info==val)
        {
            if(p==cap) sterge_inceput(cap,ult);
            else if(p==ult) sterge_final(cap,ult);
            else{ p->prev->next=p->next; p->next->prev=p->prev; delete p; }
            return;
        }
        p=p->next;
    }while(p!=cap);
}

void modifica_element(NodD* cap, int vechi, int nou)
{
    if(cap==NULL) return;
    NodD* p=cap;
    do{ if(p->info==vechi) { p->info=nou; return; } p=p->next; }while(p!=cap);
}

void parcurgere_inainte(NodD* cap)
{
    if(cap==NULL){ cout<<"Lista vida\n"; return; }
    NodD* p=cap;
    do{ cout<<p->info<<" "; p=p->next; }while(p!=cap);
    cout<<endl;
}

void parcurgere_inapoi(NodD* ult)
{
    if(ult==NULL){ cout<<"Lista vida\n"; return; }
    NodD* p=ult;
    do{ cout<<p->info<<" "; p=p->prev; }while(p!=ult);
    cout<<endl;
}

void lista_circulara()
{
    NodD *cap=NULL, *ult=NULL;
    int x,val,op;

    cout<<"\n--- Adauga primul element ---\nValoare: ";
    cin>>x;
    adauga_final(cap,ult,x);

    do{
        cout<<"\n--- MENIU LISTA CIRCULARA DUBLA ---\n";
        cout<<"1. Adauga la inceput\n2. Adauga la final\n3. Adauga dupa un element\n";
        cout<<"4. Sterge de la inceput\n5. Sterge de la final\n6. Sterge un element dat\n";
        cout<<"7. Modifica un element\n8. Parcurgere inainte\n9. Parcurgere inapoi\n0. Iesire\n";
        cout<<"Optiune: "; cin>>op;

        switch(op)
        {
            case 1: cout<<"Valoare: "; cin>>x; adauga_inceput(cap,ult,x); break;
            case 2: cout<<"Valoare: "; cin>>x; adauga_final(cap,ult,x); break;
            case 3: cout<<"Dupa ce valoare? "; cin>>val; cout<<"Valoare noua: "; cin>>x; adauga_dupa(cap,ult,val,x); break;
            case 4: sterge_inceput(cap,ult); break;
            case 5: sterge_final(cap,ult); break;
            case 6: cout<<"Valoare de sters: "; cin>>x; sterge_element(cap,ult,x); break;
            case 7: cout<<"Element de modificat: "; cin>>val; cout<<"Noua valoare: "; cin>>x; modifica_element(cap,val,x); break;
            case 8: parcurgere_inainte(cap); break;
            case 9: parcurgere_inapoi(ult); break;
        }

    }while(op!=0);
}

/* =====================================================
   6. REUNIUNE SI INTERSECTIE
   ===================================================== */
void reuniune_intersectie()
{
    int A[50],B[50],n,m;
    cout<<"Nr elem A: "; cin>>n; for(int i=0;i<n;i++) cin>>A[i];
    cout<<"Nr elem B: "; cin>>m; for(int i=0;i<m;i++) cin>>B[i];

    cout<<"Reuniune: ";
    for(int i=0;i<n;i++) cout<<A[i]<<" ";
    for(int j=0;j<m;j++){ int ok=1; for(int i=0;i<n;i++) if(B[j]==A[i]) ok=0; if(ok==1) cout<<B[j]<<" "; }

    cout<<"\nIntersectie: ";
    for(int i=0;i<n;i++) for(int j=0;j<m;j++) if(A[i]==B[j]) cout<<A[i]<<" ";
    cout<<endl<<endl;
}

/* =====================================================
   7. ARBORI BINARI 
   ===================================================== */
struct NodA
{
    int info;
    NodA* st;
    NodA* dr;
};

NodA* inserare(NodA* rad,int x)
{
    if(rad==NULL){ NodA* p=new NodA; p->info=x; p->st=p->dr=NULL; return p; }
    if(x<rad->info) rad->st=inserare(rad->st,x);
    else rad->dr=inserare(rad->dr,x);
    return rad;
}

NodA* minim(NodA* rad){ while(rad->st!=NULL) rad=rad->st; return rad; }

NodA* stergere(NodA* rad,int x)
{
    if(rad==NULL) return NULL;
    if(x<rad->info) rad->st=stergere(rad->st,x);
    else if(x>rad->info) rad->dr=stergere(rad->dr,x);
    else
    {
        if(rad->st==NULL && rad->dr==NULL){ delete rad; return NULL; }
        else if(rad->st==NULL){ NodA* aux=rad->dr; delete rad; return aux; }
        else if(rad->dr==NULL){ NodA* aux=rad->st; delete rad; return aux; }
        else{ NodA* aux=minim(rad->dr); rad->info=aux->info; rad->dr=stergere(rad->dr,aux->info); }
    }
    return rad;
}

void modifica_nod(NodA* rad,int vechi,int nou)
{
    if(rad==NULL) return;
    if(rad->info==vechi) rad->info=nou;
    modifica_nod(rad->st,vechi,nou); modifica_nod(rad->dr,vechi,nou);
}

// Parcurgeri
void RSD(NodA* rad){ if(rad!=NULL){ cout<<rad->info<<" "; RSD(rad->st); RSD(rad->dr); } } // Pre-order
void SRD(NodA* rad){ if(rad!=NULL){ SRD(rad->st); cout<<rad->info<<" "; SRD(rad->dr); } } // In-order redenumit
void SDR(NodA* rad){ if(rad!=NULL){ SDR(rad->st); SDR(rad->dr); cout<<rad->info<<" "; } } // Post-order redenumit

void meniu_arbori()
{
    NodA* rad=NULL; int opt,val,nou;
    do{
        cout<<"\n--- MENIU ARBORI BINARI ---\n";
        cout<<"1. Inserare nod\n2. Stergere nod\n3. Modificare nod\n";
        cout<<"4. Parcurgere Pre-order (RSD)\n5. Parcurgere In-order (SRD)\n6. Parcurgere Post-order (SDR)\n0. Iesire\n";
        cout<<"Optiune: "; cin>>opt;
        switch(opt)
        {
            case 1: cout<<"Valoare de inserat: "; cin>>val; rad=inserare(rad,val); break;
            case 2: cout<<"Valoare de sters: "; cin>>val; rad=stergere(rad,val); break;
            case 3: cout<<"Valoare de modificat: "; cin>>val; cout<<"Noua valoare: "; cin>>nou; modifica_nod(rad,val,nou); break;
            case 4: RSD(rad); cout<<endl; break;
            case 5: SRD(rad); cout<<endl; break;
            case 6: SDR(rad); cout<<endl; break;
        }
    }while(opt!=0);
}

/* =====================================================
   MAIN
   ===================================================== */
int main()
{
    int optiune=1;
    do
    {
        cout<<"\n--- PROIECT STRUCTURI DE DATE ---\n";
        cout<<"1. Ordonare sir de caractere\n2. Ordonare sir de cuvinte\n3. Radix Sort\n4. Interclasare liste\n";
        cout<<"5. Lista circulara dubla\n6. Reuniune si intersectie\n7. Arbori binari\n0. Terminare\n";
        cout<<"Scrieti optiune: "; cin>>optiune;

        switch(optiune)
        {
            case 1: ordonare_sir_de_caractere(); break;
            case 2: ordonare_sir_de_cuvinte(); break;
            case 3: Radix_cu_cozi(); break;
            case 4: interclasare_liste(); break;
            case 5: lista_circulara(); break;
            case 6: reuniune_intersectie(); break;
            case 7: meniu_arbori(); break;
            case 0: cout<<"La revedere!\n"; break;
            default: cout<<"Optiune invalida!\n";
        }
    }while(optiune!=0);

    return 0;
}
