import sys
if __name__ == '__main__':
   sys.path.append('../common')
import autosar
import PortInterfaces
import Signals
import Services

class SteeringWheelButtonReader(autosar.Template):
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
      swc.apply(Signals.SWS_ButtonStatus_Back.Send)
      swc.apply(Signals.SWS_ButtonStatus_Down.Send)
      swc.apply(Signals.SWS_ButtonStatus_Enter.Send)
      swc.apply(Signals.SWS_ButtonStatus_Home.Send)
      swc.apply(Signals.SWS_ButtonStatus_Left.Send)
      swc.apply(Signals.SWS_ButtonStatus_Right.Send)
      swc.apply(Signals.SWS_ButtonStatus_Up.Send)
      swc.apply(Services.BspApi.Call)
   
   @classmethod
   def addBehavior(cls, swc):
      componentName = cls.__name__
      swc.behavior.createRunnable(componentName+'_Init', portAccess=[x.name for x in swc.providePorts])
      swc.behavior.createRunnable(componentName+'_Exit', portAccess=[x.name for x in swc.providePorts])
      swc.behavior.createRunnable(componentName+'_Run', portAccess=[x.name for x in swc.requirePorts+swc.providePorts if x.name != 'BspApi']+['BspApi/GetDigitalInput'])
      swc.behavior.createTimerEvent(componentName+'_Run', 10)

if __name__ == '__main__':
   ws = autosar.workspace()
   ws.apply(SteeringWheelButtonReader)
   ws.saveXML('SteeringWheelButtonReader.arxml')
   print("Done")
