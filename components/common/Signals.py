import sys
import autosar
import PortInterfaces
import Constants
from TemplateFactory import createSenderReceiverPortTemplate

RtcSeconds = createSenderReceiverPortTemplate('RtcSeconds', PortInterfaces.RtcSeconds_I, Constants.RtcSeconds_IV)
RtcMinutes = createSenderReceiverPortTemplate('RtcMinutes', PortInterfaces.RtcMinutes_I, Constants.RtcMinutes_IV)
RtcHours = createSenderReceiverPortTemplate('RtcHours', PortInterfaces.RtcHours_I, Constants.RtcHours_IV)
SWS_PushButtonStatus_Up = createSenderReceiverPortTemplate('SWS_PushButtonStatus_Up', PortInterfaces.ButtonStatus_I, Constants.ButtonStatus_IV)
SWS_PushButtonStatus_Down = createSenderReceiverPortTemplate('SWS_PushButtonStatus_Down', PortInterfaces.ButtonStatus_I, Constants.ButtonStatus_IV)
SWS_PushButtonStatus_Left = createSenderReceiverPortTemplate('SWS_PushButtonStatus_Left', PortInterfaces.ButtonStatus_I, Constants.ButtonStatus_IV)
SWS_PushButtonStatus_Right = createSenderReceiverPortTemplate('SWS_PushButtonStatus_Right', PortInterfaces.ButtonStatus_I, Constants.ButtonStatus_IV)
SWS_PushButtonStatus_Enter = createSenderReceiverPortTemplate('SWS_PushButtonStatus_Enter', PortInterfaces.ButtonStatus_I, Constants.ButtonStatus_IV)
SWS_PushButtonStatus_Back = createSenderReceiverPortTemplate('SWS_PushButtonStatus_Back', PortInterfaces.ButtonStatus_I, Constants.ButtonStatus_IV)
SWS_PushButtonStatus_Home = createSenderReceiverPortTemplate('SWS_PushButtonStatus_Home', PortInterfaces.ButtonStatus_I, Constants.ButtonStatus_IV)
VehicleModeInternal = createSenderReceiverPortTemplate('VehicleModeInternal', PortInterfaces.VehicleModeInternal_I, Constants.VehicleModeInternal_IV)

