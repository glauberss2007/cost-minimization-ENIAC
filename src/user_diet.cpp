#include "user_diet.h"

std::mt19937 user_diet::_generator = std::mt19937(
    static_cast<unsigned long>(
        std::chrono::system_clock::now().time_since_epoch().count()) |
    std::random_device()());

/// Initially with a random solution (individual)
user_diet::user_diet(nutrition_facts &p) : _portions(p.size()) {
    std::uniform_int_distribution<int> d(0, 3);
    for (int &item : this->_portions) {
        item = d(user_diet::_generator);
    }
}

// function to display solution
std::vector<int> user_diet::disp(nutrition_facts &p, std::ofstream &fout) {
    double total_calories = 0, total_cost = 0, total_protein = 0,
           total_lipid = 0, total_carbo = 0, total_fiber = 0, total_calc = 0,
           total_magnesio = 0, total_fosfer = 0, total_ferro = 0,
           total_zinc = 0, total_manganes = 0;
    std::vector<int> _solucaoID;

    for (unsigned long i = 0; i < p.size(); ++i) {
        if (this->_portions[i]>0) {
            _solucaoID.push_back(p.id(i));
            std::cout << this->_portions[i] << " porçoes de " << p.revanues(i) << ", ";
            fout << this->_portions[i] << " porçoes de " << p.revanues(i) << ", ";
            total_calories = total_calories + (p.calories(i) * this->_portions[i]);
            total_cost = total_cost + ((p.cost(i)) * this->_portions[i]);
            total_protein = total_protein + ((p.protein(i)) * this->_portions[i]);
            total_lipid = total_lipid + ((p.lipid(i)) * this->_portions[i]);
            total_carbo = total_carbo + ((p.carbo(i)) * this->_portions[i]);
            total_fiber = total_fiber + ((p.fiber(i)) * this->_portions[i]);
            total_calc = total_calc + ((p.calc(i)) * this->_portions[i]);
            total_magnesio = total_magnesio + ((p.magnesio(i)) * this->_portions[i]);
            total_fosfer = total_fosfer + ((p.fosfer(i)) * this->_portions[i]);
            total_ferro = total_ferro + ((p.ferro(i)) * this->_portions[i]);
            total_zinc = total_zinc + ((p.zinc(i)) * this->_portions[i]);
            total_manganes = total_manganes + ((p.manganes(i)) * this->_portions[i]);
            std::cout << std::endl;
        }
    }
    std::cout << std::endl;

    std::cout << "Calorias: " << total_calories << ", "
              << "Custo: " << total_cost << std::endl;
    std::cout << "Proteinas: " << total_protein << ", "
              << "Gorduras: " << total_lipid << ", "
              << "Carboidratos: " << total_carbo << ", "
              << "Fibras: " << total_fiber << std::endl;
    std::cout << "Calcio: " << total_calc << ", "
              << "Magnesio: " << total_magnesio << ", "
              << "Fosforo: " << total_fosfer << ", "
              << "Ferro: " << total_ferro << ", "
              << "Zinco: " << total_zinc << ", "
              << "Manganes: " << total_manganes << ", ";
    std::cout << std::endl;

    fout << std::endl;
    fout << "Calorias: " << total_calories << ", "
         << "Custo: " << total_cost << std::endl;
    fout << "Proteinas: " << total_protein << ", "
         << "Gorduras: " << total_lipid << ", "
         << "Carboidratos: " << total_carbo << ", "
         << "Fibras: " << total_fiber << std::endl;
    fout << "Calcio: " << total_calc << ", "
         << "Magnesio: " << total_magnesio << ", "
         << "Fosforo: " << total_fosfer << ", "
         << "Ferro: " << total_ferro << ", "
         << "Zinco: " << total_zinc << ", "
         << "Manganes: " << total_manganes << ", ";
    fout << std::endl;

    // Mathplot graph with macronutrients ans micronutrients values
    /*
    std::vector<std::vector<double>> y,z;
    if (p.getModel()==0){
        y = {{75,150,45,25}, {total_protein,total_carbo,total_lipid,total_fiber},
             {210,300,98,0}};
        z = {{1000,260,700,14,7,2.3},{total_calc,total_magnesio,total_fosfer,
                                            total_ferro,total_zinc,total_manganes},
            {2500,350,4000,45,34,0}};
    } else {
        double mealstime_proportion;
        switch (p.turn()){
            case 1: {mealstime_proportion = 0.4;}
                break;
            case 2: {mealstime_proportion = 0.2;}
                break;
            case 3: {mealstime_proportion = 0.6;}
                break;
            case 4: {mealstime_proportion = 0.2;}
                break;
            case 5: {mealstime_proportion = 0.4;}
                break;
            case 6: {mealstime_proportion = 0.2;}
                break;
        }
        y = {{75*mealstime_proportion,150*mealstime_proportion,45*mealstime_proportion,25*mealstime_proportion},
             {total_protein,total_carbo,total_lipid,total_fiber},
             {210*mealstime_proportion,300*mealstime_proportion,98*mealstime_proportion,0*mealstime_proportion}};

        z = {{1000*mealstime_proportion,260*mealstime_proportion,700*mealstime_proportion,14*mealstime_proportion,
              7*mealstime_proportion,2.3*mealstime_proportion},{total_calc,total_magnesio,total_fosfer,total_ferro,
              total_zinc,total_manganes},{2500*mealstime_proportion,350*mealstime_proportion,4000*mealstime_proportion,
              45*mealstime_proportion,34*mealstime_proportion,0*mealstime_proportion}};
    }

    // Macro nutrients plot
    matplot::subplot(2,1,0);
    auto b = matplot::bar(y);
    std::vector<double> label_x;
    std::vector<double> label_y;
    std::vector<std::string> labels;
    b->face_colors()[2] = {0., .2, .6, .5};
    b->legend_string("Nutritional");
    matplot::gcf()->draw();
    matplot::xticks({1,2,3,4});
    matplot::xticklabels({"Proteins","Carbohydrates","Fats","Fibers"});
    matplot::xlabel("Macro Nutrient Name");
    matplot::ylabel("Nutritional Value");
    //matplot::save(LOCAL_PATH_EXPORTS"nutritional-menu-result/macro-nutrients.svg");
    //matplot::save(LOCAL_PATH_EXPORTS"nutritional-menu-result/macro-nutrients-latex", "epslatex");
    matplot::legend({{"LB"},{"Result"},{"UB"}});
    //Micronutrients plot
    matplot::subplot(2,1,1);
    auto c = matplot::bar(z);
    std::vector<double> label2_x;
    std::vector<double> label2_y;
    std::vector<std::string> labels2;
    c->face_colors()[2] = {0., .2, .6, .5};
    matplot::gcf()->draw();
    matplot::xticks({1,2,3,4,5,6});
    matplot::xticklabels({"Calcium","Magnesio","Fosfer",
                          "Ferro","Zinc","Manganes"});
    matplot::xlabel("Micro nutrient Name");
    matplot::ylabel("Nutritional Value");
    matplot::legend({"LB","Result","UB"});
    matplot::save(LOCAL_PATH_EXPORTS"nutritional-menu-result/nutrients.svg");
    matplot::save(LOCAL_PATH_EXPORTS"nutritional-menu-result/nutrients-latex", "epslatex");
    matplot::show();
    */

    std::cout << "Calorias: " << total_calories << ", "
              << "Custo: " << total_cost << std::endl;
    std::cout << "Proteinas: " << total_protein << ", "
              << "Gorduras: " << total_lipid << ", "
              << "Carboidratos: " << total_carbo << ", "
              << "Fibras: " << total_fiber << std::endl;
    std::cout << "Calcio: " << total_calc << ", "
              << "Magnesio: " << total_magnesio << ", "
              << "Fosforo: " << total_fosfer << ", "
              << "Ferro: " << total_ferro << ", "
              << "Zinco: " << total_zinc << ", "
              << "Manganes: " << total_manganes << ", ";

    return _solucaoID;
}

