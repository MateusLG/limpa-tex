#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <dirent.h>
#include <sys/stat.h>
#include <errno.h>

int ends_with(const char *str, const char *suffix) {
    if (!str || !suffix) {
        return 0;
    }
    size_t lenstr = strlen(str);
    size_t lensuffix = strlen(suffix);
    if (lensuffix > lenstr) {
        return 0;
    }
    return strncmp(str + lenstr - lensuffix, suffix, lensuffix) == 0;
}

int main() {
    const char *dest_dir_name = "Arquivos LaTeX";
    DIR *d;
    struct dirent *dir_entry;

    // --- PRIMEIRA PASSAGEM: DELETAR ARQUIVOS AUXILIARES ---
    printf("Procurando arquivos para limpar...\n");

    d = opendir(".");
    if (d == NULL) {
        perror("Não foi possível abrir o diretório atual");
        return EXIT_FAILURE;
    }

    while ((dir_entry = readdir(d)) != NULL) {
        if (dir_entry->d_name[0] == '.') {
            continue;
        }

        if (dir_entry->d_type == DT_DIR) {
            continue;
        }

        // Verifica se o arquivo NÃO é .tex, NÃO é .pdf E NÃO é o próprio executável
        if (!ends_with(dir_entry->d_name, ".tex") && 
            !ends_with(dir_entry->d_name, ".pdf") &&
            strcmp(dir_entry->d_name, "limpatex") != 0) { // <<< MUDANÇA AQUI
            
            if (remove(dir_entry->d_name) == 0) {
                printf("  [DELETADO] %s\n", dir_entry->d_name);
            } else {
                fprintf(stderr, "  [ERRO] Não foi possível deletar %s\n", dir_entry->d_name);
            }
        }
    }
    closedir(d);

    // --- SEGUNDA PASSAGEM: MOVER ARQUIVOS .TEX ---
    // (O restante do código permanece exatamente o mesmo)

    if (mkdir(dest_dir_name, 0755) == 0) {
        printf("\nDiretório '%s' criado.\n", dest_dir_name);
    } else if (errno != EEXIST) {
        perror("Não foi possível criar o diretório de destino");
        return EXIT_FAILURE;
    }

    printf("\nMovendo arquivos .tex...\n");

    d = opendir(".");
    if (d == NULL) {
        perror("Não foi possível reabrir o diretório atual");
        return EXIT_FAILURE;
    }

    while ((dir_entry = readdir(d)) != NULL) {
        if (ends_with(dir_entry->d_name, ".tex")) {
            char old_path[512];
            char new_path[512];
            snprintf(old_path, sizeof(old_path), "%s", dir_entry->d_name);
            snprintf(new_path, sizeof(new_path), "%s/%s", dest_dir_name, dir_entry->d_name);

            if (rename(old_path, new_path) == 0) {
                printf("  [MOVIDO] %s -> %s/\n", old_path, dest_dir_name);
            } else {
                fprintf(stderr, "  [ERRO] Não foi possível mover %s\n", old_path);
            }
        }
    }
    closedir(d);

    printf("\nLimpeza concluída!\n");

    return EXIT_SUCCESS;
}
