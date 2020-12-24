#include "actor.h"
#include <ray/api.h>
using namespace ::ray::api;

class Experiment {
 public:
  int count;

  Experiment() { count = 0; }

  static Experiment *FactoryCreate() { return new Experiment(); }
  /// non static function
  int Add(int x) {
    count += x;
    return count;
  }
};

int exec_add(){
  Ray::Init();
  ActorHandle<Experiment> actor = Ray::Actor(Experiment::FactoryCreate).Remote();
  auto r = actor.Task(&Experiment::Add, 5).Remote();
  int res = *(r.Get());
  return res;
}

int dummy(){
  return 2;
}

// int main(){
//   //  std::cout << exec_add() << std::endl;
//    std::cout << dummy() << std::endl;
// }