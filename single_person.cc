#include "person.h"

using std::rand;

//Illustrates the life cycle of an illness for a single person
int main(){
  srand(time(0)); //seed so that non-repetetive random numbers will be generated

  Person me("Ella");
  int day = 0;
  while(day < 50){
    day++;
    float bad_luck = (float) rand()/(float)RAND_MAX;
    if(bad_luck > .95){
      me.infect(5);
    }
    cout << "On day " << day << ", Ella is " << me.status_string();
    if(me.is_sick()){
      cout << " (" << me.get_days_left() << " to go)";
    }
    cout << endl;
    if(me.is_stable()){
      break;
    }
    me.update();
  }
  return day;
}
