import sys
import autosar
from TemplateFactory import createEnumerationDataTypeTemplate


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

valueTable=['VehicleModeInternal_Off',
            'VehicleModeInternal_Accessory',
            'VehicleModeInternal_Run',
            'VehicleModeInternal_Crank',
            'VehicleModeInternal_Spare1',
            'VehicleModeInternal_Spare2',
            'VehicleModeInternal_Error',
            'VehicleModeInternal_NotAvailable',]
VehicleModeInternal_T = createEnumerationDataTypeTemplate('VehicleModeInternal_T', valueTable)


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
   maxValue=63
   offset=0
   scaling=1
   unit='Seconds'
   invalidRangeStart=60
   errorRangeStart=62
   notAvailableRangeStart=63
   @classmethod
   def apply(cls, ws):
      package = ws.getDataTypePackage()
      if package.find(cls.__name__) is None:
         package.createIntegerDataType(cls.__name__, min=cls.minValue, max=cls.maxValue, offset=cls.offset, scaling=cls.scaling, unit=cls.unit)

class Minutes_T(autosar.Template):
   minValue=0
   maxValue=63
   offset=0
   scaling=1
   unit='Minutes'
   invalidRangeStart=60
   errorRangeStart=62
   notAvailableRangeStart=63
   @classmethod
   def apply(cls, ws):
      package = ws.getDataTypePackage()
      if package.find(cls.__name__) is None:
         package.createIntegerDataType(cls.__name__, min=cls.minValue, max=cls.maxValue, offset=cls.offset, scaling=cls.scaling, unit=cls.unit)

class Hours_T(autosar.Template):
   minValue=0
   maxValue=31
   offset=0
   scaling=1
   unit='Hours'
   invalidRangeStart=24
   errorRangeStart=30
   notAvailableRangeStart=31
   @classmethod
   def apply(cls, ws):
      package = ws.getDataTypePackage()
      if package.find(cls.__name__) is None:
         package.createIntegerDataType(cls.__name__, min=cls.minValue, max=cls.maxValue, offset=cls.offset, scaling=cls.scaling, unit=cls.unit)

class Year_T(autosar.Template):
   minValue=1
   maxValue=65535
   offset=0
   scaling=1
   unit='Year'
   invalidRangeStart=None
   errorRangeStart=65024
   notAvailableRangeStart=65280
   @classmethod
   def apply(cls, ws):
      package = ws.getDataTypePackage()
      if package.find(cls.__name__) is None:
         package.createIntegerDataType(cls.__name__, min=cls.minValue, max=cls.maxValue, offset=cls.offset, scaling=cls.scaling, unit=cls.unit)

class Month_T(autosar.Template):
   minValue=1
   maxValue=15
   offset=0
   scaling=1
   unit='Month'
   invalidRangeStart=13
   errorRangeStart=14
   notAvailableRangeStart=15
   @classmethod
   def apply(cls, ws):
      package = ws.getDataTypePackage()
      if package.find(cls.__name__) is None:
         package.createIntegerDataType(cls.__name__, min=cls.minValue, max=cls.maxValue, offset=cls.offset, scaling=cls.scaling, unit=cls.unit)

class Day_T(autosar.Template):
   minValue=1
   maxValue=63
   offset=0
   scaling=1
   unit='Days'
   invalidRangeStart=32
   errorRangeStart=62
   notAvailableRangeStart=63
   @classmethod
   def apply(cls, ws):
      package = ws.getDataTypePackage()
      if package.find(cls.__name__) is None:
         package.createIntegerDataType(cls.__name__, min=cls.minValue, max=cls.maxValue, offset=cls.offset, scaling=cls.scaling, unit=cls.unit)

class SystemTime_T(autosar.Template):
   @classmethod
   def apply(cls, ws):
      package = ws.getDataTypePackage()
      if package.find(cls.__name__) is None:
         ws.apply(Hours_T)
         ws.apply(Minutes_T)
         ws.apply(Seconds_T)
         package.createRecordDataType(cls.__name__, [('Hours', 'Hours_T'), ('Minutes','Minutes_T'),('Seconds', 'Seconds_T')])

class SystemDate_T(autosar.Template):
   @classmethod
   def apply(cls, ws):
      package = ws.getDataTypePackage()
      if package.find(cls.__name__) is None:
         ws.apply(Year_T)
         ws.apply(Month_T)
         ws.apply(Day_T)
         package.createRecordDataType(cls.__name__, [('Year', 'Year_T'), ('Month','Month_T'),('Day', 'Day_T')])


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