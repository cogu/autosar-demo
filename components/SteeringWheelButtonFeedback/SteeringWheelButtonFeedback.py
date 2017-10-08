import sys
if __name__ == '__main__':
   sys.path.append('../common')
import autosar
import PortInterfaces
import Signals
import Services
import Modes

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
      swc.apply(Modes.EcuM_CurrentMode.Require)
      swc.apply(Signals.SWS_PushButtonStatus_Back.Receive)
      swc.apply(Signals.SWS_PushButtonStatus_Down.Receive)
      swc.apply(Signals.SWS_PushButtonStatus_Enter.Receive)
      swc.apply(Signals.SWS_PushButtonStatus_Home.Receive)
      swc.apply(Signals.SWS_PushButtonStatus_Left.Receive)
      swc.apply(Signals.SWS_PushButtonStatus_Right.Receive)
      swc.apply(Signals.SWS_PushButtonStatus_Up.Receive)
      swc.apply(Services.BspApi.Call)
   
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
      swc.behavior.createRunnable(componentName+'_Run', portAccess=[x.name for x in swc.requirePorts+swc.providePorts if x.name not in accessIgnoreList] + ['BspApi/SetDiscreteOutput'])
      swc.behavior.createTimerEvent(componentName+'_Run', 10)
      swc.behavior.createModeSwitchEvent(componentName+'_Init', 'EcuM_CurrentMode/RUN', activationType = 'ENTRY')
#      swc.behavior.createModeSwitchEvent(componentName+'_Exit', 'EcuM_CurrentMode/RUN', activationType = 'EXIT')


if __name__ == '__main__':
   ws = autosar.workspace()
   ws.apply(SteeringWheelButtonFeedback)
   ws.saveXML('SteeringWheelButtonFeedback.arxml')
   print("Done")
