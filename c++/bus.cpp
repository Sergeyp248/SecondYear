#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
#include <clocale>
#include <iomanip>
#include <string>
using namespace std;

const int _SIZE = 15;
const int _CURRENT_YEAR = 2018;
const int _MAX_LEN = 50;

class Driver {

private:

	char* surname;
	char* initials;

public:

	Driver() : surname(nullptr), initials(nullptr) {
		//cout << "Сработал конструктор по умолчанию - " << this << endl;
	};

	Driver(char* str1, char* str2) : surname(nullptr), initials(nullptr) {
		if (str1 != nullptr && str2 != nullptr) {
			try {
				surname = new char[strlen(str1) + 1];
				initials = new char[strlen(str2) + 1];
			}
			catch (...) {
				cout << "Ошибка при выделении памяти!\n";
			}
			strcpy(surname, str1);
			strcpy(initials, str2);
		}
		//cout << "Сработал конструктор c параметром - " << this << endl;
	};

	~Driver() {
		delete[] surname;
		delete[] initials;
		surname = nullptr;
		initials = nullptr;
		//cout << "Сработал деструктор - " << this << endl;
	};

	void setSurname(char *str1) {
		delete[] surname;
		if (str1 != nullptr) {
			try {
				surname = new char[strlen(str1) + 1];
			}
			catch (...) {
				cout << "Ошибка при выделении памяти!\n";
			}
			strcpy(surname, str1);
		}
	};

	void setInitials(char *str2) {
		delete[] initials;
		if (str2 != nullptr) {
			try {
				initials = new char[strlen(str2) + 1];
			}
			catch (...) {
				cout << "Ошибка при выделении памяти!\n";
			}
			strcpy(initials, str2);
		}
	};

	char* getSurname() { return surname; };

	char* getInitials() { return initials; };

};

class Bus {

private:

	Driver driver;
	char *busMark;
	int busNumber;
	int routeNumber;
	int expStartYear;
	int mileage;

public:

	Bus() : driver(nullptr, nullptr), busMark(nullptr), busNumber(0), routeNumber(0), expStartYear(0), mileage(0) {
		//cout << "Сработал конструктор по умолчанию - " << this << endl;
	};

	Bus(char* str1, char* str2, char *str3, int _busNumber = 0, int _routeNumber = 0, int _expStartYear = 0, int _mileage = 0) :
		driver(str1, str2), busMark(nullptr), busNumber(_busNumber), routeNumber(_routeNumber), expStartYear(_expStartYear), mileage(_mileage) {
		if (str3 != nullptr) {
			try {
				busMark = new char[strlen(str3) + 1];
			}
			catch (...) {
				cout << "Ошибка при выделении памяти!\n";
			}
			strcpy(busMark, str3);
		}
		//cout << "Сработал конструктор c параметром - " << this << endl;
	}

	~Bus() {
		delete[] busMark;
		busMark = nullptr;
		//cout << "Сработал деструктор - " << this << endl;
	};

	void setDriver(char* str1, char* str2) {
		driver.setSurname(str1);
		driver.setInitials(str2);
	};

	void setBusMark(char *str) {
		delete[] busMark;
		if (str != nullptr) {
			try {
				busMark = new char[strlen(str) + 1];
			}
			catch (...) {
				cout << "Ошибка при выделении памяти!\n";
			}
			strcpy(busMark, str);
		}
	};

	void setBusNumber(int value) {
		if (value > 0) { busNumber = value; }
		else { busNumber = 0; }
	};

	void setRouteNumber(int value) {
		if (value > 0) { routeNumber = value; }
		else { routeNumber = 0; }
	};

	void setExpStartYear(int value) {
		if (value > 0) { expStartYear = value; }
		else { expStartYear = 0; }
	};

	void setMileage(int value) {
		if (value > 0) { mileage = value; }
		else { mileage = 0; }
	};

	char* getDriver() {
		char* str1 = driver.getSurname();
		char* str2 = driver.getInitials();
		char* string = nullptr;
		if (str1 != nullptr && str2 != nullptr) {
			try {
				string = new char[strlen(str1) + strlen(str2) + 2];
			}
			catch (...) {
				cout << "Ошибка при выделении памяти!\n";
			}

			strcpy(string, str1);
			string = strcat(string, " ");
			string = strcat(string, str2);
		}
		return string;
	};

