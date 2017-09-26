#/usr/bin/env python3
import sys, os
import time
sys.path.insert(0,'../../lib')
for swc in ['BspService', 'common', 'FreeRunningTimer']:
   sys.path.append(os.path.abspath(os.path.join(os.path.dirname(__file__), '../'+swc)))
import autosar
import apx
start=time.time()
from RealTimeClock import RealTimeClock
from BspService import BspService


if __name__ == '__main__':
   derived_dir = 'derived'
   if not os.path.exists(derived_dir):
      os.makedirs(derived_dir)   
   ws = autosar.workspace()
   ws.apply(RealTimeClock)
   #ws.apply(BspService)
   partition = autosar.rte.Partition()
   partition.addComponent(ws.find('/ComponentType/RealTimeClock'))
   #partition.addComponent(ws.find('/ComponentType/BspService'))
   typeGenerator = autosar.rte.TypeGenerator(partition)
   typeGenerator.generate(derived_dir)
   headerGenerator = autosar.rte.ComponentHeaderGenerator(partition)
   headerGenerator.generate(derived_dir)
   apx_node = apx.Node().import_autosar_swc(ws.find('/ComponentType/RealTimeClock'))
   apx_context = apx.Context()
   apx_context.append(apx_node)
   apx_context.generateAPX('derived')
   delta=float(time.time()-start)*1000
   print('%dms'%(round(delta)))

