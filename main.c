#include <stdio.h>
#include "stdlib.h"
#include "string.h"

struct KAPI{
    char isim;
    int giris_sayisi;
    char *giris_isimleri;
    int *giris_degerleri;
    int cikis;
};
struct DEVRE {
    int giris_sayisi;
    int kapi_sayisi;
    int cikis_sayisi;
    char *giris_isimleri;
    int *giris_degerleri;
    char *cikis_isimleri;
    int *cikislar;
    struct KAPI *kapilar;



};


int komutcalistir(const char *komut, struct DEVRE *devre);




int main() {
    struct DEVRE *devre = NULL;
    char *komut;
    komut=(char *)malloc(sizeof(char));
    do {

        printf("\n>");
        fgets(komut,256,stdin);
        komut=realloc(komut,sizeof(char)*strlen(komut));
        komut[strlen(komut)-1]='\0';
        if(komutcalistir(komut,devre)){

        }else {
            printf("Lutfen gecerli bir komut giriniz!");
            strcpy(komut, "Hata");
        }

    } while(komut[0]!='c'&&komut[0]!='C');





    return 0;
}

int komutcalistir(const char *komut, struct DEVRE *devre){

if(komut[0]=='Y'||komut[0]=='y'){

    return 1;
}
else if(komut[0]=='I'||komut[0]=='i'){

    return 1;
    }
else if(komut[0]=='H'||komut[0]=='h'){

    return 1;
}
else if(komut[0]=='L'||komut[0]=='l'){

    return 1;
}
else if(komut[0]=='S'||komut[0]=='s'){

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

