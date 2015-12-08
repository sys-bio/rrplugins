import rrplugins.telplugins_c_api as tpc


manager = tpc.createPluginManager('../plugins')
print('manager = {}'.format(hex(manager)))
if manager == 0:
  raise RuntimeError('Failed to create manager')

test_model_plugin = tpc.loadPlugin(manager, 'tel_test_model')
print('test model plugin = {}'.format(hex(test_model_plugin)))
if test_model_plugin == 0:
  raise RuntimeError('Failed to create test_model_plugin')

add_noise_plugin = tpc.loadPlugin(manager, 'tel_add_noise')
print('add noise plugin = {}'.format(hex(add_noise_plugin)))
if add_noise_plugin == 0:
  raise RuntimeError('Failed to create add_noise_plugin')

res = tpc.executePlugin(test_model_plugin)
print('executed test model plugin, result: {}'.format(res))