#ifndef SRC_FILE_H
#define SRC_FILE_H

#endif //SRC_FILE_H

#define max_food 5

typedef struct Food {
    char *name;
    int expiration_date[3];
    int num;
}Food;

typedef struct Foods {
    int Foodnum, capacity;
    Food* pfood;
}Foods;

void add_food(Foods* pfoods, int* food_num);
void show_food(Foods* pfoods, int food_number);
void show_expired_food(Foods* pfoods, int food_number, int date[]);
void change_food_num(Foods* pfoods, int* food_number);
void load_food_data(Foods* pfoods, int* food_number, char* filename);
void save_food_data(Foods* pfoods, int food_number);