#include <stdio.h>
#include <string.h>
#include <locale.h>//turkce karakter okunmasını saglayan kutuphane
#include <dirent.h>
#include <unistd.h>
#include <stdlib.h>
#include <ctype.h>

struct detay
{  char etkt[100];
    int tekrar;
};

int say (struct detay liste[], const char unit[], int sayac)
{
    int i;

    for (i = 0; i < sayac; i++)
    {
        if (strcmp(liste[i].etkt, unit) == 0)
        {
            liste[i].tekrar++;

            return sayac;
        }
    }

    strcpy(liste[sayac].etkt, unit);
    liste[sayac].tekrar++;

    return (sayac + 1);
}

char *aktar(char *veri,size_t ilk,size_t son,int uzunluk){
    char *s=NULL;
    if(ilk>=son)
        return 0;
    if((s=(char*)malloc(sizeof(char)*(son+uzunluk-ilk+1)))==NULL)
        return NULL;
    memcpy(s,veri+ilk,son+uzunluk-ilk);
    s[son+uzunluk-ilk]='\0';
    return s;
}

char etiket(const char *veri){ //case 3 icin outputa yazar
    char *ptr,*ptr2,*s,etiket1[150];
    char aramailk[]="[[";
    char aramason[]="]]";
    int j=0,k=0,yer[50],yer2[50],etiketadeti=0,uzunluk=0,boy=0;
    uzunluk=strlen(aramason);
    ptr=strstr(veri,aramailk);
    while(ptr!=NULL){
        yer[j]=ptr-veri;
        j++;
        ptr=strstr(ptr+1,aramailk);
    }
    ptr2=strstr(veri,aramason);
    while(ptr2!=NULL){
        yer2[k]=ptr2-veri;
        k++;
        ptr2=strstr(ptr2+1,aramason);
    }

    FILE *tampon= fopen("/Users/silasener/CLionProjects/lab_pro/cmake-build-debug/Üniversite/tampon.txt","a+");
    if(j<=k){
        for(int i=0;i<=k;i++){
            for(int t=0;t<=k;t++){
                if(yer[i]<yer2[t]){
                    char *ara=aktar(veri,yer[i]+2,yer2[t],boy);
                    char *sonuc=strchr(ara,'[');
                    char *sonuc2=strchr(ara,']');
                    if(sonuc==NULL && sonuc2==NULL){
                        s=aktar(veri,yer[i],yer2[t],uzunluk);
                        fprintf(tampon,"  %s  ",s);
                        etiketadeti++;
                        break;
                    }
                }
            }
        }
    }
    else
    {  for(int i=0;i<=j;i++)
        {    for(int t=j;t>=0;t--)
            {  if(yer[t]<yer2[i])
                {   char *ara=aktar(veri,yer[t]+2,yer2[i],boy);
                    char *sonuc=strchr(ara,'[');
                    char *sonuc2=strchr(ara,']');
                    if(sonuc==NULL && sonuc2==NULL)
                    { char *s=aktar(veri,yer[t],yer2[i],uzunluk);
                        fprintf(tampon,"  %s  ",s);
                        etiketadeti++;
                        break;
                    }
                }
            }
        }
    }
    fclose(tampon);
}
char EtiketListele(const char *veri){ //case 1 icin tüm etiketler ekrana basılır
    char *ptr,*ptr2,*s,etiket1[150];
    char aramailk[]="[[";
    char aramason[]="]]";
    int j=0,k=0,yer[50],yer2[50],etiketadeti=0,uzunluk=0,boy=0;
    uzunluk=strlen(aramason);
    ptr=strstr(veri,aramailk);
    while(ptr!=NULL){
        yer[j]=ptr-veri;
        j++;
        ptr=strstr(ptr+1,aramailk);
    }
    ptr2=strstr(veri,aramason);
    while(ptr2!=NULL){
        yer2[k]=ptr2-veri;
        k++;
        ptr2=strstr(ptr2+1,aramason);
    }
    if(j<=k){
        for(int i=0;i<=k;i++){
            for(int t=0;t<=k;t++){
                if(yer[i]<yer2[t]){
                    char *ara=aktar(veri,yer[i]+2,yer2[t],boy);
                    char *sonuc=strchr(ara,'[');
                    char *sonuc2=strchr(ara,']');
                    if(sonuc==NULL && sonuc2==NULL){
                        s=aktar(veri,yer[i],yer2[t],uzunluk);
                        printf("%s\n",s);
                        etiketadeti++;
                        break;
                    }
                }
            }
        }
    }
    else
    {  for(int i=0;i<=j;i++)
        {    for(int t=j;t>=0;t--)
            {  if(yer[t]<yer2[i])
                {   char *ara=aktar(veri,yer[t]+2,yer2[i],boy);
                    char *sonuc=strchr(ara,'[');
                    char *sonuc2=strchr(ara,']');
                    if(sonuc==NULL && sonuc2==NULL)
                    { char *s=aktar(veri,yer[t],yer2[i],uzunluk);
                        printf("%s\n",s);
                        etiketadeti++;
                        break;
                    }
                }
            }
        }
    }
}


