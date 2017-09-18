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
   
   derived_dir = 'derived'
   if not os.path.exists(derived_dir):
      os.makedirs(derived_dir)

   ws = autosar.workspace()
   ws.apply(SteeringWheelButtonReader)
   ws.apply(SteeringWheelButtonFeedback)
   ws.apply(BspService)
   partition = autosar.rte.Partition()   
   for component in ws.findall('/ComponentType/*'):
      if isinstance(component, autosar.component.ComponentType):
         partition.addComponent(component)
   partition.autoConnect()
   partition.finalize()
   for component in partition.components:
      for port in component.requirePorts+component.providePorts:
         #if len(port.portAPI)>0:            
            #print("%s/%s: %s"%(component.name, port.name, list(port.portAPI.values())[0].func.name))
            #print(str(list(port.portAPI.values())[0].func))
         for remote_port in port.connectors:
            if isinstance(port, autosar.rte.partition.ProvidePort) and isinstance(remote_port, autosar.rte.partition.RequirePort) and len(port.data_elements)>0:
               print ("%s -> %s -> %s"%(port.name, port.data_elements[0].dataType.name, remote_port.name))
      

#   typeGenerator = autosar.rte.TypeGenerator(partition)
#   typeGenerator.generate(derived_dir+'/Rte_Type.h')
#   headerGenerator = autosar.rte.ComponentHeaderGenerator(partition)
#   headerGenerator.generate(derived_dir)
#   rteGenerator = autosar.rte.RteGenerator(partition)
#   rteGenerator.generate(derived_dir)

   delta=float(time.time()-start)*1000
   print('%dms'%(round(delta)))


