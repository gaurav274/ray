#include "actor/actor.h"

#include <ray/api.h>
#include <ray/api/ray_config.h>
#include <ray/experimental/default_worker.h>

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

int exec_add() {
  ray::api::RayConfig::GetInstance()->run_mode = RunMode::CLUSTER;
  /// TODO(Guyang Song): add the dynamic library name
  ray::api::RayConfig::GetInstance()->lib_name = "";
  std::cout << "Starting Ray Cluster" << std::endl;

  Ray::Init();
  ActorHandle<Experiment> actor = Ray::Actor(Experiment::FactoryCreate).Remote();
  auto r = actor.Task(&Experiment::Add, 5).Remote();
  int res = *(r.Get());
  return res;
}

int dummy() { return 2; }

// int main(){
//   //  std::cout << exec_add() << std::endl;
//    std::cout << dummy() << std::endl;
// }
int main(int argc, char **argv) {
  const char *default_worker_magic = "is_default_worker";
  /// `is_default_worker` is the last arg of `argv`
  if (argc > 1 &&
      memcmp(argv[argc - 1], default_worker_magic, strlen(default_worker_magic)) == 0) {
    default_worker_main(argc, argv);
    return 0;
  }
}