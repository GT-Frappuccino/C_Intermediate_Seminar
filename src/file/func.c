#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "file.h"

char kind_str[5][7] = { "Meat", "Dairy", "Fruit", "Bread", "Sweets" };

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

void load_food_data(Foods* pfoods, int* food_number, char* filename){

    char c, buf[100], n[20];
    Food* temp;

    FILE *ff = fopen(filename, "r");
    fseek(ff, 0, SEEK_SET);
    fscanf(ff, "%s", buf);
    for (int i = 0; i < 5; i++) {

        if(strcmp(kind_str[i], buf) == 0) { // buf가 음식 종류일 때
            do {
                if(pfoods[i].Foodnum >= pfoods[i].capacity) { // capacity가 Foodnum이하일 때 realloc으로 capacity 확장
                    pfoods[i].pfood = (Food *)realloc(pfoods[i].pfood, sizeof(Food)*(pfoods[i].capacity + 2));
                    pfoods[i].capacity += 2;
                }

                temp = pfoods[i].pfood;
                fscanf(ff, "%s %*s %d%*s %d%*s %d%*s %*s %d%*s ", n, temp[pfoods[i].Foodnum].expiration_date, temp[pfoods[i].Foodnum].expiration_date+1, temp[pfoods[i].Foodnum].expiration_date+2, &temp[pfoods[i].Foodnum].num);
                temp[pfoods[i].Foodnum].name = (char*) malloc(sizeof(char) * (strlen(n) + 1));
                strcpy(temp[pfoods[i].Foodnum].name, n);

                pfoods[i].Foodnum ++;
                (*food_number)++;

                if (fscanf(ff, "%[^\n]s", buf) == EOF){
                    printf("loading %s...\n\n", filename);
                    fclose(ff);
                    return;
                }
                fseek(ff, (-1)*strlen(buf), SEEK_CUR);
            }
            while (strlen(buf) > 10); // 같은 종류 음식이 더 있는지 확인
        }
    }
}
void save_food_data(Foods* pfoods, int food_number){

    if (!food_number) {
        printf("식재료가 없어서 빈 텍스트 문서를 저장합니다.\n");
        FILE *fp = fopen("food_data.txt", "w");
        fclose(fp);
        return;
    }

    FILE *fp = fopen("food_data.txt", "w");
    Food temp;
    int k = 1;

    for (int i = 0; i < 5; i++) {
        if(pfoods[i].Foodnum == 0)
            continue;

        fprintf(fp, "%s\n", kind_str[i]);
        for (int j = 0; j < pfoods[i].Foodnum; j++) {
            temp = pfoods[i].pfood[j];
            fprintf(fp, "%-10s | %4d년 %2d월 %2d일 | %2d개\n", temp.name, temp.expiration_date[0], temp.expiration_date[1], temp.expiration_date[2], temp.num);
        }
    }
    printf("데이터가 저장되었습니다. 프로그램을 종료합니다.\n");
    fclose(fp);
}