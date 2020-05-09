#include <stdio.h>

#define max_food 5

void add_food(char(*food)[10], int(*ex_date)[3], int* food_num) {
    /*** Your Code Here ***/
    printf("add food\n"); // delete
}

void show_food(char(*food)[10], int(*ex_date)[3], int food_num) {
    /*** Your Code Here ***/
    printf("show food\n"); // delete
}

void show_expired_food(char(*food)[10], int(*ex_date)[3], int food_num, int *date) {
    /*** Your Code Here ***/
    printf("show expired food\n"); // delete
}

void main() {
    int choice; // 유저가 선택한 메뉴
    char food[max_food][10]; // 식재료 개수 5개, 글자 수 10자 제한
    int expiration_date[max_food][3]; // 유통기한 개수 5개, year, month, date
    int food_num = 0; // 현재 식재료 개수
    int date[3] = { 2020, 3, 15 }; // 오늘 날짜

    printf("<< 자취생 냉장고 관리 프로그램 >> \n\n");

    while (1) {
        printf("행동을 선택하세요 \n");
        printf("1. 식재료 추가하기 \n");
        printf("2. 현재 있는 식재료 보여주기 \n");
        printf("3. 유통기한 지난 식재료 보여주기 \n");
        printf("4. 프로그램 종료 \n\n");

        printf("번호 입력 : ");
        scanf("%d", &choice);
        printf("\n");
        switch (choice) {
            case 1: add_food(food, expiration_date, &food_num); break; /* 식재료 추가 */
            case 2: show_food(food, expiration_date, food_num); break; /* 현재 식재료 보여주기 */
            case 3: show_expired_food(food, expiration_date, food_num, date); break; /* 유통기한 지난 식재료 보여주기 */
        }
        printf("\n");
        if (choice == 4) {
            /* 프로그램을 종료한다. */
            break;
        }
    }
}