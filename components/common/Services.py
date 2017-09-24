import sys
import autosar
import PortInterfaces
import Constants
from TemplateFactory import createClientServerPortTemplate

BspApi = createClientServerPortTemplate('BspApi', PortInterfaces.BspApi_I)
