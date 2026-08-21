from time import sleep
from math import ceil
from threading import Thread, Lock, Condition

def produz_rodas(num_rodas):
    global caixa
    for i in range(num_rodas):
        with lock:
            while len(caixa) == tam_caixa:
                caixa_cheia.wait()
            sleep(1)
            roda = 'roda' + str(i)
            caixa.append(roda)
            print('Roda armazenada. Há %i roda(s) na caixa' % len(caixa))

            if len(caixa) == tam_caixa:
                caixa_vazia.notify()


def troca_caixa(num_caixas):
    global caixa
    for i in range(num_caixas):
        with lock:
            while len(caixa) < tam_caixa:
                caixa_vazia.wait()
                    
            caixa.clear()
            sleep(2)
            print('Caixa trocada')

            caixa_cheia.notify_all()

caixa = []
tam_caixa = 5
quant_rodas = 50
quant_caixas = ceil(quant_rodas / tam_caixa)
lock = Lock()
caixa_vazia = Condition(lock)
caixa_cheia = Condition(lock)
t1 = Thread(target = produz_rodas, args = (quant_rodas, ))
t2 = Thread(target = troca_caixa, args = (quant_caixas, ))
t1.start()
t2.start()
t1.join()
t2.join()