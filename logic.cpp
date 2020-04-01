#include "logic.h"
Student* AddInfo(deque<Student> arr)
{
	vector<int> homework;
	int examResult;
	bool end = false;
	string vardas, pavarde;
	int rezultatas;
	cout << "Irasykite studento varda ir pavarde" << endl;
	cin >> vardas >> pavarde;
	Student* student = new Student(vardas, pavarde);
	cout << "Ivesti paciam ar generuoti rezultatus? (p/g)" << endl;
	char ats = 'o';
	while (ats != 'p' && ats != 'g')
	{
		cin >> ats;
	}
	if (ats == 'p')
	{
		cout << "Irasykite namu darbus: -1 baigia irasymo procesa" << endl;
		while (true)
		{
			cin >> rezultatas;
			if (rezultatas > 10 || rezultatas < -1)
			{
				cout << "Netinka. Rezultatas netelpa i pazymio intervala" << endl;
				continue;
			}
			if (cin.fail())
			{
				cin.clear();
				cin.ignore();
				cout << "Netinkama ivestis" << endl;
				continue;
			}
			else if (rezultatas == -1 && homework.size() > 0)
			{
				cin.clear();
				break;
			}
			homework.push_back(rezultatas);
		}
		cout << "Irasykite egzaminu rezultatus" << endl;
		int rez;
		while (true)
		{
			cin >> rez;
			if (rez > 10 || rez < 0)
			{
				cout << "Netinka. Rezultatas netelpa i pazymio intervala" << endl;
				continue;
			}
			if (cin.fail())
			{
				cin.clear();
				cin.ignore();
				cout << "Netinkama ivestis" << endl;
				continue;
			}
			else
			{
				break;
			}
		}
		examResult = rez;
	}
	else if (ats == 'g')
	{
		int n;
		srand(time(NULL));
		n = rand() % 10;
		for (int i = 0; i < n; i++)
		{
			int rezultatas = rand() % 11;
			homework.push_back(rezultatas);
		}
		rezultatas = rand() % 11;
		examResult = rezultatas;
	}
	if (medianShow)
	{
		double median = student->CountMedian(homework);
		student->CountFinal(median, examResult);
	}
	else
	{
		double average = student->CountAverage(homework);
		student->CountFinal(average, examResult);
	}
	return student;
}
bool ReturnMedianQuestion()
{
	char ats = '0';
	bool answer = false;
	cout << "Rodyti vidurki ar mediana? (v/m)" << endl;
	while (ats != 'v' && ats != 'm')
	{
		cin >> ats;
	}
	if (ats == 'v')
	{
		answer = false;
	}
	else if (ats == 'm')
	{
		answer = true;
	}
	return answer;
}
bool ReturnFileReadQuestion() ///true - input, false - read file
{
	char ats = 'o';
	while (ats != 'd' && ats != 'f')
	{
		cin >> ats;
	}
	if (ats == 'd')
	{
		return true;
	}
	else if (ats == 'f')
	{
		return false;
	}
}
void Program()
{
	int n = 5;
	cout << "YES: Generuoti txt failus is naujo\nNO: Skaityti esamus txt failus\n(y/n)" << endl;
	char ans;
	bool generates = false;
	while (true)
	{
		cin >> ans;
		if (ans == 'y')
		{
			generates = true;
			break;
		}
		else if (ans == 'n')
		{
			break;
		}
		else
		{
			cout << "Netinkama ivestis\n";
		}
	}
	cout << "Pasirinkite skaitomu failu skaiciu: (1-" << n << ")" << endl;
	int answ;
	while (true)
	{
		cin >> answ;
		if (cin.fail())
		{
			cin.clear();
			cin.ignore();
			cout << "Netinkama ivestis" << endl;
			continue;
		}
		if (answ<1 || answ>n)
		{
			cout << "Ivestis netelpa i intervala" << endl;
		}
		else
		{
			n = answ;
			break;
		}
	}
	deque<Student> arr, best;
	medianShow = false;
	int counter = 1000;
	for (int i = 0; i < n; i++)
	{
		auto start = std::chrono::high_resolution_clock::now();
		if (generates)
		{
			GenerationAlgorithm(counter, 5);
		}
		//arr.reserve(counter);
		bufer_nusk("kursiokai" + ConvertIntToString(counter),arr);
		//SortByResults(arr);
		SortElements(arr, best);
		SortByName(arr);
		SortByName(best);
		PrintElements(arr, best);
		deque<Student>().swap(arr);
		deque<Student>().swap(best);
		auto end = std::chrono::high_resolution_clock::now();
		std::chrono::duration<double> diff = end - start;
		cout << endl << counter << " dydzio vektoriaus testavimas uztruko " << diff.count() << " sekundziu\n";
		cout << "-----------------------------\n";
		arr.clear();
		best.clear();
		counter *= 10;
	}
}
void SortByResults(deque<Student>& arr)
{
	auto start = std::chrono::high_resolution_clock::now();
	sort(arr.begin(), arr.end(), [](const auto& lhs, const auto& rhs)
		{
			return lhs.final < rhs.final;
		});
	auto end = std::chrono::high_resolution_clock::now();
	std::chrono::duration<double> diff = end - start;
	cout << arr.size() << " dydzio vektoriaus rusiavimas pagal rezultatus uztruko " << diff.count() << " sekundziu\n";
}
void SortByName(deque<Student>& arr)
{
	auto start = std::chrono::high_resolution_clock::now();
	sort(arr.begin(), arr.end(), [](const auto& lhs, const auto& rhs)
		{
			return lhs.name < rhs.name;
		});
	auto end = std::chrono::high_resolution_clock::now();
	std::chrono::duration<double> diff = end - start;
	cout << arr.size() << " dydzio vektoriaus rusiavimas pagal vardus uztruko " << diff.count() << " sekundziu\n";
}
void GenerationAlgorithm(int amountToGenerate, int counter) ///prielaida, kad counter <10
{
	auto start = std::chrono::high_resolution_clock::now();
	ofstream fr("kursiokai" + ConvertIntToString(amountToGenerate) + ".txt");
	int fieldAmount = counter;
	fr << "Vardas Pavarde" << " ";
	for (int i = 1; i <= fieldAmount; i++)
	{
		fr << "ND" + ConvertIntToString(i) << " ";
	}
	fr << "Egz" << endl;
		for (int i = 0; i < amountToGenerate-1; i++)
		{
			fr << "Vardas" + ConvertIntToString(i) << " " << "Pavarde" + ConvertIntToString(i) << " ";
			for (int j = 0; j < fieldAmount; j++)
			{
				fr << ConvertIntToString(rand() % 10 + 1) << " ";
			}
			fr << ConvertIntToString(rand() % 10 + 1) << endl;
		}
		fr.clear();
	fr.close();
	std::chrono::duration<double> diff = std::chrono::high_resolution_clock::now() - start; // Skirtumas (s)
	std::cout << "Failo generavimas uztruko: " << diff.count() << " s\n";
}
void GenerateTxtFiles(int amountOfFiles)
{
	for (int i = 0; i < amountOfFiles; i++)
	{
		auto start = std::chrono::high_resolution_clock::now();
		GenerationAlgorithm(1000 * pow(10, i), i + 3);
		auto end = std::chrono::high_resolution_clock::now();
		std::chrono::duration<double> diff = end - start;
		cout << 1000 * pow(10, i) << " elementu failo generavimas uztruko " << diff.count() << " sekundziu\n";
	}
}
string ConvertIntToString(int toConvert)
{
	string result;
	ostringstream convert;
	convert << toConvert;
	result = convert.str();
	return result;
}
void PrintElements(deque<Student> arr, deque<Student> best)
{
	auto start = std::chrono::high_resolution_clock::now();
	ofstream fr("galvociai" + ConvertIntToString(best.size()) + ".txt");
	int i;
	for (deque<Student>::iterator i = best.begin(); i != best.end(); i++)
	{
		fr << "|" << setw(20) << (*i).name << "|" << setw(20) << (*i).surname << "|" <<
			setw(20) << fixed << setprecision(2) << (*i).final << "|" << endl;
	}
	fr.close();
	auto end = std::chrono::high_resolution_clock::now();
	std::chrono::duration<double> diff = end - start;
	cout << "Galvociu rasymas i faila uztruko " << diff.count() << " sekundziu\n";
	start = std::chrono::high_resolution_clock::now();
	ofstream fr2("nuskriaustieji" + ConvertIntToString(arr.size()) + ".txt");
	for (deque<Student>::iterator i = arr.begin(); i != arr.end(); i++)
	{
		fr2 << "|" << setw(20) << (*i).name << "|" << setw(20) << (*i).surname << "|" <<
			setw(20) << fixed << setprecision(2) << (*i).final << "|" << endl;
	}
	fr2.close();
	end = std::chrono::high_resolution_clock::now();
	diff = end - start;
	cout << "Nuskriaustuju rasymas i faila uztruko " << diff.count() << " sekundziu\n";
}
void SortElements(deque<Student>& arr, deque<Student>& best)
{
	auto start = std::chrono::high_resolution_clock::now();
	int index=0;
	SortByResults(arr);
	for (deque<Student>::iterator i = arr.begin(); i != arr.end(); i++)
	{
		index++;
		if ((*i).final >= 5.0f)
		{
			break;
		}
	}
	deque<Student>::iterator i = arr.begin();
	advance(i, index);
	for (i; i != arr.end(); i++)
	{
		best.push_back(*i);
	}
	//index++;
	arr.resize(index);
	auto end = std::chrono::high_resolution_clock::now();
	std::chrono::duration<double> diff = end - start;
	cout << "Vektoriaus skaidymas i du uztruko " << diff.count() << " sekundziu\n";
}
double Student::CountMedian(vector<int> homework)
{
	double median;
	for (int i = 0; i < homework.size(); i++)
	{
		for (int j = i + 1; j < homework.size(); j++)
		{
			if (homework[i] > homework[j])
			{
				int temp = homework[i];
				homework[i] = homework[j];
				homework[j] = temp;
			}
		}
	}
	if (homework.size() % 2 != 0)
	{
		median = homework[homework.size() / 2];
	}
	else
	{
		median = (double)homework[homework.size() / 2] + homework[homework.size() / 2 - 1];
	}
	return median;
}
void Student::CountFinal(double data, double examResult)
{
	final = data * 0.4 + 0.6 * examResult;
}
void Student::Print()
{
	cout << "|" << setw(20) << name << "|" << setw(20) << surname << "|" << setw(20) << fixed << setprecision(2) << final << "|" << endl;
}
double Student::CountAverage(vector<int> homework)
{
	double sum = 0, average;
	for (int i = 0; i < homework.size(); i++)
	{
		sum += (double)homework[i];
	}
	average = (double)sum / (double)homework.size();
	return average;
}
void bufer_nusk(std::string read_vardas, deque<Student>& arr)
{
	try
	{
		auto start = std::chrono::high_resolution_clock::now();
		int homeworkElement, examResult;
		Student* studentas = new Student();
		vector<int> homework;
		std::vector<std::string> splited;
		std::string eil;
		std::stringstream my_buffer;
		std::ifstream open_f(read_vardas + ".txt");
		my_buffer << open_f.rdbuf();
		open_f.close();

		start = std::chrono::high_resolution_clock::now();
		while (my_buffer) {
			if (!my_buffer.eof()) {
				std::getline(my_buffer, eil);
				splited.push_back(eil);
			}
			else break;
		}

		start = std::chrono::high_resolution_clock::now();
		std::string outputas = "";
		for (std::string& a : splited) (a.compare(*splited.rbegin()) != 0) ? outputas += a + "\n" : outputas += a;
		splited.clear();
		istringstream data;
		data.str(outputas);
		string parameter;
		data >> parameter >> ws >> parameter;
		int n = 0;
		while (parameter != "Egzaminas" && !data.eof())
		{
			data >> ws >> parameter;

			if (parameter[0] == 'E')
			{
				break;
			}
			n++;
		}
		while (!data.eof())
		{
			data >> studentas->name >> studentas->surname;
			for (int i = 0; i < n; i++)
			{
				data >> homeworkElement;
				homework.push_back(homeworkElement);
			}
			data >> examResult;
			if (medianShow)
			{
				double median = studentas->CountMedian(homework);
				studentas->CountFinal(median, examResult);
			}
			else
			{
				double average = studentas->CountAverage(homework);
				studentas->CountFinal(average, examResult);
			}
			vector<int>().swap(homework);
			arr.push_back(*studentas);
		}
		cout << arr.size() << endl;
		data.clear();
		std::chrono::duration<double> diff = std::chrono::high_resolution_clock::now() - start; // Skirtumas (s)
		std::cout << "Failo nuskaitymas uztruko: " << diff.count() << " s\n";
	}
	catch (const std::exception& e)
	{
		cerr << e.what() << endl;
		return;
	}
	
}
