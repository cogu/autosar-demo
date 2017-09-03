import sys
sys.path.append('../common')
import autosar
import PortInterfaces
import Services

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
      swc.apply(Services.BspApi.Provide)
      
   
   @classmethod
   def addBehavior(cls, swc):
      componentName = cls.__name__
      swc.behavior.createRunnable(componentName+'_Init')
      swc.behavior.createRunnable(componentName+'_Exit')
      swc.behavior.createRunnable(componentName+'_Run')
      swc.behavior.createTimerEvent(componentName+'_Run', 5)
      cls.addServerRunnables(swc)
   
   @classmethod
   def addServerRunnables(cls, swc):
      componentName = cls.__name__      
      swc.behavior.createRunnable(componentName+'_GetDigitalInput', concurrent=True)
      swc.behavior.createRunnable(componentName+'_SetDigitalOutput', concurrent=True)
      swc.behavior.createOperationInvokedEvent(componentName+'_GetDigitalInput', 'BspApi/GetDigitalInput')
      swc.behavior.createOperationInvokedEvent(componentName+'_SetDigitalOutput', 'BspApi/SetDigitalOutput')

if __name__ == '__main__':
   ws = autosar.workspace()
   ws.apply(BspService)   
   ws.saveXML('BspService.arxml')
   print("Done")
