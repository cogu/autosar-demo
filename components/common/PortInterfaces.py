import sys
sys.path.insert(0,'..')
import autosar
import DataTypes
from TemplateFactory import createSenderReceiverInterfaceTemplate

#### Sender Receiver Port Interfaces ####
ButtonStatus_I = createSenderReceiverInterfaceTemplate('ButtonStatus_I', DataTypes.ButtonStatus_T)
RtcSeconds_I = createSenderReceiverInterfaceTemplate('RtcSeconds_I', DataTypes.Seconds_T)
RtcMinutes_I = createSenderReceiverInterfaceTemplate('RtcMinutes_I', DataTypes.Minutes_T)
RtcHours_I = createSenderReceiverInterfaceTemplate('RtcHours_I', DataTypes.Hours_T)
VehicleModeInternal_I = createSenderReceiverInterfaceTemplate('VehicleModeInternal_I', DataTypes.VehicleModeInternal_T)

class BspApi_I(autosar.Template):
   @classmethod
   def apply(cls, ws):
      package = ws.getPortInterfacePackage()
      if package.find(cls.__name__) is None:
         ws.apply(DataTypes.BspApi_DigitalId_T)
         ws.apply(DataTypes.BspApi_DigitalState_T)
         operationsList = ['GetDiscreteInput', 'SetDiscreteOutput']
         portInterface=package.createClientServerInterface(cls.__name__,
                                                           operationsList,
                                                           autosar.ApplicationError("E_NOT_OK", 1),
                                                           isService=True)
         portInterface["GetDiscreteInput"].createInArgument("inputId", "BspApi_DigitalId_T")
         portInterface["GetDiscreteInput"].createOutArgument("inputValue", "BspApi_DigitalState_T")
         portInterface["SetDiscreteOutput"].possibleErrors = "E_NOT_OK"
         portInterface['SetDiscreteOutput'].createInArgument("outputId", "BspApi_DigitalId_T")
         portInterface['SetDiscreteOutput'].createInArgument("outputValue", "BspApi_DigitalState_T")
         
