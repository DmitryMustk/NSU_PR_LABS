#include <stdio.h>
#include <stdlib.h>

#include "constants.h"
#include "graph.h"

static int create_graph(graph_t** self, const int verticle_number, const int edge_number) {
    *self = malloc(sizeof(graph_t));
    if (!*self)
        return other_error;
    (*self)->verticle_number = verticle_number;
    (*self)->edge_number = edge_number;
    (*self)->sorted = (short*) malloc(sizeof(short) * (*self)->verticle_number);
    if (!(*self)->sorted) {
        destroy_graph(self);
        return other_error;
    }
    int size = (*self)->verticle_number * (*self)->verticle_number;
    int byteSize = size / 8 + (size % 8 != 0);
    (*self)->matrix = malloc(sizeof(char) * byteSize);
    if (!(*self)->matrix) {
        destroy_graph(self);
        return other_error;
    }
    for (int i = 0; i < byteSize; i++)
        (*self)->matrix[i] = 0;
    return no_error;
}

static void set_bit_to_1(graph_t** self, int bit) {
    (*self)->matrix[bit >> 3] |= (char) (1 << (bit & 7));
}

static char getBit(graph_t** self, int bit) {
    return ((*self)->matrix[bit >> 3] & (char) (1 << (bit & 0x7)));
}

int fill_graph(graph_t** self, const char* in_stream) {
    FILE* fp = fopen(in_stream, "r");
    if(!fp)
        return other_error;
    int verticle_number, edge_number;
    if (fscanf(fp, "%d %d", &verticle_number, &edge_number) != 2) {
        fclose(fp);
        return bad_number_of_lines;
    }
    if (verticle_number < 0 || verticle_number > 2000) {
        fclose(fp);
        return bad_number_of_vertices;
    }
    if (edge_number > verticle_number * (verticle_number + 1) / 2) {
        fclose(fp);
        return bad_number_of_edges;
    }
    if (create_graph(self, verticle_number, edge_number) != no_error) {
        fclose(fp);
        return other_error;
    }
    for (int i = 0; i < edge_number; ++i) {
        int a, b;
        if (fscanf(fp, "%d %d", &a, &b) != 2) {
            fclose(fp);
            return bad_number_of_lines;
        }
        if (a < 1 || b < 1 || a > verticle_number || b > verticle_number) {
            fclose(fp);
            return bad_vertex;
        }
        set_bit_to_1(self, (a - 1) * (*self)->verticle_number + (b - 1));
    }
    fclose(fp);
    return no_error;
}

static int tarjan_step(graph_t** self, short num, char* verticle_color, int* sorted_graph_height) {
    verticle_color[num] = gray;
    int k = num * (*self)->verticle_number;
    for (int i = 0; i < (*self)->verticle_number; i++)
        if (getBit(self, k + i)) {
            char color = verticle_color[i];
            if (color == gray)
                return -1;// error, cycle found
            if (color == white)
                if (tarjan_step(self, i, verticle_color, sorted_graph_height) != 0)
                    return -1;// error, cycle found
        }
    verticle_color[num] = black;
    (*self)->sorted[(*sorted_graph_height)++] = num;
    return 0;
}

int tarjan_algorithm(graph_t** self, error_code error) {
    if(error != no_error){
        return error;
    }
    int sorted_graph_height = 0;
    char* verticle_colors = malloc(sizeof(char) * (*self)->verticle_number);
    for (short i = 0; i < (*self)->verticle_number; i++)
        verticle_colors[i] = white;
    for (short i = 0; i < (*self)->verticle_number; i++)
        if (verticle_colors[i] == white && tarjan_step(self, i, verticle_colors, &sorted_graph_height) != 0) {
            free(verticle_colors);
            return impossible_to_sort;
        }
    free(verticle_colors);
    return no_error;
}

void print_error(error_code error, const char* out_stream){
    FILE* fp = fopen(out_stream, "w");
    if(!fp){
        return;
    }
    if(error == other_error){
        fprintf(fp, "other error");
    }
    if(error == bad_number_of_lines){
        fprintf(fp, "bad number of lines");
    }
    if(error == bad_number_of_vertices){
        fprintf(fp, "bad number of vertices");
    }
    if(error == bad_number_of_edges){
        fprintf(fp, "bad number of edges");
    }
    if(error == bad_vertex){
        fprintf(fp, "bad vertex");
    }
    if(error == impossible_to_sort){
        fprintf(fp, "impossible to sort");
    }
    fclose(fp);
}

void print_graph(graph_t** self, const char* out_stream){
    FILE* fp = fopen(out_stream, "w");
    if(!fp){
        return;
    }
    for (int i = (*self)->verticle_number - 1; i >= 0; i--)
        fprintf(fp, "%d\n", (*self)->sorted[i] + 1);
    fclose(fp);
}

void destroy_graph(graph_t** self) {
    if (*self) {
        free((*self)->sorted);
        free((*self)->matrix);
    }
    free(*self);
}
