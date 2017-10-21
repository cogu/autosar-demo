from template import DataTypes
from template.factory import (createParameterInterfaceTemplate,createParameterPortTemplate)

ButtonDebounceTime_I = createParameterInterfaceTemplate('ButtonDebounceTime_I', DataTypes.MilliSeconds16_T)

ButtonDebounceTime = createParameterPortTemplate('ButtonDebounceTime', ButtonDebounceTime_I)
