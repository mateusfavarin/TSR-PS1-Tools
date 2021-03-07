# MDL file documentation

The MDL files holds two data sections: the first section contains geometry data of each racer, and the second section is unknown.

## File structure

The file starts with a number indicating the section size.

| Offset (h) | Size (h) | Usage                          | Notes                                                                        |
|:---------- |:-------- |:------------------------------ |:---------------------------------------------------------------------------- |
| 0x0        | 0x4      | Half size of the geometry data | Multiplying this number by 2 gives you the offset of the second data section |

## Geometry Section

The geometry section contains the coordinates, colors, drawing format (tri or quad) and palette information of the model vertexes.

| Offset (h) | Size (h) | Usage                               | Notes                                        |
|:---------- |:-------- |:----------------------------------- |:-------------------------------------------- |
| 0x0        | 0x1u     | Red intensity of the vertex color   | Used as shading, since the model is textured |
| 0x1        | 0x1u     | Green intensity of the vertex color | Used as shading, since the model is textured |
| 0x2        | 0x1u     | Blue intensity of the vertex color  | Used as shading, since the model is textured |
| 0x3        | 0x1u     | Color command (cmd)                 | This byte is ignored if you aren't reading the first vertex of a face. If cmd equals 0, then a new mesh starts. If cmd equals 0x38, then the next 3 vertexes will form a quad with the current vertex; if cmd does not equal 0x38, then the next 2 vertexes will make a triangle with the current vertex |
| 0x4        | 0x2s     | X position of the vertex            | -                                            |
| 0x6        | 0x2s     | Y position of the vertex            | -                                            |
| 0x8        | 0x2s     | Z position of the vertex            | -                                            |
| 0xA        | 0x2s     | Vertex palette                      | Texture data is still unknown                |

## Unknown section

Work in progress.