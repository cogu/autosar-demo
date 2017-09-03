#/usr/bin/env python3
import sys, os
import time
sys.path.insert(0,'../../lib')
sys.path.extend(['../common','.'])
import autosar
start=time.time()
from SteeringWheelButtonFeedback import SteeringWheelButtonFeedback

derived_dir = 'derived'
if not os.path.exists(derived_dir):
   os.makedirs(derived_dir)

ws = autosar.workspace()
ws.apply(SteeringWheelButtonFeedback)
partition = autosar.rte.Partition()
for swc in ws.findall('/ComponentType/*'):
   partition.addComponent(swc)
typeGenerator = autosar.rte.TypeGenerator(partition)
typeGenerator.generate(derived_dir+'/Rte_Type.h')
headerGenerator = autosar.rte.ComponentHeaderGenerator(partition)
headerGenerator.generate(derived_dir)
delta=float(time.time()-start)*1000
print('%dms'%(round(delta)))
