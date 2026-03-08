#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include <time.h>

typedef struct {
    double x;
    double y;
    double z;
} Point3D;

int write_point_file(FILE *fp, const Point3D *p) {
    return fprintf(fp, "%.6f %.6f %.6f\n", p->x, p->y, p->z);
}

int read_point_file(FILE *fp, Point3D *p) {
    return fscanf(fp, "%lf %lf %lf", &p->x, &p->y, &p->z);
}

// Generate advanced 3D shapes using simulated AI parameters
void generate_shape(const char* shape_type, float scale, float param1, float param2, FILE *fp, FILE *fp_points) {
    if (strcmp(shape_type, "cube") == 0) {
        // Cube vertices
        float vertices[8][3] = {
            {-scale,-scale,-scale}, {-scale,-scale,scale}, {-scale,scale,-scale}, {-scale,scale,scale},
            {scale,-scale,-scale}, {scale,-scale,scale}, {scale,scale,-scale}, {scale,scale,scale}
        };
        for (int i = 0; i < 8; i++) {
            fprintf(fp, "v %f %f %f\n", vertices[i][0], vertices[i][1], vertices[i][2]);
            fprintf(fp_points, "%f %f %f\n", vertices[i][0], vertices[i][1], vertices[i][2]);
        }
        // Faces
        int faces[6][4] = {
            {1,2,4,3}, {5,6,8,7}, {1,2,6,5}, {3,4,8,7}, {1,3,7,5}, {2,4,8,6}
        };
        for (int i = 0; i < 6; i++) {
            fprintf(fp, "f %d %d %d %d\n", faces[i][0], faces[i][1], faces[i][2], faces[i][3]);
        }
    } else if (strcmp(shape_type, "sphere") == 0) {
        float r = scale;
        int stacks = (int)param1; if (stacks < 5) stacks = 10;
        int slices = (int)param2; if (slices < 5) slices = 10;
        for (int i = 0; i <= stacks; i++) {
            float phi = M_PI * i / stacks;
            for (int j = 0; j < slices; j++) {
                float theta = 2 * M_PI * j / slices;
                float x = r * sinf(phi) * cosf(theta);
                float y = r * sinf(phi) * sinf(theta);
                float z = r * cosf(phi);
                fprintf(fp, "v %f %f %f\n", x, y, z);
                fprintf(fp_points, "%f %f %f\n", x, y, z);
            }
        }
    } else if (strcmp(shape_type, "cylinder") == 0) {
        float r = scale;
        float h = param1; if (h <= 0) h = scale * 2;
        int slices = (int)param2; if (slices < 5) slices = 10;
        // Bottom circle
        for (int i = 0; i < slices; i++) {
            float theta = 2 * M_PI * i / slices;
            float x = r * cosf(theta);
            float y = r * sinf(theta);
            float z = -h/2;
            fprintf(fp, "v %f %f %f\n", x, y, z);
            fprintf(fp_points, "%f %f %f\n", x, y, z);
        }
        // Top circle
        for (int i = 0; i < slices; i++) {
            float theta = 2 * M_PI * i / slices;
            float x = r * cosf(theta);
            float y = r * sinf(theta);
            float z = h/2;
            fprintf(fp, "v %f %f %f\n", x, y, z);
            fprintf(fp_points, "%f %f %f\n", x, y, z);
        }
        // Side faces
        for (int i = 0; i < slices; i++) {
            int next = (i + 1) % slices;
            fprintf(fp, "f %d %d %d %d\n", i+1, next+1, next+1+slices, i+1+slices);
        }
    } else if (strcmp(shape_type, "cone") == 0) {
        float r = scale;
        float h = param1; if (h <= 0) h = scale * 2;
        int slices = (int)param2; if (slices < 5) slices = 10;
        // Base circle
        for (int i = 0; i < slices; i++) {
            float theta = 2 * M_PI * i / slices;
            float x = r * cosf(theta);
            float y = r * sinf(theta);
            float z = -h/2;
            fprintf(fp, "v %f %f %f\n", x, y, z);
            fprintf(fp_points, "%f %f %f\n", x, y, z);
        }
        // Apex
        fprintf(fp, "v %f %f %f\n", 0.0f, 0.0f, h/2);
        fprintf(fp_points, "%f %f %f\n", 0.0f, 0.0f, h/2);
        // Faces
        for (int i = 0; i < slices; i++) {
            int next = (i + 1) % slices;
            fprintf(fp, "f %d %d %d\n", i+1, next+1, slices+1);
        }
    } else if (strcmp(shape_type, "torus") == 0) {
        float R = scale; // Major radius
        float r = param1; if (r <= 0) r = scale * 0.3; // Minor radius
        int major_segments = (int)param2; if (major_segments < 5) major_segments = 16;
        int minor_segments = 8;
        for (int i = 0; i < major_segments; i++) {
            float phi = 2 * M_PI * i / major_segments;
            for (int j = 0; j < minor_segments; j++) {
                float theta = 2 * M_PI * j / minor_segments;
                float x = (R + r * cosf(theta)) * cosf(phi);
                float y = (R + r * cosf(theta)) * sinf(phi);
                float z = r * sinf(theta);
                fprintf(fp, "v %f %f %f\n", x, y, z);
                fprintf(fp_points, "%f %f %f\n", x, y, z);
            }
        }
    } else {
        // Default to octahedron
        float s = scale;
        float vertices[6][3] = {
            {s, 0, 0}, {-s, 0, 0}, {0, s, 0}, {0, -s, 0}, {0, 0, s}, {0, 0, -s}
        };
        for (int i = 0; i < 6; i++) {
            fprintf(fp, "v %f %f %f\n", vertices[i][0], vertices[i][1], vertices[i][2]);
            fprintf(fp_points, "%f %f %f\n", vertices[i][0], vertices[i][1], vertices[i][2]);
        }
        // Faces
        int faces[8][3] = {
            {1,3,5}, {1,5,4}, {1,4,6}, {1,6,3}, {2,3,5}, {2,5,4}, {2,4,6}, {2,6,3}
        };
        for (int i = 0; i < 8; i++) {
            fprintf(fp, "f %d %d %d\n", faces[i][0], faces[i][1], faces[i][2]);
        }
    }
}

