# MDL file documentation

The MDL files holds two data sections: the first section contains geometry data for each object in the file, and the second section contains metadata about each object.

## File structure

The file starts with a number indicating the section size.

| Offset (h) | Size (h)  | Description                       |
|:---------- |:--------- |:--------------------------------- |
| 0x0        | 0x4u      | Half size of the geometry section |
Size: 0x4 bytes

## Geometry Section

The geometry section contains an array of vertexes with the GPU render command, vertex colors, vertex position and texture coordinate positions. The game decides whether the next polygon is a triangle or a quad by looking at the GPU render command of the first vertex.

| Offset (h) | Size (h) | Description         |
|:---------- |:-------- |:------------------- |
| 0x0        | 0x1u     | Vertex Color: Red   |
| 0x1        | 0x1u     | Vertex Color: Green |
| 0x2        | 0x1u     | Vertex Color: Blue  |
| 0x3        | 0x1u     | GPU Render Command  |
| 0x4        | 0x2s     | Position: X         |
| 0x6        | 0x2s     | Position: Y         |
| 0x8        | 0x2s     | Position: Z         |
| 0xA        | 0x1u     | Texcoord: X         |
| 0xB        | 0x1u     | Texcoord: Y         |
Size: 0xC bytes

## Mesh metadata

This section starts with a number indicating the number of objects in the file. Each object might have one or two meshes, for level of detail purposes.

| Offset (h) | Size (h) | Description                    |
|:---------- |:-------- |:------------------------------ |
| 0x0        | 0x4u     | Number of objects in the file. |
Total size: 0x4

It's followed by a data structure with size of 0x4C bytes, which contains metadata for each object.

| Offset (h) | Size (h) | Description                            |
|:---------- |:-------- |:-------------------------------------- |
| 0x0        | 0x4u     | Offset to the end of the object halved |
| 0x4        | 0x4s     | Position: X translation                |
| 0x8        | 0x4s     | Position: Y translation                |
| 0xC        | 0x4s     | Position: Z translation                |
| 0x10-0x4C  | -        | Unknown                                |
Size: 0x4C bytes