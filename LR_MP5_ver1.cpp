#include <string>
#include <vector>
#include <iostream>
#include <stdexcept>
#include <fstream>

using namespace std;
/*
Формат ввода:
    в строку:
    номер филиала, количество дней, прибыли этих дней
         2                3            100    0    50
Формат вывода:
    номер филиала, номера дней без прибыли, отдельной строкой кол-во дней без прибыли
         2                2                                 1
*/


class ProfitDays {

private:
    int filial;  //номер филиала
    int days;   //количество дней   
    vector <double> profit_pd; //вектор прибыли в каждый день

public:
    void set_total_days(int total_days) {
        days = total_days;    //количество дней
    }
    void set_num_filial(int number_fil) {
        filial = number_fil;   //номер филиала
    }
    void set_profit_pd(vector <double> prof) {
        profit_pd = prof;
    }


    int get_num_filial() {
        return filial;
    }
    int get_total_days() {
        return days;
    }
    vector <double> get_profit_pd() {
        return profit_pd;
    }

    ProfitDays() {  //конструктор по умолчанию
        filial = 1;
        days = 1;
        //profit_pd.clear();
        profit_pd.push_back(0);

    };
    ~ProfitDays()
    {
        days = 0;
        filial = 0;
        profit_pd.clear();
    }

    vector<double> find_0_profit()
    {
        vector<double> ans;
        for (int i = 0; i < days; ++i)
            if (profit_pd[i] == 0)
                ans.push_back(i);
        return ans;
    }
    void output_info(ostream& out)
    {
        out << '\n' << "Filial: " << filial << '\n'
            << "Days: " << days << '\n'
            << "Profits are: ";

        for (int i = 0; i < days; ++i)
            out << profit_pd[i] << "  ";

        vector <double> data = find_0_profit();
        if (data.size() != 0)
        {
            out << '\n' << "There are " << data.size() << " days with 0 profit: ";
            for (auto c : data)
                out << (c + 1) << "  ";
            out << endl;
        }
        else out << '\n' << "There are NO days with 0 profit" << '\n' << endl;
    }

    friend istream& operator>>(istream& in, ProfitDays& PD);
    friend ifstream& operator>>(ifstream& in, vector <ProfitDays>& PD);
    friend ofstream& operator<<(ofstream& out, vector <ProfitDays>& PD_vector);
    friend ostream& operator<<(ostream& out,  vector <ProfitDays>& PD_vector);
};

double profit_check(string input)
{
    /*
    Функция, проверяет, являются ли введенные пользователем данные числом

    Если фукнция stold не срабатывает, то выводит ошибку "invalid_argument", обрабатывает ее через catch
    Если функция stold сработала, то дополнительно провяряем строку. Удаляем первое вхождение точки через erase,
    после этого циклом проходим по элементам

    Возвращает:
        number: long double  число, переведенное из input: string, которое ввел пользователь

    */
    bool ok = true;
    double number = 0;
    try
    {

        number = stod(input);

        if (input.find('.') != input.npos)   input.erase(input.find('.'), 1);

        for (int i = 1; i < input.length(); ++i)
        {
            if (isdigit(input[i]) == false) throw (1);
        }
        return number;
    }
    catch (invalid_argument)
    {
        throw runtime_error("Error(1)! Write a number!");
    }
    catch (int i)
    {
        throw runtime_error("Error(2)! Write a number!");
    }
}

int number_check(string input)
{
    bool ok = true;
    int number = 0;

    try
    {
        number = stoi(input);
        if (to_string(number).length() != input.length())
            throw (1);

        if (number <= 0)
            throw(2);

        return number;
    }
    catch (invalid_argument)
    {
        throw runtime_error("Error (1)! Write an integer number!");
    }
    catch (int i)
    {
        switch (i)
        {
        case (1):
            throw runtime_error("Error (2)! Write a number!");
            break;
        case (2):
            throw runtime_error("Error(3)! Number must be positive!");
            break;
        }
    }

}

int count_PD_elem()
{
    cout << '\n' << "Input total number of your filials: ";
    string str;
    bool ok = true;
    int count = -1;
    while (ok)
    {
        getline(cin, str);
        int count = number_check(str);
        if (count > 0) return count;
    }
}

void instruction()
{
    cout << "Input information about profit per days of your filial. " << '\n'
        << "Format: <number of filial> <days> <profit of 1st day> <profit of 2nd day>..." << '\n'
        << "Example: 1 3 10 0 20" << '\n' << endl;
}


void cycle_for(vector <double>& all_numbers, string str)
{
    int numi;
    double numd;
    string curr_num;
    for (int i = 0; i < (str.length()); ++i) //прохожу по строке. пока не встречу пробел, превращаю текст в число. увидел - скипнул или удалил
    {
        if ((str[i] == ' ' && str[i + 1] == ' ') || (str[0] == ' '))
        {
            throw runtime_error("Error! Wrong input, try again!");
        }
        if (str[i] != ' ')
            curr_num += str[i];
        if ((str[i] == ' ' && str[i + 1] != ' ') || (str[i + 1] == '\0'))
        {

            all_numbers.size() < 2 ? numi = number_check(curr_num) : numd = profit_check(curr_num);
            all_numbers.size() < 2 ? all_numbers.push_back(numi) : all_numbers.push_back(numd);
            curr_num = "";
        }
    }

}

