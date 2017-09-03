import sys
import autosar
import PortInterfaces
import Constants
from TemplateHelpers import createClientServerPortTemplate

BspApi = createClientServerPortTemplate('BspApi', PortInterfaces.BspApi_I)
