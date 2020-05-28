#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define max_food 5

char kind_str[5][7] = { "Meat", "Dairy", "Fruit", "Bread", "Sweets" };

typedef struct Food {
    char *name;
    int expiration_date[3];
    int num;
}Food;

typedef struct Foods {
    int Foodnum, capacity;
    Food* pfood;
}Foods;

void add_food(Foods* pfoods, int* food_num) {
    /*** Your Code Here ***/
    printf("add food\n"); // delete
}

void show_food(Foods* pfoods, int food_number) {
    /*** Your Code Here ***/
    printf("show food\n"); // delete
}

void show_expired_food(Foods* pfoods, int food_number, int date[]) {
    /*** Your Code Here ***/
    printf("show expired food\n"); // delete
}

void change_food_num(Foods* pfoods, int* food_number) {
    /*** Your Code Here ***/
    printf("change_food_num\n"); // delete
}

void main() {
    int choice; // 유저가 선택한 메뉴
    int food_num = 0; // 현재 식재료 개수
    int date[3] = { 2020, 3, 15 }; // 오늘 날짜
    Foods foods[5];
    for (int i = 0; i < 5; ++i) {
        foods[i].pfood = (Foods*) malloc(sizeof(Food) * 2);
        foods[i].capacity = 2;
        foods[i].Foodnum = 0;
    }

    printf("<< 자취생 냉장고 관리 프로그램 >> \n\n");

    while (1) {
        printf("행동을 선택하세요 \n");
        printf("1. 식재료 추가하기 \n");
        printf("2. 현재 있는 식재료 보여주기 \n");
        printf("3. 유통기한 지난 식재료 보여주기 \n");
        printf("4. 식재료 개수 증감 \n");
        printf("5. 프로그램 종료 \n\n");

        printf("번호 입력 : ");
        scanf("%d", &choice);
        printf("\n");
        switch (choice) {
            case 1: add_food(foods, &food_num); break; /* 식재료 추가 */
            case 2: show_food(foods, food_num); break; /* 현재 식재료 보여주기 */
            case 3: show_expired_food(foods, food_num, date); break; /* 유통기한 지난 식재료 보여주기 */
            case 4: change_food_num(foods, &food_num); break; /* 식재료 개수 증감 */

        }
        printf("\n");
        if (choice == 5) {
            /* 프로그램을 종료한다. */
            break;
        }
    }

    for (int i = 0; i < 5; i++)
        free(foods[i].pfood);

}