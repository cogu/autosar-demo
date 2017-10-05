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
SystemTime_I = createSenderReceiverInterfaceTemplate('SystemTime_I', DataTypes.SystemTime_T)
SystemDate_I = createSenderReceiverInterfaceTemplate('SystemDate_I', DataTypes.SystemDate_T)
BspApi_DiscreteState_I = createSenderReceiverInterfaceTemplate('BspApi_DiscreteState_I', DataTypes.BspApi_DiscreteState_T, 'State')


class BspApi_I(autosar.Template):
   @classmethod
   def apply(cls, ws):
      package = ws.getPortInterfacePackage()
      if package.find(cls.__name__) is None:
         ws.apply(DataTypes.BspApi_DiscreteId_T)
         ws.apply(DataTypes.BspApi_DiscreteState_T)
         operationsList = ['GetDiscreteInput', 'SetDiscreteOutput']
         portInterface=package.createClientServerInterface(cls.__name__,
                                                           operationsList,
                                                           autosar.ApplicationError("E_NOT_OK", 1),
                                                           isService=True)
         portInterface["GetDiscreteInput"].createInArgument("inputId", "BspApi_DiscreteId_T")
         portInterface["GetDiscreteInput"].createOutArgument("inputValue", "BspApi_DiscreteState_T")
         portInterface["SetDiscreteOutput"].possibleErrors = "E_NOT_OK"
         portInterface['SetDiscreteOutput'].createInArgument("outputId", "BspApi_DiscreteId_T")
         portInterface['SetDiscreteOutput'].createInArgument("outputValue", "BspApi_DiscreteState_T")
         
