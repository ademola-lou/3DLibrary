import { VertexBuffer } from "@babylonjs/core/Buffers/buffer";
import { StandardMaterial } from "@babylonjs/core/Materials/standardMaterial";
import { Mesh } from "@babylonjs/core/Meshes/mesh";
import { VertexData } from "@babylonjs/core/Meshes/mesh.vertexData";
import { Scene } from "@babylonjs/core/scene";

export const vertexData = new VertexData();
export function updateMesh(targetMesh, params) {
    const positions = params.positions;
    const indices = params.indices;
    if(!params.normals){
        params.normals = [];
        VertexData.ComputeNormals(positions, indices, params.normals);
    }
    vertexData.positions = positions;
    vertexData.indices = indices;
    vertexData.normals = params.normals;
    vertexData.colors = params.colors;
    vertexData.applyToMesh(targetMesh, true);
}

export function createMesh(scene, params) {
    const mesh = new Mesh("custom_mesh", scene);
    updateMesh(mesh, params);
    mesh.material = new StandardMaterial("mat", scene);
    mesh.material.backFaceCulling = false;
    mesh.rotation.y = Math.PI;
    return mesh;
}