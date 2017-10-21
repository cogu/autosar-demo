import sys
import autosar

#DataTypes
def createEnumerationDataTypeTemplate(name, valueTable):
   @classmethod
   def apply(cls, ws):
      package = ws.getDataTypePackage()
      if package.find(cls.__name__) is None:
         package.createIntegerDataType(cls.__name__, valueTable=cls.valueTable)
   return type(name, (autosar.Template,), dict(valueTable=valueTable, apply=apply))

#Constants
def createConstantTemplateFromEnumerationType(name, dataTypeTemplate, adminData=None):
   @classmethod
   def apply(cls, ws):
      package = ws.getConstantPackage()
      if package.find(cls.__name__) is None:
         ws.apply(cls.dataTypeTemplate)
         package.createConstant(cls.__name__, cls.dataTypeTemplate.__name__, len(cls.dataTypeTemplate.valueTable)-1, adminData=adminData)
   return type(name, (autosar.Template,), dict(dataTypeTemplate=dataTypeTemplate, apply=apply))

def createConstantTemplateFromPhysicalType(name, dataTypeTemplate, adminData=None):
   @classmethod
   def apply(cls, ws):
      package = ws.getConstantPackage()
      if package.find(cls.__name__) is None:
         ws.apply(cls.dataTypeTemplate)
         package.createConstant(cls.__name__, cls.dataTypeTemplate.__name__, cls.dataTypeTemplate.maxValue, adminData=adminData)
   return type(name, (autosar.Template,), dict(dataTypeTemplate=dataTypeTemplate, apply=apply))

#PortInterfaces

def _createAddressMethod(ws, softwareAddressMethodRef):
   parts = autosar.base.splitRef(softwareAddressMethodRef)
   assert(len(parts)==2)
   (package_name, method_ref) = parts
   package = ws.find(package_name)
   if package is None:
      package = ws.createPackage(package_name)   
   if package.find(method_ref) is None:
      package.createSoftwareAddressMethod(method_ref)
   
   
def createSenderReceiverInterfaceTemplate(name, dataTypeTemplate, dataElementName = None):
   if dataElementName is None:
      dataElementName = name
   if dataElementName[-2:]=='_I':
      dataElementName=dataElementName[:-2]
      
   @classmethod
   def apply(cls, ws):
      package = ws.getPortInterfacePackage()
      if package.find(name) is None:
         ws.apply(cls.dataTypeTemplate)
         package.createSenderReceiverInterface(name, autosar.DataElement(cls.dataElementName, cls.dataTypeTemplate.__name__))
   return type(name, (autosar.Template,), dict(dataTypeTemplate=dataTypeTemplate, apply=apply, dataElementName=dataElementName))

def createParameterInterfaceTemplate(name, dataTypeTemplate, softwareAddressMethodRef=None, adminData = None):
     
   @classmethod
   def apply(cls, ws):
      if softwareAddressMethodRef is not None:
         _createAddressMethod(ws, softwareAddressMethodRef)
      package = ws.getPortInterfacePackage()
      if package.find(name) is None:
         ws.apply(cls.dataTypeTemplate)
         parameter=autosar.Parameter(cls.dataElementName, cls.dataTypeTemplate.__name__, swAddressMethodRef=softwareAddressMethodRef, adminData=adminData)
         package.createParameterInterface(name, parameter)
   return type(name, (autosar.Template,), dict(dataTypeTemplate=dataTypeTemplate, apply=apply, dataElementName='v'))

#Ports
def _createProvidePortHelper(swc, name, portInterfaceTemplate, initValueTemplate=None):
   ws = swc.rootWS()
   ws.apply(portInterfaceTemplate)
   if initValueTemplate is not None:
      ws.apply(initValueTemplate)
      swc.createProvidePort(name, portInterfaceTemplate.__name__, initValueRef=initValueTemplate.__name__)
   else:
      swc.createProvidePort(name, portInterfaceTemplate.__name__)

def _createRequirePortHelper(swc, name, portInterfaceTemplate, initValueTemplate=None, aliveTimeout=0):
   ws = swc.rootWS()
   ws.apply(portInterfaceTemplate)
   if initValueTemplate is not None:
      ws.apply(initValueTemplate)
      swc.createRequirePort(name, portInterfaceTemplate.__name__, initValueRef=initValueTemplate.__name__, aliveTimeout=aliveTimeout)
   else:
      swc.createRequirePort(name, portInterfaceTemplate.__name__, aliveTimeout=aliveTimeout)

def _createProvidePortTemplate(innerClassName, templateName, portInterfaceTemplate, initValueTemplate=None):
   @classmethod
   def apply(cls, swc):
      _createProvidePortHelper(swc, cls.name, cls.portInterfaceTemplate, cls.initValueTemplate)
   return type(innerClassName, (autosar.Template,), dict(name=templateName, portInterfaceTemplate=portInterfaceTemplate, initValueTemplate=initValueTemplate, apply=apply))

def _createRequirePortTemplate(innerClassName, templateName, portInterfaceTemplate, initValueTemplate=None, aliveTimeout=0):
   @classmethod
   def apply(cls, swc):
      _createRequirePortHelper(swc, cls.name, cls.portInterfaceTemplate, cls.initValueTemplate, cls.aliveTimeout)
   return type(innerClassName, (autosar.Template,), dict(name=templateName, portInterfaceTemplate=portInterfaceTemplate, initValueTemplate=initValueTemplate, aliveTimeout=aliveTimeout, apply=apply))
   

def createSenderReceiverPortTemplate(name, portInterfaceTemplate, initValueTemplate=None, aliveTimeout=0):
   return type(name, (), dict(Provide=_createProvidePortTemplate('Provide', name, portInterfaceTemplate, initValueTemplate),
                              Send=_createProvidePortTemplate('Send', name, portInterfaceTemplate, initValueTemplate),
                              Require=_createRequirePortTemplate('Require', name, portInterfaceTemplate, initValueTemplate, aliveTimeout),
                              Receive=_createRequirePortTemplate('Receive', name, portInterfaceTemplate, initValueTemplate, aliveTimeout)))

def createParameterPortTemplate(name, portInterfaceTemplate, initValueTemplate=None):
   return type(name, (), dict(Provide=_createProvidePortTemplate('Provide', name, portInterfaceTemplate, initValueTemplate),
                              Send=_createProvidePortTemplate('Send', name, portInterfaceTemplate, initValueTemplate),
                              Require=_createRequirePortTemplate('Require', name, portInterfaceTemplate, initValueTemplate),
                              Receive=_createRequirePortTemplate('Receive', name, portInterfaceTemplate, initValueTemplate)))

def createClientServerPortTemplate(name, portInterfaceTemplate):
   return type(name, (), dict(Call=_createRequirePortTemplate('Call', name, portInterfaceTemplate),
                              Require=_createRequirePortTemplate('Require', name, portInterfaceTemplate),
                              Serve=_createProvidePortTemplate('Serve', name, portInterfaceTemplate),                              
                              Provide=_createProvidePortTemplate('Provide', name, portInterfaceTemplate)))
