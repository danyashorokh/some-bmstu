// vychit.cpp : Defines the entry point for the console application.
//
#include "stdafx.h"
#include "stdio.h"
#include "conio.h"
#include "ctype.h"
#include "string.h"

int _tmain(int argc, _TCHAR* argv[])
{const int kk=200;
	char s[kk];
	int a[kk],b[kk],c[kk];//было int
	int i,j=0,n1=0,n2=0,shet,z1,z2,w1,w2,w3,w4,pokaz=0;//w1-количество цифр до запятой,z1-после запятой
	bool p=true;
	puts("Vvedite pervoe chislo");
	gets(s);
	//запись и переворот 1го числа

	j=0;
for(i=0;i<strlen(s);i++)
if((s[strlen(s)-i-1]!=',')&&(s[strlen(s)-i-1]!='.'))
	{a[j] = s[strlen(s)-i-1] - '0';
n1++;
j++;}
else
{z1=i;
p=false;}
w1=strlen(s)-z1-1;
//вывод 1го числа
	for(i=n1-1;i>=0;i--)
	printf("%d",a[i]);
	printf("\n");
puts("Vvedite vtoroe chislo");
gets(s);
//запись и переворот 2го числа
j=0;
for(i=0;i<strlen(s);i++)
if((s[strlen(s)-i-1]!=',')&&(s[strlen(s)-i-1]!='.'))
	{b[j]=s[strlen(s)-i-1] - '0';
n2++;
j++;}
else 
	{z2=i;

p=false;}
w2=strlen(s)-z2-1;
//вывод 2го числа
for(i=n2-1;i>=0;i--)
	printf("%d",b[i]);
printf("\n");
//добавление нулей
if(n1>=n2)
{
for(i=n2;i<=n1;i++)
b[i]=0;
shet=n1;
}
else
{
for(i=n1;i<=n2;i++)
a[i]=0;
shet=n2;
}

printf("vedennye chisla posle dobavleniya nulei:\n");
//вывод 1го числа
	for(i=shet-1;i>=0;i--)
	printf("%d",a[i]);
	printf("\n");
//вывод 2го числа
for(i=shet-1;i>=0;i--)
	printf("%d",b[i]);
printf("\n");
//printf("%d %d %d %d",w1,z1,w2,z2);
printf("\n");
//вычитание

for(i=0;i<=shet-1;i++)
{if(a[shet-1]>=b[shet-1])//если первая цифра у первого числа больше,чем у второго-считаем обычным образом
  {

	if(a[i]<b[i])
	{c[i]=10.0+a[i]-b[i];
	a[i+1]--;
	}
	else c[i]=a[i]-b[i];

  }else //иначе-считаем наоборот и добавляем знак минус в начале
    {if(b[i]<a[i])
      {c[i]=10.0+b[i]-a[i];
      b[i+1]--;
      }
          else c[i]=b[i]-a[i];
		pokaz++;
    }
}
printf("rezultat:\n");
if(pokaz>0)
printf("-");
for(i=shet-1;i>=0;i--)
printf("%d",c[i]);
printf("\n");
getch();
return 0;
}
/*Объем памяти, необходимый для хранения массива, непосредственно определяется его типом и размером. Для одномерного массива количество байтов памяти вычисляется следующим образом:

количество_байтов = sizeof(базовый_тип) × длина_массива*/

