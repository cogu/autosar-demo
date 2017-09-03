import sys
import autosar
import PortInterfaces
import Constants
from TemplateHelpers import createSenderReceiverPortTemplate

RtcSeconds = createSenderReceiverPortTemplate('RtcSeconds', PortInterfaces.RtcSeconds_I, Constants.RtcSeconds_IV)
RtcMinutes = createSenderReceiverPortTemplate('RtcMinutes', PortInterfaces.RtcMinutes_I, Constants.RtcMinutes_IV)
RtcHours = createSenderReceiverPortTemplate('RtcHours', PortInterfaces.RtcHours_I, Constants.RtcHours_IV)
SWS_ButtonStatus_Up = createSenderReceiverPortTemplate('SWS_ButtonStatus_Up', PortInterfaces.ButtonStatus_I, Constants.ButtonStatus_IV)
SWS_ButtonStatus_Down = createSenderReceiverPortTemplate('SWS_ButtonStatus_Down', PortInterfaces.ButtonStatus_I, Constants.ButtonStatus_IV)
SWS_ButtonStatus_Left = createSenderReceiverPortTemplate('SWS_ButtonStatus_Left', PortInterfaces.ButtonStatus_I, Constants.ButtonStatus_IV)
SWS_ButtonStatus_Right = createSenderReceiverPortTemplate('SWS_ButtonStatus_Right', PortInterfaces.ButtonStatus_I, Constants.ButtonStatus_IV)
SWS_ButtonStatus_Enter = createSenderReceiverPortTemplate('SWS_ButtonStatus_Enter', PortInterfaces.ButtonStatus_I, Constants.ButtonStatus_IV)
SWS_ButtonStatus_Back = createSenderReceiverPortTemplate('SWS_ButtonStatus_Back', PortInterfaces.ButtonStatus_I, Constants.ButtonStatus_IV)
SWS_ButtonStatus_Home = createSenderReceiverPortTemplate('SWS_ButtonStatus_Home', PortInterfaces.ButtonStatus_I, Constants.ButtonStatus_IV)

