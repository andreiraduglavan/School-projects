#include <iostream>
#include <string.h>
#include <vector>
#include <fstream>
#include <exception>
#include <stdexcept>
#include <stdlib.h>
#include <stdio.h>

using namespace std;

class Jucator {
private:
    const int nrcrt;
    char* nume;
    int an;
    float inaltime;
    int nretape;
    int nrEseuri;
    int* etape;
    char pozitie[100];
    bool statutJS;

public:
    static int  nrJuc, l;

    Jucator():nrcrt(l++) {

    nume=new char[strlen("Anonim")+1];
    strcpy(this->nume,"Anonim");
    an=1900;
    nrEseuri=0;
    nretape=0;
    etape=nullptr;
    strcpy(pozitie, "la");
    statutJS=true;
    nrJuc++;


    }

    Jucator(char* nume, int an, float inaltime,int nrEseuri,int nretape, int* etape, char pozitie[100], bool statuJS):nrcrt(l++) {
    this->nume=new char[strlen(nume)+1];
    strcpy(this->nume, nume);
    this->an=an;
    this->inaltime=inaltime;
    this->nretape=nretape;
    this->etape=new int[nretape];
    for(int i=0; i<nretape; i++)
        this->etape[i]=etape[i];
    this->nrEseuri=nrEseuri;
    strcpy(this->pozitie, pozitie);
    this->statutJS=statuJS;
    nrJuc++;
    }

    friend istream& operator>>(istream& in, Jucator& juc) {
        int n=1;
        while(n==1){
        cout<<"\nintroduceti numele ";
        char nume1[100];
        in>>nume1;
        try{
        if(nume1[0]=='\0') {throw 'a';}
        strcpy(juc.nume, nume1);
        n=0;
        }
        catch(char a) {
            n=1;
        }
        }
        cout<<"\nintroduceti an ";
        //int an;
        in>>juc.an;
        //juc.an=an;

        cout<<"\nintroduceti inaltimea ";
        float h;
        in>>h;
        juc.inaltime=h;

        cout<<"\nintroduceti nr de etape jucate ";
        int nr;
        in>>nr;
        juc.nretape=nr;


        cout<<"\nintroduceti etapele ";

        juc.etape=new int[nr];

        for(int i=0; i<nr; i++) {
            int et;
            in>>et;
            juc.etape[i]=et;
        }

        cout<<"\nintroduceti nr eseuri: ";
        int nr2;
        in>>nr2;
        juc.nrEseuri=nr2;

        cout<<"\nintroduceti pozitia ";
        char poz[100];
        in>>poz;
        strcpy(juc.pozitie, poz);
        cout<<"\n statut junior senior? (1/0) ";
        bool st;
        in>>st;
        juc.statutJS=st;

        return in;
    }
    friend ofstream& operator<<(ofstream& fout, const Jucator& j) {
        fout<<j.nume<<endl;
        fout<<j.an<<endl;
        fout<<j.inaltime<<endl;
        fout<<j.nrEseuri<<endl;
        fout<<j.pozitie<<endl;
        fout<<j.statutJS<<endl;

        return fout;
    }

    void afisare() {
    cout<<this->nume<<" ";
    for(int i=0; i<this->nretape; i++)
        cout<<this->etape[i]<<" ";
    cout<<" "<<this->an;
    cout<<" "<<this->inaltime;
    cout<<" "<<this->pozitie;
    cout<<" a marcat "<<nrEseuri<<" eseuri ";
    cout<<" "<<statutJS;
    }

    void setNume(char* a){

            this->nume=new char[strlen(a)+1];
            strcpy(this->nume,a);

    }
    void setInaltime(float a) {
        this->inaltime=a;

    }

    void setAn(int a) {
        this->an=a;
    }
    void setEtape(int* a, int b) {
        this->nretape=b;
        this->etape=new int(b);
        for(int i=0; i<b; i++)
            this->etape[i]=a[i];

    }

    void setPozitie(char* a) {
        strcpy(this->pozitie, a);
    }
    void setStatutJS(bool a) {
        this->statutJS=a;
    }

    char* getNume() {
        return this->nume;
    }
    int getAn(){
        return this->an;
    }
    float getInaltime() {
        return this->inaltime;

    }
    int* getEtape() {
        return this->etape;
    }
    char* getPozitie() {
        return this->pozitie;
    }
    bool getStatut() {
        return this->statutJS;
    }
    void setNrEseuri(int a) {
        this->nrEseuri=a;
    }
    int getNrEseuri() {
        return this->nrEseuri;
    }

