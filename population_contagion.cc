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
    pop.update_neighbor_transmission();
  }
  //handles output showing last step when population is entirely healthy
  cout << "In step " << step + 1 << ":  ";
  pop.print_sickness_count();
  cout << "Disease ran its course by step " << step + 1 << endl;
};

//Prompts user to create population by determining population size,
//probability of illness transmission, and percentage of population innoculated
Population create_population(){
  //user prompts
  int population_size;
  double transmission_prob;
  double inoculated_percent;
  cout << "What is the size of the population? ";
  cin >> population_size;
  cout << endl << "What is the probability of transmission? ";
  cin >> transmission_prob;
  cout << endl << "What percentage of people in the population are inoculated (decimal)? ";
  cin >> inoculated_percent;

  //create population
  Population pop(population_size);
  pop.set_probability_of_transfer(transmission_prob);
  pop.set_inoculation(inoculated_percent);
  pop.random_infection(); //infect after population is innoculated
  return pop;
}

//this program expanded upon population_prototype
int main(){
  srand(time(0)); //seed so that non-repetetive random numbers will be generated
  Population pop = create_population();
  print_trial(pop);
  return 1;
};
