#include <stdio.h>

#define max_food 3

struct Food {
    char name[10]; // 이름
    int expiration_date[3]; // 유통기한
    int num; // 개수
};

void add_food(struct Food *ptr, int* food_num) {
    /*** Your Code Here ***/
    printf("add food\n"); // delete
}

void show_food(struct Food* ptr, int food_num) {
    /*** Your Code Here ***/
    printf("show food\n"); // delete
}

void show_expired_food(struct Food* ptr, int food_num, int date[]) {
    /*** Your Code Here ***/
    printf("show expired food\n"); // delete
}

void change_food_num(struct Food* ptr, int* food_num, int date[]) {
    /*** Your Code Here ***/
    printf("change_food_num\n"); // delete
}

void main() {
    int choice; // 유저가 선택한 메뉴
    int food_num = 0; // 현재 식재료 개수
    int date[3] = { 2020, 3, 15 }; // 오늘 날짜
    struct Food food[max_food];
    struct Food* food_ptr = food;
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
            case 1: add_food(food_ptr, &food_num); break; /* 식재료 추가 */
            case 2: show_food(food_ptr, food_num); break; /* 현재 식재료 보여주기 */
            case 3: show_expired_food(food_ptr, food_num, date); break; /* 유통기한 지난 식재료 보여주기 */
            case 4: change_food_num(food_ptr, &food_num, date); break; /* 식재료 개수 증감 */

        }
        printf("\n");
        if (choice == 5) {
            /* 프로그램을 종료한다. */
            break;
        }
    }
}