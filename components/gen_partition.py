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
from SteeringWheelButtonReader import SteeringWheelButtonReader
from SteeringWheelButtonFeedback import SteeringWheelButtonFeedback
from BspService import BspService
import Signals
import apx

if __name__ == '__main__':
   start=time.time()
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
   com = autosar.bsw.ComComponent(ws, 'ApxCom')
   com.apply(Signals.SWS_PushButtonStatus_Back.Receive)
   com.apply(Signals.SWS_PushButtonStatus_Down.Receive)
   com.apply(Signals.SWS_PushButtonStatus_Enter.Receive)
   com.apply(Signals.SWS_PushButtonStatus_Home.Receive)
   com.apply(Signals.SWS_PushButtonStatus_Left.Receive)
   com.apply(Signals.SWS_PushButtonStatus_Right.Receive)
   com.apply(Signals.SWS_PushButtonStatus_Up.Receive)
   com.apply(Signals.VehicleModeInternal.Send)
   partition.addComponent(com)
   partition.autoConnect()
   partition.finalize()   
   com.finalize()
   
   typeGenerator = autosar.rte.TypeGenerator(partition)
   typeGenerator.generate(derived_dir)
   headerGenerator = autosar.rte.ComponentHeaderGenerator(partition)
   headerGenerator.generate(derived_dir)
   rteGenerator = autosar.rte.RteGenerator(partition)
   rteGenerator.generate(derived_dir)   
   #print('\n'.join(com_apx_node.lines()))
   comGenerator = apx.generator.ComGenerator(com)

   delta=float(time.time()-start)*1000
   print('%dms'%(round(delta)))


