import sys
import autosar
import DataTypes
from TemplateFactory import createConstantTemplateFromEnumerationType, createConstantTemplateFromPhysicalType


#### Enumeration Constants ####
ButtonStatus_IV = createConstantTemplateFromEnumerationType('ButtonStatus_IV', DataTypes.ButtonStatus_T)
VehicleModeInternal_IV = createConstantTemplateFromEnumerationType('VehicleModeInternal_IV', DataTypes.VehicleModeInternal_T)
DiscreteState_IV = createConstantTemplateFromEnumerationType('DiscreteState_IV', DataTypes.BspApi_DiscreteState_T)

#### Physical Constants ####
RtcSeconds_IV = createConstantTemplateFromPhysicalType('RtcSeconds_IV', DataTypes.Seconds_T)
RtcMinutes_IV = createConstantTemplateFromPhysicalType('RtcMinutes_IV', DataTypes.Minutes_T)
RtcHours_IV = createConstantTemplateFromPhysicalType('RtcHours_IV', DataTypes.Hours_T)

#### Custom Constants ####
class SystemTime_IV(autosar.Template):
   
   dataTypeTemplate = DataTypes.SystemTime_T
   
   @classmethod
   def apply(cls, ws):
      package = ws.getConstantPackage()
      if package.find(cls.__name__) is None:
         ws.apply(cls.dataTypeTemplate)
         package.createConstant(cls.__name__, cls.dataTypeTemplate.__name__, {'Hours':31, 'Minutes': 63, 'Seconds': 63})

class SystemDate_IV(autosar.Template):
   
   dataTypeTemplate = DataTypes.SystemDate_T
   
   @classmethod
   def apply(cls, ws):
      package = ws.getConstantPackage()
      if package.find(cls.__name__) is None:
         ws.apply(cls.dataTypeTemplate)
         package.createConstant(cls.__name__, cls.dataTypeTemplate.__name__, {'Year':65535, 'Month': 15, 'Day': 63})
