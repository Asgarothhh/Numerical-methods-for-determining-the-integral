#include <iostream>
#include <cmath>
#include <process.h>
using namespace std;

const int SIZE=6;

double f(double x)
{
    double y = x / (1 + pow(x, 2));
    return y;
}

double trapezoid_method(double a, double b, int n)
{
    double h = (b - a) / n;
    double integral_value = 0;
    for (int i = 0; i < n; i++)
    {
        double x0 = a + i * h;
        double x1 = a + (i + 1) * h;
        integral_value += (f(x0) + f(x1)) * h / 2;
    }
    return integral_value;
}

double simpsons_method(double a, double b, int n)
{
    double h = (b - a) / n;
    double integral_value = 0;
    for (int i = 0; i < n; i++)
    {
        double x0 = a + i * h;
        double x1 = a + (i + 1) * h;
        integral_value += ((x1 - x0) / 6.0) * (f(x0) + 4.0 * f(0.5 * (x0 + x1)) + f(x1));;
    }
    return integral_value;
}

double middle_rectangle_method(double a, double b, int n)
{
    double h = (b - a) / n;
    double integral_value = 0;
    for (int i = 0; i < n; i++)
    {
        double x0 = a + i * h;
        double x1 = a + (i + 1) * h;
        double xk = (x0 + x1) / 2;
        integral_value += f(xk);
    }
    integral_value *= h;
    return integral_value;

}

int main()
{
    setlocale(LC_ALL, "Russian");

    double a, b;
    int answer;
    double eps[SIZE];
    double integral[SIZE];
    int N[SIZE] = { 10, 20, 50, 100, 500, 2000};

    cout << "\tОпределение значения интеграла при помощи квадратурных формул.";
    cout << "\nВведите значение левой границы интегрирования: ";
    cin >> a;
    if (a < 0)
    {
        cout << "\nОшибка ввода! Левая граница не может быть меньше нуля.";
        exit(1);
    }
    cout << "\nВведите значение правой границы интегрирования: ";
    cin >> b;
    if (a >= b)
    {
        cout << "\nОшибка ввода! Левая граница не может быть больше (или равной) правой.";
        exit(1);
    }

    cout << "\nВыберете метод численного интегрирования: ";
    cout << "\nНажмите '1', чтобы выбрать метод трапеций, '2', чтобы выбрать метод Симпсона, ";
    cout << "\n'3', чтобы выбрать метод средних прямоугольников: ";
    cin >> answer;
    switch (answer)
    {
        case 1: 
            cout << "\n\tВы выбрали метод трапеций." << endl;

            for (int i = 0; i < SIZE; i++)
            {   
                int n = N[i];
                integral[i] = trapezoid_method(a, b, n);
                double I1 = trapezoid_method(a, b, n);
                double I2 = trapezoid_method(a, b, n) * 2;
                eps[i] = abs((I1 - I2)) / (pow(2, 2) - 1);
            }

            for (int i = 0; i < SIZE; i++)
            {
                cout << i+1 << ") Результата интегрирования при отрекзке разбиения равном " << N[i] << ": " << integral[i];
                cout << "\nОценка погрешности апостериорным методом: " << eps[i] << endl << endl;
            }
            break;

        case 2: 
            cout << "\n\tВы выбрали метод Симпсона." << endl;

            for (int i = 0; i < SIZE; i++)
            {
                int n = N[i];
                integral[i] = simpsons_method(a, b, n);
                double I1 = simpsons_method(a, b, n);
                double I2 = simpsons_method(a, b, n) * 2;
                eps[i] = abs((I1 - I2)) / (pow(2, 4) - 1);
            }

            for (int i = 0; i < SIZE; i++)
            {
                cout << i+1 << ") Результата интегрирования при отрекзке разбиения равном " << N[i] << ": " << integral[i];
                cout << "\nОценка погрешности апостериорным методом: " << eps[i] << endl << endl;
            }
            break;

        case 3:
            cout << "\n\tВы выбрали метод средних прямоугольников" << endl;

            for (int i = 0; i < SIZE; i++)
            {
                int n = N[i];
                integral[i] = middle_rectangle_method(a, b, n);
                double I1 = middle_rectangle_method(a, b, n);
                double I2 = middle_rectangle_method(a, b, n) * 2;
                eps[i] = abs((I1 - I2)) / (pow(2, 2) - 1);
            }

            for (int i = 0; i < SIZE; i++)
            {
                cout << i + 1 << ") Результата интегрирования при отрекзке разбиения равном " << N[i] << ": " << integral[i];
                cout << "\nОценка погрешности апостериорным методом: " << eps[i] << endl << endl;
            }
            break;

        default: 
            cout << "\nВы ввели недопустимое значение! Попробуйте снова." << endl;
            break;
    }
    
    system("pause");
    return 0;
}
