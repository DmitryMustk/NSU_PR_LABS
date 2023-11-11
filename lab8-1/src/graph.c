#include "graph.h"
#include "constants.h"
#include "prim_info.h"

#include <limits.h>
#include <stdio.h>
#include <stdlib.h>

#define MAX_VERTICES_COUNT 5000

static int create_graph(graph_t** self, const int ver_num) {
    *self = malloc(sizeof(graph_t));
    if (!*self) {
        return other_error;
    }
    (*self)->ver_num = ver_num;
    (*self)->weights = malloc(sizeof(unsigned int) * ver_num * ver_num);
    if (!(*self)->weights) {
        return other_error;
    }
    return no_error;
}

int fill_graph(graph_t** self, const char* in_stream) {
    int ver_num;
    FILE* fp = fopen(in_stream, "r");
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
    if (edge_num < 0 || edge_num > (ver_num + 1) * ver_num / 2) {
        fclose(fp);
        return bad_number_of_edges;
    }
    if (edge_num == 0 && ver_num != 1) {
        fclose(fp);
        return no_spanning_tree;
    }
    if (create_graph(self, ver_num) != no_error) {
        fclose(fp);
        return other_error;
    }
    (*self)->edge_num = edge_num;

    for (int i = 0; i < (*self)->ver_num * (*self)->ver_num; ++i)
        (*self)->weights[i] = UINT_MAX;
    for (int i = 0; i < edge_num; ++i) {
        int a, b, weight;
        if (fscanf(fp, "%d %d %d", &a, &b, &weight) != 3) {
            fclose(fp);
            return bad_number_of_lines;
        }
        if (a < 1 || b < 1 || a > ver_num || b > ver_num) {
            fclose(fp);
            return bad_vertex;
        }
        if (weight <= 0 || weight > INT_MAX) {
            fclose(fp);
            return bad_length;
        }
        (*self)->weights[(*self)->ver_num * (a - 1) + (b - 1)] = weight;
        (*self)->weights[(*self)->ver_num * (b - 1) + (a - 1)] = weight;
    }
    fclose(fp);
    return no_error;
}

int prim(graph_t** self, const char* out_stream) {
    FILE* fp = fopen(out_stream, "w");
    if(!fp){
        return other_error;
    }
    prim_info* p_inf = NULL;
    create_prim_info(&p_inf, (*self)->ver_num);
    if(!p_inf) {
        fclose(fp);
        return other_error;
    }
    for (int i = 0; i < (*self)->ver_num; i++) {
        p_inf->used[i] = 0;
        p_inf->min_e[i] = UINT_MAX;
        p_inf->sel_e[i] = -1;
    }
    p_inf->min_e[0] = 0;
    for (int i = 0; i < (*self)->ver_num; i++) {
        int v = -1;
        for (int j = 0; j < (*self)->ver_num; j++)
            if (!p_inf->used[j] && (v == -1 || p_inf->min_e[j] < p_inf->min_e[v]))
                v = j;
        if (p_inf->min_e[v] == UINT_MAX) {
            fclose(fp);
            fp = fopen("out.txt", "w");
            if (!fp) {
                return other_error;
            }
            fprintf(fp, "no spanning tree\n");
            destroy_prim_info(&p_inf);
            fclose(fp);
            return no_spanning_tree;
        }
        p_inf->used[v] = 1;
        if (p_inf->sel_e[v] != -1)
            fprintf(fp, "%d %d\n", v + 1, p_inf->sel_e[v] + 1);
        for (int to = 0; to < (*self)->ver_num; to++)
            if ((*self)->weights[(*self)->ver_num * v + to] < p_inf->min_e[to]) {
                p_inf->min_e[to] = (*self)->weights[(*self)->ver_num * v + to];
                p_inf->sel_e[to] = v;
            }
    }
    destroy_prim_info(&p_inf);
    fclose(fp);
    return no_error;
}


int print_error(error_code error, const char* out_stream) {
    FILE* fp = fopen(out_stream, "w");
    if (!fp)
        return other_error;
    if (error == other_error) {
        fprintf(fp, "other error");
    }
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

void destroy_graph(graph_t** self) {
    if (*self) {
        free((*self)->weights);
    }
    free(*self);
}
