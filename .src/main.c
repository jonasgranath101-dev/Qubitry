#include <stdio.h>

// AI handle.

<<<<<<< HEAD
#include "../AI/.core/handle.h"
=======
#include "AI/.core/handle.h"
>>>>>>> origin/main
#include <math.h>
#include <string.h>
#include <stdlib.h>
#include <time.h>

typedef struct {
    double x;
    double y;
    double z;
} Point3D;

int write_point_file(FILE *fp, const Point3D *p) {
    /* Example text format: "x y z\n" */
    return fprintf(fp, "%.6f %.6f %.6f\n", p->x, p->y, p->z);   /* returns number of chars or negative on error */
}

int read_point_file(FILE *fp, Point3D *p) {
    return fscanf(fp, "%lf %lf %lf", &p->x, &p->y, &p->z);      /* returns 3 on success */
}

void graph(const char* obj, const char* shape);

int main(int argc, char *argv[]) {
    if (argc >= 3) {
        graph(argv[1], argv[2]);
        return 0;
    }

    Point3D p = {1.0, 2.0, 3.0};
    FILE *fp = fopen("points.txt", "w");
    if (!fp) return 1;

    if (write_point_file(fp, &p) < 0) {
        fclose(fp);
        return 1;
    }
    fclose(fp);

    fp = fopen("points.txt", "r");
    if (!fp) return 1;

    Point3D q;
    if (read_point_file(fp, &q) != 3) {
        fclose(fp);
        return 1;
    }
    fclose(fp);

    printf("Read point: (%.3f, %.3f, %.3f)\n", q.x, q.y, q.z);
    return 0;
}

void graph(const char* obj, const char* shape) {
    // Create .bin if not exists
    system("mkdir -p .bin");
    // Train AI core
    core_create("graph_core", 0.01f, 50);
    block_run();
    AICore* core = core_get(1);
    float scale = core ? core->weight : 1.0f;
    // Generate new OBJ file
    time_t t = time(NULL);
    char filename[50];
<<<<<<< HEAD
    sprintf(filename, ".src/example_%ld.obj", t);
=======
    sprintf(filename, "example_%ld.obj", t);
>>>>>>> origin/main
    FILE *fp = fopen(filename, "w");
    if (!fp) return;
    FILE *fp_points = fopen(".bin/utility.txt", "w");
    if (!fp_points) { fclose(fp); return; }
    if (strstr(shape, "cube")) {
        // Cube vertices
        float vertices[8][3] = {
            {-1*scale,-1*scale,-1*scale}, {-1*scale,-1*scale,1*scale}, {-1*scale,1*scale,-1*scale}, {-1*scale,1*scale,1*scale},
            {1*scale,-1*scale,-1*scale}, {1*scale,-1*scale,1*scale}, {1*scale,1*scale,-1*scale}, {1*scale,1*scale,1*scale}
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
    } else if (strstr(shape, "sphere")) {
        float r = scale;
        int stacks = 10;
        int slices = 10;
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
    } else {
        // Default cube
        float vertices[8][3] = {
            {-1*scale,-1*scale,-1*scale}, {-1*scale,-1*scale,1*scale}, {-1*scale,1*scale,-1*scale}, {-1*scale,1*scale,1*scale},
            {1*scale,-1*scale,-1*scale}, {1*scale,-1*scale,1*scale}, {1*scale,1*scale,-1*scale}, {1*scale,1*scale,1*scale}
        };
        for (int i = 0; i < 8; i++) {
            fprintf(fp, "v %f %f %f\n", vertices[i][0], vertices[i][1], vertices[i][2]);
            fprintf(fp_points, "%f %f %f\n", vertices[i][0], vertices[i][1], vertices[i][2]);
        }
        int faces[6][4] = {
            {1,2,4,3}, {5,6,8,7}, {1,2,6,5}, {3,4,8,7}, {1,3,7,5}, {2,4,8,6}
        };
        for (int i = 0; i < 6; i++) {
            fprintf(fp, "f %d %d %d %d\n", faces[i][0], faces[i][1], faces[i][2], faces[i][3]);
        }
    }
    fclose(fp);
    fclose(fp_points);
}

#ifdef __cplusplus
#include <emscripten/bind.h>
using namespace emscripten;

class MyClass {
public:
    MyClass(int x) {}
    std::string graph(std::string obj, std::string shape) {
        ::graph(obj.c_str(), shape.c_str());
        return "OBJ generated for " + shape;
    }
};

EMSCRIPTEN_BINDINGS(my_module) {
    class_<MyClass>("MyClass")
        .constructor<int>()
        .function("graph", &MyClass::graph);
}
#endif
