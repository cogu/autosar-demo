import sys
import time


if __name__ == '__main__':
   sys.path.insert(0,'../lib')
   sys.path.append('../common')
import autosar
from template import PortInterfaces, Signals, Services, Modes

class RealTimeClock(autosar.Template):
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
      swc.apply(Modes.EcuM_CurrentMode.Require)
      swc.apply(Signals.SystemTime.Send)
      swc.apply(Signals.SystemDate.Send)
      #swc.apply(Services.BspApi.Call)
   
   @classmethod
   def addBehavior(cls, swc):
      componentName = cls.__name__
      accessIgnoreList=[]
      ws = swc.rootWS()
      for port in swc.requirePorts+swc.providePorts:
         portInterface = ws.find(port.portInterfaceRef)
         if not isinstance(portInterface, autosar.portinterface.SenderReceiverInterface) or len(portInterface.dataElements)==0:
            accessIgnoreList.append(port.name)
      swc.behavior.createRunnable(componentName+'_Init', portAccess=[x.name for x in swc.providePorts])
      swc.behavior.createRunnable(componentName+'_Exit', portAccess=[x.name for x in swc.providePorts])
      swc.behavior.createRunnable(componentName+'_Run', portAccess=[x.name for x in swc.requirePorts+swc.providePorts if x.name not in accessIgnoreList])
      swc.behavior.createTimerEvent(componentName+'_Run', 10)
      swc.behavior.createModeSwitchEvent(componentName+'_Init', 'EcuM_CurrentMode/RUN')

if __name__ == '__main__':
   ws = autosar.workspace()
   ws.apply(RealTimeClock)
   ws.saveXML('RealTimeClock.arxml')
   print("Done")
