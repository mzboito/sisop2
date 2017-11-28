# T2FS - Sistema de Arquivos  
Repositório para armazenar os arquivos do trabalho 2 (Sistema de Arquivos T2FS) de sistemas operacionais. Alunas: Lisiane Aguiar e Marcely Zanon Boito.

** ESCOLHAS DE IMPLEMENTAÇÃO **

* read2: Um read2 apois um seek2(handle, -1) retornará -1.
* opendir2: Como não foi definido um número máximo de arquivos no enunciado, utilizamos o mesmo que para arquivos: 10.
* chdir2 e getcwd2: se o usuário fizer um chdir2 com um path relativo (por exemplo: ../../dir/dir2/./dir3/), o getcwd2 retornará a exata mesma string (não fazemos uma conversão para a string de caminho absoluto, mas o caminhamento de diretórios funciona perfeitamente).
* opendir2 e readdir2: na abertura do diretório com opendir2, uma estrutura é alocada em memória contendo as entradas do diretório, por causa disso, se após abrir um diretório o usuário atualizar arquivos (delete2, write2, create2), essas informações não aparecerão na readdir2. Para acessá-las, é necessário abrir o diretório novamente, para a informação ser recuperada do disco.
read2 e write2: estou devolvendo -1 no caso do tamanho do buffer enviado ser menor que o size informado.
