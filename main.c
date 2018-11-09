#include <stdio.h>
#include "stdlib.h"
#include "string.h"
#define BOYUT 256
#define BOYUT2 500

char olaylar[BOYUT2];
int saniye=0;
struct KAPI{
    char isim[4];
    int giris_sayisi;
    char *giris_isimleri;
    int *giris_degerleri;
    char cikis_isim;
    int cikis_degeri;
    int gecikme_suresi;
};
struct DEVRE {
    int giris_sayisi;
    int kapi_sayisi;
    int cikis_sayisi;
    char *giris_isimleri;
    int *giris_degerleri;
    char *cikis_isimleri;
    int *cikis_degerleri;
    struct KAPI *kapilar;



};


int komutcalistir(const char *komut, struct DEVRE *devre);
void kapilarisirala(struct DEVRE *devre);
int giris_var_mi(const struct  DEVRE *devre,char giris);
void devresimulasyonu(struct DEVRE *devre,char *degisecekuclar,int durum);
void kapiyicalistir(struct KAPI *kapi);
int indexbul(char *dizi,char a);

int main() {
    struct DEVRE *devre=malloc(sizeof(struct DEVRE)) ;

    devre->giris_sayisi= 3;
    devre->kapi_sayisi=3;
    devre->cikis_sayisi=1;

    devre->giris_isimleri=(char*)malloc(devre->giris_sayisi * sizeof(char));
    devre->giris_isimleri[0]='a';
    devre->giris_isimleri[1]='b';
    devre->giris_isimleri[2]='c';

    devre->giris_degerleri=(int*)malloc(devre->giris_sayisi * sizeof(int));
    devre->giris_degerleri[0]=0;
    devre->giris_degerleri[1]=0;
    devre->giris_degerleri[2]=1;

    devre->cikis_isimleri=(char*)malloc(devre->cikis_sayisi * sizeof(char));
    devre->cikis_isimleri[0]='f';

    devre->cikis_degerleri=(int*)malloc(devre->cikis_sayisi * sizeof(int));
    devre->cikis_degerleri[0]=0;

    devre->kapilar=(struct KAPI*)malloc(devre->kapi_sayisi * sizeof(struct KAPI));

    devre->kapilar[0].giris_sayisi=2;
    devre->kapilar[1].giris_sayisi=2;
    devre->kapilar[2].giris_sayisi=2;

    devre->kapilar[0].gecikme_suresi=3;
    devre->kapilar[1].gecikme_suresi=1;
    devre->kapilar[2].gecikme_suresi=1;

    strcpy(devre->kapilar[0].isim,"nor");
    strcpy(devre->kapilar[1].isim,"nand");
    strcpy(devre->kapilar[2].isim,"exor");


    devre->kapilar[0].giris_isimleri=(char*)malloc(devre->kapilar[0].giris_sayisi * sizeof(char));
    devre->kapilar[1].giris_isimleri=(char*)malloc(devre->kapilar[1].giris_sayisi * sizeof(char));
    devre->kapilar[2].giris_isimleri=(char*)malloc(devre->kapilar[2].giris_sayisi * sizeof(char));
    devre->kapilar[0].giris_degerleri=(int*)malloc(devre->kapilar[0].giris_sayisi * sizeof(int));
    devre->kapilar[1].giris_degerleri=(int*)malloc(devre->kapilar[1].giris_sayisi * sizeof(int));
    devre->kapilar[2].giris_degerleri=(int*)malloc(devre->kapilar[2].giris_sayisi * sizeof(int));

    devre->kapilar[0].giris_isimleri[0]='a';
    devre->kapilar[0].giris_isimleri[1]='b';
    devre->kapilar[0].giris_degerleri[0]=0;
    devre->kapilar[0].giris_degerleri[1]=0;

    devre->kapilar[1].giris_isimleri[0]='b';
    devre->kapilar[1].giris_isimleri[1]='c';
    devre->kapilar[1].giris_degerleri[0]=0;
    devre->kapilar[1].giris_degerleri[1]=1;

    devre->kapilar[2].giris_isimleri[0]='d';
    devre->kapilar[2].giris_isimleri[1]='e';
    devre->kapilar[2].giris_degerleri[0]=1;
    devre->kapilar[2].giris_degerleri[1]=1;

    devre->kapilar[0].cikis_isim='d';
    devre->kapilar[1].cikis_isim='e';
    devre->kapilar[2].cikis_isim='f';

    devre->kapilar[0].cikis_degeri=1;
    devre->kapilar[1].cikis_degeri=1;
    devre->kapilar[2].cikis_degeri=0;

    kapilarisirala(devre);






    printf("%c  %d   %d",devre->giris_isimleri[0],devre->giris_degerleri[1],devre->giris_degerleri[2]);
    char *komut;
    komut=(char *)malloc(sizeof(char)*BOYUT);
    do {

        printf("\n>");
        fgets(komut,BOYUT,stdin);
        komut[strlen(komut)-1]='\0'; // Stringin sonuna sonlandıra karakteri ekler.
        if(komutcalistir(komut,devre)){

        }
        else
            {
            printf("Lutfen gecerli bir komut giriniz!");
            strcpy(komut, "Hata");
        }

    } while(komut[0]!='c'&&komut[0]!='C');





    return 0;
}





