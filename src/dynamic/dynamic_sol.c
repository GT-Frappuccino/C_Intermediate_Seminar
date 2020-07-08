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
    char input_name[20];
    int tkind;
    Food* temp;
    if (*food_num == max_food) {
        printf("냉장고가 다 찼습니다ㅠㅠ 냉장고를 바꾸던지 식재료를 없애던지 알아서 하세요!!\n");
        return;
    }

    printf("식재료 종류 (0: Meat, 1: Dairy, 2: Fruit, 3: Bread, 4: Sweets): ");
    scanf("%d",&tkind);
    if(pfoods[tkind].capacity <= pfoods[tkind].Foodnum) { // capacity가 Foodnum이하일 때 realloc으로 capacity 확장
        pfoods[tkind].pfood = (Food *)realloc(pfoods[tkind].pfood, sizeof(Food)*(pfoods[tkind].capacity + 2));
        pfoods[tkind].capacity += 2;
        printf("%s capacity를 %d개로 늘렸습니다.\n", kind_str[tkind], pfoods[tkind].capacity);
    }
    temp = pfoods[tkind].pfood;

    printf("식재료 이름: ");
    getchar();
    scanf("%[^\n]s", input_name);
    temp[pfoods[tkind].Foodnum].name = (char*) malloc(sizeof(char) * (strlen(input_name) + 1));
    strcpy(temp[pfoods[tkind].Foodnum].name, input_name);
    printf("%s를 냉장고에 넣었습니다. \n", temp[pfoods[tkind].Foodnum].name);
    printf("식재료 유통기한(ex. 2020 1 23): ");
    for (int i = 0; i < 3; i++)
        scanf("%d", &temp[pfoods[tkind].Foodnum].expiration_date[i]);

    printf("%s의 유통기한은 %4d년 %2d월 %2d일입니다. 상하기 전에 빨리 먹으세요.^^ \n", temp[pfoods[tkind].Foodnum].name, temp[pfoods[tkind].Foodnum].expiration_date[0],
           temp[pfoods[tkind].Foodnum].expiration_date[1], temp[pfoods[tkind].Foodnum].expiration_date[2]);
    printf("식재료 개수: ");
    scanf("%d", &temp[pfoods[tkind].Foodnum].num);

    pfoods[tkind].Foodnum++;
    (*food_num)++;

}

void show_food(Foods* pfoods, int food_number) {
    Food temp;
    int k = 1;
    if (!food_number) {
        printf("식재료가 없습니다. 냉장고에게 식재료를 주세요ㅠㅠ.\n");
        return;
    }
    for (int i = 0; i < 5; i++) {
        if(pfoods[i].Foodnum == 0)
            continue;
        printf("%s\n", kind_str[i]);
        for (int j = 0; j < pfoods[i].Foodnum; j++) {
            temp = pfoods[i].pfood[j];
            printf("%d: ", k++);
            printf("%-10s | %4d년 %2d월 %2d일 | %2d개\n", temp.name, temp.expiration_date[0], temp.expiration_date[1], temp.expiration_date[2], temp.num);
        }
    }
}

void show_expired_food(Foods* pfoods, int food_number, int date[]) {
    Food temp;
    if (!food_number) {
        printf("식재료가 없습니다. 냉장고에게 식재료를 주세요ㅠㅠ.\n");
        return;
    }
    for (int i = 0; i < 5; i++) {
        for (int j = 0; j < pfoods[i].Foodnum; j++) {
            temp = pfoods[i].pfood[j];
            for (int k = 0; k < 3; k++) {
                if (date[k] > temp.expiration_date[k]) {
                    printf("%-10s | %4d년 %2d월 %2d일 | %2d개\n", temp.name, temp.expiration_date[0], temp.expiration_date[1], temp.expiration_date[2], temp.num);
                    break;
                }
                else if (date[k] < temp.expiration_date[k])
                    break;
            }
        }
    }
}

void change_food_num(Foods* pfoods, int* food_number) {

    int food_to_change, num_to_change, sum = 0;
    if (!*food_number) {
        printf("식재료가 없습니다. 냉장고에게 식재료를 주세요ㅠㅠ.\n");
        return;
    }
    printf("<< 현재 냉장고 상황 >>\n");
    show_food(pfoods, *food_number);
    printf("\n");
    printf("개수를 바꾸고 싶은 식재료 번호: ");
    scanf("%d", &food_to_change);
    printf("바꾸고 싶은 개수 (ex. 2: 2개 증가, -2: 2개 감소): ");
    scanf("%d", &num_to_change);

    for (int i = 0; i < 5; i++) {
        sum += pfoods[i].Foodnum;
        if(sum >= food_to_change) {
            sum -= pfoods[i].Foodnum;
            pfoods[i].pfood[food_to_change-sum-1].num += num_to_change; // 개수 조정
            if(pfoods[i].pfood[food_to_change-sum-1].num <= 0) {
                printf("%s개수가 0개 이하이므로 관리대상에서 제거합니다. 다른 식재료를 사와서 빈 자리를 채워주세요!^^\n\n", pfoods[i].pfood[food_to_change-sum-1].name);
                for (int j = food_to_change-sum-1; j < pfoods[i].Foodnum; ++j) {
                    pfoods[i].pfood[j] = pfoods[i].pfood[j+1];
                }
                (*food_number)--;
                pfoods[i].Foodnum--;
                break;
            }
            printf("바뀐 식재료 정보\n");
            printf("%-10s | %4d년 %2d월 %2d일 | %2d개\n", pfoods[i].pfood[food_to_change-sum-1].name, pfoods[i].pfood[food_to_change-sum-1].expiration_date[0],
                   pfoods[i].pfood[food_to_change-sum-1].expiration_date[1], pfoods[i].pfood[food_to_change-sum-1].expiration_date[2], pfoods[i].pfood[food_to_change-sum-1].num);
            break;
        }
    }
}

void main() {
    int choice; // 유저가 선택한 메뉴
    int food_num = 0; // 현재 식재료 개수
    int date[3] = { 2020, 3, 15 }; // 오늘 날짜
    Foods foods[5];
    for (int i = 0; i < 5; ++i) {
        foods[i].pfood = (Food*) malloc(sizeof(Food) * 2);
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