double user_diet::avaliation_function(double total_cost, double penalties_result){
    return 10000/((total_cost*total_cost) + penalties_result);
}

double user_diet::penalty_calculation(double aux,double limit,double proportionality,double penalizing_factor){
    return  ((aux / limit * proportionality) * penalizing_factor);
}

/// this function limit the inclusion of prefered ranked itens
void user_diet::preferences_inclusion_limit(nutrition_facts &p){
    switch (p.turn()) {
        ///Breakfast
    case 1: {
        //std::cout << "There is still no knowledge of any food eaten by the user." << std::endl;
    }
        break;
        ///Snack 1
    case 2: {
        //Vector of scores
        std::vector<double> _preferences = p.getSnack1Preferences();

        //Pair considering food ID and Score
        std::vector<std::pair<int, double>> _t;

        //Excludes non-scored items, that is without any preference relationship
        double aux = 0;
        for (unsigned long i = 0; i < _preferences.size(); i++)
            if (_preferences[i] > 0)
                _t.emplace_back(i, _preferences[i]);

        //Sort items in descending order by score
        std::sort(_t.begin(), _t.end(),
                  [](const std::pair<int, double> &left,
                     const std::pair<int, double> &right) {
                    return left.second > right.second;
                  });

        //FFD (first-fit Decreasing) method for inclusion of the highest rated items
        for (auto & i : _t) {

            //limits the inclusion of preferred items by 33,3% of calories for this mealtime
            if ((p.calories(i.first) + aux) <
                (p.getCaloricTargetSnack1() - p.changeTarget()) / 1.5) {

                aux += p.calories(i.first);

                // Portion of preferred items limited to 1
                this->_portions[i.first] = 1;

            }
        }
    } break;
        ///Lunch
    case 3: {
        std::vector<double> _preferences = p.getLunchPreferences();
        std::vector<std::pair<int, double>> _t;
        double aux = 0;
        for (unsigned long i = 0; i < _preferences.size(); i++)
            if (_preferences[i] > 0)
                _t.emplace_back(i, _preferences[i]);
        std::sort(_t.begin(), _t.end(),
                  [](const std::pair<int, double> &left,
                     const std::pair<int, double> &right) {
                    return left.second > right.second;
                  });

        for (auto & i : _t) {
            if ((p.calories(i.first) + aux) <
                (p.getCaloricTargetLunch() - p.changeTarget()) / 1.5) {
                aux += p.calories(i.first);
                this->_portions[i.first] = 1;
            }
        }
    }
        break;
        ///Snack 2
    case 4: {
        std::vector<double> _preferences = p.getSnack2Preferences();
        std::vector<std::pair<int, double>> _t;
        double aux = 0;
        for (unsigned long i = 0; i < _preferences.size(); i++)
            if (_preferences[i] > 0)
                _t.emplace_back(i, _preferences[i]);
        std::sort(_t.begin(), _t.end(),
                  [](const std::pair<int, double> &left,
                     const std::pair<int, double> &right) {
                    return left.second > right.second;
                  });

        for (auto & i : _t) {
            if ((p.calories(i.first) + aux) <
                (p.getCaloricTargetSnack2() - p.changeTarget()) / 1.5) {
                aux += p.calories(i.first);
                this->_portions[i.first] = 1;
            }
        }
    }
        break;
        ///Dinner
    case 5: {
        std::vector<double> _preferences = p.getDinnerPreferences();
        std::vector<std::pair<int, double>> _t;
        double aux = 0;
        for (unsigned long i = 0; i < _preferences.size(); i++)
            if (_preferences[i] > 0)
                _t.emplace_back(i, _preferences[i]);
        std::sort(_t.begin(), _t.end(),
                  [](const std::pair<int, double> &left,
                     const std::pair<int, double> &right) {
                    return left.second > right.second;
                  });
        aux =0;
        for (auto & i : _t) {
            if ((p.calories(i.first) + aux) <
                (p.getDinnerCaloriesTarget() - p.changeTarget()) / 1.5) {
                aux += p.calories(i.first);
                this->_portions[i.first] = 1;
            }
        }
    }
        break;
        ///Sopper
    case 6: {
        std::vector<double> _preferences = p.getSupperPreferences();
        std::vector<std::pair<int, double>> _t;
        double aux = 0;
        for (unsigned long i = 0; i < _preferences.size(); i++)
            if (_preferences[i] > 0)
                _t.emplace_back(i, _preferences[i]);
        std::sort(_t.begin(), _t.end(),
                  [](const std::pair<int, double> &left,
                     const std::pair<int, double> &right) {
                    return left.second > right.second;
                  });

        for (auto & i : _t) {
            if ((p.calories(i.first) + aux) <
                (p.getSupperCaloricTarget() - p.changeTarget()) / 1.5) {
                aux += p.calories(i.first);
                this->_portions[i.first] = 1;
            }
        }
    }
        break;
    }
}

