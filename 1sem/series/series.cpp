#include <stdio.h>
#include <math.h>

/*
Эта программа вычисляет арктангенс используя замену переменной и тот факт, что arctg(y) = y при малых y

Выкладки:
arctg(y) = 2*arctg((sqrt(1 + y^2) - 1) / y), вспомните тригонометрию
((sqrt(1 + y^2) - 1) / y) = (y / (sqrt(1 + y^2) + 1)), проверьте перемножением
(y / (sqrt(1 + y^2) + 1)) меньше чем y / 2

Но при больших значениях y эта программа довольно медлительна 
Например при y = 1024 потребуется 41 замена переменной
Эффективность такого алгоритма - O(log(n))

Написано в конце 2019 Акостеловым И.И.
Рефакторинг 28.08.20
*/

const double EPS = 1e-12;

int main()
{
	double x;

	while (true)
	{
		printf("x: ");
		if (scanf("%lg", &x) < 1)
			break;

		// сохраняем значение в переменную что бы потом сравнить результат с Си-шным арктангенсом
		double xBackup = x; 
		
		int numOfChanges = 0;
		while (abs(x) > EPS) // abs(x) позволяет программе работать и для отрицательных значений
		{
			// заменяем переменную
			x = (x / (1 + sqrt(1 + x * x)));
			// сохраняем число замен, т.к при каждой замене arctg(x)=2*arctg(newX)
			++numOfChanges;
		}

		// используем то, что для малых x, arctg(x) == x и не забываем про замены
		printf("arctg(x) = %.14f\n", x * pow(2, numOfChanges));
		printf("lib arctg(x) = %.14f\n", atan(xBackup));
	}
	return 0;
}