import os, sys
for comp in ['common', 'BspService', 'FreeRunningTimer', 'SteeringWheelButtonFeedback']:
   sys.path.append(os.path.abspath(os.path.join(os.path.dirname(__file__), comp)))
