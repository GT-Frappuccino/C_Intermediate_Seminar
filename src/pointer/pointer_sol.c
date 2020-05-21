#include <stdio.h>

#define max_food 5

void add_food(char(*food)[10], int(*ex_date)[3], int* food_num) {
    if (*food_num == max_food) {
        printf("냉장고가 다 찼습니다ㅠㅠ 냉장고를 바꾸던지 식재료를 없애세요!!");
        return;
    }
    printf("식재료 이름: ");
    scanf("%s", food[*food_num]);
    printf("%s를 냉장고에 넣었습니다. \n", food[*food_num]);
    printf("식재료 유통기한(ex. 2020 1 23): ");
    for (int i = 0; i < 3; i++)
        scanf("%d", &ex_date[*food_num][i]);
    printf("%s의 유통기한은 %4d년 %2d월 %2d일입니다. 상하기 전에 빨리 먹으세요 ^^ \n", food, ex_date[*food_num][0], ex_date[*food_num][1], ex_date[*food_num][2]);
    (*food_num)++;
}

void show_food(char(*food)[10], int(*ex_date)[3], int food_num) {
    if (!food_num)
        printf("식재료가 없습니다. 냉장고에게 식재료를 주세요 ㅠㅠ\n");
    for (int i = 0; i < food_num; i++)
        printf("%-10s | %4d년 %2d월 %2d일\n", food[i], ex_date[i][0], ex_date[i][1], ex_date[i][2]); // 식재료 정보 printf
}

void show_expired_food(char(*food)[10], int(*ex_date)[3], int food_num, int *date) {
    for (int i = 0; i < food_num; i++) {
        for (int j = 0; j < 3; j++)
            if (date[j] > ex_date[i][j]) {
                printf("%-10s | %4d년 %2d월 %2d일\n", food[i], ex_date[i][0], ex_date[i][1], ex_date[i][2]);
                break;
            }
            else if (date[j] < ex_date[i][j])
                break;
    }
    printf("\n");
}

void main() {
    int choice; /* 유저가 선택한 메뉴*/
    char food[max_food][10]; // 식재료 개수 5개, 글자 수 10자 제한 // 나중에 동적할당으로 -> char *food[5]
    int expiration_date[max_food][3]; // 5개, year, month, date
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