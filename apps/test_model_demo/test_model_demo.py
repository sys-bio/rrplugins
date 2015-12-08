from ctypes import CDLL, c_void_p, c_char_p, c_bool

tpclib = CDLL('../lib/libtelplugins_c_api.so')

TELHandle = c_void_p

# prototypes
tpclib.tpCreatePluginManager.argtypes = [c_char_p]
tpclib.tpCreatePluginManager.restype = TELHandle

tpclib.tpLoadPlugin.argtypes = [TELHandle, c_char_p]
tpclib.tpLoadPlugin.restype = TELHandle

tpclib.tpExecutePlugin.argtypes = [TELHandle]
tpclib.tpExecutePlugin.restype = c_bool


manager = tpclib.tpCreatePluginManager('../plugins')
#print(hex(manager))
if manager == 0:
  raise RuntimeError('Failed to create manager')

test_model_plugin = tpclib.tpLoadPlugin(manager, 'tel_test_model')
#print(hex(test_model_plugin))
if test_model_plugin == 0:
  raise RuntimeError('Failed to create test_model_plugin')

add_noise_plugin = tpclib.tpLoadPlugin(manager, 'tel_add_noise')
print(hex(add_noise_plugin))
if add_noise_plugin == 0:
  raise RuntimeError('Failed to create add_noise_plugin')

res = tpclib.tpExecutePlugin(test_model_plugin)
print('executed test model plugin, result: {}'.format(res))