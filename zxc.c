#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_LINE_LENGTH 100
#define MAX_STUDENTS 100

// Структура для хранения информации о студенте
struct Student {
    char name[MAX_LINE_LENGTH];
    int homework_done;
    int exams_passed;
};

int main() {
    FILE *input_file;
    FILE *output_file;
    char line[MAX_LINE_LENGTH];
    struct Student students[MAX_STUDENTS];
    int num_students = 0;

    // Открываем файл для чтения
    input_file = fopen("in.txt", "r");
    if (input_file == NULL) {
        perror("Ошибка при открытии файла in.txt");
        return 1;
    }

    // Читаем данные из файла и сохраняем их в структуру Студент
    while (fgets(line, MAX_LINE_LENGTH, input_file) != NULL) {
        sscanf(line, "%[^,], %d, %d", students[num_students].name, &students[num_students].homework_done, &students[num_students].exams_passed);
        num_students++;
    }

    // Закрываем входной файл
    fclose(input_file);

    // Открываем файл для записи списка студентов, заслуживающих награды
    output_file = fopen("out.txt", "w");
    if (output_file == NULL) {
        perror("Ошибка при открытии/создании файла out.txt");
        return 1;
    }

    // Пороговые значения для получения награды
    float homework_threshold = 0.8;
    float exams_threshold = 0.75;

    // Проверяем критерии для получения награды и записываем студентов в файл
    for (int i = 0; i < num_students; i++) {
        float homework_percentage = (float)students[i].homework_done / 100;
        float exams_percentage = (float)students[i].exams_passed / 10;
        if (homework_percentage >= homework_threshold && exams_percentage >= exams_threshold) {
            fprintf(output_file, "%s\n", students[i].name);
        }
    }

    // Закрываем выходной файл
    fclose(output_file);

    printf("Список студентов, заслуживающих награду, успешно записан в out.txt\n");

    return 0;
}
