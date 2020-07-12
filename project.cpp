#include <iostream>
#include <set>
#include <sstream>
#include <limits>
#include <fstream>


using namespace std;
/// Структура работника
struct Person { 
	string firstName;	///< Имя
	string lastName;	///< Фамилия
	string position;	///< Должность
	int salary;	///< Зарплата
};
/*!
	\brief Перегрузка оператора сравнения работников

	Позволяет создать set работников
*/
bool operator<(Person lhs, Person rhs) { 
	if (lhs.lastName == rhs.lastName)
	{
		return lhs.firstName < rhs.firstName;
	}
	return lhs.lastName < rhs.lastName;
}
/*!
		Класс, содержащий список со трудников с методами для работы с ним

		
	*/
class App {
public:
	/*!	
		\brief Отображает меню выбора действия

		Также вызывает функцию chooseOption()
	*/
	void renderMenu() { // Выводит меню
		cout << "МЕНЮ:" << endl;
		cout << "1) Добавить позицию" << endl;
		cout << "2) Удалить позицию" << endl;
		cout << "3) Вывести список" << endl;
		cout << "4) Поиск позиции" << endl;
		cout << "5) Загрузить список из файла" << endl;
		cout << "6) Сохранить список в файл" << endl;
		cout << "Введите номер операции:" << endl;
		chooseOption();
	}

private:
	/*!
		\brief Позволяет выбрать действие из меню
	*/
	void chooseOption() { 
		int option;
		cin >> option;
		if (option == 1)
		{
			addPosition(); 
		}
		else if (option == 2)
		{
			deletePosition();
		}
		else if (option == 3)
		{
			printList(); 
		}
		else if (option == 4)
		{
			findPerson(); 
		}
		else if (option == 5)
		{
			readFile(); 
		}
		else if (option == 6)
		{
			writeFile(); 
		}
		renderMenu();
	}

	/*!
		\brief Считывает список из файла

		Обеспечивает персистентность данных. В конце сеанса пользователь
		может воспользоваться функцией writeFile(), чтобы сохранить результаты в файл
	*/
	void readFile() {
		string line;

		ifstream in("D:\\1.txt"); 
		if (in.is_open())
		{
			while (getline(in, line))
			{
				stringstream ss(line);
				Person p;
				ss >> p.lastName >> p.firstName >> p.position >> p.salary;
				employees.insert(p);
			}
		}
		in.close();     
	}
	/*!
		\brief Записывает список в файл

		Обеспечивает персистентность данных. В начале сеанса пользователь
		может воспользоваться функцией readFile(), чтобы загрузить данные
	*/
	void writeFile() const {
		ofstream out("D:\\1.txt");
		if (out.is_open())
		{
			for (const auto& x : employees) {
				out << x.lastName << " " << x.firstName << " " << x.position << " " << x.salary << endl;
			}
		}
		out.close();
	}
	/*!
		\brief Выполняет поиск по Фамилии и Имени работника

		При успешном нахождении работника выводит все его данные: Фамилия, Имя, Должность и Зарплата.
		В противном случае выводит сообщение "Сотрудник не найден"
	*/
	void findPerson() const {
		if (employees.empty())
		{
			cout << "Список пуст!" << endl;
			return;
		}
		string data, fN, lN;
		std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
		getline(cin, data);
		stringstream ss(data);
		ss >> fN >> lN;
		for (const auto& x : employees) {
			if (fN == x.firstName && lN == x.lastName)
			{
				cout << x.lastName << " " << x.firstName << " | Должность: " << x.position << " | Зарплата: " << x.salary << endl;
				return;
			}
		}
		cout << "Сотрудник не найден" << endl;
	}
	/*!
		\brief Выводит весь список сотрудников

		Если список пуст, выводит сообщение "Список пуст"
	*/
	void printList() const {
		if (employees.empty())
		{
			cout << "Список пуст!" << endl;
			return;
		}
		cout << "Список сотрудников:" << endl;
		for (const auto& x : employees) {
			cout << x.lastName << " " << x.firstName << " | Должность: " << x.position << " | Зарплата: " << x.salary << endl;
		}
	}
	/*!
		\brief Удаляет сотрудника

		На ввод принимаются фамилия и имя сотрудника: если найдена успешна, выводится "Позиция успешно удалена!",
		в противном случае выводится "Позиция не найдена".
		Если список пуст, выводится сообщение "Список пуст"
	*/
	void deletePosition() {
		if (employees.empty())
		{
			cout << "Список пуст!" << endl;
			return;
		}
		cout << "Введите Имя и Фамилию работника, которого хотите удалить:" << endl;
		string data, fN, lN;
		std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
		getline(cin, data);
		stringstream ss(data);
		ss >> lN >> fN;
		if (checkAndDelete(fN, lN))
		{
			cout << "Позиция успешно удалена!" << endl;
		}
		else
		{
			cout << "Позиция не найдена" << endl;
		}
	}
	/*!
	 \brief функция удаляет позицию из списка

	  Функция возвращает true, если удалось удалить позицию. И false - если позиция не найдена.
	*/
	bool checkAndDelete(string fN, string lN) {
		for (const auto& x : employees) {
			if (x.firstName == fN && x.lastName == lN)
			{
				employees.erase(x);
				return true;
			}
		}
		return false;
	}
	/*!
		\brief Добавляет работника в список

		С потока считываются данные через пробел: Фамилия, Имя, Должность и Зарплата
	*/
	void addPosition() {
		cout << "Введите данные работника:" << endl;
		string data;
		Person temp;
		std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
		getline(cin, data);
		stringstream ss(data);
		ss >> temp.lastName >> temp.firstName >> temp.position >> temp.salary;
		employees.insert(temp);
	}
	set<Person> employees; ///< Список сотрудников
};

int main()
{
	setlocale(LC_ALL, "Russian");
	App newApp;

	newApp.renderMenu();
}