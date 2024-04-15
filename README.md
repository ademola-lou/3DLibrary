#CGAL wasm implementation

# How to build
## Linux

### install libraries
```cd 3DLibrary/wasm-library && ./install_libraries.sh ```

### install emsdk (https://emscripten.org/docs/getting_started/downloads.html)

```
git clone https://github.com/emscripten-core/emsdk.git
cd emsdk
git pull
./emsdk install latest
./emsdk activate latest
source ./emsdk_env.sh
```

### building wasm library (make sure you are in /wasm-library directory)

compiling cmake file and build
```
./build.sh gener
```
after editing the main.cpp, recurrent build will be
```
./build.sh
```

check build folder for index.js and index.wasm file

# How to use

```
<html>
<body>
 <canvas id="app"></canvas>
    <script>
    var Module = {
      onRuntimeInitialized: function() {
        window.Module = Module;
        console.log("hehe", Module)
      }
    };
    </script>
    <script src="../wasm-library/build/index.js"></script>
    <script>
    const polyMesh = new Module.PolyMesh(); //First need to create an instance of the polymesh wrapper (referenced in wasm-library/main.cpp)
    
    const mesh = BABYLON.MeshBuilder.CreateBox("mesh", {size: 2});
    const position = mesh.getVerticesData(BABYLON.VertexBuffer.PositionKind);
    const indices = mesh.getIndices();
    
    //populate the polyMesh with the position data from mesh to create a CGAL::Surface_mesh
    for(let i = 0; i<position.length / 3; i++){
      polyMesh.addVertex(position[i * 3], position[i * 3 + 1], position[i * 3 + 2]);
    }
    
    for(let j = 0; j < indices.length / 3; j++){
      polyMesh.addFace([indices[j * 3], indices[j * 3 + 1], indices[j * 3 + 2]])
    }
    
    //retrieve a position/indices data to update mesh
     function getMeshData(){
        let positions_buffer = polyMesh.getVertices();
        positions = Array.from(positions_buffer);
        positions_buffer = null;

        let triangles_buffer = polyMesh.getIndices();
        let indices = Array.from(triangles_buffer);
        triangles_buffer = null;

        return {positions, indices};
    }
    
    //do a simple CGAL operation like catmull smooth
    polyMesh.catmull_smooth();
    
    //update the mesh
    const dt = getMeshData()
    const vertexData = new BABYLON.VertexData()
    vertexData.positions = dt.positions
    vertexData.indices = dt.indices
    const normals = []
    BABYLON.VertexData.ComputeNormals(dt.positions, dt.indices, normals);
    vertexData.applyToMesh(mesh, true);
    
    
    </script>
</body>
</html>

```

