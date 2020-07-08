#include <stdio.h>

#define max_food 3

struct Food {
    char name[10]; // 이름
    int expiration_date[3]; // 유통기한
    int num; // 개수
} ;

void add_food(struct Food *ptr, int* food_num) {
    ptr += *food_num;

    if (*food_num == max_food) {
        printf("냉장고가 다 찼습니다ㅠㅠ 냉장고를 바꾸던지 식재료를 없애세요!!");
        return;
    }

    printf("식재료 이름: ");
    scanf("%s", ptr->name);
    printf("%s를 냉장고에 넣었습니다. \n", ptr->name);
    printf("식재료 유통기한(ex. 2020 1 23): ");
    for (int i = 0; i < 3; i++)
        scanf("%d", &ptr->expiration_date[i]);
    printf("%s의 유통기한은 %4d년 %2d월 %2d일입니다. 상하기 전에 빨리 먹으세요.^^ \n", ptr->name, ptr->expiration_date[0], ptr->expiration_date[1], ptr->expiration_date[2]);
    printf("식재료 개수: ");
    scanf("%d", &ptr->num);

    (*food_num)++;
}

void show_food(struct Food* ptr, int food_number) {
    if (!food_number)
        printf("식재료가 없습니다. 냉장고에게 식재료를 주세요ㅠㅠ.\n");
    for (int i = 0; i < food_number; i++)
        printf("%-10s | %4d년 %2d월 %2d일 | %2d개 \n", ptr[i].name, ptr[i].expiration_date[0], ptr[i].expiration_date[1], ptr[i].expiration_date[2], ptr[i].num);
}

void show_expired_food(struct Food* ptr, int food_number, int date[]) {
    if (!food_number) {
        printf("식재료가 없습니다. 냉장고에게 식재료를 주세요ㅠㅠ.\n");
        return;
    }
    for (int i = 0; i < food_number; i++) {
        for (int j = 0; j < 3; j++) {
            if (date[j] > ptr->expiration_date[j]) {
                printf("%-10s | %4d년 %2d월 %2d일 | %2d개 ", ptr->name, ptr->expiration_date[0], ptr->expiration_date[1], ptr->expiration_date[2], ptr->num);
                printf("\n");
                break;
            }
            else if (date[j] < ptr->expiration_date[j])
                break;
        }
        ptr++;
    }
}

void change_food_num(struct Food* ptr, int* food_number) {

    int food_to_change, num_to_change = 0;
    if (*food_number == 0) {
        printf("식재료가 없습니다. 냉장고에게 식재료를 주세요ㅠㅠ.\n");
        return;
    }

    printf("<< 현재 냉장고 상황 >>\n");
    for (int i = 0; i < *food_number; i++) {
        printf("%d: %-10s | %4d년 %2d월 %2d일 | %2d개 \n", i + 1, ptr[i].name, ptr[i].expiration_date[0], ptr[i].expiration_date[1], ptr[i].expiration_date[2], ptr[i].num);
    }

    printf("\n");
    printf("개수를 바꾸고 싶은 식재료 번호: ");
    scanf("%d", &food_to_change);
    printf("바꾸고 싶은 개수 (ex. 2: 2개 증가, -2: 2개 감소): ");
    scanf("%d", &num_to_change);
    (ptr += food_to_change - 1)->num += num_to_change; // 개수 조정

    if (ptr->num <= 0) {
        printf("%s개수가 0개 이하이므로 관리대상에서 제거합니다. 다른 식재료를 사와서 빈 자리를 채워주세요!^^\n", ptr->name);
        for (int i = 0; i < *food_number - food_to_change; i++)
            *(ptr + i) = *(ptr + i + 1);
        (*food_number)--;
        return;
    }
    printf("바뀐 식재료 정보\n");
    printf("%-10s | %4d년 %2d월 %2d일 | %2d개 \n", ptr->name, ptr->expiration_date[0], ptr->expiration_date[1], ptr->expiration_date[2], ptr->num);
}

void main() {
    int choice; /* 유저가 선택한 메뉴*/
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
            case 1: add_food(food_ptr, &food_num); break;
            case 2: show_food(food_ptr, food_num); break;
            case 3: show_expired_food(food_ptr, food_num, date); break;
            case 4: change_food_num(food_ptr, &food_num); break;

        }
        printf("\n");
        if (choice == 5) {
            /* 프로그램을 종료한다. */
            break;
        }
    }
}