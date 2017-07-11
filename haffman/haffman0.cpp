// haffman0.cpp : Defines the entry point for the console application.
//
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "stdafx.h"
#include <iostream>
#include "conio.h"
#include "ctype.h"

struct sym 
{
        unsigned char ch;
        float freq;
		char code[255];
        sym *left;
        sym *right;
};
struct block
{
        unsigned char bch;
		int bh;
        float freq1;
		char code1[255];
		block *left1;
        block *right1;
};
sym *makeTree(sym *psym[],int k)//рeкурсивная функция создания дерева Хофмана v1
{
    sym *temp;
    temp=(sym*)malloc(sizeof(sym));
    temp->freq=psym[k-1]->freq+psym[k-2]->freq;
    temp->code[0]=0;
    temp->left=psym[k-1];
    temp->right=psym[k-2];
 
    if(k==2)
        return temp;
    else //внесение в массив в нужное место элемента дерева Хофмана v1
    {
        for(int i=0;i<k;i++)
            if (temp->freq>psym[i]->freq)
            {   
                for(int j=k-1;j>i;j--)
                    psym[j]=psym[j-1];                                  
                
                psym[i]=temp;
                break;
            }       
    }
return makeTree(psym,k-1);
}
void makeCodes(sym *root)//Рекурсивная функция кодирования v1
{
    if(root->left)
    {
        strcpy(root->left->code,root->code);
        strcat(root->left->code,"0");
        makeCodes(root->left);
    }
    if(root->right)
    {
        strcpy(root->right->code,root->code);
        strcat(root->right->code,"1");
        makeCodes(root->right);
    }
}
block *makeTree1(block *psym1[],int k1)//рeкурсивная функция создания дерева Хофмана v2
{
    block *temp1;
    temp1=(block*)malloc(sizeof(block));
    temp1->freq1=psym1[k1-1]->freq1+psym1[k1-2]->freq1;
    temp1->code1[0]=0;
    temp1->left1=psym1[k1-1];
    temp1->right1=psym1[k1-2];
 
    if(k1==2)
        return temp1;
    else //внесение в массив в нужное место элемента дерева Хофмана v2
    {
        for(int i=0;i<k1;i++)
            if (temp1->freq1>psym1[i]->freq1)
            {   
                for(int j=k1-1;j>i;j--)
                    psym1[j]=psym1[j-1];                                  
                
                psym1[i]=temp1;
                break;
            }       
    }
return makeTree1(psym1,k1-1);
}
void makeCodes1(block *root1)//Рекурсивная функция кодирования v2
{
    if(root1->left1)
    {
        strcpy(root1->left1->code1,root1->code1);
        strcat(root1->left1->code1,"0");
        makeCodes1(root1->left1);
    }
    if(root1->right1)
    {
        strcpy(root1->right1->code1,root1->code1);
        strcat(root1->right1->code1,"1");
        makeCodes1(root1->right1);
    }
}

