#include <iostream>
#include <iomanip> // Для гарного виводу часу (setw, setfill)

using namespace std;

// =========================================================
// ОГОЛОШЕННЯ СТРУКТУР (Згідно з Завданням 1 та 2)
// =========================================================

// Структура для Завдання 1 (Параметри часу)
struct TTime {
    int Hour, Min, Sec;
};

// Структура для Завдання 2 (Begin25 - містить вхід x та вихід y)
struct DataBegin25 {
    double x;
    double y;
};

// Структура для Завдання 2 (Boolean16 - містить вхід x та вихід result)
struct DataBoolean16 {
    int x;
    bool result;
};

// =========================================================
// ЛОГІЧНІ ФУНКЦІЇ ОБРОБКИ
// =========================================================

// Перевірка коректності часу
bool IsValid(TTime t) {
    return (t.Hour >= 0 && t.Hour < 24 &&
            t.Min >= 0 && t.Min < 60 &&
            t.Sec >= 0 && t.Sec < 60);
}

// Завдання 1: Віднімання N хвилин від часу T
TTime SubMin(TTime T, int N) {
    if (!IsValid(T)) return T;

    // Переводимо все в секунди (long для уникнення переповнення)
    long totalSec = T.Hour * 3600L + T.Min * 60L + T.Sec;
    totalSec -= (long)N * 60L;

    // Обробка переходу через північ (якщо результат від'ємний)
    while (totalSec < 0) totalSec += 24 * 3600L;
    totalSec %= (24 * 3600L);

    TTime result;
    result.Hour = (int)(totalSec / 3600);
    result.Min = (int)((totalSec % 3600) / 60);
    result.Sec = (int)(totalSec % 60);
    return result;
}

// Завдання 2 (Begin25): Обчислення y = 3x^6 - 6x^2 - 7
void ProcessBegin25(DataBegin25 &d) {
    double x2 = d.x * d.x;          // x^2
    double x6 = x2 * x2 * x2;       // x^6
    d.y = 3 * x6 - 6 * x2 - 7;
}

// Завдання 2 (Boolean16): Перевірка чи число парне двозначне
void ProcessBoolean16(DataBoolean16 &d) {
    // Число має бути в межах [10, 99] та ділитися на 2 без остачі
    d.result = (d.x >= 10 && d.x <= 99 && d.x % 2 == 0);
}

// =========================================================
// ФУНКЦІЇ-ОБОЛОНКИ ДЛЯ МЕНЮ (Завдання 3)
// =========================================================

void Task1() {
    TTime times[5];
    cout << "\n--- Завдання 1 (Робота з часом) ---\n";
    for (int i = 0; i < 5; i++) {
        cout << "Введіть час " << i + 1 << " (години хвилини секунди): ";
        cin >> times[i].Hour >> times[i].Min >> times[i].Sec;
    }

    int N;
    cout << "Введіть кількість хвилин для віднімання: ";
    cin >> N;

    cout << "\nРезультати (Новий час):\n";
    for (int i = 0; i < 5; i++) {
        TTime res = SubMin(times[i], N);
        // Форматований вивід 00:00:00
        cout << i + 1 << ") " << setfill('0') << setw(2) << res.Hour << ":"
             << setw(2) << res.Min << ":"
             << setw(2) << res.Sec << endl;
    }
}

void Task2() {
    DataBegin25 d;
    cout << "\n--- Завдання 2 (Begin25: 3x^6 - 6x^2 - 7) ---\n";
    cout << "Введіть значення x: ";
    cin >> d.x;

    ProcessBegin25(d);

    cout << "Вхідні дані (x): " << d.x << endl;
    cout << "Вихідні дані (y): " << d.y << endl;
}

void Task3() {
    DataBoolean16 d;
    cout << "\n--- Завдання 3 (Boolean16: Парне двозначне) ---\n";
    cout << "Введіть ціле число: ";
    cin >> d.x;

    ProcessBoolean16(d);

    cout << "Вхідне число: " << d.x << endl;
    cout << "Результат (істинність): " << (d.result ? "True (Так)" : "False (Ні)") << endl;
}

// =========================================================
// ГОЛОВНА ФУНКЦІЯ (Меню)
// =========================================================

int main() {
    // Налаштування для коректного відображення кирилиці (Windows)
    setlocale(LC_ALL, "Ukrainian");

    int choice;
    do {
        cout << "\n===============================" << endl;
        cout << "         ГОЛОВНЕ МЕНЮ          " << endl;
        cout << "===============================" << endl;
        cout << "1. Виконати Завдання 1 (Час - N хв)" << endl;
        cout << "2. Виконати Завдання 2 (Begin25)" << endl;
        cout << "3. Виконати Завдання 3 (Boolean16)" << endl;
        cout << "0. Вихід з програми" << endl;
        cout << "-------------------------------" << endl;
        cout << "Ваш вибір: ";
        cin >> choice;

        switch (choice) {
            case 1: Task1(); break;
            case 2: Task2(); break;
            case 3: Task3(); break;
            case 0: cout << "Програма завершена. До побачення!" << endl; break;
            default: cout << "Помилка! Оберіть пункт від 0 до 3." << endl;
        }
    } while (choice != 0);

    return 0;
}