    Jucator (const Jucator& juc):nrcrt(juc.nrcrt) {
        this->nume=new char[strlen(juc.nume)+1];
        strcpy(this->nume, juc.nume);
        this->an=juc.an;
        this->inaltime=juc.inaltime;
        strcpy(this->pozitie, juc.pozitie);

        this->nretape=juc.nretape;
        this->etape=new int[nretape];
        for(int i=0; i<nretape; i++)
            this->etape[i]=juc.etape[i];
        this->nrEseuri=juc.nrEseuri;
        this->statutJS=juc.statutJS;
    }

    Jucator &operator =(const Jucator& juc) {
        if(this!=&juc) {
                if(this->nume!=nullptr) {
                    delete[] this->nume;
                }
                this->nume=new char[strlen(juc.nume)+1];
                strcpy(this->nume, juc.nume);
                this->an=juc.an;
                this->inaltime=juc.inaltime;
                this->nretape=juc.nretape;
                if(this->etape!=nullptr)
                    delete[] this->etape;
                this->etape=new int[nretape];
                for(int i=0; i<nretape; i++)
                    this->etape[i]=juc.etape[i];
                this->nrEseuri=juc.nrEseuri;
                strcpy(this->pozitie, juc.pozitie);
                this->statutJS=juc.statutJS;

        }
        return *this;
    }
    ~Jucator() {
        if(this->nume!=nullptr)
            delete[] this-> nume;
        if(this->etape!=nullptr)
            delete[] this->etape;
    }

    Jucator& operator +(int a) {
        int etape2[100];
        if(this->etape!=nullptr) {
            for(int i=0; i<this->nretape; i++)
                etape2[i]=this->etape[i];
            delete[] this->etape;
        }
        this->nretape++;
        this->etape=new int[this->nretape];
        for(int i=0; i<this->nretape-1; i++)
            this->etape[i]=etape2[i];
        this->etape[this->nretape-1]=a;
        return *this;
    }
    void aplicaEtapa(int a) {
        int etape2[100];
        if(this->etape!=nullptr) {
            for(int i=0; i<this->nretape; i++)
                etape2[i]=this->etape[i];
            delete[] this->etape;
        }
        this->nretape++;
        this->etape=new int[this->nretape];
        for(int i=0; i<this->nretape-1; i++)
            this->etape[i]=etape2[i];
        this->etape[this->nretape-1]=a;
    }
    Jucator& operator++(int) {
        this->nrEseuri++;
        return *this;
    }
    void eseuriPlus() {
        this->nrEseuri++;
    }
    Jucator& operator-(float a) {
        this->inaltime=this->inaltime-a;
        return *this;
    }
    bool operator ==(Jucator& juc) {
        if(this->inaltime==juc.inaltime)
            {return true;}
        else
           {return false;}
    }
    bool operator <(Jucator& juc) {
        if(this->inaltime<juc.inaltime)
            {return true;}
        else
            {return false;}
    }
    bool operator >(Jucator& juc) {
        if(this->inaltime>juc.inaltime)
            {return true;}
        else
            {return false;}
    }
    explicit operator int() {
        return (int)this->inaltime;
    }
    int operator[](int i) {
        if(i>nretape-1) {
            cout<<"index out\n";
            return -1;
        }
        else{
            return this->etape[i];
        }
    }
    bool operator&&(const Jucator &juc) {
        if(this->statutJS && juc.statutJS) {
            return true;
        }
        else {
            return false;
        }
    }


};

class eseu {
private:
    Jucator* juc;
    int minut;
public:
    eseu() {
        Jucator* a;
        juc=a;
        minut=0;
    }
    eseu(Jucator* juc, int minut) {
        this->juc=juc;
        this->minut=minut;
    }
    eseu(const eseu& e) {
        this->juc=e.juc;
        this->minut=e.minut;
    }
    eseu& operator =(const eseu& e) {
        if(this!=&e) {
            this->juc=e.juc;
            this->minut=e.minut;
        }
        return *this;
    }

    //~eseu();

    void setJuc(Jucator* juc) {
        this->juc=juc;
    }
    void setMinut(int minut) {
        this->minut=minut;
    }
    Jucator* getJuc() {
        return this->juc;
    }
    int getMinut() {
        return this->minut;
    }
};

