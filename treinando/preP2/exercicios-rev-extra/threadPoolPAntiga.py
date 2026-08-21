from random import randint
from concurrent.futures import ThreadPoolExecutor

futs = []

with ThreadPoolExecutor(max_workers=5) as executor:
    for i in range(50):
        futs.append(executor.submit(randint,0,100))
    
for i in range(50):
    try:
        result = futs[i].result()
    except Exception as exc:
        print("erro")
    else:
        print(result)


# b, d, c, g, 