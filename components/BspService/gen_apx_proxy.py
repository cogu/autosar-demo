#/usr/bin/env python3
import sys, os
import time
sys.path.insert(0,'../../lib')
sys.path.append('../../')
import autosar
import apx
import components
import PortInterfaces
import Constants
from TemplateFactory import createSenderReceiverPortTemplate

HomeButtonPressed = createSenderReceiverPortTemplate('HomeButtonPressed', PortInterfaces.BspApi_DiscreteState_I, Constants.DiscreteState_IV)
BackButtonPressed = createSenderReceiverPortTemplate('BackButtonPressed', PortInterfaces.BspApi_DiscreteState_I, Constants.DiscreteState_IV)
EnterButtonPressed = createSenderReceiverPortTemplate('EnterButtonPressed', PortInterfaces.BspApi_DiscreteState_I, Constants.DiscreteState_IV)
LeftButtonPressed = createSenderReceiverPortTemplate('LeftButtonPressed', PortInterfaces.BspApi_DiscreteState_I, Constants.DiscreteState_IV)
RightButtonPressed = createSenderReceiverPortTemplate('RightButtonPressed', PortInterfaces.BspApi_DiscreteState_I, Constants.DiscreteState_IV)
UpButtonPressed = createSenderReceiverPortTemplate('UpButtonPressed', PortInterfaces.BspApi_DiscreteState_I, Constants.DiscreteState_IV)
DownButtonPressed = createSenderReceiverPortTemplate('DownButtonPressed', PortInterfaces.BspApi_DiscreteState_I, Constants.DiscreteState_IV)

HomeButtonLED = createSenderReceiverPortTemplate('HomeButtonLED', PortInterfaces.BspApi_DiscreteState_I, Constants.DiscreteState_IV)
BackButtonLED = createSenderReceiverPortTemplate('BackButtonLED', PortInterfaces.BspApi_DiscreteState_I, Constants.DiscreteState_IV)
EnterButtonLED = createSenderReceiverPortTemplate('EnterButtonLED', PortInterfaces.BspApi_DiscreteState_I, Constants.DiscreteState_IV)
LeftButtonLED = createSenderReceiverPortTemplate('LeftButtonLED', PortInterfaces.BspApi_DiscreteState_I, Constants.DiscreteState_IV)
RightButtonLED = createSenderReceiverPortTemplate('RightButtonLED', PortInterfaces.BspApi_DiscreteState_I, Constants.DiscreteState_IV)
UpButtonLED = createSenderReceiverPortTemplate('UpButtonLED', PortInterfaces.BspApi_DiscreteState_I, Constants.DiscreteState_IV)
DownButtonLED = createSenderReceiverPortTemplate('DownButtonLED', PortInterfaces.BspApi_DiscreteState_I, Constants.DiscreteState_IV)

class BspServiceProxy(autosar.Template):
   @classmethod
   def apply(cls, ws):
      componentName = cls.__name__
      package = ws.getComponentTypePackage()
      if package.find(componentName) is None:
         swc = package.createApplicationSoftwareComponent(componentName)
         swc.apply(HomeButtonPressed.Receive)
         swc.apply(BackButtonPressed.Receive)
         swc.apply(EnterButtonPressed.Receive)
         swc.apply(LeftButtonPressed.Receive)
         swc.apply(RightButtonPressed.Receive)
         swc.apply(UpButtonPressed.Receive)
         swc.apply(DownButtonPressed.Receive)

         swc.apply(HomeButtonLED.Send)
         swc.apply(BackButtonLED.Send)
         swc.apply(EnterButtonLED.Send)
         swc.apply(LeftButtonLED.Send)
         swc.apply(RightButtonLED.Send)
         swc.apply(UpButtonLED.Send)
         swc.apply(DownButtonLED.Send)
   
if __name__ == '__main__':
   start=time.time()
   gen_dir = os.path.abspath('source/apx_proxy')

   ws = autosar.workspace()
   ws.apply(BspServiceProxy)
   node = apx.Node.from_autosar_swc(ws.find('/ComponentType/BspServiceProxy'))
   context = apx.Context()
   #context.append(node)
   #context.generateAPX('.')
   apx.NodeGenerator().generate(gen_dir, node, includes=['Rte_Type.h'])

   delta=float(time.time()-start)*1000
   print('%dms'%(round(delta)))
