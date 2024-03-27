#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_LINE_LENGTH 100
#define MAX_SUBJECTS 10
#define MAX_STUDENTS 100

// Структура для хранения информации о студенте
struct Student {
    char name[MAX_LINE_LENGTH];
    float grades[MAX_SUBJECTS];
    int num_grades;
};

// Функция для вычисления среднего балла студента
float calculateAverage(float *grades, int num_grades) {
    float sum = 0;
    for (int i = 0; i < num_grades; i++) {
        sum += grades[i];
    }
    return sum / num_grades;
}

int main() {
    FILE *input_file;
    FILE *output_file;
    char line[MAX_LINE_LENGTH];
    struct Student students[MAX_STUDENTS];
    int num_students = 0;

    // Открываем файл для чтения
    input_file = fopen("in.txt", "r");

    // Читаем данные из файла и сохраняем их в структуру Студент
    while (fgets(line, MAX_LINE_LENGTH, input_file) != NULL) {
        char *token = strtok(line, ",");
        strcpy(students[num_students].name, token);
        int index = 0;
        token = strtok(NULL, ",");
        while (token != NULL) {
            students[num_students].grades[index] = atof(token);
            index++;
            token = strtok(NULL, ",");
        }
        students[num_students].num_grades = index;
        num_students++;
    }

    // Закрываем входной файл
    fclose(input_file);

    // Просим пользователя ввести пороговое значение для среднего балла
    float average_threshold;
    printf("Введите пороговое значение для среднего балла: ");
    scanf("%f", &average_threshold);

    // Открываем файл для записи списка студентов с баллами выше порога
    output_file = fopen("out.txt", "w");

    // Проверяем средний балл каждого студента и записываем студентов в файл
    for (int i = 0; i < num_students; i++) {
        float average = calculateAverage(students[i].grades, students[i].num_grades);
        if (average > average_threshold) {
            fprintf(output_file, "%s\n", students[i].name);
        }
    }

    // Закрываем выходной файл
    fclose(output_file);

    printf("Список студентов с баллами выше %.2f успешно записан в out.txt\n", average_threshold);

    return 0;
}
