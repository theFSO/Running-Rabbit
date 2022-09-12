#ifndef OBJECT_H
#define OBJECT_H

#include <vector>
#include <string>

/**
 * @brief The enum class of all types of objects
 * 
 */
enum ObjectType { PLAYER, OBSTACLE, LANE };

enum Material
{
    BLUE_RUBBER = 1, BRASS = 2, BRONZE = 3, GOLD = 4, COPPER = 5, CYAN_PLASTIC = 6, RUBY = 7, GREEN_RUBBER=8, NO = 9
};
/**
 * @brief Generic object (coordinates, type specfier, obj loader logic)
 * 
 */
class Object
{
public:
	float positionX; // The x position
	float positionY; // The y position
	float positionZ; // The z position

	int color; // The colour of the object
    Material obj_mat;
	ObjectType type; // The type of the object
	Object(float x = 0, float y = 0, float z = 0, int color = 0);
	void obj_render(int counter);
    bool load_obj(const char *path, int list);
    void apply_obj_mat();


private:

    class Face {
    public:
        int edge;
        int *vertices;
        int *texcoords;
        int normal;

        Face(int edge, int *vertices, int *texcoords, int normal = -1) {
            this->edge = edge;
            this->vertices = vertices;
            this->texcoords = texcoords;
            this->normal = normal;
        }
    };
    GLuint list1;
    std::vector<float *> veI;
    std::vector<float *> uvI;
    std::vector<float *> noI;
    std::vector<Face> faces;
    GLuint list2;
    GLuint list3;

    void setAmb(float x, float y, float z, float a);
    void setDiff(float x, float y, float z, float a);
    void setSpec(float x, float y, float z, float a);
    void setShin(float s);
};




#endif