/// this function evaluates the model according to its category
double user_diet::evaluate(nutrition_facts &p) {
    double total_calories = 0.0;
    double total_cost = 0.0;
    double total_protein = 0.0;
    double total_lipid = 0.0;
    double total_carbo = 0.0;
    double total_magnesio = 0.0;
    double total_ferro = 0.0;
    double total_fosfer = 0.0;
    double total_calc = 0.0;
    double total_fiber = 0.0;
    double total_zinc = 0.0;
    double total_manganes = 0.0;

    //Checks the model to be evaluated
    /// static model refers to equations 3.1 and 3.2 on page 24
    /// static model with mealstime refers to equations 3.3 - 3.6 on page 26
    /// dinamic model without preferences refers to equations 3.7 - 3.9 on page 27
    /// dinamic model considering preferences refers to equations 3.7 - 3.9 on page 27
    /// the penalties refers to equations
    int model_avaliationFunction_and_penalties = p.getModel();

    // Function that considers preferences in menu
    if (model_avaliationFunction_and_penalties == 3) preferences_inclusion_limit(p);

    //Considers nutrients and cost proportionally
    for (unsigned long i = 0; i < p.size(); ++i) {
        total_calories += this->_portions[i] * (p.calories(i));
        total_cost += this->_portions[i] * (p.cost(i));
        total_protein += this->_portions[i] * (p.protein(i));
        total_lipid += this->_portions[i] * (p.lipid(i));
        total_carbo += this->_portions[i] * (p.carbo(i));
        total_magnesio += this->_portions[i] * (p.magnesio(i));
        total_ferro += this->_portions[i] * (p.ferro(i));
        total_fosfer += this->_portions[i] * (p.fosfer(i));
        total_calc += this->_portions[i] * (p.calc(i));
        total_fiber += this->_portions[i] * (p.fiber(i));
        total_zinc += this->_portions[i] * (p.zinc(i));
        total_manganes += this->_portions[i] * (p.manganes(i));
    }

    ///Model-based assessment function
    double proportionality = 0.0;
    double caloric_deviation = 0;

    /// Total map creation to be used on penalties calc
    std::map<std::string,double> _total_nutrients;
    _total_nutrients.emplace("total_calories",total_calories);
    _total_nutrients.emplace("total_calories",total_calories);
    _total_nutrients.emplace("total_cost",total_cost);
    _total_nutrients.emplace("total_protein",total_protein);
    _total_nutrients.emplace("total_lipid",total_lipid);
    _total_nutrients.emplace("total_carbo",total_carbo);
    _total_nutrients.emplace("total_magnesio",total_magnesio);
    _total_nutrients.emplace("total_ferro",total_ferro);
    _total_nutrients.emplace("total_fosfer",total_fosfer);
    _total_nutrients.emplace("total_calc",total_calc);
    _total_nutrients.emplace("total_fiber",total_fiber);
    _total_nutrients.emplace("total_zinc",total_zinc);
    _total_nutrients.emplace("total_manganes",total_manganes);

    //Static model of single meal
    if (model_avaliationFunction_and_penalties == 0) {

        //Set up unique goal for energy and nutrients
        p.setMeta(p.getmeta());
        proportionality = 1;

        //Nutritional penalties calculation
        double nutritional_penalties = penalties_avaliation(_total_nutrients, proportionality, caloric_deviation);

        //Avaliation function to be maximized
        return avaliation_function(total_cost, nutritional_penalties);
    }

    // Mealstime models
    else if (model_avaliationFunction_and_penalties == 1 ||
             model_avaliationFunction_and_penalties == 2 ||
             model_avaliationFunction_and_penalties == 3) {
        switch (p.turn()) {
        case 1:{
            //caloric_deviation = p.getBreakfastTarget() - p.changeTarget();
            proportionality = 0.2;
            }
            break;
        case 2: {
            //caloric_deviation = p.getCaloricTargetSnack1() - p.changeTarget();
            proportionality = 0.1;
            }
            break;
        case 3: {
            //caloric_deviation = p.getCaloricTargetLunch() - p.changeTarget();
            proportionality = 0.3;
            }
            break;
        case 4:{
            //caloric_deviation = p.getCaloricTargetSnack2() - p.changeTarget();
            proportionality = 0.1;
            }
            break;
        case 5:{
            //caloric_deviation = p.getDinnerCaloriesTarget() - p.changeTarget();
            proportionality = 0.2;
            }
            break;
        case 6: {
            //caloric_deviation = p.getSupperCaloricTarget() - p.changeTarget();
            proportionality = 0.1;
            }
            break;
            default:throw std::logic_error("Please consider 6 mealstime and model options form 1 to 4");
        }

    }

    //Dinamic Nutritional penalties calculation
    double nutritional_penalties = penalties_avaliation(_total_nutrients, proportionality, caloric_deviation);

    //Dinamic Avaliation function to be maximized
    return avaliation_function(total_cost, nutritional_penalties);
}

