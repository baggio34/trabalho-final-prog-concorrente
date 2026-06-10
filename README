# trabalho-final-prog-concorrente
Esse repositório contém o desenvolvimento do trabalho final da disciplina de programação concorrente, o qual se trata sobre um problema de concorrência chamado Banquete Viking


<img width="370" height="356" alt="image" src="https://github.com/user-attachments/assets/20c17b6b-375a-4d39-9a9f-eaa061db22a7" />


# Banquete Viking

Uma horda viking se prepara para pilhar uma vila de inocentes cristãos na Inglaterra. A pilhagem de vilas é uma atividade que exige guerreiros bem alimentados e devidamente embriagados. Logo, é realizado um banquete antes dos guerreiros embarcarem em seus langskips.

---

## Banquete

O banquete ocorre em uma gigantesca mesa circular construída ao redor de uma churrasqueira.

Cada viking se comporta da seguinte forma:

* Senta na mesa
* Pega dois pratos de comida
* Come
* Se levanta e aguarda o fim do banquete em pé no open bar de hidromel

Apesar da destruição costumeiramente imposta sobre os vilarejos pilhados, os vikings devem obedecer algumas regras sobre o banquete:

* Apenas um viking deve sentar em uma cadeira. Nessa época não era bem visto dois vikings em uma única cadeira.
* Há dois tipos de guerreiros vikings: berserkers e guerreiros normais. Por motivos de segurança, um guerreiro normal não deve sentar ao lado de um berserker e vice-versa. O espaço de uma cadeira vazia é suficiente para evitar incidentes. Da mesma forma, o vão da mesa (berserker-safe, na figura acima) também é suficiente para evitar acidentes.
* O viking precisa pegar dois pratos antes de começar a comer. O viking pode escolher entre três possibilidades:

  * O prato alinhado com sua cadeira
  * O prato alinhado com a cadeira à sua esquerda (pode atravessar o vão)
  * O prato alinhado com a cadeira à sua direita (pode atravessar o vão)

Essas regras são garantidas pelo chieftain, o líder da horda viking. As ações de se sentar e pegar os pratos correspondem à função `chieftain_acquire_seat_plates(...)` que deve ser implementada. Após comer, o viking avisa que levantou e liberou os pratos chamando a função `chieftain_release_seat_plates(...)`, que também deve ser implementada.

A produção de comida (assim como sua colocação nos pratos) e o open bar do mais fabuloso e entorpecente hidromel não precisam ser modelados. No entanto, os vikings que participam do banquete precisam esperar que os demais participantes do banquete terminem de comer antes de iniciarem suas preces.

---

## Preces

Após o término do banquete, cada viking deve fazer suas preces a um deus viking. No entanto há algumas desavenças entre os deuses:

* Baldr vs. Loki
* Vali vs. Hoder
* Frigg vs. Jord

Caso um desses deuses receba mais preces do que seu desafeto, e essa diferença exceder 5% das preces recebidas pelo primeiro deus, ele pode enfurecer-se e ajudar os cristãos durante a pilhagem. Para computar a tolerância em número de preces deve-se considerar o arredondamento para cima. Por exemplo, se Baldr recebeu 23 preces, Loki pode receber até 25 preces sem causar problemas.

Além desses deuses, há dois deuses que possuem bom trânsito entre seus pares: Thor e Odin. Cada um desses deuses pode receber até 10% mais preces do que a soma das preces destinadas aos 6 deuses listados anteriormente. Novamente, a tolerância em número de preces deve ser computada arredondando para cima.

Para garantir o sucesso da pilhagem, cada viking consulta o chieftain para saber para qual deus deve rezar. Essa consulta ocorre através da função `chieftain_get_god(...)`, que deve ser implementada. De modo a não levantar suspeitas de manipulação, o chieftain deve atribuir deuses aleatoriamente com auxílio da função `rand()`, mas respeitando as regras acima.

Assim como o banquete, as preces devem ocorrer com rapidez. O chieftain não pode demorar muito tempo para atribuir o deus de cada guerreiro. Por fim, lembre-se que é falta de educação um participante do banquete começar a rezar antes dos outros participantes terminarem de comer.

---

## Gênese Viking