	char* getBusMark() { return busMark; };

	int getBusNumber() { return busNumber; };

	int getRouteNumber() { return routeNumber; };

	int getExpStartYear() { return expStartYear; };

	int getMileage() { return mileage; };
};

typedef Bus* fun(Bus*);
typedef fun* ptrfun;

Bus* giveMemory();
Bus* getBusByRouteNumber(Bus*);
Bus* getBusByExpStartYear(Bus*);
Bus* getBusByMileage(Bus*);
Bus* initArray(Bus*);
Bus* printBuses(Bus*);
Bus* enterBuses(Bus*);
Bus* exit(Bus*);

void menu(Bus*);
void forEach(Bus*, ptrfun);

int main() {

	setlocale(LC_ALL, "ru");

	Bus *buses = nullptr;
	buses = giveMemory();
	menu(buses);
	delete[] buses;
	system("pause");
	return 0;

}

Bus* giveMemory() {
	Bus* arr = new Bus[_SIZE];
	return arr;
}

Bus* getBusByRouteNumber(Bus* arr) {
	int input = 0;
	cout << "Введите желаемый номер маршрута: ";
	cin >> input;
	Bus* tempArr = giveMemory();
	int index = 0;

	for (int i = 0; i < _SIZE; i++) {
		if (input == arr[i].getRouteNumber()) {
			tempArr[index++] = arr[i];
		}
	}

	if (!index) {
		cout << "Данных автобусов с номером маршрута " << input << " не найдено\n";
		return nullptr;
	}

	printBuses(tempArr);

	return nullptr;
}

Bus* getBusByExpStartYear(Bus* arr) {
	Bus* tempArr = giveMemory();
	int index = 0;

	for (int i = 0; i < _SIZE; i++) {
		if (_CURRENT_YEAR - arr[i].getExpStartYear() > 10) {
			tempArr[index++] = arr[i];
		}
	}

	if (!index) {
		cout << "Данных автобусов со сроком эксплуатации более 10 лет не найдено\n";
		return nullptr;
	}

	printBuses(tempArr);

	return nullptr;
}

Bus* getBusByMileage(Bus* arr) {
	Bus* tempArr = giveMemory();
	int index = 0;

	for (int i = 0; i < _SIZE; i++) {
		if (arr[i].getMileage() > 10000) {
			tempArr[index++] = arr[i];
		}
	}

	if (!index) {
		cout << "Данных автобусов с пробегом более 10000 км не найдено\n";
		return nullptr;
	}

	printBuses(tempArr);

	return nullptr;
}

Bus* initArray(Bus* arr) {
	char* marks[15] = {"Iveco FBI 83 LR", "Neoplan Trendliner N 3516 U", "Mercedes-Benz Intouro",
							"Mercedes-Benz Sprinter", "Peugeot Boxer", "Ford Transit",
							"Hyundai Bogdan A 201", "Hyundai Super Aero City", "Irisbus Iveco Arway",
							"Golden Dragon XML6121", "Troliga Fenix CNG", "JAC HFC6128H",
							"JAC HK6127H", "Ankai HFF6110K06D", "Ankai HFF6850K57"};

	char* driversSurnames[15] = { "Зайцев", "Максимов", "Носков", "Беляев", "Киселёв", "Никифоров", "Иванов", "Сергеенко",
								"Павлов", "Новиков", "Шубин", "Лепестеков", "Одеялкин", "Панфилов", "Ручкин" };

	char* driversInitials[15] = { "В.А", "Р.О", "М.К", "А.П.", "К.Е.", "У.В.", "А.Ю.", "У.Ш.",
		"Н.Л.", "Ц.И.", "С.Л.", "Я.Б.", "И.К.", "Е.Н.", "Г.Р." };

	for (int i = 0; i < _SIZE; i++) {

		arr[i].setBusMark(marks[i]);
		arr[i].setBusNumber(rand() % 4001 + 1000);
		arr[i].setRouteNumber(rand() % 11 + 80);
		arr[i].setExpStartYear(rand() % 14  + 2005);
		arr[i].setMileage(rand() % 195001 + 5000);
		arr[i].setDriver(driversSurnames[i], driversInitials[i]);
	}

	return arr;
}

