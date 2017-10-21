#/usr/bin/env python3
import sys, os
import time
sys.path.insert(0,'../../lib')
sys.path.append('../..')
import components
import autosar
from template.components.SteeringWheelButtonFeedback import SteeringWheelButtonFeedback

if __name__ == '__main__':
   start=time.time()
   derived_dir = 'derived'
   if not os.path.exists(derived_dir):
      os.makedirs(derived_dir)
   
   ws = autosar.workspace()
   ws.apply(SteeringWheelButtonFeedback)   
   partition = autosar.rte.Partition()
   partition.addComponent(ws.find('/ComponentType/SteeringWheelButtonFeedback'))   
   typeGenerator = autosar.rte.TypeGenerator(partition)
   typeGenerator.generate(derived_dir)
   headerGenerator = autosar.rte.ComponentHeaderGenerator(partition)
   headerGenerator.generate(derived_dir)
   rteGenerator = autosar.rte.MockRteGenerator(partition)
   rteGenerator.generate(derived_dir)
   delta=float(time.time()-start)*1000
   print('%dms'%(round(delta)))
