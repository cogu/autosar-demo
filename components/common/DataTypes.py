import sys
import autosar
from TemplateHelpers import createEnumerationDataTypeTemplate

      
#### Enumeration Data Types ####
valueTable=['InactiveActive_Inactive',
            'InactiveActive_Active',
            'InactiveActive_Error',
            'InactiveActive_NotAvailable']
InactiveActive_T = createEnumerationDataTypeTemplate('InactiveActive_T', valueTable)

valueTable=['ButtonStatus_Released',
            'ButtonStatus_Pressed',
            'ButtonStatus_Error',
            'ButtonStatus_NotAvailable']
ButtonStatus_T = createEnumerationDataTypeTemplate('ButtonStatus_T', valueTable)

valueTable=['BspApi_DigitalState_Inactive',
            'BspApi_DigitalState_Active',
            'BspApi_DigitalState_Error',
            'BspApi_DigitalState_NotAvailable']
BspApi_DigitalState_T = createEnumerationDataTypeTemplate('BspApi_DigitalState_T', valueTable)

#### Physical Data Types ####
class Percent_T(autosar.Template):
   minValue=0
   maxValue=255
   offset=0
   scaling=0.4
   unit='percent'
   invalidRangeStart=251
   errorRangeStart=254
   notAvailableRangeStart=255
   @classmethod
   def apply(cls, ws):
      package = ws.getDataTypePackage()
      if package.find(cls.__name__) is None:         
         package.createIntegerDataType(cls.__name__, min=cls.minValue, max=cls.maxValue, offset=cls.offset, scaling=cls.scaling, unit=cls.unit)

class Seconds_T(autosar.Template):
   minValue=0
   maxValue=255
   offset=0
   scaling=1
   unit='Seconds'
   invalidRangeStart=60
   errorRangeStart=254
   notAvailableRangeStart=255
   @classmethod
   def apply(cls, ws):
      package = ws.getDataTypePackage()
      if package.find(cls.__name__) is None:         
         package.createIntegerDataType(cls.__name__, min=cls.minValue, max=cls.maxValue, offset=cls.offset, scaling=cls.scaling, unit=cls.unit)

class Minutes_T(autosar.Template):
   minValue=0
   maxValue=255
   offset=0
   scaling=1
   unit='Minutes'
   invalidRangeStart=60
   errorRangeStart=254
   notAvailableRangeStart=255
   @classmethod
   def apply(cls, ws):
      package = ws.getDataTypePackage()
      if package.find(cls.__name__) is None:         
         package.createIntegerDataType(cls.__name__, min=cls.minValue, max=cls.maxValue, offset=cls.offset, scaling=cls.scaling, unit=cls.unit)

class Hours_T(autosar.Template):
   minValue=0
   maxValue=255
   offset=0
   scaling=1
   unit='Hours'
   invalidRangeStart=60
   errorRangeStart=254
   notAvailableRangeStart=255
   @classmethod
   def apply(cls, ws):
      package = ws.getDataTypePackage()
      if package.find(cls.__name__) is None:         
         package.createIntegerDataType(cls.__name__, min=cls.minValue, max=cls.maxValue, offset=cls.offset, scaling=cls.scaling, unit=cls.unit)


class DistanceHiRes_T(autosar.Template):
   minValue=0
   maxValue=0xFFFFFFFF
   offset=0
   scaling=1
   unit='Meters'
   invalidRangeStart=None
   errorRangeStart=0xFE000000
   notAvailableRangeStart=0xFF000000
   @classmethod
   def apply(cls, ws):
      package = ws.getDataTypePackage()
      if package.find(cls.__name__) is None:         
         package.createIntegerDataType(cls.__name__, min=cls.minValue, max=cls.maxValue, offset=cls.offset, scaling=cls.scaling, unit=cls.unit)

class BspApi_DigitalId_T(autosar.Template):
   minValue=0
   maxValue=255
   offset=0
   scaling=1
   unit='Id'
   invalidRangeStart=251
   errorRangeStart=254
   notAvailableRangeStart=255
   @classmethod
   def apply(cls, ws):
      package = ws.getDataTypePackage()
      if package.find(cls.__name__) is None:         
         package.createIntegerDataType(cls.__name__, min=cls.minValue, max=cls.maxValue, offset=cls.offset, scaling=cls.scaling, unit=cls.unit)