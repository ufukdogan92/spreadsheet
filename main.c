#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int karsilastir(int ,int , int );
int formulHesapla(char *,int *);
void tabloYazdir(int ,int ,int *);
void filtreliYazdir(int ,int ,int *,int);
void satirSil(int *,int ,int );
void sutunDuzenle(int *);
int satirEkle(int ,int ,int * );

int main ()
{
    char girdi[] = "4,3,10,34,37,=A1+B1+C1,40,17,34,=A2+B2+C2,=A1+A2,=B1+B2,=C1+C2,=D1+D2";
    int tablo[10][10];
    char sonucDizisi[103][1024];
    char tutulanGirdi[103][1024];
    char * ayracPtr;
    int elemanSayisi =0;
    ayracPtr = strtok (girdi,",");
    while (ayracPtr != NULL)
    {
        strcpy(*(sonucDizisi+elemanSayisi),ayracPtr);
        strcpy(*(tutulanGirdi+elemanSayisi),ayracPtr);
        ayracPtr = strtok (NULL, ",");
        elemanSayisi++;
    }
    int i,j,arttir=2;
    int satirSayisi = atoi(*(sonucDizisi+1));
    int sutunSayisi = atoi(*(sonucDizisi+0));
    int a = karsilastir(satirSayisi,sutunSayisi,elemanSayisi);
    if (a == 0)
        return 0;

    for(i=0;i<satirSayisi;i++){
        for(j=0;j<sutunSayisi;j++){
            tablo[i][j] = formulHesapla(sonucDizisi+arttir,tablo);
                arttir++;
        }
    }

    char islem;
    int cikis=1;
    do{

        printf(" \n\t\t#### SPREADSHEET #### \n\n");
        printf("\t#### Formul Hesapla  ( islem kodu: 1 )\n");
        printf("\t#### Yeni Satir Ekle ( islem kodu: 2 )\n");
        printf("\t#### Satir Sil ( islem kodu: 3 )\n");
        printf("\t#### Satir Duzenle ( islem kodu: 4 )\n");
        printf("\t#### Filtreleme ( islem kodu: 5 )\n");
        printf("\t#### Cikmak icin 1-5 araligi haric bir tusa basabilirsiniz..\n");
        printf("\n\t#### islem giriniz: ");
        scanf(" %c",&islem);

        switch(islem){
            case '1':
                printf("\n\t####   Girdi Sonucu   #### \n");
                tabloYazdir(satirSayisi,sutunSayisi,tablo);
                printf("\n");
                break;
            case '2':
                printf("\n");

                satirEkle(satirSayisi,sutunSayisi,tablo);
                tabloYazdir(satirSayisi+1,sutunSayisi,tablo);
                satirSayisi++;

                break;

            case '3':
                printf("\n\t####   Silme Islemi   #### \n");
                int silinecek,i,j,sayac=0;
                printf("\tSilinecek Sayiyi Giriniz: ");
                scanf("%d",&silinecek);
                if(satirSayisi<silinecek){
                    printf("\tSatir Bulunamadi.");
                }
                else{
                    satirSil(tablo,satirSayisi,silinecek);
                    satirSayisi--;
                    printf("\n\t####   Silinme Sonrasi   #### \n");
                    tabloYazdir(satirSayisi,sutunSayisi,tablo);
                }

                break;

            case '4':
                printf("\n\t####   Duzenleme Islemi   #### \n");
                sutunDuzenle(tablo);
                tabloYazdir(satirSayisi,sutunSayisi,tablo);

                printf("\n");
                break;

            case '5':
                printf("\n\t####   Filtre Islemi   #### \n");
                int kosul=50;
                printf("\tFiltrelenecek Sayiyi Giriniz: ");
                scanf("%d",&kosul);
                printf("\n\t####   Filtre Islemi   #### \n");
                filtreliYazdir(satirSayisi,sutunSayisi,tablo,kosul);
                printf("\n");
                break;
            default:
                cikis = 0;
                break;
        }
    }
    while(cikis);


    return 0;
}


int satirEkle(int satirSayisi,int sutunSayisi,int *tablo){
        int sira,i,j,deger;
                if(satirSayisi>=10){
                    printf("\n\t####   10dan fazla satir eklenemez..   #### \n\n");
                    return 0;
                }
                do{

                    printf("\tKacinci satirdan sonra eklensin ? (1-%d) : ",satirSayisi);
                    scanf("%d",&sira);

                }
                while(sira > satirSayisi || sira < 0);

                for(i=satirSayisi-1;i>=sira ;i--){
                    for(j=sutunSayisi;j>=0;j--){
                        *(tablo+j+i*10+10) = *(tablo+j+i*10);
                    }
                }

                for(i=0;i<sutunSayisi ;i++){
                    printf("\t%d. Degeri giriniz: ",i+1);
                    scanf(" %d",&deger);
                    *(tablo+i+sira*10) = deger;
                }

}