void bulunaniguncelle (char *satir,const char *aranankelime, const char *yenikelime) //case2 icin printdiryazdirin icinde cagrilir
{  char *yer; char gecici[100]; int indis=0;
    int aranankelimeuzunluk= strlen(aranankelime);
    while ((yer=strstr(satir,aranankelime))!=NULL)
    {  strcpy(gecici,satir);
        indis=yer-satir; //aranan kelimenin ilk bulunduğu yeri verir
        satir[indis]='\0'; //başlangıç indisinde kelimeyi sonlandırır
        strcat(satir,yenikelime); //ve kaldığı yerden yerine yeni kelimeyi ekler
        strcat(satir,gecici+ indis+aranankelimeuzunluk); //aranan kelimeden sonra kalan kelimeleri ekler
    }
}

void printdirArama(char *dir,char aranankelime[]) //case1 de kelime araması yapmak icin kullanildi
{  char arakelime[100];
    strcpy(arakelime,aranankelime);
    DIR *dp;
    struct dirent *entry;
    dp = opendir(dir);
    chdir(dir);
    while((entry = readdir(dp)) != NULL) {
        int len = strlen(entry->d_name);
        if(entry->d_type==4)
        { if(strcmp(entry->d_name, ".")==0 || strcmp(entry->d_name, "..")==0){
                continue;
            }
            //printf("%s %s\n","FOLDER",entry->d_name);
            printdirArama(entry->d_name,arakelime); // alt klasor olarak buldugunu fonksiyona gonderir
        }
        else{
            if(len > 4 && memcmp(entry->d_name + len - 4, ".txt", 4) == 0){
                FILE *Deneme= fopen(entry->d_name,"r");
                int i=1; char satir[1000];
                while (fgets(satir,1000,Deneme))
                { if(strstr(satir,aranankelime)!=NULL)
                    {   printf("%s \n",entry->d_name);
                        printf("%d. satirda aranan bulundu\n",i);
                    }
                    i=i+1;
                }

            }
        }
    }
    chdir("..");
    closedir(dp);
}

void printdirGuncelleme(char *dir,char aranankelime[],char yenikelime[]) //case2 de eski kelime yerine yeni kelime koymak icin kullanildi
{ char kelimeara[100]; char newkelime[100];
    strcpy(kelimeara,aranankelime);
    strcpy(newkelime,yenikelime);
    DIR *dp;
    struct dirent *entry;
    dp = opendir(dir);
    chdir(dir);
    while((entry = readdir(dp)) != NULL) {
        int len = strlen(entry->d_name);
        if(entry->d_type==4)
        { if(strcmp(entry->d_name, ".")==0 || strcmp(entry->d_name, "..")==0){
                continue;
            }
            //printf("%s %s\n","FOLDER",entry->d_name);
            printdirGuncelleme(entry->d_name,kelimeara,newkelime); // alt klasor olarak buldugunu fonksiyona gonderir
        }


        else{
            if(len > 4 && memcmp(entry->d_name + len - 4, ".txt", 4) == 0){
                FILE *okunacakdosya;
                okunacakdosya=fopen(entry->d_name,"r");
                FILE *geciciyazmadosyasi;
                geciciyazmadosyasi=fopen("/Users/silasener/CLionProjects/lab_pro/cmake-build-debug/input.txt","w+");
                char satir[1000];
                while ((fgets(satir,1000,okunacakdosya))!=NULL)
                {   bulunaniguncelle(satir,aranankelime,yenikelime); //fonksiyonda degistirmeyi yapar
                    fputs(satir,geciciyazmadosyasi);
                }
                fclose(okunacakdosya);
                fclose(geciciyazmadosyasi);
                remove(entry->d_name);
                rename("/Users/silasener/CLionProjects/lab_pro/cmake-build-debug/input.txt",entry->d_name);

            }
        }
    }
    chdir("..");
    closedir(dp);
}

void printdirYazma(char *dir) //case 3 te outputa etiketleri yazdirmak icin kullanildi
{  DIR *dp;
    struct dirent *entry;
    dp = opendir(dir);
    chdir(dir);
    while((entry = readdir(dp)) != NULL) {
        int len = strlen(entry->d_name);
        if(entry->d_type==4)
        { if(strcmp(entry->d_name, ".")==0 || strcmp(entry->d_name, "..")==0){
                continue;
            }
            //printf("%s %s\n","FOLDER",entry->d_name);
            printdirYazma(entry->d_name); // alt klasor olarak buldugunu fonksiyona gonderir
        }
        else{
            if(len > 4 && memcmp(entry->d_name + len - 4, ".txt", 4) == 0){
                // printf("%*s%s\n",depth,"",entry->d_name); //alt klasorlerin txt dosyalarini yazdirir
                char satir[1000];
                FILE *dosya1=fopen(entry->d_name,"r");
                while((fgets(satir,1000,dosya1))!=NULL)
                {   printf(" ");
                    etiket(satir);
                }
                fclose(dosya1);
            }
        }
    }
    chdir("..");
    closedir(dp);
}

