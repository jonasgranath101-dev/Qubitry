#include <stdio.h>

// AI handle.

#include "../OneCoreAI/.core/handle.h"
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

// Parse a string of coordinates into a list of points.
// Supported formats:
// - "x,y,z;x,y,z;..." (semicolon-separated)
// - "x y z\n..." (whitespace-separated triples)
// - Mixed commas and whitespace.
// Returns the number of points parsed (0 on failure).
int parse_points(const char *input, Point3D **out_points, int *out_count) {
    if (!input || !out_points || !out_count) return 0;

    char *buf = strdup(input);
    if (!buf) return 0;

    size_t max_points = 64;
    Point3D *points = malloc(sizeof(Point3D) * max_points);
    if (!points) {
        free(buf);
        return 0;
    }

    int count = 0;
    // Split on semicolons or newlines first
    char *segment = strtok(buf, ";\n");
    while (segment) {
        // Trim leading/trailing whitespace
        while (*segment == ' ' || *segment == '\t') segment++;
        size_t len = strlen(segment);
        while (len && (segment[len - 1] == ' ' || segment[len - 1] == '\t')) {
            segment[--len] = '\0';
        }

        if (len == 0) {
            segment = strtok(NULL, ";\n");
            continue;
        }

        // Replace commas with spaces for easier parsing
        for (char *p = segment; *p; ++p) {
            if (*p == ',') *p = ' ';
        }

        // Try to parse exactly three numbers first
        double x, y, z;
        if (sscanf(segment, "%lf %lf %lf", &x, &y, &z) == 3) {
            if (count >= (int)max_points) {
                max_points *= 2;
                Point3D *tmp = realloc(points, sizeof(Point3D) * max_points);
                if (!tmp) break;
                points = tmp;
            }
            points[count].x = x;
            points[count].y = y;
            points[count].z = z;
            count++;
        } else {
            // Fallback: parse any whitespace-delimited numbers and group them in triples
            double nums[1024];
            int num_count = 0;
            char *tok = strtok(segment, " \t");
            while (tok && num_count < (int)(sizeof(nums) / sizeof(nums[0]))) {
                char *end;
                double v = strtod(tok, &end);
                if (end == tok) break;
                nums[num_count++] = v;
                tok = strtok(NULL, " \t");
            }
            for (int i = 0; i + 2 < num_count; i += 3) {
                if (count >= (int)max_points) {
                    max_points *= 2;
                    Point3D *tmp = realloc(points, sizeof(Point3D) * max_points);
                    if (!tmp) break;
                    points = tmp;
                }
                points[count].x = nums[i];
                points[count].y = nums[i + 1];
                points[count].z = nums[i + 2];
                count++;
            }
        }

        segment = strtok(NULL, ";\n");
    }

    free(buf);

    if (count == 0) {
        free(points);
        *out_points = NULL;
        *out_count = 0;
        return 0;
    }

    *out_points = points;
    *out_count = count;
    return 1;
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
    sprintf(filename, ".src/example_%ld.obj", t);
    FILE *fp = fopen(filename, "w");
    if (!fp) return;
    FILE *fp_points = fopen(".bin/utility.txt", "w");
    if (!fp_points) { fclose(fp); return; }

    // Handle custom coordinate input: allow a list of points provided via the first argument.
    // Example: "0,0,0; 1,0,0; 1,1,0" or "0 0 0\n1 0 0\n1 1 0"
    int use_custom = 0;
    Point3D *custom_points = NULL;
    int custom_count = 0;

    if (obj && (strstr(shape, "coord") || strstr(shape, "custom") || strchr(obj, ';') || strchr(obj, ','))) {
        if (parse_points(obj, &custom_points, &custom_count) && custom_count > 0) {
            use_custom = 1;
        }
    }

    if (use_custom) {
        // Normalize and scale custom points relative to the learned AI weight.
        double minx = custom_points[0].x, maxx = custom_points[0].x;
        double miny = custom_points[0].y, maxy = custom_points[0].y;
        double minz = custom_points[0].z, maxz = custom_points[0].z;
        for (int i = 1; i < custom_count; i++) {
            if (custom_points[i].x < minx) minx = custom_points[i].x;
            if (custom_points[i].x > maxx) maxx = custom_points[i].x;
            if (custom_points[i].y < miny) miny = custom_points[i].y;
            if (custom_points[i].y > maxy) maxy = custom_points[i].y;
            if (custom_points[i].z < minz) minz = custom_points[i].z;
            if (custom_points[i].z > maxz) maxz = custom_points[i].z;
        }
        double range_x = maxx - minx;
        double range_y = maxy - miny;
        double range_z = maxz - minz;
        double max_range = range_x;
        if (range_y > max_range) max_range = range_y;
        if (range_z > max_range) max_range = range_z;
        if (max_range < 1e-6) max_range = 1.0;

        double target_scale = scale;
        if (target_scale <= 0.0f) target_scale = 1.0f;

        for (int i = 0; i < custom_count; i++) {
            // Normalize to -0.5..0.5 then scale
            double nx = (custom_points[i].x - minx) / max_range - 0.5;
            double ny = (custom_points[i].y - miny) / max_range - 0.5;
            double nz = (custom_points[i].z - minz) / max_range - 0.5;
            double sx = nx * target_scale * 2.0;
            double sy = ny * target_scale * 2.0;
            double sz = nz * target_scale * 2.0;
            fprintf(fp, "v %f %f %f\n", sx, sy, sz);
            fprintf(fp_points, "%f %f %f\n", sx, sy, sz);
        }

        free(custom_points);
    } else if (strstr(shape, "cube")) {
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