int komutcalistir(const char *komut, struct DEVRE *devre){

if(komut[0]=='Y'||komut[0]=='y'){
    /*
     *
     *
     *
     *
     *
     *
     *devre.txt dosyasini
     *
     *
     *
     *
     *
     * */








    return 1;
}
else if(komut[0]=='I'||komut[0]=='i'){



    /*
     *
     *
     *
     *
     *
     * deger.txt
     *
     *
     *
     *
     * */

    return 1;
    }

else if(komut[0]=='H'||komut[0]=='h') //verilen uçları lojik-1 yapar.
{

    int uc_sayisi=0,kontrol=0;

    if(strlen(komut)==1){
        printf("Yetersiz parametre girdiniz.");
        return 0;
    }

    for (int i = 1; i <strlen(komut) ; ++i) { //uc sayisi bulunur.

        if(komut[i]==' ')continue; // bosluklar atlanir.

        kontrol=giris_var_mi(devre,komut[i]); //giris ucunun devrede bulunup bulunmadığını konrol eden fonksiyon

        if(kontrol==0)
        {
            printf("Girdiginiz giris ucu devrede bulunmamaktadir.");
            return 0;
        }
        uc_sayisi++;

    }

    char degisecekuclar[uc_sayisi];int j=0; //uc sayisi kadar eleman tutacak bir degisecekuclar dizisi olusturulur.
    degisecekuclar[uc_sayisi]='\0'; //strlen fonksiyonunun kullanımı için son karaktere '\0'(sonlandırma karakteri) değeri atandı.
    for (int i = 1; i <strlen(komut) ; ++i) //degisecekuclar dizisi komutta verilen uclar ile doldurur.
         {


        if(komut[i]==' ')continue;

        degisecekuclar[j]=komut[i];
        j++;

    }


    devresimulasyonu(devre,degisecekuclar,1);




    return 1;
}
else if(komut[0]=='L'||komut[0]=='l'){

    return 1;
}
else if(komut[0]=='S'||komut[0]=='s'){

    printf("%s",olaylar);
    strcpy(olaylar,"");
    saniye=0;
    return 1;
}
else if(komut[0]=='G'||komut[0]=='g'){

    return 1;
}
else if(komut[0]=='K'||komut[0]=='k'){

    return 1;
}
else if(komut[0]=='C'||komut[0]=='c'){

if(strlen(komut)>1)return 0;
    return 1;
}

    return 0;

}

void kapilarisirala(struct DEVRE *devre){

    struct KAPI temp;

    for (int i = 0; i < devre->kapi_sayisi; ++i) {  //Burada gecikme süresine göre kapilar siralaniyor.(Bubble Short)

        for (int j = 0; j < devre->kapi_sayisi; ++j) {

            if (devre->kapilar[i].gecikme_suresi < devre->kapilar[j].gecikme_suresi) {

                temp = devre->kapilar[i];
                devre->kapilar[i] = devre->kapilar[j];
                devre->kapilar[j] = temp;

            }

        }

    }

    //  printf("%s , %d \n%s , %d \n%s , %d \n",devre->kapilar[0].isim,devre->kapilar[0].gecikme_suresi,devre->kapilar[1].isim,devre->kapilar[1].gecikme_suresi,devre->kapilar[2].isim,devre->kapilar[2].gecikme_suresi);

}


int giris_var_mi(const struct  DEVRE *devre,char giris){

    int kontrol=0;

    for (int i = 0; i <devre->giris_sayisi ; ++i) {

        if(devre->giris_isimleri[i]==giris)kontrol++;

    }

    return kontrol;

}

void devresimulasyonu(struct DEVRE *devre,char *degisecekuclar,int durum){
 char temp[BOYUT2];

    if(durum==1) {

        for (int i = 0; i < strlen(degisecekuclar); ++i) {

            sprintf(temp,"%dns: %c %d->%d\n", saniye,devre->giris_isimleri[indexbul(devre->giris_isimleri,degisecekuclar[i])],(devre->giris_degerleri[indexbul(devre->giris_isimleri,degisecekuclar[i])]),1);
            strcat(olaylar,temp);
            saniye++;
            devre->giris_degerleri[indexbul(devre->giris_isimleri,degisecekuclar[i])]=1;
        }
        for (int j = 0; j <devre->kapi_sayisi ; ++j) {

                kapiyicalistir(&(devre->kapilar[j]));

        }



    }

}

void kapiyicalistir(struct KAPI *kapi){


if(strcmp(kapi->isim,"AND")==0||strcmp(kapi->isim,"and")==0){





}
else if(strcmp(kapi->isim,"NOR")==0||strcmp(kapi->isim,"nor")==0){





}
else if(strcmp(kapi->isim,"OR")==0||strcmp(kapi->isim,"or")==0){





}
else if(strcmp(kapi->isim,"XOR")==0||strcmp(kapi->isim,"xor")==0){





}
else if(strcmp(kapi->isim,"NAND")==0||strcmp(kapi->isim,"nand")==0){





}
else if(strcmp(kapi->isim,"NOT")==0||strcmp(kapi->isim,"not")==0){





}




}

int indexbul(char *dizi,char a){

    for (int i = 0; i <strlen(dizi) ; ++i) {
        if(dizi[i]==a)return i;
    }
    return -1;
}