#include <iostream>
#include "experiment.h"
#include <string>


int main() {
    /// Size of the problem equals the amount of recipes used in the instance
    const size_t problem_size = 568;

    /// number of experiments
    int number_of_experiments = 15;

    /// Setting parameters
    /* Insert the numeral that indicates the model to be used
    set "0": static model
    set "1": static model with meals time division and calories restriction
    set "2": dinamic model without preferences considering
    set "3": dinamic model with preferences prediction considering */
    enum Model {
        STATIC,
        STATIC_MEASLTIME,
        DINAMIC_ONLY,
    };

    /// Full instance path of foods
    //Instance PATH is defined in CMAKE as LOCAL_PATH

    for (int i=1;i<=number_of_experiments;i++){
    /// Output file saved on ...ProjectName/experiments/
    std::string path = LOCAL_PATH_EXPORTS"cost-100/experiments_result_";
    std::string file_output = path + std::to_string(i);

    /// Solving the problem
    run_experiment(problem_size, STATIC_MEASLTIME, file_output);
    }
    return 0;
}