class arbitru {
private:
    char* nume;
    int varsta;
    char clasificare;
    bool licentaPro;
public:
    arbitru() {
        nume=new char[strlen("anonim")+1];
        strcpy(nume, "anonim");
        varsta=0;
        clasificare='a';
        licentaPro=false;
    }
    arbitru(char* nume, int varsta, char clasificare, bool licentaPro) {
        this->nume=new char(strlen(nume)+1);
        strcpy(this->nume, nume);
        this->varsta=varsta;
        this->clasificare=clasificare;
        this->licentaPro=licentaPro;
    }
    arbitru(const arbitru &a) {
        this->nume=new char(strlen(a.nume)+1);
        strcpy(this->nume, a.nume);
        this->varsta=a.varsta;
        this->clasificare=a.clasificare;
        this->licentaPro=a.licentaPro;
    }
    arbitru &operator=(const arbitru& a) {
        if(this!=&a) {
            this->nume=new char(strlen(a.nume)+1);
            strcpy(this->nume, a.nume);
            this->varsta=a.varsta;
            this->clasificare=a.clasificare;
            this->licentaPro=a.licentaPro;
        }
        return *this;
    }
    ~arbitru() {
        if(this->nume!=nullptr)
            delete[] this->nume;
    }
    bool operator==(const arbitru& a) {
        if(this->varsta==a.varsta)
            return true;
        else {return false;}
    }
    bool operator<(const arbitru& a) {
        if(this->varsta<a.varsta)
            return true;
        else {return false;}
    }
    bool operator &&(const arbitru& a) {
        if(this->licentaPro&&a.licentaPro)
            return true;
        else {
            return false;
        }
    }
    arbitru &operator++() {
        this->varsta++;
        return *this;
    }
    arbitru &operator+(int a) {
        this->varsta=this->varsta+a;
        return *this;
    }
    void licenta() {
        this->licentaPro=true;
    }
    char* getNume() {
        return this->nume;
    }
    int getVarsta(){
        return this->varsta;
    }
    virtual void ali()=0;
};

class Examene {
public:
    virtual void verificareVarsta()=0;
    virtual void verificareCompetenta()=0;
};

class arbitruInternational: public arbitru, public Examene {
private:
    string tara;
    int meciuriInternationale;
public:
    arbitruInternational():arbitru() {
        tara="";
        meciuriInternationale=0;
    }
    arbitruInternational(char* nume, int varsta, char clasificare, bool licentaPro, string tara, int meciuriInternationale):arbitru(nume, varsta, clasificare, licentaPro) {
        this->tara=tara;
        this->meciuriInternationale=meciuriInternationale;
    }
    void ali() {
     cout<<"ali";
    }
    void verificareCompetenta() {
        if(this->meciuriInternationale>50)
            cout<<"e competent";
        else{
            cout<<"nu e competent";
        }
    }
    void verificareVarsta(){
        if(this->getVarsta()>45) {
            cout<<"trebuie sa se pensioneze";
        }
        else {
            cout<<"nu trebuie sa se pensioneze";
        }
    }
};

class meci {
private:
    int nrjuc;
    vector<Jucator*> echipa;
    arbitruInternational arb;
    int nrtries;
    eseu* tries;
    const int etapa;
    char* antrenor;
    char stadion[100];
    float temperatura;
public:
    static int et;
    meci(): etapa(et++) {
        nrjuc=0;
        arbitruInternational a;
        arb=a;
        vector<Jucator*> ech;
        echipa=ech;
        nrtries=0;
        tries=nullptr;
        antrenor=new char[strlen("anonim")+1];
        strcpy(antrenor, "anonim");
        strcpy(stadion, "");
        temperatura=0;

    }

