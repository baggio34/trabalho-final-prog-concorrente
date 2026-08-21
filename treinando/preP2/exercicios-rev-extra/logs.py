from multiprocessing import Process, Queue
import time

NUM_WORKERS = 3

def coletor(fila_tarefas):
    logs = ["ERRO: db timeout", "INFO: login user_42", "AVISO: disco 80%", "ERRO: auth falhou"] * 5
    for log in logs:
        # TODO: Envie o log para a fila de tarefas
        fila_tarefas.put(log)
        print(f"[Coletor] Log capturado: {log}")
        time.sleep(0.1)
    
    # TODO: Envie "sinais de parada" (poison pills) para os analisadores encerrarem
    for _ in range(NUM_WORKERS):
        fila_tarefas.put(None)

        
def analisador(id_worker, fila_tarefas):
    while True:
        # TODO: Receba o log da fila. Se for o sinal de parada, quebre o laço (break).
        log = fila_tarefas.get()

        if log is None:     # poison pill
            print(f"[Analisador {id_worker}] Encerrando")
            break
        
        print(f"[Analisador {id_worker}] Processando: {log}")
        time.sleep(0.3) # Simula o custo de processamento

if __name__ == '__main__':
    # TODO: Crie a Queue de tarefas
    queue = Queue()
    # TODO: Instancie e inicie o processo Coletor
    colector = Process(target=coletor, args=(queue,))
    
    analizer1 = Process(target=analisador, args=(1, queue))
    analizer2 = Process(target=analisador, args=(2, queue))
    analizer3 = Process(target=analisador, args=(3, queue))

    #  iniciar TODOS
    colector.start()
    analizer1.start()
    analizer2.start()
    analizer3.start()

    # esperar primeiro o coletor terminar de produzir
    colector.join()

    # depois esperar os workers
    analizer1.join()
    analizer2.join()
    analizer3.join()

    print("Processamento de logs finalizado.")