void satirSil(int *tablo,int satirSayisi,int silinecekSatir){

    int i,sayac;
    for(i=0;i<satirSayisi;i++){
        if(i==silinecekSatir-1){
            for(sayac=0;sayac<satirSayisi;sayac++)
                *(tablo+i*10+sayac)=*(tablo+(i+1)*10+sayac);
        break;
        }
    }
}

void sutunDuzenle(int *tablo){



                int saSayisi =0;
                int sSayisi =0;
                char *gelenHarf;
                int harfIslem=0;
                int deger;
                int satir;
                int gelenHarfInt;
                int pointerSayisi = 0;
                do{
                    harfIslem=0;
                    printf("\tA-J araligini giriniz: (sutun sirasi): ");
                    scanf(" %c",&gelenHarf);
                    if(gelenHarf == 'A')
                        gelenHarfInt =0;
                    else if(gelenHarf == 'B')
                        gelenHarfInt =1;
                    else if(gelenHarf == 'C')
                        gelenHarfInt =2;
                    else if(gelenHarf == 'D')
                        gelenHarfInt =3;
                    else if(gelenHarf == 'E')
                        gelenHarfInt =4;
                    else if(gelenHarf == 'F')
                        gelenHarfInt =5;
                    else if(gelenHarf == 'G')
                        gelenHarfInt =6;
                    else if(gelenHarf == 'H')
                        gelenHarfInt =7;
                    else if(gelenHarf == 'I')
                        gelenHarfInt =8;
                    else if(gelenHarf == 'J')
                        gelenHarfInt =9;
                    else harfIslem=1;

                }
                while(harfIslem>=1);

                do{
                    printf("\t1-10 araligini giriniz (satir sayisi): ");
                    scanf(" %d",&satir);
                }
                while(satir<0 || satir>10);

                satir=satir-1;   // dizide 1 indis geride

                printf("\tEski degeri =  %d\n\tDegistirmek istediginiz degeri giriniz: ",*(tablo+satir*10+harfIslem));
                scanf("%d",&deger);
                *(tablo+satir*10+gelenHarfInt) = deger;

}
int karsilastir(int satirSayisi,int sutunSayisi, int elemanSayisi){

    if(satirSayisi>10){
        printf("Lutfen satir sayisini 1-10 araliginda giriniz ve tekrar deneyiniz. \n");
        return 0;
        }
    else if(sutunSayisi>10){
        printf("\tLutfen sutun sayisini 1-10 araliginda giriniz ve tekrar deneyiniz.  \n");
        return 0;
        }
    else if((elemanSayisi-2) != satirSayisi*sutunSayisi){
        printf("\tElemanlari satir ve sutun sayisina gore dogru giriniz. Toplam %d eleman girmeniz gerekiyor.  \n ",satirSayisi*sutunSayisi);
        return 0;
    }
    return 1;
}

