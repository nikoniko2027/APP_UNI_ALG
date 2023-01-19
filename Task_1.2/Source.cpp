#include <iostream>
#include <vector>
#include <string>
#include <fstream>

using namespace std;

ifstream al("alph.txt");
ifstream in("input.txt");
ofstream out("Result.txt");

int LenString = 0; // Глобальная переменная размерности текста

struct LetterInfo { // Структура вектора
	string letter; // Буква
	int i; // Количество букв
};

vector<LetterInfo> Init() { // Функция загрузки русского алфавита в вектор
	vector <LetterInfo> res, sup;
	while (!al.eof()) { // Идем до конца файла
		string x;
		al >> x;
		LetterInfo a;
		a.i = 0;
		a.letter = x;
		sup.push_back(a);
	}
	
	for (int i = 0; i < sup.size(); i++)
		for (int j = 0; j < sup.size(); j++) { // Циклы для объединения двух букв алфавита (всевозможные комбинации)
			LetterInfo a;
			a.letter = sup[i].letter + sup[j].letter;
			a.i = 0;
			res.push_back(a);
		}

	return res;
}

vector<LetterInfo> Separation(vector <LetterInfo> res) { // Функция считывания файла и подсчет букв
	string x = "";

	while (!in.eof()) { // Идем до конца файла
		string a;
		in >> a;
		x += a; // Соединяем слова в строку
	}

	LenString = x.size();

		for (int i = 0; i < x.size(); i++) { // Разбираем полученное слово на буквы
			//bool fl = false;
			for (int j = 0; j < res.size(); j++) { // Ищем букву в векторе
				if (res[j].letter == x.substr(i, 2)) { // Если нашлась, то фиксируем ее
					res[j].i++;
					//fl = true;
					break;
				}
			}
			//if (!fl) { // Если буква на нашлась, то создаем для нее элемент в векторе
			//	LetterInfo a;
			//	a.letter = x[i];
			//	a.i = 1;
			//	res.push_back(a);
			//}
		}
	return res;
}

vector<LetterInfo> BubbleSort(vector <LetterInfo> res) { // Сортировка пузырьком от большего к меньшему
	for (int j = 0; j < res.size(); j++)
		for (int i = 0; i < res.size() - 1; i++)
			if (res[i].i < res[i + 1].i)
				swap(res[i], res[i + 1]);
	return res;
}

int main() {
	setlocale(LC_ALL, "RUS");

	vector <LetterInfo> res = Init();
	res = Separation(res);
	res = BubbleSort(res);

	for (int i = 0; i < res.size(); i++) { // Выводим на экран все буквы
		if (res[i].i > 0) {
			double frequency = round(((double)res[i].i / (double)LenString) * 1000) / 1000; // Округляем до тысячных
			cout << "Пара букв [" << res[i].letter << "] | Встречается -> " << res[i].i << " раз(а) | Частота -> " << frequency << endl;
			out << "Пара букв [" << res[i].letter << "] | Встречается -> " << res[i].i << " раз(а) | Частота -> " << frequency << endl;
		}
	}


	al.close();
	in.close();
	out.close();
	system("pause");
	return 0;
}