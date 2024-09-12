# classroom_control_system

Compilar: gcc *.c -o student_management
Rodar: ./student_management

Sistema de controle de sala de aula

Um professor solicitou que você melhore o sistema utilizado para controlar a sala de aula na instituição, lidando com cálculo de notas e frequência.

Inicialmente, deseja-se armazenar informações a respeito de cada aluno, como matrı́cula (um valor inteiro), nome, curso e ano de entrada no curso. Além disso, cada aluno tem um conjunto de notas (de tamanho variável) e um conjunto de 18 aulas que pode estar presente ou ausente.

Para interagir com o sistema, serão necessárias as seguintes opções no menu:

• Cadastrar aluno: solicita os dados para o cadastro de um aluno e, se já existem avaliações no sistema, pede as notas contabilizadas. Se já existem chamadas realizadas no sistema, solicita também a presença do aluno em cada um dos dias.

• Cadastrar avaliação: recebe uma avaliação e o seu valor total. Em seguida, solicita a nota de cada aluno.

• Realiza chamada: contabiliza a frequência dos alunos em um determinado dia, perguntando quem está presente e ausente. Assim que um aluno atingir 10 faltas, deve imprimir um aviso dizendo que o mesmo foi reprovado por infrequência.

• Relatório de alunos: Imprime a lista de alunos informando a matrı́cula, nome, soma de todas as notas já registradas e o número de faltas. Além disso, antes de imprimir o relatório dá a opção de ordenar a lista por um destes campos.

• Relatório de notas: Imprime o relatório de notas de uma determinada avaliação informando a nota máxima, mı́nima e média. Após isso, imprime todas as notas em ordem decrescente sem indicar o nome dos alunos.

Para garantir que o sistema possa aumentar o número de alunos sem se preocupar com um espaço contı́guo na memória, o professor pediu para você armazenar os alunos de forma encadeada. Mas entendendo que isso pode tornar o acesso mais complicado, ele propôs a seguinte solução:

Considerando que as matrı́culas são números inteiros (aleatórios e não limitados) mas que temos no máximo 100 alunos na turma, crie uma tabela hash cujo ı́ndice seja uma função hash de sua escolha aplicada à matrı́cula e o valor armazenado seja o endereço do nó na lista encadeada. Sempre que um novo aluno for adicionado atualize essa tabela se atentando para a possibilidade de colisões.

Sugestão: utilize esse acesso direto à lista encadeada para realizar a ordenação. Ainda, ele solicitou que você teste alguns algoritmos de ordenação, um de complexidade quadrática e outra de complexidade n log(n) e avalie como isso influencia na geração dos relatórios.

Compilar: gcc *.c -o student_management
Rodar: ./student_management
