const { Module } = window as any;
import { Nullable } from "@babylonjs/core/types";

interface PopulateMeshSoupParams {
    positions: number[];
    indices: number[][];
}

interface MeshData {
    positions: any [];
    indices: any [];
}

interface DecimateMeshParams {
    targetCount: number;
}

interface SegmentMeshParams {
    number_clusters: number;
    smooth_lambda: number;
}

export enum Smooth_Algorithm {
    Catmull_Clark = 0,
    Loop = 1,
    Doo_Sabin = 2,
    Sqrt = 3
}

export class CGALWrapper {
    protected static polyMesh: any;
    constructor(){}
    public static init(){
    //make sure we are removing the old polyMesh
    const test = function(){
        // console.log("passing func")
        return 6;
    }

    if(this.polyMesh){
        delete this.polyMesh;
        this.polyMesh = null;
    }
    this.polyMesh = new Module.PolyMesh();
    // this.polyMesh.defineSDF(test);
    console.log(this.polyMesh);//.sdf_p.y())
    }
    public static populateMesh(params: PopulateMeshSoupParams): void {
        for(let i = 0; i < params.positions.length; i+=3){
            this.polyMesh.addVertex(params.positions[i], params.positions[i+1], params.positions[i+2]);
        }
        
        for(let i = 0; i < params.indices.length; i++){
            const face = params.indices[i];
            this.polyMesh.addFace(face);
        }
    }
    public static smoothMesh(smoothType: Smooth_Algorithm): void {
        switch (smoothType) {
            case Smooth_Algorithm.Catmull_Clark:
                this.polyMesh.catmull_smooth();
            break;
            case Smooth_Algorithm.Loop:
                this.polyMesh.loop_smooth();
            break;
            case Smooth_Algorithm.Doo_Sabin:
                this.polyMesh.dooSabin_smooth();
            break;
            case Smooth_Algorithm.Sqrt:
                this.polyMesh.sqrt_smooth();
            break;
        }
    }
    public static decimateMesh(params: DecimateMeshParams): void {
        this.polyMesh.decimate(params.targetCount);
    }

    public static getMeshData(): MeshData {
        let positions_buffer = this.polyMesh.getVertices();
        let positions = Array.from(positions_buffer);
        positions_buffer = null;

        let triangles_buffer = this.polyMesh.getIndices();
        let indices = Array.from(triangles_buffer);
        triangles_buffer = null;

        return {positions, indices};
    }

    public static segmentMesh(params: any): number[] {
        let segments: number[];
        if(params){
            let segments_buffer = this.polyMesh.segment(params.number_clusters, params.smooth_lambda);
            segments = Array.from(segments_buffer);
            segments_buffer = null;
        }else{
            let segments_buffer = this.polyMesh.segment(0, 0);
            segments = Array.from(segments_buffer);
            segments_buffer = null;
        }
        return segments;
    }

    public static parametizeMesh(): void {
        // this.polyMesh.segMent()
        //parametizeMesh();
    }

    public static generateSDFMesh(): void {
        // this.polyMesh.createSDFMesh();
        // const sdf = new Module.SDFGenerator();
    }
}