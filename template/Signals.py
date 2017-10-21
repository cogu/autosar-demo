import sys
import autosar
from template import PortInterfaces, Constants
from template.factory import createSenderReceiverPortTemplate

SystemTime = createSenderReceiverPortTemplate('SystemTime', PortInterfaces.SystemTime_I, Constants.SystemTime_IV)
SystemDate = createSenderReceiverPortTemplate('SystemDate', PortInterfaces.SystemDate_I, Constants.SystemDate_IV)
SWS_PushButtonStatus_Up = createSenderReceiverPortTemplate('SWS_PushButtonStatus_Up', PortInterfaces.ButtonStatus_I, Constants.ButtonStatus_IV)
SWS_PushButtonStatus_Down = createSenderReceiverPortTemplate('SWS_PushButtonStatus_Down', PortInterfaces.ButtonStatus_I, Constants.ButtonStatus_IV)
SWS_PushButtonStatus_Left = createSenderReceiverPortTemplate('SWS_PushButtonStatus_Left', PortInterfaces.ButtonStatus_I, Constants.ButtonStatus_IV)
SWS_PushButtonStatus_Right = createSenderReceiverPortTemplate('SWS_PushButtonStatus_Right', PortInterfaces.ButtonStatus_I, Constants.ButtonStatus_IV)
SWS_PushButtonStatus_Enter = createSenderReceiverPortTemplate('SWS_PushButtonStatus_Enter', PortInterfaces.ButtonStatus_I, Constants.ButtonStatus_IV)
SWS_PushButtonStatus_Back = createSenderReceiverPortTemplate('SWS_PushButtonStatus_Back', PortInterfaces.ButtonStatus_I, Constants.ButtonStatus_IV)
SWS_PushButtonStatus_Home = createSenderReceiverPortTemplate('SWS_PushButtonStatus_Home', PortInterfaces.ButtonStatus_I, Constants.ButtonStatus_IV)
VehicleModeInternal = createSenderReceiverPortTemplate('VehicleModeInternal', PortInterfaces.VehicleModeInternal_I, Constants.VehicleModeInternal_IV)

