
#ifndef OBJLOADER_H
#define OBJLOADER_H

#include <vector>
#include <string>
#include <glm/glm.hpp>

class ObjLoader {
  public:
    ObjLoader();
    ~ObjLoader();

    void load(std::string filename);

    int getIndexCount();
    int getVertCount();

    void getFaceIndexData(std::vector<unsigned int> &arg_indices);
    void getPositionData(std::vector<glm::vec3> &arg_verts);
    void getNormalData(std::vector<glm::vec3> &arg_normals);

  private:
    std::vector<glm::vec3> Vertecies;
    std::vector<glm::vec3> Normals;
    std::vector<unsigned int> Indices;

    void clear();

};

#endif // OBJLOADER_H

