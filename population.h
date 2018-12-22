#include <cstdlib>
#include <vector>
#include "person.h"

using std::vector;

class Population {
  private:
    int num_people;
    static const int days_sick = 7; // days one is sick after catching illness
    static const int num_interactions = 6; //sick people interact with a default of one person per day
    double transmission_probability;
    double inoculation_percentage;
    vector<Person> population;

  public:
    Population(int npeople){
      num_people = npeople;
      for(int i = 0; i < num_people; i++){
        population.push_back(Person());
      }
      transmission_probability = 0;
      inoculation_percentage = 0;
    }

    int get_num_people(){
      return num_people;
    }

    void set_probability_of_transfer(double p){
      transmission_probability = p;
    }

    //randomly determines what members of the population are innoculated based on percentage
    void set_inoculation(double inoculation_percentage){
      int num_to_inoculate = (int)(num_people * inoculation_percentage);
      while(num_to_inoculate != 0){
        int index = rand() % num_people;
        if(population.at(index).get_status() == susceptible){ //ensures no member of the population will be innoculated multiple times
          population.at(index).inoculate();
          num_to_inoculate--;
        }
      }
    }

    //infects random person in population for random # of days
    void random_infection(){
      int index = rand() % num_people;
      population.at(index).infect(days_sick);
    }

    //returns a count of the sick members of population
    int count_infected(){
      int num_infected = 0;
      for(int i = 0; i < num_people; i++){
        Person p = population.at(i);
        if(p.is_sick()){
          num_infected++;
        }
      }
      return num_infected;
    }

    //returns a count of the members of the population that were never infected
    int count_never_infected(){
      int num_healthy = 0;
      for(int i = 0; i < num_people; i++){
        Person p = population.at(i);
        if(p.get_status() == susceptible){
          num_healthy++;
        }
      }
      return num_healthy;
    }

    //count inoculated memevers of a population
    int count_inoculated(){
      int num_inoculated = 0;
      for(int i = 0; i < num_people; i++){
        Person p = population.at(i);
        if(p.get_status() == inoculated){
          num_inoculated++;
        }
      }
      return num_inoculated;
    }

    //person is either infected due to neighbor, gets one day closer to recover if sick, or remains healthy
    void update(){
      for(int i = 0; i < num_people; i++){
        population.at(i).update();
      }
      random_interactions();
    }

    void random_interactions(){
      for(int i = 0; i < num_people; i++){
        Person current = population.at(i);
        if(current.is_sick()){ //only executes if current person is sick
          int num_to_interact = num_interactions;
          while(num_to_interact != 0){
            int index = rand() % num_people;
            double rand_val= ((double) rand() / (RAND_MAX));
            if(rand_val <= transmission_probability && population.at(index).get_status() == susceptible){
              population.at(index).infect(days_sick);
            }
            num_to_interact--;
          }
        }
      }
    }

    //used for exercise 39.4, but not used in main.cc program as we use
    //random interaction rather than direct neighbor interaction
    void update_neighbor_transmission(){
      for(int i = 0; i < num_people; i++){
        population.at(i).update();
      }
      determine_neighbor_transmission();
    }

    //returns a vector that represents people who will get
    //during next update because of their neighbor
    //used for exercise 39.4, but not used in main.cc program as we use
    //random interaction rather than direct neighbor interaction
    void determine_neighbor_transmission(){
      for(int i = 0; i < num_people; i++){
        Person current = population.at(i);
        if(current.is_sick()){
          if((i - 1) >= 0){ //ensures search for neighbors is in bounds
            double rand_val= ((double) rand() / (RAND_MAX));
            if(rand_val <= transmission_probability && population.at(i-1).get_status() == susceptible){
              population.at(i - 1).infect(days_sick);
            }
          }
          if((i + 1) < num_people){ //ensures search for neighbors is in bounds
            double rand_val= ((double) rand() / (RAND_MAX));
            if(rand_val <= transmission_probability && population.at(i+1).get_status() == susceptible){
              population.at(i + 1).infect(days_sick);
            }
          }
        }
      }
    }

    void update_until_well(){
      while(count_infected() != 0){
        update();
      }
    }

    //prints status of population on a singular day
    void print_sickness_count(){
      cout << "# sick: " << count_infected() << " ";
      for(int i = 0; i < num_people; i++){
        Person p = population.at(i);
        switch(p.get_status()){
          case 1: cout << "+ "; break; //sick
          case 2: cout << "? "; break; //susceptible ('healthy')
          case 3: cout << "- "; break; //recovered
          case 4: cout << "! "; break; //inocculated
        }
      }
      cout << endl;
    }
};
