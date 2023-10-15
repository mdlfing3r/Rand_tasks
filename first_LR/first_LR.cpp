#include <iostream>
#include <random>
#include <vector>
#include <windows.h>
#include <thread>
#include <fstream>
#include <string>
#include <sstream>


#define File_addr "./tasks.txt"
#define min_value 0;
#define max_value 10;

#define min_value_of_duration 0;
#define max_value_of_duration 0;

#define Employes_amount 20;
#define Daily_time_limit 24;

//title - формируется на основании "задача" + <0..n>;   n - количество задач(вершин графа)
//id - формируется рандомом 
 
class task {
public:
    task(uint16_t id, std::string title, uint16_t task_duration, std::vector<std::string>another_connected_task)
        :
        _id(id) //id потока
        ,_title(title)  //имя задачи
        , _task_duration(task_duration)   //продолжительность задачи
        , _another_connected_task(another_connected_task)  //все задачи которые связаны с этой
    {
        
        std::cout << "Thread_id: " << std::this_thread::get_id() << " ||| title:" << title << " ||| task_duration: " << task_duration
            << "||| list_of_connected_tasks:" << title << " " <<
            std::string{ [](std::vector<std::string> input_vec) {
                    std::string _retval;
                    for (auto& it : input_vec) 
                        _retval += "->" + it;
                    return _retval;
                }(another_connected_task) };
    }

private:
    uint16_t _id;
    std::string _title;
    uint16_t _task_duration;
    std::vector<std::string>_another_connected_task;
};

void distrib_func(std::vector<int>input_vec) {
    std::cout << "Distribution function\n";
    int in_process = 10;
    int input_vec_counter = input_vec.size();
    int digit_counter[10] = {};
    for (auto it = 0; it < input_vec.size() - 1; it++) {
        switch (input_vec.at(it)) {
            case 0:
                digit_counter[0]++;
                break;
            case 1:
                digit_counter[1]++;
                break;
            case 2:
                digit_counter[2]++;
                break;
            case 3:
                digit_counter[3]++;
                break;
            case 4:
                digit_counter[4]++;
                break;
            case 5:
                digit_counter[5]++;
                break;
            case 6:
                digit_counter[6]++;
                break;
            case 7:
                digit_counter[7]++;
                break;
            case 8:
                digit_counter[8]++;
                break;
            case 9:
                digit_counter[9]++;
                break;
        }
    }
    std::cout << "0 1 2 3 4 5 6 7 8 9\n";
    while (input_vec_counter) {
        for (auto it = 0; it < 10; it++) {
            if (input_vec_counter <= 0)
                break;
            if (digit_counter[it]) {
                std::cout << "+ ";
                input_vec_counter--;
            }
            else
                std::cout << "  ";
        }
        std::cout << std::endl;

    }
}


void ditrib_graphics(std::vector<int>input_vec) {
    std::cout << "Distribution graph\n";
    for (auto it = 0; it < input_vec.size() - 1; it++) {
        switch (input_vec.at(it)) {
        case 0:
            std::cout << "+         " << std::endl;
            std::cout << "+         " << std::endl;

            break;
        case 1:
            std::cout << " +        " << std::endl;
            std::cout << " +        " << std::endl;

            break;
        case 2:
            std::cout << "  +       " << std::endl;
            std::cout << "  +       " << std::endl;

            break;
        case 3:
            std::cout << "   +      " << std::endl;
            std::cout << "   +      " << std::endl;

            break;
        case 4:
            std::cout << "    +     " << std::endl;
            std::cout << "    +     " << std::endl;

            break;
        case 5:
            std::cout << "     +    " << std::endl;
            std::cout << "     +    " << std::endl;

            break;
        case 6:
            std::cout << "      +   " << std::endl;
            std::cout << "      +   " << std::endl;

            break;
        case 7:
            std::cout << "       +  " << std::endl;
            std::cout << "       +  " << std::endl;

            break;
        case 8:
            std::cout << "        + " << std::endl;
            std::cout << "        + " << std::endl;

            break;
        case 9:
            std::cout << "         +" << std::endl;
            std::cout << "         +" << std::endl;

            break;
        }
        //Sleep(1);
    }
}

std::string GetRandName(int string_num) {
    std::ifstream Names_Container(File_addr);
    char* ptr;
    char symb;
    ptr = &symb;

    std::string RandName;

    Names_Container.get(symb);
    do {
        string_num--;
        //Names_Container.seekg(0, std::ios_base::cur);
        Names_Container.get(*ptr);
        getline(Names_Container, RandName);
    } while (string_num > 0);
    return *ptr + RandName;
}

void thread_func() {
    std::ostringstream oss;
    int local_min = min_value;
    int local_max = max_value;
    std::vector<std::string>connected_tasks;

    std::random_device r_dev;
    std::default_random_engine r_eng_name(r_dev());
    std::default_random_engine r_eng_dur(r_dev());
    std::default_random_engine r_eng_con_amount(r_dev());
    std::default_random_engine r_eng_con_task(r_dev());

    std::uniform_int_distribution<int> uniform_dist(local_min, local_max);
    std::uniform_int_distribution<int> uniform_dist_tasks(local_min, 100);


    int connected_task_amount = uniform_dist(r_eng_con_amount); //0...10

    for (auto it = 0; it < connected_task_amount; it++) {
        connected_tasks.push_back(GetRandName(uniform_dist_tasks(r_eng_con_task)));
    }
    oss << std::this_thread::get_id();
    new task(std::stoi(oss.str()), GetRandName(uniform_dist_tasks(r_eng_name)), uniform_dist(r_eng_dur), connected_tasks);
}




int main()
{
    std::random_device r;
    std::vector<int>digit_vec;

    int _Employes_amount = Employes_amount;
    int _Daily_time_limit = Daily_time_limit;

    std::ifstream Names_Container(File_addr);

    std::default_random_engine e1(r());
    std::default_random_engine e2(r());
    std::default_random_engine e3(r());
    std::default_random_engine e4(r());

   /*
    for (auto it = 0; it < 300; it++) {
        std::cout << "Randomly-chosen mean: " << uniform_dist(e1) << '\n';
        digit_vec.push_back(uniform_dist(e1));
    }
    if (Names_Container.is_open())
        std::cout << "File_is_open";
    else
        std::cout << "File_isn`t_open";
    */
    int _symb_offset = 0;

   // Names_Container.seekg(5, std::ios_base::cur);


    //distrib_func(digit_vec);
    //ditrib_graphics(digit_vec);
    thread_func();

    return 0;
}
