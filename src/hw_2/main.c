#include "avl-tree.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

Tree* loadFromFile(char* filename)
{
    FILE* file = fopen(filename, "r");
    if (file == NULL) {
        return NULL;
    }

    Tree* tree = createTree();
    if (tree == NULL) {
        fclose(file);
        return NULL;
    }

    char line[512];
    int loaded = 0;

    while (fgets(line, sizeof(line), file)) {
        line[strcspn(line, "\n")] = 0;
        if (strlen(line) == 0)
            continue;

        char* iata = strtok(line, ":");
        char* name = strtok(NULL, ":");

        if (iata && name) {
            TreeInsert(tree, iata, name);
            loaded++;
        }
    }

    fclose(file);
    printf("Загружено %d аэропортов. Система готова к работе.\n", loaded);
    return tree;
}

void saveRecursive(Node* node, FILE* file)
{
    if (node == NULL)
        return;
    saveRecursive(node->left, file);
    fprintf(file, "%s:%s\n", node->code, node->name);
    saveRecursive(node->right, file);
}

void saveToFile(Tree* tree, char* filename)
{
    if (tree == NULL)
        return;

    FILE* file = fopen(filename, "w");
    if (file == NULL) {
        return;
    }

    saveRecursive(tree->root, file);
    fclose(file);
    printf("База сохранена: %d аэропортов.\n", tree->size);
}

int main(int argc, char* argv[])
{
    if (argc != 2) {
        printf("Использование: %s <файл_с_аэропортами>\n", argv[0]);
        return 1;
    }

    Tree* tree = loadFromFile(argv[1]);
    if (tree == NULL) {
        return 1;
    }

    char buffer[512];

    while (1) {
        printf("> ");

        if (fgets(buffer, sizeof(buffer), stdin) == NULL) {
            printf("\n");
            break;
        }

        buffer[strcspn(buffer, "\n")] = 0;

        if (strlen(buffer) == 0) {
            continue;
        }

        char* cmd = strtok(buffer, " ");
        char* args = strtok(NULL, "");

        if (strcmp(cmd, "quit") == 0) {
            break;
        } else if (strcmp(cmd, "save") == 0) {
            saveToFile(tree, argv[1]);
        } else if (strcmp(cmd, "find") == 0) {
            if (args == NULL) {
                printf("Использование: find <код>\n");
                continue;
            }

            char* code = args;
            code[strcspn(code, " \n")] = 0;

            char* name = get_name(tree, code);
            if (name != NULL) {
                printf("%s → %s\n", code, name);
            } else {
                printf("Аэропорт с кодом '%s' не найден в базе.\n", code);
            }
        } else if (strcmp(cmd, "add") == 0) {
            if (args == NULL) {
                printf("Использование: add <код>:<название>\n");
                continue;
            }

            char* colon = strchr(args, ':');
            if (colon == NULL) {
                printf("Неверный формат. Используйте: add <код>:<название>\n");
                continue;
            }

            *colon = '\0';
            char* code = args;
            char* name = colon + 1;

            if (strlen(code) == 0 || strlen(name) == 0) {
                printf("Ошибка: код и название не могут быть пустыми\n");
                continue;
            }

            TreeInsert(tree, code, name);
            printf("Аэропорт '%s' добавлен в базу.\n", code);
        } else if (strcmp(cmd, "delete") == 0) {
            if (args == NULL) {
                printf("Использование: delete <код>\n");
                continue;
            }

            char* code = args;
            code[strcspn(code, " \n")] = 0;

            Node* existing = TreeFind(tree, code);
            if (existing == NULL) {
                printf("Аэропорт с кодом '%s' не найден в базе.\n", code);
                continue;
            }

            TreeDelete(tree, code);
            printf("Аэропорт '%s' удалён из базы.\n", code);
        } else {
            printf("Неизвестная команда: %s\n", cmd);
            printf("Доступные команды: find, add, delete, save, quit\n");
        }
    }

    TreeFree(tree);
    return 0;
}