void islemleriAl(char *girdi,char *karakterler){

    // girdi(girdinin sadece bir elemanı) elemanında kaç tane işlem varsa (*/-+) sırasıyla bi diziye atama yapan fonksiyon
    int uzunluk = strlen(girdi);
    int i;
    int karakterSayisi=0,islemSayisi;
    for(i=0;i<uzunluk;i++){
         char a= {*(girdi+i)};
         if(a=='+'){
            karakterler[karakterSayisi] = '+';
            karakterSayisi+=1;
         }
         else if(a=='*'){
            karakterler[karakterSayisi] = '*';
            karakterSayisi+=1;
         }
         else if(a=='-'){
            karakterler[karakterSayisi] = '-';
            karakterSayisi+=1;
         }
         else if(a=='/'){
            karakterler[karakterSayisi] = '/';
            karakterSayisi+=1;
         }
    }
}
int formulHesapla(char *dizi,int *tablo){
    int i,k,sayiMi;
    char konumlarDizisi[0][1024];  //A1 vs gibi değeri tutacak olan dizi
    int konumlarSayisi =0; //A1 vs gibi değeri sayacak değişken

    char karakterler[] = {'A','B','C','D','E','F','G','H','I','J'};
    char islemler[100];  // dizideki matematiksel işlemler sırasıyla diziye atandı,
    int sayiDizisi[1024],harfinKonumu;  //A1 vs gibi elemanlarının tablodaki int değerini tutacak olan dizi.
    char harf=0,*sayi;
    islemleriAl(dizi,islemler);

    char * ayracPtr;
    ayracPtr = strtok (dizi,"=*/-+");
    while (ayracPtr != NULL)
    {
        strcpy(konumlarDizisi[konumlarSayisi],ayracPtr);  // diziden A1 gibi komutları ayırarak yeni diziye kopyalıyoruz.
        ayracPtr = strtok (NULL, "=*/+-");
        konumlarSayisi++;
    }


     for(i=0;i<konumlarSayisi;i++){
            sayiMi = atoi(*(konumlarDizisi+i));
            if(sayiMi!=0){
                sayiDizisi[i] = sayiMi;   // değer sayi ise direkt olarak tabloya eklendi. sırası "i" ile belirlendi.
            }
    }

    for(i=0;i<konumlarSayisi;i++){
            sayiMi = atoi(*(konumlarDizisi+i));
            if(sayiMi==0){
                harf = konumlarDizisi[i][0]; // konumdaki harfin kendisini aldı. A1 ise sadece A yı alıyor. (sütun numarası)
                sayi = konumlarDizisi[i][1]; // konumdaki harfin sayisini aldık. (satir numarasi)
                harfinKonumu = sayi - '0';
                    if(konumlarDizisi[i][2] == '0' && harfinKonumu==1){
                        harfinKonumu = 10; // karakter A10,B10 gibi olursa konumu 10 yapar.
                    }
                 for(k=0;k<10;k++){
                    if(karakterler[k] == harf){
                        sayiDizisi[i] = *(tablo+(10*(harfinKonumu-1))+k);  // dizideki int değerini bulup, sayılar tablomuza ekledik.
                    }
                }
            }
    }
    for(i=0;i<konumlarSayisi;i++)
    for(i=0;i<konumlarSayisi-1;i++){  // burada islemler dizisi ile int değerlerin bulunduğu sayiDizisi yardımı ile dizideki işlemler soldan sağa olarak yapıldı.
        if(*(islemler+i) == '*'){
            (*(sayiDizisi+i+1)) = (*(sayiDizisi+i)) * (*(sayiDizisi+i+1)) ;
        }
        if(*(islemler+i) == '/'){
            (*(sayiDizisi+i+1)) = (*(sayiDizisi+i)) / (*(sayiDizisi+i+1));
        }

        if(*(islemler+i) == '+'){
            (*(sayiDizisi+i+1)) = (*(sayiDizisi+i)) + (*(sayiDizisi+i+1));
        }

        if(*(islemler+i) == '-'){
            (*(sayiDizisi+i+1)) = (*(sayiDizisi+i)) - (*(sayiDizisi+i+1));
        }
    }
    return *(sayiDizisi+konumlarSayisi-1);  //işlemler sonrasında tablodaki int değeri dönderdik.
}

void tabloYazdir(int satirSayisi,int sutunSayisi,int *tablo){
    int i,j, elemanSayisi = (satirSayisi*sutunSayisi);
    int saSayisi =0;
    int sSayisi =0;
    int pointerSayisi = 0;
    j=1;
    printf("\n");
    for(i=0;i<elemanSayisi;i++){
        if(i%sutunSayisi==0)
            printf("\t");

        printf("\t%d",*(tablo+pointerSayisi));

        if(sSayisi!=sutunSayisi-1){
            printf(",");
        }
        sSayisi++;
        pointerSayisi++;
        if(sSayisi == sutunSayisi){
            sSayisi =0;
            saSayisi =saSayisi+1;
        }

        if(sSayisi==0){
            printf("\n");
            pointerSayisi = 10*j;
            j++;
        }
    }
}

void filtreliYazdir(int satirSayisi,int sutunSayisi,int *tablo,int kosul){
    int i,j, elemanSayisi = (satirSayisi*sutunSayisi);
    int saSayisi =0;
    int sSayisi =0;
    int pointerSayisi = 0;
    j=1;
    printf("\n");
    for(i=0;i<elemanSayisi;i++){

        if(i%sutunSayisi==0)
            printf("\t");


        if(kosul!=0 && *(tablo+pointerSayisi)<=kosul)
            printf("\t!");
        else
        printf("\t%d",*(tablo+pointerSayisi));

        if(sSayisi!=sutunSayisi-1){
            printf(",");
        }
        sSayisi++;
        pointerSayisi++;
        if(sSayisi == sutunSayisi){
            sSayisi =0;
            saSayisi =saSayisi+1;
        }

        if(sSayisi==0){
            printf("\n");
            pointerSayisi = 10*j;
            j++;
        }
    }
}




