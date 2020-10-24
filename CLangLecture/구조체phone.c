#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <string.h>


struct _Phone {
    int nationalNumber;
    char myNumber[15];
};

typedef struct _Phone Phone;

//typedef struct _Person Person;
//typedef struct _Person {
//    char name[20];
//    int age;
//    Phone myPhone;
//}Person;

typedef struct {
    char name[20];
    int age;
    Phone myPhone;
}Person;


int main()
{
    Person kim;

    kim.myPhone.nationalNumber = 82;
    strcpy(kim.myPhone.myNumber, "01012345678");

    printf("국가번호 : %d\n", kim.myPhone.nationalNumber);
    printf("전화번호 : %s\n", kim.myPhone.myNumber);

    return 0;
}