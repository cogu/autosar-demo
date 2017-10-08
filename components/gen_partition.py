import os, sys
import time

sys.path.insert(0,'../lib')
sys.path.append('..')
import components
import autosar
from SteeringWheelButtonReader import SteeringWheelButtonReader
from SteeringWheelButtonFeedback import SteeringWheelButtonFeedback
from BspService import BspService
#from RealTimeClock import RealTimeClock
import Signals
import apx

def create_os_config(partition):
   os_cfg = os_cfg = autosar.bsw.OsConfig()
   app_task = os_cfg.create_task('App_Task')
   service_task = os_cfg.create_task('Service_Task')
   map_runnables_to_task(os_cfg, app_task, service_task)
   return os_cfg

def map_runnables_to_task(os_cfg, app_task, service_task):
   for component in partition.components:
      if isinstance(component.inner, autosar.component.ServiceComponent):
         for runnable in component.runnables:
            service_task.map_runnable(runnable)
      else:
         for runnable in component.runnables:
            app_task.map_runnable(runnable)


if __name__ == '__main__':
   start=time.time()
   derived_dir = 'derived'
   if not os.path.exists(derived_dir):
      os.makedirs(derived_dir)

   ws = autosar.workspace()
   ws.apply(SteeringWheelButtonReader)
   ws.apply(SteeringWheelButtonFeedback)
   #ws.apply(RealTimeClock)
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
   #com.apply(Signals.SystemTime.Receive)
   #com.apply(Signals.SystemDate.Receive)
   #com.apply(Signals.VehicleModeInternal.Send)
   partition.addComponent(com)
   partition.autoConnect()
   partition.finalize()

   typeGenerator = autosar.rte.TypeGenerator(partition)
   typeGenerator.generate(derived_dir)
   headerGenerator = autosar.rte.ComponentHeaderGenerator(partition)
   headerGenerator.generate(derived_dir)
   rteGenerator = autosar.rte.RteGenerator(partition)
   rteGenerator.generate(derived_dir)
   comGenerator = apx.generator.ComGenerator(com)
   comGenerator.generateHeader(derived_dir)
   comGenerator.generateSource(derived_dir)
   nodeGenerator = apx.NodeGenerator()
   nodeGenerator.generate(derived_dir, comGenerator.apx_node, includes=['Rte_Type.h'])

   os_cfg = create_os_config(partition)
   osConfigGenerator = autosar.bsw.OsConfigGenerator(os_cfg)
   osConfigGenerator.generateEventCfg(derived_dir)
   

   delta=float(time.time()-start)*1000
   print('%dms'%(round(delta)))