/// Nutritional penalties calculation
double user_diet::penalties_avaliation(std::map<std::string,double> &_totals, double proportionality, double caloric_deviation){

    int penalizing_factor = 1000;
    double penalties_sum_aux = 0;
    double nutritional_penalty = 0;


    //rebalancing calories limit acording to deviation
    double rebalanced_calories = ((2000 * proportionality) - caloric_deviation);
    std::abs(rebalanced_calories);
    // Calories
    if (_totals["total_calories"] != rebalanced_calories) {
        penalties_sum_aux = (_totals["total_calories"] - rebalanced_calories);
        std::abs(penalties_sum_aux);
        nutritional_penalty += penalty_calculation(penalties_sum_aux,rebalanced_calories,proportionality,penalizing_factor);
    } //else if (_totals["total_calories"] > 2400*proportionality) {
        //penalties_sum_aux = (_totals["total_calories"] - 2400*proportionality);
        //nutritional_penalty += penalty_calculation(penalties_sum_aux,210,2400*proportionality,penalizing_factor);
    //}

    //Fibers
    if (_totals["total_fiber"] < 25 * proportionality) {
        penalties_sum_aux = (_totals["total_fiber"] - 25 * proportionality);
        if (penalties_sum_aux < 0)
            penalties_sum_aux *= -1;
        nutritional_penalty += penalty_calculation(penalties_sum_aux,25,proportionality,penalizing_factor);
    }

    // Carbohidratos
    if (_totals["total_carbo"] < 150 * proportionality) {
        penalties_sum_aux = (_totals["total_carbo"] - 150 * proportionality);
        if (penalties_sum_aux < 0)
            penalties_sum_aux *= -1;
        nutritional_penalty += penalty_calculation(penalties_sum_aux,150,proportionality,penalizing_factor);
    } else if (_totals["total_carbo"] > 300 * proportionality) {
        penalties_sum_aux = (_totals["total_carbo"] - 300 * proportionality);
        nutritional_penalty += penalty_calculation(penalties_sum_aux,300,proportionality,penalizing_factor);
    }

    // Proteinas
    if (_totals["total_protein"] < 75 * proportionality) {
        penalties_sum_aux = (_totals["total_protein"] - 75 * proportionality);
        if (penalties_sum_aux < 0)
            penalties_sum_aux *= -1;
        nutritional_penalty += penalty_calculation(penalties_sum_aux,75,proportionality,penalizing_factor);
    } else if (_totals["total_protein"] > 210 * proportionality) {
        penalties_sum_aux = (_totals["total_protein"] - 210 * proportionality);
        nutritional_penalty += penalty_calculation(penalties_sum_aux,210,proportionality,penalizing_factor);
    }

    // Calcio
    if (_totals["total_calc"] < 1000 * proportionality) {
        penalties_sum_aux = (_totals["total_calc"] - 1000 * proportionality);
        if (penalties_sum_aux < 0)
            penalties_sum_aux *= -1;
        nutritional_penalty += penalty_calculation(penalties_sum_aux,1000,proportionality,penalizing_factor);
    } else if (_totals["total_calc"] > 2500 * proportionality) {
        penalties_sum_aux = (_totals["total_calc"] - 2500 * proportionality);
        nutritional_penalty += penalty_calculation(penalties_sum_aux,2500,proportionality,penalizing_factor);
    }

    //Manganes
    if (_totals["total_manganes"] < 2.3 * proportionality) {
        penalties_sum_aux = (_totals["total_manganes"] - 2.3 * proportionality);
        if (penalties_sum_aux < 0)
            penalties_sum_aux *= -1;
        nutritional_penalty += penalty_calculation(penalties_sum_aux,2.3,proportionality,penalizing_factor);
    }

    //Ferro
    if (_totals["total_ferro"] < 14 * proportionality) {
        penalties_sum_aux = (_totals["total_ferro"] - 14 * proportionality);
        if (penalties_sum_aux < 0)
            penalties_sum_aux *= -1;
        nutritional_penalty += penalty_calculation(penalties_sum_aux,14,proportionality,penalizing_factor);
    } else if (_totals["total_ferro"] > 45 * proportionality) {
        penalties_sum_aux = (_totals["total_ferro"] - 45 * proportionality);
        nutritional_penalty += penalty_calculation(penalties_sum_aux,45,proportionality,penalizing_factor);
    }

    //Magnesio
    if (_totals["total_magnesio"] < 260 * proportionality) {
        penalties_sum_aux = (_totals["total_magnesio"] - 260 * proportionality);
        if (penalties_sum_aux < 0)
            penalties_sum_aux *= -1;
        nutritional_penalty += penalty_calculation(penalties_sum_aux,260,proportionality,penalizing_factor);
    } else if (_totals["total_magnesio"] > 350 * proportionality) {
        penalties_sum_aux = (_totals["total_magnesio"] - 350 * proportionality);
        nutritional_penalty += penalty_calculation(penalties_sum_aux,350,proportionality,penalizing_factor);
    }

    //Zinco
    if (_totals["total_zinc"] < 7) {
        penalties_sum_aux = (_totals["total_zinc"] - 7 * proportionality);
        if (penalties_sum_aux < 0)
            penalties_sum_aux *= -1;
        nutritional_penalty += penalty_calculation(penalties_sum_aux,7,proportionality,penalizing_factor);
    } else if (_totals["total_zinc"] > 34) {
        penalties_sum_aux = (_totals["total_zinc"] - 34 * proportionality);
        nutritional_penalty += penalty_calculation(penalties_sum_aux,34,proportionality,penalizing_factor);
    }

    //Fosforo
    if (_totals["total_fosfer"] < 700 * proportionality) {
        penalties_sum_aux = (_totals["total_fosfer"] - 700 * proportionality);
        if (penalties_sum_aux < 0)
            penalties_sum_aux *= -1;
        nutritional_penalty += penalty_calculation(penalties_sum_aux,700,proportionality,penalizing_factor);
    } else if (_totals["total_fosfer"] > 4000 * proportionality) {
        penalties_sum_aux = (_totals["total_fosfer"] - 4000 * proportionality);
        nutritional_penalty += penalty_calculation(penalties_sum_aux,4000,proportionality,penalizing_factor);
    }

    // Lipidios
    if (_totals["total_lipid"] < 45) {
        penalties_sum_aux = (_totals["total_lipid"] - 45 * proportionality);
        if (penalties_sum_aux < 0)
            penalties_sum_aux *= -1;
        nutritional_penalty += penalty_calculation(penalties_sum_aux,45,proportionality,penalizing_factor);
    } else if (_totals["total_lipid"] > 98) {
        penalties_sum_aux = (_totals["total_lipid"] - 98 * proportionality);
        nutritional_penalty += penalty_calculation(penalties_sum_aux,98,proportionality,penalizing_factor);
    }
    return nutritional_penalty;
}

