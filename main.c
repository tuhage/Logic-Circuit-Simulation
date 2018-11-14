#include <stdio.h>
#include "stdlib.h"
#include "string.h"
#include "time.h"
#include "ctype.h"

#define BOYUT 256
#define BOYUT2 500
#define KOMUTBOYUT 100
#define SATIRBOYUT 100

struct KAPI{
    char isim[5];
    int giris_sayisi;
    char *giris_isimleri;
    int *giris_degerleri;
    char cikis_isim;
    int cikis_degeri;
    int gecikme_suresi;
    int sure;
    int acikkapali;
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

struct DEVRE *devre ;
char olaylar[BOYUT2];
int saniye=0;

time_t t;          //     -__Kaynak__- (log.txt içine tarih yazmak için kullanıldı)
struct tm zaman;  // https://stackoverflow.com/questions/1442116/how-to-get-the-date-and-time-values-in-a-c-program

FILE *log;

int komutcalistir(const char *komut);
void kapilarisirala();
void kapilarisirala2();
int giris_var_mi(char giris);
int uc_var_mi(char giris);
int birdenfazlakontrolu(char *uclar);
void arabulyaz(char *uclar);
void devresimulasyonu(char *degisecekuclar,int durum);
void saniyeayarlama(struct KAPI *kapi);
void OnOff(char isim,int onoff);
int kapiyicalistir(struct KAPI *kapi);
int indexbul(char *dizi,char a);
void degerdegistir(char isim,int yenideger);
void kapisayisibul(FILE *devredosyasi);
void Ykomutu_satirislem(const char * satir);

int main() {

    devre=malloc(sizeof(struct DEVRE));










    char *komut;
    komut=(char *)malloc(sizeof(char)*BOYUT);

    t=time(NULL);
    zaman=*localtime(&t);
    printf("%d/%d/%d-%d:%d:%d\n", zaman.tm_year + 1900, zaman.tm_mon + 1, zaman.tm_mday, zaman.tm_hour, zaman.tm_min, zaman.tm_sec);


    if(!(log=fopen("log.txt","w+"))){
        printf("Log dosyasi acilamadi.");
    }
    fprintf(log,"       Zaman                  Komut                 Cikti\n");
    fprintf(log,"------------------         -------------         ------------------------\n");

    do {

        printf("\n>");
        fgets(komut,BOYUT,stdin);
        komut[strlen(komut)-1]='\0'; // Stringin sonuna sonlandıra karakteri ekler.
        if(komutcalistir(komut)){

        }
        else
        {
            fprintf(log,"Lutfen gecerli bir komut giriniz!\n");
            printf("Lutfen gecerli bir komut giriniz!");
            strcpy(komut, "Hata");
        }

    } while(komut[0]!='c'&&komut[0]!='C');



    fclose(log);
    free(komut);
    free(devre);
    return 0;
}





int komutcalistir(const char *komut){

    if(komut[0]=='Y'||komut[0]=='y'){
        // y komutunun basi

        t = time(NULL);
        zaman = *localtime(&t);

        fprintf(log, "%d/%d/%d-%d:%d:%-10d %-21s ", zaman.tm_year + 1900, zaman.tm_mon + 1, zaman.tm_mday,
                zaman.tm_hour, zaman.tm_min, zaman.tm_sec, komut);


        char dosyaadi[strlen(komut)-1],satir[SATIRBOYUT];int k=0;

        if(komut[1]!=' ')return 0;

        for (int i = 2; i <strlen(komut) ; ++i) {
            dosyaadi[k]=komut[i];
            k++;
        }
        dosyaadi[k]='\0';

        FILE *devredosyasi;

        if(!(devredosyasi=fopen(dosyaadi,"r"))){
            fprintf(log,"Dosya acilamadi.\n");
            printf("Dosya acilamadi.");return 0;
        }else fprintf(log,"devre dosyasi alindi.\n");


        kapisayisibul(devredosyasi);
        rewind(devredosyasi);//devrenin basina donuyor.

        while(fgets(satir,SATIRBOYUT,devredosyasi)!=NULL){

            if(satir[strlen(satir)-1]=='\n')
                satir[strlen(satir)-1]='\0';
            for (int i = 0; i <strlen(satir) ; ++i) {
                if(satir[i]=='\t')satir[i]=' ';
            }






            if(strcmp(satir,"")==0)continue;

            Ykomutu_satirislem(satir);



        }








        return 1;
    }
    else if(komut[0]=='I'||komut[0]=='i'){

// i komutunun basi

        t = time(NULL);
        zaman = *localtime(&t);

        fprintf(log, "%d/%d/%d-%d:%d:%-10d %-21s ", zaman.tm_year + 1900, zaman.tm_mon + 1, zaman.tm_mday,
                zaman.tm_hour, zaman.tm_min, zaman.tm_sec, komut);


        char dosyaadi[strlen(komut)-1],satir[SATIRBOYUT];int k=0;

        if(komut[1]!=' ')return 0;

        for (int i = 2; i <strlen(komut) ; ++i) {
            dosyaadi[k]=komut[i];
            k++;
        }
        dosyaadi[k]='\0';

        FILE *devredosyasi;

        if(!(devredosyasi=fopen(dosyaadi,"r"))){
            fprintf(log,"Dosya acilamadi.\n");
            printf("Dosya acilamadi.");return 0;
        }else fprintf(log,"degerler dosyasi alindi.\n");




        while(fgets(satir,SATIRBOYUT,devredosyasi)!=NULL){

            if(satir[strlen(satir)-1]=='\n')
                satir[strlen(satir)-1]='\0';
            for (int i = 0; i <strlen(satir) ; ++i) {
                if(satir[i]=='\t')satir[i]=' ';
            }






            if(strcmp(satir,"")==0)continue;


            //printf("%c%d==\n",satir[0],atoi(satir+2));

            degerdegistir(satir[0],atoi(satir+2));





        }





        kapilarisirala();





        return 1;
    }

    else if(komut[0]=='H'||komut[0]=='h') //verilen uçları lojik-1 yapar.
    {
        //h komutunun başı

        t = time(NULL);
        zaman = *localtime(&t);

        fprintf(log, "%d/%d/%d-%d:%d:%-10d %-21s ", zaman.tm_year + 1900, zaman.tm_mon + 1, zaman.tm_mday,
                zaman.tm_hour, zaman.tm_min, zaman.tm_sec, komut);



        int uc_sayisi = 0, kontrol = 0;

        if (strlen(komut) == 1) {
            printf("Yetersiz parametre girdiniz.");
            fprintf(log,"Yetersiz parametre girdiniz.");
            return 0;
        }

        for (int i = 1; i < strlen(komut); ++i) { //uc sayisi bulunur.

            if (komut[i] == ' ' || komut[i] == '\t')continue; // bosluklar atlanir.

            kontrol = giris_var_mi(komut[i]); //giris ucunun devrede bulunup bulunmadığını konrol eden fonksiyon
            if (kontrol == 0) {
                fprintf(log,"Girdiginiz giris ucu devrede bulunmamaktadir.");
                printf("Girdiginiz giris ucu devrede bulunmamaktadir.");
                return 0;
            }
            uc_sayisi++;

        }
        if(uc_sayisi==0){
            printf("Yetersiz parametre girdiniz.");
            fprintf(log,"Yetersiz parametre girdiniz.");
            return 0;
        }
        char degisecekuclar[uc_sayisi];
        int j = 0; //uc sayisi kadar eleman tutacak bir degisecekuclar dizisi olusturulur.
        degisecekuclar[uc_sayisi] = '\0'; //strlen fonksiyonunun kullanımı için son karaktere '\0'(sonlandırma karakteri) değeri atandı.
        for (int i = 1; i < strlen(komut); ++i) //degisecekuclar dizisi komutta verilen uclar ile doldurur.
        {


            if (komut[i] == ' ' || komut[i] == '\t')continue;

            degisecekuclar[j] = komut[i];
            j++;

        }
        if (birdenfazlakontrolu(degisecekuclar)) {
            fprintf(log,"Aynı uç birden fazla girilemez.");
            printf("Aynı uç birden fazla girilemez.");
            return 0;
        }


        devresimulasyonu(degisecekuclar, 1);


        if (strlen(degisecekuclar) == 1) {

            fprintf(log, "%s girisi birlendi\n",degisecekuclar);
        }else{
            fprintf(log, "%s girisleri birlendi\n",degisecekuclar);

        }


// h komutunun sonu
        return 1;
    }
    else if(komut[0]=='L'||komut[0]=='l'){  // verilen uçları lojik 0 yapar.

        //l komutunun başı

        t = time(NULL);
        zaman = *localtime(&t);

        fprintf(log, "%d/%d/%d-%d:%d:%-10d %-21s ", zaman.tm_year + 1900, zaman.tm_mon + 1, zaman.tm_mday,
                zaman.tm_hour, zaman.tm_min, zaman.tm_sec, komut);


        int uc_sayisi=0,kontrol=0;

        if(strlen(komut)==1){
            fprintf(log,"Yetersiz parametre girdiniz.");
            printf("Yetersiz parametre girdiniz.");
            return 0;
        }

        for (int i = 1; i <strlen(komut) ; ++i) { //uc sayisi bulunur.

            if(komut[i]==' '||komut[i]=='\t')continue; // bosluklar atlanir.

            kontrol=giris_var_mi(komut[i]); //giris ucunun devrede bulunup bulunmadığını konrol eden fonksiyon

            if(kontrol==0)
            {
                fprintf(log,"Girdiginiz giris ucu devrede bulunmamaktadir.");
                printf("Girdiginiz giris ucu devrede bulunmamaktadir.");
                return 0;
            }
            uc_sayisi++;

        }

        if(uc_sayisi==0){
            printf("Yetersiz parametre girdiniz.");
            fprintf(log,"Yetersiz parametre girdiniz.");
            return 0;
        }

        char degisecekuclar[uc_sayisi];int j=0; //uc sayisi kadar eleman tutacak bir degisecekuclar dizisi olusturulur.
        degisecekuclar[uc_sayisi]='\0'; //strlen fonksiyonunun kullanımı için son karaktere '\0'(sonlandırma karakteri) değeri atandı.
        for (int i = 1; i <strlen(komut) ; ++i) //degisecekuclar dizisi komutta verilen uclar ile doldurur.
        {


            if(komut[i]==' '||komut[i]=='\t')continue;

            degisecekuclar[j]=komut[i];
            j++;

        }
        if(birdenfazlakontrolu(degisecekuclar)){
            fprintf(log,"Aynı uç birden fazla girilemez.");
            printf("Aynı uç birden fazla girilemez.");
            return 0;
        }



        devresimulasyonu(degisecekuclar,0);

        if (strlen(degisecekuclar) == 1) {

            fprintf(log, "%s girisi sıfırlandı\n",degisecekuclar);
        }else{
            fprintf(log, "%s girisleri sıfırlandı\n",degisecekuclar);

        }

        //l komutunun sonu
        return 1;
    }
    else if(komut[0]=='S'||komut[0]=='s'){ //gerçekleşen olayları yazar.
        //s komutunun başı

        char temp[BOYUT2];int k=0,k1=0;

        t = time(NULL);
        zaman = *localtime(&t);

        fprintf(log, "%d/%d/%d-%d:%d:%-10d %-21s ", zaman.tm_year + 1900, zaman.tm_mon + 1, zaman.tm_mday,
                zaman.tm_hour, zaman.tm_min, zaman.tm_sec, komut);

        for (int i = 0; i <strlen(olaylar) ; ++i) {

            if(olaylar[i]!='\n'){

                temp[k]=olaylar[i];
                k++;
            }else{
                if(k1==0){
                    fprintf(log,"%s\n",temp);
                    k1++;
                    strcpy(temp,"");
                    k=0;
                    continue;
                }
                fprintf(log,"%49s%s\n","",temp);
                strcpy(temp,"");
                k=0;
            }

        }
        printf("%s",olaylar);
        strcpy(olaylar,"");
        saniye=0;
        return 1;
    }
    else if(komut[0]=='G'||komut[0]=='g')
    {
        //g komutunun başı


        fprintf(log, "%d/%d/%d-%d:%d:%-10d %-21s ", zaman.tm_year + 1900, zaman.tm_mon + 1, zaman.tm_mday,
                zaman.tm_hour, zaman.tm_min, zaman.tm_sec, komut);


        int uc_sayisi=0,kontrol=0;

        if(komut[1]=='*'&&strlen(komut)>2){
            return 0;
        }
        else if(komut[1]=='*'){

            arabulyaz("all");
            return 1;
        }


        if(strlen(komut)==1){
            fprintf(log,"Yetersiz parametre girdiniz.");
            printf("Yetersiz parametre girdiniz.");
            return 0;
        }

        for (int i = 1; i <strlen(komut) ; ++i) { //uc sayisi bulunur.

            if(komut[i]==' '||komut[i]=='\t')continue; // bosluklar atlanir.

            kontrol=uc_var_mi(komut[i]); //giris ucunun devrede bulunup bulunmadığını konrol eden fonksiyon

            if(kontrol==0)
            {
                fprintf(log,"Girdiginiz uc devrede bulunmamaktadir.");
                printf("Girdiginiz uc devrede bulunmamaktadir.");
                return 0;
            }
            uc_sayisi++;

        }

        char uclar[uc_sayisi];int j=0; //uc sayisi kadar eleman tutacak bir uclar dizisi olusturulur.
        uclar[uc_sayisi]='\0'; //strlen fonksiyonunun kullanımı için son karaktere '\0'(sonlandırma karakteri) değeri atandı.
        for (int i = 1; i <strlen(komut) ; ++i) //degisecekuclar dizisi komutta verilen uclar ile doldurur.
        {


            if(komut[i]==' '||komut[i]=='\t')continue;

            uclar[j]=komut[i];
            j++;

        }


        arabulyaz(uclar);


        return 1;

        //g komutunun sonu
    }
    else if(komut[0]=='K'||komut[0]=='k'){

        //k komutunun başı
        t = time(NULL);
        zaman = *localtime(&t);

        fprintf(log, "%d/%d/%d-%d:%d:%-10d %-21s ", zaman.tm_year + 1900, zaman.tm_mon + 1, zaman.tm_mday,
                zaman.tm_hour, zaman.tm_min, zaman.tm_sec, komut);


        char dosyaadi[strlen(komut)-1],komut2[KOMUTBOYUT]; int k=0;

        if(komut[1]!=' ')return 0;

        for (int i = 2; i <strlen(komut) ; ++i) {
            dosyaadi[k]=komut[i];
            k++;
        }
        dosyaadi[k]='\0';

        FILE *komutdosyasi;

        if(!(komutdosyasi=fopen(dosyaadi,"r"))){
            fprintf(log,"Dosya acilamadi.\n");
            printf("Dosya acilamadi.");return 0;
        }else fprintf(log,"komut dosyasi alindi.\n");



        while(fgets(komut2,KOMUTBOYUT,komutdosyasi)!=NULL){

            if(komut2[strlen(komut2)-1]=='\n')
                komut2[strlen(komut2)-1]='\0';
            for (int i = 0; i <strlen(komut2) ; ++i) {
                if(komut2[i]=='\t')komut2[i]=' ';
            }
            if(strcmp(komut2,"")==0)continue;
            printf("\n>%s\n",komut2);

            komutcalistir(komut2);


        }







        //k komutunun sonu

        return 1;
    }
    else if(komut[0]=='C'||komut[0]=='c'){

        t = time(NULL);
        zaman = *localtime(&t);

        fprintf(log, "%d/%d/%d-%d:%d:%-10d %-21s program sonlandirildi", zaman.tm_year + 1900, zaman.tm_mon + 1, zaman.tm_mday,
                zaman.tm_hour, zaman.tm_min, zaman.tm_sec, komut);

        if(strlen(komut)>1)return 0;
        exit(1);
    }

    t = time(NULL);
    zaman = *localtime(&t);

    fprintf(log, "%d/%d/%d-%d:%d:%-10d %-21s ", zaman.tm_year + 1900, zaman.tm_mon + 1, zaman.tm_mday,
            zaman.tm_hour, zaman.tm_min, zaman.tm_sec, komut);

    return 0;

}

void kapilarisirala(){

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
void kapilarisirala2(){

    struct KAPI temp;

    for (int i = 0; i < devre->kapi_sayisi; ++i) {  //Burada gecikme süresine göre kapilar siralaniyor.(Bubble Short)

        for (int j = 0; j < devre->kapi_sayisi; ++j) {

            if (devre->kapilar[i].sure < devre->kapilar[j].sure) {

                temp = devre->kapilar[i];
                devre->kapilar[i] = devre->kapilar[j];
                devre->kapilar[j] = temp;

            }

        }

    }

    //  printf("%s , %d \n%s , %d \n%s , %d \n",devre->kapilar[0].isim,devre->kapilar[0].gecikme_suresi,devre->kapilar[1].isim,devre->kapilar[1].gecikme_suresi,devre->kapilar[2].isim,devre->kapilar[2].gecikme_suresi);

}


int giris_var_mi(char giris){

    int kontrol=0;

    for (int i = 0; i <devre->giris_sayisi ; ++i) {

        if(devre->giris_isimleri[i]==giris)kontrol++;

    }

    return kontrol;

}

int uc_var_mi(char giris){

    int kontrol=0;
    for (int i = 0; i <devre->giris_sayisi ; ++i) {
        if(devre->giris_isimleri[i]==giris)kontrol++;
    }
    for (int j = 0; j <devre->kapi_sayisi ; ++j) {
        if(devre->kapilar[j].cikis_isim==giris)kontrol++;
    }

    return kontrol;


}
int birdenfazlakontrolu(char *uclar){

    for (int i = 0; i <strlen(uclar) ; ++i) {
        for (int j = i+1; j <strlen(uclar) ; ++j) {

            if(uclar[i]==uclar[j])return 1;

        }



    }
    return 0;




}

void arabulyaz(char *uclar){

    if(strcmp(uclar,"all")==0){

        for (int j = 0; j <devre->giris_sayisi ; ++j) {
            printf("%c: %d\n",devre->giris_isimleri[j],devre->giris_degerleri[j]);

            if(j==0)fprintf(log,"%c: %d\n",devre->giris_isimleri[j],devre->giris_degerleri[j]);
            else fprintf(log,"%50c: %d\n",devre->giris_isimleri[j],devre->giris_degerleri[j]);
        }

        for (int j = 0; j <devre->kapi_sayisi ; ++j) {

            printf("%c: %d\n",devre->kapilar[j].cikis_isim,devre->kapilar[j].cikis_degeri);
            fprintf(log,"%50c: %d\n",devre->kapilar[j].cikis_isim,devre->kapilar[j].cikis_degeri);

        }

        return;
    }
    int k=0;
    for (int i = 0; i <strlen(uclar) ; ++i) {
        for (int j = 0; j <devre->giris_sayisi ; ++j) {

            if(uclar[i]==devre->giris_isimleri[j]){

                printf("%c: %d\n",uclar[i],devre->giris_degerleri[j]);
                if(k==0){
                    fprintf(log,"%c: %d\n",uclar[i],devre->giris_degerleri[j]);
                    k++;
                }else fprintf(log,"%50c: %d\n",uclar[i],devre->giris_degerleri[j]);
            }
        }
    }

    for (int i = 0; i <strlen(uclar) ; ++i) {
        for (int j = 0; j <devre->kapi_sayisi ; ++j) {

            if(uclar[i]==devre->kapilar[j].cikis_isim){

                printf("%c: %d\n",uclar[i],devre->kapilar[j].cikis_degeri);
                if(k==0){
                    fprintf(log,"%c: %d\n",uclar[i],devre->kapilar[j].cikis_degeri);
                    k++;
                }else fprintf(log,"%50c: %d\n",uclar[i],devre->kapilar[j].cikis_degeri);
            }
        }
    }

}

void devresimulasyonu(char *degisecekuclar,int durum){
    char temp[BOYUT];int kontrol=0;

    if(durum==1) {

        for (int i = 0; i < strlen(degisecekuclar); ++i) {

            sprintf(temp,"%dns: %c %d->%d\n", saniye,devre->giris_isimleri[indexbul(devre->giris_isimleri,degisecekuclar[i])],(devre->giris_degerleri[indexbul(devre->giris_isimleri,degisecekuclar[i])]),1);
            strcat(olaylar,temp);
            //  saniye++;  ilk atamada saniye değeri hep 0 fakat bu yorum satırı kaldırılırsa değer arttırılır.
            degerdegistir(degisecekuclar[i],1);
            OnOff(degisecekuclar[i],1);

        }


        for (int j = 0; j <devre->kapi_sayisi ; ++j) {

            if(!(devre->kapilar[j].acikkapali==0)){
                if(kapiyicalistir(&(devre->kapilar[j]))){
                    kontrol++;
                    kapilarisirala2();
                    j=-1;
                }}


        }

    }
    else
    {

        for (int i = 0; i < strlen(degisecekuclar); ++i) {

            sprintf(temp,"%dns: %c %d->%d\n", saniye,devre->giris_isimleri[indexbul(devre->giris_isimleri,degisecekuclar[i])],(devre->giris_degerleri[indexbul(devre->giris_isimleri,degisecekuclar[i])]),0);
            strcat(olaylar,temp);
            //  saniye++;  ilk atamada saniye değeri hep 0 fakat bu yorum satırı kaldırılırsa değer arttırılır.
            degerdegistir(degisecekuclar[i],0);
            OnOff(degisecekuclar[i],1);

        }


        for (int j = 0; j <devre->kapi_sayisi ; ++j) {

            if(!(devre->kapilar[j].acikkapali==0)){
                if(kapiyicalistir(&(devre->kapilar[j]))){
                    kontrol++;
                    kapilarisirala2();
                    j=-1;
                }}



        }



    }

}

void saniyeayarlama(struct KAPI *kapi){
    //printf("***1***-%s kapısı = %d süre = %d saniye= %d\n",kapi->isim,kapi->acikkapali,kapi->sure,saniye);

    saniye+=kapi->sure;
    int kapisure=kapi->sure;


    for (int i = 0; i <devre->kapi_sayisi; ++i) {
        // printf("1 - kapi ismi = %s acikkapali = %d kapinin süresi = %d \n",devre->kapilar[i].isim,devre->kapilar[i].acikkapali,devre->kapilar[i].sure);
        if(devre->kapilar[i].acikkapali==1)
            devre->kapilar[i].sure-=kapisure;
        // printf("2 - kapi ismi = %s acikkapali = %d kapinin süresi = %d \n\n",devre->kapilar[i].isim,devre->kapilar[i].acikkapali,devre->kapilar[i].sure);
    }


    //   printf("***2***-%s kapısı = %d süre = %d saniye=%d\n\n",kapi->isim,kapi->acikkapali,kapi->sure,saniye);

}

void OnOff(char isim,int onoff){


    for (int i = 0; i <devre->kapi_sayisi ; ++i) {
        if(indexbul(devre->kapilar[i].giris_isimleri,isim)!=-1)
            devre->kapilar[i].acikkapali=onoff;

    }




}

int kapiyicalistir(struct KAPI *kapi){ // kapıyı çalışıtırır mantıksal işlemleri yapar ve kapının çıkış değerini değiştirir.

    char temp[BOYUT];int sonuc=kapi->giris_degerleri[0], deger=kapi->cikis_degeri;


    if(strcmp(kapi->isim,"AND")==0||strcmp(kapi->isim,"and")==0){

        for (int i = 1; i <kapi->giris_sayisi ; ++i) {
            sonuc*=kapi->giris_degerleri[i];
        }



        if(sonuc==0)degerdegistir(kapi->cikis_isim,0);
        else degerdegistir(kapi->cikis_isim,1);


        saniyeayarlama(kapi);
        OnOff(kapi->cikis_isim,1);

        kapi->acikkapali=0;
        kapi->sure=kapi->gecikme_suresi;
        sprintf(temp,"%dns: %c %d->%d\n", saniye,kapi->cikis_isim,deger,kapi->cikis_degeri);
        strcat(olaylar,temp);
        //saniye++;

        return 1;
    }
    else if(strcmp(kapi->isim,"NOR")==0||strcmp(kapi->isim,"nor")==0){


        for (int i = 1; i <kapi->giris_sayisi ; ++i) {
            sonuc+=kapi->giris_degerleri[i];
        }



        if(sonuc==0)degerdegistir(kapi->cikis_isim,1);
        else degerdegistir(kapi->cikis_isim,0);



        saniyeayarlama(kapi);
        OnOff(kapi->cikis_isim,1);

        kapi->acikkapali=0;
        kapi->sure=kapi->gecikme_suresi;

        sprintf(temp,"%dns: %c %d->%d\n", saniye,kapi->cikis_isim,deger,kapi->cikis_degeri);
        strcat(olaylar,temp);
        // saniye++;


        return 1;
    }
    else if(strcmp(kapi->isim,"OR")==0||strcmp(kapi->isim,"or")==0){


        for (int i = 1; i <kapi->giris_sayisi ; ++i) {
            sonuc+=kapi->giris_degerleri[i];
        }

        if(sonuc==0)degerdegistir(kapi->cikis_isim,0);
        else degerdegistir(kapi->cikis_isim,1);



        saniyeayarlama(kapi);
        OnOff(kapi->cikis_isim,1);


        kapi->acikkapali=0;
        kapi->sure=kapi->gecikme_suresi;
        sprintf(temp,"%dns: %c %d->%d\n", saniye,kapi->cikis_isim,deger,kapi->cikis_degeri);
        strcat(olaylar,temp);
        //saniye++;

        return 1;

    }
    else if(strcmp(kapi->isim,"XOR")==0||strcmp(kapi->isim,"xor")==0){




        if(kapi->giris_degerleri[0]==kapi->giris_degerleri[1])degerdegistir(kapi->cikis_isim,0);
        else degerdegistir(kapi->cikis_isim,1);


        saniyeayarlama(kapi);
        OnOff(kapi->cikis_isim,1);


        kapi->acikkapali=0;
        kapi->sure=kapi->gecikme_suresi;

        sprintf(temp,"%dns: %c %d->%d\n", saniye,kapi->cikis_isim,deger,kapi->cikis_degeri);
        strcat(olaylar,temp);
        //saniye++;
        return 1;
    }
    else if(strcmp(kapi->isim,"NAND")==0||strcmp(kapi->isim,"nand")==0){


        for (int i = 1; i <kapi->giris_sayisi ; ++i) {
            sonuc*=kapi->giris_degerleri[i];
        }

        if(sonuc==0)degerdegistir(kapi->cikis_isim,1);
        else degerdegistir(kapi->cikis_isim,0);



        saniyeayarlama(kapi);
        OnOff(kapi->cikis_isim,1);


        kapi->acikkapali=0;
        kapi->sure=kapi->gecikme_suresi;
        //printf("\n %c=%d %c=%d \nsonuc=%d\n",kapi->giris_isimleri[0],kapi->giris_degerleri[0],kapi->giris_isimleri[1],kapi->giris_degerleri[1],sonuc);
        sprintf(temp,"%dns: %c %d->%d\n", saniye,kapi->cikis_isim,deger,kapi->cikis_degeri);
        strcat(olaylar,temp);
        //saniye++;

        return 1;

    }
    else if(strcmp(kapi->isim,"NOT")==0||strcmp(kapi->isim,"not")==0){


        if(kapi->giris_degerleri[0]==0)degerdegistir(kapi->cikis_isim,1);
        else degerdegistir(kapi->cikis_isim,0);


        saniyeayarlama(kapi);
        OnOff(kapi->cikis_isim,1);


        kapi->acikkapali=0;
        kapi->sure=kapi->gecikme_suresi;
        sprintf(temp,"%dns: %c %d->%d\n", saniye,kapi->cikis_isim,deger,kapi->cikis_degeri);
        strcat(olaylar,temp);
        //saniye++;
        return 1;
    }
    else if(strcmp(kapi->isim,"EXOR")==0||strcmp(kapi->isim,"exor")==0){


        if(kapi->giris_degerleri[0]==kapi->giris_degerleri[1])degerdegistir(kapi->cikis_isim,0);
        else degerdegistir(kapi->cikis_isim,1);


        saniyeayarlama(kapi);
        OnOff(kapi->cikis_isim,1);


        kapi->acikkapali=0;
        kapi->sure=kapi->gecikme_suresi;
        sprintf(temp,"%dns: %c %d->%d\n", saniye,kapi->cikis_isim,deger,kapi->cikis_degeri);
        strcat(olaylar,temp);
        //saniye++;
        return 1;
    }

    return 0;


}

int indexbul(char *dizi,char a){

    for (int i = 0; i <strlen(dizi) ; ++i) {
        if(dizi[i]==a)return i;
    }
    return -1;
}

void degerdegistir(char isim,int yenideger){

/*
    for (int i = 0; i <devre->kapi_sayisi ; ++i) {
        if(devre->kapilar[i].giris_isimleri[indexbul(devre->kapilar[i].giris_isimleri,isim)]!=-1)
        devre->kapilar[i].giris_degerleri[indexbul(devre->kapilar[i].giris_isimleri,isim)]=yenideger;
        if(devre->kapilar[i].cikis_isim==isim)devre->kapilar[i].cikis_degeri=yenideger;
    }
    for (int j = 0; j <devre->giris_sayisi ; ++j) {
        if(devre->giris_isimleri[indexbul(devre->giris_isimleri,isim)]!=-1)
            devre->giris_degerleri[indexbul(devre->giris_isimleri,isim)]=yenideger;
    }
    for (int j = 0; j <devre->cikis_sayisi ; ++j) {
        if(devre->cikis_isimleri[indexbul(devre->cikis_isimleri,isim)]!=-1)
            devre->cikis_degerleri[indexbul(devre->cikis_isimleri,isim)]=yenideger;
    }
*/


    for (int i = 0; i <devre->kapi_sayisi ; ++i) {
        if(indexbul(devre->kapilar[i].giris_isimleri,isim)!=-1)
            devre->kapilar[i].giris_degerleri[indexbul(devre->kapilar[i].giris_isimleri,isim)]=yenideger;

        if(devre->kapilar[i].cikis_isim==isim)devre->kapilar[i].cikis_degeri=yenideger;
    }

    for (int j = 0; j <devre->giris_sayisi ; ++j) {
        if(indexbul(devre->giris_isimleri,isim)!=-1)
            devre->giris_degerleri[indexbul(devre->giris_isimleri,isim)]=yenideger;

    }

    for (int j = 0; j <devre->cikis_sayisi ; ++j) {
        if(indexbul(devre->cikis_isimleri,isim)!=-1)
            devre->cikis_degerleri[indexbul(devre->cikis_isimleri,isim)]=yenideger;

    }

}

void kapisayisibul(FILE *devredosyasi){

    char *satir;int k=0,girissayisi=0;

    while(fgets(satir,SATIRBOYUT,devredosyasi)!=NULL){

        if(satir[strlen(satir)-1]=='\n')
            satir[strlen(satir)-1]='\0';
        for (int i = 0; i <strlen(satir) ; ++i) {
            if(satir[i]=='\t')satir[i]=' ';
        }






        if(strcmp(satir,"")==0)continue;

        if(strstr(satir,".kapi")!=NULL)k++;




    }

    devre->kapi_sayisi=k;
    devre->kapilar=(struct KAPI*)malloc(devre->kapi_sayisi * sizeof(struct KAPI));

    rewind(devredosyasi);
    k=0;
    int kontrol,j;
    while(fgets(satir,SATIRBOYUT,devredosyasi)!=NULL){
            j=0;
            kontrol=0;
        if(satir[strlen(satir)-1]=='\n')
            satir[strlen(satir)-1]='\0';
        for (int i = 0; i <strlen(satir) ; ++i) {
            if(satir[i]=='\t')satir[i]=' ';
        }

        if(strcmp(satir,"")==0)continue;


        if(strstr(satir,".kapi")!=NULL){
            if(strstr(satir,"NOR")!=NULL){
                satir=strstr(satir,"NOR");

                strcpy(devre->kapilar[k].isim,"NOR");
                for (int i = 3; i <strlen(satir) ; ++i) {

                    if(isalnum(satir[i])){
                        kontrol++;

                    }if(satir[i]==' ')continue;

                    if(kontrol==1){
                        devre->kapilar[k].giris_sayisi=atoi(satir+i);
                        devre->kapilar[k].giris_isimleri=(char*)malloc(sizeof(char)*devre->kapilar[k].giris_sayisi);
                        devre->kapilar[k].giris_degerleri=(int*)malloc(sizeof(int)*devre->kapilar[k].giris_sayisi);
                        continue;
                    }
                    if(kontrol==2){
                        devre->kapilar[k].cikis_isim=satir[i];

                        continue;
                    }
                    if(kontrol<=devre->kapilar[k].giris_sayisi+2){

                        devre->kapilar[k].giris_isimleri[j]=satir[i];

                        j++;
                        continue;
                    }

                    devre->kapilar[k].gecikme_suresi=atoi(satir+i);

                }
                devre->kapilar[k].acikkapali=0;
                devre->kapilar[k].sure=devre->kapilar[k].gecikme_suresi;

                k++;
            }
            else if(strstr(satir,"XOR")!=NULL){
                satir=strstr(satir,"XOR");
                strcpy(devre->kapilar[k].isim,"XOR");
                for (int i = 3; i <strlen(satir) ; ++i) {

                    if(isalnum(satir[i])){
                        kontrol++;

                    }if(satir[i]==' ')continue;

                    if(kontrol==1){
                        devre->kapilar[k].giris_sayisi=atoi(satir+i);
                        devre->kapilar[k].giris_isimleri=(char*)malloc(sizeof(char)*devre->kapilar[k].giris_sayisi);
                        devre->kapilar[k].giris_degerleri=(int*)malloc(sizeof(int)*devre->kapilar[k].giris_sayisi);
                        continue;
                    }
                    if(kontrol==2){
                        devre->kapilar[k].cikis_isim=satir[i];

                        continue;
                    }
                    if(kontrol<=devre->kapilar[k].giris_sayisi+2){

                        devre->kapilar[k].giris_isimleri[j]=satir[i];

                        j++;
                        continue;
                    }

                    devre->kapilar[k].gecikme_suresi=atoi(satir+i);

                }
                devre->kapilar[k].acikkapali=0;
                devre->kapilar[k].sure=devre->kapilar[k].gecikme_suresi;
                k++;
            }

            else if(strstr(satir,"NAND")!=NULL){
                satir=strstr(satir,"NAND");


                strcpy(devre->kapilar[k].isim,"NAND");

                for (int i = 4; i <strlen(satir) ; ++i) {


                    if(isalnum(satir[i])){
                        kontrol++;

                    }if(satir[i]==' ')continue;

                    if(kontrol==1){


                        devre->kapilar[k].giris_sayisi=atoi(satir+i);
                        devre->kapilar[k].giris_isimleri=(char*)malloc(sizeof(char)*devre->kapilar[k].giris_sayisi);
                        devre->kapilar[k].giris_degerleri=(int*)malloc(sizeof(int)*devre->kapilar[k].giris_sayisi);
                        continue;
                    }

                    if(kontrol==2){
                        devre->kapilar[k].cikis_isim=satir[i];

                        continue;
                    }
                    if(kontrol<=devre->kapilar[k].giris_sayisi+2){

                        devre->kapilar[k].giris_isimleri[j]=satir[i];

                        j++;
                        continue;
                    }

                    devre->kapilar[k].gecikme_suresi=atoi(satir+i);

                }
                devre->kapilar[k].acikkapali=0;
                devre->kapilar[k].sure=devre->kapilar[k].gecikme_suresi;
                k++;



            }
            else if(strstr(satir,"AND")!=NULL){
                satir=strstr(satir,"AND");

                strcpy(devre->kapilar[k].isim,"AND");
                for (int i = 3; i <strlen(satir) ; ++i) {

                    if(isalnum(satir[i])){
                        kontrol++;

                    }if(satir[i]==' ')continue;

                    if(kontrol==1){
                        devre->kapilar[k].giris_sayisi=atoi(satir+i);
                        devre->kapilar[k].giris_isimleri=(char*)malloc(sizeof(char)*devre->kapilar[k].giris_sayisi);
                        devre->kapilar[k].giris_degerleri=(int*)malloc(sizeof(int)*devre->kapilar[k].giris_sayisi);
                        continue;
                    }
                    if(kontrol==2){
                        devre->kapilar[k].cikis_isim=satir[i];

                        continue;
                    }
                    if(kontrol<=devre->kapilar[k].giris_sayisi+2){

                        devre->kapilar[k].giris_isimleri[j]=satir[i];

                        j++;
                        continue;
                    }

                    devre->kapilar[k].gecikme_suresi=atoi(satir+i);

                }
                devre->kapilar[k].acikkapali=0;
                devre->kapilar[k].sure=devre->kapilar[k].gecikme_suresi;
                k++;
            }

            else if(strstr(satir,"NOT")!=NULL){
                satir=strstr(satir,"NOT");

                strcpy(devre->kapilar[k].isim,"NOT");
                for (int i = 3; i <strlen(satir) ; ++i) {

                    if(isalnum(satir[i])){
                        kontrol++;

                    }if(satir[i]==' ')continue;

                    if(kontrol==1){
                        devre->kapilar[k].giris_sayisi=atoi(satir+i);
                        devre->kapilar[k].giris_isimleri=(char*)malloc(sizeof(char)*devre->kapilar[k].giris_sayisi);
                        devre->kapilar[k].giris_degerleri=(int*)malloc(sizeof(int)*devre->kapilar[k].giris_sayisi);
                        continue;
                    }
                    if(kontrol==2){
                        devre->kapilar[k].cikis_isim=satir[i];

                        continue;
                    }
                    if(kontrol<=devre->kapilar[k].giris_sayisi+2){

                        devre->kapilar[k].giris_isimleri[j]=satir[i];

                        j++;
                        continue;
                    }

                    devre->kapilar[k].gecikme_suresi=atoi(satir+i);

                }
                devre->kapilar[k].acikkapali=0;
                devre->kapilar[k].sure=devre->kapilar[k].gecikme_suresi;
                k++;
            }


            else if(strstr(satir,"OR")!=NULL){
                satir=strstr(satir,"OR");

                strcpy(devre->kapilar[k].isim,"OR");
                for (int i = 2; i <strlen(satir) ; ++i) {

                    if(isalnum(satir[i])){
                        kontrol++;

                    }if(satir[i]==' ')continue;

                    if(kontrol==1){
                        devre->kapilar[k].giris_sayisi=atoi(satir+i);
                        devre->kapilar[k].giris_isimleri=(char*)malloc(sizeof(char)*devre->kapilar[k].giris_sayisi);
                        devre->kapilar[k].giris_degerleri=(int*)malloc(sizeof(int)*devre->kapilar[k].giris_sayisi);
                        continue;
                    }
                    if(kontrol==2){
                        devre->kapilar[k].cikis_isim=satir[i];

                        continue;
                    }
                    if(kontrol<=devre->kapilar[k].giris_sayisi+2){

                        devre->kapilar[k].giris_isimleri[j]=satir[i];

                        j++;
                        continue;
                    }

                    devre->kapilar[k].gecikme_suresi=atoi(satir+i);

                }
                devre->kapilar[k].acikkapali=0;
                devre->kapilar[k].sure=devre->kapilar[k].gecikme_suresi;
                k++;
            }

            else if(strstr(satir,"nor")!=NULL){
                satir=strstr(satir,"nor");
                strcpy(devre->kapilar[k].isim,"nor");
                for (int i = 3; i <strlen(satir) ; ++i) {

                    if(isalnum(satir[i])){
                        kontrol++;

                    }if(satir[i]==' ')continue;

                    if(kontrol==1){
                        devre->kapilar[k].giris_sayisi=atoi(satir+i);
                        devre->kapilar[k].giris_isimleri=(char*)malloc(sizeof(char)*devre->kapilar[k].giris_sayisi);
                        devre->kapilar[k].giris_degerleri=(int*)malloc(sizeof(int)*devre->kapilar[k].giris_sayisi);
                        continue;
                    }
                    if(kontrol==2){
                        devre->kapilar[k].cikis_isim=satir[i];

                        continue;
                    }
                    if(kontrol<=devre->kapilar[k].giris_sayisi+2){

                        devre->kapilar[k].giris_isimleri[j]=satir[i];

                        j++;
                        continue;
                    }

                    devre->kapilar[k].gecikme_suresi=atoi(satir+i);

                }
                devre->kapilar[k].acikkapali=0;
                devre->kapilar[k].sure=devre->kapilar[k].gecikme_suresi;
                k++;
            }
            else if(strstr(satir,"xor")!=NULL){
                satir=strstr(satir,"xor");

                strcpy(devre->kapilar[k].isim,"xor");
                for (int i = 3; i <strlen(satir) ; ++i) {

                    if(isalnum(satir[i])){
                        kontrol++;

                    }if(satir[i]==' ')continue;

                    if(kontrol==1){
                        devre->kapilar[k].giris_sayisi=atoi(satir+i);
                        devre->kapilar[k].giris_isimleri=(char*)malloc(sizeof(char)*devre->kapilar[k].giris_sayisi);
                        devre->kapilar[k].giris_degerleri=(int*)malloc(sizeof(int)*devre->kapilar[k].giris_sayisi);
                        continue;
                    }
                    if(kontrol==2){
                        devre->kapilar[k].cikis_isim=satir[i];

                        continue;
                    }
                    if(kontrol<=devre->kapilar[k].giris_sayisi+2){

                        devre->kapilar[k].giris_isimleri[j]=satir[i];

                        j++;
                        continue;
                    }

                    devre->kapilar[k].gecikme_suresi=atoi(satir+i);

                }
                devre->kapilar[k].acikkapali=0;
                devre->kapilar[k].sure=devre->kapilar[k].gecikme_suresi;
                k++;
            }

            else if(strstr(satir,"nand")!=NULL){
                satir=strstr(satir,"nand");

                strcpy(devre->kapilar[k].isim,"nand");
                for (int i = 4; i <strlen(satir) ; ++i) {

                    if(isalnum(satir[i])){
                        kontrol++;

                    }if(satir[i]==' ')continue;

                    if(kontrol==1){
                        devre->kapilar[k].giris_sayisi=atoi(satir+i);
                        devre->kapilar[k].giris_isimleri=(char*)malloc(sizeof(char)*devre->kapilar[k].giris_sayisi);
                        devre->kapilar[k].giris_degerleri=(int*)malloc(sizeof(int)*devre->kapilar[k].giris_sayisi);
                        continue;
                    }
                    if(kontrol==2){
                        devre->kapilar[k].cikis_isim=satir[i];

                        continue;
                    }
                    if(kontrol<=devre->kapilar[k].giris_sayisi+2){

                        devre->kapilar[k].giris_isimleri[j]=satir[i];

                        j++;
                        continue;
                    }

                    devre->kapilar[k].gecikme_suresi=atoi(satir+i);

                }
                devre->kapilar[k].acikkapali=0;
                devre->kapilar[k].sure=devre->kapilar[k].gecikme_suresi;
                k++;
            }
            else if(strstr(satir,"and")!=NULL){
                satir=strstr(satir,"and");

                strcpy(devre->kapilar[k].isim,"and");
                for (int i = 3; i <strlen(satir) ; ++i) {

                    if(isalnum(satir[i])){
                        kontrol++;

                    }if(satir[i]==' ')continue;

                    if(kontrol==1){
                        devre->kapilar[k].giris_sayisi=atoi(satir+i);
                        devre->kapilar[k].giris_isimleri=(char*)malloc(sizeof(char)*devre->kapilar[k].giris_sayisi);
                        devre->kapilar[k].giris_degerleri=(int*)malloc(sizeof(int)*devre->kapilar[k].giris_sayisi);
                        continue;
                    }
                    if(kontrol==2){
                        devre->kapilar[k].cikis_isim=satir[i];

                        continue;
                    }
                    if(kontrol<=devre->kapilar[k].giris_sayisi+2){

                        devre->kapilar[k].giris_isimleri[j]=satir[i];

                        j++;
                        continue;
                    }

                    devre->kapilar[k].gecikme_suresi=atoi(satir+i);

                }
                devre->kapilar[k].acikkapali=0;
                devre->kapilar[k].sure=devre->kapilar[k].gecikme_suresi;
                k++;
            }

            else if(strstr(satir,"not")!=NULL){
                satir=strstr(satir,"not");

                strcpy(devre->kapilar[k].isim,"not");
                for (int i = 3; i <strlen(satir) ; ++i) {

                    if(isalnum(satir[i])){
                        kontrol++;

                    }if(satir[i]==' ')continue;

                    if(kontrol==1){
                        devre->kapilar[k].giris_sayisi=atoi(satir+i);
                        devre->kapilar[k].giris_isimleri=(char*)malloc(sizeof(char)*devre->kapilar[k].giris_sayisi);
                        devre->kapilar[k].giris_degerleri=(int*)malloc(sizeof(int)*devre->kapilar[k].giris_sayisi);
                        continue;
                    }
                    if(kontrol==2){
                        devre->kapilar[k].cikis_isim=satir[i];

                        continue;
                    }
                    if(kontrol<=devre->kapilar[k].giris_sayisi+2){

                        devre->kapilar[k].giris_isimleri[j]=satir[i];

                        j++;
                        continue;
                    }

                    devre->kapilar[k].gecikme_suresi=atoi(satir+i);

                }
                devre->kapilar[k].acikkapali=0;
                devre->kapilar[k].sure=devre->kapilar[k].gecikme_suresi;
                k++;
            }


            else if(strstr(satir,"or")!=NULL){
                satir=strstr(satir,"or");

                strcpy(devre->kapilar[k].isim,"or");
                for (int i = 2; i <strlen(satir) ; ++i) {

                    if(isalnum(satir[i])){
                        kontrol++;

                    }if(satir[i]==' ')continue;

                    if(kontrol==1){
                        devre->kapilar[k].giris_sayisi=atoi(satir+i);
                        devre->kapilar[k].giris_isimleri=(char*)malloc(sizeof(char)*devre->kapilar[k].giris_sayisi);
                        devre->kapilar[k].giris_degerleri=(int*)malloc(sizeof(int)*devre->kapilar[k].giris_sayisi);
                        continue;
                    }
                    if(kontrol==2){
                        devre->kapilar[k].cikis_isim=satir[i];

                        continue;
                    }
                    if(kontrol<=devre->kapilar[k].giris_sayisi+2){

                        devre->kapilar[k].giris_isimleri[j]=satir[i];

                        j++;
                        continue;
                    }

                    devre->kapilar[k].gecikme_suresi=atoi(satir+i);

                }
                devre->kapilar[k].acikkapali=0;
                devre->kapilar[k].sure=devre->kapilar[k].gecikme_suresi;
                k++;
            }










        }




    }


}

void Ykomutu_satirislem(const char * satir){

    if( strstr(satir,".giris")!=NULL){
        int i=0,k=0;
        for (int j = 0; j <strlen(satir) ; ++j) {

            if(satir[j]==' '){
                i=j;
                break;
            }
        }
        for (int j=i+1; j <strlen(satir) ; ++j) {
            if(satir[j]==' ')continue;
            if(satir[j]=='#')break;
            k++;

        }
        devre->giris_sayisi=k;
        devre->giris_isimleri=(char*)malloc(sizeof(char)*devre->giris_sayisi);
        devre->giris_degerleri=(int*)malloc(devre->giris_sayisi * sizeof(int));
        k=0;
        for (int l = i+1; l <strlen(satir) ; ++l) {
            if(satir[l]==' ')continue;
            if(satir[l]=='#')break;
            devre->giris_isimleri[k]=satir[l];
            k++;
        }


    }

    else if( strstr(satir,".cikis")!=NULL){
        int i=0,k=0;
        for (int j = 0; j <strlen(satir) ; ++j) {

            if(satir[j]==' '){
                i=j;
                break;
            }
        }
        for (int j=i+1; j <strlen(satir) ; ++j) {
            if(satir[j]==' ')continue;
            if(satir[j]=='#')break;
            k++;

        }

        devre->cikis_sayisi=k;
        devre->cikis_isimleri=(char*)malloc(sizeof(char)*devre->cikis_sayisi);
        devre->cikis_degerleri=(int*)malloc(devre->cikis_sayisi * sizeof(int));
        k=0;
        for (int l = i+1; l <strlen(satir) ; ++l) {
            if(satir[l]==' ')continue;
            if(satir[l]=='#')break;
            devre->cikis_isimleri[k]=satir[l];
            k++;

        }


    }






}


void devreyi_yaz(struct DEVRE *devre){

            printf("Girisler\n-------------\n");
    for (int i = 0; i <devre->giris_sayisi ; ++i) {
        printf("%c  =  %d \n",devre->giris_isimleri[i],devre->giris_degerleri[i]);
    }

    printf("Cikislar\n-------------\n");
    for (int i = 0; i <devre->cikis_sayisi ; ++i) {
        printf("%c  =  %d \n",devre->cikis_isimleri[i],devre->cikis_degerleri[i]);
    }


    printf("Kapılar\n------------------------\n");
    for (int j = 0; j <devre->kapi_sayisi ; ++j) {
        printf("Kapı ismi = %s Gecikme = %d   Giris Sayisi= %d  Sure= %d  Acikkapali=%d  Cikisi=%c cikisdegeri= %d\n",devre->kapilar[j].isim,devre->kapilar[j].gecikme_suresi,devre->kapilar[j].giris_sayisi,devre->kapilar[j].sure,devre->kapilar[j].acikkapali,devre->kapilar[j].cikis_isim,devre->kapilar[j].cikis_degeri);
        for (int i = 0; i <devre->kapilar[j].giris_sayisi ; ++i) {
            printf("%c girisi = %d\n",devre->kapilar[j].giris_isimleri[i],devre->kapilar[j].giris_degerleri[i]);

        }
    }



}