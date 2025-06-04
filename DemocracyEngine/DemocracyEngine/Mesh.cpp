//#include "Mesh.h"
//
//Mesh::Mesh(std::vector<Vertex> vertices, std::vector<unsigned int> indices, std::vector<Texture> textures)
//    : vertices(vertices), indices(indices), textures(textures) {
//    setupMesh();
//}
//
//void Mesh::setupMesh() {
//    glGenVertexArrays(1, &VAO);
//    glGenBuffers(1, &VBO);
//    glGenBuffers(1, &EBO);
//
//    glBindVertexArray(VAO);
//    glBindBuffer(GL_ARRAY_BUFFER, VBO);
//    glBufferData(GL_ARRAY_BUFFER, vertices.size() * sizeof(Vertex), &vertices[0], GL_STATIC_DRAW);
//
//    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
//    glBufferData(GL_ELEMENT_ARRAY_BUFFER, indices.size() * sizeof(unsigned int), &indices[0], GL_STATIC_DRAW);
//
//    // Positions
//    glEnableVertexAttribArray(0);
//    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)0);
//
//    // Normals
//    glEnableVertexAttribArray(1);
//    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)offsetof(Vertex, Normal));
//
//    // Texture Coords
//    glEnableVertexAttribArray(2);
//    glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)offsetof(Vertex, TexCoords));
//
//    glBindVertexArray(0);
//}
//
//void Mesh::Draw(unsigned int shaderProgram) {
//    unsigned int diffuseNr = 1;
//    unsigned int specularNr = 1;
//
//    for (unsigned int i = 0; i < textures.size(); i++) {
//        glActiveTexture(GL_TEXTURE0 + i);
//        std::string name = textures[i].type;
//        std::string number = (name == "texture_diffuse") ? std::to_string(diffuseNr++) : std::to_string(specularNr++);
//        glUniform1i(glGetUniformLocation(shaderProgram, (name + number).c_str()), i);
//        glBindTexture(GL_TEXTURE_2D, textures[i].id);
//    }
//
//    glBindVertexArray(VAO);
//    glDrawElements(GL_TRIANGLES, static_cast<unsigned int>(indices.size()), GL_UNSIGNED_INT, 0);
//    glBindVertexArray(0);
//
//    glActiveTexture(GL_TEXTURE0);
//}
