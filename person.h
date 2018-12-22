#include<iostream>
#include<string>

using std::string;
using std::cout;
using std::endl;

enum Stat {sick = 1, susceptible, recovered, inoculated };

class Person {
  private:
    string name;
    Stat status;
    int sick_days_left;

  public:
    //constructor for person without a name
    Person(){
        name = ' ';
        status = susceptible;
        sick_days_left = 0;
    }

    //constructor for person with name
    Person(string person_name){
        name = person_name;
        status = susceptible;
        sick_days_left = 0;
    }

    string status_string(){
      switch(status){
        case 1: return "sick";
        case 2: return "susceptible";
        case 3: return "recovered";
        case 4: return "innoculated";
      }
    }

    int get_status(){
      return status;
    }

    string get_name(){
      return name;
    }

    int get_days_left(){
      return sick_days_left;
    }

    //if individual is sick and is on their last sick day, they recover
    //otherwise, their amount of sick days left decrements
    void update(){
      if(sick_days_left == 1 && status == sick){
        status = recovered;
      }else if(sick_days_left > 1){
        sick_days_left--;
      }
    }

    //an individual becomes sick
    void infect(int n){
      sick_days_left = n;
      status = sick;
    }

    void inoculate(){
      status = inoculated;
    }

    bool is_stable(){
      return (status == recovered);
    }

    bool is_sick(){
      return (status == sick);
    }
};
