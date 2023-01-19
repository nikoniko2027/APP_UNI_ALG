#include <iostream>
#include <vector>
#include <string>
#include <fstream>

using namespace std;

ifstream al("alph.txt");
ifstream in("input.txt");
ofstream out("Result.txt");

int LenString = 0; // ���������� ���������� ����������� ������

struct LetterInfo { // ��������� �������
	string letter; // �����
	int i; // ���������� ����
};

vector<LetterInfo> Init() { // ������� �������� �������� �������� � ������
	vector <LetterInfo> res, sup;
	while (!al.eof()) { // ���� �� ����� �����
		string x;
		al >> x;
		LetterInfo a;
		a.i = 0;
		a.letter = x;
		sup.push_back(a);
	}
	
	for (int i = 0; i < sup.size(); i++)
		for (int j = 0; j < sup.size(); j++) { // ����� ��� ����������� ���� ���� �������� (������������ ����������)
			LetterInfo a;
			a.letter = sup[i].letter + sup[j].letter;
			a.i = 0;
			res.push_back(a);
		}

	return res;
}

vector<LetterInfo> Separation(vector <LetterInfo> res) { // ������� ���������� ����� � ������� ����
	string x = "";

	while (!in.eof()) { // ���� �� ����� �����
		string a;
		in >> a;
		x += a; // ��������� ����� � ������
	}

	LenString = x.size();

		for (int i = 0; i < x.size(); i++) { // ��������� ���������� ����� �� �����
			//bool fl = false;
			for (int j = 0; j < res.size(); j++) { // ���� ����� � �������
				if (res[j].letter == x.substr(i, 2)) { // ���� �������, �� ��������� ��
					res[j].i++;
					//fl = true;
					break;
				}
			}
			//if (!fl) { // ���� ����� �� �������, �� ������� ��� ��� ������� � �������
			//	LetterInfo a;
			//	a.letter = x[i];
			//	a.i = 1;
			//	res.push_back(a);
			//}
		}
	return res;
}

vector<LetterInfo> BubbleSort(vector <LetterInfo> res) { // ���������� ��������� �� �������� � ��������
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

	for (int i = 0; i < res.size(); i++) { // ������� �� ����� ��� �����
		if (res[i].i > 0) {
			double frequency = round(((double)res[i].i / (double)LenString) * 1000) / 1000; // ��������� �� ��������
			cout << "���� ���� [" << res[i].letter << "] | ����������� -> " << res[i].i << " ���(�) | ������� -> " << frequency << endl;
			out << "���� ���� [" << res[i].letter << "] | ����������� -> " << res[i].i << " ���(�) | ������� -> " << frequency << endl;
		}
	}


	al.close();
	in.close();
	out.close();
	system("pause");
	return 0;
}