#include "population.h"
#include <ctime>

using std::cin;

//prints population information
void print_trial(Population pop){
  int pop_size = pop.get_num_people();
  cout << "Size of population: " << pop_size << endl;
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

  int num_healthy = pop.count_never_infected();
  int num_inoculated = pop.count_inoculated();
  double percent_never_infected = ((double)(num_healthy)) / ((double)(pop_size - num_inoculated));

  cout << "Disease ran its course by step " << step + 1 << endl;
  cout << "Percent of unvaccinated people that were never ill: " << percent_never_infected << endl;
};

//Prompts user to create population by determining population size,
//probability of illness transmission, and percentage of population innoculated
Population create_population(){
  //user prompts
  int population_size;
  double transmission_prob;
  double innoculated_percent;
  cout << "What is the size of the population? ";
  cin >> population_size;
  cout << endl << "What is the probability of transmission? ";
  cin >> transmission_prob;
  cout << endl << "What percentage of people in the population are inoculated (decimal)? ";
  cin >> innoculated_percent;

  //create population
  Population pop(population_size);
  pop.set_probability_of_transfer(transmission_prob);
  pop.set_inoculation(innoculated_percent);
  pop.random_infection(); //infect after population is innoculated
  return pop;
}

//this program is expanded upon from population_contagion.cc
int main(){
  srand(time(0)); //seed so that non-repetetive random numbers will be generated
  Population pop = create_population();
  print_trial(pop);
  return 1;
};
