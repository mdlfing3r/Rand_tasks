#include <iostream>
#include <random>
#include <vector>
#include <windows.h>
#include <thread>
#include <fstream>
#include <string>
#include <sstream>
#include <map>
#include <mutex>


#define File_addr "./tasks.txt"

#define min_value_of_duration 1;
#define max_value_of_duration 5;

#define min_value_of_name_pos 2;
#define max_value_of_name_pos 20;

#define min_value_of_connected_task 0;
#define max_value_of_connected_task 2;
#define Employes_amount (20);
#define Daily_time_limit (24*60);


class task {
public:
    task(uint16_t id, std::string title, uint16_t task_duration, std::string nextTask)
        :
        _id(id) //id потока
        , _title(title)  //имя задачи
        , _task_duration(task_duration)   //продолжительность задачи
        , _nextTask(nextTask)  //все задачи которые связаны с этой
    {
        
        std::cout << title << ((nextTask!="") ? "->" + nextTask : " ") << std::endl;
            
    }

private:
    uint16_t _id;
    std::string _title;
    uint16_t _task_duration;
    std::string _nextTask;
};

//task_duration, nextTask
typedef struct task_values {
    uint16_t _task_duration;
    std::string _nextTask;
} task_values_type;


std::string GetRandName(int string_num) {
    std::ifstream Names_Container(File_addr);
    char* p_symb;
    char symb;
    p_symb = &symb;

    std::string RandName;

    Names_Container.get(*p_symb);
    do {
        string_num--;
        Names_Container.get(*p_symb);
        getline(Names_Container, RandName);
    } while (string_num > 0);
    return *p_symb + RandName;
}



std::mutex mtx;
void threadFunction() {
        int _DailyLimit = (int)Daily_time_limit;
        int min_val_dur = min_value_of_duration;
        int max_val_dur = max_value_of_duration;
        int min_val_NamePos = min_value_of_name_pos;
        int max_val_NamePos = max_value_of_name_pos;
        int min_val_DependsTaskAmount = min_value_of_connected_task;
        int max_val_DependsTaskAmount = max_value_of_connected_task;

        std::uniform_int_distribution<int> uniform_dist_dur(min_val_dur, max_val_dur)
            , uniform_dist_task(min_val_NamePos, max_val_NamePos)
            , uniform_dist_task_amount(min_val_DependsTaskAmount, max_val_DependsTaskAmount);

        std::string depends_task;
        std::random_device r_dev;
        std::default_random_engine  r_eng_name(r_dev())
                                  , r_eng_dur(r_dev())
                                  , r_eng_dep_task_amount(r_dev())
                                  , r_eng_dep_task(r_dev());


        std::map<std::string, task_values_type> Tasks_base;
        task_values_type Tasks{ 0, "" };
        std::ostringstream oss;
        oss << std::this_thread::get_id();

        uint16_t final_time = 0;



        for (auto itrtr = 0; itrtr < max_val_NamePos; itrtr++) {

            std::string temp_TaskName = GetRandName(uniform_dist_task(r_eng_name));

            if (Tasks_base.find(temp_TaskName) == Tasks_base.end())
                Tasks_base.emplace(temp_TaskName, Tasks); //если задачи нет в контейнере задач Tasks_base


            if (*&Tasks_base.at(temp_TaskName)._nextTask == "" && *&Tasks_base.at(temp_TaskName)._task_duration == 0) {       //если следующая задача не существует 

                while (max_val_NamePos > 0)
                {
                    depends_task = GetRandName(uniform_dist_task(r_eng_name));
                    if (Tasks_base.find(depends_task) == Tasks_base.end() && depends_task != temp_TaskName) {
                        *&depends_task = depends_task;
                        break;
                    }
                    max_val_NamePos--;
                }


                task_values_type newTempDepensTask = { uniform_dist_dur(r_eng_dur), "" };

                Tasks_base.emplace(*&depends_task, newTempDepensTask); //добавляем в контейнер задач подзадачу текущей задачи
                *&Tasks_base.at(temp_TaskName)._nextTask = *&depends_task;
                *&Tasks_base.at(temp_TaskName)._task_duration = uniform_dist_dur(r_eng_dur);
            }

        }
        std::map<std::string, task_values_type> Tasks_base_sorted;



        for (auto& it : Tasks_base) {

            new task(std::stoi(oss.str()), it.first, it.second._task_duration, it.second._nextTask);
            *&final_time += it.second._task_duration;

        }

        std::cout << "thread_ID: " << std::stoi(oss.str()) << " total Time : " << final_time << std::endl<<std::endl;
        oss.clear();
}




int main()
{
    int Empl_cntr = Employes_amount;


    std::thread t1(threadFunction);
    std::thread t2(threadFunction);
    std::thread t3(threadFunction);
    std::thread t4(threadFunction);
    std::thread t5(threadFunction);
    std::thread t6(threadFunction);
    std::thread t7(threadFunction);

    t1.join();
    t2.join();
    t3.join();
    t4.join();
    t5.join();
    t6.join();
    t7.join();


    getchar();
    return 0;
}
