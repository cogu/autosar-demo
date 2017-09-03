#/usr/bin/env python3
import sys
import time
sys.path.append('..')
sys.path.append('../../common')
import autosar
start=time.time()
from BspService import BspService

ws = autosar.workspace()
ws.apply(BspService)
partition = autosar.rte.Partition()
for swc in ws.findall('/ComponentType/*'):
   partition.addComponent(swc)
typeGenerator = autosar.rte.TypeGenerator(partition)
typeGenerator.generate()
headerGenerator = autosar.rte.ComponentHeaderGenerator(partition)
headerGenerator.generate('.')
delta=float(time.time()-start)*1000
print('%dms'%(round(delta)))
