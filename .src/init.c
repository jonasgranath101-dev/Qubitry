#include <stdio.h>

void graph() {

    /*
    
        Create obj file.
    
    */

}

typedef struct {
    double x;
    double y;
    double z;
} Point3D;

int write_point_file(FILE *fp, const Point3D *p) {
    /* Example text format: "x y
" */
    return fprintf(fp, "%.6f %.6f
", p->x, p->y);   /* returns number of chars or negative on error */
}

int read_point_file(FILE *fp, Point3D *p) {
    return fscanf(fp, "%lf %lf", &p->x, &p->y);      /* returns 2 on success */
}

int main(void) {
    Point3D p = {1.0, 2.0};
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
    if (read_point_file(fp, &q) != 2) {
        fclose(fp);
        return 1;
    }
    fclose(fp);

    printf("Read point: (%.3f, %.3f)
", q.x, q.y);
    return 0;
}