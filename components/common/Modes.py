import autosar

class EcuM_ModeDeclaration(autosar.Template):
   @classmethod
   def apply(cls, ws):
      package = ws.getModeDclrGroupPackage()
      if package.find(cls.__name__) is None:
         package.createModeDeclarationGroup("EcuM_Mode", ["POST_RUN", "RUN", "SHUTDOWN", "SLEEP", "STARTUP", "WAKE_SLEEP"], "STARTUP")

class EcuM_CurrentMode:

   class Require(autosar.Template):
      @classmethod
      def apply(cls, swc):
         ws = swc.rootWS()
         package = ws.getPortInterfacePackage()
         if package.find(cls.__name__) is None:
            ws.apply(EcuM_ModeDeclaration)
            package.createSenderReceiverInterface("EcuM_CurrentMode", modeGroups=autosar.ModeGroup("currentMode", "/ModeDclrGroup/EcuM_Mode"), isService=True)
         swc.createRequirePort('EcuM_CurrentMode', 'EcuM_CurrentMode')

   class Provide(autosar.Template):
      @classmethod
      def apply(cls, swc):
         ws = swc.rootWS()
         package = ws.getPortInterfacePackage()
         if package.find(cls.__name__) is None:
            ws.apply(EcuM_ModeDeclaration)
            package.createSenderReceiverInterface("EcuM_CurrentMode", modeGroups=autosar.ModeGroup("currentMode", "/ModeDclrGroup/EcuM_Mode"), isService=True, adminData={"SDG_GID": "edve:BSWM", "SD": "EcuM"})
         swc.createProvidePort('EcuM_CurrentMode', 'EcuM_CurrentMode')
