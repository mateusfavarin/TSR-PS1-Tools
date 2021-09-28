# MDL file documentation

The MDL files holds two data sections: the first section contains geometry data of each racer, and the second section is unknown.

## File structure

The file starts with a number indicating the section size.

| Offset (h) | Size (h)  | Usage                             | Notes                                                                           |
|:---------- |:--------- |:--------------------------------- |:------------------------------------------------------------------------------- |
| 0x0        | 0x4u      | Half size of the geometry section | Multiplying this number by 2 gives you the offset of the mesh metadata section. |

## Geometry Section

The geometry section contains the coordinates, colors, drawing format (tri or quad) and palette information of the model vertexes.

| Offset (h) | Size (h) | Usage                               | Notes                                        |
|:---------- |:-------- |:----------------------------------- |:-------------------------------------------- |
| 0x0        | 0x1u     | Red                 | Vertex color intensity (R, G, B). Used as shading, since the model is textured. |
| 0x1        | 0x1u     | Green               | Vertex color intensity (R, G, B). Used as shading, since the model is textured. |
| 0x2        | 0x1u     | Blue                | Vertex color intensity (R, G, B). Used as shading, since the model is textured. |
| 0x3        | 0x1u     | Color command (cmd) | This byte is ignored if you aren't reading the first vertex of a face. If cmd equals 0, then a new mesh starts. If cmd equals 0x38, then the next 3 vertexes will form a quad with the current vertex; if cmd does not equal 0x38, then the next 2 vertexes will make a triangle with the current vertex.                                                                   |
| 0x4        | 0x2s     | X                   | Position of the vertex.                                                         |
| 0x6        | 0x2s     | Y                   | Position of the vertex.                                                         |
| 0x8        | 0x2s     | Z                   | Position of the vertex.                                                         |
| 0xA        | 0x2s     | Vertex palette      | Texture data is still unknown.                                                  |

## Mesh metadata

This section starts with a number indicating the number of objects in the file. Each object has a high LOD mesh and a low LOD mesh (LOD = Level of Detail).

| Offset (h) | Size (h) | Usage                          | Notes                                      |
|:---------- |:-------- |:------------------------------ |:------------------------------------------ |
| 0x0        | 0x4u     | Number of objects in the file. | Multiplying by 2 gives you the mesh count. |

It's followed by a data structure with size of 0x4C bytes, which contains metadata of each object.

| Offset (h) | Size (h) | Usage                                         | Notes                                                |
|:---------- |:-------- |:--------------------------------------------- |:---------------------------------------------------- |
| 0x0        | 0x4u     | Size of the mesh (high + low LOD).            | N/a.                                                 |
| 0x4        | 0x4s     | X translation.                                | Translation applied to both high and low LOD meshes. |
| 0x8        | 0x4s     | Y translation.                                | Translation applied to both high and low LOD meshes. |
| 0xC        | 0x4s     | Z translation.                                | Translation applied to both high and low LOD meshes. |
| 0x10~0x48  | -        | Unknown.                                      | Unknown.                                             |