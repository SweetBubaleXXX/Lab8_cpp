#include <iostream>
#include <vector>

#define a_po_russki_mozhno setlocale(LC_ALL, "Russian"); system("chcp 1251")

using namespace std;

enum Months { JAN = 1, FEB = 2, MAR = 3, APR = 4, MAY = 5, JUN = 6, JUL = 7, AUG = 8, SEP = 9, OCT = 10, NOV = 11, DEC = 12 };

struct Semen {
    char* name;
    int month_sowing;
    int month_seating;
    int month_harvesting;
};

void get_siemens(vector<Semen*>&, int);

void filter_harvesting(vector<Semen*>&, vector<Semen*>&, int);

int find_greater_name_index(vector<Semen*>, char*);

int main() {
    a_po_russki_mozhno;

    vector<Semen*> output_siemens;
    vector<Semen*> siemens;
    int number_of_siemens;

    cout << "¬ведите количество сем€н: ";
    cin >> number_of_siemens;
    if (cin.fail() || number_of_siemens <= 0) { puts("Ќеверное число"); return -1; }

    get_siemens(siemens, number_of_siemens);
    filter_harvesting(output_siemens, siemens, AUG);

    for (int i = 0; i < output_siemens.size(); i++) {
        cout << "{\n\tЌазвание: " << output_siemens[i]->name << endl;
        cout << "\tћес€ц посева: " << output_siemens[i]->month_sowing << endl;
        cout << "\tћес€ц выссадки рассады: " << output_siemens[i]->month_seating << endl;
        cout << "\tћес€ц уборки: " << output_siemens[i]->month_harvesting << "\n}" << endl;
    }

    return 0;
}

void get_siemens(vector<Semen*>& siemens, int number_of_siemens) {
    for (int n = 0; n < number_of_siemens; n++) {
        Semen* siemen = new Semen;
        siemen->name = new char[20];

        cout << "{\n\tЌазвание культуры: ";
        scanf_s("%s", siemen->name, 20);
        cout << "\tћес€ц посева: ";
        scanf_s("%d", &(siemen->month_sowing));
        cout << "\tћес€ц выссадки рассады: ";
        scanf_s("%d", &(siemen->month_seating));
        cout << "\tћес€ц уборки: ";
        scanf_s("%d", &(siemen->month_harvesting));
        cout << "}" << endl;

        siemens.push_back(siemen);
    }
}

void filter_harvesting(vector<Semen*>& output_vector, vector<Semen*>& input_vector, int month_number) {
    for (int i = 0; i < input_vector.size(); i++) {
        if (input_vector[i]->month_harvesting != month_number) continue;
        int insert_index = find_greater_name_index(output_vector, input_vector[i]->name);
        output_vector.insert(output_vector.begin() + insert_index, input_vector[i]);
    }
}

int find_greater_name_index(vector<Semen*> siemens, char* name) {
    if (!siemens.size()) return 0;
    if (siemens.size() == 1) {
        return strcmp(name, siemens[0]->name) > 0;
    }
    int start = 0;
    int end = siemens.size() - 1;
    int cur_index = abs((start + end) / 2);
    while (end > start) {
        if (strcmp(name, siemens[cur_index]->name) > 0) {
            if (cur_index < siemens.size() - 1 && strcmp(name, siemens[cur_index + 1]->name) < 0) {
                return ++cur_index;
            }
            start = cur_index + 2;
        }
        else {
            end = cur_index;
        }
        cur_index = abs((start + end) / 2);
    }
    return cur_index;
}