#include "task2.h"
#include "constants.h"

namespace task2 {
bool is_number(string input) {
	smatch result;
	regex regular("^(-??[0-9]+?.??[0-9]*?)+?(-??[0-9]+?.??[0-9]*?)$");
	return regex_match(input, result, regular);
}
bool is_natural_number(string input) {
    smatch result;
    regex regular("[1-9][0-9]*");
    return regex_match(input, result, regular);
}
double** createMatrix(int n, int m) { 
    double** matrix {new double*[n]}; 
    for (int i {0}; i < n; ++i) { 
        matrix[i] = new double[m]; 
        if (!matrix[i]) { 
            cerr << "Memory allocation failed!" << endl; 
            exit(EXIT_FAILURE); 
        } 
    } 
    return matrix; 
} 
double parseDouble(const string& s) {
	double result;
	istringstream iss(s);
	iss >> result;
	return result;
}
void readMatrixFromFile(double** matrix, int n, int m, bool& is_valid_matrix) {
	ifstream file(constants::task375Input);
	if (!file.is_open()) {
		cerr << "Unable to open file\n";
		exit(EXIT_FAILURE);
	}
	vector<vector<double>> numbers;
	string line;
	while (!file.eof()) {
		getline(file, line);
		if (is_number(line)) {
			if (m - 1 != count(line.begin(), line.end(), ' ')) {
				cout << "Ooops, an odd column in the matrix!\n";
                is_valid_matrix = false;
				return;
			}
		}
		else {cout << "Please, fill correct the matrix. Enter only numbers separated by one space on each row!\n";
            is_valid_matrix = false;
            return; }
		stringstream ss(line);
		string token;
		vector<double> row;
		while (getline(ss, token, ' ')) {
			row.push_back(parseDouble(token));
		}
		numbers.push_back(row);
	}
    double sum_of_elements {0};
	for (int i {0}; i < numbers.size(); i++) {
		for (int j {0}; j < numbers[i].size(); j++) {
			matrix[i][j] = numbers[i][j];
            sum_of_elements += matrix[i][j];
		}
	}
    if (sum_of_elements == 0) {
        cout << "Cannot divide by zero.\n";
        is_valid_matrix = false;
        return;
    }
    file.close();
}
void deleteMatrix(double** matrix, int n) { 
    for (int i {0}; i < n; i++) { 
        delete[] matrix[i]; 
        matrix[i] = nullptr; 
    } 
    delete[] matrix; 
    matrix = nullptr; 
} 
void fillMatrixRandom(double** matrix, int n, int m) { 
    for (int i {0}; i < n; i++) { 
        for (int j {0}; j < m; j++) { 
            matrix[i][j] = rand() % 100 + 1; 
        } 
    } 
} 
void fillMatrixManual(double** matrix, int n, int m, bool& is_valid_matrix) { 
    double sum_of_elements {0};
    cout << "Enter elements of the matrix:" << endl; 
    for (int i {0}; i < n; i++) { 
        for (int j {0}; j < m; j++) { 
            cout << "Enter element [" << i << "][" << j << "]: "; 
            double n;
            string r;
            getline(cin, r);
            while (!(is_number(r))) {
                cout << "Error, try again!\n";
                cout << "Enter element [" << i << "][" << j << "]: "; 
                getline(cin, r);}
            n = stod(r);
            matrix[i][j] = n;
            sum_of_elements += n; 
        } 
    } 
    if (sum_of_elements == 0) {
        cout << "Cannot divide by zero.\n";
        is_valid_matrix = false;
        return;
    }
} 
double findMaxAbsolute(double** matrix, int n, int m) { 
    double max {abs(matrix[0][0])}; 
    for (int i {0}; i < n; i++) { 
        for (int j {0}; j < m; j++) { 
            if (abs(matrix[i][j]) > max) { 
                max = abs(matrix[i][j]); 
            } 
        } 
    } 
    return max; 
} 
void divideMatrixByMax(double** matrix, int n, int m) { 
    double max {findMaxAbsolute(matrix, n, m)}; 
    if (max == 0) { 
        cout << "Cannot divide by zero." << endl; 
        return; 
    } 
 
    for (int i {0}; i < n; i++) { 
        for (int j {0}; j < m; j++) { 
            matrix[i][j] /= max; 
        } 
    } 
} 
// Функция для отображения матрицы 
void printMatrixPretty(double** matrix, int n, int m, ostream& out) { 
    // Определение ширины столбца для выравнивания элементов 
    int max_width {0}; 
    for (int i {0}; i < n; i++) { 
        for (int j {0}; j < m; j++) { 
            unsigned int width {to_string(matrix[i][j]).length()}; 
            if (width > max_width) { 
                max_width = width; 
            } 
        } 
    } 
    // Вывод матрицы с выравниванием элементов 
    for (int i {0}; i < n; i++) { 
        for (int j {0}; j < m; j++) { 
            out << setw(max_width) << matrix[i][j] << " "; 
        } 
        out << endl; 
    } 
} 
void task375() { 
    cout << "Task2 is started ..." << endl;
    string ans;
    cout << "Enter any symbol (to continue) or b (to break): ";
    cin.ignore(1, '\n');
    getline(cin, ans);
    while (ans != "b" && ans != "B") {
    int n, m; 
    string row, column;
    cout << "Enter the number of rows: "; 
    getline(cin, row);
    while (!(is_natural_number(row))) {
        cout << "Error: enter a natural number!\n";
        cout << "Enter the number of rows: ";
        getline(cin, row);
    }
    n = atoi(row.c_str());
    cout << "Enter the number of columns: "; 
    getline(cin, column);
    while (!(is_natural_number(column))) {
        cout << "Error: enter a natural number!\n";
        cout << "Enter the number of columns: ";
        getline(cin, column);
    }
    m = atoi(column.c_str());
    double** matrix {createMatrix(n, m)}; 
    string choice; 
    bool is_valid_matrix{true};
    cout << "Do you want to fill the matrix manually (yes - y, no - any symbol)?: "; 
    getline(cin, choice);
    if (choice == "y" || choice == "Y") { 
        string filling_choice;
        cout << "Do you want to input data in file or console (file - f, console - any symbol)?: ";
        getline(cin, filling_choice);
        while (true) {
        is_valid_matrix = true;
        if (filling_choice == "f" || filling_choice == "F") { 
            readMatrixFromFile(matrix, n, m, is_valid_matrix);
            if (is_valid_matrix){
                break;
            }
            else {
                cout << "Let's try again! Do you want to input data in file or console (file - f, console - any symbol)?: ";
                getline(cin, filling_choice);
                }
        }
        else {
            fillMatrixManual(matrix, n, m, is_valid_matrix); 
            if (is_valid_matrix){
                break;
            }
            else {
                cout << "Let's try again! Do you want to input data in file or console (file - f, console - any symbol)?: ";
                getline(cin, filling_choice);
                }
        }
        }
    } 
    else { 
        fillMatrixRandom(matrix, n, m); 
    } 
    divideMatrixByMax(matrix, n, m); 
    cout << "Where do you want to output the result (file - f, console - any symbol)?: "; 
    string outputChoice; 
    getline(cin, outputChoice);
    if (outputChoice == "f" || outputChoice == "F") { 
        ofstream outFile(constants::task375Output); 
        if (!outFile.is_open()) { 
            cerr << "Failed to open the file!" << endl; 
            exit(EXIT_FAILURE); 
        } 
 
        printMatrixPretty(matrix, n, m, outFile); 
        cout << "Result's been written.\n"; 
        outFile.close(); 
    } 
    else { 
        cout << "Resulting matrix:" << endl; 
        printMatrixPretty(matrix, n, m, cout); 
    } 
    deleteMatrix(matrix, n); 
    cout << "Do you want to continue? Enter any symbol (to continue) or b (to break): ";
    getline(cin, ans);}
    cout << "Task2 is finished ...\n";
} 
}