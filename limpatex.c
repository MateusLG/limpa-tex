#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <dirent.h>
#include <sys/stat.h>
#include <errno.h>
#include <ctype.h>

#define MAX_FILES 256

const char *known_extensions[] = {
    ".aux", ".log", ".bbl", ".blg", ".out", ".toc", 
    ".synctex.gz", ".fls", ".fdb_latexmk"
};
const int num_known_extensions = sizeof(known_extensions) / sizeof(known_extensions[0]);

int is_known_aux_file(const char *filename) {
    for (int i = 0; i < num_known_extensions; i++) {
        if (strstr(filename, known_extensions[i])) {
            return 1;
        }
    }
    return 0;
}

int ends_with(const char *str, const char *suffix) {
    if (!str || !suffix) return 0;
    size_t lenstr = strlen(str);
    size_t lensuffix = strlen(suffix);
    if (lensuffix > lenstr) return 0;
    return strncmp(str + lenstr - lensuffix, suffix, lensuffix) == 0;
}

int main() {
    DIR *d;
    struct dirent *dir_entry;

    char *files_known[MAX_FILES];
    char *files_unknown[MAX_FILES];
    int count_known = 0;
    int count_unknown = 0;

    // --- FASE 1: ANÁLISE E CATALOGAÇÃO ---
    d = opendir(".");
    if (d == NULL) {
        perror("Não foi possível abrir o diretório atual");
        return EXIT_FAILURE;
    }

    while ((dir_entry = readdir(d)) != NULL && (count_known + count_unknown) < MAX_FILES) {
        const char *name = dir_entry->d_name;

        // Pular diretórios, arquivos ocultos, o executável E O ARQUIVO .C
        if (dir_entry->d_type == DT_DIR || 
            name[0] == '.' || 
            strcmp(name, "limpatex") == 0 ||
            strcmp(name, "limpatex.c") == 0) { // <<< MUDANÇA AQUI
            continue;
        }

        if (ends_with(name, ".tex") || ends_with(name, ".pdf")) {
            continue;
        }

        if (is_known_aux_file(name)) {
            files_known[count_known++] = strdup(name);
        } else {
            files_unknown[count_unknown++] = strdup(name);
        }
    }
    closedir(d);

    // --- FASE 2: CONFIRMAÇÃO DO USUÁRIO ---
    if (count_known == 0 && count_unknown == 0) {
        printf("Nenhum arquivo para limpar.\n");
        return EXIT_SUCCESS;
    }

    printf("Os seguintes arquivos serão EXCLUÍDOS:\n");
    if (count_known > 0) {
        printf("----------------------------------------\n");
        printf("Arquivos auxiliares do LaTeX:\n");
        for (int i = 0; i < count_known; i++) {
            printf("  - %s\n", files_known[i]);
        }
    }
    if (count_unknown > 0) {
        printf("----------------------------------------\n");
        printf("!! ATENÇÃO: Arquivos DESCONHECIDOS !!\n");
        for (int i = 0; i < count_unknown; i++) {
            printf("  - %s\n", files_unknown[i]);
        }
    }
    printf("----------------------------------------\n");

    printf("Deseja continuar? (y/n): ");
    char choice = getchar();
    if (tolower(choice) != 'y') {
        printf("Operação cancelada pelo usuário.\n");
        for (int i = 0; i < count_known; i++) free(files_known[i]);
        for (int i = 0; i < count_unknown; i++) free(files_unknown[i]);
        return EXIT_SUCCESS;
    }

    // --- FASE 3: EXECUÇÃO DA LIMPEZA ---
    printf("\nIniciando limpeza...\n");

    for (int i = 0; i < count_known; i++) {
        if (remove(files_known[i]) == 0) printf("  [DELETADO] %s\n", files_known[i]);
        free(files_known[i]);
    }
    for (int i = 0; i < count_unknown; i++) {
        if (remove(files_unknown[i]) == 0) printf("  [DELETADO] %s\n", files_unknown[i]);
        free(files_unknown[i]);
    }
    
    const char *dest_dir_name = "Arquivos LaTeX";
    mkdir(dest_dir_name, 0755);

    printf("\nMovendo arquivos .tex...\n");
    d = opendir(".");
    if (d == NULL) {
        perror("Não foi possível reabrir o diretório");
        return EXIT_FAILURE;
    }
    while((dir_entry = readdir(d)) != NULL) {
        if (ends_with(dir_entry->d_name, ".tex")) {
            char new_path[512];
            snprintf(new_path, sizeof(new_path), "%s/%s", dest_dir_name, dir_entry->d_name);
            if (rename(dir_entry->d_name, new_path) == 0) {
                printf("  [MOVIDO] %s\n", dir_entry->d_name);
            }
        }
    }
    closedir(d);
    
    printf("\nLimpeza concluída!\n");
    return EXIT_SUCCESS;
}
