#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "file.h"

void main(int argc, char** argv) {
    int choice; // 유저가 선택한 메뉴
    int food_num = 0; // 현재 식재료 개수
    int date[3] = { 2020, 3, 15 }; // 오늘 날짜
    Foods foods[5];
    for (int i = 0; i < 5; ++i) {
        foods[i].pfood = (Food*) malloc(sizeof(Food) * 2);
        foods[i].capacity = 2;
        foods[i].Foodnum = 0;
    }
    if (argc > 1) // 이전 data 불러오기
        load_food_data(foods, &food_num, argv[1]);

    printf("<< 자취생 냉장고 관리 프로그램 >> \n\n");

    while (1) {
        printf("행동을 선택하세요 \n");
        printf("1. 식재료 추가하기 \n");
        printf("2. 현재 있는 식재료 보여주기 \n");
        printf("3. 유통기한 지난 식재료 보여주기 \n");
        printf("4. 식재료 개수 증감 \n");
        printf("5. 데이터 저장하고 프로그램 종료 \n");

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
            save_food_data(foods, food_num); /* 데이터 저장하고 프로그램 종료 */
            break;
        }
    }

    for (int i = 0; i < 5; i++)
        free(foods[i].pfood);

}