Bus* enterBuses(Bus* arr) {
	char* surname = nullptr;
	char* initials = nullptr;
	char* busMark = nullptr;
	char tmp[_MAX_LEN];
	int busNumber = 0, routeNumber = 0, expStartYear = 0, mileage = 0;
	int capacity = 0;
	cout << "Введите количество вводимых автобусов: ";
	cin >> capacity;
	for (int i = 0; i < capacity; i++) {
		cout << "Введите фамилию водителя: ";
		cin >> tmp;
		surname = new char [strlen(tmp) + 1];
		strcpy(surname, tmp);
		cout << "Введите инициалы водителя: ";
		cin >> tmp;
		initials = new char[strlen(tmp) + 1];
		strcpy(initials, tmp);
		cout << "Введите марку автобуса: ";
		cin >> tmp;
		busMark = new char[strlen(tmp) + 1];
		strcpy(busMark, tmp);
		cout << "Введите номер автобуса: ";
		cin >> busNumber;
		cout << "Введите номер маршрута автобуса: ";
		cin >> routeNumber;
		cout << "Введите год начала эксплуатации автобуса: ";
		cin >> expStartYear;
		cout << "Введите пробег автобуса в километрах: ";
		cin >> mileage;
		arr[i].setDriver(surname, initials);
		arr[i].setBusMark(busMark);
		arr[i].setBusNumber(busNumber);
		arr[i].setRouteNumber(routeNumber);
		arr[i].setExpStartYear(expStartYear);
		arr[i].setMileage(mileage);
		delete[] surname;
		delete[] initials;
		delete[] busMark;
	}

	return nullptr;
}

Bus* printBuses(Bus* arr) {
	cout << setw(30) << "Модель автобуса\t" << setw(14) << "Номер автобуса\t" << setw(14) << "Номер маршрута\t" << setw(23) << "Год начала эксплуатации\t" << setw(9) << "Пробег\t" << "Водитель\t\n";
	for (int i = 0; i < _SIZE; i++) {
		if (arr != nullptr) {
			if (arr[i].getBusMark() != nullptr) {
				cout << setw(30) << arr[i].getBusMark() << " | ";
			}
			cout << setw(13) << arr[i].getBusNumber() << " | ";
			cout << setw(13) << arr[i].getRouteNumber() << " | ";
			cout << setw(22) << arr[i].getExpStartYear() << " | ";
			cout << setw(8) << arr[i].getMileage() << " км" << " | ";
			if (arr[i].getDriver() != nullptr) {
				cout << arr[i].getDriver();
			}
			cout << "\n";
		}
	}

	return nullptr;
}

Bus* exit(Bus* arr) {
	exit(1);
}

void menu(Bus* arr) {
	ptrfun Fmenu[7] = { printBuses, getBusByRouteNumber, getBusByExpStartYear, getBusByMileage, exit, enterBuses, initArray };
	int inputNum = 0;
	while (true) {
		cout << "############################################  MENU  ############################################\n";
		cout << "Выберите одну из следующих операций: \n";
		cout << "1 - Вывод на экран списка всех автобусов\n";
		cout << "2 - Найти и вывести на экран автобусы с заданным номером маршрута\n";
		cout << "3 - Найти и вывести на экран автобусы со сроком эксплуатации более 10 лет\n";
		cout << "4 - Найти и вывести на экран автобусы с пробегом более 10000 км\n";
		cout << "5 - Выход\n";
		cout << "6 - Ввести значения автобусов\n";
		cout << "7 - Инициализировать массив автобусов псевдослучайными значениями\n";
		cout << "################################################################################################\n";
		cout << "Ввод: ";
		cin >> inputNum;
		if (inputNum > 0 && inputNum < 8) {
			forEach(arr, Fmenu[inputNum - 1]);
		}
		else {
			cout << "Неверная операция, попробуйте ещё раз\n";
		}
	}
}

void forEach(Bus* arr, ptrfun function) {
	function(arr);
}