Devido ao consumo de entorpecentes e ausência de sistemas informatizados para o censo, o chieftain não sabe exatamente quantos vikings fazem parte da horda. Ele possui uma estimativa, que é informada através da opção de linha de comando `-v`, que indica a quantidade de vikings que iniciarão a execução e participarão do banquete e das preces. Como explicado anteriormente, o banquete se encerra após esse número de vikings comer. No entanto, vikings adicionais podem surgir apenas na etapa das preces.

Cada viking é representado individualmente por uma thread e as threads devem ser criadas necessariamente através da função `horde_spawn_viking(...)`, que deve ser implementada. O parâmetro `type` desta função define se o viking participa do banquete e preces (`NORMAL_VIKING`) ou somente das preces (`LATE_VIKING`). O parâmetro `berserker` indica se o viking é um berserker, como explicado na seção dedicada ao banquete. Todos os vikings criados por essa função devem executar concorrentemente.

A função `horde_join(...)` deve aguardar até que todos os vikings criados (atrasados ou não) tenham terminado suas preces antes de terminar a execução do programa.

---

## Quais Funções Implementar?

As principais funções a serem implementadas possuem comentários no código base fornecido. Além delas, você deverá incluir outros atributos que você achar necessários nas structs que definem o chieftain (`chieftain_t`), a horda (`horde_t`), os deuses (`valhalla_t`) e os vikings (`viking_t`). Essas structs simulam os atributos de uma classe no modelo de programação orientado a objetos e devem ser inicializadas na função `*_init(...)` correspondente. No caso de alocação dinâmica de dados, lembre-se de desalocar os dados na função `*_finalize(...)` correspondente.

Evite sempre que possível criar variáveis globais no seu programa e insira as variáveis necessárias nas structs para implementar os comportamentos definidos nas seções anteriores. É importante ressaltar que você poderá também incluir novas funções na sua solução: faça isso para tornar a sua solução mais elegante e legível.

**AVISO IMPORTANTE 1:** Não será permitido alterar o arquivo `main.c`. Outras funções que também não devem ser alteradas estão indicadas no próprio código.

**AVISO IMPORTANTE 2:** Para cada função adicionada, é necessário incluir a sua assinatura como `extern` no header (`.h`) e a sua implementação no arquivo `.c` correspondente.

---

## Compilação e Execução

Para compilar o projeto, execute:

```bash
make
```

Para limpar completamente o projeto, execute:

```bash
make clean
```

O esqueleto inicial já está escrito para aceitar alguns argumentos. Para testar um cenário de uma horda de 2000 vikings (contabilizados) e uma mesa com 16 lugares, execute:

```bash
./program -v 2000 -c 16
```

Não haverá avaliação por tempo de duração do banquete. No entanto, é importante fazer um uso eficiente dos recursos. Deve-se evitar manter locks adquiridos por muito tempo, ou permitir que cadeiras ou pratos permaneçam inutilizáveis por muito tempo.

**DICA:** Configure a opção `RELEASE` no Makefile principal para adicionar informações de debug na saída do programa. Por padrão, as informações de debug estão desabilitadas (`RELEASE` com valor `true`). Para habilitá-las, faça:

```bash
export RELEASE ?= false
```

Com `RELEASE` em `false` serão impressas informações da execução do programa e o programa será compilado com a opção de debug para o `gdb` (flag `-g`). As informações impressas são geradas através de chamadas à função `plog(...)` no código. Você também poderá utilizar a função `plog(...)` para imprimir outras informações de debug, se desejar.

Para gerar um arquivo compactado da sua solução final, execute:

```bash
make submission
```

Após a execução deste comando, um arquivo compactado denominado `solution.tar.gz` será criado no diretório principal e deverá ser submetido via Moodle até o prazo final de entrega.

---

## Grupos e Prazo de Entrega

O trabalho deverá ser realizado em grupos de 3 alunos. A seleção de grupos deverá ser feita com uso da ferramenta disponível no Moodle. Não serão aceitas entregas fora do Moodle e nem fora do prazo. É obrigatório estar em um grupo para poder realizar a entrega (organize-se com antecedência).

Prazo para definição dos grupos (3 membros por grupo): 28/06/2026 às 23h59 através desta ferramenta.

Prazo de entrega (somente via Moodle): 01/07/2026 às 23h59.

---

