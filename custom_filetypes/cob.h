struct Header{
    char* Magic[4];
    int Version;
    int VertexCount;
    int VertexTexCoordCount;
    int VertexNormalCount;
    int FaceCount;
};
struct Vertex{
    float x;
    float y;
    float z;
};
struct VertexTexCoord{
    float u;
    float v;
};

struct VertexNormal{
    float x;
    float y;
    float z;
};
struct Face{
    int VertexId[3];
    int TexCoordId[3];
    int NormalId[3];
};
