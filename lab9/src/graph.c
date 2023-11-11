#include "graph.h"
#include "constants.h"
#include "dijkstra_info.h"

#include <limits.h>
#include <stdio.h>
#include <stdlib.h>

static error_code create_graph(graph_t** self, int ver_num);
static error_code print_dist(graph_t** self, dijkstra_info* d_info, const char* out_stream);

static error_code create_graph(graph_t** self, const int ver_num) {
    *self = malloc(sizeof(graph_t));
    if (!*self) {
        return other_error;
    }
    (*self)->ver_num = ver_num;
    const int size = ver_num * ver_num;
    (*self)->weights = malloc(sizeof(unsigned int) * size);
    if (!(*self)->weights) {
        return other_error;
    }
    return no_error;
}

error_code fill_graph(graph_t** self, const char* in_stream) {
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
    int start, finish;
    if (fscanf(fp, "%d %d", &start, &finish) != 2) {
        fclose(fp);
        return bad_number_of_lines;
    }
    if (start < 1 || finish < 1 || start > ver_num || finish > ver_num) {
        fclose(fp);
        return bad_vertex;
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
    if (create_graph(self, ver_num) != no_error) {
        fclose(fp);
        return other_error;
    }
    (*self)->edge_num = edge_num;
    (*self)->finish = finish;
    (*self)->start = start;
    for (int i = 0; i < (*self)->ver_num * (*self)->ver_num; ++i)
        (*self)->weights[i] = 0;
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

error_code dijkstra(graph_t** self, const char* out_stream) {
    const int ver_num = (*self)->ver_num;
    dijkstra_info* d_inf = NULL;
    create_dijkstra_info(&d_inf, ver_num);
    for (int i = 0; i < ver_num; ++i) {
        d_inf->used[i] = 0;
        d_inf->min_d[i] = UINT_MAX;
    }
    d_inf->min_d[(*self)->start - 1] = 0;
    for (int i = 0; i < ver_num; ++i) {
        int v = -1;
        for (int j = 0; j < ver_num; ++j) {
            if (!d_inf->used[j] && (v == -1 || d_inf->min_d[j] < d_inf->min_d[v]))
                v = j;
        }
        if (d_inf->min_d[v] == UINT_MAX) {
            print_dist(self, d_inf, out_stream);
            destroy_dijkstra_info(&d_inf);
            return no_error;
        }
        d_inf->used[v] = 1;
        for (int to = 0; to < ver_num; ++to) {
            if (!(*self)->weights[ver_num * v + to])
                continue;
            if (!((*self)->weights[ver_num * v + to] + d_inf->min_d[v] < d_inf->min_d[to] && !d_inf->used[to]))
                continue;
            if ((*self)->weights[ver_num * v + to] + d_inf->min_d[v] <= INT_MAX)
                d_inf->min_d[to] = (*self)->weights[ver_num * v + to] + d_inf->min_d[v];
            else
                d_inf->min_d[to] = UINT_MAX - 1;
            d_inf->parent[to] = v;
        }
    }
    print_dist(self, d_inf, out_stream);
    destroy_dijkstra_info(&d_inf);
    return no_error;
}

static error_code print_dist(graph_t** self, dijkstra_info* d_inf, const char* out_stream) {
    FILE* fp = fopen(out_stream, "w");
    if(!fp){
        return other_error;
    }
    for (int i = 0; i < (*self)->ver_num; ++i) {
        if (d_inf->used[i]) {
            if (d_inf->min_d[i] > INT_MAX)
                fprintf(fp, "INT_MAX+ ");
            else
                fprintf(fp, "%u ", d_inf->min_d[i]);
        }
        else
            fprintf(fp, "oo ");
    }
    fprintf(fp, "\n");
    if (!d_inf->used[(*self)->finish - 1]) {
        fprintf(fp, "no path\n");
        fclose(fp);
        return no_error;
    }
    int count_int_max = 0;
    for (int i = 0; i < (*self)->ver_num; ++i) {
        if (d_inf->min_d[i] == UINT_MAX)
            continue;
        if (d_inf->min_d[i] <= INT_MAX)
            continue;
        count_int_max++;
        for (int j = i; j < (*self)->ver_num; ++j)
            if ((*self)->weights[(*self)->ver_num * i + j])
                count_int_max++;
    }
    if (count_int_max >= 2 && d_inf->min_d[(*self)->finish - 1] > INT_MAX) {
        fprintf(fp, "overflow\n");
        fclose(fp);
        return no_error;
    }
    for (int from = (*self)->finish - 1; from != (*self)->start - 1; from = d_inf->parent[from])
        fprintf(fp, "%d ", from + 1);
    fprintf(fp, "%d \n", (*self)->start);
    fclose(fp);
    return no_error;
}


void print_error(error_code error) {
    if (error == other_error) {
        printf("other error");
    }
    if (error == bad_number_of_lines) {
        printf("bad number of lines");
    }
    if (error == bad_number_of_vertices) {
        printf("bad number of vertices");
    }
    if (error == bad_number_of_edges) {
        printf("bad number of edges");
    }
    if (error == bad_vertex) {
        printf("bad vertex");
    }
    if (error == impossible_to_sort) {
        printf("impossible to sort");
    }
    if (error == bad_length) {
        printf("bad length");
    }
}

void destroy_graph(graph_t** self) {
    if (*self) {
        free((*self)->weights);
    }
    free(*self);
}
