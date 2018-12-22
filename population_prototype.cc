#include "population.h"
#include <ctime>

using std::cin;

//prints population information
void print_trial(Population pop){
  cout << "Size of population: " << pop.get_num_people() << endl;
  int step = 0;
  while(pop.count_infected() != 0){
    step++;
    cout << "In step " << step << ":  ";
    pop.print_sickness_count();
    pop.update();
  }
  //handles output showing last step when population is entirely healthy
  cout << "In step " << step + 1 << ":  ";
  pop.print_sickness_count();
  cout << "Disease ran its course by step " << step + 1 << endl;
};

//Prompts user to create population by determining population size
Population create_population(){
  //user prompts
  int population_size;
  double transmission_prob;
  double innoculated_percent;
  cout << "What is the size of the population? ";
  cin >> population_size;

  //create population
  Population pop(population_size);
  pop.random_infection();
  return pop;
}

int main(){
  srand(time(0)); //seed so that non-repetitive random numbers will be generated
  Population pop = create_population();
  print_trial(pop);
  return 1;
};
