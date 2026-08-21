from multiprocessing import Process, Queue

def gerador(fila):
    for i in range(-5, 6): # Gera dados de -5 a 5
        fila.put(i)
    fila.put(None) # Sinal de fim

def filtro(fila_in, fila_out):
    while True:
        item = fila_in.get()
        if item is None:
            fila_out.put(None)
            break
        if item >= 0: # Filtra apenas positivos
            fila_out.put(item)

def analista(fila_in):
    # TODO: Calcule a média dos números recebidos
    acc = 0
    counter = 0

    while True:
        msg = fila_in.get()

        if msg is None:
            break

        acc += msg
        counter += 1

    if counter > 0:
        media = acc/counter
        print(media)
    else:
        print("T-T")


# TODO: Monte o fluxo: Gerador -> FilaA -> Filtro -> FilaB -> Analista

filaA = Queue()
filaB = Queue()

geradorProcess = Process(target=gerador, args=(filaA,))
filtroProcess = Process(target=filtro, args=(filaA, filaB))
analistaProcess = Process(target=analista, args=(filaB,))

geradorProcess.start()
filtroProcess.start()
analistaProcess.start()

geradorProcess.join()
filtroProcess.join()
analistaProcess.join()
