from time import sleep
from random import randint
from threading import Thread, Semaphore

def produtor():
  global buffer
  for i in range(10):
    
    sleep(randint(0,2))           
    item = 'item ' + str(i)

    vagas.acquire()
    with mutex:
      buffer.append(item)
      print('Produzido %s (ha %i itens no buffer)' % (item,len(buffer)))
    itens.release()


def consumidor():
  global buffer
  for i in range(10):

    itens.acquire()
     
    with mutex:
      item = buffer.pop(0) 
      print('Consumido %s (ha %i itens no buffer)' % (item,len(buffer)))
      
    vagas.release()
    sleep(randint(0,2))         
    


buffer = []
tam_buffer = 3

mutex = Semaphore(1)
vagas = Semaphore(tam_buffer)
itens = Semaphore(0)


prod = Thread(target=produtor) 
cons = Thread(target=consumidor) 
prod.start()
cons.start()
prod.join()
cons.join()