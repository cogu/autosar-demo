import sys
import autosar
from template import PortInterfaces, Constants
from template.factory import createClientServerPortTemplate

BspApi = createClientServerPortTemplate('BspApi', PortInterfaces.BspApi_I)
