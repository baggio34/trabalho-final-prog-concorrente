import threading
import time

# Variável compartilhada
contador = 0
# TODO: Crie um objeto Lock aqui
lock = threading.Lock() 

def incrementar(nome_thread, repeticoes):
    global contador
    for _ in range(repeticoes):
        # TODO: Adquira o lock antes de modificar a variável
        
        # Região Crítica: alteração da variável compartilhada
        # poderia criar um lock = Lock() e fazer lock.acquire() e lock.release()
        with lock:
            temp = contador
            time.sleep(0.0001) # Simula um pequeno atraso para forçar o erro
            contador = temp + 1
        
        # TODO: Libere o lock depois de modificar
        
    print(f"Thread {nome_thread} finalizada.")

# Configuração
n_threads = 2
repeticoes = 1000

threads = []
# Criação e inicialização das threads
for i in range(n_threads):
    t = threading.Thread(target=incrementar, args=(i, repeticoes))
    threads.append(t)
    t.start()

# Aguarda todas as threads terminarem
for t in threads:
    t.join()

print(f"Valor final do contador: {contador} (Esperado: {n_threads * repeticoes})")