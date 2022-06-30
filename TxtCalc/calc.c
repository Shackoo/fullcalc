/*
 * calc.c
 *
 *  Created on: 30 июн. 2022 г.
 *      Author: Максим
 */
#include <stdio.h>
#include <stdlib.h>
double degree(float num1, float num2)     //Функция для степени
{
	if (num2 == 0) return 1;
	else
	{
		float numb1 = num1;
		for (int i = 1; i < num2; i++)
		{
			numb1 *= num1;
		}
		return numb1;
	}
}
void vectorCalculation(char operations, FILE* inFile, FILE* outFile)       //Функция для работы с векторами
{
	int* vector1;
	int* vector2;
	float scalar;
	int vectorSize;
	fscanf(inFile, "%i", &vectorSize);    //Размер векторов
	vector1 = malloc(vectorSize * sizeof(int));    //Выделяем память
	vector2 = malloc(vectorSize * sizeof(int));
	for (int i = 0; i < vectorSize; i++) fscanf(inFile, "%i", &vector1[i]);     //Заполняем векторы
	for (int i = 0; i < vectorSize; i++) fscanf(inFile, "%i", &vector2[i]);
	void printVector(int* vector)
	{
		fprintf(outFile, "(");
		for (int i = 0; i < (vectorSize - 1); i++) fprintf(outFile, "%i, ", vector[i]);
		fprintf(outFile, "%i)", vector[vectorSize - 1]);
	}
	printVector(vector1);
	fprintf(outFile, " %c ", operations);
	printVector(vector2);
	fprintf(outFile, " = ");
	int result[vectorSize];
	switch (operations)
	{
	case '+':
		for (int i = 0; i < vectorSize; i++) result[i] = vector1[i] + vector2[i];
		printVector(result);
		fprintf(outFile, "\n");
		break;
	case '-':
		for (int i = 0; i < vectorSize; i++) result[i] = vector1[i] - vector2[i];
		printVector(result);
		fprintf(outFile, "\n");
		break;
	case '^':
		for (int i = 0; i < vectorSize; i++) scalar += vector1[i] * vector2[i];
		fprintf(outFile, "%g\n", scalar);
		break;
	default:
		fprintf(outFile, "Error404\n", operations);
	}
	free(vector1);    //Освобождаем память
	free(vector2);
}
long long int factorial(int num1)     //Функция, для факториала
{
	if (num1 == 0) return 1;
	else
	{
		long long int fact = 1;
		for (int i = 1; i <= num1; i++)
		{
			fact *= i;
		}
		return fact;
	}
}
void arithmetic(char operations, FILE* inFile, FILE* outFile)  //Функция для простых чисел
{
	float num1, num2 = 1;
	fscanf(inFile, "%f", &num1);
	int wholeA = num1;
	float CheckA = num1 / wholeA; //Проверка int
	if (operations != '!')
	{
		fscanf(inFile, "%f", &num2);
	}
	int wholeB = num2; //Проверка int
	float CheckB = num2 / wholeB;
	switch (operations)
	{
	case '+':
		fprintf(outFile, "%g %c %g = %g\n", num1, operations, num2, num1 + num2);
		break;
	case '-':
		fprintf(outFile, "%g %c %g = %g\n", num1, operations, num2, num1 - num2);
		break;
	case '*':
		fprintf(outFile, "%g %c %g = %g\n", num1, operations, num2, num1 * num2);
		break;
	case '/':
		if (num2 == 0) fprintf(outFile, "Не то\n");
		else fprintf(outFile, "%g %c %g = %g\n", num1, operations, num2, num1 / num2);
		break;
	case '!':
		if ((CheckA != 1) || (num1 < 0)) fprintf(outFile, "Только натуральные\n");
		else fprintf(outFile, "%g %c = %lli\n", num1, operations, factorial(num1));
		break;
	case '^':
		if ((CheckB != 1) || (num2 < 0)) fprintf(outFile, "Только натуральные\n");
		else fprintf(outFile, "%g %c %g = %g\n", num1, operations, num2, degree(num1, num2));
		break;
	default:
		fprintf(outFile, "Error404\n", operations);
	}
}
int main(void)
{
	setvbuf(stdout, NULL, _IONBF, 0);
	setvbuf(stderr, NULL, _IONBF, 0);
	printf("Операция(+,- etc), Тип данных(v,s), Размер(for v),переменные\n");
	while (1)
	{
		char choice, operation, type;
		char input_Name[255];
		char output_Name[255];    //Здесь будут имена файлов
		printf("введите имя файла ввода: ");
		scanf("%s", &input_Name);
		printf("Введите имя файла вывода: ");
		scanf("%s", &output_Name);
		FILE* input = fopen(input_Name, "r");
		FILE* output = fopen(output_Name, "w");
		while (fscanf(input, " %c %c", &operation, &type) != EOF)
		{                                                         //Считываем с файла, пока он не закончится
			if (type == 'v') vectorCalculation(operation, input, output);   //вывод, в зависимости от исходных данных
			else if (type == 's') arithmetic(operation, input, output);
			else
			{
				fprintf(output, "Error404\n", type);
			}
		}
		fclose(input);     //закрываем файлы
		fclose(output);
		printf("Хочешь продолжить? (y/n) \n");  //запуск снова
		scanf(" %c", &choice);
		if (choice == 'n') break;

	}


	return 0;
}
