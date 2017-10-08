import sys
sys.path.append('../common')
import autosar
import PortInterfaces
import Services
import Modes

class BspService(autosar.Template):
   @classmethod
   def apply(cls, ws):
      componentName = cls.__name__
      package = ws.getComponentTypePackage()
      if package.find(componentName) is None:
         swc = package.createServiceComponent(componentName)
         cls.addPorts(swc)
         cls.addBehavior(swc)
   
   @classmethod
   def addPorts(cls, swc):
      componentName = cls.__name__
      swc.apply(Modes.EcuM_CurrentMode.Require)
      swc.apply(Services.BspApi.Provide)
      
   
   @classmethod
   def addBehavior(cls, swc):
      componentName = cls.__name__
      swc.behavior.createRunnable(componentName+'_Init')
      swc.behavior.createRunnable(componentName+'_Exit')
      cls.addServerRunnables(swc)
   
   @classmethod
   def addServerRunnables(cls, swc):
      componentName = cls.__name__      
      swc.behavior.createRunnable(componentName+'_GetDiscreteInput', concurrent=True)
      swc.behavior.createRunnable(componentName+'_SetDiscreteOutput', concurrent=True)
      swc.behavior.createOperationInvokedEvent(componentName+'_GetDiscreteInput', 'BspApi/GetDiscreteInput')
      swc.behavior.createOperationInvokedEvent(componentName+'_SetDiscreteOutput', 'BspApi/SetDiscreteOutput')
      swc.behavior.createModeSwitchEvent(componentName+'_Init', 'EcuM_CurrentMode/RUN', activationType = 'ENTRY')
      swc.behavior.createModeSwitchEvent(componentName+'_Exit', 'EcuM_CurrentMode/RUN', activationType = 'EXIT')


if __name__ == '__main__':
   ws = autosar.workspace()
   ws.apply(BspService)   
   ws.saveXML('BspService.arxml')
   print("Done")