void printdirYazma2(char *dir) //case 1 de etiketleri listelemek icin kullanildi
{  DIR *dp;
    struct dirent *entry;
    dp = opendir(dir);
    chdir(dir);
    while((entry = readdir(dp)) != NULL) {
        int len = strlen(entry->d_name);
        if(entry->d_type==4)
        { if(strcmp(entry->d_name, ".")==0 || strcmp(entry->d_name, "..")==0){
                continue;
            }
            //printf("%s %s\n","FOLDER",entry->d_name);
            printdirYazma2(entry->d_name); // alt klasor olarak buldugunu fonksiyona gonderir
        }
        else{
            if(len > 4 && memcmp(entry->d_name + len - 4, ".txt", 4) == 0){
                // printf("%*s%s\n",depth,"",entry->d_name); //txt dosyalarini yazdirir
                char satir[1000];
                FILE *dosya1=fopen(entry->d_name,"r");
                while((fgets(satir,1000,dosya1))!=NULL)
                {   printf("");
                    EtiketListele(satir);
                }
                fclose(dosya1);
            }
        }
    }
    chdir("..");
    closedir(dp);
}

int main(int argc,char* argv[]){
    struct detay liste[1000];
    char unit[1000], c;
    int i = 0,  j = 0, sayac = 0, num = 0;

    for (i = 0; i < 10; i++)
    {
        liste[i].tekrar = 0;
    }
    setlocale(LC_ALL,"Turkish");
    int secim;
    while(1){
        Menu:
        printf("\n*MENU* \n");
        printf("Secim 1: Arama Yapma\n");
        printf("Secim 2: Etiket ve etikete ait txt dosyasinin adini guncelleme \n");
        printf("Secim 3: Dosyaya yazma \n");
        printf("Cikis yapmak icin 0 giriniz\n");
        printf("Yapmak istediginiz islemi secin: ");
        scanf("%d",&secim);
        switch (secim)
        {
            case 1: //printdiryazma2 , etiketlistele ve printdirarama kullanılır
            {  char aranankelime[100];
                printdirYazma2("/Users/silasener/CLionProjects/lab_pro/cmake-build-debug/Üniversite");
                printf("Aranan kelimeyi giriniz:\n ");
                scanf("%s",aranankelime);
                printdirArama("/Users/silasener/CLionProjects/lab_pro/cmake-build-debug/Üniversite",aranankelime);
                break;
            }

            case 2: //printdirguncelleme ve bulunaniguncelle kullanılır
            {  char aranankelime[100]; char yenikelime[100];
                printf("degistirilmesi isteneni giriniz: ");
                scanf("%s",aranankelime);
                printf("yeni kelimeyi giriniz: ");
                scanf("%s",yenikelime);
                printdirGuncelleme("/Users/silasener/CLionProjects/lab_pro/cmake-build-debug/Üniversite",aranankelime,yenikelime);
                printf("%s yerine %s yazildi!",aranankelime,yenikelime);
                break;
            }

            case 3: //printdiryazma ;  etiket ve aktar fonksiyonları kullanılır
            {   FILE *optampon= fopen("/Users/silasener/CLionProjects/lab_pro/cmake-build-debug/Üniversite/tampon.txt","w");
                fclose(optampon);
                printdirYazma("/Users/silasener/CLionProjects/lab_pro/cmake-build-debug/Üniversite");
                FILE *ac= fopen("/Users/silasener/CLionProjects/lab_pro/cmake-build-debug/Üniversite/output.txt","w+");
                FILE *ac2=fopen("/Users/silasener/CLionProjects/lab_pro/cmake-build-debug/Üniversite/tampon.txt","r+");
                char str[10000];
                while ((fgets(str,10000,ac2))!=NULL){
                    for (i = 0; i < strlen(str); i++)
                    {
                        while (i < strlen(str) && str[i]!=' '  && isalnum(str[i]) || str[i]=='_')
                        {
                            unit[j++] = str[i++];
                        }
                        if (j != 0)
                        {
                            unit[j] = '\0';
                            sayac = say(liste, unit, sayac);
                            j = 0;
                        }
                    }

                    fprintf(ac,"\n ETİKETLER  ** TEKRAR SAYİSİ\n");
                    for (i = 0; i < sayac; i++)
                    {
                        fprintf(ac,"%s\t         %d\n", liste[i].etkt, liste[i].tekrar);
                        if (liste[i].tekrar > 1)
                        {
                            num++;
                        }
                    }

                }
                printf("\nEtiketler ve tekrar sayilari output.txt dosyasına listelenmistir!\n");
                fclose(ac2);
                fclose(ac);
                FILE *dosyasil= fopen("/Users/silasener/CLionProjects/lab_pro/cmake-build-debug/Üniversite/tampon.txt","w");
                fclose(dosyasil);
                break;
            }
            default:
                printf("yanlis secim \n");
                break;
        }

        if(secim==0){
            printf("cikis yapilmistir");
            break;
        }
        else
            goto Menu;
    }
    return 0;
}