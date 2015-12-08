#include "telplugins_c_api.h"

#include <stdio.h>
#include <assert.h>

#define AN(x) assert(x)

int main() {
  TELHandle manager = NULL;
  TELHandle test_model_plugin = NULL;
  TELHandle add_noise_plugin = NULL;
  bool res;

  manager = tpCreatePluginManager ("../plugins");
  AN(manager);

  test_model_plugin = tpLoadPlugin (manager, "tel_test_model");
  AN(test_model_plugin);

  add_noise_plugin = tpLoadPlugin (manager, "tel_add_noise");
  AN(add_noise_plugin);

  res = tpExecutePlugin(test_model_plugin);
  fprintf(stderr, "executed test model plugin: %d\n", res);
  if(!res) {
    fprintf(stderr, "failed to execute test model plugin\n");
    return res;
  }

  // free resources
  AN(tpFreePluginManager(manager));

  return 0;
}
