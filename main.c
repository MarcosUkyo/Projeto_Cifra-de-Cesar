#include <stdio.h>
#include <string.h>
#include <ctype.h> // Necessário para as funções isalpha(), islower() e isupper()

#define MAX 256        // Tamanho máximo dos vetores
#define MAX_LETRAS 15  // Limite de letras da palavra secreta (enunciado)

int main() {
    // Declaração dos vetores de caracteres
    char texto_original[MAX];
    char texto_camada1[MAX];
    char texto_cifrado[MAX];

    int chave, i, tamanho;
    int fib_a = 1, fib_b = 1, proximo, deslocamento;

    // 1. Receber a palavra secreta
    printf("Digite a palavra secreta (ate %d letras, sem acentos): ", MAX_LETRAS);
    fgets(texto_original, MAX, stdin);
    texto_original[strcspn(texto_original, "\n")] = '\0'; // remove o '\n' do fgets

    // Validação: de 1 a 15 letras, sem acentos, números ou caracteres especiais
    tamanho = strlen(texto_original);
    if (tamanho == 0 || tamanho > MAX_LETRAS) {
        printf("Erro: a palavra deve ter de 1 a %d letras.\n", MAX_LETRAS);
        return 1;
    }
    for (i = 0; i < tamanho; i++) {
        if (!isalpha((unsigned char)texto_original[i])) {
            printf("Erro: use apenas letras, sem acentos, espacos ou caracteres especiais.\n");
            return 1;
        }
    }

    printf("Digite o SHIFT (numero de saltos): ");
    scanf("%d", &chave);

    // Ajusta a chave para ficar entre 0 e 25 (também trata valores negativos)
    chave = ((chave % 26) + 26) % 26;

    // 2. CAMADA 1: Cifra de César (SHIFT fixo)
    for (i = 0; i < tamanho; i++) {
        char caractere_atual = texto_original[i];

        // Define a base dependendo se a letra é minúscula ('a') ou maiúscula ('A')
        char base = islower(caractere_atual) ? 'a' : 'A';

        texto_camada1[i] = ((caractere_atual - base + chave) % 26) + base;
    }
    texto_camada1[tamanho] = '\0';

    // 3. CAMADA 2: deslocamento dinâmico pela sequência (Fibonacci: 1, 1, 2, 3, 5, 8, 13...)
    for (i = 0; i < tamanho; i++) {
        char caractere_atual = texto_camada1[i];
        char base = islower(caractere_atual) ? 'a' : 'A';

        deslocamento = fib_a % 26; // termo atual da sequência

        texto_cifrado[i] = ((caractere_atual - base + deslocamento) % 26) + base;

        // Avança a sequência (mod 26 evita estouro de int)
        proximo = (fib_a + fib_b) % 26;
        fib_a = fib_b;
        fib_b = proximo;
    }
    texto_cifrado[tamanho] = '\0';

    // 4. Exibir o resultado
    printf("\n--- RESULTADO ---\n");
    printf("Vetor Original : %s\n", texto_original);
    printf("Apos Camada 1  : %s\n", texto_camada1);
    printf("Vetor Cifrado  : %s\n", texto_cifrado);

    // 5. Gravar o resultado em arquivo (formato do enunciado)
    FILE *arquivo = fopen("resultado_criptografia.txt", "w");
    if (arquivo == NULL) {
        printf("Erro ao criar o arquivo de resultado.\n");
        return 1;
    }
    fprintf(arquivo, "Palavra codificada: %s | SHIFT: %d | Tipo: Fibonacci | Letras: %d\n",
            texto_cifrado, chave, tamanho);
    fclose(arquivo);

    printf("\nArquivo 'resultado_criptografia.txt' gerado com sucesso.\n");

    return 0;
}