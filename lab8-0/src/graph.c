#include "constants.h"
#include "graph.h"
#include "kruskal_info.h"

#include <limits.h>
#include <stdio.h>
#include <stdlib.h>

static int create_graph(graph_t **self, const int edge_num) {
    *self = malloc(sizeof(graph_t));
    if (!*self) {
        return other_error;
    }
    (*self)->graph = malloc(sizeof(int) * edge_num * 3);
    if (!(*self)->graph) {
        return other_error;
    }
    return no_error;
}

static int compare_edge_weights(const void *a, const void *b){
    const int *edge_a = a;
    const int *edge_b = b;
    return edge_a[2] - edge_b[2];
}

int fill_graph(graph_t **self, const char *in_stream) {
    int ver_num;
    FILE *fp = fopen(in_stream, "r");
    if (!fp) {
        return other_error;
    }
    if (fscanf(fp, "%d", &ver_num) != 1) {
        fclose(fp);
        return bad_number_of_lines;
    }
    if (ver_num < 0 || ver_num > MAX_VERTICES_COUNT) {
        fclose(fp);
        return bad_number_of_vertices;
    }
    int edge_num;
    if (fscanf(fp, "%d", &edge_num) != 1) {
        fclose(fp);
        return bad_number_of_lines;
    }
    if (edge_num < 0 || edge_num > ver_num * (ver_num - 1) / 2) {
        fclose(fp);
        return bad_number_of_edges;
    }
    if (edge_num == 0 && ver_num != 1) {
        fclose(fp);
        return no_spanning_tree;
    }
    if (edge_num == 0 && ver_num == 1) {
        fclose(fp);
        return other_error;
    }
    if (create_graph(self, edge_num) != no_error) {
        fclose(fp);
        return other_error;
    }
    (*self)->ver_num = ver_num;
    (*self)->edge_num = edge_num;

    int from, to, value;
    for (int i = 0; i < edge_num; ++i) {
        if (fscanf(fp, "%d %d %d", &from, &to, &value) != 3) {
            fclose(fp);
            return bad_number_of_lines;
        }
        if (from < 0 || to < 0 || from > ver_num || to > ver_num) {
            fclose(fp);
            return bad_vertex;
        }
        if (value < 0 || value > INT_MAX) {
            fclose(fp);
            return bad_length;
        }
        (*self)->graph[3 * i + 0] = from;
        (*self)->graph[3 * i + 1] = to;
        (*self)->graph[3 * i + 2] = value;
    }
    fclose(fp);
    return no_error;
}

int print_error(error_code error, const char *out_stream) {
    FILE *fp = fopen(out_stream, "w");
    if (!fp)
        return other_error;
    if (error == bad_number_of_lines) {
        fprintf(fp, "bad number of lines");
    }
    if (error == bad_number_of_vertices) {
        fprintf(fp, "bad number of vertices");
    }
    if (error == bad_number_of_edges) {
        fprintf(fp, "bad number of edges");
    }
    if (error == bad_vertex) {
        fprintf(fp, "bad vertex");
    }
    if (error == impossible_to_sort) {
        fprintf(fp, "impossible to sort");
    }
    if (error == bad_length) {
        fprintf(fp, "bad length");
    }
    if (error == no_spanning_tree) {
        fprintf(fp, "no spanning tree");
    }
    fclose(fp);
    return no_error;
}

static int find_set(int *parent, int i) {
    if (parent[i] == i)
        return i;
    return parent[i] = find_set(parent, parent[i]);
}

int kruskal(graph_t **self) {
    kruskal_info *k_info = NULL;
    if (create_kruskal_info(&k_info, (*self)->ver_num) != no_error) {
        destroy_kruskal_info(&k_info);
        return other_error;
    }
    qsort((*self)->graph, (*self)->edge_num, sizeof(int) * 3, compare_edge_weights);
    for (int i = 0; i < (*self)->edge_num; i++) {
        int a = (*self)->graph[3 * i + 0];
        int b = (*self)->graph[3 * i + 1];
        int from_set = find_set(k_info->parent, a - 1);
        int to_set = find_set(k_info->parent, b - 1);
        if (from_set != to_set) {
            k_info->vert[a - 1] = 1;
            k_info->vert[b - 1] = 1;
            if (k_info->rank[from_set] < k_info->rank[to_set]) {
                int tmp = from_set;
                from_set = to_set;
                to_set = tmp;
            }
            k_info->parent[to_set] = from_set;
            if (k_info->rank[from_set] == k_info->rank[to_set])
                ++(k_info->rank)[from_set];
        }
        else
            (*self)->graph[3 * i + 2] = -1;
    }
    for (int i = 0; i < (*self)->ver_num; i++)
        if (!k_info->vert[i]) {
            destroy_kruskal_info(&k_info);
            return no_spanning_tree;
        }
    destroy_kruskal_info(&k_info);
    return no_error;
}

int print_spanning_tree(graph_t **self, error_code error, const char *out_stream) {
    if (error != no_error) {
        error = print_error(error, out_stream);
        return error;
    }
    FILE *fp = fopen(out_stream, "w");
    if (!fp) {
        return other_error;
    }
    for (int i = 0; i < (*self)->edge_num; i++)
        if ((*self)->graph[i * 3 + 2] != -1)
            fprintf(fp, "%d %d\n", (*self)->graph[i * 3 + 0], (*self)->graph[i * 3 + 1]);
    fclose(fp);
    return no_error;
}

void destroy_graph(graph_t **self) {
    if (*self) {
        free((*self)->graph);
    }
    free(*self);
}