    meci(int nrjuc, vector<Jucator*> echipa,arbitruInternational arb,int nrtries, eseu* tries, char* antrenor, char stadion[100], float temperatura):etapa(et++) {
        this->nrjuc=nrjuc;
        this->echipa=echipa;
        this->arb=arb;
        this->nrtries=nrtries;
        this->tries=new eseu[nrtries];
        for(int i=0; i<nrtries; i++)
            this->tries[i]=tries[i];
        this->antrenor=new char[strlen(antrenor)+1];
        strcpy(this->antrenor, antrenor);
        strcpy(this->stadion, stadion);
        this->temperatura=temperatura;
    }
    meci(const meci& m):etapa(m.etapa) {
        this->nrjuc=m.nrjuc;
        this->arb=m.arb;
        this->echipa=m.echipa;
        this->nrtries=m.nrtries;
        this->tries=new eseu[m.nrtries];
        for(int i=0; i<m.nrtries; i++)
            this->tries[i]=m.tries[i];
        this->antrenor=new char[strlen(m.antrenor)+1];
        strcpy(this->antrenor, m.antrenor);
        strcpy(this->stadion, m.stadion);
        this->temperatura=m.temperatura;
    }
    ~meci() {
        if(this->tries!=nullptr)
            delete[] this->tries;
        if(this->antrenor!=nullptr)
            delete[] this->antrenor;
    }
    meci& operator=(const meci& m) {
        if(this!=&m) {
            this->nrjuc=m.nrjuc;
            this->arb=m.arb;
            this->echipa=m.echipa;
            this->nrtries=m.nrtries;
            if(this->tries!=nullptr)
                delete[] this->tries;
            this->tries=new eseu[m.nrtries];
            for(int i=0; i<m.nrtries; i++)
                this->tries[i]=m.tries[i];
            if(this->antrenor!=nullptr) {
                delete[] this->antrenor;
            }
            this->antrenor=new char[strlen(m.antrenor)+1];
            strcpy(this->antrenor, m.antrenor);
            strcpy(this->stadion, m.stadion);
            this->temperatura=m.temperatura;
        }
        return *this;
    }

    void afisare() {
        cout<<"\nEchipa este:\n";
        for(int i=0; i<this->nrjuc; i++) {
            this->echipa[i]->afisare();
            cout<<endl;
        }
        cout<<"Antrenor "<<this->antrenor<<", s-au marcat "<<this->nrtries<<" iar arbitrul a fost "<<this->arb.getNume()<<".\n\n";

    }

    void AplicaEseurileSiEtapele() {
        for(int i=0; i<this->nrtries; i++) {
            this->tries[i].getJuc()->eseuriPlus();
        }

        for(int i=0; i<this->nrjuc; i++) {
            this->echipa[i]->aplicaEtapa(etapa);
        }
    }
    void setAntrenor(char* a) {
        this->antrenor=new char[strlen(a)+1];
        strcpy(this->antrenor, a);
    }
    char* getAntrenor() {
        return this->antrenor;
    }
    void setStadion(char* a) {
        strcpy(this->stadion, a);
    }
    char* getStadion() {
        return this->stadion;
    }
    int getNrjuc() {
        return this->nrjuc;
    }
    void setNrjuc(int a) {
        this->nrjuc=a;
    }
    void setEchipa(Jucator* a) {
        for(int i=0; i<nrjuc; i++)
            this->echipa[i]=&a[i];
    }
    void setNreseuri(int a) {
        this->nrtries=a;
    }
    void setEseuri(eseu* a) {
        this->tries=new eseu[this->nrtries];
        for(int i=0;i<nrtries ; i++)
            this->tries[i]=a[i];
    }
    void setTemp(float a) {
        this->temperatura=a;
    }
    float getTemp() {
        return this->temperatura;
    }

    Jucator &operator[](int i) {
        if(this->nrjuc>i-1){
            cout<<"index out ofbounds\n";
        }
        else{
            return *this->echipa[i];
        }
    }
    meci& operator++() {
        this->temperatura++;
        return *this;
    }
    meci& operator++(int) {
        meci aux(*this);
        this->temperatura++;
        return aux;
    }
    meci& operator+(int a) {
        this->temperatura=this->temperatura+a;
        return *this;
    }
    explicit operator int() {
        return (int)this->temperatura;

    }
    bool operator==(const meci &m) {
        if(this->temperatura==m.temperatura)
            return true;
        else {
            return false;
        }
    }
    bool operator<(const meci &m) {
        if(this->temperatura<m.temperatura)
            return true;
        else {
            return false;
        }
    }
    bool operator>(const meci &m) {
        if(this->temperatura>m.temperatura)
            return true;
        else {
            return false;
        }
    }
    virtual void functievirtuala() {
        cout<<"s-a apelat in clasa baza ";
    }
    void functie() {
        cout<<"s-a apelat in clasa baza ";
    }


};