///Mutation based in random reseting for integer problem
void user_diet::mutation( double mutation_strength) {
    std::uniform_real_distribution<double> d(0.0, 1.0);
    std::uniform_int_distribution<int> dist(0, 3);
    for (int &item : this->_portions) {
        if (d(_generator) < mutation_strength) {
            //Random reseting
            int aux;
            do {
                aux = dist(_generator);
            } while (aux == item);
            item = aux;
        }
    }
}

user_diet user_diet::crossover(nutrition_facts &p, user_diet &rhs) {
    std::uniform_int_distribution<int> d(0, 1);
    user_diet child(p);
    user_diet child2(p);
    for (unsigned long i = 0; i < p.size(); ++i) {
        if (d(_generator)) {
            child._portions[i] = this->_portions[i];
        } else {
            child._portions[i] = rhs._portions[i];
        }
    }
    return child;
}

double user_diet::distance(nutrition_facts &p, user_diet &rhs,
                           double max_dist) {
    double hamming = 0.0;
    for (unsigned long i = 0; i < p.size(); ++i) {
        if (this->_portions[i] != rhs._portions[i]) {
            hamming++;
            if (hamming > max_dist) {
                return hamming;
            }
        }
    }
    return hamming;
}

void user_diet::setPortion(int id, int quantity){
    this->_portions[id-1] = quantity;
}

int user_diet::getPortion(int id){
    return this->_portions[id-1];
}