int main ()
{
    FILE *f1,*f2,*f3,*f4,*f5; 
    f1=fopen("a.txt","r"); //файл с исходным текстом
    f2=fopen("b.txt","wb");//файл для записи бинарного кода v1
    f3=fopen("c.txt","w");//файл для записи бинарного кода v2 (кодирование блоками)
    f4=fopen("d.txt","w");//текст из "4-х" букв
	f5=fopen("e.txt","w");//файл для записи результатов
    int size1f=0;// размер 1ого закодир. текста
	int size11=0;// количество "единиц" в 1ом закодир. тексте
	int size10=0;// количество "нулей" в 1ом закодир. тексте
    int size2f=0;// размер 2ого закодир. текста
	int size21=0;// количество "единиц" во 2ом закодир. тексте
	int size20=0;// количество "нулей" во 2ом закодир. тексте
	int chh,che;  // в эту переменную читается информация из файла
    int k=0; //счётчик количества различных букв, уникальных символов
    int kk=0; // счётчик количества всех знаков в файле
    int kolvo[256]={0};//инициализируем массив количества уникальных символов
    sym simbols[256]={0}; //инициализируем массив записей v1
    sym *psym[256]; //инициализируем массив указателей на записи v1
    float summir=0;//сумма частот встречаемости
    char j=0;//вспомогательная переменная
	int max1,max2,min1,min2,n1,n2,n3,n4,b1,b2,b3,b4,jj=0,mas[26],razmer=0,raz=0;
	char alf[]={'a','b','c','d','e','f','g','h','i','j','k','l','m','n','o','p','q','r','s','t','u','v','w','x','y','z'};
	char chc,aa[13000],c1,c2;
    for (int zz=0;zz<26;zz++)mas[zz]=0;

	//Обработка ошибок чтения файла
    if(f1==NULL)
    {
        puts("Error");
        return 0;
    }
    //Считывание текста в строку
	while((chc = getc(f1)) != EOF){
		
	fgets(aa,13000,f1);
	for(int ii=0;ii<sizeof(aa);ii++) {
		for(int u=0;u<26;u++)
		if (aa[ii]==alf[u])mas[u]++;
	}	
	}
	for(int r=0;r<26;r++)
		razmer+=mas[r];
	
	//поиск "популярных" и "непопулярных" букв
	max1=mas[0];n1=0;
	for(b1=0;b1<=25;b1++){
	
		if (mas[b1]>max1){
		max1 = mas[b1];
		n1=b1;}
	}
	max2=mas[0];n2=0;
	for(b2=0;b2<=25;b2++){
		if ((mas[b2]>max2)&&(mas[b2]!=max1)){
		max2=mas[b2];
		n2=b2;
		}}
	min1=mas[0];n3=0;
	for(b3=0;b3<=25;b3++){
	
		if (mas[b3]<min1){
		min1 = mas[b3];
		n3=b3;}
	}
	min2=mas[0];n4=0;
	for(b4=0;b4<=25;b4++){
		if ((mas[b4]<min2)&&(mas[b4]!=min1)){
		min2=mas[b4];
		n4=b4;
		}}
	int sum1=mas[n1]+mas[n2]+mas[n3]+mas[n4];
	
	char *dd = new char[sum1];//строка под текст из 4х букв
	for(int ii=0;ii<sizeof(aa);ii++){
		if((aa[ii]==alf[n1])||(aa[ii]==alf[n2])||(aa[ii]==alf[n3])||(aa[ii]==alf[n4])){
	dd[jj]=aa[ii];
	jj++;}
	}
	for(int ss=0;ss<sum1;ss++)
	fprintf(f4,"%c",dd[ss]);	

    /*for(int r=0;r<26;r++)
    printf("%c = %d\n",alf[r],mas[r]);*/
	
	fclose(f4);
	f4=fopen("d.txt","r");


    sym *symbols=(sym*)malloc(k*sizeof(sym));//создание динамического массива структур simbols v1
    sym **psum=(sym**)malloc(k*sizeof(sym*));//создание динамического массива указателей на simbols v1
    
    //Начинаем читать файл и составлять таблицу встречаемости
    while((chh=fgetc(f4))!=EOF)
    {       
        for(int j=0; j<256; j++)
        {
            if (chh==simbols[j].ch)
            {
                kolvo[j]++;
                kk++;               
                break;
            }
            if (simbols[j].ch==0)
            {
                simbols[j].ch=(unsigned char)chh;
                kolvo[j]=1;
                k++; kk++;
                break;
            }           
        }       
    }
 
    // Рассчёт частоты встречаемости
    for(int i=0;i<k;i++)
        simbols[i].freq=(float)kolvo[i]/kk;
    
    for(int i=0;i<k;i++) //в массив указателей заносим адреса записей
        psym[i]=&simbols[i];
    
	//Сортировка по убыванию 
    sym tempp;
    for(int i=1;i<k;i++)
        for(int j=0;j<k-1;j++)
            if(simbols[j].freq<simbols[j+1].freq)
            {
                tempp=simbols[j];
                simbols[j]=simbols[j+1];
                simbols[j+1]=tempp;
            }
 
	for(int i=0;i<k;i++){
    summir+=simbols[i].freq;    
    printf("Ch= %d\tFreq= %f\tPPP= %c\t\n",simbols[i].ch,simbols[i].freq,psym[i]->ch,i);
	}
    printf("\nVsego bukv = %d\tSumma = %f\n",kk,summir);
    
    sym *root=makeTree(psym,k);//вызов функции создания дерева Хофмана v1
    
    makeCodes(root);//вызов функции получения кода v1
 
    rewind(f1);//возвращаем указатель в файле в начало файла
	//в цикле читаем исходный файл, и записываем полученные в функциях коды в промежуточный файл v1
	while((chh=fgetc(f1))!=EOF){
		for(int i=0;i<k;i++)
			if(chh==simbols[i].ch)
				fputs(simbols[i].code,f2);
	}
	fclose(f2);

	//Печать кода каждой буквы v1
	for(int i=0;i<k;i++)
	printf("%s  ",simbols[i].code);
	printf("\n\n");

	block simbols1[16]={0};// для блоков
	block *psym1[16];
	block *symbols1=(block*)malloc(sizeof(block));//создание динамического массива структур simbols1 v2
	block **psum1=(block**)malloc(sizeof(block*));//создание динамического массива указателей на simbols1 v2

	//---------------Кодирование блоками----------------

	//Подсчет вероятностей блоков
	simbols1[0].freq1=(float)((simbols[0].freq)*(simbols[0].freq)); //ee 
	simbols1[1].freq1=(float)((simbols[0].freq)*(simbols[1].freq)); //ea
	simbols1[2].freq1=(float)((simbols[0].freq)*(simbols[2].freq)); //eq
	simbols1[3].freq1=(float)((simbols[0].freq)*(simbols[3].freq)); //ez
	simbols1[4].freq1=(float)((simbols[1].freq)*(simbols[0].freq)); //ae
	simbols1[5].freq1=(float)((simbols[1].freq)*(simbols[1].freq)); //aa
	simbols1[6].freq1=(float)((simbols[1].freq)*(simbols[2].freq)); //aq
	simbols1[7].freq1=(float)((simbols[1].freq)*(simbols[3].freq)); //az
	simbols1[8].freq1=(float)((simbols[2].freq)*(simbols[0].freq)); //qe
	simbols1[9].freq1=(float)((simbols[2].freq)*(simbols[1].freq)); //qa
	simbols1[10].freq1=(float)((simbols[2].freq)*(simbols[2].freq)); //qq
	simbols1[11].freq1=(float)((simbols[2].freq)*(simbols[3].freq)); //qz
	simbols1[12].freq1=(float)((simbols[3].freq)*(simbols[0].freq)); //ze
	simbols1[13].freq1=(float)((simbols[3].freq)*(simbols[1].freq)); //za
	simbols1[14].freq1=(float)((simbols[3].freq)*(simbols[2].freq)); //zq
	simbols1[15].freq1=(float)((simbols[3].freq)*(simbols[3].freq)); //zz

	for(int i=0;i<16;i++) //в массив указателей заносим адреса записей v2 
	psym1[i]=&simbols1[i];

	//Сортировка по убыванию  v2
    block temppp;
    for(int i=1;i<16;i++)
        for(int j=0;j<16-1;j++)
            if(simbols1[j].freq1<simbols1[j+1].freq1)
            {
                temppp=simbols1[j];
                simbols1[j]=simbols1[j+1];
                simbols1[j+1]=temppp;
            }

	block *root1=makeTree1(psym1,16);//вызов функции создания дерева Хофмана v2
	makeCodes1(root1);//вызов функции получения кода v2
	rewind(f1);//возвращаем указатель в файле в начало файла

	//Запись кода блоков в файл
	for(int i=0;i<kk;i++){
	if((dd[2*i]==alf[n1])&&(dd[2*i+1]==alf[n1]))
	fputs(simbols1[0].code1,f3);
	else if((dd[2*i]==alf[n1])&&(dd[2*i+1]==alf[n2]))
	fputs(simbols1[1].code1,f3);
	else if((dd[2*i]==alf[n2])&&(dd[2*i+1]==alf[n1]))
	fputs(simbols1[2].code1,f3);
	else if((dd[2*i]==alf[n2])&&(dd[2*i+1]==alf[n2]))
	fputs(simbols1[3].code1,f3);
	else if((dd[2*i]==alf[n1])&&(dd[2*i+1]==alf[n4]))
	fputs(simbols1[4].code1,f3);
	else if((dd[2*i]==alf[n4])&&(dd[2*i+1]==alf[n1]))
	fputs(simbols1[5].code1,f3);
	else if((dd[2*i]==alf[n2])&&(dd[2*i+1]==alf[n4]))
	fputs(simbols1[6].code1,f3);
	else if((dd[2*i]==alf[n4])&&(dd[2*i+1]==alf[n2]))
	fputs(simbols1[7].code1,f3);
	else if((dd[2*i]==alf[n1])&&(dd[2*i+1]==alf[n3]))
	fputs(simbols1[8].code1,f3);
	else if((dd[2*i]==alf[n3])&&(dd[2*i+1]==alf[n1]))
	fputs(simbols1[9].code1,f3);
	else if((dd[2*i]==alf[n2])&&(dd[2*i+1]==alf[n3]))
	fputs(simbols1[10].code1,f3);
	else if((dd[2*i]==alf[n3])&&(dd[2*i+1]==alf[n2]))
	fputs(simbols1[11].code1,f3);
	else if((dd[2*i]==alf[n4])&&(dd[2*i+1]==alf[n4]))
	fputs(simbols1[12].code1,f3);
	else if((dd[2*i]==alf[n4])&&(dd[2*i+1]==alf[n3]))
	fputs(simbols1[13].code1,f3);
	else if((dd[2*i]==alf[n3])&&(dd[2*i+1]==alf[n4]))
	fputs(simbols1[14].code1,f3);
	else if((dd[2*i]==alf[n3])&&(dd[2*i+1]==alf[n3]))
	fputs(simbols1[15].code1,f3);
	}
	fclose(f3);

	//Подсчет размера файлов и количества "1" и "0"
	f2=fopen("b.txt","r");
	f3=fopen("c.txt","r");
	while((c1=fgetc(f2))!=EOF){
		if(c1=='1'){size11++;}
		if(c1=='0'){size10++;}
		size1f++;
	}
	while((c2=fgetc(f3))!=EOF){
		if(c2=='1'){size21++;}
		if(c2=='0'){size20++;}
		size2f++;
	}
	float proc=100-(((float)size2f/(float)size1f)*100);
	printf("1 file# vsego: %d, 1: %d, 0: %d\n",size1f,size11,size10);
	printf("2 file# vsego: %d, 1: %d, 0: %d\n",size2f,size21,size20);
	printf("kodirovanie blokami effectivnee na %4.1f procenta\n",proc);
	printf("\n");
	//Запись результатов в файл
	fprintf(f5,"v tekste iz 4x bukv %d simvolov\n\n",kk);
	fprintf(f5,"1 file# vsego: %d, 1: %d, 0: %d\n\n",size1f,size11,size10);
	fprintf(f5,"2 file# vsego: %d, 1: %d, 0: %d\n\n",size2f,size21,size20);
	fprintf(f5,"kodirovanie blokami effectivnee na %4.1f procenta\n",proc);
	for(int i=0;i<4;i++)
	fprintf(f5,"%s\n",simbols[i].code);
	fprintf(f5,"\n\n");
	for(int i=0;i<16;i++)
	fprintf(f5,"%s\n",simbols1[i].code1);

	for(int i=0;i<16;i++)
	printf("%s\n",simbols1[i].code1);
	printf("\n\n");
	//for(int i=0;i<16;i++)
	//printf("%f \n",simbols1[i].freq1);

	fcloseall();//закрываем все открытые файлы

	getch();
	return 0;
}