// Simulate AI parameter generation based on description
void generate_ai_parameters(const char* description, const char* shape_type, float* scale, float* param1, float* param2) {
    // Simple AI simulation - analyzes description for keywords
    srand(time(NULL));

    // Base parameters
    *scale = 1.0f + (rand() % 100) / 50.0f; // 1.0 to 3.0

    if (strstr(description, "small") || strstr(description, "tiny")) {
        *scale *= 0.5f;
    } else if (strstr(description, "large") || strstr(description, "big")) {
        *scale *= 2.0f;
    }

    if (strcmp(shape_type, "sphere") == 0) {
        *param1 = 8 + rand() % 8; // stacks
        *param2 = 8 + rand() % 8; // slices
        if (strstr(description, "smooth")) {
            *param1 += 4;
            *param2 += 4;
        }
    } else if (strcmp(shape_type, "cylinder") == 0) {
        *param1 = *scale * (1.5f + (rand() % 100) / 50.0f); // height
        *param2 = 8 + rand() % 8; // slices
        if (strstr(description, "tall")) {
            *param1 *= 2.0f;
        }
    } else if (strcmp(shape_type, "cone") == 0) {
        *param1 = *scale * (1.5f + (rand() % 100) / 50.0f); // height
        *param2 = 8 + rand() % 8; // slices
        if (strstr(description, "sharp") || strstr(description, "pointed")) {
            *param1 *= 1.5f;
        }
    } else if (strcmp(shape_type, "torus") == 0) {
        *param1 = *scale * (0.2f + (rand() % 50) / 100.0f); // minor radius
        *param2 = 12 + rand() % 8; // major segments
        if (strstr(description, "thick")) {
            *param1 *= 1.5f;
        }
    } else {
        *param1 = 0;
        *param2 = 0;
    }
}

void generate_ai_shape(const char* description, const char* shape_type) {
    // Create output directory
    system("mkdir -p output");

    // Generate AI parameters
    float scale, param1, param2;
    generate_ai_parameters(description, shape_type, &scale, &param1, &param2);

    // Generate timestamped filename
    time_t t = time(NULL);
    char filename[100];
    sprintf(filename, "output/shape_%ld.obj", t);

    FILE *fp = fopen(filename, "w");
    if (!fp) {
        printf("Error: Cannot create OBJ file\n");
        return;
    }

    FILE *fp_points = fopen("output/points.txt", "w");
    if (!fp_points) {
        fclose(fp);
        printf("Error: Cannot create points file\n");
        return;
    }

    printf("AI Analysis: '%s'\n", description);
    printf("Generating %s with AI parameters: scale=%.2f, param1=%.2f, param2=%.2f\n",
           shape_type, scale, param1, param2);

    generate_shape(shape_type, scale, param1, param2, fp, fp_points);

    fclose(fp);
    fclose(fp_points);

    printf("OBJ file generated: %s\n", filename);
}

int main(int argc, char *argv[]) {
    if (argc >= 3) {
        generate_ai_shape(argv[1], argv[2]);
        return 0;
    }

    // Test mode
    Point3D p = {1.0, 2.0, 3.0};
    FILE *fp = fopen("test_points.txt", "w");
    if (!fp) return 1;

    if (write_point_file(fp, &p) < 0) {
        fclose(fp);
        return 1;
    }
    fclose(fp);

    fp = fopen("test_points.txt", "r");
    if (!fp) return 1;

    Point3D q;
    if (read_point_file(fp, &q) != 3) {
        fclose(fp);
        return 1;
    }
    fclose(fp);

    printf("Test point: (%.3f, %.3f, %.3f)\n", q.x, q.y, q.z);
    return 0;
}