class meciPlayoff: public meci {
private:
    string runda;
    bool jucatoriSuspendati;
    int winsInSeason;
    string adversar;
public:
    meciPlayoff():meci() {
        runda="";
        jucatoriSuspendati=false;
        winsInSeason=0;
        adversar="";
    }
    meciPlayoff(string runda, bool jucatoriSuspendati, int winsInSeason, string adversar, int nrjuc, vector<Jucator*> echipa,arbitruInternational arb,int nrtries, eseu* tries, char* antrenor, char stadion[100], float temperatura):meci(nrjuc, echipa, arb, nrtries, tries, antrenor, stadion, temperatura) {
        this->runda=runda;
        this->jucatoriSuspendati=jucatoriSuspendati;
        this->winsInSeason=winsInSeason;
        this->adversar=adversar;
    }
    meciPlayoff(meci m, string runda, int winsInSeason, bool jucatoriSuspendati, string adversar):meci(m){
        this->runda=runda;
        this->winsInSeason=winsInSeason;
        this->adversar=adversar;
        this->jucatoriSuspendati=jucatoriSuspendati;
    }
    void afisare() {
        this->meci::afisare();
        if(this->jucatoriSuspendati==true){
            cout<<"ne aflam in runda "<<this->runda<<"a play off ului unde ii vom infrunta pe "<<this->adversar<<"si avem jucatori suspendati.";
        }
        else{
            cout<<"ne aflam in runda "<<this->runda<<"a play off ului unde ii vom infrunta pe "<<this->adversar<<"si nu avem jucatori suspendati.";
        }
    }
    void afiseazaAdversar(){
        cout<<this->adversar;
    }
    void functievirtuala() {
        cout<<"s-a apelat in clasa derivata";
    }
    void functie() {
        cout<<"s-a apelat in clasa derivata";
    }

};
float Fractie(float numarator, float numitor){

    if(numitor==0)
       throw runtime_error("\nNu este niciun jucator adaugat! ");

    return  (float)numarator/numitor;
}


int Jucator:: nrJuc=0;
int Jucator:: l=1;
int meci:: et=1;

int main()
{
    cout<<"RC GRIVITA\nBine ati venit!";
    int n;
    while(n!=5){
    vector<Jucator*> echipa;
    Jucator echipa1[100];
    int contor=0;
    ofstream g("data.txt", fstream::app);
    ifstream in("data.txt");
    while(true) {
        Jucator j;
        char nume[100];
        in>>nume;
        j.setNume(nume);
        int a;
        in>>a;
        j.setAn(a);
        float inaltime;
        in>>inaltime;
        j.setInaltime(inaltime);
        in>>a;
        j.setNrEseuri(a);
        in>>nume;
        j.setPozitie(nume);
        in>>a;
        if(a==1)
            j.setStatutJS(true);
        else
            j.setStatutJS(false);
        if(in.eof()){break;}
        echipa1[contor]=j;
        contor++;
    }
    for(int i=0; i<contor; i++){
        echipa.push_back(&echipa1[i]);
    }
    cout<<endl;
    cout<<"\nAlegeti o optiune:\n 1-Vizualizati echipa\n 2-Adaugati jucator\n 3-Numarul total de eseuri\n 4-Media de inaltime\n 5-iesiti din program\n\n";
    cin>>n;
    if(n==1) {
        cout<<endl;
        for(int i=0; i<echipa.size(); i++) {
            echipa[i]->afisare();
            cout<<endl;
        }
    }
    else{
        if(n==2){
            Jucator t;
            cin>>t;
            g<<t;
        }
        else {
            if(n==3) {
                int s=0;
                for(int i=0; i<echipa.size(); i++)
                    s=s+echipa[i]->getNrEseuri();
                cout<<"Numarul de eseuri este: "<<s<<endl;
            }
            else {
                if(n==4) {
                    float s=0;
                    int n=echipa.size();
                    for(int i=0; i<n; i++)
                        s=s+echipa[i]->getInaltime();
                    try{
                        s=Fractie(s,n);
                        cout<<"Media de inaltime este: "<<s<<endl;
                    }
                    catch(exception& e) {
                        cout<<e.what();
                    }
                }
            }
        }
    }
    }
    meciPlayoff ali;
    meci* ali1;
    ali1=&ali;
    ali1->functie();
    cout<<endl;
    ali1->functievirtuala();
    ali.functie();

    return 0;
}

