import sys
if __name__ == '__main__':
   sys.path.append('../common')
import autosar
import PortInterfaces
import Signals
import Services

class SteeringWheelButtonFeedback(autosar.Template):
   @classmethod
   def apply(cls, ws):
      componentName = cls.__name__
      package = ws.getComponentTypePackage()
      if package.find(componentName) is None:
         swc = package.createApplicationSoftwareComponent(componentName)
         cls.addPorts(swc)
         cls.addBehavior(swc)
   
   @classmethod
   def addPorts(cls, swc):
      componentName = cls.__name__
      swc.apply(Signals.SWS_ButtonStatus_Back.Receive)
      swc.apply(Signals.SWS_ButtonStatus_Down.Receive)
      swc.apply(Signals.SWS_ButtonStatus_Enter.Receive)
      swc.apply(Signals.SWS_ButtonStatus_Home.Receive)
      swc.apply(Signals.SWS_ButtonStatus_Left.Receive)
      swc.apply(Signals.SWS_ButtonStatus_Right.Receive)
      swc.apply(Signals.SWS_ButtonStatus_Up.Receive)
      swc.apply(Services.BspApi.Call)
   
   @classmethod
   def addBehavior(cls, swc):
      componentName = cls.__name__
      swc.behavior.createRunnable(componentName+'_Init', portAccess=[x.name for x in swc.providePorts]+['BspApi/SetDigitalOutput'])
      swc.behavior.createRunnable(componentName+'_Exit', portAccess=[x.name for x in swc.providePorts]+['BspApi/SetDigitalOutput'])
      swc.behavior.createRunnable(componentName+'_Run', portAccess=[x.name for x in swc.requirePorts+swc.providePorts if x.name != 'BspApi']+['BspApi/SetDigitalOutput'])
      swc.behavior.createTimerEvent(componentName+'_Run', 10)

if __name__ == '__main__':
   ws = autosar.workspace()
   ws.apply(SteeringWheelButtonFeedback)
   ws.saveXML('SteeringWheelButtonFeedback.arxml')
   print("Done")
