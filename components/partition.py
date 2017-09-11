import os, sys
import time

sys.path.insert(0,'../lib')
for dir_name in ['common', 'BspService',
            'FreeRunningTimerService',
            'SteeringWheelButtonReader',
            'SteeringWheelButtonFeedback',
            ]:
   sys.path.append(os.path.abspath(os.path.join(os.path.dirname(__file__), dir_name)))
import autosar
start=time.time()
from SteeringWheelButtonReader import SteeringWheelButtonReader
from SteeringWheelButtonFeedback import SteeringWheelButtonFeedback
from BspService import BspService


if __name__ == '__main__':
   ws = autosar.workspace()
   ws.apply(SteeringWheelButtonReader)
   ws.apply(SteeringWheelButtonFeedback)
   ws.apply(BspService)
   partition = autosar.rte.Partition()   
   for component in ws.findall('/ComponentType/*'):
      if isinstance(component, autosar.component.ComponentType):
         partition.addComponent(component)
   partition.autoConnect()
   print(len(partition.assemblyConnectors))
   for connector in partition.assemblyConnectors:
      print("%s/%s => %s/%s"%(connector.provide.component.name, connector.provide.port.name, connector.require.component.name, connector.require.port.name))
   delta=float(time.time()-start)*1000
   print('%dms'%(round(delta)))


