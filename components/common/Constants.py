import sys
import autosar
import DataTypes
from TemplateHelpers import createConstantTemplateFromEnumerationType, createConstantTemplateFromPhysicalType


#### Enumeration Constants ####
ButtonStatus_IV = createConstantTemplateFromEnumerationType('ButtonStatus_IV', DataTypes.ButtonStatus_T)

#### Physical Constants ####
RtcSeconds_IV = createConstantTemplateFromPhysicalType('C_RtcSeconds_IV', DataTypes.Seconds_T)
RtcMinutes_IV = createConstantTemplateFromPhysicalType('C_RtcMinutes_IV', DataTypes.Minutes_T)
RtcHours_IV = createConstantTemplateFromPhysicalType('C_RtcHours_IV', DataTypes.Hours_T)