void set_all_information(vector <double>& all_numbers, ProfitDays& PD)
{
    int days, filial;

    all_numbers[0] == (int)all_numbers[0] ? filial = all_numbers[0] : throw runtime_error("Error! Filial number must be integer!");
    all_numbers[1] == (int)all_numbers[1] ? days = all_numbers[1] : throw runtime_error("Error! Days number must be integer!");
    bool ok = true;

    if (days != (all_numbers.size() - 2)) ok = false;
    //cout << "vec size is " << all_numbers.size() << endl;
    PD.set_num_filial(filial);
    PD.set_total_days(days);


    if (ok) {

        all_numbers.erase(all_numbers.begin(), all_numbers.begin() + 2);

        PD.set_profit_pd(all_numbers);
        all_numbers.clear();
    }
    else
    {
        all_numbers.clear();
        throw runtime_error("Error! Numbers of days and profits are not equal!");
    }
}

vector <double> input_data_con(istream& in) {

    string str;
    vector <double> all_numbers;
    getline(in, str);

    cycle_for(all_numbers, str);

    return all_numbers;
}

void input_data_file(string str, ProfitDays& PD)
{
    vector <double> all_numbers;
    cycle_for(all_numbers, str);
    set_all_information(all_numbers, PD);
}




istream& operator>>(istream& in, ProfitDays& PD)
{
    vector <double> xz = input_data_con(in);
    set_all_information(xz, PD);
    return in;
}

ifstream& operator>>(ifstream& in, vector <ProfitDays>& PD_vector)
{
    string str;
    while (getline(in, str))
    {
        ProfitDays test;
        input_data_file(str, test);
        PD_vector.push_back(test);
    }
    return in;
}

ofstream& operator<<(ofstream& out, vector <ProfitDays>& PD_vector)
{
    for (int i = 0; i < PD_vector.size() - 1; ++i)
    {
        PD_vector[i].output_info(out);
    }
    return out;
}

ostream& operator<<(ostream& out, vector <ProfitDays>& PD_vector)
{
    for (int i = 0; i < PD_vector.size() - 1; ++i)
    {
        PD_vector[i].output_info(out);
    }
    return out;
}



ProfitDays calcNset(bool choose, ifstream& in, vector <ProfitDays>& PD_vector, int count)
{
    ProfitDays soup;
    if (choose)
    {
        for (int i = 0; i < count; ++i)
        {
            cin >> soup;

            PD_vector.push_back(soup);
        }
    }
    else in >> PD_vector;
    //cout << soup.get_num_filial();
    return soup;
}
/*
мне в операторе ввода нужно проходить по строке и создавать из нее объект
после этого объекты запихнуть в вектор или массив объектов
*/

vector <ProfitDays> total_calc_set(int count, bool choose, ifstream& in)  //массив объектов PD, в каждом уже есть информация
{
    vector <ProfitDays> arr;
    
    arr.push_back(calcNset(choose, in, arr, count));
     
    return arr;
}

bool YN_function()
{
    /*
    Функция узнает, вводит пользователь Y или N.
    В зависимости от этого возвращает:
        '1', если введено 'Y'
        '0', если введено 'N'
    */
    cout << '\n' << "Do you want to continue? Input 'Y' or 'N'" << endl;
    string button;
    bool end = false;
    while (end == 0)
    {
        getline(cin, button);
        if (button[0] == 'Y' && button.length() == 1) return  true;
        if (button[0] == 'N' && button.length() == 1)  return false;
        if (end == 0) cout << "Write 'Y' or 'N'!" << endl;
    }
}

bool console_or_file()
{
    
    bool ok = true;
    string str;
    int num = 0;
    while (ok)
    {
        getline(cin, str);
        num = number_check(str);

        if (num == 1) return true;
        if (num == 2) return false;
        else cout << "Input '1' or '2'!" << endl;
    }
}

string file_choose()
{
    /*
    Функция, позволяет выбрать файл.
    Пользователь вводит название, если файл с таким названием существует, то вовзвращает его в string.
    */
    string name;
    bool ok = true;
    while (ok)
    {

        getline(cin, name);

        ifstream file;
        file.open("d:\\texts\\" + name + ".txt");

        if (file)
        {
            name = "d:\\texts\\" + name + ".txt";
            file.close();
            return name;
        }
        else cout << '\n' << "Error! Input correct name!" << endl;
    }

}
int lines_count(ifstream& file)
{
    string str;
    int count = 0;
    cout << '\n' << "File`s data:" << endl;
    while (getline(file, str))
    {
        cout << str << '\n';
        count++;
    }
    file.close();
    return count;
}

int main()
{
    bool finish = true;
    instruction();
    while (finish)
    {
        ProfitDays test;
        ifstream ifile;
        string file_name;
        
        int counting = 0;
        try {
            cout << "Do you want to load information from Console or from File? \n"
                << "Enter '1' to use Console  or  '2' to use File" << '\n' << "Enter: ";
            bool choose_input = console_or_file();
            vector <ProfitDays> test;
            if (choose_input)
            {
                cout << "You chose console" << endl;
                counting = count_PD_elem();
                cout << "Input information about your filials: " << endl;
                
                test = total_calc_set(counting, choose_input, ifile);
                
            }

            else
            {
                cout << "You chose file. Input its name ('input'): " << endl;
                file_name = file_choose();
                
                ifile.open(file_name);
                
                counting = lines_count(ifile);
                ifile.open(file_name);

                
                test = total_calc_set(counting, choose_input, ifile);
                test;
            }
            cout << "Do you want to load information from Console or from File? \n"
                << "Enter '1' to use Console  or  '2' to use File" << '\n' << "Enter: ";
            bool choose_output = console_or_file();

            if (choose_output)
            {
                cout << "You chose console. Your information:" << endl;
                ostream out();

                cout << test;
            }
            else
            {
                cout << "You chose file. Input its name ('output'): " << endl;
                file_name = file_choose();
                ofstream ofile(file_name);
                ofile << test;
                
            }
        }

        catch (runtime_error& e) {
            cout << e.what() << endl;
        }
        finish = YN_function();
    }

}